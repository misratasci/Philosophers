/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:41:46 by mitasci           #+#    #+#             */
/*   Updated: 2024/05/02 14:42:32 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	int_in_limit(const char *s)
{
	size_t	len;

	len = ft_strlen(s);
	if ((len > 10 && s[0] != '-') || (s[0] == '-' && len > 11))
		return (0);
	if (len == 10 && s[0] != '-'
		&& ft_strncmp(s, "2147483647", 10) > 0)
		return (0);
	if (len == 11 && s[0] == '-'
		&& ft_strncmp(s, "-2147483648", 11) > 0)
		return (0);
	return (1);
}

int	valid_int(const char *s)
{
	int	i;

	if (!int_in_limit(s))
		return (0);
	i = 0;
	if (s[0] == '-' || s[0] == '+')
		i++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}