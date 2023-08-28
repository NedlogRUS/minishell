/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vatche <vatche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 18:44:21 by vtavitia          #+#    #+#             */
/*   Updated: 2023/08/28 17:38:47 by vatche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vtavitia.h"

void	check_helper(char *input, char c, int *i, int *open)
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

int	check_gt(char *input, int i, int count, int open)
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
			if (input[i] == '>' || input[i] == '<')
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

int	check_lt(char *input, int i, int count, int open)
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
			if (input[i] == '<' || input[i] == '>')
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

static int	syntax_conds(char *in, int i, t_mhstruct *mh)
{
	if ((in[i] == '<' || in[i] == '>') && ft_strlen(mh->input) == 1)
		return (1);
	if ((!ft_strcmp(in, "<<") || !ft_strcmp(in, ">>"))
		&& ft_strlen(mh->input) == 2)
		return (1);
	if ((!ft_strcmp(in, "<<>>") || !ft_strcmp(in, ">><<"))
		&& ft_strlen(mh->input) == 4)
		return (1);
	if ((!ft_strcmp(in, "<>") || !ft_strcmp(in, "<>"))
		&& ft_strlen(mh->input) == 2)
		return (1);
	return (0);
}

int	check_syntax(char *input, t_mhstruct *mh)
{
	int		i;

	i = 0;
	while (input[i])
	{
		if (syntax_conds(input, i, mh))
			return (1);
		if (check_bad_pipes(input, 0, 0, 0))
			return (1);
		if (input[i] == '\'' || input[i] == '"')
			return (0);
		else if (is_special(input[i]) && input[i] != '\''
			&& input[i] != '"' && input[i] != ' ' )
		{
			{
				if (check_bad_specials(input))
					return (1);
			}
		}
		i++;
	}
	return (0);
}
