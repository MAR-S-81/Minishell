/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 13:00:00 by erocha--          #+#    #+#             */
/*   Updated: 2026/03/26 16:59:35 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_tokens(t_token **tokens)
{
	t_token	*next;

	while (*tokens)
	{
		free((*tokens)->value);
		next = (*tokens)->next;
		free(*tokens);
		*tokens = next;
	}
	*tokens = NULL;
}

t_cmd	*parsing(char *arg, t_env *envs)
{
	t_token	*tokens;
	t_cmd	*cmds;

	tokens = NULL;
	lexer(&tokens, arg);
	expander(&tokens, envs);
	if (format_check(tokens) == 1)
	{
		free_tokens(&tokens);
		return (NULL);
	}
	cmds = build_commands(tokens, envs);
	free_tokens(&tokens);
	return (cmds);
}
