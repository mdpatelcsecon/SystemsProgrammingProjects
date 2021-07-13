/*
*A last | sort command pipeline
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int
main(int argc, char *argv[]) {
        int f_des[2];
        int f_des2[2];
        //int f_des2[2];
        if (pipe(f_des) == -1 && pipe(f_des2) == -1) 
        {
                perror("Pipe");
                exit(1);
        }  
        switch (fork()) 
        {
        case -1: 
                perror("Fork");
                exit(2);
        case 0:  /*In the child process */
                //connect the write pipe
                dup2(f_des[1], fileno(stdout));
                close(f_des[0]); 
                close(f_des[1]);
                close(f_des2[0]);
                close(f_des2[1]);
                //execute program
                execlp(argv[1], argv[1], NULL);
                exit(3);
        default:
                switch(fork())
                {
                case -1: 
                        perror("Fork2");
                        exit(2);
                case 0:
                        //connect the read pipe
                        dup2(f_des[0], fileno(stdin));
                        close(f_des[0]);
                        close(f_des[1]);
                        //connect the write pipe
                        dup2(f_des2[1], fileno(stdout));
                        close(f_des2[0]); 
                        close(f_des2[1]);
                        //execute program
                        execlp(argv[2], argv[2], NULL);
                        exit(4);
                default: //The final process runs in the parent
                        close(f_des[0]);
                        close(f_des[1]);
                        //connect the read pipe
                        dup2(f_des2[0], fileno(stdin));
                        close(f_des2[0]);
                        close(f_des2[1]);
                        //execute program
                        execlp(argv[3], argv[3], NULL);
                        exit(5);
                }
        }
}      