/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   processes.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/02 12:45:42 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/11/02 12:58:58 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESSES_H
# define PROCESSES_H

/* System headers */
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

/* User defined headers */
# include "libft/libft.h"
# include "data.h"

/* Function prototypes */
int child_one(t_data *data, int *fds, t_pids *pid, char **envp);
int child_two(t_data *data, int *fds, t_pids *pid, char **envp);

#endif