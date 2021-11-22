/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/22 14:56:59 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/11/22 14:57:08 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "check_input.h"

/*
** Check argc. If not 5, exit program with error message.
*/

int	check_input(int argc)
{
	if (argc != 5)
	{
		ft_putstr_fd("Error\nWrong amount of arguments. \
Run as: ./pipex file_in cmd1 cmd2 file_out", STDOUT_FILENO);
		return (RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
}