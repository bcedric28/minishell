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
**Fichier	create_g_env
*/

void	create_genv(char **env, t_elem *envir);
int		len_env(char **envt);
char	**split_and_delete(t_elem *envir);
char	*ft_search_env(char *path, t_elem *envir);
char	*only_path(int pos, t_elem *envir);

/*
**Fichier env
*/

void	env_bultin(char *env, t_elem *envir);
void	print_env(t_elem *envir);

/*
**Fichier error
*/

void	ft_error(char *excve, int i);

/*
**Fichier dollar
*/

int		ft_dollar_first(char *dollar, t_elem *envir);
void	ft_dollar(char **dollar, t_elem *envir, char *home);
void	ft_dollar_complement(char **tab_dollar, char **dollar, t_elem *envir);

/*
**Fichier vag
*/

int		ft_vag_first(char *vag, t_elem *envir);
void	cd_vag(char **tab, char *home, t_elem *envir);


/*
**Fichier utils
*/

void	return_and_free(char ***tab);
int		is_point(char *excve);
void	ft_access(char *path);

/*
**Fichier unsetenv
*/

void	unsetenv_builtin(char *unsetenv, t_elem *envir);
void	delete_env(int pos, t_elem *envir);

/*
**Fichier track
*/

int		track_path(char **path, char **excve, t_elem *envir);
int		track_without_path(char **excve, t_elem *envir);

/*
**Fichier setenv.c
*/

void	setenv_builtin(char *setenv, t_elem *envir);
void	on_setenv(char **tab, t_elem *envir);
void	add_env(char **tab, t_elem *envir);
void	ft_tabdel(char ***tab);

/*
**Fichier parse_inputs
*/

void	wait_input(t_elem *envir);
void	parse_commands(char *commands, t_elem *envir, char **command);
void	parse_commands_built(char *excve, t_elem *envir, char **commands);

/*
**Fichier minishell
*/

void	display_name(void);
void	exit_shell(t_elem *envir, char **commands);

/*
**Fichier execute
*/

void	main_commands(char *excve, t_elem *envir);
int		execute_commands(char *execute, char **execute_path, t_elem *envir);

/*
**Fichier echo
*/

void	echo_builtin(char *echo, t_elem *envir);
int		condition_loop(int pos, int i, char **tab_echo, t_elem *envir);
void	find_env_echo(char *env, t_elem *envir);
void	find_env_suit(char **copy, char *env, t_elem *envir);

/*
**Fichier display_echo
*/

void	display_echo(char **tab_echo, int i, int n, t_elem *envir);
void	display_echo_env(int i, t_elem *envir);
void	display_echo_vag(char *vag, t_elem *envir);

/*
**Fichier change_dir
*/

void	change_dir(char *path, int arguments, t_elem *envir);
void	print_path(t_elem *envir);

/*
**Fichier cd
*/

void	cd_builtin(char *cd, t_elem *envir);
void	cd_towards(char *home, char **tab, t_elem *envir);
void	only_cd(char *home, t_elem *envir, char **tab);
void	cd_go_back(char **tab, t_elem *envir, char *home);
void	many_arguments(char **tab, char *home);
#endif