/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 22:12:24 by vtavitia          #+#    #+#             */
/*   Updated: 2023/08/26 17:01:54 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vtavitia.h"

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

void	close_upto_i(int pipes[1000][2], int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		close(pipes[j][1]);
		close(pipes[j][0]);
		j++;
	}
}
