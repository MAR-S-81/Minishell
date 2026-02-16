/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 15:31:05 by mchesnea          #+#    #+#             */
/*   Updated: 2026/02/16 18:17:54 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*lstnew(char *key, char *value)
{
	t_env	*dest;

	dest = malloc(sizeof(t_env));
	if (!dest)
		return (NULL);
	dest->key = key;
	dest->value = value;
	dest->next = NULL;
	return (dest);
}

void	lstadd_back(t_env **lst, t_env *new)
{
	t_env	*ret;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	ret = *lst;
	while (ret->next != NULL)
		ret = ret->next;
	ret->next = new;
}

static void	extract_entry(char *env_str, t_env **lst)
{
	char	*key;
	char	*value;
	int		j;

	j = 0;
	while (env_str[j] && env_str[j] != '=')
		j++;
	if (env_str[j] == '=')
	{
		key = ft_substr(env_str, 0, j);
		value = ft_strdup(env_str + j + 1);
	}
	else
	{
		key = ft_strdup(env_str);
		value = NULL;
	}
	if (!key)
	{
		free(value);
		return ;
	}
	lstadd_back(lst, lstnew(key, value));
}

void	split_key_values(char **envp, t_env **lst)
{
	int	i;

	if (!envp || !lst)
		return ;
	i = 0;
	while (envp[i])
	{
		extract_entry(envp[i], lst);
		i++;
	}
}

char	*get_args_envp(char *str, t_env *lst)
{
	int	len;

	if (!str || !lst)
		return (0);
	len = ft_strlen(str);
	while (lst->next != NULL)
	{
		if (ft_strncmp(str, lst->key, ft_strlen(str)) == 0
			&& lst->key[len] == '\0')
			return (lst->value);
		lst = lst->next;
	}
	return (0);
}

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
	int		i;
	char	**dest;
	char	*args;
	char	*rep;

	i = 0;
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

	len = 0;
	while (env)
	{
		len++;
		env = env->next;
	}
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	len = 0;
	while (env)
	{
		tmp = ft_strjoin(env->key, "=");
		ret[len] = ft_strjoin(tmp, env->value);
		free(tmp);
		env = env->next;
		len++;
	}
	ret[len] = NULL;
	return (ret);
}

int	execute_simple_cmd(t_env *lst, char *cmd)
{
	char	**cmd_args;
	char	*path;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		perror("fork");
	if (pid == 0)
	{
		cmd_args = ft_split(cmd, ' ');
		if (!cmd_args)
			exit(1);
		path = find_path(cmd_args[0], lst);
		if (path == NULL)
		{
			write(2, "Command not found\n", 18);
			exit(127);
		}
		execve(path, cmd_args, env_list_to_tab(lst));
		perror("execve");
        exit(126);
	}
	waitpid(pid, NULL, 0);
	return (pid);
}

int	main(int argc, char *argv[], char *envp[])
{
	(void) argc;
	(void) argv;
	t_env *my_env = NULL;

	split_key_values(envp, &my_env);
	execute_simple_cmd(my_env, "ls -l");
}