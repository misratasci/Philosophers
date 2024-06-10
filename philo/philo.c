/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:33:09 by mitasci           #+#    #+#             */
/*   Updated: 2024/06/10 15:38:06 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_death_check(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->check_dead);
	if (ft_get_time_of_ms() - philo->last_meal > philo->table->time_to_die
		&& !philo->table->someone_died)
	{
		philo->table->someone_died = 1;
		ft_print(philo, ft_get_time_of_ms() - philo->table->start_time, "died");
		pthread_mutex_unlock(&philo->table->check_dead);
		return ;
	}
	pthread_mutex_unlock(&philo->table->check_dead);
}

void	ft_meals_check(t_philo *philo)
{
	int	all_philos_ate;
	int	i;

	pthread_mutex_lock(&philo->table->meals);
	all_philos_ate = 1;
	i = 0;
	while (i < philo->table->num_philo)
	{
		if (philo->table->philos[i]->meal_count < philo->table->must_eat
			|| philo->table->must_eat == -1)
		{
			all_philos_ate = 0;
			break ;
		}
		i++;
	}
	if (all_philos_ate && !philo->table->max_meals_eaten)
	{
		philo->table->max_meals_eaten = 1;
		pthread_mutex_unlock(&philo->table->meals);
		return ;
	}
	pthread_mutex_unlock(&philo->table->meals);
}

void	*ft_supervise(void *args)
{
	t_table	*table;

	table = (t_table *)args;
	while (table->finished == 0)
	{
		pthread_mutex_lock(&table->check_dead);
		if (table->someone_died || table->max_meals_eaten)
			table->finished = 1;
		pthread_mutex_unlock(&table->check_dead);
		ft_msleep(1);
	}
	return (NULL);
}

void	*ft_monitor(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (philo->table->finished == 0)
	{
		ft_death_check(philo);
		ft_meals_check(philo);
		ft_msleep(1);
	}
	return (NULL);
}

void	*ft_live(void *args)
{
	t_philo		*philo;
	pthread_t	monitor_thread;

	philo = (t_philo *)args;
	if (pthread_create(&monitor_thread, NULL, ft_monitor, philo) != 0)
	{
		printf("Failed to create monitor thread\n");
		return (NULL);
	}
	while (philo->table->finished == 0)
	{
		ft_eat(philo);
		if (philo->table->finished)
			break ;
		ft_sleep(philo);
		if (philo->table->finished)
			break ;
		ft_think(philo);
	}
	pthread_join(monitor_thread, NULL);
	return (NULL);
}
