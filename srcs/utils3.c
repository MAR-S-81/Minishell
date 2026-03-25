/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 14:18:31 by mchesnea          #+#    #+#             */
/*   Updated: 2026/03/25 19:04:09 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_n(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	close_saved_fds(void)
{
	int	i;

	i = 3;
	while (i < 1024)
	{
		close(i);
		i++;
	}
}

void	free_cmds(t_cmd **cmds)
{
	t_cmd	*next;
	int		i;

	while (*cmds)
	{
		next = (*cmds)->next;
		i = 0;
		while ((*cmds)->args && (*cmds)->args[i])
			free((*cmds)->args[i++]);
		free((*cmds)->args);
		free(*cmds);
		*cmds = next;
	}
	*cmds = NULL;
}

char	**sort_tab_tab(char **tab)
{
	int		i;
	int		j;
	size_t	len;

	i = 0;
	if (!tab)
		return (NULL);
	while (tab[i])
	{
		j = i + 1;
		while (tab[j])
		{
			len = ft_strlen(tab[i]);
			if (ft_strlen(tab[j]) > len)
				len = ft_strlen(tab[j]);
			if (ft_strncmp(tab[i], tab[j], len + 1) > 0)
			{
				ft_swap(&tab[i], &tab[j]);
			}
			j++;
		}
		i++;
	}
	return (tab);
}
