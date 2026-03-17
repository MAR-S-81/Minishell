/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 19:20:40 by mchesnea          #+#    #+#             */
/*   Updated: 2026/03/17 18:09:32 by mchesnea         ###   ########.fr       */
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

	if (ft_strncmp(args[1], "-n", 3) == 0)
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

static int	exec_export(char **args, t_env **lst, int fd_out)
{
	char	*equal_pos;
	char	*key;
	char	*value;
	int		ret;

	if (!args[1])
	{
		ret = export_no_args(lst, fd_out);
		return (ret);
	}
	equal_pos = ft_strchr(args[1], '=');
	if (equal_pos)
	{
		key = ft_substr(args[1], 0, equal_pos - args[1]);
		value = ft_strdup(equal_pos + 1);
		ret = export(lst, key, value);
		free(key);
		free(value);
		return (ret);
	}
	return (0);
}

int	execute_builtin(char **args, t_env **lst, int fd_out, int status)
{
	if (!args || !args[0])
		return (1);
	if (ft_strncmp(args[0], "echo", 5) == 0)
		return (exec_echo(args, fd_out));
	else if (ft_strncmp(args[0], "cd", 3) == 0)
		return (cd((*lst), args[1]));
	else if (ft_strncmp(args[0], "env", 4) == 0)
		return (env((*lst), fd_out));
	else if (ft_strncmp(args[0], "exit", 5) == 0)
		return (my_exit(args, status));
	else if (ft_strncmp(args[0], "export", 7) == 0)
		return (exec_export(args, lst, fd_out));
	else if (ft_strncmp(args[0], "pwd", 4) == 0)
		return (pwd(fd_out));
	else if (ft_strncmp(args[0], "unset", 6) == 0 && args[1])
		return (unset(lst, args[1]));
	return (0);
}
