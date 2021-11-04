/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 09:48:25 by guilmira          #+#    #+#             */
/*   Updated: 2021/11/04 10:56:42 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//la primera vex que lo tiras en un nuevo ordena se queda
//en un bucle como infinito. Tdos agarran el left y no tira

//si hay uno que esta thinking qu active una flag
//puede ser como un array de prioridades con los que estan think
//los demas, checkean ese array. Si hay alguienn en cola, se tragan un
//usleep.

/** PURPOSE : Execute simulation.
 * 1. Get reference time.
 * 2. Allocate memory. Notice that there is an array of philos.
 * This requires, first allocate space for (number of philos) pre.
 * this is: |pointer| |pointer| |pointer| (for 3 philos).
 * 3. Create philos and mutex and link them.
 * 4. Create threads and clean process. */
int	run_simulation(t_time *arg)
{
	t_philo			**array;
	pthread_mutex_t	**knives;

	if (gettimeofday(&(arg->init_time), NULL))
		return (1);
	array = ft_calloc(arg->total_philos, sizeof(t_philo *));
	if (!array)
		return (1);
	if (create_philos(array, arg->total_philos))
		return (1);
	knives = create_mutex(arg->total_philos);
	if (!knives || init_philos(array, arg))
	{
		clean_simulation(array, knives, arg->total_philos);
		return (1);
	}
	link_philos_and_mutex(array, knives, arg->total_philos);
	if (create_threads(array, arg->total_philos))
	{
		clean_simulation(array, knives, arg->total_philos);
		return (1);
	}
	clean_simulation(array, knives, arg->total_philos);
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
		//no uses clean aqui. se libera en run_simul.
		return (1);
	}
	clean_argument(arg);
	//return (0);
	exit(0);
}
