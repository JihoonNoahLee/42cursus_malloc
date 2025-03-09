/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __malloc_core.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoolee <jihoolee@student.42SEOUL.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 10:27:34 by jihoolee          #+#    #+#             */
/*   Updated: 2025/03/09 21:17:48 by jihoolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MALLOC_CORE_H
# define __MALLOC_CORE_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/mman.h>

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

# define WORD_SIZE			sizeof(size_t)
# define DOUBLE_WORD_SIZE	(2 * WORD_SIZE)
# define PAGE_SIZE			page_size()

# define MAX_TINY_BLOCK_SIZE	128
# define MAX_SMALL_BLOCK_SIZE	1024

# define TINY_POOL_SIZE		ceil_align(MAX_TINY_BLOCK_SIZE * 128, PAGE_SIZE)
# define SMALL_POOL_SIZE	ceil_align(MAX_SMALL_BLOCK_SIZE * 128, PAGE_SIZE)

typedef struct s_block_header
{
	size_t	header;
}	t_block_header;

# define BLOCK_USED_FLAG	0b001
// 0b110 reserved for future use
# define BLOCK_SIZE_SHIFT	3

typedef struct s_pool_header
{
	struct s_pool_header	*next;
	size_t					free_size;
	size_t					max_size;
}	t_pool_header;

typedef struct s_heap
{
	t_pool_header	*tiny_pool;
	t_pool_header	*small_pool;
	t_pool_header	*large_pool;
}	t_heap;

enum e_mem_type	__get_mem_type(size_t size);

// __find_next_available.c
void			*__find_next_available_pool(t_pool_header *pool, size_t size);
void			*__find_next_available_block(t_block_header *block,
					size_t size);

// __allocate.c
void			*__allocate_tiny(t_heap *const p_heap, size_t size);

#endif
