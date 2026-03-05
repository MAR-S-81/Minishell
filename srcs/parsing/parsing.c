/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzorolinux <enzorolinux@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 13:00:00 by erocha--          #+#    #+#             */
/*   Updated: 2026/03/05 20:06:35 by enzorolinux      ###   ########.fr       */
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
			else if (tokens_tmp->value[i] == ':' && ft_isprint(tokens_tmp->value[i + 1])
				&& in_squote == 0)
				research_implement(&tokens_tmp, envs, &i);
			i++;
		}
		tokens_tmp = tokens_tmp->next;
	}
    remove_quote(tokens);
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