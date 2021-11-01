#include "child_process.h"

int child_one(t_data data, int *fds, char **envp)
{
		close(fds[0]);
		close(data.file_out);
		dup2(fds[1], STDOUT_FILENO);
		dup2(data.file_in, STDIN_FILENO);
		close(fds[1]);
		close(data.file_in);
		execve(data.cmd1[0], data.cmd1, envp);
        return (0);
}