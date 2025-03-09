/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __find_next_available.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoolee <jihoolee@student.42SEOUL.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 00:07:45 by jihoolee          #+#    #+#             */
/*   Updated: 2025/03/09 21:45:11 by jihoolee         ###   ########.fr       */
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
	size_t			size_word_count;
	size_t			curr_word_idx;
	size_t			max_word_count;

	block = (t_block_header *)(pool + 1);
	size_word_count = size / WORD_SIZE;
	curr_word_idx = 0;
	max_word_count = pool->max_size / WORD_SIZE;
	while (curr_word_idx < max_word_count
		&& ((block->header & BLOCK_USED_FLAG)
			|| (block->header >> BLOCK_SIZE_SHIFT) < size_word_count))
	{
		block = (t_block_header *)((size_t *)block
				+ (block->header >> BLOCK_SIZE_SHIFT));
		curr_word_idx += (block->header >> BLOCK_SIZE_SHIFT);
	}
	if (curr_word_idx >= max_word_count)
		return (NULL);
	return (block);
}
