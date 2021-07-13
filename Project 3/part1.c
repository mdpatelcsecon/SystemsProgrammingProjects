#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>


#define SLEEP_TIME 3

void signal_catcher(int);

int main(int argc, char * argv[])
{
        //store the parent id for the child's use
        const pid_t parid = getpid();
        //Fork a child process to generate signals
        const pid_t chid = fork();
        /*Portion run in the child process*/
        if(chid == 0) {
                kill(parid, SIGINT); //send SIGINT to parent
                sleep(SLEEP_TIME); //Wait
                kill(parid, SIGQUIT); //send SIGQUIT to parent
        }
        /*Portion run in the parent process*/
        else {
                if (signal(SIGINT, signal_catcher) == SIG_ERR)   
                {
                        perror("SIGINT");
                        exit(1);
                }
                if (signal(SIGQUIT, signal_catcher) ==SIG_ERR) {
                        perror("SIGQUIT");
                        exit(2);
                }
                for (int i=0; ; ++i) {
                        printf("%i\n", i);
                        sleep(1);
                }
        }
        return 0;
}

void signal_catcher(int the_sig) 
{
        signal(the_sig, signal_catcher); /*reset*/
        printf("\nSignal %d received.\n", the_sig);
        if (the_sig == SIGQUIT)
        exit(3);
}