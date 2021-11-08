/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6actions2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 11:28:23 by guilmira          #+#    #+#             */
/*   Updated: 2021/11/08 14:21:37 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/** PURPOSE : Print dead message for philo. */
void	dead_message(t_philo *philo)
{
	struct timeval	time;
	int				miliseconds;
	int				philo_index_print;

	time = philo->times->init_time;
	philo_index_print = philo->index + 1;
	pthread_mutex_lock((philo->dead));
	miliseconds = get_microseconds(time);
	printf(DIED, miliseconds, philo_index_print);
	pthread_mutex_unlock((philo->dead));
}

/** PURPOSE : Print behaviour for a single philo. */
void	single_dead_message(t_philo *philo)
{
	int	miliseconds;
	int	philo_index_print;

	philo_index_print = philo->index + 1;
	pthread_mutex_lock((philo->print));
	miliseconds = philo->times->time_die;
	printf(DIED, miliseconds, philo_index_print);
	pthread_mutex_unlock((philo->print));
}
