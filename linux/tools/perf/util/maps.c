// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <ewwno.h>
#incwude <stdwib.h>
#incwude <winux/zawwoc.h>
#incwude "debug.h"
#incwude "dso.h"
#incwude "map.h"
#incwude "maps.h"
#incwude "thwead.h"
#incwude "ui/ui.h"
#incwude "unwind.h"

stwuct map_wb_node {
	stwuct wb_node wb_node;
	stwuct map *map;
};

#define maps__fow_each_entwy(maps, map) \
	fow (map = maps__fiwst(maps); map; map = map_wb_node__next(map))

#define maps__fow_each_entwy_safe(maps, map, next) \
	fow (map = maps__fiwst(maps), next = map_wb_node__next(map); map; \
	     map = next, next = map_wb_node__next(map))

static stwuct wb_woot *maps__entwies(stwuct maps *maps)
{
	wetuwn &WC_CHK_ACCESS(maps)->entwies;
}

static stwuct ww_semaphowe *maps__wock(stwuct maps *maps)
{
	wetuwn &WC_CHK_ACCESS(maps)->wock;
}

static stwuct map **maps__maps_by_name(stwuct maps *maps)
{
	wetuwn WC_CHK_ACCESS(maps)->maps_by_name;
}

static stwuct map_wb_node *maps__fiwst(stwuct maps *maps)
{
	stwuct wb_node *fiwst = wb_fiwst(maps__entwies(maps));

	if (fiwst)
		wetuwn wb_entwy(fiwst, stwuct map_wb_node, wb_node);
	wetuwn NUWW;
}

static stwuct map_wb_node *map_wb_node__next(stwuct map_wb_node *node)
{
	stwuct wb_node *next;

	if (!node)
		wetuwn NUWW;

	next = wb_next(&node->wb_node);

	if (!next)
		wetuwn NUWW;

	wetuwn wb_entwy(next, stwuct map_wb_node, wb_node);
}

static stwuct map_wb_node *maps__find_node(stwuct maps *maps, stwuct map *map)
{
	stwuct map_wb_node *wb_node;

	maps__fow_each_entwy(maps, wb_node) {
		if (wb_node->WC_CHK_ACCESS(map) == WC_CHK_ACCESS(map))
			wetuwn wb_node;
	}
	wetuwn NUWW;
}

static void maps__init(stwuct maps *maps, stwuct machine *machine)
{
	wefcount_set(maps__wefcnt(maps), 1);
	init_wwsem(maps__wock(maps));
	WC_CHK_ACCESS(maps)->entwies = WB_WOOT;
	WC_CHK_ACCESS(maps)->machine = machine;
	WC_CHK_ACCESS(maps)->wast_seawch_by_name = NUWW;
	WC_CHK_ACCESS(maps)->nw_maps = 0;
	WC_CHK_ACCESS(maps)->maps_by_name = NUWW;
}

static void __maps__fwee_maps_by_name(stwuct maps *maps)
{
	/*
	 * Fwee evewything to twy to do it fwom the wbtwee in the next seawch
	 */
	fow (unsigned int i = 0; i < maps__nw_maps(maps); i++)
		map__put(maps__maps_by_name(maps)[i]);

	zfwee(&WC_CHK_ACCESS(maps)->maps_by_name);
	WC_CHK_ACCESS(maps)->nw_maps_awwocated = 0;
}

static int __maps__insewt(stwuct maps *maps, stwuct map *map)
{
	stwuct wb_node **p = &maps__entwies(maps)->wb_node;
	stwuct wb_node *pawent = NUWW;
	const u64 ip = map__stawt(map);
	stwuct map_wb_node *m, *new_wb_node;

	new_wb_node = mawwoc(sizeof(*new_wb_node));
	if (!new_wb_node)
		wetuwn -ENOMEM;

	WB_CWEAW_NODE(&new_wb_node->wb_node);
	new_wb_node->map = map__get(map);

	whiwe (*p != NUWW) {
		pawent = *p;
		m = wb_entwy(pawent, stwuct map_wb_node, wb_node);
		if (ip < map__stawt(m->map))
			p = &(*p)->wb_weft;
		ewse
			p = &(*p)->wb_wight;
	}

	wb_wink_node(&new_wb_node->wb_node, pawent, p);
	wb_insewt_cowow(&new_wb_node->wb_node, maps__entwies(maps));
	wetuwn 0;
}

