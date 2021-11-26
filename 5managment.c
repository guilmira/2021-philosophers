/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5managment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 16:00:14 by guilmira          #+#    #+#             */
/*   Updated: 2021/11/26 13:04:54 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/** PURPOSE : Free memory of simulation.
 * For the function to properly work, all pointers have been
 * initialized to NULL at the beginning of the program.
 * Due to the use of ft_calloc while allocating memory and the
 * careful intitialization of pointers to NULL, the function will not
 * concure in double frees. */
void	clean_simulation(t_philo **array, \
pthread_mutex_t **knives, int total_philos)
{
	if (array[0]->print)
	{
		pthread_mutex_destroy(array[0]->print);
		pthread_mutex_destroy(array[0]->dead);
		free(array[0]->dead);
		free(array[0]->print);
	}
	if (knives)
	{
		if (knives[0])
		{
			mutex_destructor(knives, total_philos);
			free_array_mutex(knives, total_philos);
		}
		free(knives);
	}
	if (array)
	{
		if (array[0])
			free_array_philos(array, total_philos);
		free(array);
	}
}

/** PURPOSE : Cleaning function in order to destroy mutex. */
void	mutex_destructor(pthread_mutex_t **knives, int total_philos)
{
	int	i;

	if (!knives)
		return ;
	i = -1;
	while (++i < total_philos)
		pthread_mutex_destroy(knives[i]);
}

/** PURPOSE : Clean only the main argument. */
void	clean_argument(t_time *arg)
{
	if (arg)
		free(arg);
}

/** PURPOSE : shutdown program freeing heap allocated memory.
 * 1. Clean memory for argument.
 * 3. Print error message. */
void	ft_shutdown(t_time *arg)
{
	if (arg)
		clean_argument(arg);
	printf("%s", EX);
	return ;
}
