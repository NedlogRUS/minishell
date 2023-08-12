/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar_utils5.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 15:51:16 by vtavitia          #+#    #+#             */
/*   Updated: 2023/08/12 17:30:44 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vtavitia.h"

void	inject_term(char *search, t_token **curr, t_mhstruct *mh)
{
	t_env	*env_term;

	env_term = NULL;
	if (is_there_dollar((*curr)->data))
		term_helper(search, mh, curr, env_term);
}

void	shift_i(t_token **current, int *i)
{
	if ((*current)->data[*i] == '$' && (*current)->data[*i + 1] == '\0')
	{
		(*i)++;
		return ;
	}
	else if ((*current)->data[*i] == '$' && (*current)->data[*i + 1] == ' ')
		(*i)++;
	while ((*current)->data[*i] != '$' && (*current)->data[*i])
	{
		(*i)++;
		if ((*current)->data[*i] == '$' && (*current)->data[*i + 1] == '\0')
			(*i)++;
		else if ((*current)->data[*i] == '$' && (*current)->data[*i + 1] == ' ')
			(*i)++;
	}
	(*i)++;
}
