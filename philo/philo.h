/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:25:13 by mitasci           #+#    #+#             */
/*   Updated: 2024/05/02 15:09:38 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

# include <pthread.h>
# include <stdio.h> //gerek yoksa sil
# include <stdlib.h>

typedef struct	s_philo
{
	int id;
	int	dead;
	int	sleeping;
	int	eating;
}	t_philo;

typedef	struct	s_fork
{
	int	id;	
}	t_fork;

typedef struct	s_table
{
	int		philo_no;
	t_philo	*philos;
	t_fork	*forks;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		philo_eat_no;
}	t_table;

//utils
int	valid_int(const char *s);

//ft_atoi
int	ft_atoi(const char *str);

#endif