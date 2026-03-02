/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 13:00:00 by erocha--          #+#    #+#             */
/*   Updated: 2026/03/02 15:41:56 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

int	parsing(char *arg, char **envp)
{
	t_token	*tokens;
	int		i;

	(void)envp;
	tokens = NULL;
	lexer(&tokens, arg);
	i = 0;
	while (tokens != NULL)
	{
		i++;
		tokens = tokens->next;
	}
	return (i);
}

int	main(int argc, char **argv)
{
	(void)argc;
	printf("%d", parsing(argv[1], NULL));
}