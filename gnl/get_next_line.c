/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 10:36:22 by mchesnea          #+#    #+#             */
/*   Updated: 2025/11/17 11:53:29 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_extract_line(char *var)
{
	int		i;
	char	*line;

	i = 0;
	if (!var)
		return (NULL);
	while (var[i] != '\n' && var[i])
		i++;
	line = ft_substr(var, 0, (i + 1));
	return (line);
}

char	*ft_update_line(char *var)
{
	int		i;
	char	*new_var;

	i = 0;
	while (var[i] && var[i] != '\n')
		i++;
	new_var = ft_substr(var, (i + 1), (ft_strlen(var) - (i + 1)));
	if (!new_var)
	{
		free(var);
		return (NULL);
	}
	free(var);
	return (new_var);
}

void	ft_var(char **var, int fd, char *buff)
{
	char	*tmp;
	int		read_size;

	read_size = 1;
	while (read_size > 0 && ft_strchr(*var, '\n') == NULL)
	{
		read_size = read(fd, buff, BUFFER_SIZE);
		if (read_size < 0)
		{
			if (*var != NULL)
			{
				free(*var);
				*var = NULL;
			}
			return ;
		}
		buff[read_size] = '\0';
		tmp = *var;
		*var = ft_strjoin(tmp, buff);
		free(tmp);
	}
}

char	*get_next_line(int fd)
{
	static char	*var = NULL;
	char		*buff;
	char		*line;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	ft_var(&var, fd, buff);
	free(buff);
	if (!var)
		return (NULL);
	if (var && var[0] == '\0')
	{
		free(var);
		var = NULL;
		return (NULL);
	}
	line = ft_extract_line(var);
	if (!line)
		return (NULL);
	var = ft_update_line(var);
	return (line);
}

