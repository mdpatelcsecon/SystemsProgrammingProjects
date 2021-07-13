//Linux headers
#include <fcntl.h>
#include <sys/stat.h>
//#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

struct msgbuf {
    long mtype;
    char mtext[1];
};

int is_prime(const int n);

int main(void)
{
        //open named pipe for reading
        int pd = open("/tmp/pipe", O_RDONLY);
        if(pd < 0) {
                perror("Opening FIFO File Descriptor Failed");
        }
        //Create message queue
        //Create IPC key 
        int key = ftok("/tmp/queue", 'q');
        int qid = 0;
        //Create the message queue and handle error conditions
        if ((qid = msgget(key, IPC_CREAT | 0666)) == -1) {
                perror("MS Queue Creation");
                exit(1);
        }
        //write 100 values from named pipe to message queue with correct classification.
        unsigned int rdnum; //read value
        struct msgbuf value; //value to be written
        for(size_t i = 0; i < 100; ++i) {
                //read from pipe
                read(pd, &rdnum, sizeof(rdnum));
                //write to queue
                if (is_prime(rdnum)) 
                        value.mtype = 3;
                else if ((rdnum % 2) == 0)
                        value.mtype = 2;
                else value.mtype = 1;
                printf("%d\n", rdnum);
                sprintf(value.mtext, "%d", rdnum);
                if (msgsnd(qid, &value, sizeof(value), 0) == -1) {
                                perror("Message send");
                        exit(2);
                }
        }
        return 0;
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