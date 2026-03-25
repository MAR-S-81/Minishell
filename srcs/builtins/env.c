/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 15:36:57 by mchesnea          #+#    #+#             */
/*   Updated: 2026/03/25 18:30:23 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(t_env *lst, int fd_out, char **args)
{
	if (args[1])
	{
		ft_putstr_fd("minishell: env: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (127);
	}
	while (lst)
	{
		if (lst->value != NULL)
		{
			ft_putstr_fd(lst->key, fd_out);
			ft_putchar_fd('=', fd_out);
			ft_putendl_fd(lst->value, fd_out);
		}
		lst = lst->next;
	}
	return (0);
}
