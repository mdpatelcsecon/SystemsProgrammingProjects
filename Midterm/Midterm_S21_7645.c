/******************************************************************************
*	Program Author:	Name:				ID:		      *
*	Midterm Exam Date: March 23, 2021		Class:	CSCI7645.81   *
*******************************************************************************/
/*
1. Develop a program to do the follows.
   a) Accept a file name from command line.
   b) Find its permission.
   c) Ask user to enter a permission(an octal number), such as 765.
   d) Compare the user entered permission to the file's permission.
   e) If matched, output "Bingo! Your guess is right."
   f) If not matched, output "No, your guess is NOT right."
*/
/*
2. Modify Program 4.4 at the end of Lecrute 4 to accept an integer from command line and let the infinite loop starts from the integer.
*/
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