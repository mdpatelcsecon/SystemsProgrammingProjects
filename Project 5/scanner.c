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
int  main() {
   int intValue, semID;
   key_t key;
   FILE *fptr;

	union semun arg;
	static struct sembuf acquire = {0, -1, SEM_UNDO},
                         release = {0, 1, SEM_UNDO};

   key = ftok(".", 's');

   if ((semID = semget(key, 1, IPC_CREAT | 0666)) == -1) {
	  perror("Sem Creation:");
             exit(1);
   }
   unsigned iter = 1;
   while(1) {

      if (semop(semID, &acquire, 1) == -1) {
                perror("Consumer waiting");
	    exit(2);
      }

      if ((fptr = fopen(PUB7645, "r")) == NULL) {
	        perror(PUB7645);
	        exit(3);
      }
      fscanf(fptr, "%d", &intValue);
      printf("%d\n", intValue);
      //For debugging
      //printf("Iter: %d\n", iter++);
      fclose(fptr);
      if (semop(semID, &release, 1) == -1) {
         perror("Release");
         exit(4);
      }
      //printf("%d\t", intValue);
   }
   if (semctl(semID, 0, IPC_RMID) == -1) {
         perror("semctl: IPC_RMID");
         exit(5);
   }
}