/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 13:20:05 by mchesnea          #+#    #+#             */
/*   Updated: 2026/03/25 19:27:31 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_binary(char *path, char *cmd_name)
{
	struct stat	file_info;

	if (stat(path, &file_info) == -1)
	{
		perror(cmd_name);
		exit(127);
	}
	if (S_ISDIR(file_info.st_mode))
	{
		errno = EISDIR;
		perror(cmd_name);
		exit(126);
	}
	if (access(path, X_OK) == -1)
	{
		perror(cmd_name);
		exit(126);
	}
}

static void	execute_binary(t_cmd *cmd, t_env *lst)
{
	char	*path;

	path = find_path(cmd->args[0], lst);
	if (!path)
	{
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	check_binary(path, cmd->args[0]);
	execve(path, cmd->args, env_list_to_tab(lst));
	perror(cmd->args[0]);
	exit(127);
}

static void	child_process(t_cmd *cmd, t_exec exec, t_env *lst)
{
	int	ret;

	set_signals_default();
	if (cmd->error_redir == 1)
	{
		close_all(cmd, exec);
		close_saved_fds();
		exit(1);
	}
	setup_redirections(cmd, exec);
	close_all(cmd, exec);
	close_saved_fds();
	if (!cmd->args || !cmd->args[0])
		exit(0);
	if (is_buildins(cmd->args[0]))
	{
		ret = execute_builtin(cmd->args, &lst, STDOUT_FILENO, g_signal);
		exit(ret);
	}
	execute_binary(cmd, lst);
}

static void	parent_process(t_cmd *cmd, t_exec *exec)
{
	if (exec->fd_temp != -1)
		close(exec->fd_temp);
	if (cmd->next)
	{
		close(exec->pipe_fd[1]);
		exec->fd_temp = exec->pipe_fd[0];
	}
	if (cmd->fd_in > 2)
		close(cmd->fd_in);
	if (cmd->fd_out > 2)
		close(cmd->fd_out);
}

void	execute(t_cmd *cmd, t_exec exec, t_env *lst)
{
	int	i;

	i = 0;
	while (cmd)
	{
		if (cmd->next && pipe(exec.pipe_fd) == -1)
			break ;
		exec.pids[i] = fork();
		if (exec.pids[i] == -1)
			perror("fork");
		if (exec.pids[i] == 0)
			child_process(cmd, exec, lst);
		parent_process(cmd, &exec);
		cmd = cmd->next;
		i++;
	}
	set_signals_ignore();
	wait_all_children(exec);
	set_signals_interactive();
}
