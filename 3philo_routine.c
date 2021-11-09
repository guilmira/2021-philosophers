/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3philo_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 10:55:52 by guilmira          #+#    #+#             */
/*   Updated: 2021/11/09 13:36:15 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/** PURPOSE : Loop for philos that grab first the left fork. */
static void	ft_loop(t_philo *philo)
{
	int	i;

	i = -1;
	while (philo->times->in_execution && \
	philo->complete != philo->times->nbr_eat)
	{
		grab_knife(philo, LEFT);
		grab_knife(philo, RIGHT);
		eat(philo);
		release_knife(philo, LEFT);
		release_knife(philo, RIGHT);
		ft_sleep(philo);
		think(philo);
		philo->complete++;
	}
}

/** PURPOSE : Execute thread (philosopher) routine. */
static void	*routine(void *array_element)
{
	t_philo			*philo;

	philo = (t_philo *)array_element;
	if (philo->index % 2)
		usleep(200);
	if (philo->index == 1)
		usleep(500);
	ft_loop(philo);
	return (NULL);
}

/** PURPOSE : Simple solution for when a single philo is present. */
static void	single_philo(t_philo **array)
{
	knife(array[0]);
	single_dead_message(array[0]);
}

/** PURPOSE : Create thread for each of the phiilosphers.
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
