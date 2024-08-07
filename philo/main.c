/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:10:00 by mitasci           #+#    #+#             */
/*   Updated: 2024/08/07 22:21:04 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	arg_num_valid(int argc)
{
	if (argc < 5 || argc > 6)
	{
		printf("Error: Wrong number of arguments\n");
		return (0);
	}
	return (1);
}

static int	arg_big(char *arg)
{
	if (ft_strlen(arg) > 10
		|| (ft_strlen(arg) == 10 && ft_strncmp(arg, "2147483647", 10) == 1))
	{
		printf("Error: Arguments too big\n");
		return (1);
	}
	return (0);
}

static int	args_valid(int argc, char **argv)
{
	int	i;
	int	j;

	if (!arg_num_valid(argc))
		return (0);
	i = 0;
	while (++i < argc)
	{
		if (arg_big(argv[i]))
			return (0);
		j = -1;
		while (argv[i][++j])
		{
			if (!ft_isdig(argv[i][j]))
			{
				if (argv[i][0] == '+' && j++ == 0)
					continue ;
				printf("Error: Arguments must be positive integers\n");
				return (0);
			}
		}
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (!args_valid(argc, argv))
		return (1);
	if (ft_atoi(argv[1]) == 0)
		return (0);
	if (argc == 6 && ft_atoi(argv[5]) == 0)
		return (0);
	table_init(&table, argc, argv);
	create_philos(&table);
	table_destroy(&table);
}
