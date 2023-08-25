/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vatche <vatche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 18:31:47 by apanikov          #+#    #+#             */
/*   Updated: 2023/08/25 16:01:34 by vatche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_path2(char **paths, char *argv, char **command_path)
{
	// int		i;
	int		j;
	char	*tmp;
	// i = 2;
	j = 0;
	argv = cut_argv(argv);
	while (paths[j] != NULL)
	{
		*command_path = ft_strjoin("/", argv);
		tmp = ft_strdup(*command_path);
		free(*command_path);
		*command_path = ft_strjoin(paths[j], tmp);
		free(tmp);
		if (access(*command_path, R_OK) == 0)
		{
			free(argv);
			return (1);
		}
		else
		{
			free(*command_path);
			*command_path = NULL;
		}
		j++;
	}
	free(argv);
	return (0);
}

int	check_path(char *argv, char **envp, char **command_path)
{
	// int		i;
	char	**paths;
	int		check;

	check = 0;
	path_to_array(&paths, envp);
	if (!(paths))
		return (check);
	// i = 2;
	check = check_path2(paths, argv, command_path);
	free_all(paths);
	return (check);
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

char	**get_arg_array(t_mhstruct *mh)
{
	char	**out;
	int		i;
	t_token	*token;

	token = mh->token;
	i = get_arg_list_size(mh);
	out = (char **)malloc((i + 1) * sizeof(char *));
	if (!out)
		return (NULL);
	i = 0;
	while (token != NULL)
	{
		out[i] = ft_strdup(token->data);
		token = token->next;
		i++;
	}
	out[i] = NULL;
	return (out);
}

int	execve_of_commands_2(char *path, char **arg, char **env)
{
	int	pid;
	int	out;

	out = 0;
	pid = fork();
	if (pid == 0)
	{
		out++;
		execve(path, arg, env);
	}
	else
		waitpid(pid, &out, 0);
	return (out);
}

void	execve_of_commands(t_mhstruct *mh)
{
	char	**arg;
	char	**env;
	char	*path;
	int		out;

	path = NULL;
	out = 0;
	env = get_env_array(mh);
	arg = get_arg_array(mh);
	if (check_path(arg[0], env, &path) == 0)
	{
		if (access(arg[0], R_OK) == 0)
			path = arg[0];
		else
		{
			free(env);
			free(path);
			pr_err(mh, 127, gemsg(mh->emsg[11], mh->emsg[12], arg[0]));
			free_all(arg);
			return ;
		}
	}
	if (path != NULL)
		out = execve_of_commands_2(path, arg, env);
	GLOBAL_ERROR = out / 256;
	free(env);
	free_all(arg);
}

// void	execve_of_commands(t_mhstruct *mh)
// {
// 	int		pid;
// 	char	**arg;
// 	char	**env;
// 	char	*path;
// 	int		out;

// 	path = NULL;
// 	out = 0;
// 	env = get_env_array(mh); //don,t forget to free env
// 	arg = get_arg_array(mh); //don,t forget to free env
// 	if (check_path(arg[0], env, &path) == 0)
// 	{
// 		if (access(arg[0], R_OK) == 0)
// 			path = arg[0];
// 		else
// 		{
// 			free(env);
// 			free(arg);
// 			return (pr_err(mh, 127, gemsg(mh->emsg[11], mh->emsg[12], arg[0])));
// 		}
// 	}
// 	if (path != NULL)
// 	{
// 		pid = fork();
// 		if (pid == 0)
// 		{
// 			out++;
// 			execve(path, arg, env);
// 		}
// 		else
// 			waitpid(pid, &out, 0);
// 	}
// 	GLOBAL_ERROR = out / 256;
// 	free(env);
// 	free(arg);
// 	return ;
// }