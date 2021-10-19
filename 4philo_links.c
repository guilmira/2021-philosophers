/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4philo_links.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 13:29:55 by guilmira          #+#    #+#             */
/*   Updated: 2021/10/19 13:23:19 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/** PURPOSE : Intialize philosophers. */
int	init_philos(t_philo **array, t_time *arg)
{
	int				i;
	pthread_mutex_t	*mutex_print;

	mutex_print = ft_calloc(1, sizeof(pthread_mutex_t));
	if (!mutex_print)
		return (-1);
	if (pthread_mutex_init(mutex_print, NULL))
	{
		free(mutex_print);
		return (-1);
	}
	i = -1;
	while (++i < arg->total_philos)
	{
		array[i]->times = arg;
		array[i]->print = mutex_print;
	}
	return (0);
}

/** PURPOSE : Link mutex with struct. */
void	link_philos_and_mutex(t_philo **array, \
pthread_mutex_t **knives, int total_philos)
{
	int	i;

	i = -1;
	while (++i < total_philos)
	{
		array[i]->left = knives[i];
		if (i != total_philos - 1)
			array[i]->right = knives[i + 1];
		else
			array[i]->right = knives[0];
	}
}
