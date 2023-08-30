/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 18:44:07 by vtavitia          #+#    #+#             */
/*   Updated: 2023/08/29 18:48:19 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_for_export(t_mhstruct *mh, char *tdata)
{
	char	*arg;
	int		i;

	arg = tdata;
	i = 1;
	if (!ft_isalpha(arg[0]))
		return (pr_err(mh, 1, gemsg(mh->emsg[1], mh->emsg[10], tdata)), 1);
	while (arg[i] && arg[i] != '+' && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (pr_err(mh, 1, gemsg(mh->emsg[1], mh->emsg[10], tdata)), 1);
		i++;
	}
	return (0);
}

int	check_env_name(t_env **head, char *name)
{
	t_env	*curr;

	curr = *head;
	while (curr != NULL)
	{
		if (!ft_strcmp(curr->name, name))
			return (1);
		curr = curr->next;
	}
	return (0);
}

void	change_env_data(t_env **head, char *name, char *data)
{
	t_env	*curr;

	curr = *head;
	while (curr != NULL)
	{
		if (!ft_strcmp(curr->name, name))
		{
			if (curr->data != NULL)
				free(curr->data);
			if (!data)
				curr->data = ft_strdup("\0");
			else
				curr->data = ft_strdup(data);
			return ;
		}
		curr = curr->next;
	}
	return ;
}

void	join_env_data(t_env **head, char *name, char *data)
{
	t_env	*curr;

	curr = *head;
	while (curr != NULL)
	{
		if (!ft_strcmp(curr->name, name))
		{
			if (curr->data != 0)
				curr->data = ft_mhjoin(curr->data, data);
			else
				curr->data = ft_strdup(data);
			return ;
		}
		curr = curr->next;
	}
	return ;
}

void	join_export_2(t_mhstruct *mh, char *tdata)
{
	mh->utils = malloc(sizeof(t_utils));
	mh->utils->data = NULL;
	mh->utils->line = ft_strdup(tdata);
	mh->utils->tmp = ft_strchr(mh->utils->line, '+');
	mh->utils->tmp[0] = '\0';
	mh->utils->name = ft_strdup(mh->utils->line);
	mh->utils->tmp[0] = '0';
	mh->utils->tmp++;
	mh->utils->tmp++;
	mh->utils->data = ft_strdup(mh->utils->tmp);
}
