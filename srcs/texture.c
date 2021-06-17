/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 16:16:50 by rzukale           #+#    #+#             */
/*   Updated: 2021/03/24 14:58:39 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

unsigned int	add_pixel(unsigned char *data, int bpp, int pos)
{
	int				i;
	int				shift;
	unsigned int	pixel;

	i = 0;
	shift = bpp - 1;
	pixel = 0;
	while (i < bpp)
	{
		pixel |= (data[pos++] << (8 * shift--));
		i++;
	}
	return (pixel);
}

void			convert_to_unsigned_int(t_texture *tex, t_png *png)
{
	unsigned int x;
	unsigned int y;

	y = 0;
	while (y < png->height)
	{
		x = 0;
		while (x < png->width)
		{
			tex->pixels[(y * tex->w) + x] = add_pixel(png->pixels, tex->bpp,
				((y * tex->pitch) + x * tex->bpp));
			x++;
		}
		y++;
	}
}

t_texture		*create_texture(t_png *png, int idx)
{
	t_texture	*tex;

	if (!(tex = (t_texture*)malloc(sizeof(t_texture))))
		error_output("Memory allocation of t_texture struct failed\n");
	if (!(tex->source = (unsigned char *)malloc(sizeof(unsigned char)
		* png->source.size)))
		error_output("Memory allocation of editor pixel pointer failed\n");
	ft_memcpy(tex->source, png->source.buf, png->source.size);
	tex->h = png->height;
	tex->w = png->width;
	tex->bpp = (png->depth / 8) * png->channels;
	tex->size = png->final_size;
	tex->color_depth = png->depth;
	tex->color_type = png->color_type;
	tex->format = png->format;
	tex->source_size = png->source.size;
	tex->pitch = (tex->w * tex->bpp);
	tex->idx = idx;
	if (!(tex->pixels = (unsigned int *)malloc(sizeof(unsigned int) *
		(tex->h * tex->pitch))))
		error_output("Memory allocation of pixel pointer failed\n");
	convert_to_unsigned_int(tex, png);
	return (tex);
}
