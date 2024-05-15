/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessiz <sessiz@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:33:09 by sessiz            #+#    #+#             */
/*   Updated: 2024/05/15 20:23:01 by sessiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *ft_live(void *args)
{
	t_philo *philo;
	
	philo = (t_philo *)args;
	printf("I'm alive\n");
}

void *ft_take_forks(t_philo *philo)
{
	
	pthread_mutex_lock(philo->fork);
	pthread_mutex_lock(philo->fork);
}

void *ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->total);
	pthread_mutex_lock(&philo->last);
	ft_take_forks(philo);
	philo->last_meal = ft_get_time_of_ms();
	pthread_mutex_unlock(&philo->last);
	pthread_mutex_unlock(&philo->total);
}

void *ft_death_check(t_philo *philo)
{
	pthread_mutex_lock(&philo->last);
	if(ft_get_time_of_ms() - philo->last_meal > philo->time_to_die)
	{
		printf("I'm dead\n");
	}
	pthread_mutex_unlock(&philo->last);
}
