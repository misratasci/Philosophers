/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:33:09 by mitasci           #+#    #+#             */
/*   Updated: 2024/08/04 19:37:53 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_death_check(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->check_dead);
	if (ft_get_time_of_ms() - philo->last_meal > philo->table->time_to_die
		&& philo->table->someone_died == 0)
	{
		philo->table->someone_died = 1;
		pthread_mutex_unlock(&philo->table->check_dead);
		ft_print(philo->table, ft_get_time_of_ms() - philo->table->start_time,
			philo->id, "died");
		return (1);
	}
	pthread_mutex_unlock(&philo->table->check_dead);
	return (0);
}

int	ft_meals_check(t_philo *philo)
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
		return (1);
	}
	pthread_mutex_unlock(&philo->table->meals);
	return (0);
}

void	*ft_supervise(void *args)
{
	t_table	*table;
	int		i;
	int		fin;

	table = (t_table *)args;
	i = 0;
	fin = 0;
	while (fin == 0 && table->philos[i])
	{
		fin = table->someone_died + table->max_meals_eaten;
		pthread_mutex_lock(&table->fin);
		table->finished = fin;
		pthread_mutex_unlock(&table->fin);
		ft_death_check(table->philos[i]);
		ft_meals_check(table->philos[i]);
		i++;
		if (i == table->num_philo)
			i = 0;
		usleep(100);
	}
	return (NULL);
}

void	*ft_live(void *args)
{
	t_philo		*philo;
	int			fin;

	philo = (t_philo *)args;
	fin = 0;
	while (fin == 0)
	{
		pthread_mutex_lock(&philo->table->fin);
		fin = philo->table->finished;
		pthread_mutex_unlock(&philo->table->fin);
		if (fin)
			break ;
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (NULL);
}
