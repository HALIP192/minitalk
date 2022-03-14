/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntitan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 20:15:49 by ntitan            #+#    #+#             */
/*   Updated: 2022/03/14 20:46:26 by ntitan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

#include "signal.h"
#include "unistd.h"
#include "stdint.h"

void	print_promt(pid_t pid)
					__attribute__((__nothrow__));
void	ft_memset64(uintmax_t *buff_ptr)
					__attribute__((__nothrow__));
void	ft_putunbr(unsigned char *start, pid_t pid);

#endif
