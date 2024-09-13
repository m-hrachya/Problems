#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
int main() {
    signal(SIGSEGV, SIG_IGN);
    signal(SIGFPE, SIG_IGN);
    // int num = 0;
    // float x = 10 / num;
    int *x = NULL;
    int z = *x;
    printf("%f", x);
    //scanf("%d", &num);
    for(int i = 0; i < num; ++i) {
        for(int j = 0; j < num; ++j) {
            if(i == 0 || i == (num - 1)) {
                printf("* ");
            } else {
                if (j == 0 || j == (num - 1)) {
                    printf("* ");
                } else {
                    printf("  ");
                }
            }
        }
        printf("\n");
    }
    return 0;
}