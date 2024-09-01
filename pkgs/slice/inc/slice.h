/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slice.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <retanaka@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 19:10:07 by retanaka          #+#    #+#             */
/*   Updated: 2024/08/28 19:10:09 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SLICE_H
# define SLICE_H
# include <stdint.h>
# include <stdlib.h>

// struct
typedef struct s_slice
{
	uint64_t	l;
	uint64_t	c;
	void		*p;
}	t_slice;

// function
t_slice	*create_byte_slice(uint64_t len);

#endif
