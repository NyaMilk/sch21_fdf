/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslave <jslave@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 21:38:33 by jslave            #+#    #+#             */
/*   Updated: 2019/11/19 17:59:59 by jslave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		erase_img(t_fdf *fdf)
{
	int i;

	i = 0;
	while (i != (WIDTH * HEIGHT) - 1)
	{
		(fdf->img_data)[i] = 0x272727;
		i++;
	}
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, 0, 0);
}

t_bres		*create_offset_data(char type, int x_st, int y_st, t_fdf *fdf)
{
	t_bres *data;

	data = ft_memalloc(sizeof(t_bres));
	data->x_start = x_st;
	data->y_start = y_st;
	data->x_end = x_st;
	data->y_end = y_st;
	if (type == 'x')
		data->x_end += fdf->step * fdf->resize;
	else if (type == 'y')
		data->y_end += fdf->step * fdf->resize;
	data->color_st = 0;
	data->color_end = 0;
	return (data);
}

void		create_data_and_draw_x(t_fdf *fdf)
{
	int		p[2];
	int		st[2];
	t_bres	*data;

	st[0] = fdf->x_start;
	st[1] = fdf->y_start;
	p[1] = -1;
	while (++p[1] < fdf->rows)
	{
		p[0] = -1;
		while (++p[0] < fdf->cols)
		{
			if (p[1] + 1 < fdf->rows)
			{
				data = create_offset_data('y', st[0], st[1], fdf);
				add_col_z1(p[1], p[0], data, fdf);
				make_line(data, fdf);
			}
			st[0] += fdf->step * fdf->resize;
		}
		st[0] = fdf->x_start;
		st[1] += fdf->step * fdf->resize;
	}
}

/*
** p[0] - x;p[1] = y;st[0] - x; st[1] -y;
*/

void		create_data_and_draw_y(t_fdf *fdf)
{
	int		p[2];
	int		st[2];
	t_bres	*data;

	st[0] = fdf->x_start;
	st[1] = fdf->y_start;
	p[1] = -1;
	while (++p[1] < fdf->rows)
	{
		p[0] = -1;
		while (++p[0] < fdf->cols)
		{
			if (p[0] + 1 < fdf->cols)
			{
				data = create_offset_data('x', st[0], st[1], fdf);
				add_col_z2(p[1], p[0], data, fdf);
				make_line(data, fdf);
			}
			st[0] += fdf->step * fdf->resize;
		}
		st[0] = fdf->x_start;
		st[1] += fdf->step * fdf->resize;
	}
}

void		draw_all(t_fdf *fdf)
{
	draw_background(fdf);
	create_data_and_draw_x(fdf);
	create_data_and_draw_y(fdf);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, 0, 0);
	print_menu(fdf);
}
