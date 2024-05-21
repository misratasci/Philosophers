/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:33:09 by sessiz            #+#    #+#             */
/*   Updated: 2024/05/21 16:22:30 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_death_check(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->check_dead);
	if(ft_get_time_of_ms() - philo->last_meal > philo->table->time_to_die)
	{
		printf("%llu %d died\n", ft_get_time_of_ms() - philo->table->start_time, philo->id);	
		return (1);
	}
	pthread_mutex_unlock(&philo->table->check_dead);
	return (0);
}

void ft_take_forks(t_philo *philo)
{
	if (ft_death_check(philo))
		return ;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->lfork);
		printf("%llu %d has taken a fork\n", ft_get_time_of_ms() - philo->table->start_time, philo->id);
		pthread_mutex_lock(philo->rfork);
		printf("%llu %d has taken a fork\n", ft_get_time_of_ms() - philo->table->start_time, philo->id);
	}
	else
	{
		pthread_mutex_lock(philo->rfork);
		printf("%llu %d has taken a fork\n", ft_get_time_of_ms() - philo->table->start_time, philo->id);
		pthread_mutex_lock(philo->lfork);
		printf("%llu %d has taken a fork\n", ft_get_time_of_ms() - philo->table->start_time, philo->id);
	}
}

void ft_leave_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->lfork);	
	pthread_mutex_unlock(philo->rfork);
}

void ft_eat(t_philo *philo)
{
	ft_take_forks(philo);
	if (ft_death_check(philo))
	{
		ft_leave_forks(philo);
		return ;
	}
	philo->last_meal = ft_get_time_of_ms();
	printf("%llu %d is eating\n", philo->last_meal - philo->table->start_time, philo->id);
	ft_msleep(philo->table->time_to_eat);
	ft_leave_forks(philo);
}

void	ft_sleep(t_philo *philo)
{
	if (ft_death_check(philo))
		return ;
	printf("%llu %d is sleeping\n", ft_get_time_of_ms() - philo->table->start_time, philo->id);
	ft_msleep(philo->table->time_to_sleep);
}

void	ft_think(t_philo *philo)
{
	if (ft_death_check(philo))
		return ;
	printf("%llu %d is thinking\n", ft_get_time_of_ms() - philo->table->start_time, philo->id);
	ft_msleep(1);
}


void *ft_live(void *args)
{
	t_philo	*philo;
	
	philo = (t_philo *)args;
	while (1)
	{	
		if (ft_death_check(philo))
			break;
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	pthread_mutex_unlock(&philo->table->check_dead);
	return (NULL);
}