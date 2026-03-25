/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 16:33:31 by mchesnea          #+#    #+#             */
/*   Updated: 2026/03/25 18:30:21 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_node_if_match(t_env **lst, char *key)
{
	t_env	*curr;
	int		len;

	curr = *lst;
	len = ft_strlen(key);
	while (curr)
	{
		if (ft_strncmp(key, curr->key, len) == 0 && curr->key[len] == '\0')
		{
			lstdelone(lst, curr);
			break ;
		}
		curr = curr->next;
	}
}

int	unset(t_env **lst, char **keys)
{
	int	i;
	int	ret;

	i = 1;
	ret = 0;
	if (!lst || !*lst)
		return (1);
	while (keys[i])
	{
		if (!is_valid_identifier(keys[i]))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(keys[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			ret = 1;
		}
		else
			remove_node_if_match(lst, keys[i]);
		i++;
	}
	return (ret);
}
