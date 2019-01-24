/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lterrail <lterrail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 12:25:07 by lterrail          #+#    #+#             */
/*   Updated: 2019/01/24 12:41:56 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <time.h>
# include <dirent.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# include <pwd.h>
# include <grp.h>

# define E_SUCCESS 1
# define E_ERROR 0

typedef void	(*t_sighandler)(int);

int g_reset_input;

typedef struct		s_ms
{
	char			**env;
	char			**paths;
	char			**argcs;
	char			*first_argc;
	char			**options;
	char			*prompt;
	char			*pwd;
	char			*old_pwd;
	int				first_call;
}					t_ms;

/*
**chdir.c
*/
void				ft_chdir_back(t_ms *ms, char *line, int i);
void				ft_chdir(t_ms *ms, char *line, int i);

/*
**exec_cmd.c
*/
void				ft_exec_cmd(t_ms *ms, char *path, char *line, char **env);

/*
**ft_exit.c
*/
void				ft_exit(t_ms *ms, char *str, char *msg);
void				ft_free_cd(t_ms *ms);
void				ft_free_tab(char **tab);

/*
**find_variable_in_env.c
*/
int					ft_is_variable(char *str);
int					ft_find_env_variable(char **env, char *var);
int					ft_find_and_copy_paths(t_ms *ms, char **env);
char				*ft_find_valid_builtin(t_ms *ms, char *cmd, char **env);

/*
**parser.c
*/
int					ft_parser(t_ms *ms, char *line);

/*
**prints.c
*/
void				ft_print_paths(t_ms *ms);
void				ft_print_env(char **env);
void				ft_print_prompt(void);

/*
**ft_signal_handler.c
*/
void				ft_signal_handler(int sig);

/*
**parse_and_clear_cmd.c
*/
int					cmd_parser_echaper(char *s);
int					cmd_parser_interpret_quot(char *s);
int					cmd_parser_dollars(t_ms *ms, char *line, int index);

/*
**builtin_echo.c
*/
void				ft_echo(t_ms *ms, char *line);

/*
**builtin_unset_set_env.c
*/
char				**ft_unsetenv(t_ms *ms, char *line, char **env);
char				**ft_setenv(t_ms *ms, char *line, int flag, char **env);

/*
**builtin_env.c
*/
char				**ft_delete_env(t_ms *ms, char **env);
void				ft_parse_env(t_ms *ms, char *line, char **env);
char				**ft_refresh_variable_shlvl(t_ms *ms, char **env);

/*
**builtin_cd.c
*/
void				ft_init_cd(t_ms *ms, char *line);

/*
**utils.c
*/
char				*ft_epur_line(char *line, int len);
void				ft_get_first_argc(t_ms *ms, char *line);
char				*ft_get_last_argc(char *str);
char				*ft_strndup(const char *s1, size_t n);

#endif
