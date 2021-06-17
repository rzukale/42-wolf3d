/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inflate_trees.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 12:58:03 by rzukale           #+#    #+#             */
/*   Updated: 2021/04/13 16:19:33 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			init_huffman_tree(t_huffman_tree *tree, unsigned int *buffer,
	unsigned int num_codes, unsigned int maxbitlen)
{
	tree->tree2d = buffer;
	tree->numcodes = num_codes;
	tree->maxbitlen = maxbitlen;
}

void			ft_get_tree_inflate_dynamic(t_huffman *h,
	const unsigned char *in, unsigned int inlength)
{
	t_dynamic_helper d;

	if ((h->bit_p) >> 3 >= inlength - 2)
		error_output("bit pointer jumps past memory\n");
	setup_dynamic_helper(&d, in, &h->bit_p);
	ft_huffman_tree_create_lengths(&h->code_length_tree, d.codelengthcode);
	d.i = 0;
	while (d.i < (d.hlit + d.hdist))
	{
		d.code = ft_huffman_decode_symbol(in, &h->bit_p,
			&h->code_length_tree, inlength);
		if ((h->bit_p) >> 3 >= inlength)
			error_output("bit pointer jumps past memory\n");
		dynamic_code_cycle(&d, in, &h->bit_p);
	}
	if (d.bitlen[256] == 0)
		error_output("End code must be larger than 0\n");
	ft_huffman_tree_create_lengths(&h->codetree, d.bitlen);
	ft_huffman_tree_create_lengths(&h->codetree_dst, d.bitlen_dst);
}

void			ft_huffman_tree_create_lengths(t_huffman_tree *tree,
	const unsigned int *bitlen)
{
	t_tree_helper h;

	setup_tree_helper(&h, bitlen, tree);
	h.n = -1;
	while (++h.n < tree->numcodes)
	{
		h.i = -1;
		while (++h.i < bitlen[h.n])
			fill_nodes(&h, tree, bitlen);
	}
	h.n = -1;
	while (++h.n < (tree->numcodes * 2))
	{
		if (tree->tree2d[h.n] == UNINITED)
			tree->tree2d[h.n] = 0;
	}
}
