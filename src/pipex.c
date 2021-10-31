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

int main(int argc, char **argv, char **envp)
{
	int		ret;
	int		fds[2];
	pid_t	pid;
	t_data	data;
	
	/* Input check */
	if (check_input(argc))
		return (-1);

	/* Initialize data */
	ft_bzero(&data, sizeof(data));

	/* Parse data */
	parse_input(argv, &data);

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
		//char *args[] = {"/usr/bin/ls", "-la", NULL};
		char **alloc = malloc(sizeof(char*) * 4);
		alloc[0] = malloc(sizeof(char) * 12);
		ft_strlcpy(alloc[0], "/usr/bin/ls", 12);
		alloc[1] = malloc(sizeof(char) * 6);
		ft_strlcpy(alloc[1], "-l", 3);
		alloc[2] = malloc(sizeof(char) * 3);
		ft_strlcpy(alloc[2], "-a", 3);
		alloc[3] = 0;
		// printf("alloc[0] = %s\n", alloc[0]);
		// printf("alloc[1] = %s\n", alloc[1]);
		// printf("alloc[2] = %s\n", alloc[2]);

		close(fds[0]);
		dup2(fds[1], STDOUT_FILENO);
		execve(alloc[0], alloc, envp);
	}

	/* Main process: read form pipe */
	if (pid > 0)
	{
		char *args[] = {"/usr/bin/wc", "-l", NULL};
		close(fds[1]);
		dup2(fds[0], STDIN_FILENO);
		execve(args[0], args, envp);
	}


	return (RETURN_SUCCESS);
}