/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:34:52 by mitasci           #+#    #+#             */
/*   Updated: 2024/06/10 15:35:51 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->lfork);
	ft_print(philo, ft_get_time_of_ms() - philo->table->start_time,
		"has taken a fork");
	pthread_mutex_lock(philo->rfork);
	ft_print(philo, ft_get_time_of_ms() - philo->table->start_time,
		"has taken a fork");
}

void	ft_leave_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->lfork);
	pthread_mutex_unlock(philo->rfork);
}

void	ft_eat(t_philo *philo)
{
	ft_take_forks(philo);
	philo->last_meal = ft_get_time_of_ms();
	ft_print(philo, philo->last_meal - philo->table->start_time, "is eating");
	philo->meal_count++;
	ft_msleep(philo->table->time_to_eat);
	ft_leave_forks(philo);
}

void	ft_sleep(t_philo *philo)
{
	ft_print(philo, ft_get_time_of_ms() - philo->table->start_time,
		"is sleeping");
	ft_msleep(philo->table->time_to_sleep);
}

void	ft_think(t_philo *philo)
{
	ft_print(philo, ft_get_time_of_ms() - philo->table->start_time,
		"is thinking");
}
