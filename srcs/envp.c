/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erocha-- <erocha--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 15:31:05 by mchesnea          #+#    #+#             */
/*   Updated: 2026/02/24 11:35:06 by erocha--         ###   ########.fr       */
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
	lstadd_back(lst, lstnew(key, value));
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

char	*get_args_envp(char *str, t_env *lst)
{
	int	len;

	if (!str || !lst)
		return (0);
	len = ft_strlen(str);
	while (lst != NULL)
	{
		if (ft_strncmp(str, lst->key, len) == 0
			&& lst->key[len] == '\0')
			return (lst->value);
		lst = lst->next;
	}
	return (NULL);
}
