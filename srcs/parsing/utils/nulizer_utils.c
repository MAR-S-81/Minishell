/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nulizer_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 15:33:35 by erocha--          #+#    #+#             */
/*   Updated: 2026/03/26 17:09:27 by mchesnea         ###   ########.fr       */
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

void	start_quote(t_token **tokens, t_token *tokens_tmp)
{
	tokens_tmp = *tokens;
	while (tokens_tmp != NULL)
	{
		remove_quote(&tokens_tmp);
		tokens_tmp = tokens_tmp->next;
	}
}
