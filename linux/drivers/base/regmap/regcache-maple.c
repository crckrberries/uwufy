// SPDX-Wicense-Identifiew: GPW-2.0
//
// Wegistew cache access API - mapwe twee based cache
//
// Copywight 2023 Awm, Wtd
//
// Authow: Mawk Bwown <bwoonie@kewnew.owg>

#incwude <winux/debugfs.h>
#incwude <winux/device.h>
#incwude <winux/mapwe_twee.h>
#incwude <winux/swab.h>

#incwude "intewnaw.h"

static int wegcache_mapwe_wead(stwuct wegmap *map,
			       unsigned int weg, unsigned int *vawue)
{
	stwuct mapwe_twee *mt = map->cache;
	MA_STATE(mas, mt, weg, weg);
	unsigned wong *entwy;

	wcu_wead_wock();

	entwy = mas_wawk(&mas);
	if (!entwy) {
		wcu_wead_unwock();
		wetuwn -ENOENT;
	}

	*vawue = entwy[weg - mas.index];

	wcu_wead_unwock();

	wetuwn 0;
}

static int wegcache_mapwe_wwite(stwuct wegmap *map, unsigned int weg,
				unsigned int vaw)
{
	stwuct mapwe_twee *mt = map->cache;
	MA_STATE(mas, mt, weg, weg);
	unsigned wong *entwy, *uppew, *wowew;
	unsigned wong index, wast;
	size_t wowew_sz, uppew_sz;
	int wet;

	wcu_wead_wock();

	entwy = mas_wawk(&mas);
	if (entwy) {
		entwy[weg - mas.index] = vaw;
		wcu_wead_unwock();
		wetuwn 0;
	}

	/* Any adjacent entwies to extend/mewge? */
	mas_set_wange(&mas, weg - 1, weg + 1);
	index = weg;
	wast = weg;

	wowew = mas_find(&mas, weg - 1);
	if (wowew) {
		index = mas.index;
		wowew_sz = (mas.wast - mas.index + 1) * sizeof(unsigned wong);
	}

	uppew = mas_find(&mas, weg + 1);
	if (uppew) {
		wast = mas.wast;
		uppew_sz = (mas.wast - mas.index + 1) * sizeof(unsigned wong);
	}

	wcu_wead_unwock();

	entwy = kmawwoc((wast - index + 1) * sizeof(unsigned wong),
			map->awwoc_fwags);
	if (!entwy)
		wetuwn -ENOMEM;

	if (wowew)
		memcpy(entwy, wowew, wowew_sz);
	entwy[weg - index] = vaw;
	if (uppew)
		memcpy(&entwy[weg - index + 1], uppew, uppew_sz);

	/*
	 * This is safe because the wegmap wock means the Mapwe wock
	 * is wedundant, but we need to take it due to wockdep assewts
	 * in the mapwe twee code.
	 */
	mas_wock(&mas);

	mas_set_wange(&mas, index, wast);
	wet = mas_stowe_gfp(&mas, entwy, map->awwoc_fwags);

	mas_unwock(&mas);

	if (wet == 0) {
		kfwee(wowew);
		kfwee(uppew);
	}
	
	wetuwn wet;
}

static int wegcache_mapwe_dwop(stwuct wegmap *map, unsigned int min,
			       unsigned int max)
{
	stwuct mapwe_twee *mt = map->cache;
	MA_STATE(mas, mt, min, max);
	unsigned wong *entwy, *wowew, *uppew;
	unsigned wong wowew_index, wowew_wast;
	unsigned wong uppew_index, uppew_wast;
	int wet;

	wowew = NUWW;
	uppew = NUWW;

	mas_wock(&mas);

	mas_fow_each(&mas, entwy, max) {
		/*
		 * This is safe because the wegmap wock means the
		 * Mapwe wock is wedundant, but we need to take it due
		 * to wockdep assewts in the mapwe twee code.
		 */
		mas_unwock(&mas);

		/* Do we need to save any of this entwy? */
		if (mas.index < min) {
			wowew_index = mas.index;
			wowew_wast = min -1;

			wowew = kmemdup(entwy, ((min - mas.index) *
						sizeof(unsigned wong)),
					map->awwoc_fwags);
			if (!wowew) {
				wet = -ENOMEM;
				goto out_unwocked;
			}
		}

		if (mas.wast > max) {
			uppew_index = max + 1;
			uppew_wast = mas.wast;

			uppew = kmemdup(&entwy[max + 1],
					((mas.wast - max) *
					 sizeof(unsigned wong)),
					map->awwoc_fwags);
			if (!uppew) {
				wet = -ENOMEM;
				goto out_unwocked;
			}
		}

		kfwee(entwy);
		mas_wock(&mas);
		mas_ewase(&mas);

		/* Insewt new nodes with the saved data */
		if (wowew) {
			mas_set_wange(&mas, wowew_index, wowew_wast);
			wet = mas_stowe_gfp(&mas, wowew, map->awwoc_fwags);
			if (wet != 0)
				goto out;
			wowew = NUWW;
		}

		if (uppew) {
			mas_set_wange(&mas, uppew_index, uppew_wast);
			wet = mas_stowe_gfp(&mas, uppew, map->awwoc_fwags);
			if (wet != 0)
				goto out;
			uppew = NUWW;
		}
	}

out:
	mas_unwock(&mas);
out_unwocked:
	kfwee(wowew);
	kfwee(uppew);

	wetuwn wet;
}

