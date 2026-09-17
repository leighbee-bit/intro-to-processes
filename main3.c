// list/main3.c
//
// Creates two child processes that each sleep/print in a loop;
// parent waits for both to complete.
//
// Leighla-Marie Dantes

#include <stdio.h>      // input/output statements
#include <string.h>     // string alteration functions
#include <sys/types.h>  // pid_t
#include <unistd.h>     // fork(), getpid(), getppid(), sleep()
#include <stdlib.h>     // random(), srandom(), exit()
#include <sys/wait.h>   // wait()
#include <time.h>       // time(), used to seed srandom()

#define MAX_COUNT 30    // max loop iterations
#define MAX_SLEEP 10     // max sleep time in seconds

void ChildProcess1(void);
void ChildProcess2(void);
void ParentProcess(void);

int main(void) {
    pid_t pid1;
    pid1 = fork();   // first fork

    if (pid1 == 0) {
        ChildProcess1();
    } else {
        pid_t pid2 = fork();   // parent forks again

        if (pid2 == 0) {
            ChildProcess2();
        } else {
            ParentProcess();
        }
    }

    return 0;
}

void ChildProcess1(void) {
    srandom(time(NULL) ^ getpid());   // unique seed per process
    int iterations = random() % (MAX_COUNT + 1);   // 0 to 30

    for (int i = 0; i < iterations; i++) {
        printf("Child Pid: %d is going to sleep!\n", getpid());
        sleep(random() % (MAX_SLEEP + 1));   // 0 to 10 secs
        printf("Child Pid: %d is awake!\nWhere is my Parent: %d?\n", getpid(), getppid());
    }

    exit(0);
}

void ChildProcess2(void) {
    srandom(time(NULL) ^ getpid());
    int iterations = random() % (MAX_COUNT + 1);

    for (int i = 0; i < iterations; i++) {
        printf("Child Pid: %d is going to sleep!\n", getpid());
        sleep(random() % (MAX_SLEEP + 1));
        printf("Child Pid: %d is awake!\nWhere is my Parent: %d?\n", getpid(), getppid());
    }

    exit(0);
}

void ParentProcess(void) {
    int status;

    for (int i = 0; i < 2; i++) {
        pid_t donePid = wait(&status);   // blocks until ANY child finishes
        printf("Child Pid: %d has completed\n", donePid);
    }
}