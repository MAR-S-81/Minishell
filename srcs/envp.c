/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 15:31:05 by mchesnea          #+#    #+#             */
/*   Updated: 2026/03/03 17:47:37 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_node_data(char *env_str, char **key, char **value)
{
	int	j;

	j = 0;
	while (env_str[j] && env_str[j] != '=')
		j++;
	if (env_str[j] == '=')
	{
		*key = ft_substr(env_str, 0, j);
		*value = ft_strdup(env_str + j + 1);
	}
	else
	{
		*key = ft_strdup(env_str);
		*value = NULL;
	}
}

static void	extract_entry(char *env_str, t_env **lst)
{
	char	*key;
	char	*value;
	t_env	*new;

	get_node_data(env_str, &key, &value);
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
