/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 15:16:35 by mchesnea          #+#    #+#             */
/*   Updated: 2026/03/02 15:42:52 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_signal_status;

void	signal_handler(int sig)
{
	(void)sig;
	g_signal_status = 130;
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

int	execute_command(char **args, t_env *lst, int fd)
{
	if (!args || !args[0])
		return ;
	if (is_buildins(args[0]))
	{
		if (execute_builtin(args, lst, fd) == 1)
			return (1);
	}
	else
		execute_simple_cmd(args, lst);
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
