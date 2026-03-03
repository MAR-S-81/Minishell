///* ************************************************************************** */
///*                                                                            */
///*                                                        :::      ::::::::   */
///*   expander_utils.c                                   :+:      :+:    :+:   */
///*                                                    +:+ +:+         +:+     */
///*   By: enzorolinux <enzorolinux@student.42.fr>    +#+  +:+       +#+        */
///*                                                +#+#+#+#+#+   +#+           */
///*   Created: 2026/02/25 10:55:12 by erocha--          #+#    #+#             */
///*   Updated: 2026/03/03 14:41:55 by enzorolinux      ###   ########.fr       */
///*                                                                            */
///* ************************************************************************** */

//#include "minishell.h"

//static char	*create_dollar(char *srcstr, int i)
//{
//	char	*dollar;
//	int		j;

//	j = 0;
//	while (ft_isprint(srcstr[i + j + 1]) && srcstr[i + j + 1] != '\'' &&
//		srcstr[i + j + 1] != ':' && srcstr[i + j + 1])
//		j++;
//	dollar = malloc(sizeof(char) * (j + 1));
//	j = 0;
//	while (ft_isprint(srcstr[i + j + 1]) && srcstr[i + j + 1] != '\'' &&
//		srcstr[i + j + 1] != ':' && srcstr[i + j + 1])
//	{
//		dollar[j] = srcstr[i + j + 1];
//		j++;
//	}
//	return (dollar);
//}

//char	*found_dollar(char *srcstr)
//{
//	int		i;
//	int		in_squote;
//	char	*dollar;

//	i = 0;
//	in_squote = 0;
//	dollar = NULL;
//	while (srcstr[i])
//	{
//		if (srcstr[i] == '\'')
//			in_squote = !in_squote;
//		if (srcstr[i] == ':' && !in_squote)
//			dollar = create_dollar(srcstr, i);
//		i++;
//	}
//	return (dollar);
//}

//char	*add_dollar(t_token **token, char *new_value, char *old_dollar)
//{
//	char	*str;
//	int		i;
//	int		len_token;
//	int		len_dollar;

//	str = NULL;
//	i = 0;
//	len_token = ft_strlen((*token)->value);
//	len_dollar = ft_strlen(old_dollar);
//	while ((*token)->value[i])
//	{
//		if ((*token)->value[i] == ':' && (*token)->value[i + 1])
//		{
//			if (!ft_strncmp(ft_substr((*token)->value, i + 1, len_token), old_dollar, len_dollar))
//			{
//				str = malloc(sizeof(char) * (len_dollar + len_token));
//				ft_strlcpy(str, (*token)->value, i);
//				str = ft_strjoin(str, new_value);
//				str = ft_strjoin(str, (*token)->value + i + ft_strlen(new_value));
//			}
//		}
//		i++;
//	}
//	free((*token)->value);
//	return (str);
//}
