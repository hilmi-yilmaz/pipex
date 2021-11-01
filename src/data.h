#ifndef DATA_H
# define DATA_H

/* System headers */
# include <sys/types.h>

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
	char	**path;
}				t_data;

typedef struct	s_pids
{
	pid_t	one;
	pid_t	two;
}				t_pids;

#endif