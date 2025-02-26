/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_core.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoolee <jihoolee@student.42SEOUL.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 10:27:34 by jihoolee          #+#    #+#             */
/*   Updated: 2025/02/26 23:04:42 by jihoolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_CORE_H
# define MALLOC_CORE_H

# include <unistd.h>
# include <stdlib.h>

enum e_mem_type
{
	TINY,
	SMALL,
	LARGE
};

inline size_t	page_size(void)
{
	static size_t	page_size = 0;

	if (page_size == 0)
		page_size = getpagesize();
	return (page_size);
}

static inline size_t	ceil_align(size_t size, size_t align_len)
{
	return ((size + align_len - 1) & ~(align_len - 1));
}

# define WORD_LEN			sizeof(size_t)
# define DOUBLE_WORD_LEN	(2 * WORD_LEN)
# define PAGE_SIZE			page_size()
# define ALIGN_LEN			DOUBLE_WORD_LEN

# define TINY_BLOCK_SIZE	128
# define SMALL_BLOCK_SIZE	1024

# define TINY_POOL_SIZE		ceil_align(TINY_BLOCK_SIZE * 128, PAGE_SIZE)
# define SMALL_POOL_SIZE	ceil_align(SMALL_BLOCK_SIZE * 128, PAGE_SIZE)

#endif
