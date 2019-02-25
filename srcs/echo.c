/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcedric <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 06:57:21 by bcedric           #+#    #+#             */
/*   Updated: 2019/02/25 06:57:22 by bcedric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

void	display_echo_env(int i)
{
	int j;

	j = 0;
	while(g_env[i][j])
	{
		if (g_env[i][j - 1] == '=')
			break ;
		j++;
	}
	ft_putstr(&g_env[i][j]);
}

void	find_env_echo(char *env)
{
	char **copy;
	int i;
	int j;
	char *new_env;

	new_env = ft_strnew(ft_strlen(env));
	i = 0;
	j = 0;
	while(env[i])
	{
		if (env[i] == '"' || env[i] == '$')
			i++;
		else
		{
			new_env[j] = env[i];
			i++;
			j++;
		}
	}
	copy = split_and_delete();
	i = 0;
	while(copy[i])
	{
		if (ft_strequ(copy[i], new_env))
		{
			display_echo_env(i);
			return ;
		}
		i++;
	}
}

void	display_echo(char **tab_echo, int n)
{
	int i;
	int pos;

	i = n;
	while(tab_echo[i])
	{
		pos = 0;
		while(tab_echo[i][pos])
		{
			if (tab_echo[i][pos] == '"')
				pos++;
			if (tab_echo[i][pos] == '$')
			{
				find_env_echo(tab_echo[i]);
				break ;
			}
			else
			{
				ft_putchar(tab_echo[i][pos]);
				pos++;
			}
		}
		ft_putchar(' ');
		i++;
	}
	ft_putchar('\n');
}

void	echo_builtin(char *echo)
{
	int i;
	char *new_echo;
	char **tab_echo;

	i = -1;
	while(echo[++i])
		if (ft_isspace(echo[i]) == 1)
			break ;
	new_echo = ft_strsub(echo, i, ft_strlen(echo));
	tab_echo = ft_strsplit_space(new_echo);
	i = 0;
	if (!tab_echo[i])
	{
		ft_putendl("");
		return ;
	}
	if (ft_strcmp(tab_echo[i], "-n") == 0)
		i++;
	display_echo(tab_echo, i);
}

