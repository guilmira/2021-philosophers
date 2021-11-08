/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3philo_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 10:55:52 by guilmira          #+#    #+#             */
/*   Updated: 2021/11/08 14:44:43 by guilmira         ###   ########.fr       */
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
		usleep(200); //1000 he visto
	//gettimeofday(&(philo->times->init_time), NULL); //cada uno tiene su tiempo inical
	i = -1;
	while (philo->times->in_execution && \
	philo->complete != philo->times->nbr_eat)
	{
		grab_knife(philo, LEFT); //si eres apr, agrra primero derecha
		grab_knife(philo, RIGHT);
		eat(philo);
		//release_knife_msg(philo);
		release_knife(philo, LEFT);
		release_knife(philo, RIGHT);
		ft_sleep(philo);
		think(philo);
		philo->complete++;
	}
	return (NULL);
}

void	single_philo(t_philo **array)
{
	knife_l(array[0]);
	single_dead_message(array[0]);
}

/** PURPOSE : Create thread for ecach of the phiilosphers.
 * 1. Creates with a function that recieves as input the routine .
 * 2. Executes thread join to close the thread within main process. */
int	create_threads(t_philo **array, int total_philos)
{
	int		i;

	i = -1;
	if (total_philos == 1)
	{
		single_philo(array);
		return (0);
	}
	while (++i < total_philos)
	{
		if (pthread_create(&(array[i]->thread), NULL, routine, array[i]))
			return (1);
	}
	if (array[0]->times->nbr_eat == -1)
		dead_checker(array, total_philos);
	else
		augmented_dead_checker(array, total_philos);
	i = -1;
	while (++i < total_philos)
		pthread_join(array[i]->thread, NULL);
	return (0);
}
