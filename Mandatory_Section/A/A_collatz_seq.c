#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void collatz_sequence(int n) {
    printf("%d ", n);
    while (n != 1) {
        if (n % 2 == 0)
            n = n / 2;
        else
            n = 3 * n + 1;
        printf("%d ", n);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    //validate argument: exactly one positive integer 
    if (argc != 2) {
        printf("Usage: %s <positive_integer>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);// string theke integer e convert kora
    if (n <= 0) {
        printf("Please provide a positive integer.\n");
        return 1;
    }

    pid_t pid = fork();  // create a child process - fork a chilld process

    if (pid < 0) {
        // Error in forking
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        // Child process ekhane hobe
        printf("Child Process: Generating Collatz sequence for %d\n", n);
        collatz_sequence(n);
        exit(0);  // child process exit kore
    } else {
        // Parent process
        printf("Parent Process: Waiting for child to complete...\n");
        wait(NULL);  // wait for the child process to finish// totokkhon wait korbe jotokkhon na finish kore 
        printf("Child process finished. Parent exiting.\n");
    }

    return 0;
}
