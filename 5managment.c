/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5managment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 16:00:14 by guilmira          #+#    #+#             */
/*   Updated: 2021/10/16 14:12:40 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//EXIT no permitida, habra que quitarla.

/** PURPOSE : Cleaning function in order to free memory of array.
 * Due to the use of ft_calloc while alocating memory for the
 * array, it is sure that each sigle element is intialized to NULL. */
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
void	mutex_destructor(pthread_mutex_t	*knives, int total_philos)
{
	int	i;

	if (!knives)
		return ;
	i = -1;
	while (++i < total_philos)
		pthread_mutex_destroy(&(knives[i]));
}

/** PURPOSE : Full free memory of program.
 * For the function to properly work, all pointers have been
 * initialized to NULL at the beginning of the program.
 * Due to the use of ft_calloc while alocating memory and the
 * careful intitialization of pointers to NULL, the function will not
 * concure in double frees. */
void	clean_memory(t_time *arg)
{
	if (arg->knives)
	{
		//if (arg->knives[0])no deja
			mutex_destructor(arg->knives, arg->total_philos);
		free(arg->knives);
	}
	if (arg->array)
	{
		if (arg->array[0])
			free_array_philos(arg->array, arg->total_philos);
		free(arg->array);
	}
	if (arg)
		free (arg);
}

/** PURPOSE : shutdown program meanwhile freeing heap allocated memory.
 * 1. Clean memory for all structs if allocated.
 * 3. Print error message. */
void	full_shutdown(t_time *arg)
{
	clean_memory(arg);
	printf("%s", EX);
	exit(0);
}
