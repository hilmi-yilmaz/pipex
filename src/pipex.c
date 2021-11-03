/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/02 12:45:25 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/11/03 16:10:34 by hyilmaz       ########   odam.nl         */
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

int main(int argc, char **argv, char **envp)
{
	int		fds[2];
	t_pids  pid;
	t_data	data;
	int		status;

	ft_bzero(&data, sizeof(data));
	ft_bzero(&pid, sizeof(pid));
	if (check_input(argc) || parse_input(&data, argv, envp))
		return (RETURN_FAILURE);
	if (pipe(fds) == -1)
	{
		perror("Error creating pipe:");
		return (RETURN_FAILURE);
	}
    // if (child_one(&data, fds, &pid, envp) || child_two(&data, fds, &pid, envp))
	// 	return (RETURN_FAILURE);
	child_one(&data, fds, &pid, argv, envp);
	child_two(&data, fds, &pid, argv, envp);
	close(fds[0]);
	close(fds[1]);
	waitpid(pid.one, &status, 0);
	waitpid(pid.two, &status, 0);
	return (WEXITSTATUS(status));
}
