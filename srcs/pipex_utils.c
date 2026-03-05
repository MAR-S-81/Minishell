/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 17:00:13 by mchesnea          #+#    #+#             */
/*   Updated: 2026/03/05 15:05:33 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_here_doc(char *argv[], t_data *d)
{
	char	*line;
	int		pipe_fd[2];
	char	*join;

	line = get_next_line(0);
	if (pipe(pipe_fd) == -1)
	{
		close(d->outfile);
		close(d->infile);
		perror("pipe");
		return (-1);
	}
	join = ft_strjoin(argv[2], "\n");
	while (line != NULL && ft_strncmp(line, join, (ft_strlen(argv[2])
				+ 1)) != 0)
	{
		write(pipe_fd[1], line, ft_strlen(line));
		free(line);
		line = get_next_line(0);
	}
	free(line);
	free(join);
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}

void	utils_fork(int fd_temp, int *pipefd, int fd_outfile, int nb)
{
	if (nb == 1)
	{
		dup2(fd_temp, 0);
		dup2(pipefd[1], 1);
		close(pipefd[0]);
		close(fd_temp);
		close(fd_outfile);
		close(pipefd[1]);
	}
	if (nb == 2)
	{
		dup2(fd_temp, 0);
		dup2(fd_outfile, 1);
		close(fd_temp);
		close(pipefd[0]);
		close(fd_outfile);
		close(pipefd[1]);
	}
}

void	close_no_inf(int *pipefd, int outfile)
{
	close(outfile);
	close(pipefd[0]);
	close(pipefd[1]);
	exit(1);
}

void	close_no_pipe(t_data *d)
{
	close(d->outfile);
	close(d->infile);
	close(d->fd_temp);
	perror("pipe");
	exit(0);
}
