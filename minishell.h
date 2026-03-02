/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchesnea <mchesnea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 17:52:08 by mchesnea          #+#    #+#             */
/*   Updated: 2026/03/02 17:52:23 by mchesnea         ###   ########.fr       */
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

extern int			g_signal_status;

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
	t_token			*next;
}					t_token;

typedef struct s_args
{
	char			**args;
	int				fd_in;
	int				fd_out;
	t_args			*next;
}					t_args;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

void				quotes_handling(t_token **token, char *arg, int *i, int *j);
void				token_typer(t_token **token);
t_token				*create_node(t_token **token);
void				arger(t_token **token, t_token **token_tmp, char *arg,
						int *i);
int					parsing(char *arg, char **envp);
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
void				echo(char *str, int n, int fd_out);
void				my_exit(char **args);
void				pwd(t_env *env, int fd_out);
void				unset(t_env **lst, char *keys);
void				export(t_env **lst, char *keys, char *value);
void				export_no_args(t_env **lst, int fd_out);
int					execute_simple_cmd(t_env *lst, char *cmd);
void				ft_swap(char **a, char **b);
#endif
