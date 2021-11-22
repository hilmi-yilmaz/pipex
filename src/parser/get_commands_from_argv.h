/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_commands_from_argv.h                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/22 12:08:53 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/11/22 12:30:39 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_COMMANDS_FROM_ARGV_H
# define GET_COMMANDS_FROM_ARGV_H

/* System headers */
# include <stdio.h>

/* User defined headers */
# include "../libft/libft.h"
# include "../data.h"
# include "../utils/utils.h"

/* Function prototypes */
int	get_commands_from_argv(t_data *data, char **argv, int i);

#endif