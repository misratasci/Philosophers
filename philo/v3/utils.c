/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessiz <sessiz@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD:philo/utils.c
/*   Created: 2024/05/15 16:33:12 by sessiz            #+#    #+#             */
/*   Updated: 2024/05/15 17:34:42 by sessiz           ###   ########.fr       */
=======
/*   Created: 2024/05/02 14:41:46 by mitasci           #+#    #+#             */
/*   Updated: 2024/05/09 23:32:53 by sessiz           ###   ########.fr       */
>>>>>>> 5fa234f96c6d613439e3fefd8c25fce2a8c6fb37:philo/v3/utils.c
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isdig(int c)
{
	return (c >= 48 && c <= 57);
}

t_time	ft_get_time_of_ms(void)
{
	struct timeval	tp;
	t_time			time;

	gettimeofday(&tp, NULL);
	time = tp.tv_sec * 1000 + tp.tv_usec / 1000;
	return (time);
}
<<<<<<< HEAD:philo/utils.c
=======

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

void	write_message(char *time,char *id, char* act)
{
	// write(1, time, ft_strlen(time));
	// write(1, " ", 1);
	// write(1, id, ft_strlen(id));
	// write(1, " ", 1);
	// write(1, act, ft_strlen(act));

	printf("%s %s %s",time,id,act);
}

u_int64_t	get_time(void)
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL))
		return (-1);
	return (tv.tv_sec * (u_int64_t)1000 + tv.tv_usec / (u_int64_t)1000);
}

void	ft_usleep(int milliseconds)
{
	usleep(milliseconds * 1000);
}
>>>>>>> 5fa234f96c6d613439e3fefd8c25fce2a8c6fb37:philo/v3/utils.c
