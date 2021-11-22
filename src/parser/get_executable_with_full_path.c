/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_executable_with_full_path.c                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/22 12:03:33 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/11/22 12:32:13 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_executable_with_full_path.h"

/*
** Helper function for get_executable_with_full_path.
** If the command is found through appending a path, this function executes
** and fills the command in *cmd.
*/

static int	found_command(t_data *data, char **cmd, char *tmp, int i)
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

/*
** Loop over path, append executable to it, check whether that exists.
** If not, continue looking, else save path + executable in *cmd.
*/

int	get_executable_with_full_path(t_data *data, char **cmd)
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
			if (found_command(data, cmd, tmp, i))
				return (RETURN_FAILURE);
			return (RETURN_SUCCESS);
		}
		free(data->path[i]);
		data->path[i] = tmp;
		i++;
	}
	return (RETURN_SUCCESS);
}
