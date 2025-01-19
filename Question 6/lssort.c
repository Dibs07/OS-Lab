// Write a c program to implement the operation ------- ls| sort.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int pipe_fd[2]; 
    pid_t pid;
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid == 0) { 
        close(pipe_fd[0]);
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[1]); 
        execlp("ls", "ls", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    } else { 
        close(pipe_fd[1]); 
        dup2(pipe_fd[0], STDIN_FILENO);
        close(pipe_fd[0]); 
        execlp("sort", "sort", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    return 0;
}
