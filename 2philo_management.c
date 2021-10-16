/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2philo_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 11:30:29 by guilmira          #+#    #+#             */
/*   Updated: 2021/10/16 11:37:29 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/** PURPOSE : Calculate number of microseconds that have
 * transcurred since progrma init. */
int	get_microseconds(struct timeval	init_time)
{
	long int		seconds;
	int				microseconds;
	int				microseconds_final;
	struct timeval	current_time;

	if (gettimeofday(&current_time, NULL))
		return (0);
	seconds = current_time.tv_sec - init_time.tv_sec;
	microseconds = current_time.tv_usec - init_time.tv_usec;
	microseconds_final = (int) seconds * CONVER + microseconds;
	return (microseconds_final);
}

/** PURPOSE : Create philosophers.
 * 1. Recieves allocated memory.
 * this is: |pointer| |pointer| |pointer| (for 3 philos)
 * 2. For each of the pointers, an allocation for the struct is needed.
 * For example, for pointer number 1, it needs a malloc(sizeof(STRUCT)). */
int	create_philos(t_philo **array, int total_philos)
{
	int	i;

	i = -1;
	while (++i < total_philos)
	{
		array[i] = ft_calloc(1, sizeof(t_philo));
		if (!array[i])
		{
			free_array_philos(array, total_philos);
			return (1);
		}
		array[i]->index = i + 1;
	}
	return (0);
}
