/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/02 12:45:12 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/11/22 14:59:02 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/* System headers */
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>

/* User defined headers */
# include "libft/libft.h"
# include "data.h"
# include "parser/parse_input.h"
# include "processes.h"
# include "execute_commands.h"
# include "utils/utils.h"
# include "utils/free_data.h"
# include "check_input.h"

#endif