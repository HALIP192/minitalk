/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntitan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 23:09:52 by ntitan            #+#    #+#             */
/*   Updated: 2022/03/14 20:14:36 by ntitan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	ft_putstr_fd(char *s, int fd)
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

void	ft_putnbr_fd(int n, int fd)
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

int	ft_digit(char c)
{
	if (c <= '9' && c >= '0')
		return (1);
	return (0);
}

pid_t	ft_atoi(const char *str)
{
	pid_t	ans;

	ans = 0;
	while (*str >= '0' && *str <= '9')
		ans = ans * 10 + *str++ - '0';
	return (ans);
}
