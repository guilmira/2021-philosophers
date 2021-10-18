/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5managment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 16:00:14 by guilmira          #+#    #+#             */
/*   Updated: 2021/10/18 13:47:33 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_leaks(void)
{
	system("leaks philo");
}
//EXIT no permitida, habra que quitarla.

/** PURPOSE : Cleaning function in order to free memory of array.
 * Due to the use of ft_calloc while alocating memory for the
 * array, it is garanteed that each sigle element is intialized to NULL. */
void	free_array_philos(t_philo **array, int total_philos)
{
	int	i;

	if (!array)
		return ;
	i = -1;
	while (++i < total_philos)
	{
		if (array[i])
			free(array[i]);
	}
}

/** PURPOSE : Cleaning function in order to destroy mutex. */
void	mutex_destructor(pthread_mutex_t *knives, int total_philos)
{
	int	i;

	if (!knives)
		return ;
	i = -1;
	while (++i < total_philos)
	{
		//printf("illegal instruction\n"); revisar en algun momento
		pthread_mutex_destroy(&(knives[i]));
	}
}

/** PURPOSE : Free memory of simulation.
 * For the function to properly work, all pointers have been
 * initialized to NULL at the beginning of the program.
 * Due to the use of ft_calloc while alocating memory and the
 * careful intitialization of pointers to NULL, the function will not
 * concure in double frees. */
void	clean_simulation(t_philo **array, pthread_mutex_t *knives, int total_philos)
{
	if (knives)
	{
		mutex_destructor(knives, total_philos);
		free(knives);
	}
	if (array)
	{
		if (array[0])
			free_array_philos(array, total_philos);
		free(array);
	}
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
	exit(0);
}
