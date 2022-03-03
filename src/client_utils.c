/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntitan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 23:09:52 by ntitan            #+#    #+#             */
/*   Updated: 2022/03/03 14:28:02 by ntitan           ###   ########.fr       */
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

int ft_digit(char c)
{
    if (c <= '9' || c >= '0')
        return (1);
    return (0);
}

static int	ft_isspace_atoi(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || \
		c == '\r' || c == '\v' || c == '\f')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	minus;
	int	num;
	int	count;

	i = 0;
	minus = 1;
	num = 0;
	count = 0;
	while (ft_isspace_atoi(str[i]))
		i = i + 1;
	if (str[i] == '-')
		minus = -1;
	if (str[i] == '-' || str[i] == '+')
		i = i + 1;
	while (ft_digit(str[i]))
	{
		num = num * 10 + str[i++] - '0';
		count++;
	}
	if (count >= 19 && minus == -1)
		return (0);
	else if (count >= 19)
		return (-1);
	return (num * minus);
}
