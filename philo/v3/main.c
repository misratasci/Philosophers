/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessiz <sessiz@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD:philo/main.c
/*   Created: 2024/05/15 16:10:00 by sessiz            #+#    #+#             */
/*   Updated: 2024/05/15 20:05:18 by sessiz           ###   ########.fr       */
=======
/*   Created: 2024/05/02 14:24:38 by mitasci           #+#    #+#             */
/*   Updated: 2024/05/14 20:42:34 by sessiz           ###   ########.fr       */
>>>>>>> 5fa234f96c6d613439e3fefd8c25fce2a8c6fb37:philo/v3/main.c
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int args_valid(int argc, char **argv)
{
	int i;
	int j;

	if (argc < 5 || argc > 6)
	{
		printf("Error: .\n");
		return (0);
	}
	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
		if (!ft_isdig(argv[i][j]) || argv[i][j] == '-')
			{
				printf("Error: Arguments must be positive integers.\n");
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

<<<<<<< HEAD:philo/main.c
=======
static void	philo_init(t_philo *philo, t_table *table, int id)
{
	philo->id = id;
	philo->dead = 0;
	philo->eating = 0;
	philo->eat_count = 0;
	philo->thinking = 0;
	philo->last_eat = table->start_time;
	philo->table = table;
	pthread_mutex_init(&philo->lock, NULL);
	pthread_create(&(philo->th), NULL, live, philo);
}

static void	fork_init(t_fork *fork, int id)
{
	fork->id = id;
	pthread_mutex_init(&fork->lock, NULL);
}

static void	table_init(t_table *table, int argc, char **argv)
{
	int	i;

	table->philo_no = ft_atoi(argv[1]);
	table->philos = (t_philo *)malloc(sizeof(t_philo) * table->philo_no);
	table->forks = (t_fork *)malloc(sizeof(t_fork) * table->philo_no);
	if (!(table->philos))
		return ;
	table->start_time = get_time();
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	table->philo_eat_no = 0;
	table->philo_die = 0;
	pthread_mutex_init(&table->deadlock, NULL);
	if (argc == 6)
		table->philo_eat_no = ft_atoi(argv[5]);
	i = 0;
	while (i < table->philo_no)
	{
		philo_init(&(table->philos[i]), table, i + 1);
		fork_init(&(table->forks[i]), i + 1);
		i++;
	}
}


void	table_destroy(t_table *table)
{
	int	i;
	
	i = 0;
	pthread_mutex_unlock(&table->deadlock);
	while (i < table->philo_no)
	{
		pthread_join((table->philos[i]).th, NULL);
		i++;
	}
	i=0;
	while (i < table->philo_no)
	{
		pthread_mutex_destroy(&(table->philos[i]).lock);
		pthread_mutex_destroy(&(table->forks[i]).lock);
		i++;
	}
	pthread_mutex_destroy(&table->deadlock);
	free(table->philos);
	free(table->forks);
}
>>>>>>> 5fa234f96c6d613439e3fefd8c25fce2a8c6fb37:philo/v3/main.c

int	main(int argc, char **argv)
{
	t_philo			philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	death;
	int				check_dead;
	
	if (!args_valid(argc, argv)) //argümanların 0dan büyük olduğunu kontrol et
		return (1);
<<<<<<< HEAD:philo/main.c
	if (ft_atoi(argv[1]) == 0)
		return (1);
	
	table_init(&philo, argc, argv, &philo.check_dead);
	table_create(&philo);
	table_destroy(&philo, forks);
}
=======
	table_init(&table, argc, argv);
	table_destroy(&table);
}
>>>>>>> 5fa234f96c6d613439e3fefd8c25fce2a8c6fb37:philo/v3/main.c
