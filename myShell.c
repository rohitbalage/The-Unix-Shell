#include <stdio.h>
#include <stdlib.h>
#include <string.h> // With strcmp and strtok() ()
#include <unistd.h> // pid t with fork()
#include <sys/wait.h> // Regarding waitpid() and related macros

char SHELL_NAME[50] = "myShell";
int QUIT = 0;

// a command line function that reads a line into the queue
char *readLine()
{
	char *line = (char *)malloc(sizeof(char) * 1024); // Allocate Queue Instantaneously
	char c;
	int pos = 0, bufsize = 1024;
	if (!line) // Error in Buffer Allocation
	{
		printf("\nError in Buffer Allocation.");
		exit(EXIT_FAILURE);
	}
	while(1)
	{
		c=getchar();
		if (c == EOF || c == '\n') // If the file ends or a new line begins, substitute a null character.
		{
			line[pos] = '\0';
			return line;
		}
		else
		{
			line[pos] = c;
		}
		pos ++;
		// If the buffer has been exceeded
		if (pos >= bufsize)
		{
			bufsize += 1024;
			line = realloc(line, sizeof(char) * bufsize);
			if (!line) // Error in Buffer Allocation
			{
			printf("\nError in Buffer Allocation.");
			exit(EXIT_FAILURE);
			}
		}
	}

}

// Split a line of code into its individual instructions.
char **splitLine(char *line)
{
	char **tokens = (char **)malloc(sizeof(char *) * 64);
	char *token;
	char delim[10] = " \t\n\r\a";
	int pos = 0, bufsize = 64;
	if (!tokens)
	{
		printf("\nError in Buffer Allocation.");
		exit(EXIT_FAILURE);
	}
	token = strtok(line, delim);
	while (token != NULL)
	{
		tokens[pos] = token;
		pos ++;
		if (pos >= bufsize)
		{
			bufsize += 64;
			line = realloc(line, bufsize * sizeof(char *));
			if (!line) // Error in Buffer Allocation
			{
			printf("\nError in Buffer Allocation.");
			exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, delim);
	}
	tokens[pos] = NULL;
	return tokens;
}

// Part Pertaining to Internal Command line

// Declarations of Functions
int myShell_cd(char **args);
int myShell_exit();

// Interpretations
char *builtin_cmd[] = {"cd", "exit"};

int (*builtin_func[]) (char **) = {&myShell_cd, &myShell_exit}; // array of function pointers that execShell can call

int numBuiltin() //Number of built-in commands function
{
	return sizeof(builtin_cmd)/sizeof(char *);
}

// definitions for built-in commands
int myShell_cd(char **args)
{
	if (args[1] == NULL) 
	{
		printf("myShell: expected argument to \"cd\"\n");
	} 
	else 
	{
		if (chdir(args[1]) != 0) 
		{
			perror("myShell: ");
		}
	}
	return 1;
}

int myShell_exit()
{
	QUIT = 1;
	return 0;
}

// method that perform commands and generate child processes
int myShellLaunch(char **args)
{
	pid_t pid, wpid;
	int status;
	pid = fork();
	if (pid == 0)
	{
		// childs process
		if (execvp(args[0], args) == -1)
		{
			perror("myShell: ");
		}
	exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		//failed fork
		perror("myShell: ");
	}
	else
	{
		// parent process
	do 
	{
      wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return 1;
}

// function to carry out terminal command
int execShell(char **args)
{
	int ret;
	if (args[0] == NULL)
	{
		// null command
		return 1;
	}
	// Checking for built-in functions in a loop
	for (int i=0; i< numBuiltin(); i++) // he number of built-in functions is returned by numBuiltin().
	{
		if(strcmp(args[0], builtin_cmd[i])==0) // Make sure the built-in function name matches the user function.
			return (*builtin_func[i])(args); // Use the appropriate built-in function and pass arguments
	}
	ret = myShellLaunch(args);
	return ret;
}

// Read and parse the configuration file.
int readConfig()
{
	FILE *fptr;
	char line[200];
	char **args;
	fptr = fopen("config", "r");
	if (fptr == NULL)
	{
		printf("Unable to find config file.\n");
		return 1;
	}
	else
	{
		while(fgets(line, sizeof(line), fptr) != NULL)
		{
			printf("\n%s", line);
			args=splitLine(line);
			if(strcmp(args[0], "export")==0)
				strcpy(SHELL_NAME, args[1]);
		}
	}
	free(args);
	fclose(fptr);
	return 1;
}

// When myShell is called Interactively
int myShellInteract()
{
	char *line;
	char **args;
	while(QUIT == 0)
	{
		printf("%s> ", SHELL_NAME);
		line=readLine();
		args=splitLine(line);
		execShell(args);
		free(line);
		free(args);
	}
	return 1;
}

// When myShell is called with a Script as Argument
int myShellScript(char filename[100])
{
	printf("Received Script. Opening %s", filename);
	FILE *fptr;
	char line[200];
	char **args;
	fptr = fopen(filename, "r");
	if (fptr == NULL)
	{
		printf("\nUnable to open file.");
		return 1;
	}
	else
	{
		printf("\nFile Opened. Parsing. Parsed commands displayed first.");
		while(fgets(line, sizeof(line), fptr)!= NULL)
		{
			printf("\n%s", line);
			args=splitLine(line);
			execShell(args);
		}
	}
	free(args);
	fclose(fptr);
	return 1;
}

int main(int argc, char **argv)
{
	// Read from myShell Configuration Files
	readConfig();
	// Parsing commands Interactive mode or Script Mode
	if (argc == 1)
		myShellInteract();
	else if (argc == 2)
		myShellScript(argv[1]);
	else
		printf("\nInvalid Number of Arguments");

	// Exit the Shell
	return EXIT_SUCCESS;
}