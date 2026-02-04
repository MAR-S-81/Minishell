/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_unsign_fd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 12:27:02 by mchesnea          #+#    #+#             */
/*   Updated: 2025/11/04 15:19:38 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_len(unsigned int nb)
{
	int	i;

	i = 1;
	while (nb / 10 > 0)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

int	ft_putnbr_unsign_fd(unsigned int n, int fd)
{
	int	j;
	int	i;

	i = ft_len(n);
	j = 0;
	if (n <= 9)
	{
		j = n + 48;
		write(fd, &j, 1);
	}
	else
	{
		ft_putnbr_unsign_fd(n / 10, fd);
		ft_putnbr_unsign_fd(n % 10, fd);
	}
	return (i);
}
