/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:24:38 by mitasci           #+#    #+#             */
/*   Updated: 2024/05/02 14:44:44 by mitasci          ###   ########.fr       */
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
	}
	return (1);
}

void	*func(void *arg)
{
	printf("Hello from thread func\n");
	return (arg);
}

int	main(int argc, char **argv)
{
	pthread_t	th;
	
	if (!args_valid(argc, argv))
		return (1);
	pthread_create(&th, NULL, func, NULL);
	pthread_join(th, NULL);
}