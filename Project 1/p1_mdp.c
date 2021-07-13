/*Template for the first program in Assignment 1 provided by Dr. Yongming Tang*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int icmp(const void *fst, const void *sec) 
{
        int a = *(const int*) fst;
        int b = *(const int*) sec;
        if(a > b) return 1;
        else if(a < b) return -1;
        else return 0;
}

int main(int argc, char * argv[])/*Command line arguments*/
/*./a.out 5 3 4*/ /*argv[0], argv[1],argv[2], argv[3]*/
{
        int i=0, Sum=0, EvenCount=0, OddCount=0; 
        int data[argc-1]; //sorted array
        for (i=1; i<argc; ++i) /*convert strings to integers*/
        {
                data[i-1] = atoi(argv[i]);
                if ((data[i-1]%2) == 0) EvenCount++;
                else OddCount++;    /*do odd count here*/
                Sum += data[i-1];
        }
        /* Use array data[] to do sorting here
        then output the results with statement like printf("Sum=%d\n", Sum);
        */
        qsort(data, argc - 1, sizeof(int), icmp); //sort using libc funtion qsort

        printf("Data: ");
        for(int i = 0; i < argc - 1; ++i) {
                printf("%d ", data[i]);
        }
        printf("\n");
        printf("Sum: %d\n", Sum);
        printf("# of Evens: %d\n", EvenCount);
        printf("# of Odds: %d\n", OddCount);

        printf("User ID:%d\n",getuid());
        printf("Effective User ID:%d\n",geteuid());
        printf("User Group ID:%d\n",getgid());
        printf("Effecive User Group ID:%d\n",getegid());
}