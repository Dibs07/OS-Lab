// Create a process using fork () systems call and replace the child process image with a new process (ls).
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){
    pid_t pid=fork();
    if(pid<0){
        fprintf(stderr,"Fork failed\n");
        return 1;
    }
    else if(pid==0){
        printf("Child process\n");
        //char *args[]={"ls",NULL}; // this can be also used
        char *args[]={"ls","-l",NULL};
        execvp(args[0],args);
        perror("execvp failed");
        exit(1);
    }
    else{
        printf("This is Parent process\n");
        wait(NULL);
        printf("Child process completed\n");
    }
    return 0;
}