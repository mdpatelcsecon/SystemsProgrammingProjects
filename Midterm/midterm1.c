/*1. Develop a program to do the follows.
   a) Accept a file name from command line.
   b) Find its permission.
   c) Ask user to enter a permission(an octal number), such as 765.
   d) Compare the user entered permission to the file's permission.
   e) If matched, output "Bingo! Your guess is right."
   f) If not matched, output "No, your guess is NOT right."
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>


int main(int argc, char * argv[])
{
        struct stat fstat;
        if (stat(argv[1], &fstat)) {
                perror("Error getting file stats");
                return -1;
        } else {
                /*Get the user's guess*/
                printf("Enter the file permission code in octal: ");
                fflush(stdout);
                char guess[4];
                memset(&guess, 0, 4);
                scanf("%4s", guess);
                /*Get the actual permissions in the same format*/
                mode_t mode = fstat.st_mode;
                char actual[10];
                sprintf(actual, "%d", mode);
                memset(&actual[3], 0, 7);
                /*Compare the strings*/
                if(strcmp(guess, actual) == 0) {
                        printf("Bingo! Your guess is right.\n");
                } else {
                        printf("No, your guess is NOT right.\nThe correct answer is %s\n", actual);
                }
                return 0;        
        }
}