/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 19:13:02 by apanikov          #+#    #+#             */
/*   Updated: 2023/07/15 17:45:22 by vtavitia         ###   ########.fr       */
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

typedef enum s_token_type	t_token_type;
typedef struct s_token		t_token;

typedef struct s_mhstuct
{
	char			*input;
	t_token			*token;
	char			**env_copy;
}				t_mhstruct;

#endif