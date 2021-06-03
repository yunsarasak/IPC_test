#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct shmObject{
	pthread_mutex_t rwMutex;
	int m_iWriteIndex;
	int m_iReadIndex;
	int* addr;
}shmObject;

shmObject* shmO1;

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
