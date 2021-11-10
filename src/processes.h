/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   processes.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/02 12:45:42 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/11/10 16:55:50 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESSES_H
# define PROCESSES_H

/* System headers */
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>

/* User defined headers */
# include "libft/libft.h"
# include "data.h"
# include "utils.h"

/* Function prototypes */
int child_one(t_data *data, int *fds, t_pids *pid, char **argv, char **envp);
int child_two(t_data *data, int *fds, t_pids *pid, char **argv, char **envp);
int a(t_data *data, int *pid,int fd0,char *argv,char **envp, int fds1, int (func)(char *), int x, int y, int a);
int	input_file(char *argv);
int	output_file(char *argv);

#endif