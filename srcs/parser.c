/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lterrail <lterrail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 12:24:32 by lterrail          #+#    #+#             */
/*   Updated: 2018/11/29 17:59:28 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		ft_parse_builtins(t_ms *ms, char *line)
{
	if (!ft_strcmp(ms->first_argc, "exit"))
		ft_exit(ms, NULL, NULL);
	else if (!ft_strcmp(ms->first_argc, "cd"))
		ft_init_cd(ms, ft_epur_line(line, 2));
	else if (!ft_strcmp(ms->first_argc, "unsetenv"))
		ft_unsetenv(ms, ft_epur_line(line, 8));
	else if (!ft_strcmp(ms->first_argc, "setenv"))
		ft_setenv(ms, ft_epur_line(line, 6), 0);
	else if (!ft_strcmp(line, "env -i"))
	{
		ft_free_tab(ms->env, ms->len_env);
		ms->len_env = 0;
		if (!(ms->env = (char **)malloc(sizeof(char *) * (ms->len_env + 1))))
			ft_exit(ms, NULL, "Failed to malloc env");
		ms->env[ms->len_env] = NULL;
	}
	else if (!ft_strcmp(ms->first_argc, "env"))
		ft_print_env(ms);
	else if (!ft_strcmp(ms->first_argc, "echo"))
		(line = ft_epur_line(line, 4)) ? 0 : ft_printf("%s\n", line);
	else
		return (0);
	return (1);
}

static void		ft_parse_cmd(t_ms *ms, char *line)
{
	char	*path;

	path = NULL;
	if (!ft_strcmp(ms->first_argc, "path"))
		ft_print_paths(ms);
	else if ((path = ft_search_valid_builtin(ms)))
	{
		if (ft_strstr(path, "cat"))
			g_reset_input = 1;
		ft_exec_cmd(ms, path, line);
		free(path);
	}
	else if (!path)
		ft_exec_cmd_with_path(ms, ms->first_argc, line);
	else
		ft_printf("{red}%s: Command not found{eoc}\n", ms->first_argc);
}

int				ft_parser(t_ms *ms, char *line)
{
	line = ft_epur_line(line, 0);
	if (!line)
		return (E_ERROR);
	ft_get_first_argc(ms, line);
	if (!ft_parse_builtins(ms, line))
		ft_parse_cmd(ms, line);
	free(ms->first_argc);
	return (E_SUCCESS);
}
