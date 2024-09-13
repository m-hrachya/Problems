#include "lib.h"

void initializeMetadata(Metadata * metadata, int fd) {
    int size = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    if (size < CHUNK_COUNT) {
        printf("Sorry, chunk creation is currently unavailable!\n");
        exit(EXIT_SUCCESS);
    }
    metadata -> fileSize = size;
    metadata -> chunkSize = (size / CHUNK_COUNT) + 1;
    metadata -> totalNumberOfChunks = CHUNK_COUNT;
    return;
}

int * createChunks(int fd, char * fileName, Metadata * metadata, Chunk * chunks, struct tm * timeinfo) {
    if (!fileName) {
        printf("Invalid file name!\n");
        exit(EXIT_FAILURE);
    }
    time_t rawtime;
    char * currentFileName = NULL;
    int * chunkIds = (int *) calloc(sizeof(int), CHUNK_COUNT);
    for (int i = 0; i < CHUNK_COUNT; ++i) {
        currentFileName = (char *) calloc(sizeof(char), MAX_FILE_NAME);
        strcpy(currentFileName, fileName);
        strcat(currentFileName, "_");
        for (int j = 0; j <= i; ++j) {
            strcat(currentFileName, "I");
        }
        chunkIds[i] = open(currentFileName, O_CREAT | O_RDWR | O_EXCL, 0777);
        if (chunkIds[i] == -1) {
            printf("Oops! Chunks olready exist! Delete them first, then run program again!\n");
            exit(EXIT_FAILURE);
        }
        chunks[i].chunkIndex = i + 1;
        chunks[i].chunkSize = metadata -> chunkSize;
        time(&rawtime);
        timeinfo = localtime(&rawtime);
        strftime(chunks[i].creationTime, TIME_ARRAY_SIZE, "%H:%M:%S", timeinfo);
        strftime(chunks[i].accessTime, TIME_ARRAY_SIZE, "%H:%M:%S", timeinfo);
        strftime(chunks[i].modificationTime, TIME_ARRAY_SIZE, "%H:%M:%S", timeinfo);
        free(currentFileName);
    }
    return chunkIds;
}

void initializeChunks(int * chunkFds, int fd, Metadata * metadata) {
    int readSize = 0;
    for (int i = 0; i < metadata -> totalNumberOfChunks; ++i) {
        char * word = (char *) calloc(sizeof(char), (metadata -> chunkSize) + 1);
        readSize = read(fd, word, metadata -> chunkSize);
        write(chunkFds[i], word, readSize);
    }
}

void chunk_write(Chunk * chunk, int * chunkFds, int chunk_n, const char * str, struct tm * timeinfo) {
    int chunk_id = chunkFds[chunk_n];
    lseek(chunk_id, 0, SEEK_SET);
    write(chunk_id, str, strlen(str));
    time_t rawtime;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(chunk->modificationTime, TIME_ARRAY_SIZE, "%H:%M:%S", timeinfo);
    lseek(chunk_id, 0, SEEK_SET);
    return;
}

void chunk_read(Chunk * chunk, int * chunkFds, int chunk_n, struct tm * timeinfo) {
    int chunk_id = chunkFds[chunk_n];
    lseek(chunk_id, 0, SEEK_SET);
    char symbol = 0;
    while (read(chunk_id, &symbol, 1)) {
        printf("%c", symbol);
    } printf("\n");
    time_t rawtime;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(chunk->accessTime, TIME_ARRAY_SIZE, "%H:%M:%S", timeinfo);
    lseek(chunk_id, 0, SEEK_SET);
    return;
}

void chunks_concat(int * chunkFds, int fd, int count, char * fileName) {
    lseek(fd, 0, SEEK_SET);
    ftruncate(fd, 0);
    char symbol = 0;
    for (int i = 0; i < count; ++i) {
        lseek(chunkFds[i], 0, SEEK_SET);
    }
    for (int i = 0; i < count; ++i) {
        while (read(chunkFds[i], &symbol, 1)) {
            write(fd, &symbol, 1);
        }
    }
    char *currentFileName = NULL;
    for (int i = 0; i < CHUNK_COUNT; ++i) {
        currentFileName = (char *) calloc(sizeof(char), MAX_FILE_NAME);
        strcpy(currentFileName, fileName);
        strcat(currentFileName, "_");
        for (int j = 0; j <= i; ++j) {
            strcat(currentFileName, "I");
        }
        remove(currentFileName);
    }
    return;
}

void printMetadataInfo(Metadata * metadata) {
    printf("-----------\n");
    printf("File Size: %d\n", metadata -> fileSize);
    printf("Each Chunk Size: %d\n", metadata -> chunkSize);
    printf("Chunk count: %d\n", metadata -> totalNumberOfChunks);
    printf("-----------\n");
    return;
}

void printChunkInfo(Chunk * chunk) {
    printf("-----------\n");
    printf("Chunk Index: %d\n", chunk->chunkIndex);
    printf("Chunk Size: %d\n", chunk->chunkSize);
    printf("Creation time: %s\n", chunk->creationTime);
    printf("Modification time: %s\n", chunk->modificationTime);
    printf("Access time: %s\n", chunk->accessTime);
    printf("-----------\n");
    return;
}