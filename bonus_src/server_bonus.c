/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntitan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 17:13:57 by ntitan            #+#    #+#             */
/*   Updated: 2022/03/24 17:14:03 by ntitan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server_bonus.h"

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
void				ft_memset64(uintmax_t *buff_ptr)
					__attribute__((__nothrow__));
void				print_prompt(pid_t pid)
					__attribute__((__nothrow__));
void				print_ok(void)
					__attribute__((__nothrow__));

volatile sig_atomic_t	g_pid_sig[2] = {};

void	ft_putunbr(unsigned char *start, pid_t pid)
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

void	print_ok(void)
{
	write(1, "[ OK ] got message\n", 19);
}

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
