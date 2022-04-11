/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchatain <gchatain@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 19:11:02 by gchatain          #+#    #+#             */
/*   Updated: 2022/03/11 09:16:17 by gchatain         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	sizeint(long int n)
{
	int	ret;

	ret = 0;
	if (n < 0)
	{
		ret++;
		n = -n;
	}
	while (n > 9)
	{
		n = n / 10;
		ret++;
	}
	ret++;
	return (ret);
}

char	*ft_itoa(int n)
{
	char			*ret;
	unsigned int	len;
	long int		nb;

	nb = n;
	len = sizeint(nb);
	ret = malloc(len * sizeof(char) + 1);
	if (!ret)
		return (0);
	ret[len] = 0;
	len--;
	if (nb < 0)
	{
		nb = -nb;
		ret[0] = '-';
	}
	while (nb > 9)
	{
		ret[len] = nb % 10 + 48;
		len--;
		nb /= 10;
	}
	ret[len] = nb % 10 + 48;
	return (ret);
}
