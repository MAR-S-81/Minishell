/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 17:00:13 by mchesnea          #+#    #+#             */
/*   Updated: 2026/03/25 19:06:25 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_redirections(t_cmd *cmd, t_exec exec)
{
	if (cmd->fd_in > 0)
		dup2(cmd->fd_in, STDIN_FILENO);
	else if (exec.fd_temp != -1)
		dup2(exec.fd_temp, STDIN_FILENO);
	if (cmd->fd_out > 1)
		dup2(cmd->fd_out, STDOUT_FILENO);
	else if (cmd->next)
		dup2(exec.pipe_fd[1], STDOUT_FILENO);
}

int	init_t_exec(t_exec *exec, t_cmd *cmd)
{
	t_cmd	*tmp;

	exec->nb_cmds = 0;
	tmp = cmd;
	while (tmp)
	{
		exec->nb_cmds++;
		tmp = tmp->next;
	}
	exec->pids = malloc(sizeof(pid_t) * exec->nb_cmds);
	if (!exec->pids)
		return (0);
	exec->fd_temp = -1;
	exec->pipe_fd[0] = -1;
	exec->pipe_fd[1] = -1;
	return (1);
}

void	wait_all_children(t_exec exec)
{
	int	i;
	int	status;

	i = 0;
	while (i < exec.nb_cmds)
	{
		waitpid(exec.pids[i], &status, 0);
		if (i == exec.nb_cmds - 1)
		{
			if (WIFEXITED(status))
				g_signal = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				g_signal = 128 + WTERMSIG(status);
				if (g_signal == 131)
					write(1, "Quit (core dumped)\n", 19);
				else if (g_signal == 130)
					write(1, "\n", 1);
			}
		}
		i++;
	}
}

static void	close_when_error(t_cmd *cmd)
{
	if (cmd->fd_in > 2)
		close(cmd->fd_in);
	if (cmd->fd_out > 2)
		close(cmd->fd_out);
	g_signal = 1;
}

void	exec_single_builtin(t_cmd *cmd, t_env **lst)
{
	int	save_stdout;
	int	save_stdin;

	if (cmd->error_redir)
	{
		close_when_error(cmd);
		return ;
	}
	save_stdin = dup(STDIN_FILENO);
	save_stdout = dup(STDOUT_FILENO);
	if (cmd->fd_in > 0)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
	}
	if (cmd->fd_out > 1)
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
	}
	g_signal = execute_builtin(cmd->args, lst, STDOUT_FILENO, g_signal);
	dup2(save_stdin, STDIN_FILENO);
	dup2(save_stdout, STDOUT_FILENO);
	close(save_stdin);
	close(save_stdout);
}
