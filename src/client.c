/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntitan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 22:19:20 by ntitan            #+#    #+#             */
/*   Updated: 2022/03/03 14:09:08 by ntitan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <client.h>

static void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

static	void	get_answer(int pid)
{
	static int	 answer = 0;

	if (sig == SIGUSR1)
		answer++;
	else
	{
		ft_purnbr_fd(answer, 1);
		ft_putchar_fd('\n', 1);
		exit(0);
	}

}

static	void	send_msdge(int pid, char *str)
{
	int		cur_bit;
	char	cur_c;

	while (*str)
	{
		cur_bit = 0;
		cur_c = *str++;
		while (cur_bit < 8)
		{
			if (cur_c & (1 << cur_bit))
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			usleep(100);
			cur_bit++;
		}

	}
	while (cur_bit--)
	{
		kill(pid, SIGUSR1);
		usleep(100);
	}
}

int		main(int argc, char **argv)
{
	if (argc != 3 || !ft_strlen(argv[2]))
			return (1);
	ft_putstr_fd("To_server:\n", 1);
	ft_putstr_fd(argv[2], 1);
	ft_putstr_fd("Get_back", 1);
	signal(SigUSR1, action);
	signal(SIGUSR2, action);
	send_msge(ft_atoi(argv[1]), argv[2]);
	while (1)
		pause();
	return (0);
}

