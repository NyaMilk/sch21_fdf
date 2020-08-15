/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslave <jslave@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 21:26:52 by jslave            #+#    #+#             */
/*   Updated: 2019/11/19 18:04:34 by jslave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		x_rotate(int *y, int *z, t_fdf *fdf)
{
	int		prev_y;

	prev_y = *y;
	*y = (prev_y - HEIGHT / 2) * cos(fdf->x_rotate) + *z * sin(fdf->x_rotate);
	*y += HEIGHT / 2;
	*z = (-prev_y + HEIGHT / 2) * sin(fdf->x_rotate) + *z * cos(fdf->x_rotate);
}

void		y_rotate(int *x, int *z, t_fdf *fdf)
{
	int		prev_x;

	prev_x = *x;
	*x = (prev_x - WIDTH / 2) * cos(fdf->y_rotate) + *z * sin(fdf->y_rotate);
	*x += WIDTH / 2;
	*z = (-prev_x + WIDTH / 2) * sin(fdf->y_rotate) + *z * cos(fdf->y_rotate);
}

void		iso(int *x, int *y, int *z)
{
	int		prev_x;
	int		prev_y;

	prev_x = *x;
	prev_y = *y;
	*x = (prev_x - prev_y) * cos(0.523599);
	*y = -*z + (prev_x + prev_y) * sin(0.523599);
	*x += WIDTH / 2 - MENU_WIDTH;
	*y -= HEIGHT / 5;
}

void		change_points(int *x, int *y, int *z, t_fdf *fdf)
{
	x_rotate(y, z, fdf);
	y_rotate(x, z, fdf);
	if (fdf->projection == 'i')
		iso(x, y, z);
	*x += fdf->x_offset;
	*y += fdf->y_offset;
}
