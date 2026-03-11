/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erocha-- <erocha--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 13:07:08 by mchesnea          #+#    #+#             */
/*   Updated: 2026/03/11 15:21:37 by erocha--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*add_slash_and_check(char *cmd, char **dest)
{
	int		i;
	char	*tmp;
	char	*rep;

	i = 0;
	while (dest[i])
	{
		tmp = ft_strjoin(dest[i], "/");
		if (!tmp)
			return (NULL);
		rep = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!rep)
			return (NULL);
		if (access(rep, F_OK | X_OK) == 0)
			return (rep);
		free(rep);
		i++;
	}
	return (NULL);
}

char	*find_path(char *cmd, t_env *lst)
{
	char	**dest;
	char	*args;
	char	*rep;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	args = get_args_envp("PATH", lst);
	dest = ft_split(args, ':');
	if (!dest)
		return (NULL);
	rep = add_slash_and_check(cmd, dest);
	return (rep);
}

char	**env_list_to_tab(t_env *env)
{
	char	**ret;
	char	*tmp;
	int		len;
	t_env	*tmp_lst;

	len = 0;
	tmp_lst = env;
	while (tmp_lst)
	{
		len++;
		tmp_lst = tmp_lst->next;
	}
	ret = malloc(sizeof(char *) * (len + 1));
	if (!ret)
		return (NULL);
	len = 0;
	while (env)
	{
		tmp = ft_strjoin(env->key, "=");
		ret[len++] = ft_strjoin(tmp, env->value);
		free(tmp);
		env = env->next;
	}
	ret[len] = NULL;
	return (ret);
}
