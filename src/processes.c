/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   processes.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/02 12:45:06 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/11/06 14:00:16 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "processes.h"

int child_one(t_data *data, int *fds, t_pids *pid, char **argv, char **envp)
{
	pid->one = fork();
	if (pid->one < 0)
	{
		perror("Error forking child one.\n");
		return (RETURN_FAILURE);
	}
	else if (pid->one == 0)
	{
		close(fds[0]);
		data->file_in = open(argv[1], O_RDONLY);
		if (data->file_in == -1)
		{
			perror("Error opening input file");
			close(fds[1]);
			exit(RETURN_FAILURE);
		}
		dup2(fds[1], STDOUT_FILENO);
		dup2(data->file_in, STDIN_FILENO);
		close(fds[1]);
		close(data->file_in);
		execve(data->cmd1[0], data->cmd1, envp);
		perror("Error with execve");
		exit(RETURN_FAILURE);
	}
	return (RETURN_SUCCESS); //parent
}

int child_two(t_data *data, int *fds, t_pids *pid, char **argv, char **envp)
{
	pid->two = fork();
	if (pid->two < 0)
	{
		perror("Error forking child one.\n");
		return (RETURN_FAILURE);
	}
	else if (pid->two == 0)
	{
		close(fds[1]);
		data->file_out = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0666);
		if (data->file_out == -1)
		{
			perror("Error opening output file");
			close(fds[0]);
			exit(RETURN_FAILURE);
		}
		dup2(fds[0], STDIN_FILENO);
		dup2(data->file_out, STDOUT_FILENO);
		close(fds[0]);
		close(data->file_out);
		execve(data->cmd2[0], data->cmd2, envp);
		perror("Error with execve");
		exit(RETURN_FAILURE);
	}
	return (RETURN_SUCCESS); // parent
}