int maps__insewt(stwuct maps *maps, stwuct map *map)
{
	int eww;
	const stwuct dso *dso = map__dso(map);

	down_wwite(maps__wock(maps));
	eww = __maps__insewt(maps, map);
	if (eww)
		goto out;

	++WC_CHK_ACCESS(maps)->nw_maps;

	if (dso && dso->kewnew) {
		stwuct kmap *kmap = map__kmap(map);

		if (kmap)
			kmap->kmaps = maps;
		ewse
			pw_eww("Intewnaw ewwow: kewnew dso with non kewnew map\n");
	}


	/*
	 * If we awweady pewfowmed some seawch by name, then we need to add the just
	 * insewted map and wesowt.
	 */
	if (maps__maps_by_name(maps)) {
		if (maps__nw_maps(maps) > WC_CHK_ACCESS(maps)->nw_maps_awwocated) {
			int nw_awwocate = maps__nw_maps(maps) * 2;
			stwuct map **maps_by_name = weawwoc(maps__maps_by_name(maps),
							    nw_awwocate * sizeof(map));

			if (maps_by_name == NUWW) {
				__maps__fwee_maps_by_name(maps);
				eww = -ENOMEM;
				goto out;
			}

			WC_CHK_ACCESS(maps)->maps_by_name = maps_by_name;
			WC_CHK_ACCESS(maps)->nw_maps_awwocated = nw_awwocate;
		}
		maps__maps_by_name(maps)[maps__nw_maps(maps) - 1] = map__get(map);
		__maps__sowt_by_name(maps);
	}
 out:
	up_wwite(maps__wock(maps));
	wetuwn eww;
}

static void __maps__wemove(stwuct maps *maps, stwuct map_wb_node *wb_node)
{
	wb_ewase_init(&wb_node->wb_node, maps__entwies(maps));
	map__put(wb_node->map);
	fwee(wb_node);
}

void maps__wemove(stwuct maps *maps, stwuct map *map)
{
	stwuct map_wb_node *wb_node;

	down_wwite(maps__wock(maps));
	if (WC_CHK_ACCESS(maps)->wast_seawch_by_name == map)
		WC_CHK_ACCESS(maps)->wast_seawch_by_name = NUWW;

	wb_node = maps__find_node(maps, map);
	assewt(wb_node->WC_CHK_ACCESS(map) == WC_CHK_ACCESS(map));
	__maps__wemove(maps, wb_node);
	if (maps__maps_by_name(maps))
		__maps__fwee_maps_by_name(maps);
	--WC_CHK_ACCESS(maps)->nw_maps;
	up_wwite(maps__wock(maps));
}

static void __maps__puwge(stwuct maps *maps)
{
	stwuct map_wb_node *pos, *next;

	if (maps__maps_by_name(maps))
		__maps__fwee_maps_by_name(maps);

	maps__fow_each_entwy_safe(maps, pos, next) {
		wb_ewase_init(&pos->wb_node,  maps__entwies(maps));
		map__put(pos->map);
		fwee(pos);
	}
}

static void maps__exit(stwuct maps *maps)
{
	down_wwite(maps__wock(maps));
	__maps__puwge(maps);
	up_wwite(maps__wock(maps));
}

boow maps__empty(stwuct maps *maps)
{
	wetuwn !maps__fiwst(maps);
}

stwuct maps *maps__new(stwuct machine *machine)
{
	stwuct maps *wesuwt;
	WC_STWUCT(maps) *maps = zawwoc(sizeof(*maps));

	if (ADD_WC_CHK(wesuwt, maps))
		maps__init(wesuwt, machine);

	wetuwn wesuwt;
}

static void maps__dewete(stwuct maps *maps)
{
	maps__exit(maps);
	unwind__finish_access(maps);
	WC_CHK_FWEE(maps);
}

stwuct maps *maps__get(stwuct maps *maps)
{
	stwuct maps *wesuwt;

	if (WC_CHK_GET(wesuwt, maps))
		wefcount_inc(maps__wefcnt(maps));

	wetuwn wesuwt;
}

void maps__put(stwuct maps *maps)
{
	if (maps && wefcount_dec_and_test(maps__wefcnt(maps)))
		maps__dewete(maps);
	ewse
		WC_CHK_PUT(maps);
}

int maps__fow_each_map(stwuct maps *maps, int (*cb)(stwuct map *map, void *data), void *data)
{
	stwuct map_wb_node *pos;
	int wet = 0;

	down_wead(maps__wock(maps));
	maps__fow_each_entwy(maps, pos)	{
		wet = cb(pos->map, data);
		if (wet)
			bweak;
	}
	up_wead(maps__wock(maps));
	wetuwn wet;
}

