/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/02 12:45:46 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/11/15 17:27:06 by hyilmaz       ########   odam.nl         */
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

void	print_str_array(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		printf("%s ", str[i]);
		i++;
	}
	printf("\n");
}

void	print_data(t_data data)
{
	int i;
	
	i = 0;
	printf("---------------------------------\n");
	printf("Input  file descripter = %s\n", data.file_in_name);
	printf("Output file descriptor = %s\n", data.file_out_name);

	while (data.commands[i] != NULL)
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