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
	// t_env	*head = mh->env;
	t_env	*temp = NULL;

	if(!ft_strcmp(curr->name, tdata))
	{
		mh->env = curr->next;
		write(1, "CHECK\n", 6);
		free(curr->name);
		free(curr->data);
		free(curr->next);
		return;
	}
	curr = curr->next; // dont mandatory
	while (curr != NULL)
	{
		if(!ft_strcmp(curr->name, tdata))
		{
			free(curr->name);
			free(curr->data);
			if(curr->next != NULL)
				temp->next = curr->next;
			else
				temp->next = NULL;
			free(curr->next);
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
	
	if(!ft_isalpha(arg[0]))// not 1 ! mean 0
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
	t_token			*token;
	token = mh->token;
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

// void	unset(t_env** head, char *tdata)
// {
// 	t_env	*curr = *head;
// 	t_env	*temp = NULL;

// 	if(!ft_strcmp(curr->name, tdata))
// 	{
// 		free(curr->name);
// 		free(curr->data);
// 		*head = curr->next;
// 		free(curr->next);
// 		return;
// 	}
// 	curr = curr->next; // dont mandatory
// 	while (curr != NULL)
// 	{
// 		if(!ft_strcmp(curr->name, tdata))
// 		{
// 			free(curr->name);
// 			free(curr->data);
// 			if(curr->next != NULL)
// 				temp->next = curr->next;
// 			else
// 				temp->next = NULL;
// 			free(curr->next);
// 			return;
// 		}
// 		temp = curr;
// 		curr = curr->next;
// 	}
// 	return ;
// }

// int	handle_for_unset(t_mhstruct *mh, char *tdata)
// {
// 	char *arg = tdata;
// 	int i = 1;
	
// 	if(!ft_isalpha(arg[0]))// not 1 ! mean 0
// 	{
// 		printf("minihell: unset: %s : not a valid identifier\n", tdata);
// 		mh->er_num = 1;
// 		return 1;
// 	}
// 	while(arg[i])
// 	{
// 		if(!ft_isalnum(arg[i]) && arg[i] != '_')
// 		{
// 			printf("minihell: unset: %s : not a valid identifier\n", tdata);
// 			mh->er_num = 1;
// 			return 1;
// 		}
// 		i++;
// 	}
// 	return 0;
// }

// void builtin_unset(t_mhstruct *mh)
//  {
// 	t_token			*token;
// 	token = mh->token;
// 	token = token->next;
// 	if(token == NULL )
// 		return ;
// 	while(token != NULL)
// 	{
// 			while(1)
// 			{
// 				if(handle_for_unset(mh, token->data) == 1)
// 					break ;
// 				unset(&mh->env, token->data);
// 				break;
// 			}
// 			token = token->next;
// 	}
// 	return ;
// }