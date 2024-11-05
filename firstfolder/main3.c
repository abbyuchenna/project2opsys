#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

// function for the child process
void childProcess() {
    srandom(time(NULL) ^ (getpid() << 16)); // seed the random number generator
    
    for (int i = 0; i < 30; i++) {
        int sleepTime = random() % 10 + 1; // random sleep time between 1 and 10 seconds
        
        printf("Child PID: %d is going to sleep for %d seconds!\n", getpid(), sleepTime);
        sleep(sleepTime); // sleep for a random time

        printf("Child PID: %d is awake!\nWhere is my Parent PID: %d?\n", getpid(), getppid());
    }
    
    exit(0); // exit the child process after the loop
}

int main() {
    pid_t pid1, pid2;
    
    // create the first child process
    pid1 = fork();
    if (pid1 < 0) {
        perror("Fork failed for first child");
        return 1;
    } else if (pid1 == 0) {
        childProcess(); // run the child process code
    }
    
    // create the second child process
    pid2 = fork();
    if (pid2 < 0) {
        perror("Fork failed for second child");
        return 1;
    } else if (pid2 == 0) {
        childProcess(); // run the child process code
    }
    
    // parent process waits for both children to complete
    int status;
    pid_t completedPid;
    while ((completedPid = wait(&status)) > 0) {
        printf("Child PID: %d has completed\n", completedPid);
    }

    printf("Parent process is done.\n");
    return 0;
}
