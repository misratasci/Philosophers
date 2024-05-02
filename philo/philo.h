/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:25:13 by mitasci           #+#    #+#             */
/*   Updated: 2024/05/02 20:50:46 by mitasci          ###   ########.fr       */
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

//argumanları alıp doğru sayıda geldiğini kontrol ettik
// gelen arguman sayısıyla philo oluşturduk
//her philo ile thread oluşturduk
//her philonun yemeğe müsait olup olmadığının kontrolü yapılmalı
//bunun için sağı ve solundaki çatallar kontrol edilmeli
//philonun eat think ve sleep planlaması yapılmalı
//sıra eat - sleep - think şeklinde
// eat think sleep actlerini yaptık
// philonun doğru zaman aralığında yemek yediği kontrol edilmeli
// ölen bir philo olduğunda program  10 ms içersinde bitmeli

typedef struct s_table t_table;

typedef struct s_philo
{
	int			id;
	int			dead;
	int			sleeping;
	int			eating;
	int			thinking;
	pthread_t	th;
	int			timestamp;
	t_table		*table;
}	t_philo;


typedef struct s_fork
{
	int				id;
	pthread_mutex_t	lock;
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
void	write_message(char *time,char *id, char* act);
u_int64_t	get_time(void);
void	ft_usleep(int milliseconds);

//actions
void	ft_eat(t_philo *philo, t_table table);
void	ft_think(t_philo *philo, t_table table);
void	ft_sleep(t_philo *philo, t_table table);
void	*live(void *philo);
int	check_forks(t_philo philo, t_table table);

//libft
int	ft_atoi(const char *str);
char	*ft_itoa(int n);

#endif