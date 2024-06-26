/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:10:00 by mitasci           #+#    #+#             */
/*   Updated: 2024/06/10 15:31:00 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdig(int c)
{
	return (c >= 48 && c <= 57);
}

int	args_valid(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc < 5 || argc > 6)
	{
		printf("Error: Wrong number of arguments\n");
		return (0);
	}
	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdig(argv[i][j]) && argv[i][0] != '+')
			{
				printf("Error: Arguments must be positive integers\n");
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
	t_table	table;

	if (!args_valid(argc, argv))
		return (1);
	if (ft_atoi(argv[1]) == 0)
		return (1);
	table_init(&table, argc, argv);
	create_philos(&table);
	table_destroy(&table);
}
