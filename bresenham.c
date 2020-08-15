/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslave <jslave@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 21:56:55 by jslave            #+#    #+#             */
/*   Updated: 2019/11/19 16:44:34 by jslave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		draw(int x, int y, t_bres *dt, t_fdf *fdf)
{
	if (x > MENU_WIDTH && x < WIDTH && y > 0 && y < HEIGHT)
		fdf->img_data[y * WIDTH + x] = get_color(x, y, dt);
}

void		draw_dy(t_bres *dt, t_fdf *fdf)
{
	int x;
	int y;
	int ye;

	x = dt->x_end;
	y = dt->y_end;
	ye = ((dt->dy) >= 0) ? dt->y_end : dt->y_start;
	if (dt->dy >= 0)
	{
		x = dt->x_start;
		y = dt->y_start;
	}
	draw(x, y, dt, fdf);
	while (++y < ye)
	{
		if (dt->py <= 0)
			dt->py = dt->py + 2 * dt->dx1;
		else
		{
			((dt->dx < 0 && dt->dy < 0) || \
			(dt->dx > 0 && dt->dy > 0)) ? (x++) : (x--);
			dt->py = dt->py + 2 * (dt->dx1 - dt->dy1);
		}
		draw(x, y, dt, fdf);
	}
}

void		draw_dx(t_bres *dt, t_fdf *fdf)
{
	int x;
	int y;
	int xe;

	x = dt->x_end;
	y = dt->y_end;
	if (dt->dx >= 0)
	{
		x = dt->x_start;
		y = dt->y_start;
	}
	xe = ((dt->dx) >= 0) ? dt->x_end : dt->x_start;
	draw(x, y, dt, fdf);
	while (++x < xe)
	{
		if (dt->px <= 0)
			dt->px = dt->px + 2 * dt->dy1;
		else
		{
			((dt->dx < 0 && dt->dy < 0) || \
			(dt->dx > 0 && dt->dy > 0)) ? (y++) : (y--);
			dt->px = dt->px + 2 * (dt->dy1 - dt->dx1);
		}
		draw(x, y, dt, fdf);
	}
}

void		make_line(t_bres *dt, t_fdf *fdf)
{
	change_points(&dt->x_start, &dt->y_start, &dt->z_start, fdf);
	change_points(&dt->x_end, &dt->y_end, &dt->z_end, fdf);
	dt->dx = dt->x_end - dt->x_start;
	dt->dy = dt->y_end - dt->y_start;
	dt->dx1 = abs(dt->dx);
	dt->dy1 = abs(dt->dy);
	dt->px = 2 * dt->dy1 - dt->dx1;
	dt->py = 2 * dt->dx1 - dt->dy1;
	if (dt->dy1 <= dt->dx1)
		draw_dx(dt, fdf);
	else
		draw_dy(dt, fdf);
	free(dt);
}
