/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:20:12 by mitasci           #+#    #+#             */
/*   Updated: 2024/05/30 16:09:58 by mitasci          ###   ########.fr       */
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

char	*ft_itoa(int n, size_t count)
{
	char	*str;
	size_t	len;
	size_t	org_len;

	len = count;
	org_len = len;
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	if (n == 0)
		str[0] = '0';
	while (n > 0)
	{
		str[len-- - 1] = n % 10 + '0';
		n /= 10;
	}
	str[org_len] = 0;
	return (str);
}

char	*ft_timetoa(t_time n, size_t count)
{
	char	*str;
	size_t	len;
	size_t	org_len;

	len = count;
	org_len = len;
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	if (n == 0)
		str[0] = '0';
	else if (n < 0)
	{
		str[0] = '-';
		n *= -1;
	}
	while (n > 0)
	{
		str[len-- - 1] = n % 10 + '0';
		n /= 10;
	}
	str[org_len] = 0;
	return (str);
}