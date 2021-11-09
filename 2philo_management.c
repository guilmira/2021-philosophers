/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2philo_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 11:30:29 by guilmira          #+#    #+#             */
/*   Updated: 2021/11/09 13:14:07 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/** PURPOSE : Accurate sleep. Garantees to work by reducing
 * time lapse of microseconds. Notice that there are values for the
 * usleep that are much more precise, like 60 and 200. */
void	acc_sleep(int time, struct timeval init)
{
	int	init_miliseconds;

	init_miliseconds = get_miliseconds(init);
	while (get_miliseconds(init) < init_miliseconds + time)
		usleep(100);
}

/** PURPOSE : Calculate number of miliseconds that have
 * transcurred since program init. */
int	get_miliseconds(struct timeval	init_time)
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
	return (microseconds_final / 1000);
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
		array[i]->time_ate = 0;
		array[i]->complete = 0;
	}
	return (0);
}

/** PURPOSE : Create array of pointers to mutex.
 * The purpose of the mutex is:
 * Lock and unlock resource access. */
pthread_mutex_t	**create_mutex(int total_philos)
{
	int				i;
	pthread_mutex_t	**mutex_array;

	mutex_array = ft_calloc(total_philos, sizeof(pthread_mutex_t *));
	if (!mutex_array)
		return (NULL);
	i = -1;
	while (++i < total_philos)
	{
		mutex_array[i] = ft_calloc(1, sizeof(pthread_mutex_t));
		if (!mutex_array[i])
		{
			free_array_mutex(mutex_array, total_philos);
			free(mutex_array);
			return (NULL);
		}
		if (pthread_mutex_init(mutex_array[i], NULL))
		{
			mutex_destructor(mutex_array, total_philos);
			free_array_mutex(mutex_array, total_philos);
			free(mutex_array);
			return (NULL);
		}
	}
	return (mutex_array);
}
