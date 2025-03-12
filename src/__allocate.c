/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __allocate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoolee <jihoolee@student.42SEOUL.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 00:00:02 by jihoolee          #+#    #+#             */
/*   Updated: 2025/03/13 09:53:14 by jihoolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "__malloc_core.h"

static t_pool_header	*__append_new_pool(t_pool_header **p_pool_header,
	const size_t pool_size)
{
	t_pool_header	*new_pool;

	new_pool = (t_pool_header *)mmap(NULL, pool_size, PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);
	if (new_pool == MAP_FAILED)
		return (NULL);
	new_pool->next = *p_pool_header;
	new_pool->free_size = pool_size - sizeof(t_pool_header)
		- sizeof(t_block_header);
	new_pool->max_size = pool_size;
	((t_block_header *)(new_pool + 1))->header = new_pool->free_size;
	*p_pool_header = new_pool;
	return (new_pool);
}

static void	*__append_new_block(t_pool_header *pool, const size_t size)
{
	t_block_header	*new_block;
	size_t			padded_block_size;
	t_block_header	*next_block;

	padded_block_size
		= ceil_align(sizeof(t_block_header) + size, DOUBLE_WORD_SIZE)
		- sizeof(t_block_header);
	new_block = __find_next_available_block(pool, padded_block_size);
	if (new_block == NULL)
		return (NULL);
	next_block = (t_block_header *)((void *)new_block + padded_block_size) + 1;
	next_block->header = new_block->header
			- (sizeof(t_block_header) + padded_block_size);
	new_block->header = padded_block_size | BLOCK_USED_FLAG;
	pool->free_size -= padded_block_size + sizeof(t_block_header);
	return ((void *)(new_block + 1));
}

void	*__allocate_tiny(t_heap *const p_heap, size_t size)
{
	t_pool_header	*available_pool;

	available_pool = __find_next_available_pool(p_heap->tiny_pool, size);
	if (available_pool == NULL)
	available_pool = __append_new_pool(&p_heap->tiny_pool, TINY_POOL_SIZE);
	if (available_pool == NULL)
		return (NULL);
	return (__append_new_block(available_pool, size));
}
