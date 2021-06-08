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
#include<errno.h>
#include<string.h>
int main(int argc, char * argv[])
{
    chdir("Dir0");
    system("clear");
    //File Management
    int fd = open("t1.txt", O_RDWR);

    //Executing ls-l
    char * command[3];// [ls, -l, NULL]
    char * command_two[3];//cat tree.txt
    int child = fork();
    if(child == -1)
    {   
        perror("Error Forking Child\n");
    }
    else if(child == 0)
    {
        //Child Proc
        dup2(fd,1); //Make stdout go to t1.txt
        command[0] = "ls";
        command[1] = "-l";
        command[2] = NULL;
        int ret = execvp(command[0],command);//execute ls -l
        if(ret == -1)
        {
            fprintf(stderr, "ERROR EXECUTING ls -l\n");
            return 1;
        }
        
        close(fd);
        
        
    }
    else if(child > 0)
    {
        //Parent Proc
        wait(NULL);
        int child2 = fork();
        if(child2 == -1){
            perror("Error forking Child2\n");
        }
        else if(child2 == 0)
        {
            //Cat output of ls -l to the terminal so the user can see it
            command_two[0] = "cat";
            command_two[1] = "t1.txt";
            command_two[2] = NULL;
            int ret = execvp(command_two[0],command_two);//execute cat tree.txt
            //int ret = 0;
            if(ret == -1)
            {
                printf("ERROR EXECUTING CAT || ERRNO : [%d] : [%s]\n",errno,strerror(errno));
            }
            
        }
        else if(child2 > 0)
        {
            //Back to PARENT
            wait(NULL);
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
    }
    
}
