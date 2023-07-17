/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_quote_syntax.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 12:15:07 by vtavitia          #+#    #+#             */
/*   Updated: 2023/07/15 17:13:08 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_quotes_wrapped_loop(char *str, char c, int open, int i)
{
	while (str[i] != '\0')
	{
		if ((str[i] == '\'' || str[i] == '\"') && str[i] != '\0')
		{
			c = str[i];
			open = 1;
			i++;
			while (open && str[i])
			{
				if (str[i] == c)
				{
					open = 0;
					break ;
				}
				i++;
			}
		}
		if (str[i] == '\0')
			break ;
		i++;
	}
	return (open);
}

int	check_quotes_wrapped(char *str)
{
	int		i;
	int		open;
	char	c;

	i = 0;
	open = 0;
	c = '\0';
	open = check_quotes_wrapped_loop(str, c, open, i);
	if (open)
	{
		error_msg("Syntax error - check quotes", 1);
		return (1);
	}
	return (0);
}
