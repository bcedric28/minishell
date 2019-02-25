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

void	delete_env(int pos)
{
	int i;
	int k;
	char **copy;

	copy = (char**)malloc(sizeof(char*) * (len_env(g_env)) + 1);
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
	g_env = copy;
}

char	**split_and_delete()
{
	char **copy;
	int i;
	int j;

	i = 0;
	copy = (char**)malloc(sizeof(char*) * (len_env(g_env)) + 1);
	while(g_env[i])
	{
		j = 0;
		while(g_env[i][j])
		{
			if (g_env[i][j + 1] == '=')
			{
				copy[i] = ft_strsub(g_env[i], 0, j + 1);
				break ;
			}
			j++;
		}
		i++;
	}
	return(copy);

}

void		unsetenv_builtin(char *unsetenv)
{
	char **tab;
	int i;
	int j;
	char **copy;

	i = 0;
	copy = split_and_delete();
	tab = ft_strsplit_space(unsetenv);
	if(tab[1] == NULL)
	{
		ft_putendl("NO argument");
		return ;
	}
	if (tab[2] != NULL)
	{
		ft_putendl("TO few arguments");
		return ;
	}
	while(copy[i])
	{
		j = 0;
		if (ft_strequ(copy[i], tab[1]))
		{
			delete_env(i);
			return ;
		}
		i++;
	}
	ft_putendl("NO find the env");
	return ;

}

void	print_env(char *env)
{
	char **tab;
	int i;

	tab = ft_strsplit_space(env);
	if(tab[1] != NULL)
	{
		ft_error(tab[1], 1);
		return ;
	}
	else
	{
		i = 0;
		while(g_env[i])
		{
			ft_putendl(g_env[i]);
			i++;
		}
	}

}
