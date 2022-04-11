/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchatain <gchatain@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 09:59:59 by gchatain          #+#    #+#             */
/*   Updated: 2022/03/21 13:24:28 by gchatain         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *arg)
{
	t_philo			*philo;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

	philo = (t_philo *) arg;
	left_fork = &philo->fork;
	if (philo->number == philo->table->number_philo)
		right_fork = &philo->table->philos[0].fork;
	else
		right_fork = &philo->table->philos[philo->number].fork;
	while (1)
	{
		if (talking(philo, THINKING) == 0)
			return (0);
		taking_fork(philo, left_fork);
		taking_fork(philo, right_fork);
		talking(philo, EAT);
		my_usleep(philo->table->time_to_eat, philo->table->number_philo);
		talking(philo, SLEEP);
		pthread_mutex_unlock(left_fork);
		pthread_mutex_unlock(right_fork);
		my_usleep(philo->table->time_to_sleep, philo->table->number_philo);
	}
	return (0);
}

void	taking_fork(t_philo *philo, pthread_mutex_t *fork)
{
	pthread_mutex_lock(fork);
	talking(philo, TAKEN_FORK);
}

int	unlock(t_philo *philo)
{
	pthread_mutex_unlock(&philo->table->talking);
	return (0);
}

int	talking(t_philo *philo, int type)
{
	int			number;
	u_int64_t	time;

	number = philo->number;
	pthread_mutex_lock(&philo->table->talking);
	if (philo->table->start_time == (u_int64_t)-1)
		return (unlock(philo));
	time = get_time() - philo->table->start_time;
	if (type == TAKEN_FORK)
		ft_printf("[%i] philo %i has taken fork\n", time, number);
	else if (type == EAT)
	{
		ft_printf("[%i] philo %i is eating\n", time, number);
		philo->last_eat = get_time() - philo->table->start_time;
		philo->each_eaten++;
	}
	else if (type == SLEEP)
		ft_printf("[%i] philo %i is sleeping\n", time, number);
	else if (type == THINKING)
		ft_printf("[%i] philo %i has thinking\n", time, number);
	else if (type == DEATH)
		ft_printf("[%i] philo %i died\n", time, number);
	pthread_mutex_unlock(&philo->table->talking);
	return (1);
}
