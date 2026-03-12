/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 17:51:53 by mchesnea          #+#    #+#             */
/*   Updated: 2026/03/12 18:03:51 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_swap(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

t_env	*lstnew(char *key, char *value)
{
	t_env	*dest;

	dest = malloc(sizeof(t_env));
	if (!dest)
		return (NULL);
	dest->key = key;
	dest->value = value;
	dest->next = NULL;
	return (dest);
}

void	lstadd_back(t_env **lst, t_env *new)
{
	t_env	*ret;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	ret = *lst;
	while (ret->next != NULL)
		ret = ret->next;
	ret->next = new;
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
		free(tab[i++]);
	free(tab);
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