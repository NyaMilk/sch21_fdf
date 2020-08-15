/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrass <mgrass@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 21:26:26 by jslave            #+#    #+#             */
/*   Updated: 2019/11/19 17:31:39 by mgrass           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	check_rotates(int keycode, t_fdf *fdf)
{
	erase_img(fdf);
	if (keycode == KEY_NUM6)
		fdf->x_rotate += (0.1);
	if (keycode == KEY_NUM4)
		fdf->x_rotate -= (0.1);
	if (keycode == KEY_NUM8)
		fdf->y_rotate += (0.1);
	if (keycode == KEY_NUM2)
		fdf->y_rotate -= (0.1);
	draw_all(fdf);
}

void	check_change_size(int keycode, t_fdf *fdf)
{
	erase_img(fdf);
	if (keycode == KEY_NUM_P)
		fdf->resize += 0.1;
	if (keycode == KEY_NUM_M && fdf->resize - 0.1 >= 0.1)
		fdf->resize -= 0.1;
	if (keycode == KEY_NUM7)
		fdf->z_coeff += 20;
	else if (keycode == KEY_NUM9)
		fdf->z_coeff -= 20;
	draw_all(fdf);
	fdf->z_coeff = 0;
}

void	check_offset_and_projection(int keycode, t_fdf *fdf)
{
	erase_img(fdf);
	if (keycode == KEY_RIGHT)
		fdf->x_offset += (fdf->cols / 10);
	if (keycode == KEY_DOWN)
		fdf->y_offset += (fdf->rows / 10);
	if (keycode == KEY_LEFT)
		fdf->x_offset -= (fdf->cols / 10);
	if (keycode == KEY_UP)
		fdf->y_offset -= (fdf->rows / 10);
	if (keycode == KEY_NUM5)
	{
		if (fdf->projection == 'i')
		{
			fdf->projection = 'n';
			fdf->x_rotate = 0;
			fdf->y_rotate = 0;
		}
		else if (fdf->projection != 'i')
		{
			fdf->x_rotate = 0;
			fdf->y_rotate = 0;
			fdf->projection = 'i';
		}
	}
	draw_all(fdf);
}

void	check_restore_and_color(int keycode, t_fdf *fdf)
{
	erase_img(fdf);
	if (keycode == KEY_AST)
	{
		fdf->x_offset = 0;
		fdf->y_offset = 0;
		fdf->x_rotate = 0;
		fdf->y_rotate = 0;
		fdf->z_coeff = 0;
		fdf->resize = 1;
		fdf->step = find_step(fdf);
		fdf->x_start = ((WIDTH - (fdf->cols * fdf->step) + MENU_WIDTH) / 2);
		fdf->y_start = ((HEIGHT - (fdf->rows * fdf->step)) / 2);
	}
	if (keycode == KEY_NUM0)
		change_color(fdf);
	draw_all(fdf);
}

int		key_press(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_image(fdf->mlx_ptr, fdf->img_ptr);
		free_fdf(fdf);
		exit(0);
	}
	check_rotates(keycode, fdf);
	check_offset_and_projection(keycode, fdf);
	check_change_size(keycode, fdf);
	check_restore_and_color(keycode, fdf);
	return (0);
}
