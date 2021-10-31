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

	/* print parsed data */
	printf("file1 = %s\n", data.file1);
	printf("file2 = %s\n", data.file2);
	printf("cmd1 = ");
	int i = 0;
	while (data.cmd1[i] != NULL)
	{
		printf("%s ", data.cmd1[i]);
		i++;
	}
	printf("\n");
	printf("cmd2 = ");
	i = 0;
	while (data.cmd2[i] != NULL)
	{
		printf("%s ", data.cmd2[i]);
		i++;
	}
	printf("\n");

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
		// char **alloc = malloc(sizeof(char*) * 4);
		// alloc[0] = malloc(sizeof(char) * 12);
		// ft_strlcpy(alloc[0], "/usr/bin/ls", 12);
		// alloc[1] = malloc(sizeof(char) * 6);
		// ft_strlcpy(alloc[1], "-l", 3);
		// alloc[2] = malloc(sizeof(char) * 3);
		// ft_strlcpy(alloc[2], "-a", 3);
		// alloc[3] = 0;
		// printf("alloc[0] = %s\n", alloc[0]);
		// printf("alloc[1] = %s\n", alloc[1]);
		// printf("alloc[2] = %s\n", alloc[2]);

		close(fds[0]);
		dup2(fds[1], STDOUT_FILENO);
		execve(data.cmd1[0], data.cmd1, envp);
	}

	/* Main process: read form pipe */
	if (pid > 0)
	{
		// char *args[] = {"/usr/bin/wc", "-l", NULL};
		close(fds[1]);
		dup2(fds[0], STDIN_FILENO);
		execve(data.cmd2[0], data.cmd2, envp);
	}


	return (RETURN_SUCCESS);
}