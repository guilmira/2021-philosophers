/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1reader.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 15:59:26 by guilmira          #+#    #+#             */
/*   Updated: 2021/10/15 18:32:44 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/** PURPOSE : Generates struct argument.
 * 1. Allocates memory. Notice that function parser already
 * has checked that argument are either total 5 or 6.
 * 2. Reads value of arguments. */
t_time	*reader(int argc, char *argv[])
{
	t_time	*arg;

	arg = NULL;
	if (argc == OPT_1)
		arg = ft_calloc(1, sizeof(t_time));
	else if (argc == OPT_2)
		arg = ft_calloc(1, sizeof(t_time));
	if (!arg)
		return (NULL);
	arg->total_philos = ft_atoi(argv[1]);
	arg->time_die = ft_atoi(argv[2]);
	arg->time_eat = ft_atoi(argv[3]);
	arg->time_sleep = ft_atoi(argv[4]);
	arg->nbr_eat = -1;
	if (argc == OPT_2)
		arg->nbr_eat = ft_atoi(argv[5]);
	arg->init_time.tv_sec = 0;
	arg->init_time.tv_usec = 0;
	arg->array = NULL;
	return (arg);
}
