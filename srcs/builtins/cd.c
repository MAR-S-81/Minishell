/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 13:18:55 by mchesnea          #+#    #+#             */
/*   Updated: 2026/03/25 18:49:49 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_old_pwd(t_env *lst, char *pwd, char *str)
{
	if (!lst || !pwd || !str)
		return ;
	while (lst)
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

static int	cd_special(char *path, char *name)
{
	if (!path)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(name, 2);
		ft_putstr_fd(" not set\n", 2);
		return (-1);
	}
	if (chdir(path) != 0)
	{
		perror("cd");
		return (-1);
	}
	if (name[0] == 'O')
		printf("%s\n", path);
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

static char	*get_saved_pwd(t_env *lst)
{
	char	*tmp;

	tmp = get_args_envp("PWD", lst);
	if (tmp)
		return (ft_strdup(tmp));
	return (getcwd(NULL, 0));
}

int	cd(t_env *lst, char **args)
{
	char	*pwd;
	int		status;

	if (args[1] && args[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	pwd = get_saved_pwd(lst);
	if (!args[1] || !ft_strncmp(args[1], "~", 2))
		status = cd_special(get_args_envp("HOME", lst), "HOME");
	else if (!ft_strncmp(args[1], "-", 2))
		status = cd_special(get_args_envp("OLDPWD", lst), "OLDPWD");
	else
	{
		status = chdir(args[1]);
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
