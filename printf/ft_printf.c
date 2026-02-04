/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 16:31:17 by mchesnea          #+#    #+#             */
/*   Updated: 2025/11/04 15:19:13 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_check_format(const char *format, int i, va_list list)
{
	int	count;

	count = 0;
	if (format[i] == '%')
		count += ft_putchar_fd_edit('%', 1);
	else if (format[i] == 'c')
		count += ft_putchar_fd_edit(va_arg(list, int), 1);
	else if (format[i] == 's')
		count += ft_putstr_fd_edit(va_arg(list, char *), 1);
	else if (format[i] == 'd' || format[i] == 'i')
		count += ft_putnbr_fd_edit(va_arg(list, int), 1);
	else if (format[i] == 'u')
		count += ft_putnbr_unsign_fd(va_arg(list, unsigned int), 1);
	else if (format[i] == 'x')
		count += ft_putnbr_hex_fd(va_arg(list, unsigned int), 1, 1);
	else if (format[i] == 'X')
		count += ft_putnbr_hex_fd(va_arg(list, unsigned int), 0, 1);
	else if (format[i] == 'p')
		count += ft_putnbr_ptr_fd(va_arg(list, void *), 1);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		count;
	va_list	list;

	i = 0;
	count = 0;
	if (!format)
		return (-1);
	va_start(list, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			if (format[++i])
				count += ft_check_format(format, i++, list);
		}
		else
			count += ft_putchar_fd_edit(format[i++], 1);
	}
	va_end(list);
	return (count);
}
