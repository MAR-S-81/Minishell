/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote_extend.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erocha-- <erocha--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 15:48:35 by erocha--          #+#    #+#             */
/*   Updated: 2026/03/26 15:51:43 by erocha--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_quote_extend(t_token **token, char quote_type, int i)
{
	if ((*token)->value[i] == quote_type)
		quote_type = '\0';
	else
		quote_type = (*token)->value[i];
	(*token)->in_quote = 1;
}