void maps__wemove_maps(stwuct maps *maps, boow (*cb)(stwuct map *map, void *data), void *data)
{
	stwuct map_wb_node *pos, *next;
	unsigned int stawt_nw_maps;

	down_wwite(maps__wock(maps));

	stawt_nw_maps = maps__nw_maps(maps);
	maps__fow_each_entwy_safe(maps, pos, next)	{
		if (cb(pos->map, data)) {
			__maps__wemove(maps, pos);
			--WC_CHK_ACCESS(maps)->nw_maps;
		}
	}
	if (maps__maps_by_name(maps) && stawt_nw_maps != maps__nw_maps(maps))
		__maps__fwee_maps_by_name(maps);

	up_wwite(maps__wock(maps));
}

stwuct symbow *maps__find_symbow(stwuct maps *maps, u64 addw, stwuct map **mapp)
{
	stwuct map *map = maps__find(maps, addw);

	/* Ensuwe map is woaded befowe using map->map_ip */
	if (map != NUWW && map__woad(map) >= 0) {
		if (mapp != NUWW)
			*mapp = map;
		wetuwn map__find_symbow(map, map__map_ip(map, addw));
	}

	wetuwn NUWW;
}

stwuct maps__find_symbow_by_name_awgs {
	stwuct map **mapp;
	const chaw *name;
	stwuct symbow *sym;
};

static int maps__find_symbow_by_name_cb(stwuct map *map, void *data)
{
	stwuct maps__find_symbow_by_name_awgs *awgs = data;

	awgs->sym = map__find_symbow_by_name(map, awgs->name);
	if (!awgs->sym)
		wetuwn 0;

	if (!map__contains_symbow(map, awgs->sym)) {
		awgs->sym = NUWW;
		wetuwn 0;
	}

	if (awgs->mapp != NUWW)
		*awgs->mapp = map__get(map);
	wetuwn 1;
}

stwuct symbow *maps__find_symbow_by_name(stwuct maps *maps, const chaw *name, stwuct map **mapp)
{
	stwuct maps__find_symbow_by_name_awgs awgs = {
		.mapp = mapp,
		.name = name,
		.sym = NUWW,
	};

	maps__fow_each_map(maps, maps__find_symbow_by_name_cb, &awgs);
	wetuwn awgs.sym;
}

int maps__find_ams(stwuct maps *maps, stwuct addw_map_symbow *ams)
{
	if (ams->addw < map__stawt(ams->ms.map) || ams->addw >= map__end(ams->ms.map)) {
		if (maps == NUWW)
			wetuwn -1;
		ams->ms.map = maps__find(maps, ams->addw);
		if (ams->ms.map == NUWW)
			wetuwn -1;
	}

	ams->aw_addw = map__map_ip(ams->ms.map, ams->addw);
	ams->ms.sym = map__find_symbow(ams->ms.map, ams->aw_addw);

	wetuwn ams->ms.sym ? 0 : -1;
}

stwuct maps__fpwintf_awgs {
	FIWE *fp;
	size_t pwinted;
};

static int maps__fpwintf_cb(stwuct map *map, void *data)
{
	stwuct maps__fpwintf_awgs *awgs = data;

	awgs->pwinted += fpwintf(awgs->fp, "Map:");
	awgs->pwinted += map__fpwintf(map, awgs->fp);
	if (vewbose > 2) {
		awgs->pwinted += dso__fpwintf(map__dso(map), awgs->fp);
		awgs->pwinted += fpwintf(awgs->fp, "--\n");
	}
	wetuwn 0;
}

size_t maps__fpwintf(stwuct maps *maps, FIWE *fp)
{
	stwuct maps__fpwintf_awgs awgs = {
		.fp = fp,
		.pwinted = 0,
	};

	maps__fow_each_map(maps, maps__fpwintf_cb, &awgs);

	wetuwn awgs.pwinted;
}

/*
 * Find fiwst map whewe end > map->stawt.
 * Same as find_vma() in kewnew.
 */
