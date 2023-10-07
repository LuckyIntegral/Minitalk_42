/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrants <vfrants@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:47:57 by vfrants           #+#    #+#             */
/*   Updated: 2023/10/07 15:44:03 by vfrants          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_succes = 0;

void	error_handler(char *error)
{
	ft_putstr_fd("Error, ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}

void	set_flag(int i)
{
	if (i == SIGUSR1)
		ft_printf("The message is successfully received by server!");
	g_succes = 1;
}

void	send_chr(int pid, char c)
{
	int	counter;

	counter = 8;
	while (counter--)
	{
		g_succes = 0;
		if (kill(pid, ft_tr(c & 1, SIGUSR2, SIGUSR1)) == -1)
			error_handler(ERROR_FOR_USERSIG);
		c >>= 1;
		while (g_succes == 0)
			pause();
	}
}

void	send_str(int pid, char *c)
{
	while (*c)
	{
		send_chr(pid, *c);
		c++;
	}
	send_chr(pid, *c);
}

int	main(int c, char **v)
{
	int	i;
	int	pid;

	if (c != 3)
		error_handler(INVALID_ARGUMENT_COUNT);
	i = 0;
	pid = ft_atoi(v[1]);
	while (v[1][i])
		if (!ft_isdigit(v[1][i++]))
			error_handler(INVALID_PID);
	if (ft_strlen(v[1]) > 8 || pid > MAX_PID_NUMBER || pid <= 0)
		error_handler(INVALID_PID);
	if (!v[2][0])
		error_handler(INVALID_MESSAGE);
	signal(SIGUSR1, &set_flag);
	signal(SIGUSR2, &set_flag);
	send_str(pid, v[2]);
	return (0);
}
