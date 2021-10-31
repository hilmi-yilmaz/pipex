#ifndef DATA_H
# define DATA_H

/* Macros */
# define RETURN_FAILURE -1
# define RETURN_SUCCESS 0

/* Data structures */
typedef struct s_data
{
	int		file_in;
	int		file_out;
	char	**cmd1;
	char	**cmd2;
}				t_data;

#endif