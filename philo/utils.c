/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:33:12 by mitasci           #+#    #+#             */
/*   Updated: 2024/08/04 19:42:41 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_time	ft_get_time_of_ms(void)
{
	struct timeval	tp;
	t_time			time;

	gettimeofday(&tp, NULL);
	time = tp.tv_sec * 1000LL + tp.tv_usec / 1000LL;
	return (time);
}

void	ft_msleep(t_time time)
{
	usleep(time * 1000);
}

size_t	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	c1;
	unsigned char	c2;
	size_t			i;

	i = 0;
	while (i < n)
	{
		c1 = (unsigned char)s1[i];
		c2 = (unsigned char)s2[i];
		if (c1 != c2)
		{
			if (c1 > c2)
				return (1);
			else
				return (-1);
		}
		i += 1;
		if (c1 == 0 && c2 == 0)
			break ;
	}
	return (0);
}

void	ft_print(t_table *table, time_t time, int id, char *act)
{
	pthread_mutex_lock(&table->fin);
	if (!table->finished)
		printf("%ld %d %s\n", time, id, act);
	pthread_mutex_unlock(&table->fin);
}
