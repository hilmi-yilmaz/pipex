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
	t_pids  pid;
	t_data	data;

	/* Input check */
	if (check_input(argc))
		return (-1);

	/* Initialize data */
	ft_bzero(&data, sizeof(data));

	/* Parse data */
	parse_input(&data, argv, envp);

	/* Print data */
	print_data(data);

	/* Create pipe */
	ret = pipe(fds);
	if (ret == -1)
	{
		return (-1);
	}

	/* Fork process */
	pid.one = fork();

	/* Error forking */
	if (pid.one < 0)
	{
		printf("Error while forking process\n");
		return (RETURN_FAILURE);
	}
	/* Child process 1: write to pipe */
	if (pid.one == 0)
	{
        child_one(&data, fds, envp);
	}

	/* Child process 2: Read from pipe */
	pid.two = fork();
	if (pid.two < 0)
	{
		printf("Error while forking process\n");
		return (RETURN_FAILURE);
	}

	if (pid.two == 0)
	{
		close(fds[1]);
		close(data.file_in);
		dup2(fds[0], STDIN_FILENO);
		dup2(data.file_out, STDOUT_FILENO);
		close(fds[0]);
		close(data.file_out);
		execve(data.cmd2[0], data.cmd2, envp);
	}

	close(fds[0]);
	close(fds[1]);
	close(data.file_in);
	close(data.file_out);

	waitpid(pid.one, NULL, 0);
	waitpid(pid.two, NULL, 0);

	return (RETURN_SUCCESS);
}