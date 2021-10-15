/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 09:48:25 by guilmira          #+#    #+#             */
/*   Updated: 2021/10/15 16:15:13 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/** PURPOSE : Lock and unlock resource access. */
pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;
t_bool knife = 0;

/** PURPOSE : Execute thread (philosopher) routine. */
void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	int	i;

	i = -1;
	while (++i < 10)
	{
		pthread_mutex_lock(&mutex);


		printf(KNIFE);

		printf(EAT);

		printf(SLEEP);
		//start sleeping fnc
		pthread_mutex_unlock(&mutex);
		usleep(30);

		printf(THINK);
		usleep(1);
	}
	return (NULL);
}

int	create_philos(t_time *arg)
{
	int	i;
	t_philo	**array;

	i = -1;
	array = ft_calloc(arg->total_philos, sizeof(t_philo *));
	if (!array)
		return (0);
	i = -1;
	while (++i < arg->total_philos)
	{
		array[i] = ft_calloc(1, sizeof(t_philo));
		/* if (!array[i])
		{
			free_array(array)
			return (0);
		} */
		array[i]->index = i + 1;
		printf("philo nmbr is : %i\n", array[i]->index);
		if (pthread_create(&(array[i]->thread), NULL, routine, (void *)array[i]))
		return (0);
	}
	i = -1;
	while (++i < arg->total_philos)
	{
		pthread_join(array[i]->thread, NULL);
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
	create_philos(arg);
	//full_shutdown(arg); clean_memory;
	return (0);
}
