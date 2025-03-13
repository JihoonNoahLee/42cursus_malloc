/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __show_alloc_mem_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoolee <jihoolee@student.42SEOUL.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 07:28:40 by jihoolee          #+#    #+#             */
/*   Updated: 2025/03/13 18:38:35 by jihoolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "__malloc_core.h"

static size_t	__get_pool_len(t_pool_header *pool)
{
	size_t			pool_len;
	t_pool_header	*iter;

	pool_len = 0;
	iter = pool;
	while (iter)
	{
		pool_len++;
		iter = iter->next;
	}
	return (pool_len);
}

static void	__show_alloc_mem_blocks(t_pool_header *pool)
{
	t_block_header	*block;
	size_t			block_size;
	size_t			padded_block_size;

	block = (t_block_header *)(pool + 1);
	while ((void *)block < (void *)pool + pool->max_size)
	{
		block_size = block->header >> BLOCK_SIZE_SHIFT;
		if (block->header & BLOCK_USED_FLAG)
		{
			ft_putptr_fd((void *)(block + 1), 1);
			ft_putstr_fd(" - ", 1);
			ft_putptr_fd((void *)((size_t)(block + 1) + block_size), 1);
			ft_putstr_fd(" : ", 1);
			ft_putnbr_fd(block_size, 1);
			ft_putstr_fd(" bytes\n", 1);
		}
		padded_block_size = ceil_align(sizeof(t_block_header) + block_size,
				DOUBLE_WORD_SIZE);
		block = (t_block_header *)((void *)block + padded_block_size);
	}
}

static t_pool_header	*__get_next_min_addr_pool(t_pool_header *pool,
	t_pool_header *prev_min_addr_pool)
{
	t_pool_header	*iter;
	t_pool_header	*min_addr_pool;

	iter = pool;
	min_addr_pool = NULL;
	while (iter)
	{
		if (min_addr_pool < iter && iter > prev_min_addr_pool)
			min_addr_pool = iter;
		iter = iter->next;
	}
	return (min_addr_pool);
}

void	__show_alloc_mem_pool(t_pool_header *pool, char *pool_type)
{
	size_t			pool_len;
	size_t			iter;
	t_pool_header	*prev_min_addr_pool;
	t_pool_header	*min_addr_pool;

	ft_putstr_fd(pool_type, 1);
	ft_putstr_fd(" : ", 1);
	ft_putptr_fd(__get_next_min_addr_pool(pool, NULL), 1);
	ft_putstr_fd("\n", 1);
	pool_len = __get_pool_len(pool);
	iter = 0;
	prev_min_addr_pool = NULL;
	while (iter < pool_len)
	{
		min_addr_pool = __get_next_min_addr_pool(pool, prev_min_addr_pool);
		__show_alloc_mem_blocks(min_addr_pool);
		prev_min_addr_pool = min_addr_pool;
		iter++;
	}
}

size_t	__get_total_allocated_bytes(t_pool_header *pool)
{
	size_t			total_bytes;
	t_block_header	*block;
	size_t			padded_block_size;

	total_bytes = 0;
	while (pool)
	{
		block = (t_block_header *)(pool + 1);
		while ((void *)block < (void *)pool + pool->max_size)
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
