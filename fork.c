#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Execute the command using this shell program */
#define SHELL "/bin/sh"

int my_system(const char *command)
{
	int		status;
	pid_t	pid;

	pid = fork();
	printf("pid = %d\n", pid);
	if (pid == 0)
	{
		/* this is the child process */
		printf("Executing child process\n");
		execl(SHELL, SHELL, "-c", command, NULL);
		_exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		/* the fork failed */
		printf("Fork failed\n");
		status = -1;
	}
	else
	{
		/* this is the parent process. Wait for the child to complete */
		printf("Waiting for child process to return\n");
		if (waitpid(pid, &status, 0) != pid)
			status = -1;
	}
	printf("almost done with my_system function\n");
	return (status);
	
}

int	main(void)
{
	int	ret;

	ret = 0;
	ret = my_system("ls -l");
	return (ret);
}