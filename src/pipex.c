#include "pipex.h"

static int	check_input(int argc)
{
	if (argc != 5)
    {
        printf("Error\nWrong amount of arguments. Run as: ./pipex file1 cmd1 cmd2 file2\n");
        return (RETURN_FAILURE);
    }
	return (RETURN_SUCCESS);
}

int main(int argc, char **argv)
{
	int		ret;
	int		fds[2];
	pid_t	pid;
	
	/* Input check */
	if (check_input(argc))
		return (-1);

	/* Print arguments */
    printf("0 = %s\n", argv[0]);
	printf("1 = %s\n", argv[1]);
	printf("2 = %s\n", argv[2]);
	printf("3 = %s\n", argv[3]);
	printf("4 = %s\n", argv[4]);
	printf("5 = %s\n", argv[5]);

	/* Create pipe */
	ret = pipe(fds);
	if (ret == -1)
	{
		return (-1);
	}

	/* Fork process */
	pid = fork();

	/* Error forking */
	if (pid < 0)
	{
		printf("Error while forking process\n");
		return (RETURN_FAILURE);
	}

	/* Child process: write to pipe */
	if (pid == 0)
	{
		close(fds[0]);
		dup2(fds[1], STDOUT_FILENO);
		char *args[] = {"/bin/ls", "-l", NULL};
		//char *path[] = {"PATH=/bin:/usr/bin", NULL};
		execve(args[0], args, NULL);
	}

	/* Main process: read form pipe */
	if (pid > 0)
	{
		close(fds[1]);
		dup2(fds[0], STDIN_FILENO);
		char *args[] = {"/bin/grep", "fork", NULL};
		//char *path[] = {"PATH=/bin:/usr/bin", NULL};
		execve(args[0], args, NULL);
	}


	return (RETURN_SUCCESS);
}