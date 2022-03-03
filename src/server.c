/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntitan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 22:17:54 by ntitan            #+#    #+#             */
/*   Updated: 2022/03/01 00:27:37 by ntitan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>

static void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

static void	ft_putnbr_fd(int n, int fd)
{
	char		arr[10];
	size_t		len;
	long long	n_long;

	n_long = n;
	if (n_long < 0)
	{
		write(fd, "-", 1);
		n_long *= -1;
	}
	else if (n_long == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	len = 0;
	while (n_long)
	{
		arr[10 - 1 - (len++)] = '0' + n_long % 10;
		n_long /= 10;
	}
	write(fd, arr + 10 - len, len);
}

static void	func(int sign, siginfo_t *inf, __attribute((unused)) void *context)
{
	static int				i = 0;
	static pid_t			client_pid = 0;
	static unsigned char	c = 0;
	
	if (!client_pid)
		client_pid = inf->si_pid;
	c	|= (sign == SIGUSR2);
	if (++i == 8)
	{
		i = 0;
		if (!c)
		{
			kill(client_pid, SIGUSR2);
			client_pid = 0;
			return ;
		}
		write(1, &c, 1);
		c = 0;
		kill(client_pid, SIGUSR1);
	}
	else
		c <<= 1;
}

int		main(void)
{
	struct sigaction	sig_action;

	ft_putstr_fd("ServPID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	write(1,"\n", 1);
	sig_action.sa_sigaction = func;
	sig_action.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sig_action, 0);
	sigaction(SIGUSR2, &sig_action, 0);
	while (1)
		pause();
	return (0);
}
