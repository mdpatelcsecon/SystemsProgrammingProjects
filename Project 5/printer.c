#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#define PUB7645 "./PubFile"

union semun {
   int val;
   struct semid_ds *buf;
   ushort *array;
};
int main() 
{
   int intValue, semID;
   key_t key;
   FILE *fptr;

        union semun arg;
        static ushort startVal = 1;
        static struct sembuf acquire = {0, -1, SEM_UNDO}, release = {0, 1, SEM_UNDO};
        key = ftok(".", 's');

        if ((semID = semget(key, 1, IPC_CREAT | 0666)) == -1) {
                perror("Sem Creation:");
                exit(2);
        }

        arg.array = &startVal;
        if (semctl(semID, 1, SETALL, arg) == -1 ) {
                perror("semctl: SETALL");
                exit(3);
        }
        srand(getpid());
        while(1) {
                if (semop(semID, &acquire, 1) == -1) {
                        perror("Producer waiting");
                        exit(4);
                }
                if ((fptr = fopen(PUB7645, "w+")) == NULL) {
                                perror(PUB7645);
                                exit(1);
                }
                intValue = random()*1000/RAND_MAX + 1;
                fprintf(fptr, "%d\n", intValue);
                fclose(fptr);
                if (semop(semID, &release, 1) == -1) {
                        perror("new");
                        exit(5);
                }
        }
}