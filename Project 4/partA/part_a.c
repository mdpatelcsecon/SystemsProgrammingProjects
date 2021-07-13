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

int is_prime(const int n);

int main() {
        /*All variable declarations as provided by Prof.*/
        key_t key;
        long i=0;
        int intValue, mid;
        char intStr[3];
        struct msgbuf value;

        //Create IPC key 
        key = ftok("/tmp/queue", 'q');
        //Create the message queue and handle error conditions
        if ((mid = msgget(key, IPC_CREAT | 0666)) == -1) {
                perror("MS Queue Creation");
                exit(1);
        }
        //generate random numbers, determine their type and send that info into the queue
        for(; ;) {
                i++;
                srand(getpid()+i);
                intValue =((random()%101) + 1);
                //printf("%d\n", intValue);
                sprintf(intStr, "%d", intValue);
                if (is_prime(intValue)) //added type 3 if the number is prime
                        value.mtype = 3;
                else if ((intValue % 2) == 0)
                        value.mtype = 2;
                else
                        value.mtype = 1;
                strcpy(value.mtext, intStr);
                if (msgsnd(mid, &value, sizeof(value), 0) == -1) {
                                perror("Message send");
                        exit(2);
                }
        }
}
/*
Test a number to see if it is prime. 
Preconditions: None
Postconditions: None
Return: 1 if prime, 0 if n is composite
Except: None
*/
int is_prime(const int n)
{
        for(int i = 2; i < n - 1; ++i) {
                if(n % i == 0) return 0;
        }
        return 1;
}