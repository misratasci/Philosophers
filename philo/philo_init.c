/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:28:02 by sessiz            #+#    #+#             */
/*   Updated: 2024/05/20 16:26:34 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	table_init(t_philo **philos, int ac, char **av)
{
	int	i;
	int	len;

	len = ft_atoi(av[1]);
	i = -1;
	while (++i < len)
	{
		philos[i] = (t_philo *)malloc(sizeof(t_philo) * len);
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
		pthread_mutex_init(&philos[i]->last, NULL);
		pthread_mutex_init(&philos[i]->total, NULL);
	}
}

void	table_create(t_philo **philos)
{
	int i;

	i = 0;
	while (i < philos[0]->num_of_philo)
	{
		pthread_create(&philos[i]->thread, NULL, ft_live, philos);
		usleep(60);
		i++;
	}
	/*
	i = 0;
	while (i < philo->num_of_philo)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	*/
}

void	table_destroy(t_philo *philo, pthread_mutex_t *forks)
{
	int i;

	i = 0;
	while (i < philo->num_of_philo)
	{
		pthread_mutex_destroy(&philo[i].last);
		pthread_mutex_destroy(&philo[i].total);
		i++;
	}
	i = 0;
	while (i < philo->num_of_philo)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	pthread_mutex_destroy(philo->death);
}
