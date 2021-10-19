/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2philo_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 11:30:29 by guilmira          #+#    #+#             */
/*   Updated: 2021/10/19 10:24:03 by guilmira         ###   ########.fr       */
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
		array[i]->index = i;
	}
	return (0);
}

/** PURPOSE : Create array of mutex.
 * The purpose of the mutex is:
 * Lock and unlock resource access. */
pthread_mutex_t	*create_mutex(int total_philos)
{
	int				i;
	pthread_mutex_t	*mutex_array;

	mutex_array = ft_calloc(total_philos, sizeof(pthread_mutex_t));
	if (!mutex_array)
		return (NULL);
	i = -1;
	while (++i < total_philos)
	{
		if (pthread_mutex_init(&(mutex_array[i]), NULL))
		{
			mutex_destructor(mutex_array, total_philos);
			return (NULL);
		}
	}
	return (mutex_array);
}


/** PURPOSE : Create philosophers.
 * 1. Recieves allocated memory.
 * this is: |pointer| |pointer| |pointer| (for 3 philos)
 * 2. For each of the pointers, an allocation for the struct is needed.
 * For example, for pointer number 1, it needs a malloc(sizeof(STRUCT)). */
/* int	assign_mutex(t_time *arg, int total_philos, pthread_mutex_t	*knives)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < total_philos)
	{
		philo = arg->array[i];
		philo->left = knives[philo->index - 1];
		philo->left_index = philo->index - 1;
		if (i == total_philos - 1)
		{
			philo->right = knives[0];
			philo->right_index = 0;
		}
		else
		{

			philo->right = knives[philo->index];
			philo->right_index = philo->index;
		}
	}
	return (0);
} */

