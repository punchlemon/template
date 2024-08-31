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

#include "put.h"

void	tst_put_num(int64_t i)
{
	put_num(i);
	put("\n");
}

void	tst_put(char *s)
{
	put(s);
	put("\n");
}

int	main(void)
{
	tst_put(NULL);
	tst_put("Hello world!");
	tst_put("");
	tst_put_num(42);
	tst_put_num(0);
	tst_put_num(-42);
	tst_put_num(9223372036854775806);
	tst_put_num(9223372036854775807);
	tst_put_num(-9223372036854775807);
	tst_put_num(-9223372036854775807 -1);
	return (0);
}
