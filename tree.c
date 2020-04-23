//Anthi Papadopoulos tree* command for Final Group Project

#include <sys/types.h>
#include <sys/stat.h> 
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
//#include <dirent.h>

int main (int argc, char *argv[])
{
  struct stat st = {0}; //checker for existing directories/files

  //make directory Dir0 with user and group permissions
  int dir0 = mkdir ("Dir0", 0755);
      //if Directory creation successful print so 
  if (!dir0)
	    printf ("Directory Dir0 successfully created\n");
      //else print error	
	else 
	   {
    	printf ("Error: Unable to create Directory Dir0\n");
     }
  chdir ("Dir0");

  //if Dir1 doesn't exist within Dir0, create it with permissions for user and group.
	if (stat("Dir1", &st) == -1) 
       {
	        mkdir("Dir1", 0755);
      	}
  //if text files do not exist within Dir0, create them with permisions.

      int fd1 = open("t1.txt", O_RDWR | O_APPEND | O_CREAT); 
    	if(fd1 < 0)
       	{
      	   perror("error creating file t1.txt\n");
         	 exit(-1);
       	}

      int fd2 = open("t2.txt", O_RDWR | O_APPEND | O_CREAT); 
    	if(fd2 < 0)
   	     {
        	 perror("error creating file t2.txt\n");
       	   exit(-1);
         }
     int fd3 = open("t3.txt", O_RDWR | O_APPEND | O_CREAT); 
     if(fd3 < 0)
      	{
      	   perror("error creating file t2.txt\n");
         	 exit(-1);
      	}
     	
	 close (fd1);
	 close (fd2);
         close (fd3);
   
    int r = system("cd Dir0");

	
   return 0;
}
