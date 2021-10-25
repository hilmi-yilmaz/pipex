/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_malloc.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/18 09:30:40 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/10/18 09:30:41 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

void	*error_malloc(unsigned int bytes)
{
	void	*ptr;

	ptr = malloc(bytes);
	if (ptr == NULL)
	{
		printf("Error: %s\n", strerror(errno));
		return (NULL);
	}
	return (ptr);
}
