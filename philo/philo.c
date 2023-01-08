/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salatiel <salatiel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 22:54:39 by salatiel          #+#    #+#             */
/*   Updated: 2023/01/08 00:41:35 by salatiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread_test(void *arg)
{
	printf("This is a thread\n");
	sleep(3);
	printf("exiting thread\n");
	return (NULL);
}

int	main(void)
{
	pthread_t	t1;
	pthread_t	t2;

	if (pthread_create(&t1, NULL, &thread_test, NULL) == 0
		&& pthread_create(&t2, NULL, &thread_test, NULL) == 0)
	{
		pthread_join(t1, NULL);
		pthread_join(t2, NULL);
	}
	return (0);
}
