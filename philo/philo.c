/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salatiel <salatiel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 22:54:39 by salatiel          #+#    #+#             */
/*   Updated: 2023/03/18 17:14:59 by salatiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread_test(void *arg)
{
	int	i;

	i = *(int *)arg;
	philos()[i - 1].last_meal = get_time();
	while (true)
	{
		if (all_alive())
			ft_sleep(i - 1);
		else
			break ;
	}
	return (NULL);
}

void	start(void)
{
	int	i;
	int	qty;

	i = -1;
	qty = simulation()->qty;
	while (++i < qty)
	{
		philos()[i].is_alive = true;
		philos()[i].is_eating = false;
		philos()[i].is_sleeping = false;
		philos()[i].is_thinking = false;
		philos()[i].id = i + 1;
		philos()[i].last_meal = get_time();
		philos()[i].times_ate = 0;
	}
}

void	init(int i)
{
	philos();
	start();
	pthread_mutex_init(&simulation()->death, NULL);
	pthread_mutex_init(&simulation()->print_mutex, NULL);
	while (++i < simulation()->qty)
	{
		if (pthread_create(&philos()[i].philosopher, \
		NULL, thread_test, &philos()[i].id))
			return ;
		else
			pthread_mutex_init(&simulation()->forks[i], NULL);
	}
	i = -1;
	while (++i < simulation()->qty)
	{
		if (pthread_join(philos()[i].philosopher, NULL))
			return ;
	}
	cleanup();
}

bool	parsing(int argc, char **argv)
{
	simulation()->start = get_time();
	simulation()->qty = (int) ft_atoll(argv[1]);
	simulation()->time_to_die = ft_atoll(argv[2]);
	simulation()->time_to_eat = ft_atoll(argv[3]);
	simulation()->time_to_sleep = ft_atoll(argv[4]);
	simulation()->forks = malloc(sizeof(pthread_mutex_t) * simulation()->qty);
	if (argc == 6)
		simulation()->n_times = (int) ft_atoll(argv[5]);
	else
		simulation()->n_times = 0;
	if (simulation()->qty <= 0 || simulation()->time_to_die <= 0 \
	|| simulation()->time_to_eat <= 0 || simulation()->time_to_sleep <= 0 \
	|| (simulation()->n_times && simulation()->n_times < 0))
	{
		printf("invalid input. Positive numbers only, please\n");
		return (false);
	}
	return (true);
}

int	main(int argc, char **argv)
{
	if (argc == 5 || argc == 6)
	{
		if (!parsing(argc, argv))
			return (0);
		init(-1);
	}
	else
	{
		printf("Please provide the following values in this exact order:\n");
		printf("\t%sNumber of Philosophers%s\n", YELLOW, COLOUR_END);
		printf("\t%sTime to Die%s\n", YELLOW, COLOUR_END);
		printf("\t%sTime to Eat%s\n", YELLOW, COLOUR_END);
		printf("\t%sTime to Sleep%s\n", YELLOW, COLOUR_END);
		printf("\t%sNumber of times each philosopher must eat (optional)%s\n" \
		, YELLOW, COLOUR_END);
		return (1);
	}
	return (0);
}
