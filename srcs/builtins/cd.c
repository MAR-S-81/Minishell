/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 13:18:55 by mchesnea          #+#    #+#             */
/*   Updated: 2026/03/17 18:00:11 by mchesnea         ###   ########.fr       */
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

static int	cd_home(char *home)
{
	if (!home)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (-1);
	}
	if (chdir(home) != 0)
	{
		perror("cd");
		return (-1);
	}
	return (0);
}

static int	cd_oldpwd(char *oldpwd)
{
	if (!oldpwd)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		return (-1);
	}
	if (chdir(oldpwd) != 0)
	{
		perror("cd");
		return (-1);
	}
	printf("%s\n", oldpwd);
	return (0);
}

static void	update_env_pwds(t_env *lst, char *pwd)
{
	char	buffer[4096];
	char	*tmp;

	replace_old_pwd(lst, pwd, "OLDPWD");
	tmp = getcwd(buffer, 4096);
	if (tmp)
		replace_old_pwd(lst, tmp, "PWD");
}

int	cd(t_env *lst, char *args)
{
	char	*pwd;
	char	*tmp;
	int		status;

	tmp = get_args_envp("PWD", lst);
	if (!tmp)
		pwd = getcwd(NULL, 0);
	else
		pwd = ft_strdup(tmp);
	if (!args || (args[0] == '~' && args[1] == '\0'))
		status = cd_home(get_args_envp("HOME", lst));
	else if (args[0] == '-' && args[1] == '\0')
		status = cd_oldpwd(get_args_envp("OLDPWD", lst));
	else
	{
		status = chdir(args);
		if (status != 0)
			perror("cd");
	}
	if (status == 0)
		update_env_pwds(lst, pwd);
	free(pwd);
	if (status != 0)
		return (1);
	return (0);
}
