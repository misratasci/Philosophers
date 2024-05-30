/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:33:09 by mitasci           #+#    #+#             */
/*   Updated: 2024/05/30 14:50:30 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_death_check(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->check_dead);
	if(ft_get_time_of_ms() - philo->last_meal > philo->table->time_to_die && !philo->table->someone_died)
	{
		philo->table->someone_died = 1;
		printf("%llu %d died\n", ft_get_time_of_ms() - philo->table->start_time, philo->id);
		pthread_mutex_unlock(&philo->table->check_dead);
		return ;
	}
	pthread_mutex_unlock(&philo->table->check_dead);
}

int	ft_dead_check(t_philo *philo)
{
	int dead;

    pthread_mutex_lock(&philo->table->check_dead);
    dead = philo->table->someone_died;
    pthread_mutex_unlock(&philo->table->check_dead);
    return (dead);
}

void ft_meals_check(t_philo *philo)
{
	int	all_philos_ate;
	int	i;
	
	pthread_mutex_lock(&philo->table->meals);
	all_philos_ate = 1;
	i = 0;
	while (i < philo->table->num_philo)
	{
		if (philo->table->philos[i]->meal_count < philo->table->must_eat || philo->table->must_eat == -1)
		{
			all_philos_ate = 0;
			break ;
		}
		i++;
	}
	if(all_philos_ate && !philo->table->max_meals_eaten)
	{
		philo->table->max_meals_eaten = 1;
		pthread_mutex_unlock(&philo->table->meals);
		return ;
	}
	pthread_mutex_unlock(&philo->table->meals);
}

int	ft_eaten_check(t_philo *philo)
{
	int eaten;

    pthread_mutex_lock(&philo->table->meals);
    eaten = philo->table->max_meals_eaten;
    pthread_mutex_unlock(&philo->table->meals);
    return (eaten);
}

void ft_take_forks(t_philo *philo)
{
	if (ft_dead_check(philo) || ft_eaten_check(philo))
		return ;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->lfork);
		if (ft_dead_check(philo) || ft_eaten_check(philo))
		{
			pthread_mutex_unlock(philo->lfork);
			return ;
		}
		printf("%llu %d has taken a fork\n", ft_get_time_of_ms() - philo->table->start_time, philo->id);
		pthread_mutex_lock(philo->rfork);
		if (ft_dead_check(philo) || ft_eaten_check(philo))
        {
            pthread_mutex_unlock(philo->rfork);
            pthread_mutex_unlock(philo->lfork);
            return ;
        }
		printf("%llu %d has taken a fork\n", ft_get_time_of_ms() - philo->table->start_time, philo->id);
	}
	else
	{
		pthread_mutex_lock(philo->rfork);
		if (ft_dead_check(philo) || ft_eaten_check(philo))
		{
			pthread_mutex_unlock(philo->rfork);
			return ;
		}
		printf("%llu %d has taken a fork\n", ft_get_time_of_ms() - philo->table->start_time, philo->id);
		if (philo->table->num_philo == 1)
			return ;
		pthread_mutex_lock(philo->lfork);
		if (ft_dead_check(philo) || ft_eaten_check(philo))
        {
            pthread_mutex_unlock(philo->rfork);
            pthread_mutex_unlock(philo->lfork);
            return ;
        }
		printf("%llu %d has taken a fork\n", ft_get_time_of_ms() - philo->table->start_time, philo->id);
	}
	return ;
}

void ft_leave_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->lfork);	
	pthread_mutex_unlock(philo->rfork);
}

void ft_eat(t_philo *philo)
{
	ft_death_check(philo);
	ft_meals_check(philo);
	if (ft_dead_check(philo) || ft_eaten_check(philo))
		return ;
	ft_take_forks(philo);
	philo->last_meal = ft_get_time_of_ms();
	if (ft_dead_check(philo) || ft_eaten_check(philo))
		return ;
	printf("%llu %d is eating\n", philo->last_meal - philo->table->start_time, philo->id);
	philo->meal_count++;
	ft_msleep(philo->table->time_to_eat);
	ft_leave_forks(philo);
}

void	ft_sleep(t_philo *philo)
{
	ft_death_check(philo);
	ft_meals_check(philo);
	if (ft_dead_check(philo) || ft_eaten_check(philo))
		return ;
	printf("%llu %d is sleeping\n", ft_get_time_of_ms() - philo->table->start_time, philo->id);
	ft_msleep(philo->table->time_to_sleep);
}

void	ft_think(t_philo *philo)
{
	ft_death_check(philo);
	ft_meals_check(philo);
	if (ft_dead_check(philo) || ft_eaten_check(philo))
		return ;
	printf("%llu %d is thinking\n", ft_get_time_of_ms() - philo->table->start_time, philo->id);
}

void *ft_live(void *args)
{
	t_philo	*philo;
	
	philo = (t_philo *)args;
	while (1)
	{	
		if (ft_dead_check(philo) || ft_eaten_check(philo))
		break ;
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (NULL);
}