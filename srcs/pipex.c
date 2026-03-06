/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 13:20:05 by mchesnea          #+#    #+#             */
/*   Updated: 2026/03/06 16:14:17 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_here_doc(t_cmd *cmd)
{
	char	*line;
	int		pipe_fd[2];
	char	*limiter;

	if (pipe(pipe_fd) == -1)
	{
		perror("minishell: pipe");
		return (-1);
	}
	limiter = ft_strjoin(cmd->infile, "\n");
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

void	open_cmd(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->is_heredoc)
			cmd->fd_in = ft_here_doc(cmd);
		if (cmd->infile && cmd->fd_in == 0)
			cmd->fd_in = open(cmd->infile, O_RDONLY);
		if (cmd->fd_in == -1)
			cmd->error_redir = 1;
		if (cmd->outfile && !cmd->error_redir)
		{
			if (cmd->is_append)
				cmd->fd_out = open(cmd->outfile, O_RDWR | O_CREAT | O_APPEND,
						0644);
			else
				cmd->fd_out = open(cmd->outfile, O_RDWR | O_CREAT | O_TRUNC,
						0644);
			if (cmd->fd_out == -1)
			{
				cmd->error_redir = 1;
				if (cmd->fd_in > 0)
					close(cmd->fd_in);
			}
		}
		cmd = cmd->next;
	}
}
