/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tst_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 16:19:09 by retanaka          #+#    #+#             */
/*   Updated: 2024/09/01 16:19:09 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tst_put.h"

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
