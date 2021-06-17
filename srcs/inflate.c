/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inflate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 17:40:20 by rzukale           #+#    #+#             */
/*   Updated: 2021/03/24 16:01:31 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_inflate_huffman(t_png *png, const unsigned char *in, t_huffman *h)
{
	t_huffman_helper	s;

	s.done = 0;
	while (s.done == 0)
	{
		s.code = ft_huffman_decode_symbol(in, &h->bit_p,
			&h->codetree, png->compressed_size);
		check_code(&s, png, h);
		if (s.code >= FIRST_LENGTH_CODE_INDEX &&
			s.code <= LAST_LENGTH_CODE_INDEX)
		{
			get_length_base_extra(&s.length, &s.numextrabits, s.code);
			if ((h->bit_p >> 3) >= png->compressed_size)
				error_output("bit pointer will jump past memory\n");
			s.length += ft_read_bits(&h->bit_p, in, s.numextrabits);
			s.code_dst = ft_huffman_decode_symbol(in, &h->bit_p,
				&h->codetree_dst, png->compressed_size);
			if (s.code_dst > 29)
				error_output("invalid distance code\n");
			get_dst_base_extra(&s.distance, &s.num_extra_bits_dst, s.code_dst);
			if ((h->bit_p >> 3) >= png->compressed_size)
				error_output("bit pointer will jump past memory\n");
			fill_out(png, &s, h, in);
		}
	}
}

void	go_go_huffman(t_png *png, const unsigned char *in, t_huffman *h)
{
	init_huffman_tree(&h->codetree, h->codetree_buffer,
		NUM_DEFLATE_CODE_SYMBOLS, DEFLATE_CODE_BITLEN);
	init_huffman_tree(&h->codetree_dst, h->codetree_dst_buffer,
		NUM_DISTANCE_SYMBOLS, DISTANCE_BITLEN);
	init_huffman_tree(&h->code_length_tree, h->code_length_tree_buffer,
		NUM_CODE_LENGTH_CODES, CODE_LENGTH_BITLEN);
	ft_get_tree_inflate_dynamic(h, in, png->compressed_size);
	ft_inflate_huffman(png, in, h);
}

void	ft_inflate_data(t_png *png)
{
	t_huffman	h;
	int			done;

	h.bit_p = 0;
	h.pos = 0;
	done = 0;
	while (done == 0)
	{
		if ((h.bit_p >> 3) > png->compressed_size)
			error_output("bit pointing outside memory pointer\n");
		done = ft_read_bit(&h.bit_p, &png->compressed[2]);
		h.type = ft_read_bit(&h.bit_p, &png->compressed[2]) |
			(ft_read_bit(&h.bit_p, &png->compressed[2]) << 1);
		if (h.type == 3)
			error_output("zlib type error\n");
		else
			go_go_huffman(png, &png->compressed[2], &h);
	}
}

void	ft_inflate(t_png *png)
{
	if (png->compressed_size < 2)
		error_output("zlib size error\n");
	if ((png->compressed[0] * 256 + png->compressed[1]) % 31 != 0)
		error_output("FCHECK error\n");
	if ((png->compressed[0] & 15) != 8 || ((png->compressed[0] >> 4) & 15) > 7)
		error_output("zlib compression method error\n");
	ft_inflate_data(png);
}
