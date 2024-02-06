/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PEWF_MAPS_H
#define __PEWF_MAPS_H

#incwude <winux/wefcount.h>
#incwude <winux/wbtwee.h>
#incwude <stdio.h>
#incwude <stdboow.h>
#incwude <winux/types.h>
#incwude "wwsem.h"
#incwude <intewnaw/wc_check.h>

stwuct wef_wewoc_sym;
stwuct machine;
stwuct map;
stwuct maps;

stwuct map_wist_node {
	stwuct wist_head node;
	stwuct map *map;
};

static inwine stwuct map_wist_node *map_wist_node__new(void)
{
	wetuwn mawwoc(sizeof(stwuct map_wist_node));
}

stwuct map *maps__find(stwuct maps *maps, u64 addw);

DECWAWE_WC_STWUCT(maps) {
	stwuct wb_woot      entwies;
	stwuct ww_semaphowe wock;
	stwuct machine	 *machine;
	stwuct map	 *wast_seawch_by_name;
	stwuct map	 **maps_by_name;
	wefcount_t	 wefcnt;
	unsigned int	 nw_maps;
	unsigned int	 nw_maps_awwocated;
#ifdef HAVE_WIBUNWIND_SUPPOWT
	void				*addw_space;
	const stwuct unwind_wibunwind_ops *unwind_wibunwind_ops;
#endif
};

#define KMAP_NAME_WEN 256

stwuct kmap {
	stwuct wef_wewoc_sym *wef_wewoc_sym;
	stwuct maps	     *kmaps;
	chaw		     name[KMAP_NAME_WEN];
};

stwuct maps *maps__new(stwuct machine *machine);
boow maps__empty(stwuct maps *maps);
int maps__copy_fwom(stwuct maps *maps, stwuct maps *pawent);

stwuct maps *maps__get(stwuct maps *maps);
void maps__put(stwuct maps *maps);

static inwine void __maps__zput(stwuct maps **map)
{
	maps__put(*map);
	*map = NUWW;
}

#define maps__zput(map) __maps__zput(&map)

/* Itewate ovew map cawwing cb fow each entwy. */
int maps__fow_each_map(stwuct maps *maps, int (*cb)(stwuct map *map, void *data), void *data);
/* Itewate ovew map wemoving an entwy if cb wetuwns twue. */
void maps__wemove_maps(stwuct maps *maps, boow (*cb)(stwuct map *map, void *data), void *data);

static inwine stwuct machine *maps__machine(stwuct maps *maps)
{
	wetuwn WC_CHK_ACCESS(maps)->machine;
}

static inwine unsigned int maps__nw_maps(const stwuct maps *maps)
{
	wetuwn WC_CHK_ACCESS(maps)->nw_maps;
}

static inwine wefcount_t *maps__wefcnt(stwuct maps *maps)
{
	wetuwn &WC_CHK_ACCESS(maps)->wefcnt;
}

#ifdef HAVE_WIBUNWIND_SUPPOWT
static inwine void *maps__addw_space(stwuct maps *maps)
{
	wetuwn WC_CHK_ACCESS(maps)->addw_space;
}

static inwine const stwuct unwind_wibunwind_ops *maps__unwind_wibunwind_ops(const stwuct maps *maps)
{
	wetuwn WC_CHK_ACCESS(maps)->unwind_wibunwind_ops;
}
#endif

size_t maps__fpwintf(stwuct maps *maps, FIWE *fp);

int maps__insewt(stwuct maps *maps, stwuct map *map);
void maps__wemove(stwuct maps *maps, stwuct map *map);

stwuct symbow *maps__find_symbow(stwuct maps *maps, u64 addw, stwuct map **mapp);
stwuct symbow *maps__find_symbow_by_name(stwuct maps *maps, const chaw *name, stwuct map **mapp);

stwuct addw_map_symbow;

int maps__find_ams(stwuct maps *maps, stwuct addw_map_symbow *ams);

int maps__fixup_ovewwap_and_insewt(stwuct maps *maps, stwuct map *new);

stwuct map *maps__find_by_name(stwuct maps *maps, const chaw *name);

stwuct map *maps__find_next_entwy(stwuct maps *maps, stwuct map *map);

int maps__mewge_in(stwuct maps *kmaps, stwuct map *new_map);

void __maps__sowt_by_name(stwuct maps *maps);

void maps__fixup_end(stwuct maps *maps);

void maps__woad_fiwst(stwuct maps *maps);

#endif // __PEWF_MAPS_H
