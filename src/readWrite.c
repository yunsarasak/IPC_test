#include <stdio.h>
#include <poll.h>
#include "../libsrc/multiProcess.h"

int data = 0;

void *writeFunc();
void *readFunc();

typedef struct shmObject{
	pthread_mutex_t wrlock;
	int m_iWriteIndex;
	int m_iReadIndex;
	int* addr;
}shmObject;

shmObject* shmO1;

int main(void)
{
	init();
//	printf("hello, world!\n");
	pthread_t wt, rt;


	pthread_create(&wt, NULL, writeFunc, NULL);
	pthread_create(&rt, NULL, readFunc, NULL);

	poll((FILE*)stdin, 0, 1000 * 50);
}

void *writeFunc()
{
	while(1){
		if(enqueue(data) == -1){
			continue;
		}
		
		printf("write : %d\n", data);
		poll(NULL, 0, 100);
		data++;
	}
}

void *readFunc()
{
	int iOutput;
	while(1){
		if(dequeue(&iOutput) == -1){
			continue;
		}
		printf("read : %d\n", iOutput);
		poll(NULL, 0, 1000);
	}
}

int isEmpty()
{
	if(iWriteIndex == iReadIndex){
		return 1;	
	}else{
		return 0;
	}
}

int isFull()
{
	if((iWriteIndex - iReadIndex + 201) * 201 == 200){
		return 1;
	}else{
		return 0;
	}
}

void init()
{
        int shmid;
	iReadIndex = 0;
	iWriteIndex = 0;
        key=960110;



        if((shmid=shmget(key,(sizeof(int)*201)+sizeof(shmObject),IPC_CREAT|0666))==-1){
                printf("shmget failed\n");
                exit(0);
        }


        if((shmO1=shmat(shmid,NULL,0))==(void*)-1){
                printf("shmat failed\n");
                exit(0);
        }
	//att init
	pthread_attr_t shmatt1;
	pthread_mutexattr_init(&shmatt1);
	pthread_mutexattr_setpshared(&shmatt1, PTHREAD_PROCESS_SHARED);
	
	//shared memory object init
	//mutex init
	pthread_mutex_init(&shmO1->wrlock, &shmatt1);
	shmO1->m_iWriteIndex = 0;
	shmO1->m_iReadIndex = 0;
	shmO1->addr = shmO1 + sizeof(shmObject);
	

}

int enqueue(int _input)
{
	if(isFull()){
		return -1;
	}
	Arr[iWriteIndex++] = _input;
	return 0;
}

int dequeue(int *retVal)
{
	if(isEmpty()){
		return -1;
	}

	*retVal = Arr[iReadIndex++];
	return 0;
}






