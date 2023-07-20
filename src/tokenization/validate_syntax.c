/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 18:44:21 by vtavitia          #+#    #+#             */
/*   Updated: 2023/07/17 19:52:53 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vtavitia.h"

int check_bad_specials(char *input, int *i, char c)
{
	(void)c;
	if (input[(*i)] == '<' && (input[(*i) - 2] == '<' || input[(*i) + 2] == '<'))
		return (1);
	else if (input[(*i)] == '>' && (input[(*i) - 2] == '>' || input[(*i) + 2] == '>'))
		return (1);
	(*i)++;
	return (0);
}

int	check_syntax(char *input)
{
	int		i;
	char	c;
	int		open;

	i = 0;
	open = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			open = 1;
			c = input[i];
			i++;
			while (open && input[i])
			{
				if (input[i] == c)
					open = 0;
				i++;
			}
		}
		else if (is_special(input[i]) && input[i] != '\''
			&& input[i] != '"' && input[i] != ' ' )
		{
			// printf("heree\n");
			{
				c = input[i];
				if (check_bad_specials(input, &i, c))
				{
					// check error eg  near unexpected token `>'
					error_msg("Syntax error - near unexpected token", 1);
					return (1);
				}
			}
		}
		i++;
	}
	return (0);
}