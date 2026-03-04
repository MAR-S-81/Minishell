/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erocha-- <erocha--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 13:00:00 by erocha--          #+#    #+#             */
/*   Updated: 2026/03/04 16:15:31 by erocha--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	lexer(t_token **token, char *arg)
{
	int		i;
	t_token	*token_tmp;

	i = 0;
	while (!ft_isprint(arg[i]) && arg[i])
		i++;
	if (!arg[i])
		return ;
	(*token) = create_node(token);
	token_tmp = (*token);
	while (arg[i])
	{
		if (ft_isprint(arg[i]) && arg[i])
			arger(token, &token_tmp, arg, &i);
		while (!ft_isprint(arg[i]) && arg[i])
			i++;
		if (arg[i])
		{
			token_tmp->next = create_node(token);
			token_tmp = token_tmp->next;
		}
	}
}

//static void	expander(t_token **tokens, t_env *envs)
//{
//	t_token	*tokens_tmp;
//	char	*new_value;
//	char	*dollar;

//	tokens_tmp = *tokens;
//	while (tokens_tmp != NULL)
//	{
//		dollar = NULL;
//		while (ft_strchr(tokens_tmp->value, ':') && ft_isprint(tokens_tmp->value[1]))
//		{
//			dollar = found_dollar(tokens_tmp->value);
//			new_value = get_args_envp(dollar, envs);
//			if (new_value != NULL)
//				tokens_tmp->value = add_dollar(&tokens_tmp, new_value, dollar);
//			else
//				tokens_tmp->value = ft_strdup("");
//			if (dollar)
//				free(dollar);
//		}
//		tokens_tmp = tokens_tmp->next;
//	}
//}

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

static void	research_implement(t_token **token, t_env *envs, int *idollar)
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

static void	varenv_handling(t_token **token, int *idollar)
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

static void	expander(t_token **tokens, t_env *envs)
{
	t_token	*tokens_tmp;
	int		in_squote;
	int		i;

	tokens_tmp = *tokens;
	in_squote = 0;
	while (tokens_tmp != NULL)
	{
		i = 0;
		while (tokens_tmp->value[i])
		{
			if (tokens_tmp->value[i] == '\'')
				in_squote = !in_squote;
			if (tokens_tmp->value[i] == ':' && tokens_tmp->value[i + 1] == '?'
				&& in_squote == 0)
				varenv_handling(tokens, &i);
			else if (tokens_tmp->value[i] == ':' && ft_isprint(tokens_tmp->value[i + 1])
				&& in_squote == 0)
				research_implement(&tokens_tmp, envs, &i);
			i++;
		}
		tokens_tmp = tokens_tmp->next;
	}
}

int	parsing(char *arg, t_env *envs)
{
	t_token	*tokens;
	
	tokens = NULL;
	lexer(&tokens, arg);
	//(void)envs;
    expander(&tokens, envs);
	int i = 0;
	t_token	*tokens_tmp = tokens;
	while (tokens_tmp != NULL)
	{
		i++;
		printf("\n%s", tokens_tmp->value);
		tokens_tmp = tokens_tmp->next;
	}
	return (i);
}

int	main(int argc, char **argv)
{
	t_env	*envs;

	envs = malloc(sizeof(t_env));
	envs->key = ft_strdup("TEST");
	envs->value = ft_strdup("result");
	(void)argc;
	printf("\n%d", parsing(argv[1], envs));
}