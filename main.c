#include "lib.h"

/*
    ----------------------> Instructions <-----------------------
    Firstly, enter file name for which you want to create chunks.
    With chunks, you can:
        - Read ( >> read 1 )
        - Write ( >> write 2 Hello )
        - Get Info ( >> chunk_info 1 )
    Other features available:
        - Get Metadata ( >> metadata )
        - Concat Chunks ( >> concat )
    --------------------------------------------------------------
*/

int main() {
    struct tm *timeinfo;
    char ** command_line_args = calloc(sizeof(char *), ARG_COUNT);
    for (int i = 0; i < ARG_COUNT; ++i) {
        command_line_args[i] = calloc(sizeof(char), MAX_COMMAND_SIZE);
    }
    char * filename = (char *) calloc(sizeof(char), MAX_FILE_NAME);
    printf("Enter file name to start working with: ");
    scanf("%s", filename);
    int fd = open(filename, O_RDWR);
    Metadata * metadata = (Metadata *) malloc(sizeof(Metadata));
    initializeMetadata(metadata, fd);
    Chunk * chunks =  (Chunk *) malloc(sizeof(Chunk) * metadata -> totalNumberOfChunks);;
    int * chunkIds = createChunks(fd, filename, metadata, chunks, timeinfo);
    initializeChunks(chunkIds, fd, metadata);
    printf("Enter (concat) to concat chunks and exit:\n");
    while (1) {
        printf(" >> ");
        scanf("%s", command_line_args[0]);
        if (!strcmp(command_line_args[0], "write")) {
            scanf("%s", command_line_args[1]);
            scanf("%s", command_line_args[2]);
            chunk_write(chunks, chunkIds, atoi(command_line_args[1]) - 1, command_line_args[2], timeinfo);
        } else if (!strcmp(command_line_args[0], "read")) {
            scanf("%s", command_line_args[1]);
            chunk_read(chunks, chunkIds, atoi(command_line_args[1]) - 1, timeinfo);
        } else if (!strcmp(command_line_args[0], "concat")) {
            printf("Exiting...\n");
            chunks_concat(chunkIds, fd, metadata->totalNumberOfChunks, filename);
            break;
        } else if (!strcmp(command_line_args[0], "metadata")) {
            printMetadataInfo(metadata);
        } else if (!strcmp(command_line_args[0], "chunk_info")) {
            scanf("%s", command_line_args[1]);
            printChunkInfo(chunks + atoi(command_line_args[1]) - 1);
        } else {
            printf("Invalid commands!\nTry again\n");
        }
    }
    free(filename);
    for (int i = 0; i < ARG_COUNT; ++i) {
        free(command_line_args[i]);
    }
    free(command_line_args);
    free(metadata);
    free(chunks);
    for (int i = 0; i < CHUNK_COUNT; ++i) {
        close(chunkIds[i]);
    }
    free(chunkIds);
    close(fd);
    return 0;
}