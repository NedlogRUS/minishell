/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 12:05:18 by vtavitia          #+#    #+#             */
/*   Updated: 2023/08/04 14:27:36 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vtavitia.h"

void	error_msg2(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	int		i;
	int		k;

	join = malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2) + 1)));
	i = 0;
	while (s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	k = i;
	i = 0;
	while (s2[i])
	{
		join[k] = s2[i];
		i++;
		k++;
	}
	join[k] = '\0';
	return (join);
}

int	check_first_comm(char *argv, char **envp)
{
	int		result;
	char	**paths;

	result = 0;
	path_to_array(&paths, envp);
	result = join_commands(paths, argv);
	return (result);
}

int	check_pipe_exists(t_token *t)
{
	while (t->next)
	{
		if (t->type == PIPELINE)
			return (1);
		t = t->next;
	}
	if (t->type == PIPELINE)
		return (1);
	return (0);
}