/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 13:00:00 by erocha--          #+#    #+#             */
/*   Updated: 2026/03/25 13:03:47 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	lexer(t_token **token, char *arg)
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

static void	expander(t_token **tokens, t_env *envs)
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
		remove_quote(&tokens_tmp);
		tokens_tmp = tokens_tmp->next;
	}
}

int	args_size(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens && tokens->type != TOKEN_PIPE)
	{
		if (tokens->type == TOKEN_WORD)
			i++;
		else if (tokens->type != TOKEN_WORD && tokens->next)
			tokens = tokens->next;
		tokens = tokens->next;
	}
	return (i);
}

t_cmd	*create_cmd(t_token *tokens)
{
	t_cmd	*new_cmd;
	int		i;
	t_token	*tmp;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		exit(0);
	new_cmd->args = malloc(sizeof(char *) * (args_size(tokens) + 1));
	i = 0;
	tmp = tokens;
	while (tmp && tmp->type != TOKEN_PIPE)
	{
		if (tmp->type == TOKEN_WORD)
			new_cmd->args[i++] = ft_strdup(tmp->value);
		else if (tmp->type != TOKEN_WORD && tmp->next)
			tmp = tmp->next;
		tmp = tmp->next;
	}
	new_cmd->args[i] = NULL;
	new_cmd->next = NULL;
	new_cmd->fd_in = -1;
	new_cmd->fd_out = -1;
	new_cmd->error_redir = 0;
	return (new_cmd);
}

void	redirection_handling(t_token *token, t_cmd **cmd, t_env *envs)
{
	if (!token->next)
	{
		write(2, "Error\n", 7);
		exit(2);
	}
	if (token->type == TOKEN_REDIR_IN || token->type == TOKEN_HERE_DOC)
	{
		if ((*cmd)->fd_in != -1)
			close((*cmd)->fd_in);
		if (token->type == TOKEN_REDIR_IN)
			(*cmd)->fd_in = open(token->next->value, O_RDONLY);
		else
			(*cmd)->fd_in = ft_here_doc(token->next->value, envs);
		if ((*cmd)->fd_in == -1)
		{
			perror(token->next->value);
			(*cmd)->error_redir = 1;
		}
	}
	if (token->type == TOKEN_REDIR_OUT || token->type == TOKEN_APPEND)
	{
		if ((*cmd)->fd_out != -1)
			close((*cmd)->fd_out);
		if (token->type == TOKEN_REDIR_OUT)
			(*cmd)->fd_out = open(token->next->value,
					O_RDWR | O_CREAT | O_TRUNC, 0644);
		else
			(*cmd)->fd_out = open(token->next->value,
					O_RDWR | O_CREAT | O_APPEND, 0644);
		if ((*cmd)->fd_out == -1)
		{
			perror(token->next->value);
			(*cmd)->error_redir = 1;
		}
	}
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
			redirection_handling(tokens, &cmds_tmp, envs);
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

static int	format_check(t_token *tokens)
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
		if (tokens->type == tokens->next->type && tokens->type == TOKEN_PIPE)
		{
			write(2, "minishell: syntax error near unexpected token `|'\n", 50);
			g_signal = 2;
			return (1);
		}
		if ((tokens->type != TOKEN_PIPE && tokens->type != TOKEN_WORD)
			&& tokens->next->type != TOKEN_WORD)
		{
			write(2, "minishell: syntax error near unexpected token\n", 46);
			g_signal = 2;
			return (1);
		}
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
