/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/02 12:45:34 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/11/21 21:07:37 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_INPUT_H
# define PARSE_INPUT_H

/* System headers */
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>

/* User defined headers */
# include "libft/libft.h"
# include "data.h"
# include "get_filenames.h"
# include "utils.h"

/* Function prototypes */
int	parse_input(t_data *data, int argc, char **argv, char **envp);

#endif