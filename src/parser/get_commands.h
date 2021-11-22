/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_commands.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/22 11:54:00 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/11/22 15:01:34 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_COMMANDS_H
# define GET_COMMANDS_H

/* System headers */
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

/* User defined headers */
# include "../libft/libft.h"
# include "../data.h"
# include "get_commands_from_argv.h"
# include "get_executable_with_full_path.h"

/* Function prototypes */
int	get_commands(t_data *data, char **argv, char **envp, int *i);

#endif