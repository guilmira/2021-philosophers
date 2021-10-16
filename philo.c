/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 09:48:25 by guilmira          #+#    #+#             */
/*   Updated: 2021/10/16 15:54:35 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



/** PURPOSE : Execute thread (philosopher) routine. */
void	*routine(void *argu)
{
	int				i;
	int				ms;
	t_time			*arg;
	struct timeval	time;

	t_philo	*philo;
	static int n;

	arg = (t_time *)argu;
	philo = arg->array[n];
	philo->index = n + 1;
	assign_mutex2(arg, arg->knives, philo->index);
	n++;

	time = arg->init_time;
	i = -1;
	while (++i < 1)
	{
		//MUTEX para los print
		pthread_mutex_lock(&(philo->left));
		ms = get_microseconds(time);
		printf(KNIFE);
		pthread_mutex_lock(&(philo->right));
		ms = get_microseconds(time);
		printf(KNIFE);
		ms = get_microseconds(time);
		printf(EAT);
		ms = get_microseconds(time);
		printf(SLEEP);
		pthread_mutex_unlock(&(philo->right));
		pthread_mutex_unlock(&(philo->left));
		ms = get_microseconds(time);
		printf(THINK);
		usleep(1);
	}
	return (NULL);
}

/** PURPOSE : Create thread for ecach of the phiilosphers.
 * 1. Creates with a function that recieves as input the routine .
 * 2. Executes thread join to close the thread within main process. */
int	create_threads(t_time *arg)
{
	int		i;
	t_philo	**philos;

	philos = arg->array;
	i = -1;
	while (++i < arg->total_philos)
		if (pthread_create(&(philos[i]->thread), NULL, routine, (void *)arg))
			return (1);
	i = -1;
	while (++i < arg->total_philos)
		pthread_join(arg->array[i]->thread, NULL);
	return (0);
}



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
	/* if (assign_mutex(arg, arg->total_philos, arg->knives))
		return (1); */
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
