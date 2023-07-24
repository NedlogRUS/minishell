/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 18:44:21 by vtavitia          #+#    #+#             */
/*   Updated: 2023/07/24 13:00:49 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vtavitia.h"

static int	check_gt(char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		if (input[i] == '>')
			count++;
		if (input[i] != '>')
			count = 0;
		if (count > 2)
			return (1);
		i++;
	}
	i = 0;
	count = 0;
	return (0);
}

static int	check_bad_specials(char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		if (input[i] == '<')
			count++;
		if (input[i] != '<')
			count = 0;
		if (count > 2)
			return (1);
		i++;
	}
	if (check_gt(input))
		return (1);
	return (0);
}

int	check_syntax(char *input)
{
	int		i;
	char	c;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
			return (0);
		else if (is_special(input[i]) && input[i] != '\''
			&& input[i] != '"' && input[i] != ' ' )
		{
			{
				c = input[i];
				if (check_bad_specials(input))
				{
					error_msg("Syntax error - near unexpected token", 1);
					return (1);
				}
			}
		}
		i++;
	}
	return (0);
}
