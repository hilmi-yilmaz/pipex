/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_commands.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/22 14:47:12 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/11/23 12:34:06 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute_commands.h"

int	execute_commands(t_data data, int num_commands, char **envp, \
							int *last_process_pid)
{
	int			i;

	i = 0;
	while (i < num_commands)
	{
		if (i != num_commands - 1)
			if (wrapper_pipe(data.fds) == -1)
				return (RETURN_FAILURE);
		if (i == 0)
			first_child(&data, envp, i);
		else
			last_child(&data, envp, i, last_process_pid);
		close(data.fds[1]);
		i++;
	}
	close(data.fds[0]);
	return (RETURN_SUCCESS);
}
