/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3philo_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 10:55:52 by guilmira          #+#    #+#             */
/*   Updated: 2021/10/18 14:12:29 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//BORRA PREGUNTA Y EMPIEZA DE NUEVO CON LA RUTINA
	//dudas, como identificar a los filos e mejor manera cuando entrass a la
	//rutina
	//DUDA 2 los mutex lefy right... nesteados? o por separado

int g_count = 10;

static void	action(t_philo *philo, char *str,\
struct timeval time, int index)
{
	int	miliseconds;
	int	philo_index_print;

	philo_index_print = index++;
	pthread_mutex_lock(&(philo->print));
	miliseconds = get_microseconds(time);
	printf(str, miliseconds, philo_index_print);
	miliseconds = get_microseconds(time);
	usleep(300000);
	pthread_mutex_unlock(&(philo->print));
}



/** PURPOSE : Execute thread (philosopher) routine. */
static void	*routine(void *array_element)
{
	int				i;
	t_philo			*philo;
	struct timeval	time;
	//prohibido meter miliseconds aqui y duplicar prints. solo un
	//print en action. UN UNICO PRINT.
	philo = (t_philo *)array_element;
	time = philo->times->init_time;


	i = -1;
	while (++i < 2)
	{
		pthread_mutex_lock(&(philo->left));
		pthread_mutex_lock(&(philo->right));
		if (philo->index == 0)
			g_count++;
		else
			g_count--;
		action(philo, EAT, time, philo->index);
		pthread_mutex_unlock(&(philo->right));
		pthread_mutex_unlock(&(philo->left));
	}
	return (NULL);
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
	i = -1;
	while (++i < total_philos)
		pthread_join(array[i]->thread, NULL);
	return (0);
}
