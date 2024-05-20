/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:33:09 by sessiz            #+#    #+#             */
/*   Updated: 2024/05/20 16:26:13 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *ft_live(void *args)
{
	t_philo **philos;
	
	philos = (t_philo **)args;
	printf("I'm alive\n");
	return (NULL);
}

void ft_take_forks(t_philo *philo)
{
	
	pthread_mutex_lock(philo->fork);
	pthread_mutex_lock(philo->fork);
}

void ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->total);
	pthread_mutex_lock(&philo->last);
	ft_take_forks(philo);
	philo->last_meal = ft_get_time_of_ms();
	pthread_mutex_unlock(&philo->last);
	pthread_mutex_unlock(&philo->total);
}

void ft_death_check(t_philo *philo)
{
	pthread_mutex_lock(&philo->last);
	if(ft_get_time_of_ms() - philo->last_meal > philo->time_to_die)
	{
		printf("I'm dead\n");
	}
	pthread_mutex_unlock(&philo->last);
}
