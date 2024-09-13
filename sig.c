#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void sigkill_handler(int signum);

int main() {
    int i = 0;
    signal(SIGSEGV, sigkill_handler);
    printf("Waiting for ^C...\n");
    *NULL;
    return 0;
}

void sigkill_handler(int signum) {
    printf("Received ^C signal (%d)\n", signum);
}
