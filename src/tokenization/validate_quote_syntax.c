/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_quote_syntax.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 12:15:07 by vtavitia          #+#    #+#             */
/*   Updated: 2023/08/03 18:36:37 by vtavitia         ###   ########.fr       */
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
		return (1);
	return (0);
}

int	check_bad_specials(char *input)
{
	int	i;
	int	count;
	int	open;

	i = 0;
	count = 0;
	open = 0;
	if (check_lt(input, i, count, open))
		return (1);
	if (check_gt(input, i, count, open))
		return (1);
	return (0);
}
