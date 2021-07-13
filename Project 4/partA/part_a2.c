#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msgbuf {
    long mtype;
    char mtext[1];
};

int main() {
	key_t key;
	//long i=0;
	int mid, n;
        struct msgbuf value;
	
        key = ftok("/tmp/queue", 'q');
        if ((mid = msgget(key, IPC_CREAT | 0666)) == -1) {
            perror("MS Queue Creation");
            exit(1);
        }
        //odds 
        printf("Odds: ");
        for(int i = 0; i < 5; ++i) {
                if ((n=msgrcv(mid, &value, sizeof(value), 1, 0)) == -1) {
                        perror("MS Queue Read");
                        exit(2);
                }
                printf("%s\t", value.mtext);
        }
        printf("\n");
        //even
        printf("Evens: ");
        for(int i = 0; i < 5; ++i) {
                if ((n=msgrcv(mid, &value, sizeof(value), 2, 0)) == -1) {
                        perror("MS Queue Read");
                        exit(2);
                }
                printf("%s\t", value.mtext);
        }
        printf("\n");
        //primes
        printf("Primes: ");
        for(int i = 0; i < 5; ++i) {
                if ((n=msgrcv(mid, &value, sizeof(value), 3, 0)) == -1) {
                        perror("MS Queue Read");
                        exit(2);
                }
                printf("%s\t", value.mtext);
        }
        printf("\n");
        return 0;
        //msgctl(mid, IPC_RMID, (struct msqid_ds *) 0); //NULL
}