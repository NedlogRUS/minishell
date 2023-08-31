/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_temp_mh.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 13:44:34 by vtavitia          #+#    #+#             */
/*   Updated: 2023/08/31 13:45:19 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vtavitia.h"

void	cr_temp_mh(t_mhstruct **tmp, t_mhstruct **mh, t_token **curr, int *i)
{
	*tmp = malloc(sizeof(t_mhstruct));
	initializer_temp_mh(*tmp, *mh);
	*curr = (*mh)->token;
	while ((*curr)->pi != *i)
		*curr = (*curr)->next;
	copy_to_tmp(tmp, curr);
}

void	initializer_temp_mh( t_mhstruct *tmp, t_mhstruct *mh)
{
	tmp->token = NULL;
	tmp->env = mh->env;
	tmp->er_num = 0;
	tmp->mh_pid = mh->mh_pid;
	tmp->emsg = mh->emsg;
	tmp->in = dup(STDIN_FILENO);
	tmp->screen = dup(STDOUT_FILENO);
	tmp->dolmark = 0;
	tmp->t_size = 0;
	tmp->th_i = 0;
}

static void	copy_to_tmp_helper(t_mhstruct **tmp, t_token **new)
{
	(*tmp)->token->next = *new;
	(*tmp)->token = (*tmp)->token->next;
}

void	copy_to_tmp(t_mhstruct **tmp, t_token **curr)
{
	t_token	*start;
	t_token	*new;

	new = NULL;
	(*tmp)->token = NULL;
	while (*curr && (*curr)->type != PIPELINE)
	{
		new = init_token("", NULL_VAL);
		new->data = ft_strdup((*curr)->data);
		new->pi = (*curr)->pi;
		new->type = (*curr)->type;
		if ((*curr)->next == NULL || (*curr)->next->type == PIPELINE)
			new->next = NULL;
		if ((*tmp)->token == NULL)
		{
			(*tmp)->token = new;
			start = (*tmp)->token;
		}
		else
			copy_to_tmp_helper(tmp, &new);
		(*curr) = (*curr)->next;
	}
	(*tmp)->token = start;
}
