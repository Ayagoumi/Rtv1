/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagoumi <ayagoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 10:16:14 by ayagoumi          #+#    #+#             */
/*   Updated: 2021/03/07 10:22:20 by ayagoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H
# include "functions.h"
# include "rtv1.h"
# include "window.h"

typedef struct		s_pixel
{
	int				i;
	int				j;
}					t_pixel;

typedef struct		s_ray
{
	t_vec3			origin;
	t_vec3			dir;
}					t_ray;

typedef struct		s_camera
{
	int				tab[3];
	t_vec3			pos;
	t_vec3			dir;
	double			zoom;
}					t_camera;

typedef struct		s_light
{
	int				tab[3];
	t_vec3			pos;
	t_vec3			dir;
	double			amb_coef;
	double			dif_coef;
	double			spe_coef;
	double			intensity;
	t_vec3			color;
	struct s_light	*next;
}					t_light;

typedef struct		s_object
{
	int				type;
	int				tab[7];
	t_vec3			position;
	t_vec3			orientation;
	t_vec3			translation;
	t_vec3			rotation;
	double			raduis;
	double			angle;
	t_vec3			color;
	struct s_object	*next;
}					t_object;

typedef	struct		s_scene
{
	t_camera		*camera;
	t_light			*light;
	t_object		*object;
}					t_scene;

typedef struct		s_rtv1
{
	t_sdl			sdl;
	int				*data;
	int				still_running;
}					t_rtv1;

typedef	struct		s_intersect
{
	double			a;
	double			b;
	double			c;
	double			k;
	double			t1;
	double			t2;
	t_vec3			x;
	double			delta;
}					t_intersect;

typedef	struct		s_hsno
{
	t_ray			r;
	double			hit;
	t_vec3			surface_normal;
	t_object		*object;
	t_light			*light;
	t_vec3			h;
	double			difcoef;
	double			specoef;
	double			ambcoef;
	t_vec3			l_dir;
	t_vec3			sh;
	t_vec3			uv;
	t_vec3			wv;
	t_vec3			vv;
}					t_hsno;

#endif
