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

// static void free_str_arr(char **str)
// {
//     int i;

//     i = 0;
//     while (str[i] != NULL)
//     {
//         free(str[i]);
//         i++;
//     }
//     free(str);
// }

// static void free_data(t_data data)
// {
//     free_str_arr(data.cmd1);
//     free_str_arr(data.cmd2);
//     free_str_arr(data.path);
// }

int main(int argc, char **argv, char **envp)
{
	int		fds[2];
	t_pids  pid;
	t_data	data;

	ft_bzero(&data, sizeof(data));
	if (check_input(argc) || parse_input(&data, argv, envp))
		return (RETURN_FAILURE);
	
	if (pipe(fds) == -1)
	{
		printf("Error creating pipe: %s\n", strerror(errno));
		return (-1);
	}
	pid.one = fork();
	if (pid.one < 0)
	{
		printf("Error forking process (child 1): %s\n", strerror(errno));
		return (RETURN_FAILURE);
	}
	/* Child process 1: write to pipe */
	if (pid.one == 0)
        child_one(&data, fds, envp);
	else
	{
		wait(NULL);
		close(fds[1]);
		close(data.file_in);
		dup2(fds[0], STDIN_FILENO);
		dup2(data.file_out, STDOUT_FILENO);
		close(fds[0]);
		close(data.file_out);
		execve(data.cmd2[0], data.cmd2, envp);
	}

	return (RETURN_SUCCESS);
}
