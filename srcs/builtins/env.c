/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 15:36:57 by mchesnea          #+#    #+#             */
/*   Updated: 2026/03/04 13:41:31 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(t_env *lst, int fd_out)
{
	char	**str;
	int		i;

	i = 0;
	str = env_list_to_tab(lst);
	if (!str)
		return ;
	while (str[i])
	{
		write(fd_out, str[i], ft_strlen(str[i]));
		write(fd_out, "\n", 1);
		free(str[i]);
		i++;
	}
	free(str);
}
