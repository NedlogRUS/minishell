/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 19:13:02 by apanikov          #+#    #+#             */
/*   Updated: 2023/08/29 19:24:48 by vtavitia         ###   ########.fr       */
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
# include <sys/stat.h>

typedef enum s_token_type	t_token_type;
typedef struct s_token		t_token;

typedef struct s_mhstuct
{
	t_token			*token;
	char			*input;
	int				mh_pid;
	int				er_num;
	char			**emsg;
	int				in;
	int				screen;
	int				dolmark;
	int				t_size;
	int				th_i;
	struct s_env	*env;
	struct s_utils	*utils;
}				t_mhstruct;

typedef struct s_env {
	char			*name;
	char			*data;
	struct s_env	*next;
}	t_env;

typedef struct s_utils {
	char			*line;
	char			*name;
	char			*data;
	char			*tmp;
}	t_utils;

#endif