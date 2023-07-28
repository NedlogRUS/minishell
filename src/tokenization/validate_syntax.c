/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 18:44:21 by vtavitia          #+#    #+#             */
/*   Updated: 2023/07/28 18:47:09 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vtavitia.h"

static void	check_helper(char *input, char c, int *i, int *open)
{
	*open = 1;
	(*i)++;
	while (*open)
	{
		if (input[*i] && input[*i] == c)
			*open = 0;
		(*i)++;
	}
}

static int	check_gt(char *input, int i, int count, int open)
{
	char	c;

	c = '\0';
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			c = input[i];
			check_helper(input, c, &i, &open);
		}
		else
		{
			if (input[i] == '>')
				count++;
			else if (input[i] != '>' && input[i] != ' ')
				count = 0;
			if (count > 2)
				return (1);
			i++;
		}
	}
	return (0);
}

static int	check_lt(char *input, int i, int count, int open)
{
	char	c;

	c = '\0';
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			c = input[i];
			check_helper(input, c, &i, &open);
		}
		else
		{
			if (input[i] == '<')
				count++;
			else if (input[i] != '<' && input[i] != ' ')
				count = 0;
			if (count > 2)
				return (1);
			i++;
		}
	}
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

int	check_syntax(char *input, t_mhstruct *mh)
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
					error_msg("Syntax error - near unexpected token", 1, mh);
					return (1);
				}
			}
		}
		i++;
	}
	return (0);
}
