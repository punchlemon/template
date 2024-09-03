/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tst_slice.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 19:12:32 by retanaka          #+#    #+#             */
/*   Updated: 2024/08/28 19:12:34 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tst_slice.h"

void	print_update(uint64_t len, uint64_t cap)
{
	int	result;

	put("len = ");
	put_ud64(len);
	put(", cap = ");
	put_ud64(cap);
	put("\nupdate_cap result : ");
	result = update_cap(len, &cap);
	put_d64(result);
	put("\nnew cap : ");
	put_ud64(cap);
	put("\n");
}

void	tst_update_cap(void)
{
	put("If *cap is NULL, update_cap return : ");
	put_d64(update_cap(42, NULL));
	put("\n");
	print_update(0, 0);
	print_update(1, 0);
	print_update(200, 0);
	print_update(200, 199);
	print_update(200, 200);
	print_update(200, 201);
	print_update(1025, 0);
	print_update(1025, 1023);
	print_update(1025, 1024);
}

void	tst_create_byte_slice(void)
{
	t_slice	*s;

	s = create_byte_slice(42);
	if (!s)
		return ((void)put((char *)s));
	put_ud64(s->l);
	put("\n");
	put_ud64(s->c);
	delete_byte_slice(s);
	put("\n");
}

void	tst_delete_byte_slice(void)
{
	t_slice	*s;

	delete_byte_slice(NULL);
	s = malloc(sizeof(t_slice));
	s->p = NULL;
	delete_byte_slice(s);
}
