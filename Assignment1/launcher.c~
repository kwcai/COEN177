/* Simple shell program that takes the user input and runs commands */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
	int status;
	char com[20];
	char *parameters[] = { com, NULL };

	/* While loop to run until user inputs "exit" */
	while(1)
	{
		printf("Enter command: ");
		scanf("%s", &com);
		printf("You entered \'%s\'\n", com);
		
		/* If user input is not exit, it will attempt to launch a given program */
		if(strcmp(com, "exit") != 0)
		{
			/* Checks if parent or child process
			 * Parent would get pid of child, which is != 0
			 * Child would be returned 0*/
			if(fork()!=0)
			{
				/* Code to be run by parent */
				waitpid(-1, &status, 0);
			}
			else
			{
				/* Code to be run by child
				 * execvp takes user input as command and parameters */
				printf("Launching...\n");
				execvp(parameters[0], parameters);
				printf("Failed...\n");
				exit(1);
			}
		}
		else
		{
			printf("Exiting...\n");
			break;
		}
	}

	return;
}
