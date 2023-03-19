/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salatiel <salatiel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 22:54:48 by salatiel          #+#    #+#             */
/*   Updated: 2023/03/19 07:43:44 by salatiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>

// COLORS

# define GREEN "\033[0;32m"
# define RED "\033[1;31m"
# define PURPLE "\033[1;35m"
# define BLUE "\033[1;36m"
# define YELLOW "\033[0;33m"
# define GREY "\033[0;40m"
# define COLOUR_END "\033[0m"

typedef struct s_simulation
{
	int				qty;
	long long		time_to_die;
	long long		time_to_sleep;
	long long		time_to_eat;
	int				n_times;
	int				ensure_must_eat;
	pthread_mutex_t	death;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	time_mutex;
	pthread_mutex_t	*forks;
	long long		start;
}	t_simulation;

typedef struct s_philo
{
	pthread_t	philosopher;
	int			id;
	long long	last_meal;
	int			times_ate;
	bool		is_alive;
	bool		is_eating;
	bool		is_sleeping;
	bool		is_thinking;
}	t_philo;

// FUNCTIONS

t_philo			*philos(void);
t_simulation	*simulation(void);
long long		ft_atoll(const char *str);
long long		get_time(void);
void			print_message(char *message, int id, char *color);
void			cleanup(void);
void			death(int id);
bool			all_alive(void);
bool			is_alive(int i);
int				ft_sleep(int id, bool to_eat);
bool			eat(int id);

#endif