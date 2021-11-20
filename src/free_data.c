#include "free_data.h"

static void	free_file_names(t_data data)
{
	free(data.file_in_name);
	free(data.file_out_name);
}

static void	free_commands(t_data data, int num_commands)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < num_commands)
	{
		while (data.commands[i][j] != NULL)
		{
			free(data.commands[i][j]);
			j++;
		}
		free(data.commands[i]);
		j = 0;
		i++;
	}
	free(data.commands);
}

static void	free_path(t_data data)
{
	int	i;

	i = 0;
	if (data.path == NULL)
		return ;
	while (data.path[i] != NULL)
	{
		free(data.path[i]);
		i++;
	}
	free(data.path);
}

void	free_all(t_data data, int num_commands)
{
	free_file_names(data);
	free_commands(data, num_commands);
	free_path(data);
}