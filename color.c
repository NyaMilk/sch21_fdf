/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslave <jslave@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 12:42:53 by mgrass            #+#    #+#             */
/*   Updated: 2019/11/19 19:21:07 by jslave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double			percent(int start, int end, int current)
{
	double		placement;
	double		distance;

	placement = current - start;
	distance = end - start;
	return ((distance == 0) ? 1.0 : (placement / distance));
}

int				get_light(int start, int end, double p)
{
	return ((int)((1 - p) * start + p * end));
}

int				get_color(int x, int y, t_bres *dt)
{
	int			r;
	int			g;
	int			b;
	double		p;

	if (dt->color_st == dt->color_end)
		return (dt->color_st);
	if (dt->dx1 > dt->dy1)
		p = percent(dt->x_start, dt->x_end, x);
	else
		p = percent(dt->y_start, dt->y_end, y);
	r = get_light((dt->color_st >> 16) & 0xFF, (dt->color_end >> 16) & 0xFF, p);
	g = get_light((dt->color_st >> 8) & 0xFF, (dt->color_end >> 8) & 0xFF, p);
	b = get_light(dt->color_st & 0xFF, dt->color_end & 0xFF, p);
	return ((r << 16) | (g << 8) | b);
}

void			create_color(t_fdf *fdf)
{
	int			x;
	int			y;
	int			z;
	double		p;

	y = -1;
	while (++y < fdf->rows)
	{
		x = -1;
		while (++x < fdf->cols)
		{
			z = fdf->map[y][x];
			p = percent(fdf->z_min, fdf->z_max, z);
			if (fdf->color[y][x] == 1 && p == 0.0)
				fdf->color[y][x] = 0x00FBFF;
			else if (fdf->color[y][x] == 1 && p < 0.2)
				fdf->color[y][x] = 0x008FB3;
			else if (fdf->color[y][x] == 1 && p < 0.6)
				fdf->color[y][x] = 0x20b2aa;
			else if (fdf->color[y][x] == 1 && p < 0.8)
				fdf->color[y][x] = 0x00ddbb;
			else if (fdf->color[y][x] == 1 && p <= 1.0)
				fdf->color[y][x] = 0xC8EA26;
		}
	}
}

void			change_color(t_fdf *fdf)
{
	int			*palette;
	static int	count = 0;
	int			x;
	int			y;

	palette = (int[22]){0x20b2aa, 0x98fb98, 0xff8247, 0xff7f,
	0x8b6914, 0x7cfc00, 0xbfff, 0xff00, 0x7fff00, 0xfa9a,
	0xdb7093, 0xadff2f, 0xadff2f, 0x32cd32, 0x473c8b, 0x9acd32,
	0x9acd32, 0x228b22, 0x228b22, 0x6b8e23, 0xfff8dc, 0xbdb76b};
	y = 0;
	while (y < fdf->rows)
	{
		x = -1;
		while (++x < fdf->cols)
		{
			fdf->color[y][x] = palette[count];
		}
		y++;
	}
	if (count == 21)
		count = -1;
	count++;
}
