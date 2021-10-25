#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

int main(void)
{
	int		fds[2];
	char	buff[5];
	pid_t	pid;
	int		ret;
	int		status;

	ret = pipe(fds);
	if (ret == -1)
	{
		printf("%s\n", strerror(errno));
		return (EXIT_FAILURE);
	}

	/* Fork process */
	pid = fork();

	/* Child process */
	if (pid == 0)
	{
		close(fds[0]);
		write(fds[1], "1234\0", 5);
		printf("Write to pipe\n");
		exit(EXIT_SUCCESS);
	}

	/* Main process */
	if (pid > 0)
	{
		ret = waitpid(pid, &status, 0);
		if (ret != pid)
			printf("Error\n");
		close(fds[1]);
		read(fds[0], buff, 5);
		printf("read from pipe\n");
		close(fds[0]);

		printf("Main process received PIN as %s\n", buff);
	}

	/* Error forking */
	if (pid < 0)
	{
		printf("Error while forking process\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
	
}