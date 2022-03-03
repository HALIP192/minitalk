/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntitan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 22:19:20 by ntitan            #+#    #+#             */
/*   Updated: 2022/03/03 17:25:58 by ntitan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

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
	static int	 answer = 0;

	if (sig == SIGUSR1)
		answer++;
	else
	{
		ft_putnbr_fd(answer, 1);
		ft_putchar_fd('\n', 1);
		exit(0);
	}

}

static	void	send_mesage(int pid, char *str)
{
	int		cur_bit;
	char	cur_c;
	
	while (*str)
	{
		cur_bit = 7;
		cur_c = *str++;
		while (cur_bit >= 0)
		{
			if (cur_c & (1 << cur_bit))
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			usleep(200);
			cur_bit--;
		}

	}
	while (cur_bit++ < 8)
	{
		kill(pid, SIGUSR1);
		usleep(200);
	}
}

int		main(int argc, char **argv)
{
	if (argc != 3 || !ft_strlen(argv[2]))
			return (1);
	ft_putstr_fd("To_server:\n", 1);
	ft_putstr_fd(argv[2], 1);
	ft_putstr_fd("\nGet_back : \n", 1);
	signal(SIGUSR1, get_answer);
	signal(SIGUSR2, get_answer);
	send_mesage(ft_atoi(argv[1]), argv[2]);
	while (1)
		pause();
	return (0);
}

