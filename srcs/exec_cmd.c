/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lterrail <lterrail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 20:23:47 by lterrail          #+#    #+#             */
/*   Updated: 2019/01/21 13:27:24 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_chmod(char *path)
{
	struct stat	stat;

	lstat(path, &stat);
	if (S_ISLNK(stat.st_mode) == 1)
		return (0);
	else if (S_ISFIFO(stat.st_mode) == 1)
		return (0);
	else if (S_ISBLK(stat.st_mode) == 1)
		return (0);
	else if (S_ISCHR(stat.st_mode) == 1)
		return (0);
	else if (S_ISSOCK(stat.st_mode) == 1)
		return (0);
	else if (S_ISDIR(stat.st_mode) == 1)
		return (0);
	else if ((stat.st_mode & S_IXGRP) == 0)
		return (2);
	return (1);
}

static void	ft_fork(t_ms *ms, char *path, char **env)
{
	pid_t	father;
	int		ret;

	ret = 0;
	if ((father = fork()) == -1)
		ft_exit(ms, path, "Failed to fork");
	if (father > 0)
		wait(&father);
	else if (father == 0)
	{
		if ((ret = execve(path, ms->options, env)) == -1)
		{
			free(path);
			ft_exit(ms, NULL, "Failed to execve the program");
		}
		ft_free_tab(env);
		exit(ret);
		ms->env = env;
	}
}

void		ft_exec_cmd(t_ms *ms, char *path, char *line, char **env)
{
	if ((access(path, F_OK) != 0 || !exec_chmod(path))
		&& (access(path, X_OK) != 0 || exec_chmod(path) == 2))
	{
		ft_printf("{red}%s: Command not found{eoc}\n", line);
		return ;
	}
	else if (access(path, F_OK) != 0 || !exec_chmod(path))
	{
		ft_printf("{red}No such file or directory: %s{eoc}\n", line);
		return ;
	}
	else if (access(path, X_OK) != 0 || exec_chmod(path) == 2)
	{
		ft_printf("{red}Permission denied: %s{eoc}\n", line);
		return ;
	}
	if (!(ms->options = ft_strsplit(line, ' ')))
	{
		free(path);
		ft_exit(ms, NULL, "Failed to create ms->options");
	}
	ft_fork(ms, path, env);
	ft_free_tab(ms->options);
	ms->options = NULL;
}
