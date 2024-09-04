/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tst_put_num.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 19:12:32 by retanaka          #+#    #+#             */
/*   Updated: 2024/09/04 11:37:15 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tst_mini_printf.h"

void	tst_put_d(void)
{
	put_d(42);
	put("\n");
	put_d(0);
	put("\n");
	put_d(-42);
	put("\n");
	put_d(INT32_MAX - 1);
	put("\n");
	put_d(INT32_MAX);
	put("\n");
	put_d(INT32_MIN + 1);
	put("\n");
	put_d(INT32_MIN);
	put("\n");
}

void	tst_put_u(void)
{
	put_u(42);
	put("\n");
	put_u(0);
	put("\n");
	put_u(UINT32_MAX);
	put("\n");
	put_u(UINT32_MAX - 1);
	put("\n");
}

void	tst_put_ld(void)
{
	put_ld(42);
	put("\n");
	put_ld(0);
	put("\n");
	put_ld(-42);
	put("\n");
	put_ld(INT64_MAX - 1);
	put("\n");
	put_ld(INT64_MAX);
	put("\n");
	put_ld(INT64_MIN + 1);
	put("\n");
	put_ld(INT64_MIN);
	put("\n");
}

void	tst_put_lu(void)
{
	put_lu(42);
	put("\n");
	put_lu(0);
	put("\n");
	put_lu(UINT64_MAX);
	put("\n");
	put_lu(UINT64_MAX - 1);
	put("\n");
}
