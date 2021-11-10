/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/02 12:45:12 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/11/10 13:29:22 by hyilmaz       ########   odam.nl         */
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
# include <stdlib.h> //for exit
# include <sys/wait.h>
# include <fcntl.h> // for open

/* User defined headers */
# include "libft/libft.h"
# include "data.h"
# include "parse_input.h"
# include "processes.h"
# include "utils.h"

#endif