/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <apanikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 18:50:42 by apanikov          #+#    #+#             */
/*   Updated: 2023/08/04 14:52:28 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	unset_2(t_env *curr, char *tdata)
{
	t_env	*tmp;

	tmp = NULL;
	while (curr != NULL)
	{
		if (!ft_strcmp(curr->name, tdata))
		{
			if (curr->next != NULL)
				tmp->next = curr->next;
			else
				tmp->next = NULL;
			free(curr->name);
			if (curr->data != NULL)
				free(curr->data);
			free(curr);
			return ;
		}
		tmp = curr;
		curr = curr->next;
	}
	return ;
}

void	unset(t_mhstruct *mh, char *tdata)
{
	t_env	*curr;

	curr = mh->env;
	if (!ft_strcmp(curr->name, tdata))
	{
		free(mh->env->name);
		if (mh->env->data != NULL)
			free(mh->env->data);
		free(mh->env);
		mh->env = curr->next;
		return ;
	}
	curr = curr->next;
	return (unset_2(curr, tdata));
}

int	handle_for_unset(t_mhstruct *mh, char *tdata)
{
	char	*arg;
	int		i;

	i = 1;
	arg = tdata;
	if (!ft_isalpha(arg[0]))
		return (pr_err(mh, 1, gemsg(mh->emsg[2], mh->emsg[10], tdata)), 1);
	while (arg[i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (pr_err(mh, 1, gemsg(mh->emsg[2], mh->emsg[10], tdata)), 1);
		i++;
	}
	return (0);
}

void	builtin_unset(t_mhstruct *mh)
{
	t_token	*token;

	token = mh->token->next;
	if (token == NULL )
		return ;
	while (token != NULL)
	{
		while (1)
		{
			if (handle_for_unset(mh, token->data) == 1)
				break ;
			unset(mh, token->data);
			break ;
		}
		token = token->next;
	}
	return ;
}
