/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_data.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/21 14:12:01 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/11/21 14:12:02 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_DATA_H
# define FREE_DATA_H

/* System headers */
# include <stdlib.h>
# include <stdio.h>

/* User defined headers */
# include "data.h"

/* Function prototypes */
void	free_all(t_data data, int num_commands);

#endif