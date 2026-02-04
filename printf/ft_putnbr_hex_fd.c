/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hex_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 11:47:37 by mchesnea          #+#    #+#             */
/*   Updated: 2025/11/04 15:19:26 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_len(unsigned int nb)
{
	int	i;

	i = 1;
	while (nb / 16 > 0)
	{
		nb = nb / 16;
		i++;
	}
	return (i);
}

int	ft_putnbr_hex_fd(unsigned int n, int casee, int fd)
{
	int		i;
	char	*hex;

	i = ft_len(n);
	if (casee == 1)
		hex = "0123456789abcdef";
	if (casee == 0)
		hex = "0123456789ABCDEF";
	if (n < 16)
		write(fd, &hex[n], 1);
	else
	{
		ft_putnbr_hex_fd(n / 16, casee, fd);
		ft_putnbr_hex_fd(n % 16, casee, fd);
	}
	return (i);
}
