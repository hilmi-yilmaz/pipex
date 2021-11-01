#include "parse_input.h"

static int	get_path(t_data *data, char **envp)
{
	int i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			data->path = ft_split(envp[i] + 5, ':');
			if (data->path == NULL)
				return (RETURN_FAILURE);
			break ;
		}
		i++;
	}
	return (RETURN_SUCCESS);
}

// static int	append_path_to_executable(t_data *data)
// {

// }

int	parse_input(t_data *data, char **argv, char **envp)
{
	int	ret;

	ret = get_path(data, envp);
	data->file_in = open(argv[1], O_RDONLY); // file_in has to already exist
	if (data->file_in == -1)
	{
		printf("%s\n", strerror(errno));
		return (4);
	}
	data->file_out = open(argv[4], O_CREAT | O_WRONLY, 0666);
	data->cmd1 = ft_split(argv[2], ' ');
	if (data->cmd1 == NULL)
		return (RETURN_FAILURE);
	append_path_to_executable(data);

	data->cmd2 = ft_split(argv[3], ' ');
	if (data->cmd2 == NULL)
		return (RETURN_FAILURE);


	return (RETURN_SUCCESS);
}