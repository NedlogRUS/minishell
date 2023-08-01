/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <apanikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 19:13:02 by apanikov          #+#    #+#             */
/*   Updated: 2023/07/29 16:07:10 by apanikov         ###   ########.fr       */
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

typedef enum s_token_type	t_token_type;
typedef struct s_token		t_token;

typedef struct s_mhstuct
{
	t_token			*token;
	char			*input;
	int				mh_pid; //pid of miniHell
	// char			*mh_pid;
	int 			er_num; // number of error when comand done
	struct s_env	*env;
}				t_mhstruct;

typedef struct s_env {
    char			*name;
    char			*data;
    struct s_env	*next;
} t_env;

#endif