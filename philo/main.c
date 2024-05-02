/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:24:38 by mitasci           #+#    #+#             */
/*   Updated: 2024/05/02 22:28:15 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	args_valid(int argc, char **argv)
{
	int	i;
	
	if (argc != 5 && argc != 6)
		return (0);
	i = 1;
	while (i < argc - 1)
	{
		if (!valid_int(argv[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	philo_init(t_philo *philo, t_table *table, int id)
{
	philo->id = id;
	philo->dead = 0;
	philo->eating = 1;
	philo->sleeping = 0;
	philo->thinking = 0;
	pthread_create(&(philo->th), NULL, live, philo);
	philo->timestamp = 0;
	philo->table = table;
}

static void	fork_init(t_fork *fork, int id)
{
	fork->id = id;
	pthread_mutex_init(&(fork->lock), NULL);
}

static void	table_init(t_table *table, int argc, char **argv)
{
	int	i;

	table->philo_no = ft_atoi(argv[1]);
	table->philos = (t_philo *)malloc(sizeof(t_philo) * table->philo_no);
	table->forks = (t_fork *)malloc(sizeof(t_fork) * table->philo_no);
	if (!(table->philos))
		return ;
	i = 0;
	while (i < table->philo_no)
	{
		philo_init(&(table->philos[i]), table, i);
		fork_init(&(table->forks[i]), i);
		i++;
	}
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	table->philo_eat_no = 0;
	if (argc == 6)
		table->philo_eat_no = ft_atoi(argv[5]);
	table->start_time = get_time();
}


void	table_destroy(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_no)
	{
		pthread_join((table->philos[i]).th, NULL);
		i++;
	}
	free(table->philos);
	free(table->forks);
}

int	main(int argc, char **argv)
{
	t_table		table;
	
	if (!args_valid(argc, argv))
		return (1);
	table_init(&table, argc, argv);

	table_destroy(&table);
}