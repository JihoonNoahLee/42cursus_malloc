/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __find_next_available.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoolee <jihoolee@student.42SEOUL.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 00:07:45 by jihoolee          #+#    #+#             */
/*   Updated: 2025/03/13 01:30:27 by jihoolee         ###   ########.fr       */
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
	size_t			block_size;

	block = (t_block_header *)(pool + 1);
	while ((void *)block < (void *)pool + pool->max_size
		&& (block->header & BLOCK_USED_FLAG
			|| (block->header & ~METADATA_FLAG_BITS) < size))
	{
		block_size = sizeof(t_block_header)
			+ block->header & ~METADATA_FLAG_BITS;
		block = (t_block_header *)((void *)block + block_size);
	}
	if ((void *)block >= (void *)pool + pool->max_size)
		return (NULL);
	return (block);
}
