/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8philo_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 10:01:42 by guilmira          #+#    #+#             */
/*   Updated: 2021/10/19 13:24:11 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/** PURPOSE : returns 1 if space of variation. */
int	ft_isspaces(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || \
	c == '\r' || c == '\f' || c == '\v');
}

/** PURPOSE : returns 1 if digit. */
t_bool	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

/** PURPOSE : converts string into integer equivalent.
 * 1. Skip spaces, tabs and similar.
 * 2. Check sign.
 * 3. Take the string digit and add it to global number (multiplied by 10); */
int	ft_atoi(const char *str)
{
	unsigned int	n;
	unsigned int	i;
	int				sign;

	sign = 1;
	i = 0;
	n = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || \
	str[i] == '\r' || str[i] == '\f' || str[i] == '\v')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = (str[i] - '0') + n * 10;
		if (n > 2147483647 && sign == 1)
			return (-1);
		else if (n > 2147483648 && sign == -1)
			return (0);
		i++;
	}
	return (((int) n * sign));
}

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
 * Examples: allocate space for array of ints (grades from 0 to 10 BOTH included)
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
