/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:25:13 by mitasci           #+#    #+#             */
/*   Updated: 2024/05/02 14:48:53 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

# include <pthread.h>
# include <stdio.h>

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


//utils
int	valid_int(const char *s);

#endif