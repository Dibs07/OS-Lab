// Write a c program to implement Producer-Consumer Problem. (Using semaphore).
#include <stdio.h>
int mutex=1,full=0,empty=3,x=0;

int wait(int s){
    return --s;
}

int signal(int s){
    return ++s;
}

void producer(){
    empty=wait(empty);
    mutex=wait(mutex);
    x++;
    printf("Producer produces the item %d\n",x);
    mutex=signal(mutex);
    full=signal(full);
}

void consumer(){
    full=wait(full);
    mutex=wait(mutex);
    printf("Consumer consumes the item %d\n",x);
    x--;
    mutex=signal(mutex);
    empty=signal(empty);
}

int main(){
    int c;
    printf("1.Producer\n2.Consumer\n3.Exit\n");
    while(1){
        printf("\nEnter your choice: ");
        scanf("%d",&c);
        switch(c){
            case 1:
                if((mutex==1)&&(empty!=0)){
                    producer();
                }
                else{
                    printf("Buffer is full\n");
                }
                break;
            case 2:
                if((mutex==1)&&(full!=0)){
                    consumer();
                }
                else{
                    printf("Buffer is empty\n");
                }
                break;
            case 3:
                return 0;
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}