/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:34:52 by mitasci           #+#    #+#             */
/*   Updated: 2024/08/04 18:19:25 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->lfork);
	printf("%llu %d %s\n", ft_get_time_of_ms() - philo->table->start_time, philo->id, 
		"has taken a fork");
	pthread_mutex_lock(philo->rfork);
	printf("%llu %d %s\n", ft_get_time_of_ms() - philo->table->start_time, philo->id,
		"has taken a fork");
}

void	ft_leave_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->rfork);
	pthread_mutex_unlock(philo->lfork);
}

void	ft_eat(t_philo *philo)
{
	ft_take_forks(philo);
	pthread_mutex_lock(&philo->table->check_dead);
	philo->last_meal = ft_get_time_of_ms();
	pthread_mutex_unlock(&philo->table->check_dead);
	pthread_mutex_lock(&philo->table->meals);
	philo->meal_count++;
	pthread_mutex_unlock(&philo->table->meals);
	printf("%llu %d %s\n", philo->last_meal - philo->table->start_time, philo->id, "is eating");
	ft_msleep(philo->table->time_to_eat);
	ft_leave_forks(philo);
}

void	ft_sleep(t_philo *philo)
{
	printf("%llu %d %s\n", ft_get_time_of_ms() - philo->table->start_time, philo->id, 
		"is sleeping");
	ft_msleep(philo->table->time_to_sleep);
}

void	ft_think(t_philo *philo)
{
	printf("%llu %d %s\n", ft_get_time_of_ms() - philo->table->start_time, philo->id, 
		"is thinking");
}
