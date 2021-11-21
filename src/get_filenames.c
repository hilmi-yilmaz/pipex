/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_filenames.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/21 21:05:10 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/11/21 21:06:20 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_filenames.h"

/*
** Get the filesnames with strdup.
** Including error handling.
*/

int	get_filenames(t_data *data, int argc, char **argv)
{
	data->file_in_name = ft_strdup(argv[1]);
	if (data->file_in_name == NULL)
	{
		perror("Error with malloc");
		return (RETURN_FAILURE);
	}
	data->file_out_name = ft_strdup(argv[argc - 1]);
	if (data->file_out_name == NULL)
	{
		perror("Error with malloc");
		return (RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
}