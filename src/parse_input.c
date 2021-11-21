/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/02 12:45:15 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/11/21 21:05:05 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse_input.h"

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

static int	get_commands_from_argv(t_data *data, char **argv, int i)
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

/*
** Checks whether the current executable is given with a path.
** If so, checking the path.
** Else, returning executable.
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
** Loop over path, append executable to it, check whether that exists.
** If not, continue looking, else save path + executable in *cmd.
*/
static int	get_executable_with_full_path(t_data *data, char **cmd)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (data->path[i] != NULL)
	{
		tmp = data->path[i];
		data->path[i] = ft_strjoin(data->path[i], *cmd);
		if (data->path[i] == NULL)
		{
			perror("Error with malloc");
			return (MALLOC_FAILURE);
		}
		if (access(data->path[i], X_OK) == 0)
		{
			free(*cmd);
			*cmd = ft_strdup(data->path[i]);
			if (*cmd == NULL)
			{
				perror("Error with malloc");
				return (RETURN_FAILURE);
			}
			free(data->path[i]);
			data->path[i] = tmp;
			return (RETURN_SUCCESS);
		}
		free(data->path[i]);
		data->path[i] = tmp;
		i++;
	}
	return (RETURN_SUCCESS);
}

static int	get_commands(t_data *data, char **argv, char **envp, int *i)
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
			ft_putstr_fd("Error\nNo PATH variable in environment.\n", STDOUT_FILENO);
			return (RETURN_FAILURE);
		}
	}
	if (append_slash_in_front_of_command(&data->commands[*i][0]))
		return (RETURN_FAILURE);
	if (get_executable_with_full_path(data, &data->commands[*i][0]))
		return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}

/*
** Parse the input from the command line.
** Step 1: Get the filenames.
** Step 2: Create a 3D array to store the commands and its options.
** Step 3: Check given executable on slashes.
** Step 4: Append slashes in front of commands.
** Step 5: Get the PATH variable from the environment.
** Step 6: Loop over the PATH variable and get the correct path for the command.
** If input is empty string "", then command is like this ["/", NULL].
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
