/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erocha-- <erocha--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 18:07:07 by erocha--          #+#    #+#             */
/*   Updated: 2026/03/26 16:13:24 by erocha--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quotes_handling(t_token **token, char *arg, int *i, int *j)
{
	char	quote_type;

	quote_type = arg[*i];
	(*token)->value[*j] = arg[*i];
	(*i)++;
	(*j)++;
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
	(*token)->value[*j] = arg[*i];
	(*i)++;
	(*j)++;
}

t_token	*create_node(t_token **token)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	if (!new_node)
		clean_exit(*token);
	new_node->next = NULL;
	new_node->type = -1;
	new_node->in_quote = 0;
	new_node->value = NULL;
	return (new_node);
}

static t_token_type	is_operator(char *arg)
{
	if (!ft_strncmp(arg, ">>", 2))
		return (TOKEN_APPEND);
	if (!ft_strncmp(arg, ">", 1))
		return (TOKEN_REDIR_OUT);
	if (!ft_strncmp(arg, "<<", 2))
		return (TOKEN_HERE_DOC);
	if (!ft_strncmp(arg, "<", 1))
		return (TOKEN_REDIR_IN);
	if (!ft_strncmp(arg, "|", 1))
		return (TOKEN_PIPE);
	return (0);
}

static void	separator(t_token **token, int *i, int j, t_token_type type)
{
	if (j)
	{
		(*token)->value[j] = '\0';
		(*token)->next = create_node(token);
		(*token)->type = TOKEN_WORD;
		(*token) = (*token)->next;
	}
	else
		free((*token)->value);
	if (type == TOKEN_APPEND)
		(*token)->value = ft_strdup(">>");
	if (type == TOKEN_HERE_DOC)
		(*token)->value = ft_strdup("<<");
	if (type == TOKEN_REDIR_IN)
		(*token)->value = ft_strdup("<");
	if (type == TOKEN_REDIR_OUT)
		(*token)->value = ft_strdup(">");
	if (type == TOKEN_PIPE)
		(*token)->value = ft_strdup("|");
	if (type == TOKEN_APPEND || type == TOKEN_HERE_DOC)
		*i = *i + 2;
	else
		(*i)++;
	(*token)->type = type;
}

int	arger_extend(t_token **tokens, char *arg, int *i)
{
	int				j;

	j = 0;
	while (ft_isprint(arg[*i]) && arg[*i])
	{
		if (is_operator(arg + *i))
		{
			separator(tokens, i, j, is_operator(arg + *i));
			return (-1);
		}
		if (arg[*i] == '"' || arg[*i] == '\'')
		{
			quotes_handling(tokens, arg, i, &j);
			continue ;
		}
		if (!ft_isprint(arg[*i]))
		{
			(*tokens)->value[j] = '\0';
			(*tokens)->type = TOKEN_WORD;
			return (-1);
		}
		(*tokens)->value[j++] = arg[(*i)++];
	}
	return (j);
}
