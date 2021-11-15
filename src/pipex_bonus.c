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
	if (argc < 5)
    {
		printf("Error\nWrong amount of arguments. Run as: ./pipex file_in cmd1 cmd2 file_out\n");
		return (RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
}

static int	wait_and_get_last_exit_status(int last_process_pid)
{
	int	pid;
	int	status;
	int	last_process_status;

	pid = 1;
	last_process_status = 0;
	printf("last_process_pid = %d\n", last_process_pid);
	while (pid > 0)
	{
		pid = wait(&status);
		if (pid == -1)
		{
			perror("Error waiting for process");
			exit(RETURN_FAILURE);
		}
		if (pid == last_process_pid)
		{
			printf("last process pid = %d\n", pid);
			if (WIFEXITED(status))
				last_process_status = WEXITSTATUS(status);
		}
	}
	return (last_process_status);
}

// static void	close_pipe(int *fds)
// {
// 	close(fds[0]);
// 	close(fds[1]);
// }

// static void	close_pipe_and_exit_failure(int *fds)
// {
// 	close_pipe(fds);
// 	exit(RETURN_FAILURE);
// }

int	main(int argc, char **argv, char **envp)
{
	int			i;
	int			num_commands;
	int			read_end_pipe;
	int			last_process_pid;
	int			last_process_status;
	t_data		data;
	// int			status;

	i = 0;
	num_commands = argc - 3;
	read_end_pipe = -1;
	ft_bzero(&data, sizeof(data));
	if (check_input(argc) || parse_input(&data, argc, argv, envp))
		return (RETURN_FAILURE);
	while (i < num_commands)
	{
		// create pipe
		if (pipe(data.fds) == -1)
		{
			perror("Error creating pipe");
			return (RETURN_FAILURE);
		}
		if (i == 0)
			first_child(&data, envp, i);
		else if (i == num_commands - 1)
			last_child(&data, envp, read_end_pipe, i, &last_process_pid);
		else
			middle_child(&data, envp, read_end_pipe, i);
		read_end_pipe = data.fds[0];
		close(data.fds[1]);
		i++;
	}
	close(data.fds[0]);
	// int	pid;
	// int	last_status;
	// while ((pid = wait(&status)) > 0)
	// {
	// 	if (pid == last_pid)
	// 		last_status = status;
	// }
	//printf("pid1 = %d\n", pid1);
	last_process_status = wait_and_get_last_exit_status(last_process_pid);
	return (last_process_status);
}