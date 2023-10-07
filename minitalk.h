/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfrants <vfrants@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 22:01:36 by vfrants           #+#    #+#             */
/*   Updated: 2023/10/06 14:51:34 by vfrants          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

// libft.h includes:
// --- unistd.h for: write, getpid, pause, sleep, usleep
// --- stdlib.h for: malloc, free, exit
// --- ft_printf for: ft_printf and standart funcs
# include "libft/ft_printf.h"
# include <signal.h> // signal, sigemptyset, sigaddsetq, sigaction, kill

// error status
# define INVALID_ARGUMENT_COUNT "Invalild argument number"
# define INVALID_PID "Invalid process id number"
# define INVALID_MESSAGE "Invalid message was passed"
# define ERROR_FOR_USERSIG "USRSIG signal failed"

// max pid number
# define MAX_PID_NUMBER 4194304

// usleep time
# define SIGTIME 800

#endif
