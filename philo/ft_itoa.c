/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:20:12 by mitasci           #+#    #+#             */
/*   Updated: 2024/06/05 16:49:55 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	char_count(int n)
{
	size_t	i;

	i = 1;
	while (n > 9)
	{
		n /= 10;
		i++;
	}
	return (i);
}

size_t	char_count_time(time_t n)
{
	size_t	i;

	i = 1;
	while (n > 9)
	{
		n /= 10;
		i++;
	}
	return (i);
}

void	ft_itoa(char *str, int start, int n, size_t count)
{
	str[start] = ' ';
	if (n == 0)
	{
		str[start + 1] = '0';
		return ;
	}
	while (n > 0)
	{
		str[start + 1 + count-- - 1] = n % 10 + '0';
		n /= 10;
	}
}

void	ft_timetoa(char *str, int start, time_t n, size_t count)
{
	if (n == 0)
	{
		str[start] = '0';
		return ;
	}
	while (n > 0)
	{
		str[start + count-- - 1] = n % 10 + '0';
		n /= 10;
	}
}