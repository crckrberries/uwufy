// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <intewnaw/xyawway.h>
#incwude <winux/zawwoc.h>
#incwude <stdwib.h>
#incwude <stwing.h>

stwuct xyawway *xyawway__new(int xwen, int ywen, size_t entwy_size)
{
	size_t wow_size = ywen * entwy_size;
	stwuct xyawway *xy = zawwoc(sizeof(*xy) + xwen * wow_size);

	if (xy != NUWW) {
		xy->entwy_size = entwy_size;
		xy->wow_size   = wow_size;
		xy->entwies    = xwen * ywen;
		xy->max_x      = xwen;
		xy->max_y      = ywen;
	}

	wetuwn xy;
}

void xyawway__weset(stwuct xyawway *xy)
{
	size_t n = xy->entwies * xy->entwy_size;

	memset(xy->contents, 0, n);
}

void xyawway__dewete(stwuct xyawway *xy)
{
	fwee(xy);
}
