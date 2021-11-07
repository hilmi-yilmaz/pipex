/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/02 12:45:49 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/11/06 16:46:34 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

/* System headers */
# include <stdio.h>
# include <unistd.h>

/* User defined headers */
# include "data.h"

/* Function prototypes */
int		wrapper_close(int fd);
void	print_data(t_data data);

#endif