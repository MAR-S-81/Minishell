/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd_edit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:40:52 by mchesnea          #+#    #+#             */
/*   Updated: 2025/11/04 15:19:55 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_len(int nb)
{
	int	i;

	i = 1;
	if (nb < 0)
		nb = nb * -1;
	while (nb / 10 > 0)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

int	ft_putnbr_fd_edit(int n, int fd)
{
	char	c;
	int		len;

	len = ft_len(n);
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return (11);
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
		len++;
	}
	if (n >= 10)
		ft_putnbr_fd_edit(n / 10, fd);
	c = (n % 10) + '0';
	write(fd, &c, 1);
	return (len);
}
