#include "../libsrc/multiProcess.h"
#include <stdio.h>
#include <poll.h>
#include <sys/shm.h>
#include <sys/ipc.h>

void init()
{
        int shmid;
	iReadIndex = 0;
	iWriteIndex = 0;
        key=960110;



        if((shmid=shmget(key,(sizeof(int)*20)+sizeof(shmObject),IPC_EXCL))==-1){
                printf("shmget failed\n");
                exit(0);
        }


        if((shmO1=shmat(shmid,NULL,0))==(void*)-1){
                printf("shmat failed\n");
                exit(0);
        }

//	
//	//att init
//	pthread_attr_t shmatt1;
//	pthread_mutexattr_init(&shmatt1);
//	pthread_mutexattr_setpshared(&shmatt1, PTHREAD_PROCESS_SHARED);
//	
//	//shared memory object init
//	//mutex init
//	pthread_mutex_init(&shmO1->rwMutex, &shmatt1);
//	shmO1->m_iWriteIndex = 0;
//	shmO1->m_iReadIndex = 0;
//	shmO1->addr = shmO1 + sizeof(shmObject);
//	

}

void showQ()
{
	printf("usage : %d\n", (shmO1->m_iWriteIndex+20 - shmO1->m_iReadIndex)%20);
	printf("free : %d\n\n", 201 - (shmO1->m_iWriteIndex+20 - shmO1->m_iReadIndex)%20);
}

int main(void){

	init();
	int i = 0;
	while(1){
		showQ();
		poll(NULL, 0, 1000);
	}
	
}
