/*
 * NOTE: compile using -std=gnu99
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/wait.h>

int sum_arr(int* arr, int start, int end)
{
	int sum = 0;

	for (int i = start; i <= end; i++)
		sum += arr[i];

	return sum;
}

// taken from stackoverflow
void* create_shared_memory(size_t size) {
	// Our memory buffer will be readable and writable:
	int protection = PROT_READ | PROT_WRITE;

	// The buffer will be shared (meaning other processes can access it), but
	// anonymous (meaning third-party processes cannot obtain an address for it),
	// so only this process and its children will be able to use it:
	int visibility = MAP_ANONYMOUS | MAP_SHARED;

	// The remaining parameters to `mmap()` are not important for this use case,
	// but the manpage for `mmap` explains their purpose.
	return mmap(NULL, size, protection, visibility, 0, 0);
}

int arr[1000];

int main(void)
{
	for (int i = 0; i < 1000; i++)
		arr[i] = (i + 1);
	int* shmem = create_shared_memory(sizeof(int) * 10);

	for (int i = 0; i < 10; i++)
	{
		if (fork() == 0)
		{
			printf("IN CHILD PROCESS OF ID = %d\n", getpid());

			// do something
			int ans;
			ans = sum_arr(arr, i * 100, (i + 1) * 100 - 1);

			// write in shared memory
			shmem[i] = ans;

			// now die
			exit(i);
		}
	}

	pid_t wpid;
	int total_sum = 0;
	int status;
	while ((wpid = wait(&status)) > 0)
	{
		if (wpid != getpid())
		{
			printf("Process %d returned!\n", wpid);
			//printf("sum = %d\n", shmem[WEXITSTATUS(status)]);
			total_sum += shmem[WEXITSTATUS(status)];
		}
	}

	printf("Total = %d\n", total_sum);
	return 0;
}
