#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main() {
    if (fork()) {
        sleep(1);
        for (int i = 0; i < 100; ++i) printf("%d", i);
        wait(NULL);
    }
    else {
        char *args[] = {"b.out", NULL};
        char *envp[] = {NULL};
        execve("./b.out", args, envp);
    }
    return 0;
}