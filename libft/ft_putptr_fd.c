/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoolee <jihoolee@student.42SEOUL.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 07:51:53 by jihoolee          #+#    #+#             */
/*   Updated: 2025/03/11 20:27:05 by jihoolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	recur_putptr_fd(size_t addr, int fd)
{
	char	c;

	if (addr == 0)
		return ;
	else
	{
		c = addr % 16 + '0';
		if (c > '9')
			c = addr % 16 - 10 + 'A';
		recur_putptr_fd(addr / 16, fd);
	}
	write(fd, &c, 1);
}

void	ft_putptr_fd(void *ptr, int fd)
{
	size_t	addr;

	addr = (size_t)ptr;
	write(fd, "0x", 2);
	if (addr == 0)
		write(fd, "0", 1);
	else
		recur_putptr_fd(addr, fd);
}
