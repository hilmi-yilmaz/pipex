/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/02 12:45:15 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/11/22 12:35:39 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse_input.h"

/*
** Parse the input from the command line.
** Step 1: Get the filenames.
** Step 2: Create a 3D array to store the commands and its options.
** Step 3: Loop over the command and save the data in data->commands.
*/

int	parse_input(t_data *data, int argc, char **argv, char **envp)
{	
	int	i;
	int	ret;
	int	num_commands;

	i = 0;
	ret = 0;
	num_commands = argc - 3;
	if (get_filenames(data, argc, argv))
		return (RETURN_FAILURE);
	data->commands = ft_calloc(num_commands + 1, sizeof(*data->commands));
	if (data->commands == NULL)
		return (RETURN_FAILURE);
	while (i < num_commands)
	{
		ret = get_commands(data, argv, envp, &i);
		if (ret == RETURN_SUCCESS + 2)
			continue ;
		else if (ret == RETURN_FAILURE)
			return (RETURN_FAILURE);
		i++;
	}
	return (RETURN_SUCCESS);
}
