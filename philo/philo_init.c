/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:28:02 by sessiz            #+#    #+#             */
/*   Updated: 2024/05/20 20:04:08 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	table_init(t_philo **philos, int ac, char **av, pthread_mutex_t *forks)
{
	int	i;
	int	len;
	pthread_mutex_t	*last;

	last = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	len = ft_atoi(av[1]);
	i = -1;
	while (++i < len)
	{
		philos[i] = (t_philo *)malloc(sizeof(t_philo) * len);
		if (!philos[i])
		{
			printf("Failed to allocate philos\n");
			return ;
		}
		philos[i]->id = i + 1;
		philos[i]->num_of_philo = len;
		philos[i]->time_to_die = ft_atoi(av[2]);
		philos[i]->time_to_eat = ft_atoi(av[3]);
		philos[i]->time_to_sleep = ft_atoi(av[4]);
		if (ac == 6)
			philos[i]->must_eat = ft_atoi(av[5]);
		else
			philos[i]->must_eat = -1;
		philos[i]->last_meal = ft_get_time_of_ms();
		philos[i]->start_time = ft_get_time_of_ms();
		philos[i]->num_of_meals = 0;
		philos[i]->check_dead = 0;
		//philos[i]->last = last;
		//pthread_mutex_init(last, NULL);
		//pthread_mutex_init(&philos[i]->total, NULL);
		philos[i]->lfork = &forks[i];
		philos[i]->rfork = &forks[(i + 1) % len];
		pthread_mutex_init(&forks[i], NULL);
		//int b =pthread_mutex_lock(&forks[i]);
		//printf("%p %d %d\n", &forks[i], a, b);
	}
}

void	table_create(t_philo **philos)
{
	int i;

	i = 0;
	while (i < philos[0]->num_of_philo)
	{
		pthread_create(&philos[i]->thread, NULL, ft_live, philos[i]);
		//usleep(60);
		i++;
	}
	
	i = 0;
	while (i < philos[0]->num_of_philo)
	{
		pthread_join(philos[i]->thread, NULL);
		i++;
	}
	
}

void	table_destroy(t_philo **philos, pthread_mutex_t *forks)
{
	int i;
	/*
	i = 0;
	while (i < philos[0]->num_of_philo)
	{
		pthread_mutex_destroy(&philos[i]->last);
		pthread_mutex_destroy(&philos[i]->total);
		i++;
	}
	*/
	i = 0;
	while (i < philos[0]->num_of_philo)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	//pthread_mutex_destroy(philos->death);
}
