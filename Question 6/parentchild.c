// Write a c program to pass message from parent to child through pipe.

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(){
    int pfd1[2],pfd2[2];
    char par_msg[]="Hello child from parent";
    char ch_msg[]= "Hello parent from child";
    char buffer[100];
    if(pipe(pfd1)==-1 || pipe(pfd2)==-1){
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    int pid=fork();
    if(pid==-1){
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if(pid==0){
        close(pfd1[1]);
        close(pfd2[0]);
        read(pfd1[0],buffer,sizeof(buffer));
        printf("Child received: %s\n",buffer);
        write(pfd2[1],ch_msg,strlen(ch_msg)+1);
        close(pfd1[0]);
        close(pfd2[1]);
    }
    else{
        close(pfd1[0]);
        close(pfd2[1]);
        write(pfd1[1],par_msg,strlen(par_msg)+1);
        read(pfd2[0],buffer,sizeof(buffer));
        printf("Parent received: %s\n",buffer);
        close(pfd1[1]);
        close(pfd2[0]);
    }
}