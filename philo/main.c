/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessiz <sessiz@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:10:00 by sessiz            #+#    #+#             */
/*   Updated: 2024/05/15 20:05:18 by sessiz           ###   ########.fr       */
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


int	main(int argc, char **argv)
{
	t_philo			philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	death;
	int				check_dead;
	
	if (!args_valid(argc, argv))
		return (1);
	if (ft_atoi(argv[1]) == 0)
		return (1);
	
	table_init(&philo, argc, argv, &philo.check_dead);
	table_create(&philo);
	table_destroy(&philo, forks);
}
