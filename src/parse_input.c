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
			printf("SUCCESS FOUND PATH! = |%s|\n", data->path[i]);
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

static int	open_files(t_data *data, char **argv)
{
	data->file_in = open(argv[1], O_RDONLY); // file_in has to already exist
	if (data->file_in == -1)
	{
		printf("%s\n", strerror(errno));
		return (RETURN_FAILURE);
	}
	data->file_out = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (data->file_out == -1)
	{
		printf("%s\n", strerror(errno));
		return (RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
}

int	parse_input(t_data *data, char **argv, char **envp)
{
	get_path(data, envp);
	append_slash_to_path(data);
	open_files(data, argv);
	data->cmd1 = ft_split(argv[2], ' ');
	if (data->cmd1 == NULL)
		return (RETURN_FAILURE);
	get_executable(data, &data->cmd1[0]);
	printf("exec1 = %s\n", data->cmd1[0]);

	data->cmd2 = ft_split(argv[3], ' ');
	if (data->cmd2 == NULL)
		return (RETURN_FAILURE);
	get_executable(data, &data->cmd2[0]);
	printf("exec2 = %s\n", data->cmd2[0]);

	return (RETURN_SUCCESS);
}
