/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __allocate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoolee <jihoolee@student.42SEOUL.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 00:00:02 by jihoolee          #+#    #+#             */
/*   Updated: 2025/07/20 21:20:39 by jihoolee         ###   ########.fr       */
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
	new_pool->free_size
		= pool_size - (sizeof(t_pool_header) + sizeof(t_block_header));
	new_pool->pool_size = pool_size;
	((t_block_header *)(new_pool + 1))->header = (new_pool->free_size);
	*p_pool_header = new_pool;
	return (new_pool);
}

static void	*__append_new_block(t_pool_header *pool, const size_t size)
{
	t_block_header	*new_block;
	size_t			padded_block_size;
	t_block_header	*next_block;
	size_t			next_block_size;

	padded_block_size
		= ceil_align(sizeof(t_block_header) + size, DOUBLE_WORD_SIZE)
		- sizeof(t_block_header);
	new_block = __find_next_available_block(pool, padded_block_size);
	if (new_block == NULL)
		return (NULL);
	next_block = (t_block_header *)((void *)new_block + padded_block_size) + 1;
	next_block_size
		= (new_block->header & BLOCK_SIZE_MASK)
		- (sizeof(t_block_header) + padded_block_size);
	next_block->header = next_block_size;
	new_block->header = size | BLOCK_USED_FLAG;
	pool->free_size -= padded_block_size + sizeof(t_block_header);
	return ((void *)(new_block + 1));
}

void	*__allocate_tiny(t_heap *const p_heap, size_t payload_size)
{
	t_pool_header	*available_pool;

	available_pool
		= __find_next_available_pool(p_heap->tiny_pool, payload_size);
	if (available_pool == NULL)
		available_pool = __append_new_pool(&p_heap->tiny_pool, TINY_POOL_SIZE);
	if (available_pool == NULL)
		return (NULL);
	return (__append_new_block(available_pool, payload_size));
}

void	*__allocate_small(t_heap *const p_heap, size_t payload_size)
{
	t_pool_header	*available_pool;

	available_pool
		= __find_next_available_pool(p_heap->small_pool, payload_size);
	if (available_pool == NULL)
		available_pool
			= __append_new_pool(&p_heap->small_pool, SMALL_POOL_SIZE);
	if (available_pool == NULL)
		return (NULL);
	return (__append_new_block(available_pool, payload_size));
}

void	*__allocate_large(t_heap *const p_heap, size_t payload_size)
{
	t_pool_header	*new_pool;
	size_t			pool_size;

	pool_size = ceil_align(
			sizeof(t_pool_header) + sizeof(t_block_header) + payload_size,
			PAGE_SIZE);
	new_pool = __append_new_pool(&p_heap->large_pool, pool_size);
	if (new_pool == NULL)
		return (NULL);
	((t_block_header *)(new_pool + 1))->header = payload_size;
	return ((void *)(new_pool)
			+ sizeof(t_pool_header) + sizeof(t_block_header));
}
