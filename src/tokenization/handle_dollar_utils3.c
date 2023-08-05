/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar_utils3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:46:26 by vtavitia          #+#    #+#             */
/*   Updated: 2023/08/05 19:11:46 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vtavitia.h"

int	inject_pid(int	*k, int size, t_token **new_t, t_mhstruct **mh)
{
	int	i;
	char	*pid_char = ft_itoa((*mh)->mh_pid);

	i = 0;
	while (*k <= size && pid_char[i])
	{	
		(*new_t)->data[*k] = pid_char[i];
		(*k)++;
		i++;
	}
	free(pid_char);
	return (i);
}

int	inject_exit_msg(int	*k, int size, t_token **new_t, t_mhstruct **mh)
{
	int	i;
	char	*err_num_char;
	
	err_num_char = ft_itoa((*mh)->er_num);
	i = 0;
	while (*k <= size && err_num_char[i])
	{	
		(*new_t)->data[*k] = err_num_char[i];
		i++;
		(*k)++;
	}
	free(err_num_char);
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
	char *charpid = ft_itoa(mh->mh_pid);
	char	*charerrnum = ft_itoa(mh->er_num);
	if ((!ft_strcmp("$", term)))
	{
		found = ft_strlen(charpid);
		free(charpid);
		free(charerrnum);
		return (found);
	}
	else if ((!ft_strcmp("?", term)))
	{
		found = ft_strlen(charerrnum);
		free(charpid);
		free(charerrnum);
		return (found);
	}
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
	free(charpid);
		free(charerrnum);
	return (i);
}

void	finalise_newterm(t_token *new_t, t_token **curr, t_mhstruct *mh, int k)
{
	new_t->data[k] = '\0';
	new_t->next = (*curr)->next;
	if ((mh)->token == *curr)
	{
			(mh)->token = new_t;
		// free((*curr)->data);
		// free((*curr));
	}
	// *curr = new_t;
	// printf("now curr da/ta is >%s<\n", (*curr)->data);

		(*curr)->data = (new_t->data);
		(*curr)->next = new_t->next;
	
		
}
