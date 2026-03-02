/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 14:38:19 by mchesnea          #+#    #+#             */
/*   Updated: 2026/03/02 15:29:45 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_spacing(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

long long	ft_atoll_check(const char *str, long long *nb)
{
	int					i;
	int					sign;
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
	int	i;

	i = 0;
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

void	lstdelone(t_env **head, t_env *to_del)
{
	t_env	*curr;
	t_env	*prev;

	if (!head || !*head || !to_del)
		return ;
	curr = *head;
	prev = NULL;
	while (curr && curr != to_del)
	{
		prev = curr;
		curr = curr->next;
	}
	if (curr)
	{
		if (prev == NULL)
			*head = curr->next;
		else
			prev->next = curr->next;
		if (curr->key)
			free(curr->key);
		if (curr->value)
			free(curr->value);
		free(curr);
	}
}
