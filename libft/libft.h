/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoolee <jihoolee@student.42SEOUL.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 22:31:30 by jihoolee          #+#    #+#             */
/*   Updated: 2025/03/11 17:10:56 by jihoolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>

void	ft_putnbr_fd(size_t n, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putptr_fd(void *ptr, int fd);
size_t	ft_strlen(const char *s);

#endif
