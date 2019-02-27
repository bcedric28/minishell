/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcedric <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 08:47:42 by bcedric           #+#    #+#             */
/*   Updated: 2019/02/25 08:47:43 by bcedric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

/*
**PROBLEME DE LEAK
*/

void	delete_env(int pos, t_elem *envir)
{
	int i;
	int k;
	char **copy;

	if (!(copy = (char**)ft_memalloc(sizeof(char*) * (len_env(envir->envi)))))
		return ;
	i = 0;
	k = 0;
	while(envir->envi[i])
	{
		if (i == pos)
			i++;
		else
		{
			copy[k] = ft_strdup(envir->envi[i]);
			k++;
			i++;
		}
	}
	copy[k] = 0;
	ft_tabdel(&(envir->envi));
	envir->envi = copy;
}

char	**split_and_delete(t_elem *envir)
{
	char **copy;
	int i;
	int j;
	int k;

	i = -1;
	k = 0;
	if (!(copy = (char**)malloc(sizeof(char*) * (len_env(envir->envi)) + 1)))
		return (NULL);
	while(envir->envi[++i])
	{
		j = -1;
		while(envir->envi[i][++j])
		{
			if (envir->envi[i][j + 1] != '\0' && envir->envi[i][j + 1] == '=')
			{
				copy[k] = ft_strsub(envir->envi[i], 0, j + 1);
				k++;
				break ;
			}
		}
	}
	copy[k] = 0;
	return(copy);
}

void		unsetenv_builtin(char *unsetenv, t_elem *envir)
{
	char **tab;
	int i;
	int j;
	char **copy;

	copy = NULL;
	tab = ft_strsplit_space(unsetenv);
	if(tab[1] == NULL)
		ft_putendl("unsetenv: Too few arguments.");
	else
	{
		j = 0;
		copy = split_and_delete(envir);
		while(tab[++j])
		{
			i = -1;
			while(copy[++i])
				if (ft_strequ(copy[i], tab[j]))
					delete_env(i, envir);
		}
	}
	ft_2dtabdel((void **)copy);
	ft_2dtabdel((void **)tab);
	return ;
}

void	print_env(t_elem *envir)
{
	int i;

	i = 0;
	while(envir->envi[i])
	{
		ft_putendl(envir->envi[i]);
		i++;
	}
}

void env_bultin(char *env, t_elem *envir)
{
	char **tab;

	tab = ft_strsplit_space(env);
	if (tab[1] == NULL)
		print_env(envir);
	else
	{
		ft_putstr("env: ");
		ft_putstr(env);
		ft_putendl(": No such file or directory");
	}
	ft_2dtabdel((void **)tab);
}
