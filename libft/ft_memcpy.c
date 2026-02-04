/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 09:55:59 by mchesnea          #+#    #+#             */
/*   Updated: 2025/10/16 16:49:06 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t size)
{
	unsigned char	*ptrs;
	unsigned char	*ptrd;
	size_t			i;

	if (!dest && !src)
		return (NULL);
	ptrs = (unsigned char *)src;
	ptrd = (unsigned char *)dest;
	i = 0;
	while (i != size)
	{
		ptrd[i] = ptrs[i];
		i++;
	}
	return (dest);
}
