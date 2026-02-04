/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 15:12:21 by mchesnea          #+#    #+#             */
/*   Updated: 2025/10/16 14:44:12 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int charactere)
{
	if ((charactere >= 65 && charactere <= 90) || (charactere >= 97
			&& charactere <= 122))
		return (1024);
	return (0);
}
