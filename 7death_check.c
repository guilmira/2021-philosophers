/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7death_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 10:07:29 by guilmira          #+#    #+#             */
/*   Updated: 2021/11/09 11:58:07 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/** PURPOSE : Evaluates if actual time must kill philosphers. */
static int	fersea(t_philo *philo)
{
	int	time_die;
	int	actual_time;

	time_die = philo->times->time_die;
	if (philo->complete == philo->times->nbr_eat)
		return (0);
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

/** PURPOSE : Checks if all philoss have eaten the required
 * number of times (if specified). */
int	full_hunger_check(t_philo **array, int total_philos)
{
	int	i;

	i = -1;
	while (++i < total_philos)
		if (array[i]->complete != array[i]->times->nbr_eat)
			return (0);
	return (1);
}

/** PURPOSE : Imprved fucntion for second case program. */
int	augmented_dead_checker(t_philo **array, int total_philos)
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
			if (full_hunger_check(array, total_philos))
			{
				array[i]->times->in_execution = 0;
				return (i);
			}
			i++;
		}
	}
}
