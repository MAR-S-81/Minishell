/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 13:23:32 by mchesnea          #+#    #+#             */
/*   Updated: 2026/02/20 16:55:13 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_exit(char **args)
{
	long long nb;

	write(1, "exit\n", 5);
	if (!args || !args[0])
		exit(1); // mettre le $?
	if ((ft_all_digit(args[0]) == 0) || ft_atoll_check(args[0], &nb))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putendl_fd(": numeric argument required", 2);
		exit(2);
	}
	if (args[1])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return ;
	}
	exit(nb % 256);
}
