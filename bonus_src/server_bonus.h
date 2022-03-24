/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntitan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 17:14:55 by ntitan            #+#    #+#             */
/*   Updated: 2022/03/24 17:15:05 by ntitan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_BONUS_H
# define SERVER_BONUS_H

# include "signal.h"
# include "unistd.h"
# include "stdint.h"
# include "stdlib.h"

void	print_promt(pid_t pid)
		__attribute__((__nothrow__));
void	ft_memset64(uintmax_t *buff_ptr)
		__attribute__((__nothrow__));
void	ft_putunbr(unsigned char *start, pid_t pid);

#endif
