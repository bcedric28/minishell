/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcedric <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 13:18:12 by bcedric           #+#    #+#             */
/*   Updated: 2019/02/27 13:18:13 by bcedric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_path(t_elem *envir)
{
	char	*home;
	char	*oldpath;
	char	*str;
	int		i;

	i = -1;
	home = ft_search_env("HOME", envir);
	oldpath = ft_search_env("OLDPWD", envir);
	if (ft_strcmp(home, oldpath) == 0)
		str = ft_strdup("~");
	else
	{
		while (home[++i])
			if (oldpath[i] != home[i])
				break ;
		str = ft_strjoin("~", &oldpath[i]);
	}
	ft_putendl(str);
	free(str);
	if (home)
		free(home);
	if (oldpath)
		free(oldpath);
}

void	change_dir(char *path, int arguments, t_elem *envir)
{
	char	buff[PATH_MAX];
	char	*cwd;

	cwd = getcwd(buff, PATH_MAX);
	if (!chdir(path))
	{
		if (arguments)
			print_path(envir);
		cwd = ft_strjoin("s OLDPWD ", cwd);
		setenv_builtin(cwd, envir);
		if (cwd)
			free(cwd);
	}
	else
	{
		ft_putstr("cd: ");
		if (access(path, F_OK) == -1)
			ft_putstr("no such file or directory: ");
		else if (access(path, R_OK) == -1)
			ft_putstr("permission denied: ");
		else
			ft_putstr("not a directory: ");
		ft_putendl(path);
	}
}
