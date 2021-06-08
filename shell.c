#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_HISTORY 4

void print_history(char history[MAX_HISTORY][10], int count);
void add_to_history(char history[MAX_HISTORY][10], char *command, int *count);
bool input_check(char *command);
bool exit_shell();

int main () 
{
	pid_t child;
	char history[MAX_HISTORY][10];
	int count_history=0;
	char command[10];
	char file[]="./";
	for(;;)
	{
		printf(">>>");
		fgets(command,sizeof(command),stdin);
		strtok(command,"\n");
		while (!input_check(command))
		{
			printf(">>>");
			fgets(command,sizeof(command),stdin);
			strtok(command,"\n");
		}

		child = fork();
		switch (child)
		{
			case -1:
				printf("Failed to create a child process\n");
				exit(EXIT_FAILURE);
			case 0:
				if(strcmp(command,"exit")==0){
					execlp("ls","ls","-l",NULL);
				}
				else
				{
					strcat(file,command);
					execlp(file,file,NULL);
				}
			default:
				wait(NULL);
				add_to_history(history,command,&count_history);
		}
		if(strcmp(command,"exit")==0){
			print_history(history,count_history);
			exit_shell();
			break;
		}
	}
	return 0;
}

bool input_check(char *command)
{
	char *commands[] = {"tree","list","path","exit"};
	for(int i=0;i<4;i++)
		if(strcmp(command,commands[i])==0)
			return true;
	printf("Error: Invalid Command. (tree, list, path, exit)\n");
	return false;
}

void add_to_history(char history[MAX_HISTORY][10], char *command, int *count)
{
	if(strcmp(command,"exit")==0)
		return;
	if(*count < MAX_HISTORY)
	{
		strcpy(history[*count],command);
		(*count)++;
	}
	else
	{
		for(int i=0;i<MAX_HISTORY-1;i++)
			strcpy(history[*count],history[*count+1]);
		strcpy(history[MAX_HISTORY-1],command);
	}
}

void print_history(char history[MAX_HISTORY][10], int count)
{
	if(count == 0)
		printf("\nNo History\n");
	else
	{
		printf("\nList of last 4 commands:\n");
		for(int i=0;i<count;i++)
			printf("%s\n",history[i]);
	}
}

bool exit_shell()
{
	printf("\nPress Enter");
	char ch;
	ch = fgetc(stdin);
	if(ch=='\n')
		{printf("Bye\n");return true;}
	return false;
}