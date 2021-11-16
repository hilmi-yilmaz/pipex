/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/02 12:45:49 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/11/16 17:29:13 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

/* System headers */
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

/* User defined headers */
# include "data.h"

/* Function prototypes */
int		wrapper_close(int fd);
int		wrapper_pipe(int *fds);
void	free_data(t_data data, int num_commands);
void	print_str_array(char **str);
void	print_data(t_data data, int num_commands);

#endif