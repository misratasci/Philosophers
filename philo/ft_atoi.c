/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessiz <sessiz@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:20:20 by sessiz            #+#    #+#             */
/*   Updated: 2024/05/15 17:24:46 by sessiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_whitespace(int c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

int	ft_atoi(const char *str)
{
	int	res;
	int	i;
	int	is_neg;

	res = 0;
	i = 0;
	is_neg = 1;
	while (is_whitespace(str[i]))
		i += 1;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			is_neg *= -1;
		i += 1;
	}
	while (str[i])
	{
		if (!ft_isdig(str[i]))
			break ;
		res *= 10;
		res += str[i] - '0';
		i += 1;
	}
	return (is_neg * res);
}
