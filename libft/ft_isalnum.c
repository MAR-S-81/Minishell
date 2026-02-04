/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 15:29:09 by mchesnea          #+#    #+#             */
/*   Updated: 2025/10/16 14:44:12 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int charactere)
{
	if ((charactere >= 65 && charactere <= 90) || (charactere >= 97
			&& charactere <= 122) || (charactere >= 48 && charactere <= 57))
		return (8);
	return (0);
}
