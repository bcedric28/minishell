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
#include 	<unistd.h>
#include <stdio.h>
#include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <dirent.h>

char		**g_env = 0;

void		exit_shell(void)
{
	write(1, "\n", 1);
	exit(0);
}

int			len_env(char **env)
{
	int		i;
	int		len;

	i = -1;
	len = 0;
	while (env[++i])
		len++;
	return (len);
}

void		create_g_env(char **env)
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

int	track_path(char **path, char **excve)
{
	int i;
	struct stat file;

	i = 0;
	while(path[i])
	{
		path[i] = ft_strjoin(path[i], "/");
		path[i] = ft_strjoin(path[i], excve[0]);
		if (lstat(path[i], &file) == 0)
			return(execute_commands(path[i], excve));
		i++;
	}
	return (0);
}

void	ft_error(char *excve)
{
	ft_putstr("\033[92mminishell\033[0m: command not found: ");
	ft_putendl(excve);
}

void	main_commands(char *excve)
{
	int i;
	int j;
	char **path;
	char **execute_path;

	i = 0;
	j = 0;
	execute_path = ft_strsplit_space(excve);
	while(g_env[i])
	{
		j = 0;
		if (ft_strstr(g_env[i], "PATH") != NULL)
		{
			path = ft_strsplit(g_env[i], ':');
			path[0] = ft_strsub(path[0], 5, ft_strlen(path[0]));
			if (track_path(path, execute_path) == 0)
				ft_error(excve);
		}
		i++;
	}

}

int	excute_built_setenv(char *echo)
{
	return(0);
}


int	excute_built_unsetenv(char *echo)
{
	return(0);
}


int	excute_built_env(char *echo)
{
	return(0);
}


int	excute_built_exit(char *echo)
{
	return(0);
}

int	excute_built_cd(char *echo)
{
	return(0);
}

int	excute_built_echo(char *echo)
{
	return(0);
}

void 	parse_commands_built(char *excve)
{
	if (ft_strncmp(excve, "echo", 5) == 0)
		excute_built_echo(excve);
	else if (ft_strncmp(excve, "cd", 3) == 0)
		excute_built_cd(excve);
	else if (ft_strncmp(excve, "exit", 4) == 0)
		excute_built_exit(excve);
	else if (ft_strncmp(excve, "env", 3) == 0)
		excute_built_env(excve);
	else if (ft_strncmp(excve, "unsetenv", 3) == 0)
		excute_built_unsetenv(excve);
	else if (ft_strncmp(excve, "setenv", 6) == 0)
		excute_built_setenv(excve);
	else
		main_commands(excve);
}

void parse_commands(char *commands)
{
	int i;
	char	*excve;

	i = 0;
	while(commands[i] == ' ' || commands[i] == '\t')
		i++;
	if (!commands[i])
		return ;
	excve = ft_strtrim(&commands[i]);
	parse_commands_built(excve);
}

void	wait_input()
{
	char *line;
	char **commands;
	int 	i;

	if (get_next_line(STDIN_FILENO, &line) <= 0)
		return ;
	i = 0;
	if (line)
	{
		commands = ft_strsplit(line, ';');
		while(commands[i])
			parse_commands(commands[i++]);
	}
	free(line);

}

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
