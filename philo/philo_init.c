/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:28:02 by mitasci           #+#    #+#             */
/*   Updated: 2024/06/10 15:45:05 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	table_init(t_table	*table, int ac, char **av)
{
	table->num_philo = ft_atoi(av[1]);
	table->philos = (t_philo **)malloc(sizeof(t_philo *) * table->num_philo);
	table->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* table->num_philo);
	if (!table->philos || !table->forks)
		return ;
	if (ac == 6)
		table->must_eat = ft_atoi(av[5]);
	else
		table->must_eat = -1;
	pthread_mutex_init(&table->check_dead, NULL);
	pthread_mutex_init(&table->meals, NULL);
	pthread_mutex_init(&table->print, NULL);
	table->start_time = ft_get_time_of_ms();
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	table->someone_died = 0;
	table->max_meals_eaten = 0;
	table->finished = 0;
	philo_init(table);
}

void	philo_init(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philo)
	{
		table->philos[i] = (t_philo *)malloc(sizeof(t_philo));
		table->philos[i]->id = i + 1;
		table->philos[i]->last_meal = table->start_time;
		table->philos[i]->lfork = &table->forks[i];
		table->philos[i]->rfork = &table->forks[(i + 1) % table->num_philo];
		table->philos[i]->table = table;
		table->philos[i]->meal_count = 0;
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
}

void	create_philos(t_table *table)
{
	int	i;

	pthread_create(&table->supervisor, NULL, ft_supervise, table);
	i = 0;
	while (i < table->num_philo)
	{
		pthread_create(&table->philos[i]->thread, NULL,
			ft_live, table->philos[i]);
		usleep(100);
		i++;
	}
	if (table->num_philo == 1)
	{
		pthread_detach(table->philos[0]->thread);
		while (table->someone_died == 0)
			ft_msleep(1);
		return ;
	}
	i = 0;
	while (i < table->num_philo)
	{
		pthread_join(table->philos[i]->thread, NULL);
		i++;
	}
	pthread_join(table->supervisor, NULL);
}

void	table_destroy(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philo)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&table->check_dead);
	pthread_mutex_destroy(&table->meals);
	pthread_mutex_destroy(&table->print);
}
