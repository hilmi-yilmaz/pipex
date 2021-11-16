/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/02 12:45:46 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/11/16 17:49:21 by hyilmaz       ########   odam.nl         */
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

void	free_data(t_data data, int num_commands)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	free(data.file_in_name);
	free(data.file_out_name);
	while (i < num_commands)
	{
		if (data.commands[i] == NULL)
		{
			i++;
			continue ;
		}
		while (data.commands[i][j] != NULL)
		{
			free(data.commands[i][j]);
			j++;
		}
		j = 0;
		i++;
	}
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