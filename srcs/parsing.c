/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erocha-- <erocha--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 13:00:00 by erocha--          #+#    #+#             */
/*   Updated: 2026/02/13 13:36:04 by erocha--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void quotes_handling(t_token *token, char *arg, int *i, int *j)
{
	while (arg[*i] != '"')
	{
		if (arg[*i])
		{
			write(1, "Error\n", 7);
			clean_exit(token);
		}
		token->value[*j] = arg[*i];
		(*i)++;
		(*j)++;
	}
	while (arg[*i] != '\'')
	{
		if (arg[*i])
		{
			write(1, "Error\n", 7);
			clean_exit(token);
		}
		token->value[*j] = arg[*i];
		(*i)++;
		(*j)++;
	}
}

static void lexer(t_token *token, char *arg)
{
	int		i;
	int		j;
	t_token	*token_current;

	token_current = token;
	if (!token)
		token = malloc(sizeof(t_token));
	i = 0;
	while (arg[i])
	{
		j = 0;
		while (arg[i] != ' ' && arg[i])
		{
			if (arg[i] == '"' || arg[i] == '\'')
				quotes_handling(token_current, arg, &i, &j);
			token_current->value[j] = arg[i];
			i++;
			j++;
		}
		token_current->next = malloc(sizeof(t_token));
		token_current = token_current->next;
		i++;
	}
}

int	parsing(char *arg, char **envp)
{
	t_token tokens;
	
	(void)envp;
	lexer(&tokens, arg);
	int i = 0;
	t_token *token_current = &tokens;
	while (token_current)
	{
		i++;
		token_current = token_current->next;
	}
	return (i);
}

int main(int argc, char **argv)
{
	(void)argc;

	parsing(argv[0], NULL);
}