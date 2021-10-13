/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 09:48:40 by guilmira          #+#    #+#             */
/*   Updated: 2021/10/13 10:06:52 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* LIBS */
# include <stdio.h>

/** Struct that stores single direction linked list. */
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/** PURPOSE : struct of a vector, 2D representation. */
typedef struct s_vector
{
	int	x;
	int	y;
}		t_vector;

/* TOOLKIT */
void	*ft_calloc(size_t count, size_t size);

#endif
