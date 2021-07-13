#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LIST_LEN (size_t)argc-1

int cmpl(const void *l, const void *r);
int isnnum(const char *const str);

int main(int argc, char *argv[])
{
        if (LIST_LEN < 1) return 1;
        //To store the list of integers
        long integers[LIST_LEN];
        //parse the inputs as integers
        for(size_t i = 0; i < LIST_LEN; ++i) {
                if (isnnum(argv[i + 1])) return 2;
                integers[i] = atol(argv[i + 1]); 
        }
        //sort the integers
        qsort(&integers, LIST_LEN, sizeof(long), cmpl); 
        //print the sorted list
        printf("Sorted List: ");
        for(size_t i = 0; i < LIST_LEN; ++i) {
                printf("%ld ", integers[i]);
        }
        printf("\n");
        return 0;
}

int cmpl(const void *l, const void *r)
{
        if(*(long *) l > *(long *) r) return 1;
        else if (*(long *) l < *(long *) r) return -1;
        else return 0;
}
int isnnum(const char *const str)
{
        for (size_t i = 0; i < strlen(str); ++i) {
                if (isdigit(str[i]) == 0) return 1;
        }
        return 0;
}