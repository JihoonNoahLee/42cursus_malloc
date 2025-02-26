/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoolee <jihoolee@student.42SEOUL.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 01:01:28 by jihoolee          #+#    #+#             */
/*   Updated: 2025/02/26 23:39:37 by jihoolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_core.h"

static int g_malloc_init = 12;

void	free(void *ptr)
{
	if (ptr == NULL)
		return ;
}

void	*malloc(size_t size)
{
	void	*ptr;

	ptr = NULL;
	return (ptr);
}

void	*realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	new_ptr = NULL;
	return (new_ptr);
}

void	show_alloc_mem(void)
{
	return ;
}
