#include "parse_input.h"

static int	wrapper_strjoin(char *path, char **cmd)
{
	char	*tmp;

	tmp = *cmd;
	*cmd = ft_strjoin(path, *cmd);
	free(tmp);
	if (cmd == NULL)
		return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}

static int	find_executable_path(t_data *data, char **envp)
{
	int i = 0;
	while (envp[i] != NULL)
	{
		printf("envp[%d] = %s\n", i, envp[i]);
		if (envp[i][0] == 'P' && envp[i][1] == 'A' && envp[i][2] == 'T' && \
			envp[i][3] == 'H' && envp[i][4] == '=')
		{
			data->path = ft_split(envp[i] + 5, ':');
			if (data->path == NULL)
				return (RETURN_FAILURE);
		}
		i++;
	}
	return (RETURN_SUCCESS);
}

int	parse_input(t_data *data, char **argv, char **envp)
{
	int	ret;

	find_executable_path(data, envp);
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
	ret = wrapper_strjoin("/usr/bin/", &data->cmd1[0]);
	if (ret == RETURN_FAILURE)
		return (RETURN_FAILURE);

	data->cmd2 = ft_split(argv[3], ' ');
	if (data->cmd2 == NULL)
		return (RETURN_FAILURE);
	ret = wrapper_strjoin("/usr/bin/", &data->cmd2[0]);
	if (ret == RETURN_FAILURE)
		return (RETURN_FAILURE);

	return (RETURN_SUCCESS);
}