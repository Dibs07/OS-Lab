// Write a c program to implement to Reader-writer problem. (Using semaphore)
#include <stdio.h>

int mutex=1,db=1,rc=0;

int up(int s){
    return ++s;
}

int down(int s){
    return --s;
}

void reader(){
    if(mutex==0){
        printf("Reader is waiting\n");
    }
    else{
        mutex=down(mutex);
        rc=up(rc);
        if(rc==1){
            db=down(db);
        }
        mutex=up(mutex);
        printf("Reader is reading\n");
        mutex=down(mutex);
        rc=down(rc);
        if(rc==0){
            db=up(db);
        }
        mutex=up(mutex);
    }
}

void writer(){
    if(db==0){
        printf("Writer is waiting\n");
    }
    else{
        db=down(db);
        printf("Writer is writing\n");
        db=up(db);
    }
}

int main(){
    int c;
    printf("Enter 1 for reader and 2 for writer\n");
    while(1){
        printf("Enter choice\n");
        scanf("%d",&c);
        switch(c){
            case 1: reader();
                    break;
            case 2: writer();
                    break;
            default: printf("Invalid choice\n");
        }
    }
}