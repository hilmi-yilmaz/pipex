/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/02 12:45:46 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/11/23 12:37:18 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	wrapper_fork(void)
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

int	wrapper_pipe(int *fds)
{
	if (pipe(fds) == -1)
	{
		perror("Error creating pipe");
		return (RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
}

/*
** Error handling when dup2 fails.
*/

void	dup2_error_handling(int file_1, int file_2)
{
	perror("Error with dup2");
	close(file_1);
	close(file_2);
	exit(RETURN_FAILURE);
}

/*
** Checks whether str consists of all the same characters. 
** Returns 0 if so, else 1.
*/

int	str_all_same_chars(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c)
			return (RETURN_FAILURE);
		i++;
	}
	return (RETURN_SUCCESS);
}
