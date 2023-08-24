/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 19:13:02 by apanikov          #+#    #+#             */
/*   Updated: 2023/08/24 16:37:09 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "apanikov.h"
# include "vtavitia.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <dirent.h>
# include <errno.h>
# include <signal.h>

typedef enum s_token_type	t_token_type;
typedef struct s_token		t_token;

typedef struct s_mhstuct
{
	t_token			*token;
	char			*input;
	int				mh_pid; //pid of miniHell
	// char			*mh_pid;
	int 			er_num; // number of error when comand done
	char			**emsg; // error message and command name for print
	int				in;		//fd for stdin
	int				screen; //fd for stdout
	struct s_env	*env;
	struct s_utils	*utils;
}				t_mhstruct;

typedef struct s_env {
    char			*name;
    char			*data;
    struct s_env	*next;
} t_env;

typedef struct s_utils {
	char			*line;
    char			*name;
    char			*data;
	char			*tmp;
} t_utils;

#endif