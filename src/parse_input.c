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

int	parse_input(char **argv, t_data *data)
{
	int	ret;

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