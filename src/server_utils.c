/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntitan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 20:15:05 by ntitan            #+#    #+#             */
/*   Updated: 2022/03/14 21:23:50 by ntitan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	print_prompt(pid_t pid)
{
	unsigned char	pat[59] = "[ OK ]server started successfully \n server PID: [00000000]\n";

	ft_putunbr(&pat[49], pid);
	write(1, pat, 59);
}

void	ft_memset64(uintmax_t *buff_ptr)
{
	buff_ptr[0] = 0x0000000000000000u;
	buff_ptr[1] = 0x0000000000000000u;
	buff_ptr[2] = 0x0000000000000000u;
	buff_ptr[3] = 0x0000000000000000u;
}
