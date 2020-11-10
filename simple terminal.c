#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#define TOKEN_SIZE 64	// token size used for each parsed string

int main()
{
	char **args;    // data storage for parsed string 	
	pid_t pid;      // It will be used to get child process after fork is performed. 
 
	//Continous loop of do-while loop untill user enters quit 
	do {
		char *strng;
	       	if ((strng= readline ("minor2> " )) != NULL )
		{	
			//variable used to parse user input string strng
			int num = TOKEN_SIZE, index = 0;  
		
			args = malloc(sizeof(char*)*num);
  			char *temp_token;  

			if (!args) //Allocation memory checked 
	       		{
   				 fprintf(stderr, "Error in Memory Allocation.\n");
   				 exit(EXIT_FAILURE);
  			}
			//Individual string separated by space " " is taken from user input string by using strtok  -
			temp_token = strtok(strng," ");		
			while (temp_token != NULL) 
			{
				args[index] = temp_token;
				index++;
				temp_token = strtok(NULL, " ");
			}		
			//Null is at the end of the args 
			args[index] = NULL;
		
			//checking if user has entered quit 
			if (!strcmp(args[0],"quit"))
                break;

			pid = fork();
			if (pid == 0) 
			{
    				if (execvp(args[0], args) == -1) 
				{
					printf("%s : Command not found\n",strng);
    				}
    				exit(EXIT_FAILURE);
  			} 
			else if (pid < 0) 
			{
    				// Error occured while forking 
    				perror("ERROR\n");
  			} 
			else 
			{
				wait(NULL);
  			}
		
			//dellocating before allocated memory 
	    		free(args);
		}

  	} while (1); //Condition for while to run untill user hit quit 


	return(0);
}

