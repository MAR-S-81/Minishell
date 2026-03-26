/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_check_util.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erocha-- <erocha--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 15:34:35 by erocha--          #+#    #+#             */
/*   Updated: 2026/03/26 15:51:51 by erocha--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	format_check_middle(t_token *token)
{
	if (token->type == token->next->type && token->type == TOKEN_PIPE)
	{
		write(2, "minishell: syntax error near unexpected token `|'\n", 50);
		g_signal = 2;
		return (1);
	}
	if ((token->type != TOKEN_PIPE && token->type != TOKEN_WORD)
		&& token->next->type != TOKEN_WORD)
	{
		write(2, "minishell: syntax error near unexpected token\n", 46);
		g_signal = 2;
		return (1);
	}
	return (0);
}
