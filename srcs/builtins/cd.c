/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 13:18:55 by mchesnea          #+#    #+#             */
/*   Updated: 2026/03/02 15:51:24 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_old_pwd(t_env *lst, char *pwd, char *str)
{
	if (!lst || !pwd || !str)
		return ;
	while (lst != NULL)
	{
		if (ft_strlen(lst->key) == ft_strlen(str) && ft_strncmp(lst->key, str,
				ft_strlen(str)) == 0)
		{
			free(lst->value);
			lst->value = ft_strdup(pwd);
			return ;
		}
		lst = lst->next;
	}
}

static void	cd_home(char *home)
{
	if (!home)
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
	else if (chdir(home) != 0)
		perror("cd");
}

static void	cd_oldpwd(char *oldpwd)
{
	if (!oldpwd)
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
	else if (chdir(oldpwd) != 0)
		perror("cd");
	else
		printf("%s\n", oldpwd);
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
	tmp = get_args_envp("PWD", lst);
	if (!tmp)
		pwd = getcwd(NULL, 0);
	else
		pwd = ft_strdup(tmp);
	if (!args || (args[0] == '~' && args[1] == '\0'))
		cd_home(home);
	else if (args[0] == '-' && args[1] == '\0')
		cd_oldpwd(oldpwd);
	else if (chdir(args) != 0)
		perror("cd");
	replace_old_pwd(lst, pwd, "OLDPWD");
	tmp = getcwd(buffer, 4096);
	if (tmp)
		replace_old_pwd(lst, tmp, "PWD");
	free(pwd);
}
