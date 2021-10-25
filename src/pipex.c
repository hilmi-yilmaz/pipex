#include "pipex.h"

int main(int argc, char **argv)
{
	int		ret;
	int		status;
	int		fds[2];
	pid_t	pid;
	
	/* Input check */
	if (argc != 5)
    {
        printf("Error\nWrong amount of arguments. Run as: ./pipex file1 cmd1 cmd2 file2\n");
        return (RETURN_FAILURE);
    }

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
		printf("Error\n%s\n", strerror(errno));
		return (RETURN_FAILURE);
	}

	/* Fork process */
	pid = fork();

	/* Child process: write to pipe */
	if (pid == 0)
	{
		ret = close(fds[0]);
		if (ret == -1)
		{
			printf("Error\n%s\n", strerror(errno));
			return (RETURN_FAILURE);
		}
		ret = write(fds[1], argv[1], ft_strlen(argv[1]) + 1);
		if (ret == -1)
		{
			printf("Error\n%s\n", strerror(errno));
			return (RETURN_FAILURE);
		}
		exit(RETURN_SUCCESS);
	}

	/* Main process: read form pipe */
	if (pid > 0)
	{
		ret = waitpid(pid, &status, 0); // returns process id
		if (ret == -1)
		{
			printf("Error\n%s\n", strerror(errno));
			return (RETURN_FAILURE);
		}
		close(fds[1]);
		char	buff[100];
		ret = read(fds[0], buff, 5);
		if (ret == -1)
		{
			printf("Error\n%s\n", strerror(errno));
			return (RETURN_FAILURE);
		}
		printf("buff = |%s|\n", buff);
		close(fds[0]);
	}

	/* Error forking */
	if (pid < 0)
	{
		printf("Error while forking process\n");
		return (RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
}