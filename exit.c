/*
FINAL PROJECT
CSC 332 S
GROUP B
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX_HISTORY 4

int main()
{

    char history[MAX_HISTORY][512];     // Holds last 4 commands
    char * listDir[3];                  // [ls, -l, NULL]
    FILE *commands;

    // PLACE HOLDER FOR FINAL CODE
    strcpy(history[0], "tree*");
    strcpy(history[1], "list*");
    strcpy(history[2], "path*");
    strcpy(history[3], "exit*");


    // Create Child Process
    int child = fork();

    // Verify child was created successfully
    if(child == -1) {
        perror("Error Forking Child\n");
    }

    // Beginning of Child Process
    else if(child == 0) {

        // Will display the last 4 commands2
        printf("\nList of last 4 commands:\n");
        for (int i = 0; i < MAX_HISTORY; i++)
            printf("%s\n", history[i]);


        listDir[0] = "ls";
        listDir[1] = "-l";
        listDir[2] = NULL;

        // Will display detailed list of current directory
        printf("\nDetailed list of current directory:\n");
        if(execvp(listDir[0],listDir) == -1)  {
            fprintf(stderr, "ERROR EXECUTING ls -l\n");
            return 1;
        }


    }

    // Begninning of Parent Process
    else if(child > 0)  {

        // Wait for Child Process to complete execution
        wait(NULL);
    }

    char prompt;
    bool done = false;

    // Prompt user to exit shell
    printf("\nPlease press enter to exit the shell and return to terminal\n");
    prompt = getchar();
    if (prompt == '\n' || prompt == EOF) {
        done = true;
        printf("\nReturning to terminal...\n");
    }

    if (done = true)
        exit(0);
}
