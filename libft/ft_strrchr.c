/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 12:40:08 by mchesnea          #+#    #+#             */
/*   Updated: 2025/10/23 19:48:19 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int searchchar)
{
	int				i;
	unsigned char	c;

	i = ft_strlen(str);
	c = (unsigned char)searchchar;
	while (i >= 0)
	{
		if (str[i] == c)
			return ((char *)str + i);
		i--;
	}
	if (c == '\0' && !str[i])
		return ((char *)str + i);
	return (NULL);
}
