/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arger.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erocha-- <erocha--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 15:47:22 by erocha--          #+#    #+#             */
/*   Updated: 2026/03/26 15:51:57 by erocha--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	arger(t_token **token, t_token **token_tmp, char *arg, int *i)
{
	int	j;

	(*token_tmp)->value = malloc(sizeof(char) * (ft_strlen(&arg[*i]) + 1));
	if (!(*token_tmp)->value)
		clean_exit(*token);
	j = arger_extend(token_tmp, arg, i);
	if (j == -1)
		return ;
	(*token_tmp)->value[j] = '\0';
	(*token_tmp)->type = TOKEN_WORD;
}
