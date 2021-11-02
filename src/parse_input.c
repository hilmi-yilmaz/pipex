/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/02 12:45:15 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/11/02 12:45:18 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse_input.h"

/* 
** Open files given as input.
** file_in is opened (it should already exist).
** file_out is created or truncated if it already exists.
*/
static int	open_files(t_data *data, char **argv)
{
	data->file_in = open(argv[1], O_RDONLY);
	if (data->file_in == -1)
	{
		perror("Error opening input file");
		return (RETURN_FAILURE);
	}
	data->file_out = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (data->file_out == -1)
	{
		perror("Error opening output file");
		return (RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
}

/* Get the PATH variable from the environment and store in data->path using split 
** If no PATH variable found, return errorcode.
*/
static int	get_path_from_environment(t_data *data, char **envp)
{
	int i = 0;
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
** Loop over path, append executable to it, check whether that exists.
** If not, continue looking, else save path + executable in *cmd.
 */
static int	get_executable(t_data *data, char **cmd)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (data->path[i] != NULL)
	{
		tmp = data->path[i];
		data->path[i] = ft_strjoin(data->path[i], *cmd);
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
	//printf("Could not find executable: %s\n", *cmd);
	perror("Error finding executable");
	return (RETURN_FAILURE);
}

/*
** Parse all input:
** 1. Open files.
** 2. Find path variable in environment and append slashes to it.
** 3. Get the commands and append correct path to it.
 */
int	parse_input(t_data *data, char **argv, char **envp)
{
	if (open_files(data, argv) || get_path_from_environment(data, envp) || \
		append_slash_to_path(data))
		return (RETURN_FAILURE);
	data->cmd1 = ft_split(argv[2], ' ');
	if (data->cmd1 == NULL)
		return (RETURN_FAILURE);
	if (get_executable(data, &data->cmd1[0]))
		return (RETURN_FAILURE);
	data->cmd2 = ft_split(argv[3], ' ');
	if (data->cmd2 == NULL)
		return (RETURN_FAILURE);
	if (get_executable(data, &data->cmd2[0]))
		return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}