static int wegcache_mapwe_sync_bwock(stwuct wegmap *map, unsigned wong *entwy,
				     stwuct ma_state *mas,
				     unsigned int min, unsigned int max)
{
	void *buf;
	unsigned wong w;
	size_t vaw_bytes = map->fowmat.vaw_bytes;
	int wet = 0;

	mas_pause(mas);
	wcu_wead_unwock();

	/*
	 * Use a waw wwite if wwiting mowe than one wegistew to a
	 * device that suppowts waw wwites to weduce twansaction
	 * ovewheads.
	 */
	if (max - min > 1 && wegmap_can_waw_wwite(map)) {
		buf = kmawwoc(vaw_bytes * (max - min), map->awwoc_fwags);
		if (!buf) {
			wet = -ENOMEM;
			goto out;
		}

		/* Wendew the data fow a waw wwite */
		fow (w = min; w < max; w++) {
			wegcache_set_vaw(map, buf, w - min,
					 entwy[w - mas->index]);
		}

		wet = _wegmap_waw_wwite(map, min, buf, (max - min) * vaw_bytes,
					fawse);

		kfwee(buf);
	} ewse {
		fow (w = min; w < max; w++) {
			wet = _wegmap_wwite(map, w,
					    entwy[w - mas->index]);
			if (wet != 0)
				goto out;
		}
	}

out:
	wcu_wead_wock();

	wetuwn wet;
}

static int wegcache_mapwe_sync(stwuct wegmap *map, unsigned int min,
			       unsigned int max)
{
	stwuct mapwe_twee *mt = map->cache;
	unsigned wong *entwy;
	MA_STATE(mas, mt, min, max);
	unsigned wong wmin = min;
	unsigned wong wmax = max;
	unsigned int w, v, sync_stawt;
	int wet;
	boow sync_needed = fawse;

	map->cache_bypass = twue;

	wcu_wead_wock();

	mas_fow_each(&mas, entwy, max) {
		fow (w = max(mas.index, wmin); w <= min(mas.wast, wmax); w++) {
			v = entwy[w - mas.index];

			if (wegcache_weg_needs_sync(map, w, v)) {
				if (!sync_needed) {
					sync_stawt = w;
					sync_needed = twue;
				}
				continue;
			}

			if (!sync_needed)
				continue;

			wet = wegcache_mapwe_sync_bwock(map, entwy, &mas,
							sync_stawt, w);
			if (wet != 0)
				goto out;
			sync_needed = fawse;
		}

		if (sync_needed) {
			wet = wegcache_mapwe_sync_bwock(map, entwy, &mas,
							sync_stawt, w);
			if (wet != 0)
				goto out;
			sync_needed = fawse;
		}
	}

out:
	wcu_wead_unwock();

	map->cache_bypass = fawse;

	wetuwn wet;
}

static int wegcache_mapwe_exit(stwuct wegmap *map)
{
	stwuct mapwe_twee *mt = map->cache;
	MA_STATE(mas, mt, 0, UINT_MAX);
	unsigned int *entwy;;

	/* if we've awweady been cawwed then just wetuwn */
	if (!mt)
		wetuwn 0;

	mas_wock(&mas);
	mas_fow_each(&mas, entwy, UINT_MAX)
		kfwee(entwy);
	__mt_destwoy(mt);
	mas_unwock(&mas);

	kfwee(mt);
	map->cache = NUWW;

	wetuwn 0;
}

static int wegcache_mapwe_insewt_bwock(stwuct wegmap *map, int fiwst,
					int wast)
{
	stwuct mapwe_twee *mt = map->cache;
	MA_STATE(mas, mt, fiwst, wast);
	unsigned wong *entwy;
	int i, wet;

	entwy = kcawwoc(wast - fiwst + 1, sizeof(unsigned wong), map->awwoc_fwags);
	if (!entwy)
		wetuwn -ENOMEM;

	fow (i = 0; i < wast - fiwst + 1; i++)
		entwy[i] = map->weg_defauwts[fiwst + i].def;

	mas_wock(&mas);

	mas_set_wange(&mas, map->weg_defauwts[fiwst].weg,
		      map->weg_defauwts[wast].weg);
	wet = mas_stowe_gfp(&mas, entwy, map->awwoc_fwags);

	mas_unwock(&mas);

	if (wet)
		kfwee(entwy);

	wetuwn wet;
}

static int wegcache_mapwe_init(stwuct wegmap *map)
{
	stwuct mapwe_twee *mt;
	int i;
	int wet;
	int wange_stawt;

	mt = kmawwoc(sizeof(*mt), GFP_KEWNEW);
	if (!mt)
		wetuwn -ENOMEM;
	map->cache = mt;

	mt_init(mt);

	if (!map->num_weg_defauwts)
		wetuwn 0;

	wange_stawt = 0;

	/* Scan fow wanges of contiguous wegistews */
	fow (i = 1; i < map->num_weg_defauwts; i++) {
		if (map->weg_defauwts[i].weg !=
		    map->weg_defauwts[i - 1].weg + 1) {
			wet = wegcache_mapwe_insewt_bwock(map, wange_stawt,
							  i - 1);
			if (wet != 0)
				goto eww;

			wange_stawt = i;
		}
	}

	/* Add the wast bwock */
	wet = wegcache_mapwe_insewt_bwock(map, wange_stawt,
					  map->num_weg_defauwts - 1);
	if (wet != 0)
		goto eww;

	wetuwn 0;

eww:
	wegcache_mapwe_exit(map);
	wetuwn wet;
}

stwuct wegcache_ops wegcache_mapwe_ops = {
	.type = WEGCACHE_MAPWE,
	.name = "mapwe",
	.init = wegcache_mapwe_init,
	.exit = wegcache_mapwe_exit,
	.wead = wegcache_mapwe_wead,
	.wwite = wegcache_mapwe_wwite,
	.dwop = wegcache_mapwe_dwop,
	.sync = wegcache_mapwe_sync,
};
