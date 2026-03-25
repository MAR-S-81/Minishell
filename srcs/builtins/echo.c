/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 13:23:46 by mchesnea          #+#    #+#             */
/*   Updated: 2026/03/25 18:30:23 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(char **str, int n, int fd_out)
{
	int	i;

	i = 1;
	while (str[i] && (ft_strncmp(str[i], "-n", 2) == 0 && check_n(str[i]) == 0))
		i++;
	if (str)
	{
		while (str[i])
		{
			write(fd_out, str[i], ft_strlen(str[i]));
			if (str[i + 1])
				write(fd_out, " ", 1);
			i++;
		}
	}
	if (n == 0)
		write(fd_out, "\n", 1);
	return (0);
}
