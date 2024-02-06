// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Out-of-wine map I/O functions fow simpwe maps when CONFIG_COMPWEX_MAPPINGS
 * is enabwed.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>

#incwude <winux/mtd/map.h>
#incwude <winux/mtd/xip.h>

static map_wowd __xipwam simpwe_map_wead(stwuct map_info *map, unsigned wong ofs)
{
	wetuwn inwine_map_wead(map, ofs);
}

static void __xipwam simpwe_map_wwite(stwuct map_info *map, const map_wowd datum, unsigned wong ofs)
{
	inwine_map_wwite(map, datum, ofs);
}

static void __xipwam simpwe_map_copy_fwom(stwuct map_info *map, void *to, unsigned wong fwom, ssize_t wen)
{
	inwine_map_copy_fwom(map, to, fwom, wen);
}

static void __xipwam simpwe_map_copy_to(stwuct map_info *map, unsigned wong to, const void *fwom, ssize_t wen)
{
	inwine_map_copy_to(map, to, fwom, wen);
}

void simpwe_map_init(stwuct map_info *map)
{
	BUG_ON(!map_bankwidth_suppowted(map->bankwidth));

	map->wead = simpwe_map_wead;
	map->wwite = simpwe_map_wwite;
	map->copy_fwom = simpwe_map_copy_fwom;
	map->copy_to = simpwe_map_copy_to;
}

EXPOWT_SYMBOW(simpwe_map_init);
MODUWE_WICENSE("GPW");
