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

	if (check_input(argc))
		return (-1);
	ft_bzero(&data, sizeof(data));
	parse_input(&data, argv, envp);
	//print_data(data);
	ret = pipe(fds);
	if (ret == -1)
	{
		printf("Error creating pipe.\n%s\n", strerror(errno));
		return (-1);
	}
	pid.one = fork();
	if (pid.one < 0)
	{
		printf("Error forking process (child 1).\n%s\n", strerror(errno));
		return (RETURN_FAILURE);
	}
	/* Child process 1: write to pipe */
	if (pid.one == 0)
        child_one(&data, fds, envp);

	/* Child process 2: Read from pipe */
	pid.two = fork();
	if (pid.two < 0)
	{
		printf("Error forking process (child 2).\n%s\n", strerror(errno));
		return (RETURN_FAILURE);
	}
	if (pid.two == 0)
		child_two(&data, fds, envp);

	close(fds[0]);
	close(fds[1]);
	close(data.file_in);
	close(data.file_out);

	waitpid(pid.one, NULL, 0);
	waitpid(pid.two, NULL, 0);

	return (RETURN_SUCCESS);
}