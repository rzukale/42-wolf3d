/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inflate_setups.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 13:04:19 by rzukale           #+#    #+#             */
/*   Updated: 2021/04/13 16:12:19 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			setup_dynamic_helper(t_dynamic_helper *d,
	const unsigned char *in, unsigned int *bp)
{
	static unsigned int	clcl[NUM_CODE_LENGTH_CODES] = { 16, 17, 18, 0, 8,
		7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15 };

	ft_memset(d->bitlen, 0, sizeof(d->bitlen));
	ft_memset(d->bitlen_dst, 0, sizeof(d->bitlen_dst));
	d->hlit = ft_read_bits(bp, in, 5) + 257;
	d->hdist = ft_read_bits(bp, in, 5) + 1;
	d->hclen = ft_read_bits(bp, in, 4) + 4;
	d->i = -1;
	while (++d->i < NUM_CODE_LENGTH_CODES)
	{
		if (d->i < d->hclen)
			d->codelengthcode[clcl[d->i]] = ft_read_bits(bp, in, 3);
		else
			d->codelengthcode[clcl[d->i]] = 0;
	}
}

/*
** a value >= numcodes is an address to another bit,
** a value < numcodes is a code.
** The 2 rows are the 2 possible bit values (0 or 1),
** there are as many columns as codes
*/

void			setup_tree_helper(t_tree_helper *h, const unsigned int *bitlen,
	t_huffman_tree *tree)
{
	h->nodefilled = 0;
	h->treepos = 0;
	ft_memset(h->blcount, 0, sizeof(h->blcount));
	ft_memset(h->nextcode, 0, sizeof(h->nextcode));
	h->n = -1;
	while (++h->n < tree->numcodes)
		h->blcount[bitlen[h->n]]++;
	h->n = 0;
	while (++h->n <= tree->maxbitlen)
		h->nextcode[h->n] = (h->nextcode[h->n - 1] + h->blcount[h->n - 1]) << 1;
	h->n = -1;
	while (++h->n < tree->numcodes)
	{
		if (bitlen[h->n] != 0)
			h->tree1d[h->n] = h->nextcode[bitlen[h->n]]++;
	}
	h->n = -1;
	while (++h->n < (tree->numcodes * 2))
		tree->tree2d[h->n] = UNINITED;
}

/*
** the base lengths represented by codes 257-285
** the extra bits used by codes 257-285 (added to base length)
*/

void			get_length_base_extra(unsigned int *length,
	unsigned int *num_extra_bits_dst, unsigned int code)
{
	static unsigned int	length_base[29] = { 3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 15,
		17, 19, 23, 27, 31, 35, 43, 51, 59, 67, 83, 99, 115, 131, 163, 195, 227,
		258 };
	static unsigned int	length_extra[29] = { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
		2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 0 };

	*length = length_base[code - FIRST_LENGTH_CODE_INDEX];
	*num_extra_bits_dst = length_extra[code - FIRST_LENGTH_CODE_INDEX];
}

/*
** the base backwards distances (the bits of distance codes appear
** after length codes and use their own huffman tree)
** the extra bits of backwards distances (added to base)
*/

void			get_dst_base_extra(unsigned int *distance,
	unsigned int *num_extra_bits_dst, unsigned int code_dst)
{
	static unsigned int	distance_base[30] = { 1, 2, 3, 4, 5, 7, 9, 13, 17, 25,
		33, 49, 65, 97, 129, 193, 257, 385, 513, 769, 1025, 1537, 2049, 3073,
		4097, 6145, 8193, 12289, 16385, 24577 };
	static unsigned int	distance_extra[30] = { 0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 4,
		4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13 };

	*distance = distance_base[code_dst];
	*num_extra_bits_dst = distance_extra[code_dst];
}
