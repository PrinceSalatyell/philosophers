/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josanton <josanton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 03:23:18 by salatiel          #+#    #+#             */
/*   Updated: 2023/03/19 17:46:47 by josanton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*philos(void)
{
	static t_philo	*philos;

	if (!philos)
		philos = malloc(sizeof(t_philo) * simulation()->qty);
	return (philos);
}

t_simulation	*simulation(void)
{
	static t_simulation	simulation;

	return (&simulation);
}

void	cleanup(void)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&simulation()->death);
	pthread_mutex_destroy(&simulation()->print_mutex);
	while (++i < simulation()->qty)
		pthread_mutex_destroy(&simulation()->forks[i]);
	if (simulation()->forks)
		free(simulation()->forks);
	if (philos())
		free(philos());
}

bool	do_one(void)
{
	long long	time;

	time = get_time() - simulation()->start;
	if (simulation()->qty != 1)
		return (false);
	printf("%s[%lld ms] 1 has taken first fork%s\n", PURPLE, time, COLOUR_END);
	ft_sleep(1, false, true);
	time = get_time() - simulation()->start;
	printf("%s[%lld ms] %i is dead%s\n", RED, time, 1, COLOUR_END);
	return (true);
}
