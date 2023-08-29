/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 13:40:16 by apanikov          #+#    #+#             */
/*   Updated: 2023/08/29 18:56:23 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	reassign_path(char **path, char **arg)
{
	free(*path);
	*path = ft_strdup(arg[0]);
}

char	*ft_mhjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	if (!s2)
		return (s1);
	new = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!new)
		return (0);
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		new[i + j] = s2[j];
		j++;
	}
	new[i + j] = '\0';
	free(s1);
	return (new);
}

int	get_arg_list_size(t_mhstruct *mh)
{
	int		i;
	t_token	*tmp;

	tmp = mh->token;
	i = 0;
	if (!mh->token)
		return (0);
	while (tmp != NULL)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char	*gemsg(char *cmndname, char *errmsg, char *data)
{
	char	*out;

	out = ft_strdup("miniHell: ");
	if (cmndname != NULL)
		out = ft_mhjoin(out, cmndname);
	if (data)
		out = ft_mhjoin(out, data);
	out = ft_mhjoin(out, errmsg);
	return (out);
}

void	pr_err(t_mhstruct *mh, int i, char *errmsg)
{
	(void) mh;
	g_error = i;
	ft_putstr_fd(errmsg, 2);
	free(errmsg);
	return ;
}
