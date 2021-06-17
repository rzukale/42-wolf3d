/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unfilter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 16:12:55 by rzukale           #+#    #+#             */
/*   Updated: 2021/03/26 17:37:39 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	convert_to_pixels(t_png *png)
{
	png->final_size = (png->height * png->width * png->bpp + 7) / 8;
	if (!(png->pixels = (unsigned char *)malloc(sizeof(unsigned char)
		* png->final_size)))
		error_output("Memory allocation of filtered pixel pointer failed\n");
	unfilter_scanlines(png, png->pixels, png->inflated);
}

void	unfilter_scanlines(t_png *png, unsigned char *out, unsigned char *in)
{
	t_scan_helper	s;

	s.line = 0;
	s.prev = 0;
	s.byte_width = (png->bpp + 7) / 8;
	s.line_bytes = (png->width * png->bpp + 7) / 8;
	while (s.line < png->height)
	{
		s.out_index = s.line_bytes * s.line;
		s.in_index = (1 + s.line_bytes) * s.line;
		s.filter = in[s.in_index];
		if (s.filter > 4)
			error_output("filtering error\n");
		process_scanline(&out[s.out_index], &in[s.in_index + 1], s);
		s.prev = &out[s.out_index];
		s.line++;
	}
}

void	process_scanline(unsigned char *out,
	unsigned char *sl, t_scan_helper s)
{
	unsigned int i;

	if (s.filter == 0)
	{
		i = 0;
		while (i++ < s.line_bytes)
			out[i] = sl[i];
	}
	else if (s.filter == 1)
	{
		sub(out, sl, s);
	}
	else if (s.filter == 2)
	{
		up(out, sl, s);
	}
	else if (s.filter == 3)
	{
		avg(out, sl, s);
	}
	else if (s.filter == 4)
	{
		paeth(out, sl, s);
	}
}
