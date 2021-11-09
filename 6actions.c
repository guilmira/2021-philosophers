/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6actions.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 14:58:55 by guilmira          #+#    #+#             */
/*   Updated: 2021/11/09 11:28:13 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/** PURPOSE : Main body if printing actions.
 * 1. If program is not in execution, return.
 * 2. Lock mutex.
 * 3. Get actual time.
 * 4. Print message and unlock mutex. */
static void	action(t_philo *philo, char *str, \
struct timeval time, int index)
{
	int	miliseconds;
	int	philo_index_print;

	if (!philo->times->in_execution)
		return ;
	philo_index_print = index + 1;
	pthread_mutex_lock((philo->print));
	if (!philo->times->in_execution)
	{
		pthread_mutex_unlock((philo->print));
		return ;
	}
	miliseconds = get_microseconds(time);
	printf(str, miliseconds, philo_index_print);
	pthread_mutex_unlock((philo->print));
}

/** PURPOSE : Lock mutex, print message and wait time. */
void	knife(t_philo *philo)
{
	struct timeval	time;

	time = philo->times->init_time;
	action(philo, KNIFE, time, philo->index);
}

/** PURPOSE : Lock mutex, print message and wait time. */
void	eat(t_philo *philo)
{
	struct timeval	time;

	time = philo->times->init_time;
	action(philo, EAT, time, philo->index);
	philo->time_ate = get_microseconds(time);
	acc_sleep(philo->times->time_eat, time);
}

/** PURPOSE : Lock mutex, print message and wait time. */
void	ft_sleep(t_philo *philo)
{
	struct timeval	time;

	time = philo->times->init_time;
	action(philo, SLEEP, time, philo->index);
	acc_sleep(philo->times->time_sleep, time);
}

/** PURPOSE : Waiting natural state. */
void	think(t_philo *philo)
{
	struct timeval	time;

	time = philo->times->init_time;
	action(philo, THINK, time, philo->index);
}
