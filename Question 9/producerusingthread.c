#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <semaphore.h>
#include <errno.h>
#include <string.h>
#define MAXITEMS 5
#define BUFFERSIZE 5

sem_t empty;
sem_t full;
int in=0;
int out=0;
int buffer[BUFFERSIZE];
pthread_mutex_t mutex;

void *producer(void *pno);
void *consumer(void *cno);

int main(int argc, char* argv[])
{
	pthread_t pro[5], con[5];
	pthread_mutex_init(&mutex, NULL);
	sem_init(&empty,0,BUFFERSIZE);
	sem_init(&full,0,0);
	int arr[]={1,2,3,4,5};
	int n=sizeof(arr)/sizeof(arr[0]);
	for (int i=0; i<n; i++)
	{
		pthread_create(&pro[i], NULL, producer, (void *)&arr[i]);
	}
	for (int i=0; i<n; i++)
	{
		pthread_create(&con[i], NULL, consumer, (void *)&arr[i]);
	}
	for (int i=0; i<n; i++)
	{
		pthread_join(pro[i],NULL);
	}
	for (int i=0; i<n; i++)
	{
		pthread_join(con[i], NULL);
	}
	pthread_mutex_destroy(&mutex);
	sem_destroy(&empty);
	sem_destroy(&full);
	return 0;
}

void *producer(void *pno)
{
	int item;
	for (int i=0; i<MAXITEMS; i++)
	{
		item=rand();
		sem_wait(&empty); // Wait for an empty slot
		pthread_mutex_lock(&mutex); // Lock the critical section
		buffer[in]=item;
		printf("Producer %d: Insert item %d at %d\n", *(int *)pno, buffer[in], in);
		in=(in+1)%BUFFERSIZE;
		pthread_mutex_unlock(&mutex); // Unlock the critical section
		sem_post(&full); // Signal that a new item is available
	}
}

void *consumer(void *cno)
{
	for (int i=0; i<MAXITEMS; i++)
	{
		sem_wait(&full); // Wait for a full slot
		pthread_mutex_lock(&mutex); // Lock the critical section
		int item=buffer[out];
		printf("Consumer %d: Remove item %d from %d\n", *(int *)cno, item, out);
		out=(out+1)%BUFFERSIZE;
		pthread_mutex_unlock(&mutex); // Unlock the critical section
		sem_post(&empty); // Signal that a slot is empty
	}
}