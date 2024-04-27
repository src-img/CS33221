#ifndef HEADER_H
#define HEADER_H

#include <fcntl.h>
#include <time.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#define tableMax 2
#define errExit(msg)    do { perror(msg); exit(EXIT_FAILURE); \
                                   } while (0) //yeah idk how this works at all ty man7

typedef struct {
    char buffer[tableMax];
    sem_t vacant;
    sem_t occupied;
} table;

#endif