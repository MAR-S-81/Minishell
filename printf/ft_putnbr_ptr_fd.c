/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_ptr_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 13:20:39 by mchesnea          #+#    #+#             */
/*   Updated: 2025/11/04 15:21:08 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_len(unsigned long long nb)
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

static int	ft_ptr_fd(void *ptr, int fd)
{
	unsigned long long	n;
	char				*hex;
	int					i;

	n = (unsigned long long)ptr;
	i = ft_len(n);
	hex = "0123456789abcdef";
	if (n < 16)
		write(fd, &hex[n], 1);
	else
	{
		ft_ptr_fd((void *)(n / 16), fd);
		ft_ptr_fd((void *)(n % 16), fd);
	}
	return (i);
}

int	ft_putnbr_ptr_fd(void *ptr, int fd)
{
	int	i;

	if (!ptr)
		return (ft_putstr_fd_edit("(nil)", 1));
	write(fd, "0x", 2);
	i = ft_ptr_fd(ptr, fd);
	return (2 + i);
}
