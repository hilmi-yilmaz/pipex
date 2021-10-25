#include <unistd.h>
#include <stdio.h>
#include <stdlib.h> //exit failure and succes macros

int	main(void)
{
	int	fds[2];
	int	ret;

	ret = pipe(fds);
	if (ret == -1)
	{
		printf("Error\n");
		return (EXIT_FAILURE);
	}

	printf("read from fd = %d\n", fds[0]);
	printf("write to  fd = %d\n", fds[1]);

	/* Write to the pipe */
	ret = write(fds[1], "1234\0", 5);
		if (ret == -1)
	{
		printf("Error while writing to pipe\n");
		return (EXIT_FAILURE);
	}

	/* Read from the pipe  and save in buff */
	char	buff[5];
	ret = read(fds[0], buff, 5);
	if (ret == -1)
	{
		printf("Error while reading from pipe\n");
		return (EXIT_FAILURE);
	}

	printf("Read from the pipe: %s\n", buff);


	return (EXIT_SUCCESS);
}