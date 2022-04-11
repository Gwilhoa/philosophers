/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchatain <gchatain@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 13:16:54 by gchatain          #+#    #+#             */
/*   Updated: 2022/03/21 13:26:53 by gchatain         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <pthread.h>
# include <stdarg.h>
# include <unistd.h>
# include <sys/time.h>

# define EAT 1
# define SLEEP 2
# define THINKING 3
# define TAKEN_FORK 4
# define DEATH 0

typedef struct s_table	t_table;

typedef struct s_philosophers
{
	int				number;
	int				each_eaten;
	u_int64_t		last_eat;
	pthread_t		thread;
	t_table			*table;
	pthread_mutex_t	fork;
}	t_philo;

typedef struct s_table
{
	pthread_mutex_t	talking;
	int				number_philo;
	int				time_to_eat;
	uint64_t		time_to_die;
	int				time_to_sleep;
	int				each_time_to_eat;
	uint64_t		start_time;

	t_philo			*philos;

}	t_table;

uint64_t	get_time(void);
t_philo		init_philo(t_table **table, int i);
int			ft_atoi(char const *str);
int			ft_printf(const char *str, ...);
int			function_parser(va_list args, int c);
int			ft_putchar_fd(char c, int fd);
int			ft_putstr_fd(const char *str, int fd);
int			ft_putnbr_fd(int nb, int fd);
int			ft_putunsigned(unsigned int nb, int fd);
int			ft_putchangebase(unsigned int nbr, const char *base, int fd);
int			ft_putpointer(unsigned long long nbr, int fd);
int			init(const char **argv, t_table *table, int argc);
int			verif_args(const char **argv, int argc);
int			ft_strlen(char const *str);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			eats(t_philo *philo);
int			has_eaten(t_table *table);
int			stop(t_table *table, int philo);
int			verif_philo(t_philo *philo);
int			usage(int i);
int			talking(t_philo *philo, int type);
char		*ft_itoa(int n);
void		*routine(void *vargp);
void		taking_fork(t_philo *philo, pthread_mutex_t *fork);
void		launch_thread(t_table **table);
void		my_usleep(u_int64_t time, int number);

#endif