/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _get_pool_by_block.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoolee <jihoolee@student.42SEOUL.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 22:07:56 by jihoolee          #+#    #+#             */
/*   Updated: 2025/08/24 22:34:13 by jihoolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_malloc_core.h"

static t_pool_header	*find_pool_having_block(t_block_header *block,
												const t_pool_header *pool_head)
{
	const t_pool_header	*pool;

	pool = pool_head;
	while (pool)
	{
		if ((void *)pool < (void *)block
			&& (void *)block < (void *)pool + pool->pool_size)
			return ((t_pool_header *)pool);
		pool = pool->next;
	}
	return (NULL);
}

t_pool_header	*_get_pool_by_block(t_block_header *block, const t_heap g_heap)
{
	size_t	block_size;

	block_size = block->header & BLOCK_SIZE_MASK;
	if (sizeof(t_block_header) + block_size <= MAX_TINY_BLOCK_SIZE)
		return (find_pool_having_block(block, g_heap.tiny_pool));
	else if (sizeof(t_block_header) + block_size <= MAX_SMALL_BLOCK_SIZE)
		return (find_pool_having_block(block, g_heap.small_pool));
	else
		return ((t_pool_header *)((void *)block
			- (sizeof(t_block_header) + sizeof(t_pool_header))));
}
