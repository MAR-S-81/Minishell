/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 14:49:45 by mchesnea          #+#    #+#             */
/*   Updated: 2026/03/02 17:57:37 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	t_env	*get_env_node(char *key, t_env *lst)
{
	int	len;

	if (!key || !lst)
		return (NULL);
	len = ft_strlen(key);
	while (lst != NULL)
	{
		if (ft_strncmp(key, lst->key, len) == 0 && lst->key[len] == '\0')
			return (lst);
		lst = lst->next;
	}
	return (NULL);
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
			len = ft_strlen(tab[i]);
			if (ft_strlen(tab[j]) > len)
				len = ft_strlen(tab[j]);
			if (ft_strncmp(tab[i], tab[j], len + 1) > 0)
			{
				ft_swap(&tab[i], &tab[j]);
			}
		}
		i++;
	}
	return (tab);
}

void	export_no_args(t_env **lst, int fd_out)
{
	char	**str;
	int		i;
	int		j;

	i = -1;
	str = env_list_to_tab(*lst);
	str = sort_tab_tab(str);
	while (str[i++])
	{
		write(fd_out, "declare -x ", 11);
		j = 0;
		while (str[i][j] && str[i][j] != '=')
			write(fd_out, &str[i][j++], 1);
		if (str[i][j] == '=')
		{
			write(fd_out, "=\"", 2);
			j++;
			while (str[i][j])
				write(fd_out, &str[i][j++], 1);
			write(fd_out, "\"", 1);
		}
		write(fd_out, "\n", 1);
		free(str[i]);
	}
	free(str);
}

static void add_new_export(t_env **lst, char *keys, char *value)
{
    t_env   *new;
    char    *key_copy;
    char    *value_copy;

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
        if (value_copy)
            free(value_copy);
        return ;
    }
    lstadd_back(lst, new);
}

void    export(t_env **lst, char *keys, char *value)
{
    t_env   *actual;

    if (!keys)
        return ;
    actual = get_env_node(keys, *lst);
    if (actual != NULL)
    {
        if (value)
        {
            if (actual->value)
                free(actual->value);
            actual->value = ft_strdup(value);
        }
        return ;
    }
    add_new_export(lst, keys, value);
}
