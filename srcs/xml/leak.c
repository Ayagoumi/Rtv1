/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leak.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayagoumi <ayagoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 14:58:04 by yoouali           #+#    #+#             */
/*   Updated: 2021/03/06 12:32:07 by ayagoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/xml.h"

void	free_structer_light(t_light *light)
{
	t_light	*tmp;

	while (light)
	{
		tmp = light;
		light = light->next;
		free(tmp);
	}
}

void	free_structer_object(t_object *object)
{
	t_object	*tmp;

	while (object)
	{
		tmp = object;
		object = object->next;
		free(tmp);
	}
}

t_scene	*free_structer(t_scene *scene)
{
	if (scene->camera)
		free(scene->camera);
	if (scene->light)
		free_structer_light(scene->light);
	if (scene->object)
		free_structer_object(scene->object);
	return (NULL);
}
