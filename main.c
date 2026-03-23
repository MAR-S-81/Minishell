/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 12:59:55 by erocha--          #+#    #+#             */
/*   Updated: 2026/03/23 18:09:25 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	*envs;

	if (argc > 1)
	{
		printf("Minishell Needs No Args");
		return (0);
	}
	envs = NULL;
	(void)argv;
	split_key_values(envp, &envs);
	if (read_line(&envs) == 0)
	{
		lstclear(&envs);
		return (g_signal);
	}
	lstclear(&envs);
	return (0);
}
