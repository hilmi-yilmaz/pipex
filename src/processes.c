/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   processes.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/02 12:45:06 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/11/23 12:38:55 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "processes.h"

/*
** Open the input file.
*/

static int	open_input_file(t_data *data)
{
	int	file_in_fd;

	file_in_fd = open(data->file_in_name, O_RDONLY);
	if (file_in_fd == -1)
	{
		perror("Error opening input file");
		close(data->fds[1]);
		exit(RETURN_FAILURE);
	}
	return (file_in_fd);
}

/*
** Open the output file.
*/

static int	open_output_file(t_data *data)
{
	int	file_out_fd;

	file_out_fd = open(data->file_out_name, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (file_out_fd == -1)
	{
		perror("Error opening output file");
		close(data->fds[0]);
		exit(RETURN_FAILURE);
	}
	return (file_out_fd);
}

/*
** First child process. Executes first command.
** Open the input file and reads from it.
*/

int	first_child(t_data *data, char **envp, int i)
{
	int	pid;
	int	file_in_fd;

	pid = wrapper_fork();
	if (pid == 0)
	{
		close(data->fds[0]);
		file_in_fd = open_input_file(data);
		if (dup2(data->fds[1], STDOUT_FILENO) == -1)
			dup2_error_handling(file_in_fd, data->fds[1]);
		if (dup2(file_in_fd, STDIN_FILENO) == -1)
			dup2_error_handling(file_in_fd, data->fds[1]);
		close(data->fds[1]);
		close(file_in_fd);
		execve(data->commands[i][0], data->commands[i], envp);
		perror("Error with execve");
		exit(RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
}

/*
** The last child process. Executes last command.
*/

int	last_child(t_data *data, char **envp, int i, int *last_pid)
{
	int	file_out_fd;

	*last_pid = wrapper_fork();
	if (*last_pid == 0)
	{
		file_out_fd = open_output_file(data);
		if (dup2(file_out_fd, STDOUT_FILENO) == -1)
			dup2_error_handling(file_out_fd, data->fds[0]);
		if (dup2(data->fds[0], STDIN_FILENO) == -1)
			dup2_error_handling(file_out_fd, data->fds[0]);
		close(data->fds[0]);
		close(file_out_fd);
		execve(data->commands[i][0], data->commands[i], envp);
		perror("Error with execve");
		exit(RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
}
