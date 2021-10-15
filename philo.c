/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 09:48:25 by guilmira          #+#    #+#             */
/*   Updated: 2021/10/15 15:53:04 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;

void	full_shutdown(t_time *arg)
{
	if (arg)
		free (arg);
	printf("%s", EX);
}


/* void	init_struct(int argc, t_times *arg)
{

} */

/** PURPOSE : Generates struct argument.
 * 1. Allocates memory. Notice that function parser already
 * has checked that argument are either total 5 or 6.
 * 2. Reads value of arguments.*/
t_time	*reader(int argc, char *argv[])
{
	t_time	*arg;

	arg = NULL;
	if (argc == OPT_1)
		arg = ft_calloc(4, sizeof(int));
	else if (argc == OPT_2)
		arg = ft_calloc(5, sizeof(int));
	if (!arg)
		return (NULL);
	arg->total_philos = ft_atoi(argv[1]);
	arg->time_die = ft_atoi(argv[2]);
	arg->time_eat = ft_atoi(argv[3]);
	arg->time_sleep = ft_atoi(argv[4]);
	arg->fifht_argument = 0;
	arg->nbr_eat = 0;
	if (argc == OPT_2)
	{
		arg->fifht_argument++;
		arg->nbr_eat = ft_atoi(argv[5]);
	}
	return (arg);
}

t_bool knife = 0;

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

/** PURPOSE : .
 * 1. . */
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
