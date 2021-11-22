/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_commands_bonus.h                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/22 14:47:27 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/11/22 15:17:23 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_COMMANDS_BONUS_H
# define EXECUTE_COMMANDS_BONUS_H

/* System headers */
# include <unistd.h>

/* User defined headers */
# include "data.h"
# include "processes.h"
# include "processes_bonus.h"

/* Function prototypes */
int	execute_commands(t_data data, int num_commands, char **envp, \
							int *last_process_pid);

#endif