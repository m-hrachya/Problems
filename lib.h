#ifndef LIB
#define LIB

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>
#include <time.h>


#define CHUNK_COUNT 3
#define MAX_FILE_NAME 25
#define TIME_ARRAY_SIZE 9
#define ARG_COUNT 3
#define MAX_COMMAND_SIZE 25

typedef struct Chunk {
    int chunkIndex;
    int chunkSize;
    char creationTime[TIME_ARRAY_SIZE];
    char modificationTime[TIME_ARRAY_SIZE];
    char accessTime[TIME_ARRAY_SIZE];
} Chunk;

typedef struct Metadata {
    int fileSize;
    int chunkSize;
    int totalNumberOfChunks;
} Metadata;

int * createChunks(int fd, char * filename, Metadata * metadata, Chunk * chunks, struct tm * timeinfo);
void initializeMetadata(Metadata * metadata, int fd);
void printMetadataInfo(Metadata * metadata);
void initializeChunks(int * chunkFds, int fd, Metadata * metadata);
void printChunkInfo(Chunk * chunk);
void chunk_write(Chunk * chunk, int * chunkFds, int chunk_n, const char * str, struct tm * timeinfo);
void chunk_read(Chunk * chunk, int * chunkFds, int chunk_n, struct tm * timeinfo);
void chunks_concat(int * chunkFds, int fd, int count, char * fileName);
// concat chunks

#endif