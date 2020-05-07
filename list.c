/*
FINAL PROJECT
CSC 332 S
GROUP B
*/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<fcntl.h>
int main(int argc, char * argv[])
{
    chdir("Dir0");
    system("clear");
    //File Management
    int fd = open("t1.txt", O_RDWR);
    dup2(fd,1); //Make stdout go to t1.txt


    //Executing ls-l
    char * command[3];// [ls, -l, NULL]
    int child = fork();
    if(child == -1)
    {   
        perror("Error Forking Child\n");
    }
    else if(child == 0)
    {
        //Child Proc
        command[0] = "ls";
        command[1] = "-l";
        command[2] = NULL;
        int ret = execvp(command[0],command);//execute ls -l
        if(ret == -1)
        {
            fprintf(stderr, "ERROR EXECUTING ls -l\n");
            return 1;
        }
        
    }
    else if(child > 0)
    {
        //Parent Proc
        wait(NULL);
    }
    
    close(fd);
    //Renaming t1.txt to tree.txt
    char oldName[] = "t1.txt";
    char newName[] = "tree.txt";
    int ret = rename(oldName,newName);
    if(ret == -1)
    {
        fprintf(stderr, "ERROR EXECUTING RENAME\n");
        return 1;
    }
    return 0;
}
