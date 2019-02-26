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

	i = -1;
	home = ft_search_env("HOME");
	oldpath = ft_search_env("OLDPWD");
	if (ft_strcmp(home, oldpath) == 0)
		str = ft_strdup("~");
	else
	{
		while(home[++i])
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
		if(j != 0 && g_env[pos][j - 1] == '=')
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

void	many_arguments(char **tab, char *home)
{
	ft_putendl("cd: too many arguments");
	if (home)
		free(home);
	ft_2dtabdel((void **)tab);
	return ;
	
}

void		ft_dollar_complement(char **tab_dollar, char *dollar)
{
	char *home;

	home = ft_search_env("HOME");
	if (home == NULL)
	{
		ft_putendl("HOME is not set");
		ft_2dtabdel((void**)tab_dollar);
		free(dollar);
		return ;
	}
	change_dir(home, 0);
	ft_2dtabdel((void**)tab_dollar);
	free(dollar);
	free(home);
	return ;
}

void		ft_dollar(char *dollar)
{
	char **tab_dollar;
	char *path;

	path = NULL;
	tab_dollar = ft_strsplit(dollar, '$');
	if (ft_strcmp(tab_dollar[0], "~") == 0)
		return(ft_dollar_complement(tab_dollar, dollar));
	path = ft_search_env(tab_dollar[0]);
	if (path == NULL)
		return ;
	else
	{
		change_dir(path, 0);
		ft_2dtabdel((void**)tab_dollar);
		free(dollar);
		free(path);
	}
	return ;
}

void	cd_vag(char **tab, char *home)
{
	if (!tab[1][1])
	{
		if (home == NULL)
			ft_putendl("HOME is not set");
		else
			change_dir(home, 0);
	}
	if (tab[1][1] == '/')
	{
		if (home == NULL)
		{
			ft_putendl("HOME is not set");
			free(home);
			ft_2dtabdel((void**)tab);
			return ;
		}
		else
			tab[1] = ft_strjoin(home, &tab[1][1]);
		change_dir(tab[1], 0);
	}
	free(home);
	ft_2dtabdel((void**)tab);
	return ;
}

void	cd_go_back(char **tab)
{
	char *old;

	old = NULL;
	if (ft_strcmp(tab[1], "-") == 0)
	{
		old = ft_search_env("OLDPWD");
		if (old != NULL)
		{
			change_dir(old, 1);
			free(old);
		}
		else
			ft_putendl("OLDPWD is not set");
	}
	else
	{
		ft_putstr("cd : no such file or directory: ");
		ft_putendl(tab[1]);
	}
	ft_2dtabdel((void **)tab);
	return ;
}

void	only_cd(char *home)
{
	if (home == NULL)
		ft_putendl("HOME is not set");
	else
		change_dir(home, 0);
	free(home);
	return ;
}

void	cd_towards(char *home, char **tab)
{
	change_dir(tab[1], 0);
	if (home)
		free(home);
	ft_2dtabdel((void**)tab);
	return ;
}

void	cd_builtin(char *cd)
{
	char **tab;
	char *home;

	tab = ft_strsplit_space(cd);
	home = ft_search_env("HOME");
	if (tab[1] == NULL)
		return (only_cd(home));
	else
	{
		if (ft_strequ(tab[1], "--"))
			return (only_cd(home));
		else if (tab[1][0] == '-')
			return(cd_go_back(tab));
		else if (tab[1][0] == '$' && tab[1][1])
			return(ft_dollar(tab[1]));
		else if (tab[1][0] == '~')
			return(cd_vag(tab, home));
		else if (tab[2] == NULL)
			return(cd_towards(home, tab));
	}
	return(many_arguments(tab, home));
}