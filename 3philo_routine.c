/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3philo_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 10:55:52 by guilmira          #+#    #+#             */
/*   Updated: 2021/10/17 12:59:40 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



void	action(t_time *arg, char *str, int miliseconds, int number_philo)
{
	//pthread_mutex_lock(&(arg->mtx_print));
	printf(str, miliseconds, number_philo);
	//pthread_mutex_unlock(&(arg->mtx_print));
}

/** PURPOSE : Execute thread (philosopher) routine. */
static void	*routine(void *argu)
{

	//BORRA PREGUNTA Y EMPIEZA DE NUEVO CON LA RUTINA
	//dudas, como identificar a los filos e mejor manera cuando entrass a la
	//rutina
	//DUDA 2 los mutex lefy right... nesteados? o por separado
	int				i;
	int				ms;
	t_time			*arg;
	struct timeval	time;
	arg = (t_time *)argu;
	t_philo	*philo;
	static int n;



	ms = 0;
	time = arg->init_time;

	pthread_mutex_lock(&(arg->mtx_enter)); //ponlos global que fucnonaba
	i = -1;
	while (++i < arg->total_philos)
	{
		philo = arg->array[i];
		if (philo->index == (n + 1))
			break;
	}
	ms = get_microseconds(time);
	printf("(%i) filosofo numero %i en hilo %i\n", ms, philo->index, n );
	n++;
	pthread_mutex_unlock(&(arg->mtx_enter));

	i = -1;
	while (++i < 2)
	{
		//ve mutex a mutex viendo comportamientos. pocoa  poc y
		//One filo at a time. pon funcioes de comer dormir, pensar
		//con sus correspondientes tiempos

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
