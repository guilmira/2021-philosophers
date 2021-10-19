/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6actions.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 14:58:55 by guilmira          #+#    #+#             */
/*   Updated: 2021/10/19 12:25:48 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	action(t_philo *philo, char *str,\
struct timeval time, int index)
{
	int	miliseconds;
	int	philo_index_print;

	philo_index_print = index + 1;
	pthread_mutex_lock((philo->print));
	miliseconds = get_microseconds(time);
	printf(str, miliseconds, philo_index_print);
	pthread_mutex_unlock((philo->print));
}

void	knife_l(t_philo *philo)
{
	struct timeval	time;
	time = philo->times->init_time;

	action(philo, KNIFE, time, philo->index);
}

void	knife_r(t_philo *philo)
{
	struct timeval	time;
	time = philo->times->init_time;
	action(philo, KNIFER, time, philo->index);
}
void	eat(t_philo *philo)
{
	struct timeval	time;
	time = philo->times->init_time;
	action(philo, EAT, time, philo->index);
	usleep(philo->times->time_eat);
}

void	ft_sleep(t_philo *philo)
{
	struct timeval	time;

	time = philo->times->init_time;
	action(philo, SLEEP, time, philo->index);
	usleep(philo->times->time_sleep);
}

/** PURPOSE : Waiting natural state. */
void	think(t_philo *philo)
{
	struct timeval	time;

	time = philo->times->init_time;
	action(philo, THINK, time, philo->index);
}
