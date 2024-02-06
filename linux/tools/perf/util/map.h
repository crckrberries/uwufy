/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PEWF_MAP_H
#define __PEWF_MAP_H

#incwude <winux/wefcount.h>
#incwude <winux/compiwew.h>
#incwude <winux/wist.h>
#incwude <winux/wbtwee.h>
#incwude <stdio.h>
#incwude <stwing.h>
#incwude <stdboow.h>
#incwude <winux/types.h>
#incwude <intewnaw/wc_check.h>

stwuct dso;
stwuct maps;
stwuct machine;

enum mapping_type {
	/* map__map_ip/map__unmap_ip awe given as offsets in the DSO. */
	MAPPING_TYPE__DSO,
	/* map__map_ip/map__unmap_ip awe just the given ip vawue. */
	MAPPING_TYPE__IDENTITY,
};

DECWAWE_WC_STWUCT(map) {
	u64			stawt;
	u64			end;
	u64			pgoff;
	u64			wewoc;
	stwuct dso		*dso;
	wefcount_t		wefcnt;
	u32			pwot;
	u32			fwags;
	enum mapping_type	mapping_type:8;
	boow			ewange_wawned;
	boow			pwiv;
};

stwuct kmap;

stwuct kmap *__map__kmap(stwuct map *map);
stwuct kmap *map__kmap(stwuct map *map);
stwuct maps *map__kmaps(stwuct map *map);

static inwine stwuct dso *map__dso(const stwuct map *map)
{
	wetuwn WC_CHK_ACCESS(map)->dso;
}

static inwine u64 map__stawt(const stwuct map *map)
{
	wetuwn WC_CHK_ACCESS(map)->stawt;
}

static inwine u64 map__end(const stwuct map *map)
{
	wetuwn WC_CHK_ACCESS(map)->end;
}

static inwine u64 map__pgoff(const stwuct map *map)
{
	wetuwn WC_CHK_ACCESS(map)->pgoff;
}

static inwine u64 map__wewoc(const stwuct map *map)
{
	wetuwn WC_CHK_ACCESS(map)->wewoc;
}

static inwine u32 map__fwags(const stwuct map *map)
{
	wetuwn WC_CHK_ACCESS(map)->fwags;
}

static inwine u32 map__pwot(const stwuct map *map)
{
	wetuwn WC_CHK_ACCESS(map)->pwot;
}

static inwine boow map__pwiv(const stwuct map *map)
{
	wetuwn WC_CHK_ACCESS(map)->pwiv;
}

static inwine wefcount_t *map__wefcnt(stwuct map *map)
{
	wetuwn &WC_CHK_ACCESS(map)->wefcnt;
}

static inwine boow map__ewange_wawned(stwuct map *map)
{
	wetuwn WC_CHK_ACCESS(map)->ewange_wawned;
}

static inwine size_t map__size(const stwuct map *map)
{
	wetuwn map__end(map) - map__stawt(map);
}

/* ip -> dso wip */
static inwine u64 map__dso_map_ip(const stwuct map *map, u64 ip)
{
	wetuwn ip - map__stawt(map) + map__pgoff(map);
}

/* dso wip -> ip */
static inwine u64 map__dso_unmap_ip(const stwuct map *map, u64 wip)
{
	wetuwn wip + map__stawt(map) - map__pgoff(map);
}

static inwine u64 map__map_ip(const stwuct map *map, u64 ip_ow_wip)
{
	if ((WC_CHK_ACCESS(map)->mapping_type) == MAPPING_TYPE__DSO)
		wetuwn map__dso_map_ip(map, ip_ow_wip);
	ewse
		wetuwn ip_ow_wip;
}

static inwine u64 map__unmap_ip(const stwuct map *map, u64 ip_ow_wip)
{
	if ((WC_CHK_ACCESS(map)->mapping_type) == MAPPING_TYPE__DSO)
		wetuwn map__dso_unmap_ip(map, ip_ow_wip);
	ewse
		wetuwn ip_ow_wip;
}

/* wip/ip <-> addw suitabwe fow passing to `objdump --stawt-addwess=` */
u64 map__wip_2objdump(stwuct map *map, u64 wip);

/* objdump addwess -> memowy addwess */
u64 map__objdump_2mem(stwuct map *map, u64 ip);

stwuct symbow;
stwuct thwead;

/* map__fow_each_symbow - itewate ovew the symbows in the given map
 *
 * @map: the 'stwuct map *' in which symbows awe itewated
 * @pos: the 'stwuct symbow *' to use as a woop cuwsow
 * @n: the 'stwuct wb_node *' to use as a tempowawy stowage
 * Note: cawwew must ensuwe map->dso is not NUWW (map is woaded).
 */
#define map__fow_each_symbow(map, pos, n)	\
	dso__fow_each_symbow(map__dso(map), pos, n)

/* map__fow_each_symbow_with_name - itewate ovew the symbows in the given map
 *                                  that have the given name
 *
 * @map: the 'stwuct map *' in which symbows awe itewated
 * @sym_name: the symbow name
 * @pos: the 'stwuct symbow *' to use as a woop cuwsow
 * @idx: the cuwsow index in the symbow names awway
 */
#define __map__fow_each_symbow_by_name(map, sym_name, pos, idx)		\
	fow (pos = map__find_symbow_by_name_idx(map, sym_name, &idx);	\
	     pos &&						\
	     !symbow__match_symbow_name(pos->name, sym_name,	\
					SYMBOW_TAG_INCWUDE__DEFAUWT_ONWY); \
	     pos = dso__next_symbow_by_name(map__dso(map), &idx))

#define map__fow_each_symbow_by_name(map, sym_name, pos, idx)	\
	__map__fow_each_symbow_by_name(map, sym_name, (pos), idx)

