/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 09:48:25 by guilmira          #+#    #+#             */
/*   Updated: 2021/10/17 10:57:49 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/** PURPOSE : Create philosophers.
 * 1. Allocate memory. Notice that there is an array of philos.
 * This requires, first allocate space for (number of philos) pre.
 * this is: |pointer| |pointer| |pointer| (for 3 philos). */
int	run_simulation(t_time *arg)
{
	if (gettimeofday(&(arg->init_time), NULL))
		return (1);
	arg->array = ft_calloc(arg->total_philos, sizeof(t_philo *));
	if (!arg->array)
		return (1);
	if (create_mutex(arg, arg->total_philos))
		return (1);
	if (create_philos(arg->array, arg->total_philos))
		return (1);
	if (assign_mutex(arg, arg->total_philos, arg->knives))
		return (1);
	if (create_threads(arg))
		return (1);
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
		full_shutdown(arg);
		return (1);
	}
	arg = reader(argc, argv);
	if (!arg)
	{
		full_shutdown(arg);
		return (1);
	}
	if (run_simulation(arg))
	{
		full_shutdown(arg);
		return (1);
	}
	clean_memory(arg);
	return (0);//exit(0);
}
