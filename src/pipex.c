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

// static void	set_process(t_process *process, int read_from, int write_to, int file_in, int file_out)
// {
// 	process->read_from = read_from;
// 	process->write_to = write_to;
// 	process->file_in = file_in;
// 	process->file_out = file_out;
// }

int	main(int argc, char **argv, char **envp)
{
	int			fds[2];
	t_pids  	pid;
	t_data		data;
	int			status;

	ft_bzero(&data, sizeof(data));
	ft_bzero(&pid, sizeof(pid));
	//ft_memset(&process, -1, sizeof(process));
	if (check_input(argc) || parse_input(&data, argc, argv, envp))
		return (RETURN_FAILURE);
	if (pipe(fds) == -1)
	{
		perror("Error creating pipe");
		return (RETURN_FAILURE);
	}
	if (child_one(&data, fds, &pid, argv, envp))
		close_pipe_and_exit_failure(fds);
	if (child_two(&data, fds, &pid, argv, envp))
	{
		waitpid(pid.one, &status, 0);
		close_pipe_and_exit_failure(fds);
	}
	
	// if (a(&data,&pid.one,fds[0],argv[1],envp,fds[1], input_file,STDOUT_FILENO,STDIN_FILENO, 0))
	// 	close_pipe_and_exit_failure(fds);
	// if (a(&data,&pid.two,fds[1],argv[4],envp,fds[0], output_file,STDIN_FILENO,STDOUT_FILENO, 1))
	// 	close_pipe_and_exit_failure(fds);
		
	close_pipe(fds);
	waitpid(pid.one, &status, 0);
	waitpid(pid.two, &status, 0);
	return (WEXITSTATUS(status));
}
