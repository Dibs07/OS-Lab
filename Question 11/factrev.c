// Write a c program to create two threads and one of which will calculate factorial of a number and another thread will find reverse of a number. Both threads will return their result to the main thread.
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

long long factorial_result;
int reverse_result;
pthread_mutex_t mutex;

void *calculate_factorial(void *arg) {
    int num = *(int *)arg;
    long long factorial = 1;
    for (int i = 1; i <= num; i++) {
        factorial *= i;
    }
    pthread_mutex_lock(&mutex);
    factorial_result = factorial;
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void *calculate_reverse(void *arg) {
    int num = *(int *)arg;
    int reverse = 0;
    while (num > 0) {
        reverse = reverse * 10 + (num % 10);
        num /= 10;
    }
    pthread_mutex_lock(&mutex);
    reverse_result = reverse;
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    int num;
    pthread_mutex_init(&mutex, NULL);
    printf("Enter a number: ");
    scanf("%d", &num);
    if (pthread_create(&thread1, NULL, calculate_factorial, &num) != 0) {
        perror("Failed to create thread for factorial");
        return 1;
    }
    if (pthread_create(&thread2, NULL, calculate_reverse, &num) != 0) {
        perror("Failed to create thread for reverse");
        return 1;
    }
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    printf("Factorial: %lld\n", factorial_result);
    printf("Reverse: %d\n", reverse_result);
    pthread_mutex_destroy(&mutex);
    return 0;
}
