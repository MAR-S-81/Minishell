/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 14:42:14 by mchesnea          #+#    #+#             */
/*   Updated: 2026/03/25 18:30:21 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(int fd_out, t_env *lst)
{
	char	buffer[4096];
	char	*env_pwd;

	if (getcwd(buffer, 4096))
	{
		write(fd_out, buffer, ft_strlen(buffer));
		write(fd_out, "\n", 1);
		return (0);
	}
	env_pwd = get_args_envp("PWD", lst);
	if (env_pwd)
	{
		write(fd_out, env_pwd, ft_strlen(env_pwd));
		write(fd_out, "\n", 1);
		free(env_pwd);
		return (0);
	}
	perror("pwd");
	return (1);
}
