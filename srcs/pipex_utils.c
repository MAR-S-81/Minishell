/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erocha-- <erocha--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 17:00:13 by mchesnea          #+#    #+#             */
/*   Updated: 2026/03/11 17:58:24 by erocha--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_all(t_cmd *cmd, t_exec exec)
{
	if (exec.pipe_fd[0] > 2)
		close(exec.pipe_fd[0]);
	if (exec.pipe_fd[1] > 2)
		close(exec.pipe_fd[1]);
	if (cmd->fd_in > 2)
		close(cmd->fd_in);
	if (cmd->fd_out > 2)
		close(cmd->fd_out);
	if (exec.fd_temp > 2)
		close(exec.fd_temp);
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
