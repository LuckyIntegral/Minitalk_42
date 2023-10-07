/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrants <vfrants@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 18:11:44 by vfrants           #+#    #+#             */
/*   Updated: 2023/10/07 15:49:07 by vfrants          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_received = 0;

void	error_handler(char *error)
{
	ft_putstr_fd("Error, ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}

void	end_of_message(int pid)
{
	ft_printf("\nReceived: %d chars from client %d\n", g_received, pid);
	g_received = 0;
	kill(pid, SIGUSR1);
}

void	receiver(int n, siginfo_t *info, void *ucontent)
{
	static char	res = 0;
	static int	counter = 0;

	(void) ucontent;
	if (n == SIGUSR2)
		res += 1 << counter;
	counter++;
	if (counter == 8)
	{
		if (res == '\0')
			end_of_message(info->si_pid);
		else
		{
			ft_putchar_fd(res, STDOUT);
			g_received++;
		}
		counter = 0;
		res = 0;
	}
	kill(info->si_pid, SIGUSR2);
}

void	setup_receiver(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = &receiver;
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		error_handler(ERROR_FOR_USERSIG);
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		error_handler(ERROR_FOR_USERSIG);
}

int	main(void)
{
	ft_printf("███╗░░░███╗██╗███╗░░██╗██╗████████╗░█████╗░██╗░░░░░██╗░░██╗\n");
	ft_printf("████╗░████║██║████╗░██║██║╚══██╔══╝██╔══██╗██║░░░░░██║░██╔╝\n");
	ft_printf("██╔████╔██║██║██╔██╗██║██║░░░██║░░░███████║██║░░░░░█████═╝░\n");
	ft_printf("██║╚██╔╝██║██║██║╚████║██║░░░██║░░░██╔══██║██║░░░░░██╔═██╗░\n");
	ft_printf("██║░╚═╝░██║██║██║░╚███║██║░░░██║░░░██║░░██║███████╗██║░╚██╗\n");
	ft_printf("╚═╝░░░░░╚═╝╚═╝╚═╝░░╚══╝╚═╝░░░╚═╝░░░╚═╝░░╚═╝╚══════╝╚═╝░░╚═╝\n");
	ft_printf("Server pid = %d\n", getpid());
	setup_receiver();
	while (1)
		pause();
	return (0);
}
