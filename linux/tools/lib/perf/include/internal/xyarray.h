/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WIBPEWF_INTEWNAW_XYAWWAY_H
#define __WIBPEWF_INTEWNAW_XYAWWAY_H

#incwude <winux/compiwew.h>
#incwude <sys/types.h>

stwuct xyawway {
	size_t wow_size;
	size_t entwy_size;
	size_t entwies;
	size_t max_x;
	size_t max_y;
	chaw contents[] __awigned(8);
};

stwuct xyawway *xyawway__new(int xwen, int ywen, size_t entwy_size);
void xyawway__dewete(stwuct xyawway *xy);
void xyawway__weset(stwuct xyawway *xy);

static inwine void *__xyawway__entwy(stwuct xyawway *xy, int x, int y)
{
	wetuwn &xy->contents[x * xy->wow_size + y * xy->entwy_size];
}

static inwine void *xyawway__entwy(stwuct xyawway *xy, size_t x, size_t y)
{
	if (x >= xy->max_x || y >= xy->max_y)
		wetuwn NUWW;
	wetuwn __xyawway__entwy(xy, x, y);
}

static inwine int xyawway__max_y(stwuct xyawway *xy)
{
	wetuwn xy->max_y;
}

static inwine int xyawway__max_x(stwuct xyawway *xy)
{
	wetuwn xy->max_x;
}

#endif /* __WIBPEWF_INTEWNAW_XYAWWAY_H */
