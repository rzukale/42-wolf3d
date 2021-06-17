/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inflate_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 13:13:42 by rzukale           #+#    #+#             */
/*   Updated: 2021/04/13 16:19:41 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			fill_nodes(t_tree_helper *h, t_huffman_tree *tree,
	const unsigned int *bitlen)
{
	h->bit = (unsigned char)((h->tree1d[h->n] >>
		(bitlen[h->n] - h->i - 1)) & 1);
	if (h->treepos > tree->numcodes - 2)
		error_output("treeposition mismatch\n");
	if (tree->tree2d[2 * h->treepos + h->bit] == UNINITED)
	{
		if (h->i + 1 == bitlen[h->n])
		{
			tree->tree2d[2 * h->treepos + h->bit] = h->n;
			h->treepos = 0;
		}
		else
		{
			h->nodefilled++;
			tree->tree2d[2 * h->treepos + h->bit] = h->nodefilled +
				tree->numcodes;
			h->treepos = h->nodefilled;
		}
	}
	else
		h->treepos = tree->tree2d[2 * h->treepos + h->bit] - tree->numcodes;
}

unsigned int	ft_huffman_decode_symbol(const unsigned char *in,
	unsigned int *bp, t_huffman_tree *codetree, unsigned int inlength)
{
	unsigned int	treepos;
	unsigned int	ct;
	unsigned char	bit;

	treepos = 0;
	ct = 0;
	while (1)
	{
		if (((*bp) & 0x07) == 0 && ((*bp) >> 3) > inlength)
			error_output("end of input memory reached without endcode\n");
		bit = ft_read_bit(bp, in);
		ct = codetree->tree2d[(treepos << 1) | bit];
		if (ct < codetree->numcodes)
			return (ct);
		treepos = ct - codetree->numcodes;
		if (treepos >= codetree->numcodes)
			error_output("invalid\n");
	}
}

void			dynamic_code_cycle(t_dynamic_helper *d, const unsigned char *in,
	unsigned int *bp)
{
	if (d->code <= 15)
	{
		if (d->i < d->hlit)
			d->bitlen[d->i] = d->code;
		else
			d->bitlen_dst[d->i - d->hlit] = d->code;
		d->i++;
	}
	else if (d->code == 16 || d->code == 17 || d->code == 18)
	{
		if (d->code == 16)
		{
			if ((d->i - 1) < d->hlit)
				d->value = d->bitlen[d->i - 1];
			else
				d->value = d->bitlen_dst[d->i - d->hlit - 1];
		}
		repeat_codes(d, in, bp);
	}
	else
		error_output("FLY YOU FOOLS\n");
}

void			fill_out(t_png *png, t_huffman_helper *s,
	t_huffman *h, const unsigned char *in)
{
	s->distance += ft_read_bits(&h->bit_p, in, s->num_extra_bits_dst);
	s->start = h->pos;
	s->backward = s->start - s->distance;
	if (h->pos + s->length >= png->inflated_size)
		error_output("bail\n");
	s->forward = -1;
	while (++s->forward < s->length)
	{
		png->inflated[h->pos++] = png->inflated[s->backward];
		s->backward++;
		if (s->backward >= s->start)
			s->backward = s->start - s->distance;
	}
}
