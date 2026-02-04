/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 10:24:30 by mchesnea          #+#    #+#             */
/*   Updated: 2025/10/16 16:49:32 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t size)
{
	unsigned char	*ptrs;
	unsigned char	*ptrd;

	if (!dest && !src)
		return (NULL);
	ptrs = (unsigned char *)src;
	ptrd = (unsigned char *)dest;
	if (ptrd < ptrs)
		ft_memcpy(ptrd, ptrs, size);
	else
	{
		while (size-- > 0)
			ptrd[size] = ptrs[size];
	}
	return (dest);
}
