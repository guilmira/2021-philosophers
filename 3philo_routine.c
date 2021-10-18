/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3philo_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 10:55:52 by guilmira          #+#    #+#             */
/*   Updated: 2021/10/18 12:49:35 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



/* void	action(t_time *arg, char *str, int miliseconds, int number_philo)
{
	//pthread_mutex_lock(&(arg->mtx_print));
	printf(str, miliseconds, number_philo);
	//pthread_mutex_unlock(&(arg->mtx_print));
} */

int g_count = 10;

/** PURPOSE : Execute thread (philosopher) routine. */
static void	*routine(void *array_element)
{

	//BORRA PREGUNTA Y EMPIEZA DE NUEVO CON LA RUTINA
	//dudas, como identificar a los filos e mejor manera cuando entrass a la
	//rutina
	//DUDA 2 los mutex lefy right... nesteados? o por separado
	int		i;
	t_philo	*philo;
	struct timeval	time;
	philo = (t_philo *)array_element;
	int ms;
	ms = 0;
	time = philo->times->init_time;
	//ms = get_microseconds(time);

	i = -1;
	while (++i < 2)
	{
		//mutex;
		pthread_mutex_lock(&(philo->left));
		pthread_mutex_lock(&(philo->right));
		if (philo->index == 0)
			g_count++;
		else
			g_count--;
		ms = get_microseconds(time);
		printf("(%i) philo_index: %i y count: %i\n", ms, philo->index, g_count);
		pthread_mutex_unlock(&(philo->right));
		pthread_mutex_unlock(&(philo->left));

		//ve mutex a mutex viendo comportamientos. pocoa  poc y
		//One filo at a time. pon funcioes de comer dormir, pensar
		//con sus correspondientes tiempos

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
