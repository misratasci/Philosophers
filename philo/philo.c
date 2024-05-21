/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:33:09 by sessiz            #+#    #+#             */
/*   Updated: 2024/05/21 15:24:35 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <errno.h>

void ft_take_forks(t_philo *philo)
{
	
	if (philo->id % 2 == 0)
	{
		int a = pthread_mutex_lock(philo->lfork);
		printf("a %d\n", a);
			
		printf("%llu %d has taken a left fork\n", ft_get_time_of_ms() - philo->table->start_time, philo->id);
		printf("%llu %d left fork address: %p\n", ft_get_time_of_ms() - philo->table->start_time, philo->id, (philo->lfork));
		int b = pthread_mutex_lock(philo->rfork);
		printf("b %d\n", b);
		printf("%llu %d has taken a right fork\n", ft_get_time_of_ms() - philo->table->start_time, philo->id);
		printf("%llu %d right fork address: %p\n", ft_get_time_of_ms() - philo->table->start_time, philo->id, (philo->rfork));
	}
	else
	{
		int a = pthread_mutex_lock(philo->rfork);
		printf("a %d\n", a);
		printf("%llu %d has taken a right fork\n", ft_get_time_of_ms() - philo->table->start_time, philo->id);
		printf("%llu %d right fork address: %p\n", ft_get_time_of_ms() - philo->table->start_time, philo->id, (philo->rfork));
		int b = pthread_mutex_lock(philo->lfork);
		printf("b %d\n", b);
		printf("%llu %d has taken a left fork\n", ft_get_time_of_ms() - philo->table->start_time, philo->id);
		printf("%llu %d left fork address: %p\n", ft_get_time_of_ms() - philo->table->start_time, philo->id, (philo->lfork));
	}
}

void ft_leave_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->lfork);
	printf("%llu %d has bıraktı left fork\n", ft_get_time_of_ms() - philo->table->start_time, philo->id);
	printf("%llu %d left fork address: %p\n", ft_get_time_of_ms() - philo->table->start_time, philo->id, (philo->lfork));
		
	pthread_mutex_unlock(philo->rfork);
	printf("%llu %d has bıraktı right fork\n", ft_get_time_of_ms() - philo->table->start_time, philo->id);
	printf("%llu %d right fork address: %p\n", ft_get_time_of_ms() - philo->table->start_time, philo->id, (philo->lfork));
	
}

void ft_eat(t_philo *philo)
{
	//pthread_mutex_lock(&philo->total);
	//pthread_mutex_lock(&philo->last);
	ft_take_forks(philo);
	philo->last_meal = ft_get_time_of_ms();
	printf("%llu %d is eating\n", philo->last_meal - philo->table->start_time, philo->id);
	ft_msleep(philo->table->time_to_eat);
	printf("sa\n");
	ft_leave_forks(philo);
	//pthread_mutex_unlock(&philo->last);
	//pthread_mutex_unlock(&philo->total);
}

void	ft_sleep(t_philo *philo)
{
	printf("%llu %d is sleeping\n", ft_get_time_of_ms() - philo->table->start_time, philo->id);
	ft_msleep(philo->table->time_to_sleep);
}

int ft_death_check(t_philo *philo)
{
		
	//pthread_mutex_lock(&philo->last);
	if(ft_get_time_of_ms() - philo->last_meal > philo->table->time_to_die)
	{
		printf("%llu %d died\n", ft_get_time_of_ms() - philo->table->start_time, philo->id);	
		return (1);
	}
	//pthread_mutex_unlock(&philo->last);
	return (0);
}

void *ft_live(void *args)
{
	t_philo	*philo;
	
	philo = (t_philo *)args;
	//if (philo->id % 2 == 1)
	//	msleep(philo->time_to_eat);
	while (1)
	{	
		if (ft_death_check(philo))
			break;
		ft_eat(philo);
		ft_sleep(philo);
		
	}
	
	return (NULL);
}