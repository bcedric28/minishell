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

#include	"minishell.h"

char		**g_env = 0;

void		exit_shell(void)
{
	write(1, "\n", 1);
	exit(0);
}


void		display_name(void)
{
	int		len;
	char	*cwd;
	char	buff[PATH_MAX + 1];

	cwd = getcwd(buff, PATH_MAX + 1);
	len = ft_strlen(cwd);
	while (len > 0 && cwd[len - 1] != '/')
		--len;
	ft_putstr("\033[92m");
	ft_putstr(cwd + len);
	ft_putstr("-> \033[0m");
}

int	execute_commands(char *execute, char **execute_path)
{
	pid_t	pid;

	pid = fork();
	if(pid == 0)
		execve(execute, execute_path, g_env);
	else if (pid < 0)
		return (-1);
	wait(&pid);
	return(1);
}


int	excute_built_setenv(char *echo)
{

	return(0);
}

int	excute_built_exit(char *echo)
{
	return(0);
}

/*int	excute_built_cd(char *cd)
{
	cd_builtin(cd);
	return(0);
}
*/

int			main(int argc, char **argv, char **env)
{
	argc = 1;
	argv = NULL;
	create_g_env(env);
	while(1)
	{
		display_name();
		wait_input();
	}
	return (0);
}
