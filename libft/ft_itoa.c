/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 16:30:56 by mchesnea          #+#    #+#             */
/*   Updated: 2025/10/24 16:19:08 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	sizeofint(long int n)
{
	int	len;

	len = 0;
	if (n <= 0)
	{
		n = n * -1;
		len++;
	}
	while (n > 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char		*dest;
	long int	n2;
	int			len;

	n2 = (long int)n;
	len = sizeofint(n2);
	dest = malloc((1 + len) * sizeof(char));
	if (!dest)
		return (NULL);
	if (n == 0)
		dest[0] = '0';
	dest[len] = '\0';
	if (n < 0)
	{
		dest[0] = '-';
		n2 = n2 * -1;
	}
	while (n2 > 0)
	{
		len--;
		dest[len] = ((n2 % 10) + 48);
		n2 = n2 / 10;
	}
	return (dest);
}
