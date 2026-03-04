/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 14:42:14 by mchesnea          #+#    #+#             */
/*   Updated: 2026/03/04 13:32:59 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(t_env *env, int fd_out)
{
	char	*str;

	str = get_args_envp("PWD", env);
	if (!str)
	{
		printf("ERROR PWD");
		return ;
	}
	write(fd_out, str, ft_strlen(str));
	write(fd_out, "\n", 1);
}
