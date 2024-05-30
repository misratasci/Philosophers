/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:33:12 by mitasci           #+#    #+#             */
/*   Updated: 2024/05/30 16:22:08 by mitasci          ###   ########.fr       */
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

void	ft_print(t_philo *philo, t_time time, char *str)
{
	size_t	count[2];
	char	*s;
	char	*s2;
	
	count[0] = char_count_time(time);
	count[1] = char_count(philo->id);
	s = ft_timetoa(time, count[0]);
	s2 = ft_itoa(philo->id, count[1]);
	pthread_mutex_lock(&philo->table->print);
	write(STDOUT_FILENO, s, count[0]);
	write(STDOUT_FILENO, " ", 1);
	write(STDOUT_FILENO, s2, count[1]);
	write(STDOUT_FILENO, " ", 1);
	write(STDOUT_FILENO, str, ft_strlen(str));
	write(STDOUT_FILENO, "\n", 1);
	pthread_mutex_unlock(&philo->table->print);
	free(s);
	free(s2);
}