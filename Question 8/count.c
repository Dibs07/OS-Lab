// Write a c program to create a thread which will count the number of characters as input by the main thread. Both the threads will run simultaneously. (Using semaphore).
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <string.h>

sem_t sem;            
char string[100]; 

void *count(void *arg) {
    while (1) {
        sem_wait(&sem); 
        if (strlen(string) == 0) { 
            break;
        }
        int count = strlen(string);
        printf("Thread: The input string '%s' has %d characters.\n", string, count);
        sem_post(&sem); 
        usleep(100000);
    }
    return NULL;
}

int main() {
    pthread_t thread;
    sem_init(&sem, 0, 1);
    if (pthread_create(&thread, NULL, count, NULL) != 0) {
        perror("Failed to create thread");
        return 1;
    }
    while (1) {
        sem_wait(&sem); 
        printf("Main Thread: Enter a string (or type 'exit' to quit): ");
        fgets(string, 100, stdin);
        string[strcspn(string, "\n")] = '\0'; 
        if (strcmp(string, "exit") == 0) { 
            strcpy(string, ""); 
            sem_post(&sem);
            break;
        }
        sem_post(&sem); 
        usleep(100000); 
    }
    pthread_join(thread, NULL);
    sem_destroy(&sem);
    printf("Program terminated.\n");
    return 0;
}
