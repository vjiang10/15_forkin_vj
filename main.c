#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

int main() {
    int f, status;

    // parent 
    printf("Before 1st forking\tParent PID: %d\n", getpid());
    // first fork
    f = fork();

    // second fork (in parent)
    if (f) { 
        printf("Before 2nd forking\tParent PID: %d\n", getpid());
        f = fork();
    }

    // child process
    if (!f) {
        srand(getpid() + time(NULL));
        printf("Child PID: %d\n", getpid());
        int t = rand()%9+2;
        sleep(t);
        printf("Child process finished! PID: %d\n", getpid());
        return t;
    }

    // parent process
    else {
        int c_pid = wait(&status);
        // exit code (time taken) returned by child process
        int time = WEXITSTATUS(status);
        printf("Child PID: %d\tProcess time taken: %d\n", c_pid, time);
        printf("Parent process complete!\n");
        return 0;
    }
     
    return 0;
}
