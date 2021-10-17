/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3philo_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 10:55:52 by guilmira          #+#    #+#             */
/*   Updated: 2021/10/17 11:50:00 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t g_mutex  = PTHREAD_MUTEX_INITIALIZER;

void	action(char *str, int miliseconds, int number_philo)
{
	printf(str, miliseconds, number_philo);
}

/** PURPOSE : Execute thread (philosopher) routine. */
static void	*routine(void *argu)
{
	int				i;
	int				ms;
	t_time			*arg;
	struct timeval	time;

	int left;
	int right;
	arg = (t_time *)argu;
	t_philo	*philo;
	static int n;


	pthread_mutex_lock(&g_mutex);
	i = -1;
	while (++i < arg->total_philos)
	{
		philo = arg->array[i];
		if (philo->index == (n + 1))
			break;
	}
	printf("filosofo numero de array %i en hilo %i\n", philo->index -1, n );
	n++;
	pthread_mutex_unlock(&g_mutex);



	left = 0;
	right = 0;
	ms = 0;
	time = arg->init_time;
	i = -1;
	while (++i < 2)
	{
		//MUTEX para los print
		if (!left)
		{
			pthread_mutex_lock(&(philo->left));
			left++;
			ms = get_microseconds(time);
			printf(KNIFE);
			pthread_mutex_unlock(&(philo->left));
		}
		if (!right)
		{
			pthread_mutex_lock(&(philo->right));
			right++;
			ms = get_microseconds(time);
			printf(KNIFER);
			pthread_mutex_unlock(&(philo->right));
		}
		if (left & right)
		{
			left = 0;
			right = 0;
			ms = get_microseconds(time);
			action(EAT, ms, PH);
			ms = get_microseconds(time);
			action(SLEEP, ms, PH);
			ms = get_microseconds(time);
			action(THINK, ms, PH);
			usleep(1000);
		}
	}
	return (NULL);
}

/** PURPOSE : Create thread for ecach of the phiilosphers.
 * 1. Creates with a function that recieves as input the routine .
 * 2. Executes thread join to close the thread within main process. */
int	create_threads(t_time *arg)
{
	int		i;
	t_philo	**philos_array;

	philos_array = arg->array;
	i = -1;
	while (++i < arg->total_philos)
		if (pthread_create(&(philos_array[i]->thread), NULL, routine, (void *)arg))
			return (1);
	i = -1;
	while (++i < arg->total_philos)
		pthread_join(arg->array[i]->thread, NULL);
	return (0);
}
