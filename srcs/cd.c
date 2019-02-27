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

void	print_path(t_elem *envir)
{
	char *home;
	char *oldpath;
	char *str;
	int i;

	i = -1;
	home = ft_search_env("HOME", envir);
	oldpath = ft_search_env("OLDPWD", envir);
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

void	change_dir(char *path, int arguments, t_elem *envir)
{
	char buff[PATH_MAX];
	char *cwd;

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

char	*only_path(int pos, t_elem *envir)
{
	char *str;
	int j;

	j = 0;
	while(envir->envi[pos][j])
	{
		if(j != 0 && envir->envi[pos][j - 1] == '=')
			break ;
		j++;
	}
	str = ft_strdup(&envir->envi[pos][j]);
	return (str);
}

char	*ft_search_env(char *path, t_elem *envir)
{
	int i;
	char **copy;

	copy = split_and_delete(envir);
	i = 0;
	while(copy[i])
	{
		if (ft_strequ(copy[i], path))
		{
			ft_2dtabdel((void**)copy);
			return(only_path(i, envir));
		}
		i++;
	}
	ft_2dtabdel((void**)copy);
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

void		ft_dollar_complement(char **tab_dollar, char **dollar, t_elem *envir)
{
	char *home;

	home = ft_search_env("HOME", envir);
	if (home == NULL)
	{
		ft_putendl("HOME is not set");
		ft_2dtabdel((void **)tab_dollar);
		ft_2dtabdel((void **)dollar);
		return ;
	}
	change_dir(home, 0, envir);
	ft_2dtabdel((void **)tab_dollar);
	ft_2dtabdel((void **)dollar);
	free(home);
	return ;
}

void		ft_dollar(char **dollar, t_elem *envir, char *home)
{
	char **tab_dollar;
	char *path;

	path = NULL;
	if (home)
		free(home);
	tab_dollar = ft_strsplit(dollar[1], '$');
	if (ft_strcmp(tab_dollar[0], "~") == 0)
		return(ft_dollar_complement(tab_dollar, dollar, envir));
	path = ft_search_env(tab_dollar[0], envir);
	if (path == NULL)
	{
		ft_2dtabdel((void**)tab_dollar);
		ft_2dtabdel((void **)dollar);
		return ;
	}
	else
	{
		change_dir(path, 0, envir);
		ft_2dtabdel((void**)tab_dollar);
		ft_2dtabdel((void **)dollar);
		free(path);
	}
	return ;
}

void	cd_vag(char **tab, char *home, t_elem *envir)
{
	char *tmp; 

	if (!tab[1][1])
	{
		if (home == NULL)
			ft_putendl("HOME is not set");
		else
			change_dir(home, 0, envir);
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
		{
			tmp = tab[1];
			tab[1] = ft_strjoin(home, &tmp[1]);
			free(tmp);
		}
		change_dir(tab[1], 0, envir);
	}
	free(home);
	ft_2dtabdel((void**)tab);
	return ;
}

void	cd_go_back(char **tab, t_elem *envir, char *home)
{
	char *old;

	old = NULL;
	if (home)
		free(home);
	if (ft_strcmp(tab[1], "-") == 0)
	{
		old = ft_search_env("OLDPWD", envir);
		if (old != NULL)
		{
			change_dir(old, 1, envir);
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

void	only_cd(char *home, t_elem *envir, char **tab)
{
	if (home == NULL)
		ft_putendl("HOME is not set");
	else
		change_dir(home, 0, envir);
	free(home);
	ft_2dtabdel((void**)tab);
	return ;
}

void	cd_towards(char *home, char **tab, t_elem *envir)
{
	change_dir(tab[1], 0, envir);
	if (home)
		free(home);
	ft_2dtabdel((void**)tab);
	return ;
}

void	cd_builtin(char *cd, t_elem *envir)
{
	char **tab;
	char *home;

	tab = ft_strsplit_space(cd);
	home = ft_search_env("HOME", envir);
	if (tab[1] == NULL)
		return (only_cd(home, envir, tab));
	else
	{
		if (ft_strequ(tab[1], "--"))
			return (only_cd(home, envir, tab));
		else if (tab[1][0] == '-')
			return(cd_go_back(tab, envir, home));
		else if (tab[1][0] == '$' && tab[1][1])
			return(ft_dollar(tab, envir, home));
		else if (tab[1][0] == '~')
			return(cd_vag(tab, home, envir));
		else if (tab[2] == NULL)
			return(cd_towards(home, tab, envir));
	}
	return(many_arguments(tab, home));
}