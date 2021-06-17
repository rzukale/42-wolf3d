/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 15:19:58 by rzukale           #+#    #+#             */
/*   Updated: 2021/03/24 15:07:43 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	copy_idat_chunks(t_png *png)
{
	while (png->i < png->source.size)
	{
		get_current_chunk(&png->chunk, png->source.buf, png->i);
		if (ft_strcmp(png->chunk.type, "IDAT") == 0)
		{
			ft_memcpy(png->compressed + png->compressed_index,
				png->source.buf + png->i + 8, png->chunk.size);
			png->compressed_index += png->chunk.size;
		}
		png->i += png->chunk.size + 12;
	}
}

void	parse_png(t_png *png)
{
	validate_signature(png->source.buf);
	parse_data(png);
	decode_png(png);
}

void	free_png(t_png png)
{
	free(png.source.buf);
	free(png.compressed);
	free(png.inflated);
	free(png.pixels);
}

void	free_texture(t_texture *tex)
{
	free(tex->source);
	free(tex->pixels);
	free(tex);
}
