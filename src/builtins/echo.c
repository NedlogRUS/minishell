/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <apanikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:36:10 by apanikov          #+#    #+#             */
/*   Updated: 2023/08/24 19:19:31 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	do_echo(t_token *token, int flag)
{
	t_token	*curr;

	curr = token;
	if (curr == NULL)
	{
		if (flag == 0)
			printf("\n");
		return ;
	}
	//while(curr != NULL && curr->next != NULL)
	while (curr->next != NULL) // don't forget chek for token type
	{
		printf("%s ", curr->data);
		curr = curr->next;
	}
	// don't forget chek for token type
	printf("%s", curr->data);
	if (flag == 0)
		printf("\n");
	return ;
}

int	check_n(const char *str, char n)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if(str[i] != n)
			return(1);
		i++;
	}
	return (0);
}

// cfix case echo "-nnnn" nenie_ir // i fix that
void	builtin_echo(t_mhstruct *mh)
{
	t_token	*token;
	int		i;
	char *tmp;

	token = mh->token->next;
	GLOBAL_ERROR = 0;
	i = 0;
	if (token == NULL )
	{	
		printf("\n");
		return ;
	}
	while (token != NULL && token->data[0] == '-')
	{
		tmp = token->data;
		tmp++;
		if(!check_n(tmp, 'n'))
			i = 1;
		else
			break;	
		token = token->next;
	}
	do_echo(token, i);
	return ;
}
