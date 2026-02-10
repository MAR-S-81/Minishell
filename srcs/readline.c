/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 15:16:35 by mchesnea          #+#    #+#             */
/*   Updated: 2026/02/10 17:34:26 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	read_line(void)
{
	char	*input;
	char	*temp;

	input = readline(GREEN " MiniShell" ORANGE " → " RESET);
	while (input != NULL)
	{
		if (input[0] != '\0' && (ft_strncmp(input, temp,
					ft_strlen(input)) != 0))
			add_history(input);
		temp = input;
		input = readline(GREEN " MiniShell" ORANGE " → " RESET);
	}
	free(input);
	free(temp);
	return (0);
}

// int	signal_handler(void)
// {
// 	rl_on_new_line();
// 	rl_replace_line('\0', 0);
// 	rl_redisplay();
// }

int	main(void)
{
	read_line();
}