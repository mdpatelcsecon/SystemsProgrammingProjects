#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

/*
Converts octal permission values to the equivalent string representation
Preconditions: str is a string buffer of length 4. n represents an octal digit.
Postcondition: The string representation of the permission represented by n is written to str.
Except: If n is not a valid octal digit then the buffer pointed to by str remains unchanged and a non-zero value is returned.
*/
int oct_to_pstr(char* str, const int n);

int main(int argc, char* argv[])
{
    //Validate number of arguments
    if (argc != 2) {
        perror("Invalid number of arguments.\n");
        return -1;
    }
    //Validate argument length
    else if (strlen(argv[1]) < 3) {
        perror("Input is too short\n");
        return -1;
    }
    else {
        /*Do the actual conversion*/
        char output[10] = { 0 }; //output string
        char* ostr = calloc(4, sizeof * ostr);
        for (size_t i = 0; i < 3; ++i) {
            char val_str[2] = { 0 };
            val_str[0] = argv[1][i];
            //printf("%s\n", val_str);
            if (oct_to_pstr(ostr, atoi(val_str)) != 0) {
                perror("Invalid octal value entered.\n");
                exit(-1);
            }
            //puts(ostr);
            strcat(output, ostr);
        }
        free(ostr);
        printf("%s\n", output);
        fflush(stdout);
        return 0;
    }
}

int oct_to_pstr(char* str, const int n)
{
    if (n > 7) return -1;
    else {
        const char map[8][4] = {
                "---",
                "r--",
                "-w-",
                "rw-",
                "--x",
                "r-x",
                "-wx",
                "rwx"
        };
        strcpy(str, map[n]);
        return 0;
    }
}
