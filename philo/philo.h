/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:25:13 by mitasci           #+#    #+#             */
/*   Updated: 2024/05/02 17:47:47 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdint.h>

typedef struct s_philo
{
	int			id;
	int			dead;
	int			sleeping;
	int			eating;
	int			thinking;
	pthread_t	th;
	int			timestamp;
}	t_philo;

typedef struct s_fork
{
	int	id;	
}	t_fork;

typedef struct s_table
{
	int		philo_no;
	t_philo	*philos;
	t_fork	*forks;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		philo_eat_no;
	u_int64_t	start_time;
}	t_table;

//utils
int	valid_int(const char *s);

//libft
int	ft_atoi(const char *str);
char	*ft_itoa(int n);
void	write_message(char *time,char *id, char* act);

#endif