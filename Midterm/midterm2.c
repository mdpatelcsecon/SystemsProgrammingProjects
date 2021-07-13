/*
2. Modify Program 4.4 at the end of Lecrute 4 to accept an integer from command line and let the infinite loop starts from the integer.
*/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void signal_catcher(int);

int main(int argc, char *argv[]) 
{
        if (signal(SIGINT, signal_catcher) == SIG_ERR)   
        {
                perror("SIGINT");
                exit(1);
        }
        if (signal(SIGQUIT, signal_catcher) == SIG_ERR) {
                perror("SIGQUIT");
                exit(2);
        }
        for (int i = atoi(argv[1]); ;++i) {
                printf("%i\n", i);
                sleep(1);
        }
}

void signal_catcher(int the_sig) 
{
        signal(the_sig, signal_catcher); /*reset*/
        printf("\nSignal %d received.\n", the_sig);
        if (the_sig == SIGQUIT)
                exit(3);
}