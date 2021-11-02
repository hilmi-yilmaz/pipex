#include "child_process.h"

// static int	wrapper_strjoin(char *path, char **cmd)
// {
// 	char	*tmp;

// 	tmp = *cmd;
// 	*cmd = ft_strjoin(path, *cmd);
// 	free(tmp);
// 	if (cmd == NULL)
// 		return (RETURN_FAILURE);
// 	return (RETURN_SUCCESS);
// }

// static int	append_slash(char **path)
// {
// 	int		len;
// 	char 	*tmp;

// 	printf("entered append_slash\n");
// 	tmp = *path;
// 	len = ft_strlen(*path);
// 	*path = malloc(sizeof(**path) * (len + 2));
// 	printf("path1 = %s\n", *path);
// 	ft_strlcpy(*path, tmp, len);
// 	printf("path2 = %s\n", *path);
// 	*path[len + 1] = '/';
// 	*path[len + 2] = '\0';
// 	printf("path3 = %s\n", *path);
// 	free(tmp);
// 	printf("path4 = %s\n", *path);
// 	return (RETURN_SUCCESS);

// }

int child_one(t_data *data, int *fds, char **envp)
{
	close(fds[0]);
	close(data->file_out);
	dup2(fds[1], STDOUT_FILENO);
	dup2(data->file_in, STDIN_FILENO);
	close(fds[1]);
	close(data->file_in);
	execve(data->cmd1[0], data->cmd1, envp);
	return (RETURN_SUCCESS);
}

int	child_two(t_data *data, int *fds, char **envp)
{
	close(fds[1]);
	close(data->file_in);
	dup2(fds[0], STDIN_FILENO);
	dup2(data->file_out, STDOUT_FILENO);
	close(fds[0]);
	close(data->file_out);
	execve(data->cmd2[0], data->cmd2, envp);
	return (RETURN_SUCCESS);
}
