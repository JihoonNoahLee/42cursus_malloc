/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __find_next_available.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoolee <jihoolee@student.42SEOUL.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 00:07:45 by jihoolee          #+#    #+#             */
/*   Updated: 2025/08/24 20:13:59 by jihoolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_malloc_core.h"

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

t_block_header	*___find_next_available_block(t_pool_header *pool, size_t size)
{
	void			*end_of_pool;
	t_block_header	*block;
	size_t			block_total_size;

	end_of_pool = (void *)pool + pool->pool_size;
	block = (t_block_header *)(pool + 1);
	while ((void *)block < end_of_pool
		&& (block->header & BLOCK_USED_FLAG
			|| (block->header & BLOCK_SIZE_MASK) < size))
	{
		block_total_size
			= sizeof(t_block_header) + (block->header & BLOCK_SIZE_MASK);
		block = (t_block_header *)((void *)block + block_total_size);
	}
	if ((void *)block >= end_of_pool)
		return (NULL);
	return (block);
}
