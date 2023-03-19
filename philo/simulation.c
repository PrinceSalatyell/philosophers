/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josanton <josanton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 05:23:32 by salatiel          #+#    #+#             */
/*   Updated: 2023/03/19 17:56:14 by josanton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_alive(int i)
{
	pthread_mutex_lock(&simulation()->print_mutex);
	if (!philos()[i].is_alive)
	{
		pthread_mutex_unlock(&simulation()->print_mutex);
		return (false);
	}
	pthread_mutex_unlock(&simulation()->print_mutex);
	pthread_mutex_lock(&simulation()->time_mutex);
	if (get_time() - philos()[i].last_meal > simulation()->time_to_die)
	{
		pthread_mutex_unlock(&simulation()->time_mutex);
		return (false);
	}
	pthread_mutex_unlock(&simulation()->time_mutex);
	return (true);
}

bool	all_alive(int i)
{
	pthread_mutex_lock(&simulation()->death);
	pthread_mutex_lock(&simulation()->time_mutex);
	if (simulation()->n_times && !simulation()->ensure_must_eat)
	{
		pthread_mutex_unlock(&simulation()->death);
		pthread_mutex_unlock(&simulation()->time_mutex);
		return (false);
	}
	pthread_mutex_unlock(&simulation()->time_mutex);
	while (++i < simulation()->qty)
	{
		if (!philos()[i].is_alive || !is_alive(i))
		{
			if (philos()[i].is_alive)
				death(i + 1);
			pthread_mutex_lock(&simulation()->print_mutex);
			simulation()->all_alive = false;
			pthread_mutex_unlock(&simulation()->print_mutex);
			pthread_mutex_unlock(&simulation()->death);
			return (false);
		}
	}
	pthread_mutex_unlock(&simulation()->death);
	return (true);
}

void	death(int id)
{
	long long	time;

	pthread_mutex_lock(&simulation()->print_mutex);
	time = get_time() - simulation()->start;
	philos()[id - 1].is_alive = false;
	printf("%s[%lld ms] %i is dead%s\n", RED, time, id, COLOUR_END);
	pthread_mutex_unlock(&simulation()->print_mutex);
}

int	ft_sleep(int id, bool to_eat, bool to_die)
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
		if (to_die)
			time_reference = simulation()->time_to_die;
		else
		{
			time_reference = simulation()->time_to_sleep;
			print_message("is sleeping", id, BLUE);
		}
	}
	while (passed < time_reference)
	{
		if (!is_alive(id - 1))
			return (1);
		passed = get_time() - start;
	}
	return (passed >= time_reference);
}
