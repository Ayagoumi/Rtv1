/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoouali <yoouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 12:07:03 by ayagoumi          #+#    #+#             */
/*   Updated: 2021/03/13 18:37:00 by yoouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

t_object	*raycast_object(t_ray r, t_hsno *hsno, t_scene *scene)
{
	t_object	*object;
	t_object	*tmp;
	double		het;

	object = scene->object;
	if (!object)
		return (NULL);
	hsno->hit = calc_intersect(r, object);
	tmp = object->next;
	while (tmp)
	{
		het = calc_intersect(r, tmp);
		if (het >= 0.0001 && (het < hsno->hit || hsno->hit == -1))
		{
			hsno->hit = het;
			object = tmp;
		}
		tmp = tmp->next;
	}
	if (hsno->hit < 0.0001)
		return (NULL);
	calc_surface_normal(r, object, hsno);
	return (object);
}

void		trace(t_rtv1 *rtv, t_hsno *hsno, t_scene *scene, t_pixel pixel)
{
	if (hsno->object)
	{
		if (scene->light)
			rtv->data[(WIDTH * pixel.j) + pixel.i] =\
				ft_get_full_color(hsno, scene, &(hsno->r));
		else
			rtv->data[(WIDTH * pixel.j) + pixel.i] =\
				rgb_to_int(hsno->object->color);
	}
	else
		rtv->data[(WIDTH * pixel.j) + pixel.i] = 0;
}

t_vec3		int_to_rgb(int color)
{
	t_vec3	rgb;

	rgb.x = (color >> 16) & 255;
	rgb.y = (color >> 8) & 255;
	rgb.z = color & 255;
	return (rgb);
}

int			*color_tableu(void)
{
	int	*tab;

	tab = (int *)malloc(sizeof(int) * 50);
	tab[0] = 0xC0392B;
	tab[1] = 0x922B21;
	tab[2] = 0x641E16;
	tab[3] = 0x9B59B6;
	tab[4] = 0x6C3483;
	tab[5] = 0x4A235A;
	tab[6] = 0x3498DB;
	tab[7] = 0x2874A6;
	tab[8] = 0x1B4F72;	
	tab[9] = 0x16A085;
	tab[10] = 0x117A65;
	tab[11] = 0x0E6251;
	tab[12] = 0x2ECC71;
	tab[13] = 0x239B56;
	tab[14] = 0x186A3B;
	tab[15] = 0xF1C40F;
	tab[16] = 0xB7950B;
	tab[17] = 0x7D6608;
	tab[18] = 0xF39C12;
	tab[19] = 0xB9770E;
	tab[20] = 0x7E5109;
	tab[21] = 0xD35400;
	tab[22] = 0xA04000;
	tab[23] = 0x6E2C00;
	tab[24] = 0xECF0F1;
	tab[25] = 0xB3B6B7;
	tab[26] = 0x7B7D7D;
	tab[27] = 0x95A5A6;
	tab[28] = 0x717D7E;
	tab[29] = 0x4D5656;	
	return (tab);
}

void		blur_box_effect(t_rtv1 *rtv, int *data)
{
	printf("start bluring\n");
	t_pixel	pixel;
	t_vec3		sum;
	t_vec3		col;
	int			cont = 0;


	pixel.i = -1;
	while (++pixel.i < WIDTH)
	{
		pixel.j = -1;
		while (++pixel.j < HEIGHT)
		{
			cont = 1;
			sum  = int_to_rgb(rtv->data[(WIDTH * pixel.j) + pixel.i]);
			while (cont < 30)
			{
				if (pixel.i + cont < WIDTH)
					col = int_to_rgb(rtv->data[(WIDTH * pixel.j) + pixel.i + cont]);
				sum = plus(sum, col); 
				cont++;
			}
			sum = divide(sum, 30.0);
			data[(WIDTH * pixel.j)+ pixel.i] = rgb_to_int(sum);
			rtv->data[(WIDTH * pixel.j)+ pixel.i] = data[(WIDTH * pixel.j)+ pixel.i];
			//printf("i : %d | j : %d", pixel.i, pixel.j);
		}
	}
	/*pixel.i = -1;
	while (++pixel.i < WIDTH)
	{
		pixel.j = -1;
		while (++pixel.j < HEIGHT)
		{
			rtv->data[(WIDTH * pixel.j) + pixel.i] = data[(WIDTH * pixel.j) + pixel.i];
			//printf("i : %d | j : %d", pixel.i, pixel.j);
		}
	}*/
}

void		color_defference_effect(t_rtv1	*rtv)
{
	t_pixel	pixel;
	int	*tab = color_tableu();
	t_vec3	col;
	t_vec3	col2;
	int		distance;
	int		dis;
	int		save;

	pixel.i = 0;
	while (pixel.i < WIDTH * HEIGHT)
	{
		pixel.j = 0;
		col = int_to_rgb(rtv->data[pixel.i]);
		save = 0;
		distance = INFINITY;
		while (pixel.j < 30)
		{
			col2 = int_to_rgb(tab[pixel.j]);
			//printf("the color %d: R : %d| B : %d| G : %d\n", pixel.j, (int)tab[pixel.j].x, (int)tab[pixel.j].y, (int)tab[pixel.j].z);
			//dis = (col.x - col2.x) * (col.x - col2.x) + (col.y - col2.y) * (col.y - col2.y) + (col.z - col2.z) * (col.z - col2.z);
			dis = pow(col.x - col2.x, 2) + pow(col.y - col2.y, 2) + pow(col.z - col2.z, 2);
			dis = sqrt(dis);
			if (dis < distance)
			{
				distance = dis;
				save = pixel.j;
			}
			pixel.j++;
		}
		rtv->data[pixel.i] = tab[save];
		pixel.i++;
	}

}

void		ft_cast_rays(t_rtv1 *rtv, t_scene *scene)
{
	t_pixel	pixel;
	t_hsno	hsno;
	t_point	p;
	//int		*data;
	double	u;
	double	v;

	declare_camera(&hsno.r, scene, &hsno, &p);
	pixel.i = 0;
	while (pixel.i < WIDTH)
	{
		pixel.j = 0;
		while (pixel.j < HEIGHT)
		{
			u = map(pixel.i, WIDTH, -1, 1) * p.y;
			v = map(pixel.j, HEIGHT, 1, -1) * p.x;
			hsno.r.dir = plus(hsno.wv, plus(mult2(v, hsno.vv),\
				mult2(u, hsno.uv)));
			hsno.r.dir = normalize(hsno.r.dir);
			hsno.object = raycast_object(hsno.r, &hsno, scene);
			trace(rtv, &hsno, scene, pixel);
			pixel.j++;
		}
		pixel.i++;
	}
	printf("finish raycasting\n");
	//data = (int *)malloc(sizeof(int) * (WIDTH * HEIGHT));
	//blur_box_effect(rtv, data);
	color_defference_effect(rtv);
	printf("finidh bluring\n");
}
