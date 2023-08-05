/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_for_execve.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:49:47 by vtavitia          #+#    #+#             */
/*   Updated: 2023/08/04 18:52:20 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vtavitia.h"

static int	check_path_exists2(char **paths, char *argv, char **command_path)
{
	int		i;
	int		j;
	char	*tmp;
	int		check;

	i = 2;
	j = 0;
	check = 0;
	argv = cut_argv(argv);
	while (paths[j] != NULL)
	{
		*command_path = ft_strjoin("/", argv);
		tmp = *command_path;
		*command_path = ft_strjoin(paths[j], tmp);
		if (access(*command_path, R_OK) == 0)
			return (check++);
		else
			*command_path = NULL;
		j++;
		free(tmp);
	}
	free(argv);
	return (check);
}

int	check_path_exists(char *argv, char **envp, char **command_path)
{
	int		i;
	char	**paths;
	int		check;

	path_to_array(&paths, envp);
	i = 2;
	check = 0;
	check = check_path_exists2(paths, argv, command_path);
	free_all(paths);
	return (check);
}
