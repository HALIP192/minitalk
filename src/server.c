/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntitan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 22:17:54 by ntitan            #+#    #+#             */
/*   Updated: 2022/03/06 22:38:45 by ntitan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal.h"
#include "unistd.h"
#include "stdint.h"

#define BUFF_SIZE	0x40

ssize_t				write(int fd, const void *buf, size_t count)
					__attribute__((__nothrow__));
int					main(int argc, __attribute__((unused)) char *const *argv)
					__attribute__((__nothrow__));
static void			ft_sa_sigaction(int sig, siginfo_t *info,
						__attribute__((unused)) void *context)
					__attribute__((__nothrow__));
static uint8_t		server(void)
					__attribute__((warn_unused_result)) __attribute__((
							__nothrow__));
static void			ft_memset64(uintmax_t *buff_ptr)
					__attribute__((__nothrow__));
void				print_prompt(pid_t pid)
					__attribute__((__nothrow__));
void				print_ok(void)
					__attribute__((__nothrow__));

/*int		main(void)
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
}*/

volatile sig_atomic_t	g_pid_sig[2] = {};

static void	ft_putunbr(unsigned char *start, pid_t pid)
{
	start[7] = pid % 10 + 48;
	pid /= 10;
	start[6] = pid % 10 + 48;
	pid /= 10;
	start[5] = pid % 10 + 48;
	pid /= 10;
	start[4] = pid % 10 + 48;
	pid /= 10;
	start[3] = pid % 10 + 48;
	pid /= 10;
	start[2] = pid % 10 + 48;
	pid /= 10;
	start[1] = pid % 10 + 48;
	pid /= 10;
	start[0] = pid % 10 + 48;
}

/*static void	ft_putnbr_fd(int n, int fd)
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
}*/

void	print_prompt(pid_t pid)
{
	unsigned char	pat[] ="[ OK ]server started successfully \n server PID: [00000000]\n";
	ft_putunbr(&pat[49], pid);
	write(1, pat, 59);	
}

void	print_ok(void)
{
	unsigned char	pat[] = "[ OK ] got message from PID: [00000000]\n";
	ft_putunbr(&pat[30], g_pid_sig[1]);
	write(1, pat, 40);
}

/*static void	ft_putstr_fd(char *s, int fd)
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
}*/

/*static void	func(int sign, siginfo_t *inf, __attribute((unused)) void *context)
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
}*/

int	main(int argc, __attribute__((unused)) char *const *argv)
{
	struct sigaction	sig;
	uint_fast8_t		ret;

	if (argc != 1)
		write(1, "[WARN] server parameters ignored\n", 33);
	print_prompt(getpid());
	sigemptyset(&sig.sa_mask);
	sig.sa_sigaction = ft_sa_sigaction;
	sig.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
	while (1)
	{
		while (!g_pid_sig[1])
			;
		ret = server();
		g_pid_sig[1] = 0;
		if (ret)
		{
			print_ok();
			kill(g_pid_sig[0], SIGUSR2);
		}
		else
			kill(g_pid_sig[0], SIGUSR1);
	}
}

static void	ft_sa_sigaction(int sig, siginfo_t *info, __attribute__((unused))
				void *context)
{
	g_pid_sig[1] = sig;
	g_pid_sig[0] = info->si_pid;
}

static uint_fast8_t	server(void)
{
	static unsigned char	buff[BUFF_SIZE] = {};
	static unsigned char	bit = 0x00u;
	static unsigned char	sym = 0;
	uint_fast8_t			ret;

	if (g_pid_sig[1] == SIGUSR1)
		buff[sym] |= 1 << bit;
	bit = (bit + 1) % 8;
	sym += bit == 0;
	if (bit)
		return (0);
	ret = 0;
	if (!buff[sym - 1])
	{
		ret = 1;
		buff[sym - 1] = 0xAu;
	}
	if (ret || sym == 32)
	{
		write(1, buff, sym);
		ft_memset64((uintmax_t *)buff);
		sym = 0;
		return (ret);
	}
	return (0);
}

static void	ft_memset64(uintmax_t *buff_ptr)
{
	buff_ptr[0] = 0x0000000000000000u;
	buff_ptr[1] = 0x0000000000000000u;
	buff_ptr[2] = 0x0000000000000000u;
	buff_ptr[3] = 0x0000000000000000u;
}
