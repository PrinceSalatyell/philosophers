/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salatiel <salatiel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 05:23:32 by salatiel          #+#    #+#             */
/*   Updated: 2023/03/19 07:43:42 by salatiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_alive(int i)
{
	if (!philos()[i].is_alive)
		return (false);
	if (get_time() - philos()[i].last_meal >= simulation()->time_to_die)
		return (false);
	return (true);
}

bool	all_alive(void)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&simulation()->death);
	while (++i < simulation()->qty)
	{
		if (!philos()[i].is_alive || !is_alive(i))
		{
			if (philos()[i].is_alive)
				death(i + 1);
			pthread_mutex_unlock(&simulation()->death);
			return (false);
		}
	}
	pthread_mutex_unlock(&simulation()->death);
	if (simulation()->n_times && !simulation()->ensure_must_eat)
		return (false);
	return (true);
}

void	death(int id)
{
	philos()[id - 1].is_alive = false;
	pthread_mutex_lock(&simulation()->print_mutex);
	print_message("is dead", id, RED);
	pthread_mutex_unlock(&simulation()->print_mutex);
}

int	ft_sleep(int id, bool to_eat)
{
	long long	start;
	long long	passed;
	long long	time_reference;

	start = get_time();
	passed = 0;
	if (to_eat)
		time_reference = simulation()->time_to_eat;
	else
	{
		time_reference = simulation()->time_to_sleep;
		print_message("is sleeping", id, BLUE);
	}
	while (passed < time_reference)
	{
		if (!is_alive(id - 1))
			return (1);
		passed = get_time() - start;
	}
	return (passed >= time_reference);
}
