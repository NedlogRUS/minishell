/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 19:54:52 by vtavitia          #+#    #+#             */
/*   Updated: 2023/08/25 22:57:47 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vtavitia.h"

static void	term_helper3(t_token **tmp, t_token **new_term)
{
	free((*tmp)->data);
	free(*tmp);
	free(*new_term);
}

static void	term_helper2(t_token **tmp, t_token **new_term, t_token **curr)
{
	*tmp = init_token("", NULL_VAL);
	*new_term = init_token(NULL, NULL_VAL);
	(*tmp)->data = ft_strdup((*curr)->data);
	(*tmp)->s_quote = (*curr)->s_quote;
	(*tmp)->d_quote = (*curr)->d_quote;
	free((*curr)->data);
	(*curr)->data = (*tmp)->data;
}

void	term_helper(char *search, t_mhstruct *mh, t_token **curr, t_env *env_t)
{
	t_token	*new_term;
	t_token	*tmp;
	int		location;
	int		k;

	k = 0;
	term_helper2(&tmp, &new_term, curr);
	location = get_location(search, curr);
	if (!ft_strcmp(search, "$"))
		location--;
	mh->t_size = get_size(search, mh->env, &env_t, mh)
		- ft_strlen(search) - 1 + ft_strlen((*curr)->data);
	new_term->data = (char *)malloc(sizeof(char) * mh->t_size + 1);
	mh->th_i = inject_helper(&k, location, curr, &new_term);
	if (ft_strcmp(search, "$") && ft_strcmp(search, "?"))
		inject_wo_dollar(&k, mh->t_size, &env_t, &new_term);
	else if (!ft_strcmp(search, "?"))
		mh->th_i = inject_exit_msg(&k, mh->t_size, &new_term, &mh);
	else if (!ft_strcmp(search, "$"))
		mh->th_i = inject_pid(&k, mh->t_size, &new_term, &mh);
	mh->th_i = location + ft_strlen(search) + 1;
	if ((*curr)->data[mh->th_i] != '\0')
		copy_remaining(&mh->th_i, &k, curr, &new_term);
	finalise_newterm(new_term, curr, mh, k);
	term_helper3(&tmp, &new_term);
}
