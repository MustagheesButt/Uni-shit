#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int arr[1000];

int main(void)
{
    for (int i = 0; i < 1000; i++)
        arr[i] = (i + 1);

    // creating pipe
    int fd[2];
    if (pipe(fd) == -1)
	{
	    printf("Pipe could not be created!\n" );
	    return -1;
	}

    int base = 0;
    for (int i = 0; i < 10; i++)
    {
        pid_t pid;
        if ((pid = fork()) == -1)
        {
            printf("An unexpected error occurred!\n");
            return -1;
        }
       
        if (pid == 0)
        {
            int sum = 0;
            for (int j = base; j < base + 100; j++)
            {
                sum += arr[j];
            }

            write(fd[1], &sum, sizeof(int));
            close(fd[1]);
            
            return 0;
        }

        base = base + 100;
    }

    int total_sum = 0;
    for (int i = 0; i < 10; i++)
    {
        wait(NULL);

        int temp;
        read(fd[0], &temp, sizeof(int));
        total_sum = total_sum + temp;
    }

    close(fd[0]);
    close(fd[1]);

    printf("Total = %d\n", total_sum);

    return 0;
}