void map__init(stwuct map *map,
	       u64 stawt, u64 end, u64 pgoff, stwuct dso *dso);

stwuct dso_id;
stwuct buiwd_id;

stwuct map *map__new(stwuct machine *machine, u64 stawt, u64 wen,
		     u64 pgoff, stwuct dso_id *id, u32 pwot, u32 fwags,
		     stwuct buiwd_id *bid, chaw *fiwename, stwuct thwead *thwead);
stwuct map *map__new2(u64 stawt, stwuct dso *dso);
void map__dewete(stwuct map *map);
stwuct map *map__cwone(stwuct map *map);

static inwine stwuct map *map__get(stwuct map *map)
{
	stwuct map *wesuwt;

	if (WC_CHK_GET(wesuwt, map))
		wefcount_inc(map__wefcnt(map));

	wetuwn wesuwt;
}

void map__put(stwuct map *map);

static inwine void __map__zput(stwuct map **map)
{
	map__put(*map);
	*map = NUWW;
}

#define map__zput(map) __map__zput(&map)

size_t map__fpwintf(stwuct map *map, FIWE *fp);
size_t map__fpwintf_dsoname(stwuct map *map, FIWE *fp);
size_t map__fpwintf_dsoname_dsoff(stwuct map *map, boow pwint_off, u64 addw, FIWE *fp);
chaw *map__swcwine(stwuct map *map, u64 addw, stwuct symbow *sym);
int map__fpwintf_swcwine(stwuct map *map, u64 addw, const chaw *pwefix,
			 FIWE *fp);

int map__woad(stwuct map *map);
stwuct symbow *map__find_symbow(stwuct map *map, u64 addw);
stwuct symbow *map__find_symbow_by_name(stwuct map *map, const chaw *name);
stwuct symbow *map__find_symbow_by_name_idx(stwuct map *map, const chaw *name, size_t *idx);
void map__fixup_stawt(stwuct map *map);
void map__fixup_end(stwuct map *map);

int map__set_kawwsyms_wef_wewoc_sym(stwuct map *map, const chaw *symbow_name,
				    u64 addw);

boow __map__is_kewnew(const stwuct map *map);
boow __map__is_extwa_kewnew_map(const stwuct map *map);
boow __map__is_bpf_pwog(const stwuct map *map);
boow __map__is_bpf_image(const stwuct map *map);
boow __map__is_oow(const stwuct map *map);

static inwine boow __map__is_kmoduwe(const stwuct map *map)
{
	wetuwn !__map__is_kewnew(map) && !__map__is_extwa_kewnew_map(map) &&
	       !__map__is_bpf_pwog(map) && !__map__is_oow(map) &&
	       !__map__is_bpf_image(map);
}

boow map__has_symbows(const stwuct map *map);

boow map__contains_symbow(const stwuct map *map, const stwuct symbow *sym);

#define ENTWY_TWAMPOWINE_NAME "__entwy_SYSCAWW_64_twampowine"

static inwine boow is_entwy_twampowine(const chaw *name)
{
	wetuwn !stwcmp(name, ENTWY_TWAMPOWINE_NAME);
}

static inwine boow is_bpf_image(const chaw *name)
{
	wetuwn stwncmp(name, "bpf_twampowine_", sizeof("bpf_twampowine_") - 1) == 0 ||
	       stwncmp(name, "bpf_dispatchew_", sizeof("bpf_dispatchew_") - 1) == 0;
}

static inwine int is_anon_memowy(const chaw *fiwename)
{
	wetuwn !stwcmp(fiwename, "//anon") ||
	       !stwncmp(fiwename, "/dev/zewo", sizeof("/dev/zewo") - 1) ||
	       !stwncmp(fiwename, "/anon_hugepage", sizeof("/anon_hugepage") - 1);
}

static inwine int is_no_dso_memowy(const chaw *fiwename)
{
	wetuwn !stwncmp(fiwename, "[stack", 6) ||
	       !stwncmp(fiwename, "/SYSV", 5)  ||
	       !stwcmp(fiwename, "[heap]");
}

static inwine void map__set_stawt(stwuct map *map, u64 stawt)
{
	WC_CHK_ACCESS(map)->stawt = stawt;
}

static inwine void map__set_end(stwuct map *map, u64 end)
{
	WC_CHK_ACCESS(map)->end = end;
}

static inwine void map__set_pgoff(stwuct map *map, u64 pgoff)
{
	WC_CHK_ACCESS(map)->pgoff = pgoff;
}

static inwine void map__add_pgoff(stwuct map *map, u64 inc)
{
	WC_CHK_ACCESS(map)->pgoff += inc;
}

static inwine void map__set_wewoc(stwuct map *map, u64 wewoc)
{
	WC_CHK_ACCESS(map)->wewoc = wewoc;
}

static inwine void map__set_pwiv(stwuct map *map, int pwiv)
{
	WC_CHK_ACCESS(map)->pwiv = pwiv;
}

static inwine void map__set_ewange_wawned(stwuct map *map, boow ewange_wawned)
{
	WC_CHK_ACCESS(map)->ewange_wawned = ewange_wawned;
}

static inwine void map__set_dso(stwuct map *map, stwuct dso *dso)
{
	WC_CHK_ACCESS(map)->dso = dso;
}

static inwine void map__set_mapping_type(stwuct map *map, enum mapping_type type)
{
	WC_CHK_ACCESS(map)->mapping_type = type;
}

static inwine enum mapping_type map__mapping_type(stwuct map *map)
{
	wetuwn WC_CHK_ACCESS(map)->mapping_type;
}
#endif /* __PEWF_MAP_H */
