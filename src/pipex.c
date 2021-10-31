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
	printf("file1 = %d\n", data.file1);
	printf("file2 = %d\n", data.file2);
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
		close(fds[0]);
		dup2(fds[1], STDOUT_FILENO);
		dup2(data.file1, STDIN_FILENO);
		execve(data.cmd1[0], data.cmd1, envp);
	}
	/* Main process: read form pipe */
	if (pid > 0)
	{
		close(fds[1]);
		dup2(fds[0], STDIN_FILENO);
		dup2(data.file2, STDOUT_FILENO);
		close(data.file2);
		execve(data.cmd2[0], data.cmd2, envp);
	}


	return (RETURN_SUCCESS);
}