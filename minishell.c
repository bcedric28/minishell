/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcedric <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 21:51:10 by bcedric           #+#    #+#             */
/*   Updated: 2019/02/20 21:51:14 by bcedric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft/includes/libft.h"
char					**g_env;

void	exit_shell(void)
{
	write(1, "\n", 1);
	exit(0);
}

static int		len_env(char **env)
{
	int		i;
	int		len;

	i = -1;
	len = 0;
	while (env[++i])
		len++;
	return (len);
}

void			create_g_env(int argc, char **argv, char **env)
{
	int		i;

	g_env = (char **)malloc(sizeof(char *) * (len_env(env) + 1));
	i = -1;
	while (env[++i])
	{
		if (!(g_env[i] = ft_strdup(env[i])))
			exit_shell();
	}
}

void	display_name(void)
{
	int		len;
	char	*cwd;
	char	buff[PATH_MAX + 1];

	cwd = getcwd(buff, PATH_MAX + 1);
	len = ft_strlen(cwd);
	while (len > 0 && cwd[len - 1] != '/')
		--len;
	ft_putstr("\033[92m->");
	ft_putstr(cwd + len);
}

int main(int argc, char **argv, char **env)
{
	int i = 0;
	create_g_env(argc, argv, env);
	while(1)
	{
		display_name();
		sleep(5);		
	}
	return (0);
}
