/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/02 12:45:15 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/11/10 13:25:08 by hyilmaz       ########   odam.nl         */
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
	{
		if (access(cmd, F_OK) == 0)
			return (RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
}

/*
** Loop over path, append executable to it, check whether that exists.
** If not, continue looking, else save path + executable in *cmd.
*/
static int	get_executable(t_data *data, char **cmd)
{
	int		i;
	char	*tmp;

	i = 0;
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
			*cmd = ft_strdup(data->path[i]);
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
	data->commands = malloc(sizeof(*data->commands) * (num_commands + 1));
	if (data->commands == NULL)
		return (RETURN_FAILURE);
	data->commands[num_commands] = NULL;
	while (i < num_commands)
	{
		data->commands[i] = ft_split(argv[i + 2], ' ');
		if (data->commands[i] == NULL)
			return (RETURN_FAILURE);
		if (get_executable(data, &data->commands[i][0]) == MALLOC_FAILURE)
			return (RETURN_FAILURE);
		i++;
	}
	// data->cmd1 = ft_split(argv[2], ' ');
	// if (data->cmd1 == NULL)
	// 	return (RETURN_FAILURE);
	// if (get_executable(data, &data->cmd1[0]) == MALLOC_FAILURE)
	// 	return (RETURN_FAILURE);

	// data->cmd2 = ft_split(argv[3], ' ');
	// if (data->cmd2 == NULL)
	// 	return (RETURN_FAILURE);
	// if (get_executable(data, &data->cmd2[0]) == MALLOC_FAILURE)
	// 	return (RETURN_FAILURE);

	return (RETURN_SUCCESS);
}
