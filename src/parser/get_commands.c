/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_commands.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/22 11:53:40 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/11/22 12:26:57 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_commands.h"

/*
** Checks whether the current executable is given with a path.
*/

static int	check_given_executable_on_slashes(char *cmd)
{
	if (cmd == NULL)
		return (RETURN_SUCCESS);
	if (ft_strchr(cmd, '/') != NULL)
		return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}

/* 
** Get PATH variable from the environment and store in data->path using split.
** If no PATH variable found, return errorcode.
*/

static int	get_path_from_environment(t_data *data, char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			data->path = ft_split(envp[i] + 5, ':');
			if (data->path == NULL)
				return (RETURN_FAILURE);
			return (RETURN_SUCCESS);
		}
		i++;
	}
	return (RETURN_FAILURE);
}

/*
** Append slash in front of the command.
*/

static int	append_slash_in_front_of_command(char **command)
{
	char	*tmp;

	tmp = *command;
	*command = ft_strjoin("/", *command);
	if (command == NULL)
	{
		perror("Error with malloc");
		return (RETURN_FAILURE);
	}
	free(tmp);
	return (RETURN_SUCCESS);
}

/*
** Get the commands from the command line.
** Step 1: Get the commands from argv.
** Step 2: Check given executable on slashes.
** Step 3: If no slashes, get the PATH variable from the environment.
** Step 4: Append slashes in front of commands.
** Step 5: Loop over PATH variable and get the correct path for the command.
** If input is empty string "", then command is like this ["/", NULL].
*/

int	get_commands(t_data *data, char **argv, char **envp, int *i)
{
	if (get_commands_from_argv(data, argv, *i))
		return (RETURN_FAILURE);
	if (check_given_executable_on_slashes(data->commands[*i][0]))
	{
		*i = *i + 1;
		return (RETURN_SUCCESS + 2);
	}
	if (data->path == NULL)
	{
		if (get_path_from_environment(data, envp))
		{
			ft_putstr_fd("Error\nNo PATH variable in environment.\n", \
							STDOUT_FILENO);
			return (RETURN_FAILURE);
		}
	}
	if (append_slash_in_front_of_command(&data->commands[*i][0]))
		return (RETURN_FAILURE);
	if (get_executable_with_full_path(data, &data->commands[*i][0]))
		return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}
