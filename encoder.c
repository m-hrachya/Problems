#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

void foo();
void foo();
extern int y;

int main() {
    //printf("%d\n", y);
    // FILE * source = fopen("regular.txt", "r");
    // FILE * destination = fopen("decoded.txt", "r+");
    // char symbol = 0;
    // char next_symbol = 0;
    // int count = 0;
    // while(fread(&symbol, 1, 1, source)) {
    //     do {
    //         ++count;
    //         fread(&next_symbol, 1, 1, source);
    //         if (feof(source)) break;
    //     } while (next_symbol == symbol);
    //     fprintf(destination, "%c", symbol);
    //     if (count > 1) {
    //         fprintf(destination, "%d", count);
    //     }
    //     count = 0;
    //     symbol = 0;
    //     next_symbol = 0;
    //     if (feof(source)) break;
    //     fseek(source, -1, SEEK_CUR);
    // }
    // fclose(source);
    // fclose(destination);
    return 0;
}

