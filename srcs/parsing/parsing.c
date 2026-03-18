/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 13:00:00 by erocha--          #+#    #+#             */
/*   Updated: 2026/03/18 16:49:23 by mchesnea         ###   ########.fr       */
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
	(*token) = create_token(token);
	token_tmp = (*token);
	while (arg[i])
	{
		if (ft_isprint(arg[i]) && arg[i])
			arger(token, &token_tmp, arg, &i);
		while (!ft_isprint(arg[i]) && arg[i])
			i++;
		if (arg[i])
		{
			token_tmp->next = create_token(token);
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
	in_squote = 0;
	while (tokens_tmp != NULL)
	{
		i = 0;
		while (tokens_tmp->value[i])
		{
			if (tokens_tmp->value[i] == '\'')
				in_squote = !in_squote;
			else if (tokens_tmp->value[i] == ':'
				&& ft_isprint(tokens_tmp->value[i + 1]) && in_squote == 0)
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
	while (tokens && tokens->type == TOKEN_WORD)
	{
		i++;
		tokens = tokens->next;
	}
	return (i);
}

t_cmd	*create_cmd(t_token *tokens)
{
	t_cmd	*new_cmd;
	int		i;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		exit(0);
	new_cmd->args = malloc(sizeof(char *) * (args_size(tokens) + 1));
	i = 0;
	while (tokens && tokens->type == TOKEN_WORD)
	{
		new_cmd->args[i] = tokens->value;
		i++;
		tokens = tokens->next;
	}
	new_cmd->args[i] = NULL;
	new_cmd->next = NULL;
	new_cmd->fd_in = -1;
	new_cmd->fd_out = -1;
	new_cmd->error_redir = 0;
	return (new_cmd);
}

static int	ft_here_doc(char *infile)
{
	char	*line;
	int		pipe_fd[2];
	char	*limiter;

	if (pipe(pipe_fd) == -1)
	{
		perror("minishell: pipe");
		return (-1);
	}
	limiter = ft_strjoin(infile, "\n");
	if (!limiter)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (-1);
	}
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!line || ft_strncmp(line, limiter, ft_strlen(limiter) + 1) == 0)
		{
			free(line);
			break ;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		free(line);
	}
	free(limiter);
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}

void	redirection_handling(t_token *token, t_cmd **cmd)
{
	if (!token->next)
	{
		write(2, "ERROR\n", 7);
		exit(2);
	}
	if (token->type == TOKEN_REDIR_IN || token->type == TOKEN_HERE_DOC)
	{
		if ((*cmd)->fd_in != -1)
			close((*cmd)->fd_in);
		if (token->type == TOKEN_REDIR_IN)
			(*cmd)->fd_in = open(token->next->value, O_RDONLY);
		else
			(*cmd)->fd_in = ft_here_doc(token->next->value);
		if ((*cmd)->fd_in == -1)
		{
			perror(token->next->value);
			(*cmd)->error_redir = 1;
		}
	}
	if (token->type == TOKEN_REDIR_OUT || token->type == TOKEN_APPEND)
	{
		if ((*cmd)->fd_out != -1)
			close((*cmd)->fd_in);
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

t_cmd	*build_commands(t_token *tokens)
{
	t_cmd	*cmds;
	t_cmd	*cmds_tmp;

	cmds = create_cmd(tokens);
	cmds_tmp = cmds;
	while (tokens)
	{
		if (tokens->type != TOKEN_PIPE && tokens->type != TOKEN_WORD)
			redirection_handling(tokens, &cmds_tmp);
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

t_cmd	*parsing(char *arg, t_env *envs)
{
	t_token	*tokens;
	t_cmd	*cmds;

	tokens = NULL;
	lexer(&tokens, arg);
	expander(&tokens, envs);
	cmds = build_commands(tokens);
	return (cmds);
}
