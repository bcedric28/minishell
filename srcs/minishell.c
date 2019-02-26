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

/*
**LEAK OK
*/

void		exit_shell(t_elem *envir)
{
	ft_2dtabdel((void**)envir->envi);
	exit(0);
}


void		display_name(void)
{
	int		len;
	char	*cwd;
	char	buff[PATH_MAX + 1];

	cwd = NULL;
	cwd = getcwd(buff, PATH_MAX + 1);
	len = ft_strlen(cwd);
	while (len > 0 && cwd[len - 1] != '/')
		--len;
	ft_putstr("\033[92m");
	ft_putstr(cwd + len);
	ft_putstr("-> \033[0m");
}

int	execute_commands(char *execute, char **execute_path, t_elem *envir)
{
	pid_t	pid;
	struct stat file;

	pid = fork();
	lstat(execute, &file);
	if ((S_ISREG(file.st_mode)) && !(file.st_mode & S_IXUSR))
	{
		ft_putstr("minishell: permission denied: ");
		ft_putendl(execute);
		kill(pid, SIGINT);
		return (1);
	}
	if (pid == 0)
		execve(execute, execute_path, envir->envi);
	else if (pid < 0)
		return (-1);
	wait(&pid);
	return(1);
}

int			main(int argc, char **argv, char **env)
{
	t_elem envir;

	envir.envi = NULL;
	argc = 1;
	argv = NULL;
	create_genv(env, &envir);
	while(1)
	{
		display_name();
		wait_input(&envir);
	}
	return (0);
}
