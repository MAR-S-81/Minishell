/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erocha-- <erocha--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 17:52:08 by mchesnea          #+#    #+#             */
/*   Updated: 2026/03/11 17:13:24 by erocha--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <gnl/get_next_line.h>
# include <libft/libft.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define RESET "\001\033[0m\002"
# define GREEN "\001\033[1;32m\002"
# define ORANGE "\001\033[1;33m\002"

extern int	g_signal;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_HERE_DOC,
	TOKEN_APPEND
}					t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}					t_token;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_cmd
{
	char **args; // {"ls", "-l", NULL}
	int				fd_in;
	int				fd_out;
	int error_redir; // 0 par défaut, 1 si un open a foiré
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_exec
{
	int				pipe_fd[2];
	int				fd_temp;
	int				nb_cmds;
	pid_t			*pids;
}					t_exec;

void				quotes_handling(t_token **token, char *arg, int *i, int *j);
void				token_typer(t_token **token);
t_token				*create_token(t_token **token);
void				arger(t_token **token, t_token **token_tmp, char *arg, int *i);
t_cmd				*parsing(char *arg, t_env *envs);
void				research_implement(t_token **token, t_env *envs, int *idollar);
void				remove_quote(t_token **tokens);
void				clean_exit(t_token *tokens);
char				*get_args_envp(char *str, t_env *lst);
void				split_key_values(char **envp, t_env **lst);
char				**env_list_to_tab(t_env *env);
t_env				*lstnew(char *key, char *value);
void				lstadd_back(t_env **lst, t_env *new);
void				env(t_env *lst, int fd_out);
void				lstdelone(t_env **head, t_env *to_del);
void				lstclear(t_env **lst);
long long			ft_atoll_check(const char *str, long long *nb);
int					ft_all_digit(char *str);
int					is_buildins(char *arg);
void				cd(t_env *lst, char *args);
void				echo(char **strs, int n, int fd_out);
void				my_exit(char **args, int status);
void				pwd(t_env *env, int fd_out);
void				unset(t_env **lst, char *keys);
void				export(t_env **lst, char *keys, char *value);
void				export_no_args(t_env **lst, int fd_out);
void				ft_swap(char **a, char **b);
void				free_tab(char **tab);
char				*find_path(char *cmd, t_env *lst);
int					execute_builtin(char **args, t_env **lst, int fd_out,
						int status);
void				close_all(t_cmd *cmd, t_exec exec);
void				wait_all_children(t_exec exec);
int					init_t_exec(t_exec *exec, t_cmd *cmd);
void				execute(t_cmd *cmd, t_exec exec, char **envp, t_env *lst);
void				execute_command(t_cmd *cmd, t_env **lst, char **envp);
void				exec_single_builtin(t_cmd *cmd, t_env **lst);
int					read_line(t_env **envs, char **envp);
#endif
