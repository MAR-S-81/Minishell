/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erocha-- <erocha--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 13:00:00 by erocha--          #+#    #+#             */
/*   Updated: 2026/02/13 11:30:26 by erocha--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void quotes_handling(t_token *token, char *arg, int *i, int *j)
{
	while (arg[*i] != '"' && arg[*i])
	{
		
		*i++;
	}
}

static void lexer(t_token *token, char *arg)
{
	int		i;
	int		j;
	t_token	*token_current;

	token_current = token;
	if (!token)
		token = malloc(sizeof(t_token));
	i = 0;
	while (arg[i])
	{
		j = 0;
		while (arg[i] != ' ' && arg[i])
		{
			if (!arg[i])
				clean_exit(token);
			if (arg[i] == '"')
				quotes_handling(token_current, arg, &i, &j);
			token_current->value[j] = arg[i];
			i++;
			j++;
		}
		token_current->next = malloc(sizeof(t_token));
		token_current = token_current->next;
		i++;
	}
}

t_args	**parsing(char *arg, char **envp)
{
	t_token tokens;
	
	lexer(&tokens, arg);
}