/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 14:49:45 by mchesnea          #+#    #+#             */
/*   Updated: 2026/03/02 15:41:39 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_swap(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

static char	**sort_tab_tab(char **tab)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	if (!tab)
		return (NULL);
	while (tab[i])
	{
		j = i + 1;
		while (tab[j])
		{
			if (ft_strlen(tab[i]) > ft_strlen(tab[j]))
				len = ft_strlen(tab[i]);
			else
				len = ft_strlen(tab[j]);
			if (ft_strncmp(tab[i], tab[j], len) > 0)
			{
				ft_swap(&tab[i], &tab[j]);
			}
			j++;
		}
		i++;
	}
	return (tab);
}

void	export_no_args(t_env **lst, int fd_out)
{
	char	**str;
	int		i;

	i = 0;
	str = env_list_to_tab(*lst);
	str = sort_tab_tab(str);
	while (str[i])
	{
		write(fd_out, &"declare -x ", 11);
		write(fd_out, str[i], ft_strlen(str[i]));
		write(fd_out, &"\n", 1);
		free(str[i]);
		i++;
	}
}

void	export(t_env **lst, char *keys, char *value)
{
	t_env	*new;
	char	*key_copy;
	char	*value_copy;

	key_copy = ft_strdup(keys);
	value_copy = NULL;
	if (value)
		value_copy = ft_strdup(value);
	if (!key_copy)
		return ;
	new = lstnew(key_copy, value_copy);
	if (!new)
	{
		free(key_copy);
		free(value_copy);
		return ;
	}
	lstadd_back(lst, new);
}
