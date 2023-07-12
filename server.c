/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiranda <jmiranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 23:14:07 by jmiranda          #+#    #+#             */
/*   Updated: 2023/07/12 13:46:50 by jmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static	size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (*(s + i) != '\0')
	{
		i++;
	}
	return (i);
}

static	char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	char	*tmp;

	if (!s1 || !s2)
		return (NULL);
	s3 = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s3)
		return (NULL);
	tmp = s3;
	while (*s1 != '\0')
		*(tmp++) = *(s1++);
	while (*s2 != '\0')
		*(tmp++) = *(s2++);
	*tmp = '\0';
	return (s3);
}

static	void	handler(int sig, siginfo_t *info, void *ucontext)
{
	static int			bit;
	static int			c;
	static char			*s = "";	

	(void) ucontext;
	if (sig == SIGUSR1)
		c |= (128 >> bit);
	bit++;
	if (bit == 8)
	{
		s = ft_strjoin(s, (char *)&c);
		if (c == '\0')
		{
			write(1, s, ft_strlen(s));
			write(1, "\n", 1);
			free(s);
			s = "";
			kill(info->si_pid, SIGUSR1);
		}
		bit = 0;
		c = 0;
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	sigact;

	(void)argv;
	if (argc != 1)
	{
		printf("Wrong Number Of Arguments\n");
		printf("Write : ./server\n");
		return (1);
	}
	printf("PID : %d\nWaiting for data...\n", getpid());
	sigact.sa_sigaction = handler;
	sigemptyset(&sigact.sa_mask);
	sigact.sa_flags = 0;
	sigaction(SIGUSR1, &sigact, NULL);
	sigaction(SIGUSR2, &sigact, NULL);
	while (1)
		pause();
	return (0);
}
