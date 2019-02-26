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

void	delete_env(int pos)
{
	int i;
	int k;
	char **copy;

	if (!(copy = (char**)ft_memalloc(sizeof(char*) * (len_env(g_env)))))
		return ;
	i = 0;
	k = 0;
	while(g_env[i])
	{
		if (i == pos)
			i++;
		else
		{
			copy[k] = ft_strdup(g_env[i]);
			k++;
			i++;
		}
	}
	copy[k] = 0;
	g_env = copy;
}

char	**split_and_delete()
{
	char **copy;
	int i;
	int j;
	int k;

	i = -1;
	k = 0;
	if (!(copy = (char**)malloc(sizeof(char*) * (len_env(g_env)) + 1)))
		return (NULL);
	while(g_env[++i])
	{
		j = -1;
		while(g_env[i][++j])
		{
			if (g_env[i][j + 1] != '\0' && g_env[i][j + 1] == '=')
			{
				copy[k] = ft_strsub(g_env[i], 0, j + 1);
				k++;
				break ;
			}
		}
	}
	copy[k] = 0;
	return(copy);
}

void		unsetenv_builtin(char *unsetenv)
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
		while(tab[++j])
		{
			copy = split_and_delete();
			i = -1;
			while(copy[++i])
				if (ft_strequ(copy[i], tab[j]))
					delete_env(i);
		}
	}
	ft_2dtabdel((void **)tab);
	if (copy)
		ft_2dtabdel((void **)copy);
	return ;
}

void	print_env()
{
	int i;

	i = 0;
	while(g_env[i])
	{
		ft_putendl(g_env[i]);
		i++;
	}
}

void env_bultin(char *env)
{
	char **tab;

	tab = ft_strsplit_space(env);
	if (tab[1] == NULL)
		print_env();
	else
	{
		ft_putstr("env: ");
		ft_putstr(env);
		ft_putendl(": No such file or directory");
	}
	ft_2dtabdel((void **)tab);
}
