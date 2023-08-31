/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 13:37:40 by vtavitia          #+#    #+#             */
/*   Updated: 2023/08/31 13:40:57 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vtavitia.h"

int	do_gt(t_token **t, t_mhstruct **mh)
{
	int	fd;

	if (access((*t)->next->data, F_OK) == 0)
	{
		if (access((*t)->next->data, W_OK) != 0)
		{
			pr_err(*mh, 1, gemsg((*t)->next->data, (*mh)->emsg[7], ""));
			return (1);
		}
	}
	else
	{
		fd = open((*t)->next->data, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		dup2(fd, STDOUT_FILENO);
	}
	return (0);
}

int	do_d_gt(t_token **t, t_mhstruct **mh)
{
	int	fd;

	if (access((*t)->next->data, F_OK) == 0)
	{
		if (access((*t)->next->data, W_OK) != 0)
		{
			pr_err(*mh, 1, gemsg((*t)->next->data, (*mh)->emsg[7], ""));
			return (1);
		}
	}
	{
		fd = open((*t)->next->data, O_CREAT | O_APPEND | O_WRONLY, 0644);
		dup2(fd, STDOUT_FILENO);
	}
	return (0);
}
