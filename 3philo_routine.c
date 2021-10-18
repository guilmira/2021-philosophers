/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3philo_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 10:55:52 by guilmira          #+#    #+#             */
/*   Updated: 2021/10/18 15:42:33 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//BORRA PREGUNTA Y EMPIEZA DE NUEVO CON LA RUTINA
	//dudas, como identificar a los filos e mejor manera cuando entrass a la
	//rutina
	//DUDA 2 los mutex lefy right... nesteados? o por separado

int g_count = 10;

/** PURPOSE : Execute thread (philosopher) routine. */
static void	*routine(void *array_element)
{
	int				i;
	t_philo			*philo;

	//prohibido meter miliseconds aqui y duplicar prints. solo un
	//print en action. UN UNICO PRINT.
	philo = (t_philo *)array_element;

t//llimPIRAR Y DEARLO SOLO CON FORKS A VER QUE SUCCEDE. ES EN LOS FORKS
DOONDE NO VA EL MUTEX, EN EL COUNT FUNCIIONA BIEN. PRUEBA CON UN SOLO MUTEX, NADA defaultAMBOS FORKS.
	i = -1;
	while (++i < 2)
	{
		if (philo->index % 2)
			usleep(500);
		pthread_mutex_lock(&(philo->left));
		knife_l(philo);
		pthread_mutex_lock(&(philo->right));
		knife_r(philo);
		if (!(philo->index % 2))
			g_count++;
		else
			g_count--;
		usleep(100);
		eat(philo);
		pthread_mutex_unlock(&(philo->right));
		pthread_mutex_unlock(&(philo->left));
		ft_sleep(philo);
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
