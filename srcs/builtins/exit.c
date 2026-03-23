/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 13:23:32 by mchesnea          #+#    #+#             */
/*   Updated: 2026/03/23 17:22:37 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_exit(char **args, int status)
{
	long long	nb;

	write(1, "exit\n", 5);
	if (!args || !args[1])
	{
		close_saved_fds();
		exit(status);
	}
	if ((ft_all_digit(args[1]) == 0) || ft_atoll_check(args[1], &nb) != 0)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		close_saved_fds();
		exit(2);
	}
	if (args[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (1);
	}
	close_saved_fds();
	exit(nb % 256);
	return (0);
}
