/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar_utils3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:46:26 by vtavitia          #+#    #+#             */
/*   Updated: 2023/08/25 22:13:51 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vtavitia.h"

int	inject_pid(int	*k, int size, t_token **new_t, t_mhstruct **mh)
{
	int		i;
	char	*pid_char;

	pid_char = ft_itoa((*mh)->mh_pid);
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
	int		i;
	char	*err_num_char;

	(void)mh;
	err_num_char = ft_itoa(g_error);
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
	if ((!ft_strcmp("$", term)))
		return (found_dollar(mh));
	else if ((!ft_strcmp("?", term)))
		return (found_err_num(mh));
	while (env_lst != NULL)
	{
		if (!ft_strcmp(env_lst->name, term))
		{
			*env_term = env_lst;
			found = 1;
			while (env_lst->data[i])
				i++;
		}
		if (found)
			break ;
		env_lst = env_lst->next;
	}
	if (ft_strcmp(env_lst->name, term) && !found)
		get_size_helper(env_lst, &i);
	return (i);
}
