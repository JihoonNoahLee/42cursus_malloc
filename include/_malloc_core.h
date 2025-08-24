/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _malloc_core.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoolee <jihoolee@student.42SEOUL.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 10:27:34 by jihoolee          #+#    #+#             */
/*   Updated: 2025/08/24 22:36:52 by jihoolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MALLOC_CORE_H
# define __MALLOC_CORE_H

# include <unistd.h>
# include <sys/mman.h>
# include "libft.h"

enum e_mem_type
{
	TINY,
	SMALL,
	LARGE
};

static inline size_t	page_size(void)
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

# define BLOCK_USED_FLAG	((size_t)0b001)
// 0b110 reserved for future use
# define METADATA_FLAG_BITS	((size_t)0b111)
# define BLOCK_SIZE_MASK	(~METADATA_FLAG_BITS)

typedef struct s_pool_header
{
	struct s_pool_header	*next;
	size_t					free_size;
	size_t					pool_size;
}	t_pool_header;

typedef struct s_heap
{
	t_pool_header	*tiny_pool;
	t_pool_header	*small_pool;
	t_pool_header	*large_pool;
}	t_heap;

enum e_mem_type	_get_mem_type(size_t size);

// __find_next_available.c
t_pool_header		*__find_next_available_pool(t_pool_header *pool,
												size_t size);
t_block_header		*___find_next_available_block(t_pool_header *block,
													size_t size);

// _allocate.c
void				*_allocate_tiny(t_heap *const p_heap, size_t size);
void				*_allocate_small(t_heap *const p_heap, size_t size);
void				*_allocate_large(t_heap *const p_heap, size_t size);

// _get_pool_by_block.c
t_pool_header		*_get_pool_by_block(t_block_header *block,
										const t_heap g_heap);

// _free_block.c
void				_free_block(t_block_header *block, t_pool_header *pool);

// _show_alloc_mem_pool.c
void				_show_alloc_mem_pool(const t_pool_header *pool,
											enum e_mem_type type);

// _pool_traversal.c
const t_pool_header	*_get_next_min_pool(const t_heap g_heap,
										const t_pool_header *curr_min);
const t_pool_header	*_get_last_pool_in_heap(const t_heap g_heap);

// _get_allocated_bytes.c
size_t			_get_allocated_bytes(const t_pool_header *pool);

#endif
