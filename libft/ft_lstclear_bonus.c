/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 16:50:25 by mchesnea          #+#    #+#             */
/*   Updated: 2025/10/23 17:44:33 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*check;
	t_list	*temp;

	if (!lst || !del)
		return ;
	check = *lst;
	while (check != NULL)
	{
		del(check->content);
		temp = check->next;
		free(check);
		check = temp;
	}
	*lst = NULL;
}
