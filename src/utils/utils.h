/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/02 12:45:49 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/11/22 15:10:49 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

/* System headers */
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

/* User defined headers */
# include "../data.h"

/* Function prototypes */
int		wrapper_fork();
int		wrapper_pipe(int *fds);
void	dup2_error_handling(int file_1, int file_2);
int		str_all_same_chars(char *str, char c);


#endif