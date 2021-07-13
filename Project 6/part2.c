#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/shm.h>

#include <stdio.h>
#include <stdlib.h>

#define FPATH "ipcf2.txt"
#define PROJID 2

int main(int argc, char *argv[])
{
        /***Generate all IPC structures***/

        /*Generate key*/
        key_t key = ftok(FPATH, PROJID);
        if(key == -1) { //Exit with message if there's an error
                perror("System V IPC key generation error");
                exit(1);
        } else {
                printf("IPC Key Generated. Value = %d\n\n\n", key);
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
                printf("System V shared memory segment created. ID = %d.\n\n\n", mque);
        }





        /***Make modifications based on user input***/

        /*Create the uid and gid fields from commandline parameters*/
        uid_t euid = 0, egid = 0;

        euid = atol(argv[1]);  
        if(euid == 0) perror("Could not convert first argument to valid uid_t");
        egid = atol(argv[2]);
        if(euid == 0) perror("Could not convert second argument to valid uid_t");

        /*Create the common ipc_perm to be used for all modifications*/
        struct ipc_perm perms = {
                .uid   = euid,
                .gid   = egid
        };

        /*Modify the message queue*/
        struct msqid_ds mds;
        mds.msg_perm = perms;

        if (msgctl(mque, IPC_SET, &mds) == -1) {
                perror("Error changing message queue uid and gid");
        } else {
                printf("Successfully changed message queue uid and gid to values: %u %u\n", euid, egid);
        }
        
        /*Modify the semaphore*/
        struct semid_ds semds;
        semds.sem_perm = perms;

        if (semctl(semid, 1, IPC_SET, &semds) == -1) {
                perror("Error changing semaphore uid and gid");
        } else {
                printf("Successfully changed semaphore uid and gid to values: %u %u\n", euid, egid);
        }

        /*Modify the shared memory segment*/
        struct shmid_ds shmds;
        shmds.shm_perm = perms;

        if (shmctl(shmid, IPC_SET, &shmds) == -1) {
                perror("Error changing shared memory segment uid and gid");
        } else {
                printf("Successfully changed shared memory segment uid and gid to values: %u %u\n", euid, egid);
        }

        return 0;
}