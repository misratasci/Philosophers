/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:33:09 by mitasci           #+#    #+#             */
/*   Updated: 2024/05/30 13:50:16 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_death_check(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->check_dead);
	if(ft_get_time_of_ms() - philo->last_meal > philo->table->time_to_die && !philo->table->someone_died)
	{
		philo->table->someone_died = 1;
		printf("%llu %d died\n", ft_get_time_of_ms() - philo->table->start_time, philo->id);
		pthread_mutex_unlock(&philo->table->check_dead);
		return ;
	}
	pthread_mutex_unlock(&philo->table->check_dead);
}

void ft_take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->check_dead);
	if (philo->table->someone_died)
	{
		pthread_mutex_unlock(&philo->table->check_dead);
		return ;
	}
	pthread_mutex_unlock(&philo->table->check_dead);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->lfork);
		printf("%llu %d has taken a fork\n", ft_get_time_of_ms() - philo->table->start_time, philo->id);
		pthread_mutex_lock(&philo->table->check_dead);
		if (philo->table->someone_died)
		{
			pthread_mutex_unlock(&philo->table->check_dead);
			pthread_mutex_unlock(philo->lfork);
			return ;
		}
		pthread_mutex_unlock(&philo->table->check_dead);
		pthread_mutex_lock(philo->rfork);
		printf("%llu %d has taken a fork\n", ft_get_time_of_ms() - philo->table->start_time, philo->id);
	}
	else
	{
		pthread_mutex_lock(philo->rfork);
		printf("%llu %d has taken a fork\n", ft_get_time_of_ms() - philo->table->start_time, philo->id);
		pthread_mutex_lock(&philo->table->check_dead);
		if (philo->table->someone_died)
		{
			pthread_mutex_unlock(&philo->table->check_dead);
			pthread_mutex_unlock(philo->rfork);
			return ;
		}
		pthread_mutex_unlock(&philo->table->check_dead);
		pthread_mutex_lock(philo->lfork);
		printf("%llu %d has taken a fork\n", ft_get_time_of_ms() - philo->table->start_time, philo->id);
	}
	return ;
}

void ft_leave_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->lfork);	
	pthread_mutex_unlock(philo->rfork);
}

void ft_eat(t_philo *philo)
{
	ft_death_check(philo);
	pthread_mutex_lock(&philo->table->check_dead);
	if (philo->table->someone_died)
	{
		pthread_mutex_unlock(&philo->table->check_dead);
		return ;
	}
	pthread_mutex_unlock(&philo->table->check_dead);
	ft_take_forks(philo);
	philo->last_meal = ft_get_time_of_ms();
	printf("%llu %d is eating\n", philo->last_meal - philo->table->start_time, philo->id);
	ft_msleep(philo->table->time_to_eat);
	ft_leave_forks(philo);
}

void	ft_sleep(t_philo *philo)
{
	ft_death_check(philo);
	pthread_mutex_lock(&philo->table->check_dead);
	if (philo->table->someone_died)
	{
		pthread_mutex_unlock(&philo->table->check_dead);
		return ;
	}
	pthread_mutex_unlock(&philo->table->check_dead);
	printf("%llu %d is sleeping\n", ft_get_time_of_ms() - philo->table->start_time, philo->id);
	ft_msleep(philo->table->time_to_sleep);
}

void	ft_think(t_philo *philo)
{
	ft_death_check(philo);
	pthread_mutex_lock(&philo->table->check_dead);
	if (philo->table->someone_died)
	{
		pthread_mutex_unlock(&philo->table->check_dead);
		return ;
	}
	pthread_mutex_unlock(&philo->table->check_dead);
	printf("%llu %d is thinking\n", ft_get_time_of_ms() - philo->table->start_time, philo->id);
}

void *ft_live(void *args)
{
	t_philo	*philo;
	
	philo = (t_philo *)args;
	while (!philo->table->someone_died)
	{	
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (NULL);
}