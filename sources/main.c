/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchatain <gchatain@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 10:49:24 by gchatain          #+#    #+#             */
/*   Updated: 2022/03/22 09:04:14 by gchatain         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char const *argv[])
{
	t_table		table;
	int			i;
	int			nb;

	i = 0;
	nb = 0;
	if ((argc == 5 || argc == 6))
	{
		if (verif_args(argv, argc) == 2)
			return (usage(1));
		init(argv, &table, argc);
		while (1)
		{
			if (verif_philo(&table.philos[i]) == 1)
				return (stop(&table, i + 1));
			if (verif_philo(&table.philos[i]) == 2)
				return (stop(&table, -1));
			if (++i >= table.number_philo)
				i = 0;
		}
	}
	else
		return (usage(0));
	return (0);
}

int	usage(int i)
{
	if (i == 0)
	{
		ft_putstr_fd("./philo [number philo] [time_to_die]", 2);
		ft_putstr_fd("[time_to_eat] [time_to_sleep]", 2);
		ft_putstr_fd("[number_of_times_each_philosopher_must_eat]", 2);
	}
	else
		ft_putstr_fd("illegal or invalid argument", 1);
	return (0);
}

int	stop(t_table *table, int philo)
{
	int			i;
	u_int64_t	time;

	time = get_time() - table->start_time;
	pthread_mutex_lock(&table->talking);
	table->start_time = (u_int64_t) - 1;
	pthread_mutex_unlock(&table->talking);
	i = 0;
	while (i < table->number_philo)
	{
		pthread_mutex_unlock(&table->philos[i].fork);
		pthread_join(table->philos[i].thread, NULL);
		i++;
	}
	if (philo != -1)
		ft_printf("[%i] philo %i died\n", time, philo);
	else
		ft_printf("[%i] dinner is over\n", time);
	free(table->philos);
	return (1);
}

int	has_eaten(t_table *table)
{
	int	nb;
	int	i;
	int	ret;

	nb = table->number_philo;
	i = 0;
	ret = 0;
	while (i < nb)
	{
		if (table->philos[i].each_eaten >= table->each_time_to_eat)
			ret++;
		i++;
	}
	return (ret);
}

int	verif_args(const char **argv, int argc)
{
	int		i;
	char	*temp;

	i = 1;
	while (i < argc)
	{
		temp = ft_itoa(ft_atoi(argv[i]));
		if (ft_strncmp(argv[i], temp, ft_strlen(argv[i])))
		{
			free(temp);
			return (2);
		}
		if (ft_atoi(temp) <= 0)
			return (2);
		i++;
		free(temp);
	}
	return (1);
}
