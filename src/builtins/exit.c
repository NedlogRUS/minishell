/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <apanikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 12:54:14 by apanikov          #+#    #+#             */
/*   Updated: 2023/08/02 18:49:23 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_num_req(t_mhstruct *mh, const char *data)
{
	(void) mh;
	ft_putstr_fd("exit\n", 1);
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd((char *)data, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	exit(255);
}

int	check_long_min(const char *str)
{
	char	*line;
	char	*tmp;

	line = ft_strdup((char *) str);
	tmp = line;
	while (*tmp == 32 || (*tmp > 8 && *tmp < 14))
		tmp++;
	if ((!ft_strcmp(tmp, "-9223372036854775808")))
	{
		free(line);
		return (0);
	}
	free(line);
	return (1);
}

int	exit_check_long(const char *str)
{
	unsigned long long	out;
	int					sign;
	int					i;

	out = 0;
	sign = 1;
	i = 0;
	while (str[i] == 32 || (str[i] > 8 && str[i] < 14))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		out = out * 10 + str[i] - '0';
		i++;
		if (!(out <= 9223372036854775807))
			return (0);
	}
	return (1);
}

int	exit_atoi(const char *str)
{
	long long	out;
	int			sign;
	int			i;

	out = 0;
	sign = 1;
	i = 0;
	while (str[i] == 32 || (str[i] > 8 && str[i] < 14))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		out = out * 10 + str[i] - '0';
		i++;
	}
	return ((int)out * sign);
}

void	do_exit_2(t_mhstruct *mh, char *data)
{
	if (!check_long_min(data))
	{
		ft_putstr_fd("exit\n", 1);
		exit(0);
	}
	exit_num_req(mh, data);
}

void	do_exit(t_mhstruct *mh, int en, char *data)
{
	int	i;

	i = 0;
	if (!data)
	{
		ft_putstr_fd("exit\n", 1);
		exit(en);
	}
	while (data[i] == 32 || (data[i] > 8 && data[i] < 14))
		i++;
	if (data[i] == '-' || data[i] == '+')
		i++;
	if (!data[i])
		exit_num_req(mh, data);
	while (data[i])
	{
		if (!ft_isdigit(data[i]))
			exit_num_req(mh, data);
		i++;
	}
	if (!exit_check_long(data))
		do_exit_2(mh, data);
	ft_putstr_fd("exit\n", 1);
	exit(exit_atoi(data));
}

void	builtin_exit(t_mhstruct *mh)
{
	t_token	*token;
	int		i;

	i = 0;
	token = mh->token->next;
	if (token == NULL )
		do_exit(mh, mh->er_num, NULL);
	while (token != NULL) // don't forget chek for token type
	{
		i++;
		token = token->next;
	}
	if (i > 1)
	{
		printf("minihell: exit: too many arguments\n");
		mh->er_num = 1;
		return ;
	}
	token = mh->token->next;
	do_exit(mh, 0, token->data);
	return ;
}
