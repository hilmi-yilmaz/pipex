/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/02 12:45:46 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/11/21 16:37:26 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	wrapper_close(int fd)
{
	if (close(fd) == 0)
		return (RETURN_SUCCESS);
	perror("Error with close");
	return (RETURN_FAILURE);
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