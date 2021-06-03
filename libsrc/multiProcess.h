#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int *Arr;

int iReadIndex;
int iWriteIndex;

key_t key;

pthread_mutex_t rwMutex;

void init();
int isEmpty();
int isFull();
int enqueue(int _input);
int dequeue(int *);
