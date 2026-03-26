/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 15:38:52 by erocha--          #+#    #+#             */
/*   Updated: 2026/03/26 17:09:34 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	format_check(t_token *tokens)
{
	if (!tokens)
		return (1);
	if (tokens && (tokens->type == TOKEN_PIPE))
	{
		write(2, "minishell: syntax error near unexpected token `|'\n", 50);
		g_signal = 2;
		return (1);
	}
	while (tokens && tokens->next)
	{
		if (format_check_middle(tokens) == 1)
			return (1);
		tokens = tokens->next;
	}
	if (tokens->type != TOKEN_WORD)
	{
		write(2, "minishell: syntax error near unexpected token `newline'\n",
			56);
		g_signal = 2;
		return (1);
	}
	return (0);
}

void	nulizer(t_token **tokens)
{
	t_token	*token_current;
	t_token	*next;

	init_checker(tokens);
	token_current = *tokens;
	while (token_current && token_current->next)
	{
		if (is_void(token_current->next->value)
			&& token_current->next->type != TOKEN_HERE_DOC)
		{
			next = token_current->next->next;
			free(token_current->next->value);
			free(token_current->next);
			if (next)
				token_current->next = next;
			else
				token_current->next = NULL;
			continue ;
		}
		token_current = token_current->next;
	}
}

void	lexer(t_token **token, char *arg)
{
	int		i;
	t_token	*token_tmp;

	i = 0;
	while (!ft_isprint(arg[i]) && arg[i])
		i++;
	if (!arg[i])
		return ;
	(*token) = create_node(token);
	token_tmp = (*token);
	while (arg[i])
	{
		if (ft_isprint(arg[i]) && arg[i])
			arger(token, &token_tmp, arg, &i);
		while (!ft_isprint(arg[i]) && arg[i])
			i++;
		if (arg[i])
		{
			token_tmp->next = create_node(token);
			token_tmp = token_tmp->next;
		}
	}
}

void	expander(t_token **tokens, t_env *envs)
{
	t_token	*tokens_tmp;
	int		in_squote;
	int		i;

	tokens_tmp = *tokens;
	while (tokens_tmp != NULL)
	{
		i = 0;
		in_squote = 0;
		while (tokens_tmp->value[i])
		{
			if (tokens_tmp->value[i] == '\'')
				in_squote = !in_squote;
			else if (tokens_tmp->value[i] == '$'
				&& (ft_isalnum(tokens_tmp->value[i + 1]) || tokens_tmp->value[i
						+ 1] == '?' || tokens_tmp->value[i + 1] == '_')
				&& in_squote == 0)
				research_implement(&tokens_tmp, envs, &i);
			i++;
		}
		tokens_tmp = tokens_tmp->next;
	}
	nulizer(tokens);
	start_quote(tokens, tokens_tmp);
}

t_cmd	*build_commands(t_token *tokens, t_env *envs)
{
	t_cmd	*cmds;
	t_cmd	*cmds_tmp;

	cmds = create_cmd(tokens);
	cmds_tmp = cmds;
	while (tokens)
	{
		if (tokens->type != TOKEN_PIPE && tokens->type != TOKEN_WORD)
		{
			if (cmds_tmp->error_redir == 0)
				redirection_handling(tokens, &cmds_tmp, envs);
		}
		if (tokens->type == TOKEN_PIPE)
		{
			if (!tokens->next)
			{
				write(2, "ERROR\n", 7);
				exit(2);
			}
			cmds_tmp->next = create_cmd(tokens->next);
			cmds_tmp = cmds_tmp->next;
		}
		tokens = tokens->next;
	}
	return (cmds);
}
