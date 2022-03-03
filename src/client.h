/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntitan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 14:11:29 by ntitan            #+#    #+#             */
/*   Updated: 2022/03/03 14:11:34 by ntitan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	CLIENT_H
# define CLIENT_H

# include <unistd.h>
# include <stdlib.h>
# include <signal.h>

void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_digit(char c);
void	ft_isspace_atoi(int c);
void	ft_atoi(const char *str);

#endif