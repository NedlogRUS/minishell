/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar_utils3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:46:26 by vtavitia          #+#    #+#             */
/*   Updated: 2023/07/24 15:01:00 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vtavitia.h"

int	inject_pid(int	*k, int size, t_token **new_t, t_mhstruct **mh)
{
	int	i;

	i = 0;
	while (*k <= size && ft_itoa((*mh)->mh_pid)[i])
	{	
		(*new_t)->data[*k] = ft_itoa((*mh)->mh_pid)[i];
		(*k)++;
		i++;
	}
	return (i);
}

int	inject_exit_msg(int	*k, int size, t_token **new_t, t_mhstruct **mh)
{
	int	i;

	i = 0;
	while (*k <= size && ft_itoa((*mh)->er_num)[i])
	{	
		(*new_t)->data[*k] = ft_itoa((*mh)->er_num)[i];
		i++;
		(*k)++;
	}
	return (i);
}

static void	get_size_helper(t_env *env_lst, int *i)
{
	while (env_lst->data[*i])
		(*i)++;
}

int	get_size(char *term, t_env *env_lst, t_env **env_term, t_mhstruct *mh)
{
	int	i;
	int	found;

	i = 0;
	found = 0;
	if ((!ft_strcmp("$", term)))
		return (ft_strlen(ft_itoa(mh->mh_pid)));
	else if ((!ft_strcmp("?", term)))
		return (ft_strlen(ft_itoa(mh->er_num)));
	while (env_lst->next)
	{
		if (!ft_strcmp(env_lst->name, term))
		{
			*env_term = env_lst;
			found = 1;
			while (env_lst->data[i])
				i++;
		}
		env_lst = env_lst->next;
	}
	if (ft_strcmp(env_lst->name, term) && !found)
		get_size_helper(env_lst, &i);
	return (i);
}

void	finalise_newterm(t_token *new_t, t_token **curr, t_mhstruct *mh, int k)
{
	new_t->data[k] = '\0';
	new_t->next = (*curr)->next;
	if ((mh)->token == *curr)
			(mh)->token = new_t;
	*curr = new_t;
}
