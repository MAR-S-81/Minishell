/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 16:25:41 by mchesnea          #+#    #+#             */
/*   Updated: 2025/11/04 15:29:53 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int	ft_printf(const char *format, ...);
int	ft_putnbr_hex_fd(unsigned int n, int casee, int fd);
int	ft_putnbr_unsign_fd(unsigned int n, int fd);
int	ft_putnbr_ptr_fd(void *ptr, int fd);
int	ft_putstr_fd_edit(char *s, int fd);
int	ft_putnbr_fd_edit(int n, int fd);
int	ft_putchar_fd_edit(char c, int fd);

#endif
