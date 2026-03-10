/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 15:16:35 by mchesnea          #+#    #+#             */
/*   Updated: 2026/03/10 16:06:21 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	execute_command(t_cmd *cmd, t_env *lst, char **envp)
{
	t_exec	exec;

	if (!cmd)
		return ;
	if (!init_t_exec(&exec, cmd))
		return ;
	if (exec.nb_cmds == 1 && is_buildins(cmd->args[0]))
		exec_single_builtin(cmd, lst, &exec);
	else
		execute(cmd, exec, envp, lst);
	if (exec.pids)
		free(exec.pids);
}

int	read_line(void)
{
	char	*input;

	init_signal();
	input = readline(GREEN " MiniShell" ORANGE " → " RESET);
	while (input != NULL)
	{
		if (input[0] != '\0')
			add_history(input);
		free(input);
		input = readline(GREEN " MiniShell" ORANGE " → " RESET);
	}
	printf("exit\n");
	return (0);
}
