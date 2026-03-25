/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erocha-- <erocha--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 17:37:18 by erocha--          #+#    #+#             */
/*   Updated: 2026/03/25 18:16:46 by erocha--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*search_word(char *line)
{
	char	*word;
	int		i;

	i = 0;
	if (!line[0])
		return (NULL);
	while ((line[i] && ft_isalnum(line[i])) || line[i] == '?')
		i++;
	word = malloc(sizeof(char) * i + 1);
	i = 0;
	while ((line[i] && ft_isalnum(line[i])) || line[i] == '?')
	{
		word[i] = line[i];
		if (line[i] == '?')
		{
			i++;
			break ;
		}
		i++;
	}
	word[i] = '\0';
	return (word);
}

static char	*hd_implement(char *new_word, char *line, int i, int len_word)
{
	char	*prefix;
	char	*suffix;
	char	*word;

	prefix = ft_substr(line, 0, i);
	suffix = ft_strjoin(prefix, new_word);
	word = ft_strjoin(suffix, line + i + len_word + 1);
	free(prefix);
	free(suffix);
	free(new_word);
	return (word);
}

static char	*reline(char *line, int i, t_env *envs)
{
	char	*new_line;
	char	*the_word;
	int		len_word;
	char	*new_word;
	char	*env_val;

	the_word = search_word(line + i + 1);
	len_word = ft_strlen(the_word);
	if (the_word && !ft_strncmp("?", the_word, len_word))
	{
		free(the_word);
		return (ft_itoa(g_signal));
	}
	env_val = get_args_envp(the_word, envs);
	if (env_val)
		new_word = ft_strdup(env_val);
	else
		new_word = ft_strdup("");
	new_line = hd_implement(new_word, line, i, len_word);
	free(the_word);
	return (new_line);
}

static char	*get_line(int in_quote, t_env *envs)
{
	char	*line;
	char	*tmp;
	int		i;

	if (isatty(STDIN_FILENO))
		write(1, "> ", 2);
	line = get_next_line(0);
	if (!line)
		return (NULL);
	if (in_quote)
		return (line);
	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			tmp = reline(line, i, envs);
			if (tmp)
			{
				free(line);
				line = tmp;
			}
		}
		i++;
	}
	return (line);
}

int	ft_here_doc(char *limiter, int in_quote, t_env *envs)
{
	char	*line;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
	{
		perror("minishell: pipe");
		return (-1);
	}
	if (!limiter)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (-1);
	}
	while (1)
	{
		line = get_line(in_quote, envs);
		if (!line)
			break ;
		if (ft_strlen(line) - 1 == ft_strlen(limiter) && !ft_strncmp(line,
				limiter, ft_strlen(limiter)))
		{
			free(line);
			break ;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		free(line);
	}
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}
