/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   data.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/02 12:45:29 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/11/22 19:20:27 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

/* System headers */
# include <sys/types.h>

/* Macros */
# define RETURN_FAILURE 1
# define RETURN_SUCCESS 0
# define CLOSE_FAILURE 2
# define MALLOC_FAILURE 3

/* Data structures */

/*
** Data struct:
** - file_in_name and file_out_name are filenames given through command line.
** - commands looks like:
** -->	[[cmd1], [cmd2], ... , NULL]
** -->	[["ls", "la"], ["grep", "file_in"], ... , NULL]
** - path is the environment variable path.
** - fds holds both ends of the pipe.
*/

typedef struct s_data
{
	char	*file_in_name;
	char	*file_out_name;
	char	***commands;
	char	**path;
	int		fds[2];
}				t_data;

typedef struct s_pids
{
	pid_t	one;
	pid_t	two;
}				t_pids;

#endif