/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   data.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/02 12:45:29 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/11/10 18:09:44 by hyilmaz       ########   odam.nl         */
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
typedef struct s_data
{
	int		file_in;
	int		file_out;
	char	***commands; // [[cmd1], [cmd2], ... , NULL] --> [["ls", "la"], ["grep", "file_in"], ... , NULL]
	char	**path;
}				t_data;

typedef struct s_pids
{
	pid_t	one;
	pid_t	two;
}				t_pids;

#endif