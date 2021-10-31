#include "utils.h"

void	print_data(t_data data)
{
	int i;
	
	i = 0;
	printf("Input  file descripter = %d\n", data.file_in);
	printf("Output file descriptor = %d\n", data.file_out);
	printf("cmd1 = ");
	while (data.cmd1[i] != NULL)
	{
		printf("%s ", data.cmd1[i]);
		i++;
	}
	printf("\n");
	printf("cmd2 = ");
	i = 0;
	while (data.cmd2[i] != NULL)
	{
		printf("%s ", data.cmd2[i]);
		i++;
	}
	printf("\n");
}