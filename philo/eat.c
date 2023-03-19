/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salatiel <salatiel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 05:07:29 by salatiel          #+#    #+#             */
/*   Updated: 2023/03/19 07:43:37 by salatiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eating(int id)
{
	pthread_mutex_lock(&simulation()->time_mutex);
	philos()[id - 1].last_meal = get_time();
	pthread_mutex_unlock(&simulation()->time_mutex);
	print_message("is eating", id, GREEN);
	ft_sleep(id, true);
	if (++philos()[id - 1].times_ate == simulation()->n_times)
	{
		pthread_mutex_lock(&simulation()->time_mutex);
		simulation()->ensure_must_eat--;
		pthread_mutex_unlock(&simulation()->time_mutex);
	}
}

void	which_fork(int id, int *first_fork, int *second_fork)
{
	int	tmp;

	if (id % 2 == 0)
	{
		*first_fork = (id - 2 + simulation()->qty) % simulation()->qty;
		*second_fork = id - 1;
	}
	else
	{
		*first_fork = id - 1;
		*second_fork = (id % simulation()->qty);
	}

	if (id == 1)
	{
		*first_fork = simulation()->qty - 1;
		*second_fork = 0;
	}

	if (*first_fork > *second_fork)
	{
		tmp = *first_fork;
		*first_fork = *second_fork;
		*second_fork = tmp;
	}
}

bool	eat(int id)
{
	int	forks[2];

	which_fork(id, &forks[0], &forks[1]);
	pthread_mutex_lock(&simulation()->forks[forks[0]]);
	if (!is_alive(id - 1))
	{
		pthread_mutex_unlock(&simulation()->forks[forks[0]]);
		return (false);
	}
	print_message("has taken first fork", id, PURPLE);
	pthread_mutex_lock(&simulation()->forks[forks[1]]);
	if (!is_alive(id - 1))
	{
		pthread_mutex_unlock(&simulation()->forks[forks[1]]);
		pthread_mutex_unlock(&simulation()->forks[forks[0]]);
		return (false);
	}
	print_message("has taken second fork", id, PURPLE);
	eating(id);
	pthread_mutex_unlock(&simulation()->forks[forks[1]]);
	pthread_mutex_unlock(&simulation()->forks[forks[0]]);
	return (true);
}
