/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 15:31:05 by mchesnea          #+#    #+#             */
/*   Updated: 2026/02/18 18:11:00 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	extract_entry(char *env_str, t_env **lst)
{
	char	*key;
	char	*value;
	int		j;
	t_env	*new;

	j = 0;
	while (env_str[j] && env_str[j] != '=')
		j++;
	if (env_str[j] == '=')
	{
		key = ft_substr(env_str, 0, j);
		value = ft_strdup(env_str + j + 1);
	}
	else
	{
		key = ft_strdup(env_str);
		value = NULL;
	}
	if (!key)
	{
		free(value);
		return ;
	}
	new = lstnew(key, value);
	if (!new)
    {
        free(key);
        free(value);
        return ;
    }
	lstadd_back(lst, new);
}

void	split_key_values(char **envp, t_env **lst)
{
	int	i;

	if (!envp || !lst)
		return ;
	i = 0;
	while (envp[i])
	{
		extract_entry(envp[i], lst);
		i++;
	}
}
