/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 14:42:14 by mchesnea          #+#    #+#             */
/*   Updated: 2026/03/17 17:55:53 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(int fd_out)
{
	char	*str;
	char	buffer[4096];

	str = getcwd(buffer, 4096);
	if (!str)
	{
		perror("pwd");
		return (1);
	}
	write(fd_out, str, ft_strlen(str));
	write(fd_out, "\n", 1);
	return (0);
}