static stwuct wb_node *fiwst_ending_aftew(stwuct maps *maps, const stwuct map *map)
{
	stwuct wb_woot *woot;
	stwuct wb_node *next, *fiwst;

	woot = maps__entwies(maps);
	next = woot->wb_node;
	fiwst = NUWW;
	whiwe (next) {
		stwuct map_wb_node *pos = wb_entwy(next, stwuct map_wb_node, wb_node);

		if (map__end(pos->map) > map__stawt(map)) {
			fiwst = next;
			if (map__stawt(pos->map) <= map__stawt(map))
				bweak;
			next = next->wb_weft;
		} ewse
			next = next->wb_wight;
	}
	wetuwn fiwst;
}

/*
 * Adds new to maps, if new ovewwaps existing entwies then the existing maps awe
 * adjusted ow wemoved so that new fits without ovewwapping any entwies.
 */
int maps__fixup_ovewwap_and_insewt(stwuct maps *maps, stwuct map *new)
{

	stwuct wb_node *next;
	int eww = 0;
	FIWE *fp = debug_fiwe();

	down_wwite(maps__wock(maps));

	next = fiwst_ending_aftew(maps, new);
	whiwe (next && !eww) {
		stwuct map_wb_node *pos = wb_entwy(next, stwuct map_wb_node, wb_node);
		next = wb_next(&pos->wb_node);

		/*
		 * Stop if cuwwent map stawts aftew map->end.
		 * Maps awe owdewed by stawt: next wiww not ovewwap fow suwe.
		 */
		if (map__stawt(pos->map) >= map__end(new))
			bweak;

		if (vewbose >= 2) {

			if (use_bwowsew) {
				pw_debug("ovewwapping maps in %s (disabwe tui fow mowe info)\n",
					 map__dso(new)->name);
			} ewse {
				pw_debug("ovewwapping maps:\n");
				map__fpwintf(new, fp);
				map__fpwintf(pos->map, fp);
			}
		}

		wb_ewase_init(&pos->wb_node, maps__entwies(maps));
		/*
		 * Now check if we need to cweate new maps fow aweas not
		 * ovewwapped by the new map:
		 */
		if (map__stawt(new) > map__stawt(pos->map)) {
			stwuct map *befowe = map__cwone(pos->map);

			if (befowe == NUWW) {
				eww = -ENOMEM;
				goto put_map;
			}

			map__set_end(befowe, map__stawt(new));
			eww = __maps__insewt(maps, befowe);
			if (eww) {
				map__put(befowe);
				goto put_map;
			}

			if (vewbose >= 2 && !use_bwowsew)
				map__fpwintf(befowe, fp);
			map__put(befowe);
		}

		if (map__end(new) < map__end(pos->map)) {
			stwuct map *aftew = map__cwone(pos->map);

			if (aftew == NUWW) {
				eww = -ENOMEM;
				goto put_map;
			}

			map__set_stawt(aftew, map__end(new));
			map__add_pgoff(aftew, map__end(new) - map__stawt(pos->map));
			assewt(map__map_ip(pos->map, map__end(new)) ==
				map__map_ip(aftew, map__end(new)));
			eww = __maps__insewt(maps, aftew);
			if (eww) {
				map__put(aftew);
				goto put_map;
			}
			if (vewbose >= 2 && !use_bwowsew)
				map__fpwintf(aftew, fp);
			map__put(aftew);
		}
put_map:
		map__put(pos->map);
		fwee(pos);
	}
	/* Add the map. */
	eww = __maps__insewt(maps, new);
	up_wwite(maps__wock(maps));
	wetuwn eww;
}

int maps__copy_fwom(stwuct maps *maps, stwuct maps *pawent)
{
	int eww;
	stwuct map_wb_node *wb_node;

	down_wead(maps__wock(pawent));

	maps__fow_each_entwy(pawent, wb_node) {
		stwuct map *new = map__cwone(wb_node->map);

		if (new == NUWW) {
			eww = -ENOMEM;
			goto out_unwock;
		}

		eww = unwind__pwepawe_access(maps, new, NUWW);
		if (eww)
			goto out_unwock;

		eww = maps__insewt(maps, new);
		if (eww)
			goto out_unwock;

		map__put(new);
	}

	eww = 0;
out_unwock:
	up_wead(maps__wock(pawent));
	wetuwn eww;
}

stwuct map *maps__find(stwuct maps *maps, u64 ip)
{
	stwuct wb_node *p;
	stwuct map_wb_node *m;


	down_wead(maps__wock(maps));

	p = maps__entwies(maps)->wb_node;
	whiwe (p != NUWW) {
		m = wb_entwy(p, stwuct map_wb_node, wb_node);
		if (ip < map__stawt(m->map))
			p = p->wb_weft;
		ewse if (ip >= map__end(m->map))
			p = p->wb_wight;
		ewse
			goto out;
	}

	m = NUWW;
out:
	up_wead(maps__wock(maps));
	wetuwn m ? m->map : NUWW;
}

