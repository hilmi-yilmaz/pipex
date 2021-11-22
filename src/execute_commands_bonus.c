/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_commands_bonus.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/22 14:47:12 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/11/22 15:54:45 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute_commands_bonus.h"

int	execute_commands(t_data data, int num_commands, char **envp, \
							int *last_process_pid)
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
		else if (i == num_commands - 1)
			last_child(&data, envp, i, last_process_pid);
		else
			middle_child(&data, envp, read_end_pipe, i);
		read_end_pipe = data.fds[0];
		close(data.fds[1]);
		i++;
	}
	return (RETURN_SUCCESS);
}