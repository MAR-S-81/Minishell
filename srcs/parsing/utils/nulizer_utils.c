/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nulizer_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erocha-- <erocha--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 15:33:35 by erocha--          #+#    #+#             */
/*   Updated: 2026/03/26 15:51:46 by erocha--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_void(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '\0')
			return (0);
		i++;
	}
	return (1);
}

int	init_checker(t_token **tokens)
{
	int		i;
	t_token	*next;

	i = 0;
	next = *tokens;
	while ((*tokens) && is_void((*tokens)->value)
		&& (*tokens)->type != TOKEN_HERE_DOC)
	{
		next = (*tokens)->next;
		free((*tokens)->value);
		free(*tokens);
		(*tokens) = next;
		i++;
	}
	return (i);
}
