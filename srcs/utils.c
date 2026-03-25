/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 14:38:19 by mchesnea          #+#    #+#             */
/*   Updated: 2026/03/25 18:30:28 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_spacing(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

static int	is_overflow(const char *str, int sign, unsigned long long res)
{
	int	d;

	d = *str - '0';
	if (sign == 1 && (res > LONG_MAX / 10 || (res == LONG_MAX / 10 && d > 7)))
		return (1);
	if (sign == -1 && (res > LONG_MAX / 10 || (res == LONG_MAX / 10 && d > 8)))
		return (1);
	return (0);
}

long long	ft_atoll_check(const char *str, long long *nb)
{
	int					i;
	int					sign;
	unsigned long long	res;

	i = 0;
	sign = 1;
	res = 0;
	while (ft_is_spacing(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	if (!str[i])
		return (1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (is_overflow(&str[i], sign, res))
			return (1);
		res = res * 10 + (str[i++] - '0');
	}
	return (*nb = res * sign, 0);
}

int	ft_all_digit(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	lstclear(t_env **lst)
{
	t_env	*check;
	t_env	*temp;

	if (!lst || !*lst)
		return ;
	check = *lst;
	while (check != NULL)
	{
		free(check->key);
		free(check->value);
		temp = check->next;
		free(check);
		check = temp;
	}
	*lst = NULL;
}
