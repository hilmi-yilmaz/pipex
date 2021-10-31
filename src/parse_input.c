#include "parse_input.h"

// static int	count_words(char *str, char sep)
// {
// 	int	i;
// 	int	count;

// 	i = 0;
// 	count = 0;
// 	while (str[i] != '\0')
// 	{
// 		if (str[i] != sep && (str[i + 1] == sep || str[i + 1] == '\0'))
// 			count++;
// 		i++;
// 	}
// 	return (count);
// }

int	parse_input(char **argv, t_data *data)
{
	data->file1 = argv[1];
	data->file2 = argv[4];
	data->cmd1 = ft_split(argv[2], ' ');
	if (data->cmd1 == NULL)
		return (RETURN_FAILURE);
	data->cmd2 = ft_split(argv[3], ' ');
	if (data->cmd2 == NULL)
		return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}