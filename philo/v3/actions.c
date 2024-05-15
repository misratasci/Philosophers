/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessiz <sessiz@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:51:28 by mitasci           #+#    #+#             */
/*   Updated: 2024/05/14 20:52:34 by sessiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_take_fork(t_philo *philo, t_table *table)
{
	t_fork	*fork1;
	t_fork	*fork2;

	fork1 = &(table->forks[philo->id - 1]);
	if (philo->id == 1)
		fork2 = &(table->forks[table->philo_no - 1]);
	else
		fork2 = &(table->forks[philo->id - 2]);
	pthread_mutex_lock(&fork1->lock);
	pthread_mutex_lock(&fork2->lock);
}

void	ft_leave_fork(t_philo *philo, t_table *table)
{
	t_fork	*fork1;
	t_fork	*fork2;

	fork1 = &(table->forks[philo->id - 1]);
	if (philo->id == 1)
		fork2 = &(table->forks[table->philo_no - 1]);
	else
		fork2 = &(table->forks[philo->id - 2]);

	pthread_mutex_unlock(&fork1->lock);
	pthread_mutex_unlock(&fork2->lock);
}

void	ft_eat(t_philo *philo)
{
	if (philo->table->philo_die != 1)
	{
		pthread_mutex_lock(&philo->table->deadlock);
		ft_take_fork(philo, philo->table);
		pthread_mutex_lock(&philo->lock);
		if (philo->table->philo_die != 1)
			write_message(ft_itoa(get_time() - philo->table->start_time), ft_itoa(philo->id), "is eating\n");
		ft_usleep(philo->table->time_to_eat);
		philo->eat_count++;
		philo->last_eat = get_time();
		philo->eating = 1;
		pthread_mutex_unlock(&philo->lock);
		pthread_mutex_unlock(&philo->table->deadlock);
		ft_leave_fork(philo, philo->table);
		ft_sleep(philo, *philo->table);
	}
}

void	ft_think(t_philo *philo, t_table table)
{
	write_message(ft_itoa(get_time() - table.start_time), ft_itoa(philo->id), "is thinking\n");
	ft_usleep(table.time_to_eat);
}

void	ft_sleep(t_philo *philo, t_table table)
{
	if (philo->table->philo_die != 1)
	{
	pthread_mutex_lock(&philo->table->deadlock);
	if (philo->table->philo_die != 1)
	{
		write_message(ft_itoa(get_time() - table.start_time), ft_itoa(philo->id), "is sleeping\n");
		ft_usleep(table.time_to_sleep);
	}
	pthread_mutex_unlock(&philo->table->deadlock);
	}
}

void	dead_check(t_philo *philo)
{
	//pthread_mutex_lock(&philo->lock);
	int lasteat = get_time() - philo->last_eat;
	if (lasteat >= philo->table->time_to_die)
	{
		if(philo->table->philo_die != 1)
			write_message(ft_itoa(get_time() - philo->table->start_time), ft_itoa(philo->id), "died\n"); //eğer ölen threadin die 1 ise threadler destroy edilmeli
		//printf("philo %d died\n", philo->id);
		philo->table->philo_die = 1;
	}
	
	//pthread_mutex_unlock(&philo->lock);
}

void	*live(void *arg)
{
	t_philo *philo;
	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(200);
	while (philo->table->philo_die == 0)
	{
		pthread_mutex_lock(&philo->table->deadlock);
		dead_check(philo);
		if(philo->table->philo_die == 1)
		{
			pthread_mutex_unlock(&philo->table->deadlock);
			break;
		}
		pthread_mutex_unlock(&philo->table->deadlock);
		//if(philo->eat_count == 0)
			ft_eat(philo);
		// else
		// 	break;
	}
	//philo->eating = 0;
	return (arg);
}
