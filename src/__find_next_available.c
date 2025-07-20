/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __find_next_available.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoolee <jihoolee@student.42SEOUL.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 00:07:45 by jihoolee          #+#    #+#             */
/*   Updated: 2025/07/20 21:12:55 by jihoolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "__malloc_core.h"

t_pool_header	*__find_next_available_pool(t_pool_header *pool, size_t size)
{
	while (pool)
	{
		if (pool->free_size >= sizeof(t_block_header) + size)
			break ;
		pool = pool->next;
	}
	return (pool);
}

t_block_header	*__find_next_available_block(t_pool_header *pool, size_t size)
{
	t_block_header	*block;
	size_t			block_size_in_use;

	block = (t_block_header *)(pool + 1);
	while ((void *)block < (void *)pool + pool->pool_size
		&& (block->header & BLOCK_USED_FLAG
			|| (block->header & BLOCK_SIZE_MASK) < size))
	{
		block_size_in_use
			= ceil_align(
				sizeof(t_block_header) + (block->header & BLOCK_SIZE_MASK),
				DOUBLE_WORD_SIZE);
		block = (t_block_header *)((void *)block + block_size_in_use);
	}
	if ((void *)block >= (void *)pool + pool->pool_size)
		return (NULL);
	return (block);
}
