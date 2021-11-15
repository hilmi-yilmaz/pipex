/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   data.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/02 12:45:29 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/11/15 17:23:15 by hyilmaz       ########   odam.nl         */
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
	char	*file_in_name;
	char	*file_out_name;
	char	***commands; // [[cmd1], [cmd2], ... , NULL] --> [["ls", "la"], ["grep", "file_in"], ... , NULL]
	char	**path;
	int		fds[2];
}				t_data;

#endif