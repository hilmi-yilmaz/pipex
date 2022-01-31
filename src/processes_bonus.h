/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   processes_bonus.h                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/02 12:45:42 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/11/23 12:35:15 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESSES_BONUS_H
# define PROCESSES_BONUS_H

/* System headers */
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>

/* User defined headers */
# include "libft/libft.h"
# include "data.h"
# include "utils/utils.h"

/* Function prototypes */
int	middle_child(t_data *data, char **envp, int read_end_pipe, int i);

#endif