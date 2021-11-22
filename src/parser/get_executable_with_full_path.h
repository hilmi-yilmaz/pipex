/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_executable_with_full_path.h                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/22 12:32:34 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/11/22 12:32:35 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_EXECUTABLE_WITH_FULL_PATH_H
# define GET_EXECUTABLE_WITH_FULL_PATH_H

/* System headers */
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

/* User defined headers */
# include "../libft/libft.h"
# include "../data.h"

/* Function prototypes */
int	get_executable_with_full_path(t_data *data, char **cmd);

#endif