/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 14:38:36 by vtavitia          #+#    #+#             */
/*   Updated: 2023/07/15 17:18:23 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_msg(char *str, int err_num)
{
	errno = err_num;
	perror(str);
}

int	is_special(char c)
{
	char	*special;
	int		i;

	special = "\'\";| ";
	i = 0;
	while (special[i] != '\0')
	{
		if (special[i] == c || special[i] == '\0')
			return (1);
		i++;
	}
	return (0);
}

int	just_whitespace(char *input, int i)
{
	while (input[i] == ' ')
	{
		if (input[i] == '\0')
			return (1);
		i++;
	}
	while (input[i])
	{
		if (input[i] != ' ' || input[i] != '\0')
			break ;
		i++;
	}
	if (input[i] == '\0')
		return (1);
	return (0);
}

void	skip_all_whitespace(char *input, int *ip, int *jp)
{
	int	i;
	int	j;

	i = *ip;
	j = *jp;
	if (input[i] == ' ')
	{
		while (input[i] == ' ')
			i++;
		j = i;
	}
	*ip = i;
	*jp = j;
}

void	increment_i(char *input, int *ip)
{
	int	i;

	i = *ip;
	if (is_special(input[i]))
		i++;
	else
	{
		while (!is_special(input[i]) && input[i])
			i++;
	}
	*ip = i;
}
