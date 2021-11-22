/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_commands_from_argv.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/22 12:08:50 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/11/22 12:31:54 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_commands_from_argv.h"

/*
** Returns a 2D array containing: [str, NULL] 
** to handle exceptional inputs like only-spaces-string
** or empty-string.
*/

static char	**handle_exceptional_inputs(char *str)
{
	char	**single_command;

	single_command = ft_calloc(2, sizeof(*single_command));
	if (single_command == NULL)
		return (NULL);
	single_command[0] = ft_strdup(str);
	if (single_command[0] == NULL)
		return (NULL);
	return (single_command);
}

/*
** Get the commands from the command line and save in 2D array.
** If input is empty string "", then command is like this ["/", NULL].
*/

int	get_commands_from_argv(t_data *data, char **argv, int i)
{
	if (argv[i + 2][0] == '\0')
		data->commands[i] = handle_exceptional_inputs("/");
	else if (str_all_same_chars(argv[i + 2], ' ') == 0)
		data->commands[i] = handle_exceptional_inputs(argv[i + 2]);
	else
		data->commands[i] = ft_split(argv[i + 2], ' ');
	if (data->commands[i] == NULL)
	{
		perror("Error with malloc");
		return (RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
}
