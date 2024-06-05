/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:11:07 by sessiz            #+#    #+#             */
/*   Updated: 2024/06/05 15:13:27 by mitasci          ###   ########.fr       */
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
	pthread_mutex_t	print;
}	t_table;


void	table_init(t_table	*table, int ac, char **av);
void	philo_init(t_table *table, int i);
void	create_philos(t_table *table);
void	table_destroy(t_table *table);
int		ft_isdig(int c);
int		ft_atoi(const char *str);
size_t	char_count(int n);
size_t	char_count_time(time_t n);
char	*ft_itoa(int n, size_t count);
char	*ft_timetoa(t_time n, size_t count);
t_time	ft_get_time_of_ms(void);
void	*ft_live(void *args);
void	ft_msleep(t_time time);
void	ft_print(t_philo *philo, t_time time, char *str);

#endif