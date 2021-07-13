/*
3. Develop a program that does the follows.
   a) Accept an integer from command line.
   b) Write the integer to an unnamed pipe.
   c) fork() a child process.
   d) The child process read the integer from the pipe, and then use execl() to run the program of Question 2 with the integer as argument.
   e) The parent process delivers signal SIGINT to the child process, sleep 3 seconds, and then delivers signal SIGQUIT to the child process.
   f) The parent process wait for the child process to terminate.
   g) The parent process outputs the exit code of the child process.
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char *argv[]) 
{
        int f_des[2];
        if (pipe(f_des) == -1) {
                perror("Pipe"); 
                exit(1);
        }
        pid_t cpid = fork();
        switch (cpid) {
        case -1: 
                perror("Fork"); 
                exit(2);
        case 0: 
                dup2(f_des[0], fileno(stdin));
                close(f_des[1]); 
                close(f_des[0]);
                /*read integer from the pipe*/
                char start_val[10];
                memset(start_val, 0, 10);
                scanf("%10s", start_val);

                execl("./midterm2", start_val, (char *) NULL);
                exit(3);
        default:
                close(f_des[0]);
                /*Write the int to the pipe*/ 
                if(write(f_des[1], argv[1], strlen(argv[1])) == -1) {
                        perror("Write to pipe.");
                }
                /*Send signals*/
                kill(cpid, SIGINT);
                sleep(3);
                kill(cpid, SIGKILL);
                /*print exit code*/
                int cp_exit;
                wait(&cp_exit);
                printf("Child exited with value: %d\n", cp_exit);
                exit(4);
        }
}      