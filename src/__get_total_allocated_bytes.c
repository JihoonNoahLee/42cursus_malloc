/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __get_total_allocated_bytes.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoolee <jihoolee@student.42SEOUL.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:28:20 by jihoolee          #+#    #+#             */
/*   Updated: 2025/03/17 15:42:18 by jihoolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "__malloc_core.h"

size_t	__get_total_allocated_bytes(t_pool_header *pool)
{
	size_t			total_bytes;
	t_block_header	*block;
	size_t			padded_block_size;

	total_bytes = 0;
	while (pool)
	{
		block = (t_block_header *)(pool + 1);
		while ((void *)block < (void *)pool + pool->pool_size)
		{
			if (block->header & BLOCK_USED_FLAG)
				total_bytes += block->header >> BLOCK_SIZE_SHIFT;
			padded_block_size = ceil_align(sizeof(t_block_header)
					+ (block->header >> BLOCK_SIZE_SHIFT), DOUBLE_WORD_SIZE);
			block = (t_block_header *)((void *)block + padded_block_size);
		}
		pool = pool->next;
	}
	return (total_bytes);
}

size_t	__get_total_allocated_bytes_large(t_pool_header *pool)
{
	size_t			total_bytes;
	t_block_header	*block;

	total_bytes = 0;
	while (pool)
	{
		block = (t_block_header *)(pool + 1);
		total_bytes += block->header;
		pool = pool->next;
	}
	return (total_bytes);
}
