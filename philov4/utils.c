/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessiz <sessiz@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:33:12 by sessiz            #+#    #+#             */
/*   Updated: 2024/05/15 17:34:42 by sessiz           ###   ########.fr       */
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
