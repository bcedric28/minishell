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

void 	display_echo_vag(char *vag)
{
	char	*home;

	home = ft_search_env("HOME");
	if (home == NULL)
	{
		ft_putstr("HOME is not set");
		return ;
	}
	if (!vag[1])
		ft_putstr(home);
	else if (vag[1] == '/')
	{
		vag = ft_strjoin(home, &vag[1]);
		ft_putstr(vag);
		free(vag);
	}
	else
		ft_putstr("minishell: not enough directory stack entries");
	free(home);
	return ;
}

void	find_env_suit(char **copy, char *env)
{
	int i;

	i = -1;
	while(copy[++i])
	{
		if (ft_strequ(copy[i], env))
		{
			display_echo_env(i);
			break ;
		}
	}
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
	find_env_suit(copy, new_env);
	free(new_env);
	ft_2dtabdel((void **)copy);
}

int		condition_loop(int pos, int i, char **tab_echo)
{
	if (tab_echo[i][pos] == '~'
			&& ((ft_isspace(tab_echo[i][pos]) == 1) || pos == 0))
	{
		display_echo_vag(tab_echo[i]);
		return (1);
	}
	if (tab_echo[i][pos] == '"' || tab_echo[i][pos] == '\'')
		return (0);
	if (tab_echo[i][pos] == '$' && tab_echo[i][pos - 1] != '\'')
	{
		find_env_echo(&tab_echo[i][pos]);
		return (1);
	}
	else
	{
		ft_putchar(tab_echo[i][pos]);
		return (0);
	}
	return (0);
}

void	display_echo(char **tab_echo, int i, int n)
{
	int pos;
	int condition;

	if (n == 1)
		i++;
	while(tab_echo[++i])
	{
		pos = 0;
		while(tab_echo[i][pos])
		{
			condition = condition_loop(pos, i , tab_echo);
			if (condition == 1)
				break ;
			else
				pos++;
		}
		ft_putchar(' ');
	}
	if (n == 0)
		ft_putchar('\n');
}

void	echo_builtin(char *echo)
{
	int i;
	int n;
	char *new_echo;
	char **tab_echo;

	i = -1;
	n = 0;
	while(echo[++i])
		if (ft_isspace(echo[i]) == 1)
			break ;
	new_echo = ft_strsub(echo, i, ft_strlen(echo));
	tab_echo = ft_strsplit_space(new_echo);
	i = 0;
	if (!tab_echo[0])
	{
		ft_putendl("");
		free(new_echo);
		ft_2dtabdel((void **)tab_echo);
		return ;
	}
	if (ft_strcmp(tab_echo[i], "-n") == 0)
		n = 1;
	display_echo(tab_echo, (i - 1), n);
	free(new_echo);
	ft_2dtabdel((void **)tab_echo);
}