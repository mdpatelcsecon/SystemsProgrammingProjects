#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/shm.h>

#include <stdio.h>
#include <stdlib.h>

#define FPATH "ipcf.txt"
#define PROJID 1

int main()
{
        /*Generate key*/
        key_t key = ftok(FPATH, PROJID);
        if(key == -1) { //Exit with message if there's an error
                perror("System V IPC key generation error");
                exit(1);
        } else {
                printf("IPC Key Generated. Value = %d\n", key);
        }
        /*Create System V message queue*/
        int mque = msgget(key, IPC_CREAT);
        if(mque == -1) {
                perror("System V message queue generation error");
        } else {
                printf("System V message queue created. ID = %d.\n", mque);
        }
        /*Create System V semaphore*/
        int semid = semget(key, 1, IPC_CREAT);
        if (semid == -1) {
                perror("System V semaphore generation error");
        } else {
                printf("System V semaphore set created. ID = %d.\n", semid);
        }
        /*Create System V shared memory*/
        int shmid = shmget(key, 1024, IPC_CREAT);
        if(shmid == -1) {
                perror("System V shared memory segment allocation error");
        } else {
                printf("System V shared memory segment created. ID = %d.\n", mque);
        }
        return 0;
}