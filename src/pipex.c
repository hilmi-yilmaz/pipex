#include "pipex.h"

static int	check_input(int argc)
{
	if (argc != 5)
    {
        printf("Error\nWrong amount of arguments. Run as: ./pipex file_in cmd1 cmd2 file_out\n");
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

	/* Print data */
	print_data(data);

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
		dup2(data.file_in, STDIN_FILENO);
		execve(data.cmd1[0], data.cmd1, envp);
	}
	/* Main process: read form pipe */
	if (pid > 0)
	{
		close(fds[1]);
		dup2(fds[0], STDIN_FILENO);
		dup2(data.file_out, STDOUT_FILENO);
		close(data.file_out);
		execve(data.cmd2[0], data.cmd2, envp);
	}


	return (RETURN_SUCCESS);
}