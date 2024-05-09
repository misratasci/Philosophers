/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:51:28 by mitasci           #+#    #+#             */
/*   Updated: 2024/05/09 17:33:09 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_take_fork(t_philo *philo, t_table table)
{
	t_fork	*fork1;
	t_fork	*fork2;

	fork1 = &(table.forks[philo->id]);
	if (philo->id == 0)
		fork2 = &(table.forks[table.philo_no - 1]);
	else
		fork2 = &(table.forks[philo->id - 1]);

	pthread_mutex_lock(&fork1->lock);
	printf("couldn't lock\n");
	pthread_mutex_lock(&fork2->lock);
	printf("couldn't lock\n");
}

void	ft_leave_fork(t_philo *philo, t_table table)
{
	t_fork	*fork1;
	t_fork	*fork2;

	fork1 = &(table.forks[philo->id]);
	if (philo->id == 0)
		fork2 = &(table.forks[table.philo_no - 1]);
	else
		fork2 = &(table.forks[philo->id - 1]);

	pthread_mutex_unlock(&fork1->lock);
	pthread_mutex_unlock(&fork2->lock);
}

void	ft_eat(t_philo *philo, t_table table)
{
	write_message(ft_itoa(get_time() - table.start_time), ft_itoa(philo->id), "is eating\n");
	ft_usleep(table.time_to_eat);
}

void	ft_think(t_philo *philo, t_table table)
{
	write_message(ft_itoa(get_time() - table.start_time), ft_itoa(philo->id), "is thinking\n");
	//ft_usleep(ne kadar düşünecek daha bilmiyoruz);
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
	ft_take_fork(philo, *(philo->table));
	ft_eat(philo, *(philo->table));
	ft_leave_fork(philo, *(philo->table));
	return (arg);
}
