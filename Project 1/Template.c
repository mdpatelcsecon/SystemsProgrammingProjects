/*Template for the first program in Assignment 1 provided by Dr. Yongming Tang*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int
main(int argc, char * argv[])/*Command line arguments*/
/*./a.out 5 3 4*/ /*argv[0], argv[1],argv[2], argv[3]*/
{
   int i=0, data[argc-1], Sum=0, EvenCount=0, OddCount=0; 
   for (i=1; i<argc; i++) /*convert strings to integers*/
   {
      data[i-1] = atoi(argv[i]);
      if ((data[i-1]%2) == 0) EvenCount++;
      else     /*do odd count here*/
      Sum=Sum+data[i-1];
   }
/* Use array data[] to do sorting here
   then output the results with statement like printf("Sum=%d\n", Sum);

*/
printf("User ID:%d\n",getuid());
printf("Effective User ID:%d\n",geteuid());
printf("User Group ID:%d\n",getgid());
printf("Effecive User Group ID:%d\n",getegid());
uid_t geteuid();
gid_t getgid();
gid_t getegid();


}



/*Template for the 2nd program in Assignment 1 provided by Dr. Yongming Tang*/

/*After conversion of string integers to real integers,
  do the follows so that there are 4 child processes.
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int
main(int argc, char * argv[])
{
   int i=0, data[argc-1], Sum=0, EvenCount=0, OddCount=0; 
   for (i=1; i<argc; i++) /*convert strings to integers*/
      data[i-1] = atoi(argv[i]);

	switch(fork())
	{   case -1:
		   break;
	    case 0: /*1st child process*/

		   /*here for sorting*/

		   exit(1);
	    default:
		   switch(fork())
		   {   case -1:
			      break;
		       case 0: /*2nd child process*/

			      /*here for summing*/

			      exit(2);
		       default:
			      switch(fork())
			      {   case -1:
					 break;
				  case 0: /*3rd child process*/

					 /*here for counting even*/

					 exit(3);
				  default:
					 switch(fork())
					 {   case -1:
						    break;
					     case 0: /*4th child process*/

						    /*here for counting odd*/

						    exit(4);
					     default:
						    break:
					 }
			      }
		   }
	}
} 
