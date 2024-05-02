/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:51:28 by mitasci           #+#    #+#             */
/*   Updated: 2024/05/02 20:36:32 by mitasci          ###   ########.fr       */
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

	fork1->is_being_used = 1;
	fork2->is_being_used = 1;
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
	if (check_forks(*philo, *(philo->table)))
		ft_eat(philo, *(philo->table));
	return (arg);
}

int	check_forks(t_philo philo, t_table table)
{
	int i;
	t_fork	*forks;

	forks = table.forks;
	i = 0;
	//sol
	if(forks[philo.id].is_being_used == 0)
		i++;
	//sağ
	if (philo.id != 0)
	{
		if(forks[philo.id - 1].is_being_used == 0)
			i++;
	}
	else if (philo.id == 0)
	{
		if(forks[table.philo_no - 1].is_being_used == 0)
		i++;
	}
	/*
	if(i==2)
		printf("%d yemek yiyebilir\n",philo.id);
		*/
	return(i == 2);
}