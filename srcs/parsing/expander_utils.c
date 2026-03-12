/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 10:55:12 by erocha--          #+#    #+#             */
/*   Updated: 2026/03/12 18:31:19 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*dollarid_init(t_token *token, int idollar)
{
	char	*dollar_id;
	int		i;

	if (token->value[idollar] == '?')
		return (ft_strdup("?"));
	dollar_id = NULL;
	i = 0;
	while (ft_isalnum(token->value[idollar + i])
		|| token->value[idollar + i] == '_')
		i++;
	dollar_id = malloc(sizeof(char) * (i + 1));
	if (!dollar_id)
		return (NULL);
	ft_strlcpy(dollar_id, token->value + idollar, i + 1);
	return (dollar_id);
}

static void	no_value_handling(t_token **token, int *idollar, char **dollar_id)
{
	char	*tmp;
	char	*old_value;

	tmp = ft_substr((*token)->value, 0, (*idollar));
	old_value = (*token)->value;
	(*token)->value = ft_strjoin(tmp, old_value + (*idollar)
		+ ft_strlen((*dollar_id)) + 1);
	free(tmp);
	free(old_value);
	if (*dollar_id)
		free(*dollar_id);
	(*idollar) = (*idollar) - 1;
}

void	research_implement(t_token **token, t_env *envs, int *idollar)
{
	char	*tmp1;
	char	*tmp2;
	char	*dollar_id;
	char	*dollar_value;

	dollar_id = dollarid_init(*token, *idollar + 1);
	if (dollar_id && dollar_id[0] == '?' && !dollar_id[1])
		dollar_value = ft_itoa(g_signal);
	else if (dollar_id)
		dollar_value = get_args_envp(dollar_id, envs);
	if ((dollar_id && dollar_id[0] == '?' && !dollar_id[1]) || dollar_id)
	{
		tmp1 = ft_substr((*token)->value, 0, *idollar);
		tmp2 = ft_strjoin(tmp1, dollar_value);
		free(tmp1);
		tmp1 = ft_strjoin(tmp2, (*token)->value + (*idollar) + ft_strlen(dollar_id) + 1);
		free((*token)->value);
		(*token)->value = tmp1;
		free(tmp2);
		(*idollar) = (*idollar) + ft_strlen(dollar_value) - 1;
		free(dollar_value);
		free(dollar_id);
	}
	else
		no_value_handling(token, idollar, &dollar_id);
}

void	remove_quote(t_token **token)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = malloc(sizeof(char) * (ft_strlen((*token)->value) + 1));
	while ((*token)->value[i])
	{
		if ((*token)->value[i] != '\'' && (*token)->value[i] != '\"')
		{
			str[j] = (*token)->value[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
	free((*token)->value);
	(*token)->value = str;
}
