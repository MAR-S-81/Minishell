/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 13:18:55 by mchesnea          #+#    #+#             */
/*   Updated: 2026/02/23 17:47:53 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_old_pwd(t_env *lst, char *pwd, char *str)
{
	if (!lst)
		return ;
	while (lst != NULL)
	{
		if (lst->key == str)
		{
			free(lst->value);
			lst->value = ft_strdup(pwd);
			return ;
		}
	}
}

void	cd(t_env *lst, char *args)
{
	char	*home;
	char	*oldpwd;
	char	*pwd;
	char	buffer[4096];
	char	*tmp;

	home = get_args_envp("HOME", lst);
	oldpwd = get_args_envp("OLDPWD", lst);
	pwd = get_args_envp("PWD", lst);
	if ((args[0] == '~' && args[1] == '\0') || !args)
	{
		if (chdir(home) != 0)
		{
			perror("chdir:");
			return ;
		}
		replace_old_pwd(lst, pwd, "OLDPWD");
		tmp = getcwd(buffer, 4096);
		if (!tmp)
			return;
		replace_old_pwd(lst, tmp, "PWD");
	}
	else if ((args[0] == '-' && args[1] == '\0'))
	{
		if (chdir(oldpwd) != 0)
		{
			perror("chdir:");
			return ;
		}
		replace_old_pwd(lst, pwd, "OLDPWD");
		tmp = getcwd(buffer, 4096);
		if (!tmp)
			return;
		replace_old_pwd(lst, tmp, "PWD");
	}
	else
	{
		if (chdir(args) != 0)
		{
			perror("chdir:");
			return ;
		}
		replace_old_pwd(lst, pwd, "OLDPWD");
		tmp = getcwd(buffer, 4096);
		if (!tmp)
			return;
		replace_old_pwd(lst, tmp, "PWD");
	}
}

// sécurisé getcwd
