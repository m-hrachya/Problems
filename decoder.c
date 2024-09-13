// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>
// #include <unistd.h>
int x ;
// int main() {
//     FILE * source = fopen("decoded.txt", "r");
//     FILE * destination = fopen("regular.txt", "r+");

//     char symbol = 0;
//     int count = 0;

//     while (fscanf(source, "%c", &symbol)) {
//         fscanf(source, "%d", &count);
//         if (count == 0) {
//             fprintf(destination, "%c", symbol);
//         } else {
//             for (int i = 0; i < count; ++i) {
//                 fprintf(destination, "%c", symbol);
//             }
//         }
//         symbol = 0;
//         count = 0;
//         if (feof(source)) break;
//     }

//     fclose(source);
//     fclose(destination);
//     return -1;
// }