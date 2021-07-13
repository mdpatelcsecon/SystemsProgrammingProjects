#include <stdio.h>
#include <stdlib.h>
int
main(int argc, char* argv[]) {
   int intData[argc-1], i, max=0;

   if (argc <2) {
	   printf("At least one integer is required from command line.\n");
	   exit(2);
   }

   for (i=1; i<argc; i++)
      intData[i-1] = atoi(argv[i]);
   max = intData[0];
   for (i=1; i<argc-1; i++)
      if (intData[i] > max)
         max = intData[i];
   printf("Max=%d\n", max);
   exit(0);
}
