/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 18:48:03 by mchesnea          #+#    #+#             */
/*   Updated: 2026/03/25 18:50:08 by mchesnea         ###   ########.fr       */
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
