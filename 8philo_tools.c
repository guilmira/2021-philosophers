/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8philo_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 10:01:42 by guilmira          #+#    #+#             */
/*   Updated: 2021/10/13 10:04:36 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/** PURPOSE : fills reference with zeros.
 * 1. Uses memset with '0' input over 'n' bytes
 * */
static void	ft_bzero(void *s, size_t n)
{
	memset(s, 0, n);
}

/** PURPOSE : allocates memory, then fills it with 0.
 * 1. Casts malloc to return an UNSIGNED CHAR pointer.
 * 2. Uses ft_bzero to fill with zero.
 * Examples: allocate space for array if ints (grades from 0 to 10 BOTH included)
 * 		int *array;
 * 		array = ft_calloc(11, size of(int)); //usually int has size 4
 * 		free (array);
 * 		equivalent to definition in stack: int array[11];
 * */
void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*ptr;

	ptr = (unsigned char *) malloc(count * size);
	if (ptr == 0)
		return (0);
	ft_bzero(ptr, count * size);
	return (ptr);
}
