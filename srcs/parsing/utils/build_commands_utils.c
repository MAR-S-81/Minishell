/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_commands_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erocha-- <erocha--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 15:35:58 by erocha--          #+#    #+#             */
/*   Updated: 2026/03/26 16:07:24 by erocha--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	args_size(t_token *tokens)
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

static void	redirection_handling_in(t_token *token, t_cmd **cmd, t_env *envs)
{
	if ((*cmd)->fd_in != -1)
		close((*cmd)->fd_in);
	if (token->type == TOKEN_REDIR_IN)
		(*cmd)->fd_in = open(token->next->value, O_RDONLY);
	else
		(*cmd)->fd_in = ft_here_doc(token->next->value,
				token->next->in_quote, envs);
	if ((*cmd)->fd_in == -1)
	{
		perror(token->next->value);
		(*cmd)->error_redir = 1;
	}
}

static void	redirection_handling_out(t_token *token, t_cmd **cmd)
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

void	redirection_handling(t_token *token, t_cmd **cmd, t_env *envs)
{
	if (!token->next)
	{
		write(2, "Error\n", 7);
		exit(2);
	}
	if (token->type == TOKEN_REDIR_IN || token->type == TOKEN_HERE_DOC)
		redirection_handling_in(token, cmd, envs);
	if (token->type == TOKEN_REDIR_OUT || token->type == TOKEN_APPEND)
		redirection_handling_out(token, cmd);
}
