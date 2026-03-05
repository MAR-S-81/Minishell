/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 13:20:05 by mchesnea          #+#    #+#             */
/*   Updated: 2026/03/05 18:06:47 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_child(t_data *d)
{
	char	**cmd;
	char	*path;

	if (d->fd_temp == -1)
		close_no_inf(d->pipe_fd, d->outfile);
	if (d->infile != -1)
		close(d->infile);
	utils_fork(d->fd_temp, d->pipe_fd, d->outfile, (d->i == d->nb_cmds - 1)
		+ 1);
	cmd = ft_split(d->argv[2 + d->i + d->is_heredoc], ' ');
	if (!cmd || !cmd[0])
	{
		if (cmd)
			free_tab(cmd);
		ft_putstr_fd("Command not found\n", 2);
		exit(127);
	}
	path = find_path(cmd[0], d->envp);
	if (path)
		execve(path, cmd, d->envp);
	free_tab(cmd);
	if (path)
		free(path);
	ft_putstr_fd("Command not found\n", 2);
	exit(127);
}

static int	wait_process(t_data *d)
{
	int	status;

	close(d->fd_temp);
	if (d->infile != -1)
		close(d->infile);
	close(d->outfile);
	waitpid(d->pid, &status, 0);
	while (d->nb_cmds-- - 1 > 0)
		wait(NULL);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

int	childs_process(t_data *d)
{
	int	ret;

	d->nb_cmds = d->argc - 3 - d->is_heredoc;
	d->fd_temp = dup(d->infile);
	d->i = -1;
	while (++d->i < d->nb_cmds)
	{
		if (pipe(d->pipe_fd) == -1)
			close_no_pipe(d);
		d->pid = fork();
		if (d->pid == -1)
			perror("fork");
		if (d->pid == 0)
			exec_child(d);
		else
		{
			close(d->pipe_fd[1]);
			if (d->fd_temp != -1)
				close(d->fd_temp);
			d->fd_temp = d->pipe_fd[0];
		}
	}
	ret = wait_process(d);
	return (ret);
}

static void	open_files(t_data *d)
{
	char	*join;

	if (d->is_heredoc)
	{
		free(join);
		d->infile = ft_here_doc(argv, d);
		d->outfile = open(argv[argc - 1], O_RDWR | O_CREAT | O_APPEND, 0644);
	}
	else
	{
		free(join);
		d->infile = open(argv[1], O_RDONLY);
		d->outfile = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	}
}

int	pipex()
{
	int		ret;
	t_exec	d;

	open_files(&d);
	if (d.infile == -1 && !d.is_heredoc)
		perror(argv[1]);
	if (d.outfile == -1)
	{
		perror(argv[argc - 1]);
		if (d.infile != -1)
			close(d.infile);
		return (1);
	}
	ret = childs_process(&d);
	return (ret);
}
