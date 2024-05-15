/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessiz <sessiz@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:28:02 by sessiz            #+#    #+#             */
/*   Updated: 2024/05/15 19:37:20 by sessiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	table_init(t_philo *philo, int ac, char **av, int *check_dead)
{
	int	i;

	i = -1;
	while (++i < ft_atoi(av[1]))
	{
		philo[i].id = i + 1;
		philo[i].num_of_philo = ft_atoi(av[1]);
		philo[i].time_to_die = ft_atoi(av[2]);
		philo[i].time_to_eat = ft_atoi(av[3]);
		philo[i].time_to_sleep = ft_atoi(av[4]);
		if (ac == 6)
			philo[i].must_eat = ft_atoi(av[5]);
		else
			philo[i].must_eat = -1;
		philo[i].last_meal = ft_get_time_of_ms();
		philo[i].start_time = ft_get_time_of_ms();
		philo[i].num_of_meals = 0;
		philo[i].check_dead = check_dead;
		pthread_mutex_init(&philo[i].last, NULL);
		pthread_mutex_init(&philo[i].total, NULL);
	}
	return (0);
}

void	*table_create(t_philo *philo)
{
	int i;

	i = 0;
	while (i < philo->num_of_philo)
	{
		pthread_create(&philo[i].thread, NULL, ft_live, &philo[i]);
		usleep(60);
		i++;
	}
	i = 0;
	
	while (i < philo->num_of_philo)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
}

void	*table_destroy(t_philo *philo, pthread_mutex_t *forks)
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
	pthread_mutex_destroy(&philo->death);
}
