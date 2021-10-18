/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 09:48:40 by guilmira          #+#    #+#             */
/*   Updated: 2021/10/18 15:39:25 by guilmira         ###   ########.fr       */
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

# include <sys/time.h>

/* PROGRAM OPTIONS */
# define OPT_1	5
# define OPT_2	6
# define CONVER	1000000
/* ERROR MESSAGES */
# define EX		"Error.\n"

/* COLOURS */
# define RED	"\033[0;31m"//dead
# define YELLOW	"\033[0;33m"//eat
# define BLUE	"\033[0;34m"//sleep
# define WHITE	"\033[0;37m"//thinking
# define NONE	"\033[0m"
/* MESSAGES */
# define MS		ms
# define PH		philo->index
# define KNIFE	"(%i) Philo %i has taken left fork   🗡\n"
# define KNIFER	"(%i) Philo %i has taken right fork   🗡\n"
# define EAT	YELLOW"(%i) Philo %i is eating\n"NONE
# define SLEEP	BLUE"(%i) Philo %i is sleeping\n"NONE
# define THINK	WHITE"(%i) Philo %i is thinking\n"NONE
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
	int				total_philos;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nbr_eat;
	struct timeval	init_time;
}		t_time;

/** Struct that stores philospher variables. */
typedef struct s_philo
{
	int				index;
	pthread_mutex_t	left;
	pthread_mutex_t	right;
	pthread_mutex_t	*knives;
	pthread_mutex_t	print;
	pthread_t		thread;
	t_time			*times;
}				t_philo;

/* PARSER AND ARGUMENTS */
int		parser(int argc, char *argv[]);
/* ARGUMENT READ */
t_time	*reader(int argc, char *argv[]);
/* PHILOSPHERS MANAGEMENT */
int		get_microseconds(struct timeval	init_time);
int		create_philos(t_philo **array, int total_philos);
pthread_mutex_t	*create_mutex(int total_philos);
int		assign_mutex(t_time *arg, int total_philos, pthread_mutex_t	*knives);
/* PHILOSPHERS ROUTINE */
int	create_threads(t_philo **array, int total_philos);
/* PHILOSPHERS LINKER */
void	link_philos_and_mutex(t_philo **array, \
pthread_mutex_t *knives, int total_philos);
int	init_philos(t_philo **array, t_time *arg);

/* MEMORY MANAGEMENT */
void	ft_shutdown(t_time *arg);
void	clean_argument(t_time *arg);
void	free_array_philos(t_philo **array, int total_philos);
void	mutex_destructor(pthread_mutex_t	*knives, int total_philos);
void	clean_simulation(t_philo **array, pthread_mutex_t *knives, int total_philos);
/* ACTIONS */
void	knife_l(t_philo *philo);
void	knife_r(t_philo *philo);
void	eat(t_philo *philo);
void	ft_sleep(t_philo *philo);

/* TOOLKIT */
int		ft_isspaces(int c);
size_t	ft_strlen(const char *s);
void	*ft_calloc(size_t count, size_t size);
t_bool	ft_isdigit(int c);
int		ft_atoi(const char *str);


void ft_leaks(void);

#endif
