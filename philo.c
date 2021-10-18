/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 09:48:25 by guilmira          #+#    #+#             */
/*   Updated: 2021/10/18 13:33:21 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	knives = create_mutex(arg->total_philos);
	if (!knives) //no clenees aqui argument. te cargas stack
	{
		free(knives); //hay que poner el destructor de mutex
		free_array_philos(array, arg->total_philos);
		free(array);
		return(1);
	}
	init_philos(array, arg);
	link_philos_and_mutex(array, knives, arg->total_philos); //aqui podria haber fallo si no apss mutex x ref.
	if (create_threads(array, arg->total_philos)) //aqui flataria unos clean memory debajo
		return (1);
	clean_array_and_knives(array, knives, arg->total_philos);
	return (0);
}





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
		ft_shutdown(arg);
		return (1);
	}
	arg = reader(argc, argv);
	if (!arg)
	{
		ft_shutdown(arg);
		return (1);
	}
	if (run_simulation(arg))
	{

		ft_shutdown(arg); //lleva exit ahora mismo.
		//no ahce falta un cleane rdebajo xk se libera todo en run simultion
		return (1);
	}
	//system("leaks philo");
	clean_argument(arg);
	return (0);//exit(0);
}
