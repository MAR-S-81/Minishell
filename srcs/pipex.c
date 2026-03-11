/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erocha-- <erocha--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 13:20:05 by mchesnea          #+#    #+#             */
/*   Updated: 2026/03/11 17:12:17 by erocha--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_single_builtin(t_cmd *cmd, t_env **lst)
{
	int	save_stdout;
	int	save_stdin;

	if (cmd->error_redir)
	{
		g_signal = 1;
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

static void	setup_redirections(t_cmd *cmd, t_exec exec)
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

void	execute(t_cmd *cmd, t_exec exec, char **envp, t_env *lst)
{
	int		i;
	char	*path;

	i = 0;
	while (cmd)
	{
		if (cmd->next && pipe(exec.pipe_fd) == -1)
			break ;
		exec.pids[i] = fork();
		if (exec.pids[i] == -1)
			perror("fork");
		if (exec.pids[i] == 0)
		{
			if (cmd->error_redir == 1)
				exit(1);
			setup_redirections(cmd, exec);
			if (is_buildins(cmd->args[0]))
			{
				execute_builtin(cmd->args, &lst, 1, g_signal);
				exit(0);
			}
			close_all(cmd, exec);
			if (!cmd->args || !cmd->args[0])
				exit(0);
			path = find_path(cmd->args[0], lst);
			if (!path)
			{
				ft_putstr_fd("minishell: command not found\n", 2);
				exit(127);
			}
			execve(path, cmd->args, envp);
			perror("execve");
			exit(127);
		}
		if (exec.fd_temp != -1)
			close(exec.fd_temp);
		if (cmd->next)
		{
			close(exec.pipe_fd[1]);
			exec.fd_temp = exec.pipe_fd[0];
		}
		if (cmd->fd_in > 2)
			close(cmd->fd_in);
		if (cmd->fd_out > 2)
			close(cmd->fd_out);
		cmd = cmd->next;
		i++;
	}
	wait_all_children(exec);
}
