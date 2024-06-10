/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:33:12 by mitasci           #+#    #+#             */
/*   Updated: 2024/06/10 14:06:09 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdig(int c)
{
	return (c >= 48 && c <= 57);
}

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

void	ft_print(t_philo *philo, t_time	time, char *str)
{
	size_t	count[2];
	char	buffer[100];
	int		i;
	
	count[0] = char_count_time(time);
	count[1] = char_count(philo->id);
	ft_timetoa(buffer, 0, time, count[0]);
	ft_itoa(buffer, count[0], philo->id, count[1]);
	buffer[count[0] + 1 + count[1]] = ' ';
	i = 0;
	while (str[i])
	{
		buffer[count[0] + 1 + count[1] + 1 + i] = str[i];
		i++;
	}
	buffer[count[0] + 1 + count[1] + 1 + i] = '\n';
	buffer[count[0] + 1 + count[1] + 2 + i] = 0;
	if ((philo->table->someone_died && ft_strncmp(str, "died", 4) == 0)
		|| (!philo->table->someone_died && ft_strncmp(str, "died", 4) != 0))
	{
		pthread_mutex_lock(&philo->table->print);
		write(STDOUT_FILENO, buffer, count[0] + 1 + count[1] + 2 + i);
		pthread_mutex_unlock(&philo->table->print);
	}
}