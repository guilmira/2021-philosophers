/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 09:48:40 by guilmira          #+#    #+#             */
/*   Updated: 2021/10/15 16:16:10 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* LIBS */
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <string.h>

/* PROGRAM OPTIONS */
# define OPT_1	5
# define OPT_2	6

/* ERROR MESSAGES */
# define EX		"Error.\n"

/* COLOURS */
# define RED	"\033[0;31m"//dead
# define YELLOW	"\033[0;33m"//eat
# define BLUE	"\033[0;34m"//sleep
# define WHITE	"\033[0;37m"//thinking
# define NONE	"\033[0m"
/* MESSAGES */
# define MS		0
# define PH		philo->index
# define KNIFE	"(%i) Philo %i has taken a fork   🗡\n", MS, PH
# define EAT	YELLOW"(%i) Philo %i is eating\n"NONE, MS, PH
# define SLEEP	BLUE"(%i) Philo %i is sleeping\n"NONE, MS, PH
# define THINK	WHITE"(%i) Philo %i is thinking\n"NONE, MS, PH
# define DIED	RED"(%i) Philo %i died\n"NONE, MS, PH

typedef int	t_bool;

/** Struct that stores single direction linked list. */
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/** Struct of a vector, 2D representation. */
typedef struct s_vector
{
	int	x;
	int	y;
}		t_vector;

/** Struct that stores argument times. */
typedef struct s_times
{
	int	total_philos;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	fifht_argument;
	int	nbr_eat;
}		t_time;

/** Struct that stores philospher variables. */
typedef struct s_philo
{
	int			index;
	int			time_ate;
	pthread_t	thread;
}				t_philo;

/* PARSER AND ARGUMENTS */
int	parser(int argc, char *argv[]);
/* TOOLKIT */
int	ft_isspaces(int c);
size_t	ft_strlen(const char *s);
void	*ft_calloc(size_t count, size_t size);
t_bool	ft_isdigit(int c);
int	ft_atoi(const char *str);
/* MEMORY MANAGEMENT */
void	full_shutdown(t_time *arg);

/* ARGUMENT READ */
t_time	*reader(int argc, char *argv[]);

#endif
