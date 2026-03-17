/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 13:07:08 by mchesnea          #+#    #+#             */
/*   Updated: 2026/03/17 16:48:55 by mchesnea         ###   ########.fr       */
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
		return (ft_strdup(cmd));
	args = get_args_envp("PATH", lst);
	if (!args)
		return (NULL);
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

void	execute_command(t_cmd *cmd, t_env **lst)
{
	t_exec	exec;

	if (!cmd)
		return ;
	if (!init_t_exec(&exec, cmd))
		return ;
	if (exec.nb_cmds == 1 && is_buildins(cmd->args[0]))
		exec_single_builtin(cmd, lst);
	else
		execute(cmd, exec, *lst);
	if (exec.pids)
		free(exec.pids);
}