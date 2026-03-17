/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 16:33:31 by mchesnea          #+#    #+#             */
/*   Updated: 2026/03/17 17:57:19 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset(t_env **lst, char *keys)
{
	t_env	*curr;
	int		len;

	if (!lst || !*lst)
		return (1);
	curr = *lst;
	len = ft_strlen(keys);
	while (curr)
	{
		if (ft_strncmp(keys, curr->key, len) == 0 && curr->key[len] == '\0')
		{
			lstdelone(lst, curr);
			return (1);
		}
		curr = curr->next;
	}
	return (0);
}
