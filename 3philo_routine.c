/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3philo_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 10:55:52 by guilmira          #+#    #+#             */
/*   Updated: 2021/11/04 13:20:03 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	release_knife(t_philo *philo, int flag)
{
	if (!flag)
		pthread_mutex_unlock((philo->left));
	else
		pthread_mutex_unlock((philo->right));
}

void	grab_knife(t_philo *philo, int flag)
{
	if (!flag)
	{
		pthread_mutex_lock((philo->left));
		knife_l(philo);
	}
	else
	{
		pthread_mutex_lock((philo->right));
		knife_r(philo);
	}
}



/** PURPOSE : Execute thread (philosopher) routine. */
static void	*routine(void *array_element)
{
	int				i;
	t_philo			*philo;


	philo = (t_philo *)array_element;
	if (philo->index % 2)
		usleep(200); //ir probando, con poco vale
	i = -1;
	while (philo->times->in_execution) //prg->running
	{
		grab_knife(philo, LEFT); //si eres apr, agrra primero derecha
		grab_knife(philo, RIGHT);
		eat(philo);
		release_knife_msg(philo); //provisional para k te ayude a entender
		release_knife(philo, LEFT);
		release_knife(philo, RIGHT);
		ft_sleep(philo);
		think(philo);
	}
	return (NULL);
}

//Initial check
/* int	fersea(t_philo *philo)
{
	int	time_die;
	int	time_eat;
	int	time_sleep;

	time_die = philo->times->time_die;
	time_eat = philo->times->time_eat;
	time_sleep = philo->times->time_sleep;

	if ((time_eat + time_sleep) > time_die || \
	time_eat > time_die || time_sleep > time_die)
		return (1);

	return (0);
} */

int	fersea(t_philo *philo)
{
	int	time_die;
	int	actual_time;

	time_die = philo->times->time_die;
	actual_time = get_microseconds(philo->times->init_time);
	if ((actual_time - philo->time_ate) > time_die)
		return (1);
	return (0);
}

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
				full_dead(array[i]);
				return (i);
			}
			i++;
		}
	}
}

/** PURPOSE : Create thread for ecach of the phiilosphers.
 * 1. Creates with a function that recieves as input the routine .
 * 2. Executes thread join to close the thread within main process. */
int	create_threads(t_philo **array, int total_philos)
{
	int		i;

	i = -1;
	while (++i < total_philos)
	{
		if (pthread_create(&(array[i]->thread), NULL, routine, array[i]))
			return (1);
	}
	dead_checker(array, total_philos);
	i = -1;
	while (++i < total_philos)
		pthread_join(array[i]->thread, NULL);
	return (0);
}
