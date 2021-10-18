/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 09:48:25 by guilmira          #+#    #+#             */
/*   Updated: 2021/10/18 12:32:59 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	init_philos(t_philo **array, t_time *arg)
{
	int	i;

	i = -1;
	while (++i < arg->total_philos)
	{
		array[i]->times = arg;
	}
	return (0);
}

void	link_philos_and_mutex(t_philo **array, \
pthread_mutex_t *knives, int total_philos)
{
	int	i;

	i = -1;
	while (++i < total_philos)
	{
		array[i]->left = knives[i];
		if (i != total_philos - 1)
			array[i]->right = knives[i + 1];
		else
			array[i]->right = knives[0];
	}
}

/** PURPOSE : Create philosophers.
 * 1. Allocate memory. Notice that there is an array of philos.
 * This requires, first allocate space for (number of philos) pre.
 * this is: |pointer| |pointer| |pointer| (for 3 philos). */
int	run_simulation(t_time *arg)
{
	t_philo			**array;
	pthread_mutex_t	*knives;

	if (gettimeofday(&(arg->init_time), NULL))
		return (1);
	array = ft_calloc(arg->total_philos, sizeof(t_philo *));
	if (!array)
		return (1);
	if (create_philos(array, arg->total_philos))
		return (1);
	create_mutex(&knives, arg->total_philos);
	init_philos(array, arg);
	link_philos_and_mutex(array, knives, arg->total_philos); //aqui podria haber fallo si no apss mutex x ref.

	if (create_threads(array, arg->total_philos))
		return (1);
	//clean_array_and_knives(array, knives, arg->total_philos);
	return (0);
}

/* void ft_leaks(void)
{
	system("leaks philo");
} */



/** PURPOSE : Model and simulation of a philosophers table.
 * 1. Parser argument. Must be 4 or 5 clean natural numbers.
 * 2. Read arguments into struct.
 * 3. Execute philosophers routine. */
int	main(int argc, char *argv[])
{
	t_time	*arg;

	//atexit(ft_leaks);
	arg = NULL;
	if (parser(argc, argv))
	{
		//full_shutdown(arg); shutdown(arg)
		return (1);
	}
	arg = reader(argc, argv);
	if (!arg)
	{
		//full_shutdown(arg); shutdown(arg)
		return (1);
	}
	if (run_simulation(arg))
	{
		//full_shutdown(arg);
		return (1);
	}
	//clean_memory(arg);
	return (0);//exit(0);
}
