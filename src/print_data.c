/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_data.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/21 16:37:36 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/11/21 16:39:34 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "print_data.h"

static void	print_str_array(char **str)
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
	printf("\n");
}