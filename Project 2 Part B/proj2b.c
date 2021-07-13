#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> 
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char * argv[])
{
        int sort_status, sort_es, sum_status, sum_es;

        
        sort_status = 0;
        sort_es     = 0;
        sum_status  = 0; 
        sum_es      = 0;
        /*Fork-Exec for sort*/
        pid_t sort_pid = fork();

        if (sort_pid == 0) { //sorts and prints the list
                execv("./sort", argv);
                fprintf(stderr, "Could not execute sort.");
        }
        /*Fork-Exec for sum*/
        pid_t sum_pid = fork();

        if (sum_pid == 0) {
                execv("./sum", argv);
                fprintf(stderr, "Could not execute sum.");
        }
        /*Wait and get status for sort*/
        waitpid(sort_pid, &sort_status, 0);
        if (WIFEXITED(sort_status)) {
                sort_es = WEXITSTATUS(sort_status);
                printf("Sort Exit Status: %d\n", sort_es);
                if(sort_es != 0) {
                        fprintf(stderr, "Retrying Sort\n");
                        sort_pid = fork();
                        if (sort_pid == 0) { //sorts and prints the list
                                execv("./sort", argv);
                                fprintf(stderr, "Could not execute sort.");
                        }
                        waitpid(sort_pid, &sort_status, 0);
                        if (WIFEXITED(sort_status)) {
                                sort_es = WEXITSTATUS(sort_status);
                                printf("Sort (Retry) Exit Status: %d\n", sort_es);
                        }
                }
        }
        /*Wait and get status for sum*/
        waitpid(sum_pid, &sum_status, 0);
        if (WIFEXITED(sum_status)) {
                sum_es = WEXITSTATUS(sum_status);
                printf("Sum Exit Status: %d\n", sort_es);
                if(sum_es != 0) {
                        fprintf(stderr, "Retrying Sum\n");
                        sum_pid = fork();
                        if (sum_pid == 0) { 
                                execv("./sort", argv);
                                fprintf(stderr, "Could not execute sort.");
                        }
                        waitpid(sum_pid, &sum_status, 0);
                        if (WIFEXITED(sum_status)) {
                                sum_es = WEXITSTATUS(sum_status);
                                printf("Sum (Retry) Exit Status: %d\n", sum_es);
                        }
                }
        }
        /*Print message if there are input errors*/
        if (sort_es == 1 || sum_es == 1) fprintf(stderr, "Retry failed: No numbers entered. Rerun the program with valid inputs.\n");
        else if (sort_es == 2 || sum_es == 2) fprintf(stderr, "Retry failed: Non-numeric value found. Rerun the program with valid input.\n");

        return 0;
}