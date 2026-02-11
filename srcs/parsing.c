/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erocha-- <erocha--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 13:00:00 by erocha--          #+#    #+#             */
/*   Updated: 2026/02/11 17:59:36 by erocha--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void lexer(t_token *token, char *arg)
{
	int	i;
	t_token	token_current;

	token_current = *token;
	i = 0;
	while (arg[i])
	{
		if (!token->value)
			token = malloc(sizeof(t_token));
		else
			token->next = malloc(sizeof(t_token));
		while (arg[i] != ' ' && arg[i])
		{
			
			i++;
		}
		i++;
	}
}

t_args	**parsing(char *arg, char **envp)
{
	t_token token;
	
	lexer(&token, arg);
}