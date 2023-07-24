/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <apanikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 19:13:02 by apanikov          #+#    #+#             */
/*   Updated: 2023/07/21 16:41:05 by apanikov         ###   ########.fr       */
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

typedef enum s_token_type	t_token_type;
typedef struct s_token		t_token;

typedef struct s_mhstuct
{
	t_token			*token;
	char			*input;
	int				mh_pid; //pid of miniHell
	int 			er_num; // number of error when comand done
	struct s_env	*env;
	char			*mh_pid;
}				t_mhstruct;

typedef struct s_env {
    char			*name;
    char			*data;
    struct s_env	*next;
} t_env;

#endif