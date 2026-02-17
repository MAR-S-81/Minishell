/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erocha-- <erocha--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 18:07:07 by erocha--          #+#    #+#             */
/*   Updated: 2026/02/17 18:11:27 by erocha--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	quotes_handling(t_token **token, char *arg, int *i, int *j)
{
	char	quote_type;

	quote_type = arg[*i];
	(*i)++;
	while (arg[*i] != quote_type)
	{
		if (!arg[*i])
		{
			write(1, "Error\n", 7);
			return ;
		}
		(*token)->value[*j] = arg[*i];
		(*i)++;
		(*j)++;
	}
}

void	token_typer(t_token **token)
{
	if (!strncmp((*token)->value, ">", 1))
		(*token)->type = TOKEN_REDIR_OUT;
	else if (!strncmp((*token)->value, "<", 1))
		(*token)->type = TOKEN_REDIR_IN;
	else if (!strncmp((*token)->value, "|", 2))
		(*token)->type = TOKEN_PIPE;
	else if (!strncmp((*token)->value, "<<", 2))
		(*token)->type = TOKEN_HERE_DOC;
	else if (!strncmp((*token)->value, ">>", 2))
		(*token)->type = TOKEN_APPEND;
	else
		(*token)->type = TOKEN_WORD;
}

t_token	*create_node(t_token **token)
{
	t_token *new_node;

	new_node = malloc(sizeof(t_token));
	if (!new_node)
		clean_exit(*token);
	new_node->next = NULL;
	new_node->type = -1;
	new_node->value = NULL;
	return (new_node);
}

void	arger(t_token **token, t_token **token_tmp, char *arg, int *i)
{
	int		j;
		
	j = 0;
	while (ft_isprint(arg[j]) && arg[j])
		j++;
	(*token_tmp)->value = malloc(sizeof(char) * j);
	if (!(*token_tmp)->value)
		clean_exit(*token);
	j = 0;
	while (ft_isprint(arg[*i]) && arg[*i])
	{
		if (arg[*i] == '"' || arg[*i] == '\'')
			quotes_handling(token_tmp, arg, i, &j);
		if (!arg[*i])
			clean_exit(*token);
		(*token_tmp)->value[j] = arg[*i];
		j++;
		(*i)++;
	}
	token_typer(token);
}