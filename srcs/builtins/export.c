/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 14:49:45 by mchesnea          #+#    #+#             */
/*   Updated: 2026/02/18 17:45:56 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export(t_env **lst, char *keys, char *value)
{
	t_env	*new;
	char	*key_copy;
	char	*value_copy;

	key_copy = ft_strdup(keys);
	value_copy = NULL;
	if (value)
		value_copy = ft_strdup(value);
	if (!key_copy)
		return ;
	new = lstnew(key_copy, value_copy);
	if (!new)
	{
		free(key_copy);
		free(value_copy);
		return ;
	}
	lstadd_back(lst, new);
}
