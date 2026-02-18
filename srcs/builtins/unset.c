/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 16:33:31 by mchesnea          #+#    #+#             */
/*   Updated: 2026/02/18 18:47:55 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset(t_env **lst, char *keys)
{
	t_env	*curr;
	int		len;

	if (!lst || !*lst)
		return ;
	curr = *lst;
	len = ft_strlen(keys);
	while (curr)
	{
		if (ft_strncmp(keys, curr->key, len) == 0 && curr->key[len] == '\0')
		{
			lstdelone(lst, curr);
			return ; 
		}
		curr = curr->next;
	}
}

// int	main(int argc, char *argv[], char *envp[])
// {
// 	(void)argc;
// 	(void)argv;
// 	t_env *lst = NULL;
// 	split_key_values(envp, &lst);
// 	export(&lst, "JAIME", "MAEL");
// 	env(lst, 1);
// 	printf("\n\n\n\n\n");
// 	unset(&lst, "JAIME");
// 	env(lst, 1);
//     lstclear(&lst);
// }