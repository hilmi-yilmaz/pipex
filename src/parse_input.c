/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/02 12:45:15 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/11/16 17:54:31 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse_input.h"

/* Get PATH variable from the environment and store in data->path using split 
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
** Append slash to all paths so that executable can be appended later.
 */
static int	append_slash_to_path(t_data *data)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (data->path[i] != NULL)
	{
		tmp = data->path[i];
		data->path[i] = ft_strjoin(data->path[i], "/");
		free(tmp);
		i++;
	}
	return (0);
}

/*
** Checks whether the current executable is given with a path.
** If so, checking the path.
** Else, returning executable.
*/
static int	check_given_executable_on_slashes(char *cmd)
{
	if (ft_strchr(cmd, '/') != NULL)
		return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}

// static int	handle_null_for_command(char **cmd)
// {
// 	cmd = 
// }

/*
** Loop over path, append executable to it, check whether that exists.
** If not, continue looking, else save path + executable in *cmd.
*/
static int	get_executable_with_full_path(t_data *data, char **cmd)
{
	int		i;
	char	*tmp;

	i = 0;
	if (*cmd == NULL)
	{
		*cmd = ft_strdup(data->path[0]);
		return (RETURN_SUCCESS);
	}
	tmp = NULL;
	if (check_given_executable_on_slashes(*cmd))
		return (RETURN_SUCCESS);
	while (data->path[i] != NULL)
	{
		tmp = data->path[i];
		data->path[i] = ft_strjoin(data->path[i], *cmd);
		if (data->path[i] == NULL)
		{
			perror("Error with malloc");
			return (MALLOC_FAILURE);
		}
		if (access(data->path[i], F_OK) == 0)
		{
			free(*cmd);
			*cmd = ft_strdup(data->path[i]); // check malloc
			free(data->path[i]);
			data->path[i] = tmp;
			return (RETURN_SUCCESS);
		}
		free(data->path[i]);
		data->path[i] = tmp;
		i++;
	}
	return (RETURN_FAILURE);
}

static char	**handle_input_empty_string(t_data *data, int i)
{
	char	**single_command;
	
	single_command = ft_calloc(2, sizeof(*data->commands[i]));
	single_command[0] = ft_strdup("/");
	return (single_command);
}

/*
** Parse all input:
** 1. Find path variable in environment and append slashes to it.
** 2. Get the commands and append correct path to it.
*/
int	parse_input(t_data *data, int argc, char **argv, char **envp)
{
	int	i;
	int	num_commands;
	
	i = 0;
	num_commands = argc - 3;
	if (get_path_from_environment(data, envp) || \
		append_slash_to_path(data))
		return (RETURN_FAILURE);
	data->commands = ft_calloc(num_commands + 1, sizeof(*data->commands));
	if (data->commands == NULL)
		return (RETURN_FAILURE);
	data->commands[num_commands] = NULL; // not needed with calloc
	while (i < num_commands)
	{
		if (argv[i + 2][0] != '\0')
			data->commands[i] = ft_split(argv[i + 2], ' ');
		else
			data->commands[i] = handle_input_empty_string(data, i);
		if (data->commands[i] == NULL)
			return (RETURN_FAILURE);
		if (get_executable_with_full_path(data, &data->commands[i][0]) == MALLOC_FAILURE)
			return (RETURN_FAILURE);
		i++;
	}
	data->file_in_name = ft_strdup(argv[1]);
	data->file_out_name = ft_strdup(argv[argc - 1]);
	return (RETURN_SUCCESS);
}
