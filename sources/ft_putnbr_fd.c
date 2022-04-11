/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchatain <gchatain@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 14:23:22 by gchatain          #+#    #+#             */
/*   Updated: 2022/03/04 11:34:21 by gchatain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	print_nb(int nb, int fd)
{
	int	i;

	if (nb > 9)
		i = print_nb(nb / 10, fd) + print_nb(nb % 10, fd);
	else
		i = ft_putchar_fd(nb + 48, fd);
	return (i);
}

int	ft_putnbr_fd(int nb, int fd)
{
	int	i;

	i = 0;
	if (nb == -2147483648)
		return (ft_putstr_fd("-2147483648", fd));
	if (nb < 0)
	{
		i += ft_putchar_fd('-', fd);
		nb = -nb;
	}
	i += print_nb(nb, fd);
	return (i);
}
