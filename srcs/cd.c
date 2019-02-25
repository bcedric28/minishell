/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcedric <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 08:14:29 by bcedric           #+#    #+#             */
/*   Updated: 2019/02/25 08:14:30 by bcedric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

void	print_path()
{
	char *home;
	char *oldpath;
	char *str;
	int i;

	i = 0;
	home = ft_search_env("HOME");
	oldpath = ft_search_env("OLDPWD");
	if (ft_strcmp(home, oldpath) == 0)
		str = ft_strdup("~");
	else
	{
		while(home[i])
		{
			if (oldpath[i] != home[i])
				break ;
			i++;
		}
		str = ft_strjoin("~", &oldpath[i]);
	}
	ft_putendl(str);
	free(str);
}

void	change_dir(char *path, int arguments)
{
	char buff[PATH_MAX];
	char *cwd;

	cwd = getcwd(buff, PATH_MAX);
	if (!chdir(path))
	{
		if (arguments)
			print_path();
		cwd = ft_strjoin("s OLDPWD ", cwd);
		setenv_builtin(cwd);
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

char	*only_path(int pos)
{
	char *str;
	int j;

	j = 0;
	while(g_env[pos][j])
	{
		if(g_env[pos][j - 1] == '=')
			break ;
		j++;
	}
	str = ft_strdup(&g_env[pos][j]);
	return (str);
}

char	*ft_search_env(char *path)
{
	int i;
	char **copy;

	copy = split_and_delete();
	i = 0;
	while(copy[i])
	{
		if (ft_strequ(copy[i], path))
		{
			return(only_path(i));
		}
		i++;
	}
	return(NULL);
}

void	many_arguments(char **tab)
{
	if (tab[2])
	{
		ft_putendl("cd: too many arguments");
		return ;
	}
	
}

void		ft_dollar(char *dollar)
{
	char **tab_dollar;
	char *path;
	char *home;

	path = NULL;
	tab_dollar = ft_strsplit(dollar, '$');
	if (ft_strcmp(tab_dollar[0], "~") == 0)
	{
		home = ft_search_env("HOME");
		change_dir(home, 0);
		return ;
	}
	path = ft_search_env(tab_dollar[0]);
	if (path == NULL)
		return ;
	else
		change_dir(path, 0);
	return ;
}

void	cd_builtin(char *cd)
{
	char **tab;
	char *home;

	tab = ft_strsplit_space(cd);
	home = ft_search_env("HOME");
	if (tab[1] == NULL)
	{
		change_dir(home, 0);
		return ;
	}
	else
	{
		if (ft_strequ(tab[1], "--"))
		{
				change_dir(home, 0);
				return ;
		}
		else if (tab[1][0] == '-' && !tab[1][2])
		{
			change_dir(ft_search_env("OLDPWD"), 1);
			return ;
		}
		else if (tab[1][0] == '$' && tab[1][1])
			ft_dollar(tab[1]);
		else if (tab[1][0] == '~' && !tab[1][1])
		{
			change_dir(home, 0);
			return ;
		}
		else if (tab[2] == NULL)
		{
			change_dir(tab[1], 0);
			return ;
		}
	}
	many_arguments(tab);
}