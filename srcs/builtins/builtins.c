/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 19:20:40 by mchesnea          #+#    #+#             */
/*   Updated: 2026/02/25 19:45:17 by mchesnea         ###   ########.fr       */
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

int	execute_builtin(char **args, t_env *lst, int fd_out)
{
	if (!args || !args[0])
		return (1);
	if (ft_strncmp(args[0], "echo", 5) == 0)
	{
		if (args[1] && ft_strncmp(args[1], "-n", 3) == 0)
			echo(args, 1, fd_out);
		else
			echo(args, 0, fd_out);
	}
	else if (ft_strncmp(args[0], "cd", 3) == 0)
		cd(lst, args[1]);
	else if (ft_strncmp(args[0], "env", 4) == 0)
		env(lst, fd_out);
	else if (ft_strncmp(args[0], "exit", 5) == 0)
		my_exit(args);
	else if (ft_strncmp(args[0], "export", 7) == 0)
	{
		if (!args[1])
			export_sorting();   //faire export sorting
		else
			export(lst, args[1], args[2]);
	}
	else if (ft_strncmp(args[0], "pwd", 4) == 0)
		pwd(lst, fd_out);
	else if (ft_strncmp(args[0], "unset", 6) == 0)
	{
		if (args[1])
			unset(lst, args[1]);
	}
	return (0);
}
