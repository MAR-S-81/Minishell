/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 16:04:53 by mchesnea          #+#    #+#             */
/*   Updated: 2025/10/23 17:44:40 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	t_list	*check;
	t_list	*nextlst;

	if (!lst || !del)
		return ;
	check = lst;
	nextlst = check->next;
	del(check->content);
	free(lst);
	check = nextlst;
}
