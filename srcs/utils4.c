/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 19:03:39 by mchesnea          #+#    #+#             */
/*   Updated: 2026/03/25 19:05:17 by mchesnea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_all(t_cmd *cmd, t_exec exec)
{
	if (exec.pipe_fd[0] > 2)
		close(exec.pipe_fd[0]);
	if (exec.pipe_fd[1] > 2)
		close(exec.pipe_fd[1]);
	if (cmd->fd_in > 2)
		close(cmd->fd_in);
	if (cmd->fd_out > 2)
		close(cmd->fd_out);
	if (exec.fd_temp > 2)
		close(exec.fd_temp);
}
