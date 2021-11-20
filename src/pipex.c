// /* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/02 12:45:25 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/11/10 16:02:05 by hyilmaz       ########   odam.nl         */
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

static int	wait_and_get_last_exit_status(int last_process_pid)
{
	int	pid;
	int	last_process_status;
	int	status;

	pid = 1;
	last_process_status = 0;
	while (pid > 0)
	{
		pid = wait(&status);
		if (pid == last_process_pid)
		{
			if (WIFEXITED(status))
				last_process_status = WEXITSTATUS(status);
		}
	}
	return (last_process_status);
}

static int	execute_commands(t_data data, int num_commands, char **envp, int *last_process_pid)
{
	int			i;
	int			read_end_pipe;

	i = 0;
	read_end_pipe = -1;
	while (i < num_commands)
	{
		if (i != num_commands - 1)
			if (wrapper_pipe(data.fds) == -1)
				return (RETURN_FAILURE);
		if (i == 0)
			first_child(&data, envp, i);
		else
			last_child(&data, envp, read_end_pipe, i, last_process_pid);
		read_end_pipe = data.fds[0];
		close(data.fds[1]);
		i++;
	}
	close(data.fds[0]);
	return (RETURN_SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	int			num_commands;
	int			last_process_pid;
	t_data		data;

	num_commands = argc - 3;
	ft_bzero(&data, sizeof(data));
	if (check_input(argc) || parse_input(&data, argc, argv, envp))
		return (RETURN_FAILURE);
	execute_commands(data, num_commands, envp, &last_process_pid);
	free_all(data, num_commands);
	return (wait_and_get_last_exit_status(last_process_pid));
}