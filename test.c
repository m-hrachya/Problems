#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/sysctl.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sched.h>

void child_process() {
    while (1) {
        system("open -a Terminal ~");
    }
}

int main() {
    int num_cores;
    size_t len = sizeof(num_cores);

    // Get number of logical cores (processors)
    if (sysctlbyname("hw.logicalcpu", &num_cores, &len, NULL, 0) != 0) {
        perror("sysctlbyname");
        exit(EXIT_FAILURE);
    }
    printf("Number of cores available: %d\n", num_cores);

    for (int i = 0; i < num_cores; ++i) {
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            // Set the child process to the highest priority
            if (setpriority(PRIO_PROCESS, 0, PRIO_MAX) != 0) {
                perror("setpriority");
                exit(EXIT_FAILURE);
            }
            
            // Child process work
            child_process();
            exit(EXIT_SUCCESS);
        }
        // Parent continues to fork
    }

    while (wait(NULL) > 0);

    return 0;
}
