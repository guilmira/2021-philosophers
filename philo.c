/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 09:48:25 by guilmira          #+#    #+#             */
/*   Updated: 2021/10/15 18:42:35 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/** PURPOSE : Lock and unlock resource access. */
pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;
t_bool knife = 0;

int	get_microseconds(t_time	*arg)
{
	long int	seconds;
	int 		microseconds;
	int			microseconds_final;
	struct		timeval current_time;

	if (gettimeofday(&current_time, NULL))
		return (0);
	seconds = current_time.tv_sec - arg->init_time.tv_sec;
	microseconds = current_time.tv_usec - arg->init_time.tv_usec;
	microseconds_final = (int) seconds * CONVER + microseconds;
	return (microseconds_final);
}

/** PURPOSE : Execute thread (philosopher) routine. */
void	*routine(void *argu)
{
	int ms;
	t_time *arg;

	arg = (t_time *)argu;
	int	i;

	i = -1;
	while (++i < 1)
	{
		pthread_mutex_lock(&mutex);

		ms = get_microseconds(arg);
		printf(KNIFE);
		ms = get_microseconds(arg);
		printf(EAT);
		ms = get_microseconds(arg);
		printf(SLEEP);
		//start sleeping fnc
		pthread_mutex_unlock(&mutex);
		usleep(1);
		ms = get_microseconds(arg);
		printf(THINK);
		usleep(1);
	}
	return (NULL);
}

/** PURPOSE : Create philosophers.
 * 1. Allocate memory. Notice that there is an array of philos.
 * This requires, first allocate space for (number of philos) pre.
 * this is: |pointer| |pointer| |pointer| (for 3 philos)
 * 2. Then, in each of the pointers, an allocation for the struct is needed.
 * For example, for pointer number 1, it need a malloc(sizeof(STRUCT)). */
int	create_philos(t_time *arg)
{
	int	i;
	t_philo **philos;
	i = -1;

	arg->array = ft_calloc(arg->total_philos, sizeof(t_philo *));
	philos = arg->array;
	if (!philos)
		return (0);
	i = -1;
	while (++i < arg->total_philos)
	{
		philos[i] = ft_calloc(1, sizeof(t_philo));
		/* if (!array[i])
		{
			free_array(array)
			return (0);
		} */
		philos[i]->index = i + 1;
		if (pthread_create(&(philos[i]->thread), NULL, routine, (void *)arg))
		return (0);
	}
	i = -1;
	while (++i < arg->total_philos)
	{
		pthread_join(arg->array[i]->thread, NULL);
	}
	return (0);
}



/** PURPOSE : Model and simulation of a philosophers table.
 * 1. Parser argument. Must be 4 or 5 clean natural numbers.
 * 2. Read arguments into struct.
 * 3. Execute philosophers routine. */
int main(int argc, char *argv[])
{
	t_time	*arg;

	//printf("init: %li y %i\n", init_time.tv_sec, init_time.tv_usec);

	//atexit(leaks);
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
	if (gettimeofday(&(arg->init_time), NULL))
	{
		full_shutdown(arg);
		return (1);
	}

	create_philos(arg);
	//full_shutdown(arg); clean_memory;
	usleep(100);
	printf("%i\n", get_microseconds(arg));

	return (0);
}


