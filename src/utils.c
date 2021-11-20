/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/02 12:45:46 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/11/17 15:13:38 by hyilmaz       ########   odam.nl         */
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

void	print_str_array(char **str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return ;
	while (str[i] != NULL)
	{
		printf("%s ", str[i]);
		i++;
	}
	printf("\n");
}

void	print_data(t_data data, int num_commands)
{
	int i;
	
	i = 0;
	printf("---------------------------------\n");
	printf("Input  file descripter = %s\n", data.file_in_name);
	printf("Output file descriptor = %s\n", data.file_out_name);

	while (i < num_commands)
	{
		print_str_array(data.commands[i]);
		i++;
	}

	// printf("\npath=\n");
	// i = 0;
	// while (data.path[i] != NULL)
	// {
	// 	printf("%s\n", data.path[i]);
	// 	i++;
	// }
	printf("\n");
}