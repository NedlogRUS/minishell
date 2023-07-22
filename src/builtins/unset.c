/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <apanikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 18:50:42 by apanikov          #+#    #+#             */
/*   Updated: 2023/07/21 20:33:45 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	unset(t_mhstruct *mh, char *tdata)
{
	t_env	*curr = mh->env;
	t_env	*temp = NULL;

	if(!ft_strcmp(curr->name, tdata))
	{
		free(mh->env);
		mh->env = curr->next;
		return;
	}
	curr = curr->next; // not necessary
	while (curr != NULL)
	{
		if(!ft_strcmp(curr->name, tdata))
		{
			if(curr->next != NULL)
				temp->next = curr->next;
			else
				temp->next = NULL;
			free(curr);
			return;
		}
		temp = curr;
		curr = curr->next;
	}
	return ;
}

int	handle_for_unset(t_mhstruct *mh, char *tdata)
{
	char *arg = tdata;
	int i = 1;
	
	if(!ft_isalpha(arg[0]))
	{
		printf("minihell: unset: %s : not a valid identifier\n", tdata);
		mh->er_num = 1;
		return 1;
	}
	while(arg[i])
	{
		if(!ft_isalnum(arg[i]) && arg[i] != '_')
		{
			printf("minihell: unset: %s : not a valid identifier\n", tdata);
			mh->er_num = 1;
			return 1;
		}
		i++;
	}
	return 0;
}

void builtin_unset(t_mhstruct *mh)
 {
	t_token	*token;
	token = mh->token; // token = mh->token->next;
	token = token->next;
	if(token == NULL )
		return ;
	while(token != NULL)
	{
			while(1)
			{
				if(handle_for_unset(mh, token->data) == 1)
					break ;
				unset(mh, token->data);
				break;
			}
			token = token->next;
	}
	return ;
}
