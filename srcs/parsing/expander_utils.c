/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erocha-- <erocha--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 10:55:12 by erocha--          #+#    #+#             */
/*   Updated: 2026/03/04 17:44:54 by erocha--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*dollarid_init(t_token *token, int idollar, int *i)
{
	char	*dollar_id;

	dollar_id = NULL;
	while (ft_isprint(token->value[idollar + *i]) && token->value[idollar + *i] != ':'
		&& token->value[idollar + *i] != '\'' && token->value[idollar + *i] != '\"')
		(*i)++;
	dollar_id = malloc(sizeof(char) * (*i));
	dollar_id[*i] = '\0';
	(*i) = 0;
	while (ft_isprint(token->value[idollar + *i]) && token->value[idollar + *i] != ':'
		&& token->value[idollar + *i] != '\'' && token->value[idollar + *i] != '\"')
	{
		dollar_id[*i] = token->value[idollar + *i];
		(*i)++;
	}
	return (dollar_id);
}

void	research_implement(t_token **token, t_env *envs, int *idollar)
{
	char	*dollar_id;
	char	*dollar_value;
	char	*str;
	int		i;

	i = 0;
	(*idollar)++;
	dollar_id = dollarid_init(*token, *idollar, &i);
	dollar_value = get_args_envp(dollar_id, envs);
	str = malloc(sizeof(char) * (ft_strlen((*token)->value) + 1));
	ft_strlcpy(str, (*token)->value, (*idollar));
	if (dollar_value)
	{
		str = ft_strjoin(str, dollar_value);
		(*idollar) += i;
		str = ft_strjoin(str, (*token)->value + (*idollar));
	}
	else
	{
		str = ft_strjoin(str, (*token)->value + (*idollar) + i);
		(*idollar) = (*idollar) - 2;
	}
	free((*token)->value);
	(*token)->value = str;
}

void	varenv_handling(t_token **token, int *idollar)
{
	char	*str;
	char	*nbr;
	
	str = malloc(sizeof(char) * ft_strlen((*token)->value));
	ft_strlcpy(str, (*token)->value, (*idollar));
	nbr = ft_itoa(g_signal_status);
	str = ft_strjoin(str, nbr);
	str = ft_strjoin(str, (*token)->value + (*idollar) + 2);
	(*idollar) = ft_strlen(str);
	free((*token)->value);
	(*token)->value = str;
}