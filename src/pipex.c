/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/02 12:45:25 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/11/09 11:01:47 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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

static void	close_pipe(int *fds)
{
	close(fds[0]);
	close(fds[1]);
}

static void	close_pipe_and_exit_failure(int *fds)
{
	close_pipe(fds);
	exit(RETURN_FAILURE);
}

int	main(int argc, char **argv, char **envp)
{
	int		fds[2];
	t_pids  pid;
	t_data	data;
	int		status;

	ft_bzero(&data, sizeof(data));
	ft_bzero(&pid, sizeof(pid));
	if (check_input(argc) || parse_input(&data, argv, envp))
		return (RETURN_FAILURE);
	if (pipe(fds) == -1)
	{
		perror("Error creating pipe:");
		return (RETURN_FAILURE);
	}
	if (child_one(&data, fds, &pid, argv, envp))
		close_pipe_and_exit_failure(fds);
	if (child_two(&data, fds, &pid, argv, envp))
	{
		waitpid(pid.one, &status, 0);
		close_pipe_and_exit_failure(fds);
	}
	close_pipe(fds);
	waitpid(pid.one, &status, 0);
	waitpid(pid.two, &status, 0);
	return (WEXITSTATUS(status));
}
