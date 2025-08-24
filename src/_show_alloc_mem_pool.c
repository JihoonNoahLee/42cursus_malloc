/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _show_alloc_mem_pool.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoolee <jihoolee@student.42SEOUL.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 19:00:41 by jihoolee          #+#    #+#             */
/*   Updated: 2025/08/24 19:36:08 by jihoolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "__malloc_core.h"

static void ___show_alloc_mem_block(const t_block_header *block)
{
	size_t	block_payload_size;

	block_payload_size = block->header & BLOCK_SIZE_MASK;
	ft_putptr_fd((void *)(block + 1), 1);
	ft_putstr_fd(" - ", 1);
	ft_putptr_fd((void *)((size_t)(block + 1) + block_payload_size), 1);
	ft_putstr_fd(" : ", 1);
	ft_putnbr_fd(block_payload_size, 1);
	ft_putstr_fd(" bytes\n", 1);
}

static void	__show_alloc_mem_blocks(const t_pool_header *pool)
{
	void					*end_of_pool;
	const t_block_header	*block_header;
	size_t					block_size;
	size_t					block_payload_size;

	end_of_pool = (void *)pool + pool->pool_size;
	block_header = (t_block_header *)(pool + 1);
	while ((void *)block_header < end_of_pool)
	{
		block_payload_size = block_header->header & BLOCK_SIZE_MASK;
		block_size = sizeof(t_block_header) + block_payload_size;
		if (block_header->header & BLOCK_USED_FLAG)
			___show_alloc_mem_block(block_header);
		block_header = (t_block_header *)((void *)block_header + block_size);
	}
}

void	_show_alloc_mem_pool(const t_pool_header *pool, enum e_mem_type type)
{
	char	*type_str[3];

	type_str[TINY] = "TINY";
	type_str[SMALL] = "SMALL";
	type_str[LARGE] = "LARGE";
	ft_putstr_fd(type_str[type], 1);
	ft_putstr_fd(" : ", 1);
	ft_putptr_fd((void *)(pool), 1);
	ft_putstr_fd("\n", 1);
	if (type == TINY || type == SMALL)
		__show_alloc_mem_blocks(pool);
	else
		___show_alloc_mem_block((t_block_header *)(pool + 1));
}
