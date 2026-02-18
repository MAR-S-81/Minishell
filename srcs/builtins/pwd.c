/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 14:42:14 by mchesnea          #+#    #+#             */
/*   Updated: 2026/02/18 15:09:41 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void pwd(t_env *env, int fd_out)
{
	char *str;
	int i;
	
	i = 0;
	str = get_args_envp("PWD", env);
	if (!str)
	{
		printf("ERROR PWD");
	}
	while (str[i])
	{
		write(fd_out, &str[i], 1);
		i++;
	}
	write(fd_out, &"\n", 1);
}

