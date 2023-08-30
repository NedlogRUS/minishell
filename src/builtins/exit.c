/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 12:54:14 by apanikov          #+#    #+#             */
/*   Updated: 2023/08/29 18:40:17 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exit_check_long(const char *str)
{
	unsigned long long	out;
	int					i;

	out = 0;
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
		do_exit(mh, g_error, NULL);
	while (token != NULL)
	{
		i++;
		token = token->next;
	}
	if (i > 1)
		return (pr_err(mh, 1, gemsg(mh->emsg[3], mh->emsg[6], NULL)));
	token = mh->token->next;
	do_exit(mh, 0, token->data);
	return ;
}
