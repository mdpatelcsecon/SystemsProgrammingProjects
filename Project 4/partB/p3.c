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
#include <string.h>


struct msgbuf {
    long mtype;
    char mtext[1];
};

int main(void)
{
        //Open message queue
        //Create IPC key 
        int key = ftok("/tmp/queue", 'q');
        int qid = 0;
        //Get message queue and handle error conditions
        if ((qid = msgget(key, IPC_CREAT | 0666)) == -1) {
                perror("MS Queue Creation");
                exit(1);
        }
        /*Obtain the numbers from the queue*/
        char rdbuf[6];
        memset(rdbuf, 0, sizeof(rdbuf));
        int rdtype = 0;
        struct msgbuf msg;
        while(1) {
                //get type from user
                printf("Enter the number type to obtain from the the queue (even, odd, prime): ");
                fflush(stdout);
                memset(rdbuf, 0, sizeof(rdbuf));
                //fgets(rdbuf, 5, stdin);
                scanf("%s", rdbuf);
                printf("%s", rdbuf);
                //set numeric result type
                if(strcmp(rdbuf, "prime") == 0)     rdtype = 3;
                else if(strcmp(rdbuf, "even") == 0) rdtype = 2;
                else if(strcmp(rdbuf, "odd") == 0)  rdtype = 1;
                //get result value
                if (msgrcv(qid, &msg, sizeof(msg), rdtype, 0) == -1) {
                                perror("Message recieve");
                        exit(2);
                }
                //print result
                printf("Result: %s\n", msg.mtext);
                
        }
        return 0;
}