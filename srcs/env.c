/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 15:31:05 by mchesnea          #+#    #+#             */
/*   Updated: 2026/02/13 17:44:51 by mchesnea         ###   ########.fr       */
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

void	split_key_values(char **envp, t_env **lst)
{
	int		i;
	int		j;
	char	*key;
	char	*value;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		if (envp[i][j] == '=')
		{
			key = ft_substr(envp[i], 0, j);
			value = ft_strdup(envp[i] + j + 1);
		}
		else
		{
			key = ft_strdup(envp[i]);
			value = NULL;
		}
		if (!key)
		{
			free(value);
			return ;
		}
		lstadd_back(lst, lstnew(key, value));
		printf("%s:%s\n",key, value);
		i++;
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_env **my_env = NULL;
	
	split_key_values(envp, my_env);
}