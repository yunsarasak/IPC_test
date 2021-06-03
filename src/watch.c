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

        if((shmid=shmget(key,sizeof(int)*201,IPC_EXCL))==-1){
                printf("shmget failed\n");
                exit(0);
        }


        if((Arr=shmat(shmid,NULL,0))==(void*)-1){
                printf("shmat failed\n");
                exit(0);
        }
}

void showQ()
{
	printf("usage : %d\n", (iWriteIndex+201 - iReadIndex)%201);
	printf("free : %d\n\n", 201 - (iWriteIndex+201 - iReadIndex)%201);
}

int main(void){

	init();
	int i = 0;
	while(1){
		showQ();
		poll(NULL, 0, 1000);
	}
	
}
