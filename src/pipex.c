/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/22 13:49:36 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/11/22 14:56:56 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
** Wait for all children to finish.
** Return the exit status of the last process.
*/

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

/*
** Pipex program which replicates the behaviour of pipes in bash.
** Run as: 			./pipex file_in cmd1 cmd2 file_out
** Equivalent to:	< file_in cmd1 | cmd2 > file_out
** in Bash.
*/

int	main(int argc, char **argv, char **envp)
{
	int			num_commands;
	int			last_process_pid;
	t_data		data;

	num_commands = argc - 3;
	ft_bzero(&data, sizeof(data));
	if (check_input(argc) || parse_input(&data, argc, argv, envp))
	{
		free_all(data, num_commands);
		return (RETURN_FAILURE);
	}
	execute_commands(data, num_commands, envp, &last_process_pid);
	free_all(data, num_commands);
	return (wait_and_get_last_exit_status(last_process_pid));
}
