/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erocha-- <erocha--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 19:20:40 by mchesnea          #+#    #+#             */
/*   Updated: 2026/03/23 17:58:51 by erocha--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_buildins(char *arg)
{
	int		i;
	char	**str;

	i = 0;
	str = (char *[]){"cd", "echo", "env", "exit", "export", "pwd", "unset",
		NULL};
	while (str[i])
	{
		if (ft_strlen(arg) == ft_strlen(str[i]) && ft_strncmp(arg, str[i],
				ft_strlen(arg)) == 0)
			return (1);
		i++;
	}
	return (0);
}

static int	exec_echo(char **args, int fd_out)
{
	int	ret;

	if (ft_strncmp(args[1], "-n", 2) == 0 && check_n(args[1]) == 0)
	{
		ret = echo(args, 1, fd_out);
		return (ret);
	}
	else
	{
		ret = echo(args, 0, fd_out);
		return (ret);
	}
}

static int	process_single_export(char *arg, t_env **lst)
{
	char	*equal_pos;
	char	*key;
	char	*value;
	int		ret;

	equal_pos = ft_strchr(arg, '=');
	if (equal_pos)
		key = ft_substr(arg, 0, equal_pos - arg);
	else
		key = ft_strdup(arg);
	if (!is_valid_identifier(key))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		free(key);
		return (1);
	}
	if (equal_pos)
	{
		value = ft_strdup(equal_pos + 1);
		ret = export(lst, key, value);
		free(value);
	}
	else
		ret = export(lst, key, NULL);
	free(key);
	return (ret);
}

static int	exec_export(char **args, t_env **lst, int fd_out)
{
	int	i;
	int	ret;
	int	error_flag;

	if (!args[1])
		return (export_no_args(lst, fd_out));
	i = 1;
	error_flag = 0;
	while (args[i])
	{
		ret = process_single_export(args[i], lst);
		if (ret != 0)
			error_flag = 1;
		i++;
	}
	return (error_flag);
}

int	execute_builtin(char **args, t_env **lst, int fd_out, int status)
{
	if (!args || !args[0])
		return (1);
	if (ft_strncmp(args[0], "echo", 5) == 0)
	{
		if (!args[1])
		{
			write(fd_out, "\n", 1);
			return (0);
		}
		return (exec_echo(args, fd_out));
	}
	else if (ft_strncmp(args[0], "cd", 3) == 0)
		return (cd((*lst), args[1]));
	else if (ft_strncmp(args[0], "env", 4) == 0)
		return (env((*lst), fd_out, args));
	else if (ft_strncmp(args[0], "exit", 5) == 0)
		return (my_exit(args, status));
	else if (ft_strncmp(args[0], "export", 7) == 0)
		return (exec_export(args, lst, fd_out));
	else if (ft_strncmp(args[0], "pwd", 4) == 0)
		return (pwd(fd_out, *(lst)));
	else if (ft_strncmp(args[0], "unset", 6) == 0 && args[1])
		return (unset(lst, args));
	return (0);
}
