/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 13:05:16 by mchesnea          #+#    #+#             */
/*   Updated: 2025/10/24 11:29:27 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_word(char const *s, char c)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			nb++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (nb);
}

static void	*free_all(char **dest, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		if (dest[i] == NULL)
		{
			while (j > 0)
			{
				j--;
				free(dest[j]);
			}
			free(dest);
			return (NULL);
		}
		i++;
	}
	return (dest);
}

char	**ft_split(char const *s, char c)
{
	char	**dest;
	int		len;
	int		j;

	j = 0;
	if (!s)
		return (NULL);
	dest = malloc((count_word(s, c) + 1) * sizeof(char *));
	if (!dest)
		return (NULL);
	while (*s)
	{
		len = 0;
		while (s[len] && s[len] != c)
			len++;
		if (len)
			dest[j++] = ft_substr(s, 0, len);
		while (s[len] && s[len] == c)
			len++;
		s += len;
	}
	dest[j] = NULL;
	dest = free_all(dest, j);
	return (dest);
}
