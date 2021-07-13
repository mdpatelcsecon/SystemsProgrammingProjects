#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LIST_LEN (size_t)argc-1

int isnnum(const char *const str);

int main(int argc, char *argv[])
{
        if (LIST_LEN < 1) return 1;
        /*Variable declarations*/
        long sum = 0, integers[LIST_LEN];
        //parse the inputs as integers
        for(size_t i = 0; i < LIST_LEN; ++i) {
                if (isnnum(argv[i + 1])) return 2;
                integers[i] = atol(argv[i + 1]); 
        }
        //sum the integers
        for(size_t i = 0; i < LIST_LEN; ++i) {
                sum += integers[i];
        }
        //print the sum
        printf("Sum: %ld\n", sum);
        //exit
        return 0;
}

int isnnum(const char *const str)
{
        for (size_t i = 0; i < strlen(str); ++i) {
                if (isdigit(str[i]) == 0) return 1;
        }
        return 0;
}