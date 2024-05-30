/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:11:07 by sessiz            #+#    #+#             */
/*   Updated: 2024/05/30 14:20:05 by mitasci          ###   ########.fr       */
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

typedef unsigned long long	t_time;

typedef struct s_table t_table;

typedef struct s_philo
{
	int						id;
	t_time					last_meal;
	pthread_t				thread;
	pthread_mutex_t			*rfork;
	pthread_mutex_t			*lfork;
	t_table					*table;
	int						meal_count;
}							t_philo;

typedef struct s_table
{
	int				num_philo;
	t_philo			**philos;
	int				must_eat;
	t_time			time_to_die;
	t_time			time_to_eat;
	t_time			time_to_sleep;
	t_time			start_time;
	int				someone_died;
	int				max_meals_eaten;
	pthread_mutex_t	check_dead;
	pthread_mutex_t	*forks;
	pthread_mutex_t	meals;
}	t_table;


void	table_init(t_table	*table, int ac, char **av);
void	philo_init(t_table *table, int i);
void	create_philos(t_table *table);
void	table_destroy(t_table *table);
int		ft_isdig(int c);
int		ft_atoi(const char *str);
char	*ft_itoa(int n);
t_time	ft_get_time_of_ms(void);
void	*ft_live(void *args);
void	ft_msleep(t_time time);

#endif