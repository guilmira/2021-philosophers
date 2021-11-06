/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7death_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 10:07:29 by guilmira          #+#    #+#             */
/*   Updated: 2021/11/06 12:58:34 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/** PURPOSE : Evaluates if actual time must kill philosphers. */
static int	fersea(t_philo *philo)
{
	int	time_die;
	int	actual_time;

	time_die = philo->times->time_die;
	actual_time = get_microseconds(philo->times->init_time);
	if ((actual_time - philo->time_ate) > time_die)
		return (1);
	return (0);
}

/** PURPOSE : Constantly checks threads for philo. */
int	dead_checker(t_philo **array, int total_philos)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < total_philos)
		{
			if (fersea(array[i]))
			{
				array[i]->times->in_execution = 0;
				dead_message(array[i]);
				return (i);
			}
			i++;
		}
	}
}

/** PURPOSE : Cleaning function in order to free memory of array.
 * Due to the use of ft_calloc while alocating memory for the
 * array, it is garanteed that each sigle element is intialized to NULL. */
void	free_array_mutex(pthread_mutex_t **array, int total_philos)
{
	int	i;

	if (!array)
		return ;
	i = -1;
	while (++i < total_philos)
	{
		if (array[i])
			free(array[i]);
	}
}

/** PURPOSE : Cleaning function in order to free memory of array.
 * Due to the use of ft_calloc while alocating memory for the
 * array, it is garanteed that each sigle element is intialized to NULL. */
void	free_array_philos(t_philo **array, int total_philos)
{
	int	i;

	if (!array)
		return ;
	i = -1;
	while (++i < total_philos)
	{
		if (array[i])
			free(array[i]);
	}
}
