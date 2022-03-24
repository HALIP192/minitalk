/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntitan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 17:14:31 by ntitan            #+#    #+#             */
/*   Updated: 2022/03/24 17:14:33 by ntitan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server_bonus.h"

static void	print_pid(pid_t pid)
{
	int		i;
	char	*buf;

	i = 0;
	buf = (char *)malloc(sizeof(char) * 9);
	buf[8] = 0;
	while (i < 8)
	{
		buf[7 - i] = pid % 10 + 48;
		pid /= 10;
		i++;
	}
	write(1, buf, 8);
	free(buf);
}

void	print_prompt(pid_t pid)
{
	write(1, "[ OK ]server started successfully \n server PID: [", 49);
	print_pid(pid);
	write(1, "]\n", 2);
}

void	ft_memset64(uintmax_t *buff_ptr)
{
	buff_ptr[0] = 0x0000000000000000u;
	buff_ptr[1] = 0x0000000000000000u;
	buff_ptr[2] = 0x0000000000000000u;
	buff_ptr[3] = 0x0000000000000000u;
}
