/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tst_put.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 19:12:32 by retanaka          #+#    #+#             */
/*   Updated: 2024/08/28 19:12:34 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tst_put.h"

void	tst_put(void)
{
	put(NULL);
	put("\n");
	put("Hello world!");
	put("\n");
	put("");
	put("\n");
}

void	tst_put_d64(void)
{
	put_d64(42);
	put("\n");
	put_d64(0);
	put("\n");
	put_d64(-42);
	put("\n");
	put_d64(INT64_MAX - 1);
	put("\n");
	put_d64(INT64_MAX);
	put("\n");
	put_d64(INT64_MIN + 1);
	put("\n");
	put_d64(INT64_MIN);
	put("\n");
}

void	tst_put_ud64(void)
{
	put_ud64(42);
	put("\n");
	put_ud64(0);
	put("\n");
	put_ud64(UINT64_MAX);
	put("\n");
	put_ud64(UINT64_MAX - 1);
	put("\n");
}
