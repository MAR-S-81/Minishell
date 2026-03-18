/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erocha-- <erocha--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 15:16:35 by mchesnea          #+#    #+#             */
/*   Updated: 2026/03/18 17:05:24 by erocha--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

void	signal_handler(int sig)
{
	(void)sig;
	g_signal = 130;
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	init_signal(void)
{
	struct sigaction	sa;

	sa.sa_handler = &signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

void	execute_command(t_cmd *cmd, t_env **lst, char **envp)
{
	t_exec	exec;

	if (!cmd)
		return ;
	if (!init_t_exec(&exec, cmd))
		return ;
	if (exec.nb_cmds == 1 && is_buildins(cmd->args[0]))
		exec_single_builtin(cmd, lst);
	else
		execute(cmd, exec, envp, *lst);
	if (exec.pids)
		free(exec.pids);
}

static void free_cmds(t_cmd **cmds)
{
	t_cmd	*next;
	int		i;

	while (*cmds)
	{
		next = (*cmds)->next;
		i = 0;
		while ((*cmds)->args && (*cmds)->args[i])
			free((*cmds)->args[i++]);
		free((*cmds)->args);
		free(*cmds);
		*cmds = next;
	}
	*cmds = NULL;
}

int	read_line(t_env **envs, char **envp)
{
	char	*input;
	t_cmd	*cmds;

	init_signal();
	input = readline(GREEN " MiniShell" ORANGE " → " RESET);
	while (input != NULL)
	{
		if (input[0] != '\0')
			add_history(input);
		cmds = parsing(input, *envs);
		execute_command(cmds, envs, envp);
		free_cmds(&cmds);
		free(input);
		input = readline(GREEN " MiniShell" ORANGE " → " RESET);
	}
	printf("exit\n");
	return (0);
}
