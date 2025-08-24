/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _free_blcok.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoolee <jihoolee@student.42SEOUL.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 22:37:01 by jihoolee          #+#    #+#             */
/*   Updated: 2025/08/24 23:17:53 by jihoolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_malloc_core.h"

static t_block_header	*___get_next_block(t_block_header *current)
{
	return ((t_block_header *)((void *)current
		+ sizeof(t_block_header)
		+ (current->header & BLOCK_SIZE_MASK)));
}

static void	__merge_near_free_blocks(t_pool_header *pool)
{
	t_block_header	*current;
	t_block_header	*next;

	current = (t_block_header *)(pool + 1);
	next = ___get_next_block(current);
	while ((void *)next < (void *)pool + pool->pool_size)
	{
		if (!(current->header & BLOCK_USED_FLAG)
			&& !(next->header & BLOCK_USED_FLAG))
		{
			current->header += sizeof(t_block_header)
				+ (next->header & BLOCK_SIZE_MASK);
			next = ___get_next_block(current);
		}
		else
		{
			current = next;
			next = ___get_next_block(current);
		}
	}
}

void	_free_block(t_block_header *block, t_pool_header *pool)
{
	block->header &= ~BLOCK_USED_FLAG;
	pool->free_size
		+= sizeof(t_block_header) + (block->header & BLOCK_SIZE_MASK);
	__merge_near_free_blocks(pool);
}
