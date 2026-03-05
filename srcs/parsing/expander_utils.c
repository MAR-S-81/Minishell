/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzorolinux <enzorolinux@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 10:55:12 by erocha--          #+#    #+#             */
/*   Updated: 2026/03/05 20:06:58 by enzorolinux      ###   ########.fr       */
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
	dollar_id[i] = '\0';
	i = 0;
	while (ft_isalnum(token->value[idollar + i])
		|| token->value[idollar + i] == '_')
	{
		dollar_id[i] = token->value[idollar + i];
		i++;
	}
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
	char	*dollar_id;
	char	*dollar_value;
	char	*tmp2;

	dollar_id = dollarid_init(*token, *idollar + 1);
	if (dollar_id && dollar_id[0] == '?' && !dollar_id[1])
		dollar_value = ft_itoa(5);
	else if (dollar_id)
		dollar_value = get_args_envp(dollar_id, envs);
	if (dollar_value)
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

void	remove_quote(t_token **tokens)
{
	t_token *tokens_tmp;
	char	*str;
	int		i;
	int		j;

	tokens_tmp = *tokens;
	while (tokens_tmp)
	{
		i = 0;
		j = 0;
		str = malloc(sizeof(char) * (ft_strlen(tokens_tmp->value) + 1));
		while (tokens_tmp->value[i])
		{
			if (tokens_tmp->value[i] != '\'' && tokens_tmp->value[i] != '\"')
			{
				str[j] = tokens_tmp->value[i];
				j++;
			}
			i++;
		}
		str[j] = '\0';
		free(tokens_tmp->value);
		tokens_tmp->value = str;
		tokens_tmp = tokens_tmp->next;
	}
}
