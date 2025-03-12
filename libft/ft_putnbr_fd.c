/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoolee <jihoolee@student.42SEOUL.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 22:37:51 by jihoolee          #+#    #+#             */
/*   Updated: 2025/03/10 07:56:43 by jihoolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	recur_putnbr_fd(size_t n, int fd)
{
	char	c;

	if (n == 0)
		return ;
	else
	{
		c = n % 10 + '0';
		recur_putnbr_fd(n / 10, fd);
	}
	write(fd, &c, 1);
}

void	ft_putnbr_fd(size_t n, int fd)
{
	if (n == 0)
		write(fd, "0", 1);
	else
		recur_putnbr_fd(n, fd);
}
