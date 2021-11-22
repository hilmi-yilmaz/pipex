/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/02 12:45:34 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/11/22 12:22:33 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_INPUT_H
# define PARSE_INPUT_H

/* User defined headers */
# include "../libft/libft.h"
# include "../data.h"
# include "get_commands.h"
# include "get_filenames.h"
# include "../utils/utils.h"

/* Function prototypes */
int	parse_input(t_data *data, int argc, char **argv, char **envp);

#endif