/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __show_alloc_mem_pool.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoolee <jihoolee@student.42SEOUL.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 07:28:40 by jihoolee          #+#    #+#             */
/*   Updated: 2025/03/17 16:23:46 by jihoolee         ###   ########.fr       */
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
	while ((void *)block < (void *)pool + pool->pool_size)
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

static void	__show_alloc_mem_blocks_large(t_pool_header *pool)
{
	t_block_header	*block_header;
	size_t			size;

	block_header = (t_block_header *)(pool + 1);
	size = block_header->header;
	ft_putstr_fd((void *)(block_header + 1), 1);
	ft_putstr_fd(" - ", 1);
	ft_putptr_fd((void *)(block_header + 1) + size, 1);
	ft_putstr_fd(" : ", 1);
	ft_putnbr_fd(size, 1);
	ft_putstr_fd(" bytes\n", 1);
}

static t_pool_header	*__get_next_min_addr_pool(t_pool_header *pool,
	t_pool_header *prev_min_addr_pool)
{
	t_pool_header	*min_addr_pool;

	min_addr_pool = pool;
	while (pool)
	{
		if (pool < min_addr_pool && pool > prev_min_addr_pool)
			min_addr_pool = pool;
		pool = pool->next;
	}
	return (min_addr_pool);
}

void	__show_alloc_mem_pool(t_pool_header *pool, enum e_mem_type pool_type)
{
	size_t			pool_len;
	size_t			iter;
	t_pool_header	*prev_min_addr_pool;
	t_pool_header	*min_addr_pool;
	static void		(*p_show_alloc_mem_blocks[3])(t_pool_header *);

	p_show_alloc_mem_blocks[TINY] = &__show_alloc_mem_blocks;
	p_show_alloc_mem_blocks[SMALL] = &__show_alloc_mem_blocks;
	p_show_alloc_mem_blocks[LARGE] = &__show_alloc_mem_blocks_large;
	ft_putptr_fd(__get_next_min_addr_pool(pool, NULL), 1);
	ft_putstr_fd("\n", 1);
	pool_len = __get_pool_len(pool);
	iter = 0;
	prev_min_addr_pool = NULL;
	while (iter < pool_len)
	{
		min_addr_pool = __get_next_min_addr_pool(pool, prev_min_addr_pool);
		(*p_show_alloc_mem_blocks[pool_type])(min_addr_pool);
		prev_min_addr_pool = min_addr_pool;
		iter++;
	}
}
