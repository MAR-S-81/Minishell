/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 13:23:46 by mchesnea          #+#    #+#             */
/*   Updated: 2026/03/02 15:41:34 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(char *str, int n, int fd_out)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(fd_out, &str[i], 1);
		i++;
	}
	if (n == 0)
		write(fd_out, &"\n", 1);
}
