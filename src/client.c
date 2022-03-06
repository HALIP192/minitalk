/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntitan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 22:19:20 by ntitan            #+#    #+#             */
/*   Updated: 2022/03/06 22:53:13 by ntitan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

volatile sig_atomic_t	g_signal = 1;

static void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static	void	get_answer(int sig)
{
	g_signal = sig;
}

static	int		send_message(pid_t pid, const char *str)
{
	static int		helper = SIGUSR1 - SIGUSR2;
	uint			cur_bit;
	unsigned char	cur_c;
	
	while (1)
	{
		cur_bit = 0;
		cur_c = *str;
		while (cur_bit < 8)
		{
			g_signal = 0;
			if (kill(pid, (int)((cur_c >> cur_bit) & 0x1u) * helper + SIGUSR2))
				return (1);
			while (!g_signal)
			{
			}
			if (g_signal == SIGUSR2)
				write(1, "Got it\n", 7);
			++cur_bit;
		}
		if (!*str++)
			break ;
	}
	return (0);
}

int		main(int argc, char **argv)
{
	pid_t	pid;

	if (argc != 3 || !ft_strlen(argv[2]))
			return (1);
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
	   return (1);	
	ft_putstr_fd("To_server:\n", 1);
	ft_putstr_fd(argv[2], 1);
	ft_putstr_fd("\nGet_back : \n", 1);
	signal(SIGUSR1, get_answer);
	signal(SIGUSR2, get_answer);
	if (send_message(pid , argv[2]))
			return ((int)(write(1, "Send message error\n", 19)));
	return (0);
}

