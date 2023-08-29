/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 18:09:54 by apanikov          #+#    #+#             */
/*   Updated: 2023/08/29 18:45:40 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	join_export(t_mhstruct *mh, char *tdata)
{
	t_env	*node;

	node = NULL;
	join_export_2(mh, tdata);
	if (!check_env_name(&mh->env, mh->utils->name))
	{
		node = create_env_node(mh->utils->name, mh->utils->data);
		if (node != NULL)
			insert_env_node(&mh->env, node);
	}
	else
		join_env_data(&mh->env, mh->utils->name, mh->utils->data);
	free(mh->utils->line);
	free(mh->utils->name);
	if (mh->utils->data != NULL)
		free(mh->utils->data);
	free(mh->utils);
	return ;
}

int	export(t_mhstruct *mh, char *tdata)
{
	int	i;

	i = 0;
	while (tdata[i])
	{
		if (tdata[i] == '+')
		{
			if (tdata[i + 1] != '=')
				return (pr_err(mh, 1, gemsg(mh->emsg[1], mh->emsg[10] \
				, tdata)), 1);
			else if (tdata[i + 1] == '=')
			{
				join_export(mh, tdata);
				return (1);
			}
		}
		else if (tdata[i] == '=')
		{
			add_export(mh, tdata);
			return (1);
		}
		i++;
	}
	return (1);
}

void	add_key(t_mhstruct *mh, char *tdata)
{
	t_env	*node;
	int		i;

	i = 0;
	node = NULL;
	while (tdata[i])
	{
		if (tdata[i] == '+')
			return (pr_err(mh, 1, gemsg(mh->emsg[1], mh->emsg[10], tdata)));
		i++;
	}
	if (!check_env_name(&mh->env, tdata))
	{
		node = create_env_node(tdata, NULL);
		if (node != NULL)
			insert_env_node(&mh->env, node);
	}
	else
		return ;
}

void	export_print(t_mhstruct *mh)
{
	t_env	*curr;

	curr = mh->env;
	while (curr != NULL)
	{
		printf("declare -x %s", curr->name);
		if (curr->data != NULL)
			printf("=\"%s\"\n", curr->data);
		else
			printf("\n");
		curr = curr->next;
	}
}

void	builtin_export(t_mhstruct *mh)
{
	t_token	*token;

	token = mh->token->next;
	if (token == NULL )
		return (export_print(mh));
	while (token != NULL)
	{
		while (1)
		{
			if (handle_for_export(mh, token->data) == 1)
				break ;
			if (ft_strchr(token->data, '='))
			{
				if (export(mh, token->data) == 1)
					break ;
			}
			else
			{
				add_key(mh, token->data);
				break ;
			}
		}
		token = token->next;
	}
	return ;
}
