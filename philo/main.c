/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:24:38 by mitasci           #+#    #+#             */
/*   Updated: 2024/05/02 15:54:05 by mitasci          ###   ########.fr       */
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

static void	philo_init(t_philo *philo, int id)
{
	philo->id = id;
	philo->dead = 0;
	philo->eating = 0;
	philo->sleeping = 0;
}

static void	fork_init(t_fork *fork, int id)
{
	fork->id = id;
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
		philo_init(&(table->philos[i]), i);
		fork_init(&(table->forks[i]), i);
		i++;
	}
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	table->philo_eat_no = 0;
	if (argc == 6)
		table->philo_eat_no = ft_atoi(argv[5]);
}

void	*func(void *arg)
{
	printf("Hello from thread func\n");
	return (arg);
}

int	main(int argc, char **argv)
{
	pthread_t	th;
	t_table		table;
	struct timeval tv;
	
	gettimeofday(&tv, NULL);
	printf("start time: %d\n", tv.tv_usec);
	if (!args_valid(argc, argv))
		return (1);
	table_init(&table, argc, argv);
	//printf("philo no: %d, die time: %d, eat time: %d, sleep time: %d\n", table.philo_no, table.time_to_die, table.time_to_eat, table.time_to_sleep);
	pthread_create(&th, NULL, func, NULL);
	pthread_join(th, NULL);
	usleep(100000);
	gettimeofday(&tv, NULL);
	printf("end time: %d\n", tv.tv_usec);

	//destroy table
}