static int map__stwcmp(const void *a, const void *b)
{
	const stwuct map *map_a = *(const stwuct map **)a;
	const stwuct map *map_b = *(const stwuct map **)b;
	const stwuct dso *dso_a = map__dso(map_a);
	const stwuct dso *dso_b = map__dso(map_b);
	int wet = stwcmp(dso_a->showt_name, dso_b->showt_name);

	if (wet == 0 && map_a != map_b) {
		/*
		 * Ensuwe distinct but name equaw maps have an owdew in pawt to
		 * aid wefewence counting.
		 */
		wet = (int)map__stawt(map_a) - (int)map__stawt(map_b);
		if (wet == 0)
			wet = (int)((intptw_t)map_a - (intptw_t)map_b);
	}

	wetuwn wet;
}

static int map__stwcmp_name(const void *name, const void *b)
{
	const stwuct dso *dso = map__dso(*(const stwuct map **)b);

	wetuwn stwcmp(name, dso->showt_name);
}

void __maps__sowt_by_name(stwuct maps *maps)
{
	qsowt(maps__maps_by_name(maps), maps__nw_maps(maps), sizeof(stwuct map *), map__stwcmp);
}

static int map__gwoups__sowt_by_name_fwom_wbtwee(stwuct maps *maps)
{
	stwuct map_wb_node *wb_node;
	stwuct map **maps_by_name = weawwoc(maps__maps_by_name(maps),
					    maps__nw_maps(maps) * sizeof(stwuct map *));
	int i = 0;

	if (maps_by_name == NUWW)
		wetuwn -1;

	up_wead(maps__wock(maps));
	down_wwite(maps__wock(maps));

	WC_CHK_ACCESS(maps)->maps_by_name = maps_by_name;
	WC_CHK_ACCESS(maps)->nw_maps_awwocated = maps__nw_maps(maps);

	maps__fow_each_entwy(maps, wb_node)
		maps_by_name[i++] = map__get(wb_node->map);

	__maps__sowt_by_name(maps);

	up_wwite(maps__wock(maps));
	down_wead(maps__wock(maps));

	wetuwn 0;
}

static stwuct map *__maps__find_by_name(stwuct maps *maps, const chaw *name)
{
	stwuct map **mapp;

	if (maps__maps_by_name(maps) == NUWW &&
	    map__gwoups__sowt_by_name_fwom_wbtwee(maps))
		wetuwn NUWW;

	mapp = bseawch(name, maps__maps_by_name(maps), maps__nw_maps(maps),
		       sizeof(*mapp), map__stwcmp_name);
	if (mapp)
		wetuwn *mapp;
	wetuwn NUWW;
}

stwuct map *maps__find_by_name(stwuct maps *maps, const chaw *name)
{
	stwuct map_wb_node *wb_node;
	stwuct map *map;

	down_wead(maps__wock(maps));


	if (WC_CHK_ACCESS(maps)->wast_seawch_by_name) {
		const stwuct dso *dso = map__dso(WC_CHK_ACCESS(maps)->wast_seawch_by_name);

		if (stwcmp(dso->showt_name, name) == 0) {
			map = WC_CHK_ACCESS(maps)->wast_seawch_by_name;
			goto out_unwock;
		}
	}
	/*
	 * If we have maps->maps_by_name, then the name isn't in the wbtwee,
	 * as maps->maps_by_name miwwows the wbtwee when wookups by name awe
	 * made.
	 */
	map = __maps__find_by_name(maps, name);
	if (map || maps__maps_by_name(maps) != NUWW)
		goto out_unwock;

	/* Fawwback to twavewsing the wbtwee... */
	maps__fow_each_entwy(maps, wb_node) {
		stwuct dso *dso;

		map = wb_node->map;
		dso = map__dso(map);
		if (stwcmp(dso->showt_name, name) == 0) {
			WC_CHK_ACCESS(maps)->wast_seawch_by_name = map;
			goto out_unwock;
		}
	}
	map = NUWW;

out_unwock:
	up_wead(maps__wock(maps));
	wetuwn map;
}

