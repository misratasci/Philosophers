/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:28:02 by sessiz            #+#    #+#             */
/*   Updated: 2024/05/21 15:29:05 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	table_init(t_table	*table, int ac, char **av)
{
	int	i;
	table->num_philo = ft_atoi(av[1]);
	table->philos = (t_philo **)malloc(sizeof(t_philo *) * table->num_philo);
	table->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * table->num_philo);
	if (!table->philos || !table->forks)
	{
		printf("Failed to allocate\n");
		return ;
	}
	table->num_of_meals = 0;
	if (ac == 6)
		table->must_eat = ft_atoi(av[5]);
	else
		table->must_eat = -1;
	pthread_mutex_init(&table->check_dead, NULL);
	table->start_time = ft_get_time_of_ms();
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	i = -1;
	while (++i < table->num_philo)
	{
		philo_init(table, i);
		pthread_mutex_init(&table->forks[i], NULL);
	}
}

void	philo_init(t_table *table, int i)
{
	table->philos[i] = (t_philo *)malloc(sizeof(t_philo));
	table->philos[i]->id = i + 1;
	table->philos[i]->last_meal = table->start_time;
	table->philos[i]->lfork = &table->forks[i];
	table->philos[i]->rfork = &table->forks[(i + 1) % table->num_philo];
	table->philos[i]->table = table;
}

void	create_philos(t_table *table)
{
	int i;

	i = 0;
	while (i < table->num_philo)
	{
		pthread_create(&table->philos[i]->thread, NULL, ft_live, table->philos[i]);
		i++;
	}

	i = 0;
	while (i < table->num_philo)
	{
		pthread_join(table->philos[i]->thread, NULL);
		i++;
	}
}

void	table_destroy(t_table *table)
{
	int i;
	i = 0;
	while (i < table->num_philo)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
}
