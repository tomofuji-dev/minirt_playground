/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shape.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:01:53 by tfujiwar          #+#    #+#             */
/*   Updated: 2023/01/20 17:25:25 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "init.h"
#include "utils.h"
#include "color.h"

bool		init_sphere(t_scene *scene, char ***splited);
bool		init_plane(t_scene *scene, char ***splited);
bool		init_cylinder(t_scene *scene, char ***splited);
static void	default_material(t_material *material);

bool	init_sphere(t_scene *scene, char ***splited)
{
	const size_t	tp_len = 4;
	const size_t	dp_lens[4] = {1, 3, 1, 3};
	t_shape			*shape;
	t_sphere		*sph;
	t_rgb			rgb;

	if (!is_valid_format(splited, tp_len, dp_lens))
		return (false);
	if (!append_shape(scene))
		return (false);
	shape = lst_last_shape(scene->shape);
	sph = &shape->u_data.sphere;
	if (!is_valid_vec(splited[1], &sph->center, false))
		return (false);
	if (!rt_strtod(splited[2][0], &sph->radius))
		return (false);
	if (!is_valid_rgb(splited[3], &rgb))
		return (false);
	shape->material.diffuse_ref = calc_rgb_ratio(rgb, 1.0);
	default_material(&shape->material);
	return (true);
}

bool	init_plane(t_scene *scene, char ***splited)
{
	const size_t	tp_len = 4;
	const size_t	dp_lens[4] = {1, 3, 3, 3};
	t_shape			*shape;
	t_plane			*pl;
	t_rgb			rgb;

	if (!is_valid_format(splited, tp_len, dp_lens))
		return (false);
	if (!append_shape(scene))
		return (false);
	shape = lst_last_shape(scene->shape);
	pl = &shape->u_data.plane;
	if (!is_valid_vec(splited[1], &pl->position, false))
		return (false);
	if (!is_valid_vec(splited[2], &pl->normal, true))
		return (false);
	if (!is_valid_rgb(splited[3], &rgb))
		return (false);
	shape->material.diffuse_ref = calc_rgb_ratio(rgb, 1.0);
	default_material(&shape->material);
	return (true);
}

bool	init_cylinder(t_scene *scene, char ***splited)
{
	const size_t	tp_len = 6;
	const size_t	dp_lens[6] = {1, 3, 3, 1, 1, 3};
	t_shape			*shape;
	t_cylinder		*cy;
	t_rgb			rgb;

	if (!is_valid_format(splited, tp_len, dp_lens))
		return (false);
	if (!append_shape(scene))
		return (false);
	shape = lst_last_shape(scene->shape);
	cy = &shape->u_data.cylinder;
	if (!is_valid_vec(splited[1], &cy->position, false))
		return (false);
	if (!is_valid_vec(splited[2], &cy->direction, true))
		return (false);
	if (!rt_strtod(splited[3][0], &cy->radius))
		return (false);
	if (!rt_strtod(splited[4][0], &cy->height))
		return (false);
	if (!is_valid_rgb(splited[5], &rgb))
		return (false);
	shape->material.diffuse_ref = calc_rgb_ratio(rgb, 1.0);
	default_material(&shape->material);
	return (true);
}

static void	default_material(t_material *material)
{
	set_trgb(&material->ambient_ref, 0.01, 0.01, 0.01);
	set_trgb(&material->specular_ref, 0.3, 0.3, 0.3);
	material->shininess = 8.0;
	return ;
}