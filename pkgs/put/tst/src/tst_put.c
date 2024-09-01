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

void	tst_put_num(void)
{
	put_num(42);
	put("\n");
	put_num(0);
	put("\n");
	put_num(-42);
	put("\n");
	put_num(9223372036854775806);
	put("\n");
	put_num(9223372036854775807);
	put("\n");
	put_num(-9223372036854775807);
	put("\n");
	put_num(-9223372036854775807 -1);
	put("\n");
}
