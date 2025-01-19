#include <stdio.h>
#include <pthread.h>
#include <unistd.h>  

int mutex = 1;   
int db = 1;     
int rc = 0;      


void wait(int *s) {
    while (*s <= 0) {
        printf("Semaphore value is %d, thread is waiting...\n", *s);
        sleep(1);  
    }
    (*s)--; 
    printf("Semaphore acquired, new value: %d\n", *s);  
}

void signal(int *s) {
    (*s)++;  
    printf("Semaphore released, new value: %d\n", *s); 
}


void* reader(void* param) {
    wait(&mutex);  
    rc++;       
    if (rc == 1) { 
        wait(&db);
    }
    signal(&mutex);  

    printf("Reader %ld is reading\n", (long)param);
    sleep(1);

    wait(&mutex); 
    rc--;         
    if (rc == 0) { 
        signal(&db);
    }
    signal(&mutex);  

    return NULL;
}

void* writer(void* param) {
    printf("Writer %ld trying to write\n", (long)param);  
    wait(&db);
    printf("Writer %ld is writing\n", (long)param);
    sleep(2);
    signal(&db);
    return NULL;
}

int main() {
    pthread_t threads[10];  
    int choice, i;
    int thread_count = 0;    

    printf("Enter 1 for reader and 2 for writer. Enter 0 to exit.\n");
    while (1) {
        printf("Enter choice (1 for reader, 2 for writer, 0 to exit): ");
        scanf("%d", &choice);

        if (choice == 0) break;

        switch (choice) {
            case 1: 
                for (i = 0; i < 3; i++) {  
                    if (thread_count < 10) {
                        pthread_create(&threads[thread_count], NULL, reader, (void *)(long)thread_count);
                        thread_count++;
                    }
                }
                break;
            case 2: 
                for (i = 0; i < 2; i++) {  
                    if (thread_count < 10) {
                        pthread_create(&threads[thread_count], NULL, writer, (void *)(long)thread_count);
                        thread_count++;
                    }
                }
                break;
            default:
                printf("Invalid choice\n");
                continue;
        }

        for (i = 0; i < thread_count; i++) {
            pthread_join(threads[i], NULL);
        }
        thread_count = 0;
    }

    return 0;
}
