#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int arr[1000];

int add(int arr[], int start, int end)
{
    int sum = 0;
    for (int i = start; i <= end; i++)
        sum += arr[i];

    return sum;
}

void* thread_xd(void* arg)
{
    g_sum += add(arr, (int)arg * 100, (int)arg * 100 + 99);
}

int main(void)
{
    for (int i = 0; i < 1000; i++)
        arr[i] = i;

    int g_sum = 0;
    int status;
    pthread_t threads[10];

    for (int i = 0; i < 10; i++)
    {
        pthread_create(&threads[i], NULL, thread_xd, (void*)i);
    }

    pthread_exit(NULL);

    printf("Sum: %d\n", g_sum);

    return 0;
}
