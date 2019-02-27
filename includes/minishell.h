/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcedric <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 00:12:55 by bcedric           #+#    #+#             */
/*   Updated: 2019/02/21 00:12:56 by bcedric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	MINISHELL_H
# define MINISHELL_H

# include "../Libft/includes/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>

typedef struct	s_elem
{
	char		**envi;
}				t_elem;

/*
**Fichier minishell.h
*/
int	execute_commands(char *execute, char **execute_path, t_elem *envir);
void		display_name(void);
void		exit_shell(t_elem *envir, char **commands);
void	ft_tabdel(char ***tab);

/*
**Fichier parse_inputs.c
*/
int	track_path(char **path, char **excve, t_elem *envir);
void	main_commands(char *excve, t_elem *envir);
void 	parse_commands_built(char *excve, t_elem *envir, char **commands);
void parse_commands(char *commands, t_elem *envir, char **command);
void	wait_input(t_elem *envir);

/*
**Fichier create_g_env.c
*/
int			len_env(char **env);
void		create_genv(char **env, t_elem *envir);

/*
**Fichier env.c
*/
void	print_env(t_elem *envir);
void	unsetenv_builtin(char *unsetenv, t_elem *envir);
char	**split_and_delete(t_elem *envir);
void	delete_env(int pos, t_elem *envir);


void	echo_builtin(char *echo, t_elem *envir);
void	ft_error(char *excve, int i);
void 	setenv_builtin(char *setenv, t_elem *envir);
void env_bultin(char *env, t_elem *envir);
void	cd_builtin(char *cd, t_elem *envir);
char	*ft_search_env(char *path, t_elem *envir);

#endif