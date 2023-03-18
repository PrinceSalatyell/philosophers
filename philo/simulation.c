/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salatiel <salatiel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 05:23:32 by salatiel          #+#    #+#             */
/*   Updated: 2023/03/18 17:19:37 by salatiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_alive(int id)
{
	if (!philos()[id - 1].is_alive)
		return (false);
	if (get_time() - philos()[id - 1].last_meal >= simulation()->time_to_die)
	{
		pthread_mutex_lock(&simulation()->death);
		death(id);
		pthread_mutex_unlock(&simulation()->death);
		return (false);
	}
	return (true);
}

bool	all_alive(void)
{
	int	i;

	i = -1;
	while (++i < simulation()->qty)
		if (!is_alive(i + 1))
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

int	ft_sleep(int id)
{
	long long	start;
	long long	passed;

	start = get_time();
	passed = 0;
	while (passed < simulation()->time_to_sleep)
	{
		if (!is_alive(id))
			return (1);
		passed = get_time() - start;
	}
	return (passed >= simulation()->time_to_sleep);
}
