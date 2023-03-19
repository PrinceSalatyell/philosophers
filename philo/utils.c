/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salatiel <salatiel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 03:23:18 by salatiel          #+#    #+#             */
/*   Updated: 2023/03/19 07:43:39 by salatiel         ###   ########.fr       */
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
