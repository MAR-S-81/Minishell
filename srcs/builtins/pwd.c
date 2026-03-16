/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 14:42:14 by mchesnea          #+#    #+#             */
/*   Updated: 2026/03/16 12:27:00 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(int fd_out)
{
	char	*str;
	char	buffer[4096];

	str = getcwd(buffer, 4096);
	if (!str)
	{
		perror("pwd");
		return ;
	}
	write(fd_out, str, ft_strlen(str));
	write(fd_out, "\n", 1);
}
