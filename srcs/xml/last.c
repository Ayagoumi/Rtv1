/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoouali <yoouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 14:46:56 by yoouali           #+#    #+#             */
/*   Updated: 2021/03/04 14:57:47 by yoouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/xml.h"

void	vectorse_rotation(t_object *o)
{
	t_vec3		vec;
	double		alpha;

	alpha = o->rotation.x * (M_PI / 180.0);
	vec.x = o->orientation.x;
	vec.y = o->orientation.y * cos(alpha) + o->orientation.z * sin(alpha);
	vec.z = -o->orientation.y * sin(alpha) + o->orientation.z * cos(alpha);
	o->orientation = vec;
	alpha = o->rotation.y * (M_PI / 180.0);
	vec.y = o->orientation.y;
	vec.x = o->orientation.x * cos(alpha) + o->orientation.z * sin(alpha);
	vec.z = -o->orientation.x * sin(alpha) + o->orientation.z * cos(alpha);
	o->orientation = vec;
	alpha = o->rotation.z * (M_PI / 180.0);
	vec.z = o->orientation.z;
	vec.x = o->orientation.x * cos(alpha) - o->orientation.y * sin(alpha);
	vec.y = o->orientation.x * sin(alpha) + o->orientation.y * cos(alpha);
	o->orientation = vec;
}

int		check_object_structer(t_object *object)
{
	t_object	*tmp;

	tmp = object;
	while (tmp)
	{
		if (tmp->tab[0] == 0 || tmp->tab[1] == 0 || tmp->tab[5]\
				== 0 || tmp->tab[4] == 0 || tmp->tab[6] == 0)
			return (0);
		if (tmp->tab[2] == 1)
			tmp->position = plus(tmp->position, tmp->translation);
		if (tmp->tab[3] == 1)
			vectorse_rotation(tmp);
		tmp = tmp->next;
	}
	return (1);
}

int		check_light_structer(t_light *light)
{
	t_light		*tmp;

	tmp = light;
	while (tmp)
	{
		if (tmp->tab[0] == 0 || tmp->tab[1] == 0 || tmp->tab[2] == 0)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int		structer_check(t_xmlpar xmlpar)
{
	t_camera	*camera;
	t_light		*light;

	if (!xmlpar.scene->camera)
		return (0);
	camera = xmlpar.scene->camera;
	light = xmlpar.scene->light;
	if (camera->tab[0] == 0 || camera->tab[1] == 0 || camera->tab[2] == 0)
		return (0);
	if (xmlpar.scene->light)
		if (!check_light_structer(xmlpar.scene->light))
			return (0);
	if (xmlpar.scene->object)
		if (!check_object_structer(xmlpar.scene->object))
			return (0);
	return (1);
}
