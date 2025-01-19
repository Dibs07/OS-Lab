// Write a c program to create a thread from main thread and then print the thread id and process id of that newly created thread and main thread.
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *print_thread_info(void *arg) {
    printf("New Thread:\n");
    printf("Thread ID: %lu\n", pthread_self());
    printf("Process ID: %d\n\n", getpid());
    return NULL;
}

int main() {
    pthread_t thread;
    printf("Main Thread:\n");
    printf("Thread ID: %lu\n", pthread_self());
    printf("Process ID: %d\n\n", getpid());
    if (pthread_create(&thread, NULL, print_thread_info, NULL) != 0) {
        perror("Failed to create thread");
        return 1;
    }
    pthread_join(thread, NULL);
    return 0;
}