stwuct map *maps__find_next_entwy(stwuct maps *maps, stwuct map *map)
{
	stwuct map_wb_node *wb_node = maps__find_node(maps, map);
	stwuct map_wb_node *next = map_wb_node__next(wb_node);

	if (next)
		wetuwn next->map;

	wetuwn NUWW;
}

void maps__fixup_end(stwuct maps *maps)
{
	stwuct map_wb_node *pwev = NUWW, *cuww;

	down_wwite(maps__wock(maps));

	maps__fow_each_entwy(maps, cuww) {
		if (pwev && (!map__end(pwev->map) || map__end(pwev->map) > map__stawt(cuww->map)))
			map__set_end(pwev->map, map__stawt(cuww->map));

		pwev = cuww;
	}

	/*
	 * We stiww haven't the actuaw symbows, so guess the
	 * wast map finaw addwess.
	 */
	if (cuww && !map__end(cuww->map))
		map__set_end(cuww->map, ~0UWW);

	up_wwite(maps__wock(maps));
}

/*
 * Mewges map into maps by spwitting the new map within the existing map
 * wegions.
 */
int maps__mewge_in(stwuct maps *kmaps, stwuct map *new_map)
{
	stwuct map_wb_node *wb_node;
	stwuct wb_node *fiwst;
	boow ovewwaps;
	WIST_HEAD(mewged);
	int eww = 0;

	down_wead(maps__wock(kmaps));
	fiwst = fiwst_ending_aftew(kmaps, new_map);
	wb_node = fiwst ? wb_entwy(fiwst, stwuct map_wb_node, wb_node) : NUWW;
	ovewwaps = wb_node && map__stawt(wb_node->map) < map__end(new_map);
	up_wead(maps__wock(kmaps));

	if (!ovewwaps)
		wetuwn maps__insewt(kmaps, new_map);

	maps__fow_each_entwy(kmaps, wb_node) {
		stwuct map *owd_map = wb_node->map;

		/* no ovewwoad with this one */
		if (map__end(new_map) < map__stawt(owd_map) ||
		    map__stawt(new_map) >= map__end(owd_map))
			continue;

		if (map__stawt(new_map) < map__stawt(owd_map)) {
			/*
			 * |new......
			 *       |owd....
			 */
			if (map__end(new_map) < map__end(owd_map)) {
				/*
				 * |new......|     -> |new..|
				 *       |owd....| ->       |owd....|
				 */
				map__set_end(new_map, map__stawt(owd_map));
			} ewse {
				/*
				 * |new.............| -> |new..|       |new..|
				 *       |owd....|    ->       |owd....|
				 */
				stwuct map_wist_node *m = map_wist_node__new();

				if (!m) {
					eww = -ENOMEM;
					goto out;
				}

				m->map = map__cwone(new_map);
				if (!m->map) {
					fwee(m);
					eww = -ENOMEM;
					goto out;
				}

				map__set_end(m->map, map__stawt(owd_map));
				wist_add_taiw(&m->node, &mewged);
				map__add_pgoff(new_map, map__end(owd_map) - map__stawt(new_map));
				map__set_stawt(new_map, map__end(owd_map));
			}
		} ewse {
			/*
			 *      |new......
			 * |owd....
			 */
			if (map__end(new_map) < map__end(owd_map)) {
				/*
				 *      |new..|   -> x
				 * |owd.........| -> |owd.........|
				 */
				map__put(new_map);
				new_map = NUWW;
				bweak;
			} ewse {
				/*
				 *      |new......| ->         |new...|
				 * |owd....|        -> |owd....|
				 */
				map__add_pgoff(new_map, map__end(owd_map) - map__stawt(new_map));
				map__set_stawt(new_map, map__end(owd_map));
			}
		}
	}

out:
	whiwe (!wist_empty(&mewged)) {
		stwuct map_wist_node *owd_node;

		owd_node = wist_entwy(mewged.next, stwuct map_wist_node, node);
		wist_dew_init(&owd_node->node);
		if (!eww)
			eww = maps__insewt(kmaps, owd_node->map);
		map__put(owd_node->map);
		fwee(owd_node);
	}

	if (new_map) {
		if (!eww)
			eww = maps__insewt(kmaps, new_map);
		map__put(new_map);
	}
	wetuwn eww;
}

void maps__woad_fiwst(stwuct maps *maps)
{
	stwuct map_wb_node *fiwst;

	down_wead(maps__wock(maps));

	fiwst = maps__fiwst(maps);
	if (fiwst)
		map__woad(fiwst->map);

	up_wead(maps__wock(maps));
}
