/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 19:10:07 by retanaka          #+#    #+#             */
/*   Updated: 2024/08/28 19:10:09 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUT_H
# define PUT_H
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include "common.h"
# define INTMIN_ADDR "-9223372036854775808"
# define INT64_MAX_10 922337203685477580

// function
int			put(char *src);
int			put_d64(int64_t num);
int			put_ud64(uint64_t num);

#endif
