/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiranda <jmiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 23:13:58 by jmiranda          #+#    #+#             */
/*   Updated: 2023/07/12 13:48:01 by jmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static	int	ft_atoi(const char *str)
{
	int		i;
	int		neg;
	size_t	res;

	i = 0;
	neg = 1;
	res = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-')
	{
		neg = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res *= 10;
		res += str[i] - '0';
		i++;
	}
	return (res * neg);
}

static void	handler(int sig, siginfo_t *info, void *ucontext)
{
	(void) info;
	(void) ucontext;
	if (sig == SIGUSR1)
	{
		write(1, "Data Received\n", 14);
		exit(0);
	}
	else
	{
		write(1, "Signal Error\n", 13);
		exit(1);
	}
}

static	void	compare_send(pid_t pid, char *data)
{
	int	i;
	int	bit;

	i = 0;
	while ((i && data[i - 1]) || i == 0)
	{
		bit = 128;
		while (bit > 0)
		{
			if (bit & data[i])
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			bit /= 2;
			usleep(300);
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	pid_t				pid;
	struct sigaction	sigact;

	if (argc != 3)
	{
		printf("Error Wrong Number of Arguments\n");
		printf("./client [PID] [Data]\n");
		return (1);
	}
	pid = ft_atoi(argv[1]);
	sigact.sa_sigaction = handler;
	sigemptyset(&sigact.sa_mask);
	sigact.sa_flags = 0;
	sigaction(SIGUSR1, &sigact, NULL);
	sigaction(SIGUSR2, &sigact, NULL);
	compare_send(pid, argv[2]);
	while (1)
		pause();
	return (0);
}
