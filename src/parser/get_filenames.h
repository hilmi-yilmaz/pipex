/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_filenames.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/22 12:32:49 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/11/22 12:32:50 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_FILENAMES_H
# define GET_FILENAMES_H

/* System headers */
# include <stdio.h>

/* User defined headers */
# include "../libft/libft.h"
# include "../data.h"

/* Function prototypes */
int	get_filenames(t_data *data, int argc, char **argv);

#endif