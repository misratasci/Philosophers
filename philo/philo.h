/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessiz <sessiz@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:11:07 by sessiz            #+#    #+#             */
/*   Updated: 2024/05/15 19:24:09 by sessiz           ###   ########.fr       */
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

typedef struct s_philo
{
	int						id;
	int						must_eat;
	int						num_of_philo;
	int						num_of_meals;
	int						*check_dead;
	t_time					time_to_die;
	t_time					time_to_eat;
	t_time					time_to_sleep;
	t_time					start_time;
	t_time					last_meal;
	pthread_t				thread;
	pthread_mutex_t			*death;
	pthread_mutex_t			last;
	pthread_mutex_t			total;
	pthread_mutex_t			*fork;
}							t_philo;


static int	ft_isdig(int c);
int			ft_atoi(const char *str);
char		*ft_itoa(int n);
t_time		ft_get_time_of_ms(void);
int			table_init(t_philo *philo, int ac, char **av, int *check_dead);
void		*table_create(t_philo *philo);
void		*table_destroy(t_philo *philo, pthread_mutex_t *forks);
void 		*ft_live(void *args);

#endif