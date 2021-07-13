//linux headers
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
//standard C headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(void)
{
        //Create the FIFO
        if(mknod("/tmp/pipe", S_IFIFO | 0666, 0) == -1) {
                perror("Creating Named Pipe Failed");
        }
        //open the named pipe for writing only
        int pd = open("/tmp/pipe", O_WRONLY);
        if(pd < 0) {
                perror("Opening FIFO File Descriptor Failed");
        }
        //seed the RNG with the current time to produce random values
        srand(time(NULL));
        //printf("Testing\n");
        //generate and write the values in a loop
        unsigned int n = 0;
        for(unsigned int i = 0; i < 100; ++i) {
                n = rand()%101 + 1; //generate random number in range [0, 100]
                printf("%d\n", n);
                write(pd, &n, sizeof(n)); //write the random number to the FIFO
                //printf("%d\n", n);
        }
        return 0;
}