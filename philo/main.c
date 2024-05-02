/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:24:38 by mitasci           #+#    #+#             */
/*   Updated: 2024/05/02 14:38:30 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*func(void *arg)
{
	printf("Hello from thread func\n");
	return (arg);
}

int	main(int argc, char **argv)
{
	pthread_t	th;
	
	pthread_create(&th, NULL, func, NULL);
	pthread_join(th, NULL);
}