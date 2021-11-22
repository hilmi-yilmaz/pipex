/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   processes_bonus.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/02 12:45:06 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/11/22 15:52:08 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "processes_bonus.h"

int middle_child(t_data *data, char **envp, int read_end_pipe, int i)
{
	int	pid;

	pid = wrapper_fork();
	if (pid == 0)
	{
		if (dup2(data->fds[1], STDOUT_FILENO) == -1)
			dup2_error_handling(data->fds[1], read_end_pipe);
		if (dup2(read_end_pipe, STDIN_FILENO) == -1)
			dup2_error_handling(data->fds[1], read_end_pipe);
		close(data->fds[1]);
		close(read_end_pipe);
		execve(data->commands[i][0], data->commands[i], envp);
		perror("Error with execve");
		exit(RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
}
