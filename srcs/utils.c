/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 14:38:19 by mchesnea          #+#    #+#             */
/*   Updated: 2026/02/20 16:27:24 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_spacing(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

long long	ft_atoll_check(const char *str, long long *nb)
{
	int			i;
	int			sign;
	unsigned long long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (ft_is_spacing(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	if (!str[i]) 
		return (1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i++] - '0');
		if (result > (unsigned long long)LONG_MAX + 1 && sign == -1) 
			return (1);
		if (result > (unsigned long long)LONG_MAX && sign == 1) 
			return (1);
	}
	*nb = result * sign;
	return (0);
}

int	ft_all_digit(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}