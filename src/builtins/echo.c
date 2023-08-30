/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:36:10 by apanikov          #+#    #+#             */
/*   Updated: 2023/08/29 18:37:51 by vtavitia         ###   ########.fr       */
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
	while (curr->next != NULL)
	{
		printf("%s ", curr->data);
		curr = curr->next;
	}
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
		if (str[i] != n)
			return (1);
		i++;
	}
	return (0);
}

void	builtin_echo(t_mhstruct *mh)
{
	t_token	*token;
	int		i;
	char	*tmp;

	token = mh->token->next;
	g_error = 0;
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
		if (!check_n(tmp, 'n'))
			i = 1;
		else
			break ;
		token = token->next;
	}
	do_echo(token, i);
	return ;
}
