/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:51:28 by mitasci           #+#    #+#             */
/*   Updated: 2024/05/09 19:16:56 by mitasci          ###   ########.fr       */
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
	write_message(ft_itoa(get_time() - table->start_time), ft_itoa(philo->id), "has taken a fork 1");
	printf("fork1 id: %d\n", fork1->id);
	write_message(ft_itoa(get_time() - table->start_time), ft_itoa(philo->id), "has taken a fork 2");
	printf("fork2 id: %d\n", fork2->id);
}

void	ft_leave_fork(t_philo *philo, t_table table)
{
	t_fork	*fork1;
	t_fork	*fork2;

	fork1 = &(table.forks[philo->id - 1]);
	if (philo->id == 1)
		fork2 = &(table.forks[table.philo_no - 1]);
	else
		fork2 = &(table.forks[philo->id - 2]);

	pthread_mutex_unlock(&fork1->lock);
	pthread_mutex_unlock(&fork2->lock);
}

void	ft_eat(t_philo *philo)
{
	ft_take_fork(philo, philo->table);
	//write_message(ft_itoa(get_time() - table.start_time), ft_itoa(philo->id), "is eating\n");
	ft_usleep(philo->table->time_to_eat);
	ft_leave_fork(philo, *(philo->table));
}

void	ft_think(t_philo *philo, t_table table)
{
	write_message(ft_itoa(get_time() - table.start_time), ft_itoa(philo->id), "is thinking\n");
	ft_usleep(table.time_to_eat);
}

void	ft_sleep(t_philo *philo, t_table table)
{
	write_message(ft_itoa(get_time() - table.start_time), ft_itoa(philo->id), "is sleeping\n");
	ft_usleep(table.time_to_sleep);
}

void	*live(void *arg)
{
	t_philo *philo;
	philo = (t_philo *)arg;
	//printf("%s, %d living\n",ft_itoa(get_time() - philo->table->start_time) , philo->id);
	ft_eat(philo);
	return (arg);
}
