/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagoumi <ayagoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:05:37 by ayagoumi          #+#    #+#             */
/*   Updated: 2021/03/07 10:25:41 by ayagoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "../libft/libft.h"
# include "mlx.h"
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include "../SDL/SDL2.framework/Headers/SDL.h"
# include "../SDL/SDL2_ttf.framework/Headers/SDL_ttf.h"
# include "../SDL/SDL2_image.framework/Headers/SDL_image.h"
# define WIDTH 1000
# define HEIGHT 1000
# include "raycast.h"
# include "functions.h"
# include "xml.h"
# include "window.h"

int					sdl_init_texture(t_rtv1	*rtv);
int					sdl_init_render(t_rtv1 *rtv);
int					sdl_init_win(t_rtv1	*rtv);
void				sdl_quit(t_rtv1 *rtv);
void				process_input(t_rtv1 *rtv, t_scene *scene);
double				map(int position, int max_wh, double new_min_scope
					, double new_max_scope);
void				cast_rays(t_rtv1 *rtv, char *file);
double				vec_length(t_vec3 vec);
t_vec3				plus(t_vec3 a, t_vec3 b);
t_vec3				minus(t_vec3 a, t_vec3 b);
t_vec3				mult(t_vec3 a, t_vec3 b);
t_vec3				mult2(double t, t_vec3 b);
t_vec3				divide(t_vec3 b, double t);
double				dot(t_vec3 a, t_vec3 b);
t_vec3				cross(t_vec3 a, t_vec3 b);
t_vec3				normalize(t_vec3 vec);
void				ft_cast_rays(t_rtv1 *rtv, t_scene *scene);
t_object			*raycast_object(t_ray r, t_hsno *hsno, t_scene *scene);
double				calc_intersect(t_ray r, t_object *object);
double				intersect_cone(t_ray r, t_object *cone);
double				intersect_cylinder(t_ray r, t_object *cylinder);
double				intersect_plane(t_ray r, t_object *plane);
double				intersect_sphere(t_ray r, t_object *sphere);
int					ft_get_full_color(t_hsno *hsno, t_scene *scene, t_ray *ray);
double				ft_get_specular(t_hsno *hsno, t_light *light);
double				ft_get_diffuse(t_hsno *hsno, t_light *light);
void				calc_surface_normal2(t_ray r,\
					t_object *object, t_hsno *hsno);
void				calc_surface_normal(t_ray r,\
					t_object *object, t_hsno *hsno);
t_vec3				get_ambiant(t_hsno *hsno);
double				ft_get_diffuse(t_hsno *hsno, t_light *light);
double				ft_get_specular(t_hsno *hsno, t_light *light);
int					shadow(t_ray *r, t_hsno *hsno,
					t_light *l, t_object *objects);
int					rgb_to_int(t_vec3 rgb);
void				declare_camera(t_ray *r, t_scene *scene,\
					t_hsno *hsno, t_point *p);
void				calc_surface_normal(t_ray r, t_object\
					*object, t_hsno *hsno);
void				calc_surface_normal2(t_ray r, t_object\
					*object, t_hsno *hsno);
void				process_input(t_rtv1 *rtv, t_scene *scene);
double				map(int position, int max_wh, double new_min_scope
		, double new_max_scope);
void				cast_rays(t_rtv1 *rtv, char *file);
double				vec_length(t_vec3 vec);
t_vec3				plus(t_vec3 a, t_vec3 b);
t_vec3				minus(t_vec3 a, t_vec3 b);
t_vec3				mult(t_vec3 a, t_vec3 b);
t_vec3				mult2(double t, t_vec3 b);
t_vec3				divide(t_vec3 b, double t);
double				dot(t_vec3 a, t_vec3 b);
t_vec3				cross(t_vec3 a, t_vec3 b);
t_vec3				normalize(t_vec3 vec);
void				ft_cast_rays(t_rtv1 *rtv, t_scene *scene);
t_object			*raycast_object(t_ray r, t_hsno *hsno, t_scene *scene);
double				calc_intersect(t_ray r, t_object *object);
double				intersect_cone(t_ray r, t_object *cone);
double				intersect_cylinder(t_ray r, t_object *cylinder);
double				intersect_plane(t_ray r, t_object *plane);
double				intersect_sphere(t_ray r, t_object *sphere);
int					ft_get_full_color(t_hsno *hsno, t_scene *scene, t_ray *ray);
double				ft_get_specular(t_hsno *hsno, t_light *light);
double				ft_get_diffuse(t_hsno *hsno, t_light *light);
void				calc_surface_normal2(t_ray r, t_object *object,\
		t_hsno *hsno);
void				calc_surface_normal(t_ray r, t_object *object,\
		t_hsno *hsno);
t_vec3				get_ambiant(t_hsno *hsno);
double				ft_get_diffuse(t_hsno *hsno, t_light *light);
double				ft_get_specular(t_hsno *hsno, t_light *light);
int					shadow(t_ray *r, t_hsno *hsno, t_light *l,\
		t_object *objects);
int					rgb_to_int(t_vec3 rgb);
void				declare_camera(t_ray *r, t_scene *scene,\
		t_hsno *hsno, t_point *p);
void				calc_surface_normal(t_ray r, t_object *object,\
		t_hsno *hsno);
void				calc_surface_normal2(t_ray r, t_object *object,\
		t_hsno *hsno);

#endif
