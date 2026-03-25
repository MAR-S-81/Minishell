/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 14:49:45 by mchesnea          #+#    #+#             */
/*   Updated: 2026/03/25 18:46:19 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*get_env_node(char *key, t_env *lst)
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

static void	print_export_line(char *env_str, int fd_out)
{
	int	j;

	j = 0;
	write(fd_out, "declare -x ", 11);
	while (env_str[j] && env_str[j] != '=')
		write(fd_out, &env_str[j++], 1);
	if (env_str[j] == '=')
	{
		write(fd_out, "=\"", 2);
		j++;
		while (env_str[j])
			write(fd_out, &env_str[j++], 1);
		write(fd_out, "\"", 1);
	}
	write(fd_out, "\n", 1);
}

int	export_no_args(t_env **lst, int fd_out)
{
	char	**str;
	int		i;

	str = env_list_to_tab(*lst);
	if (!str)
		return (1);
	str = sort_tab_tab(str);
	i = 0;
	while (str[i])
	{
		print_export_line(str[i], fd_out);
		free(str[i]);
		i++;
	}
	free(str);
	return (0);
}

static int	add_new_export(t_env **lst, char *keys, char *value)
{
	t_env	*new;
	char	*key_copy;
	char	*value_copy;

	key_copy = ft_strdup(keys);
	value_copy = NULL;
	if (value)
		value_copy = ft_strdup(value);
	if (!key_copy)
		return (1);
	new = lstnew(key_copy, value_copy);
	if (!new)
	{
		free(key_copy);
		if (value_copy)
			free(value_copy);
		return (1);
	}
	lstadd_back(lst, new);
	return (0);
}

int	export(t_env **lst, char *keys, char *value)
{
	t_env	*actual;
	int		ret;

	if (!keys)
		return (1);
	actual = get_env_node(keys, *lst);
	if (actual != NULL)
	{
		if (value)
		{
			if (actual->value)
				free(actual->value);
			actual->value = ft_strdup(value);
		}
		return (0);
	}
	ret = add_new_export(lst, keys, value);
	return (ret);
}
