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

typedef struct	s_el
{
	char	**envi;
}				t_elem;

/*
**Fichier minishell.h
*/
int	execute_commands(char *execute, char **execute_path);
void		display_name(void);
void		exit_shell(void);

/*
**Fichier parse_inputs.c
*/
int	track_path(char **path, char **excve);
void	main_commands(char *excve);
void 	parse_commands_built(char *excve);
void parse_commands(char *commands);
void	wait_input();

/*
**Fichier create_g_env.c
*/
int			len_env(char **env);
void		create_g_env(char **env);

/*
**Fichier env.c
*/
void	print_env();
void	unsetenv_builtin(char *unsetenv);
char	**split_and_delete();
void	delete_env(int pos);


void	echo_builtin(char *echo);
void	ft_error(char *excve, int i);
void 	setenv_builtin(char *setenv);
void env_bultin(char *env);
void	cd_builtin(char *cd);
char	*ft_search_env(char *path);

#endif