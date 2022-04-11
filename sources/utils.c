/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchatain <gchatain@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 11:43:23 by gchatain          #+#    #+#             */
/*   Updated: 2022/03/21 11:43:59 by gchatain         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	my_usleep(u_int64_t time, int number)
{
	u_int64_t	start;

	start = get_time();
	while (start + time > get_time())
	{
		if (number < 100)
			usleep(100);
		else
			usleep(1000);
	}
	return ;
}

u_int64_t	get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (u_int64_t)1000) + (tv.tv_usec / 1000));
}
