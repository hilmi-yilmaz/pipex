/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   processes.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/02 12:45:06 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/11/15 18:34:53 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "processes.h"

static void	dup2_error_handling(int	file_1, int file_2)
{
	perror("Error with dup2");
	close(file_1);
	close(file_2);
	exit(RETURN_FAILURE);
}

static int	wrapper_fork()
{
	int	pid;
	
	pid = fork();
	if (pid < 0)
	{
		perror("Error forking child");
		return (RETURN_FAILURE);
	}
	return (pid);
}

/*
** still need to close a descriptor here
*/
// int	input_file(char *argv)
// {
// 	int file = open(argv, O_RDONLY);
// 	if (file == -1)
// 	{
// 		perror("Error opening input file");
// 		exit(RETURN_FAILURE);
// 	}
// 	return (file);
// }

// int	output_file(char *argv)
// {
// 	int file = open(argv, O_CREAT | O_WRONLY | O_TRUNC, 0666);
// 	if (file == -1)
// 	{
// 		perror("Error opening output file");
// 		exit(RETURN_FAILURE);
// 	}
// 	return (file);
// }

int middle_child(t_data *data, char **envp, int read_end_pipe, int i)
{
	int	pid;

	pid = wrapper_fork();
	if (pid == 0)
	{
		if (dup2(data->fds[1], STDOUT_FILENO) == -1)
		{
			printf("HAndle this error.\n");
		}
		if (dup2(read_end_pipe, STDIN_FILENO) == -1)
		{
			printf("HAndle this error.\n");
		}
		close(data->fds[1]);
		close(read_end_pipe);
		execve(data->commands[i][0], data->commands[i], envp);
		perror("Error with execve");
		exit(RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
}

int first_child(t_data *data, char **envp, int i)
{
	int	pid;
	int	file_in_fd;
	
	pid = wrapper_fork();
	if (pid == 0)
	{
		close(data->fds[0]);
		file_in_fd = open(data->file_in_name, O_RDONLY);
		if (file_in_fd == -1)
		{
			perror("Error opening input file");
			close(data->fds[1]);
			exit(RETURN_FAILURE);
		}
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
	return (RETURN_SUCCESS); //parent
}

/*
** The last child process. Executes the second command.
*/
int last_child(t_data *data, char **envp, int read_end_pipe, int i, int *last_pid)
{
	int	file_out_fd;
	
	*last_pid = wrapper_fork();
	if (*last_pid == 0)
	{
		close(data->fds[1]);
		file_out_fd = open(data->file_out_name, O_CREAT | O_WRONLY | O_TRUNC, 0666);
		if (file_out_fd == -1)
		{
			perror("Error opening output file");
			close(data->fds[0]);
			exit(RETURN_FAILURE);
		}
		if (dup2(file_out_fd, STDOUT_FILENO) == -1)
			dup2_error_handling(file_out_fd, data->fds[0]);
		if (dup2(read_end_pipe, STDIN_FILENO) == -1)
			dup2_error_handling(file_out_fd, data->fds[0]);
		close(data->fds[0]);
		close(read_end_pipe);
		close(file_out_fd);
		execve(data->commands[i][0], data->commands[i], envp);
		perror("Error with execve");
		exit(RETURN_FAILURE);
	}
	return (RETURN_SUCCESS); // parent
}
