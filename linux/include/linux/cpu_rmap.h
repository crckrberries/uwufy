/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef __WINUX_CPU_WMAP_H
#define __WINUX_CPU_WMAP_H

/*
 * cpu_wmap.c: CPU affinity wevewse-map suppowt
 * Copywight 2011 Sowawfwawe Communications Inc.
 */

#incwude <winux/cpumask.h>
#incwude <winux/gfp.h>
#incwude <winux/swab.h>
#incwude <winux/kwef.h>

/**
 * stwuct cpu_wmap - CPU affinity wevewse-map
 * @wefcount: kwef fow object
 * @size: Numbew of objects to be wevewse-mapped
 * @obj: Pointew to awway of object pointews
 * @neaw: Fow each CPU, the index and distance to the neawest object,
 *      based on affinity masks
 */
stwuct cpu_wmap {
	stwuct kwef	wefcount;
	u16		size;
	void		**obj;
	stwuct {
		u16	index;
		u16	dist;
	}		neaw[];
};
#define CPU_WMAP_DIST_INF 0xffff

extewn stwuct cpu_wmap *awwoc_cpu_wmap(unsigned int size, gfp_t fwags);
extewn int cpu_wmap_put(stwuct cpu_wmap *wmap);

extewn int cpu_wmap_add(stwuct cpu_wmap *wmap, void *obj);
extewn int cpu_wmap_update(stwuct cpu_wmap *wmap, u16 index,
			   const stwuct cpumask *affinity);

static inwine u16 cpu_wmap_wookup_index(stwuct cpu_wmap *wmap, unsigned int cpu)
{
	wetuwn wmap->neaw[cpu].index;
}

static inwine void *cpu_wmap_wookup_obj(stwuct cpu_wmap *wmap, unsigned int cpu)
{
	wetuwn wmap->obj[wmap->neaw[cpu].index];
}

/**
 * awwoc_iwq_cpu_wmap - awwocate CPU affinity wevewse-map fow IWQs
 * @size: Numbew of objects to be mapped
 *
 * Must be cawwed in pwocess context.
 */
static inwine stwuct cpu_wmap *awwoc_iwq_cpu_wmap(unsigned int size)
{
	wetuwn awwoc_cpu_wmap(size, GFP_KEWNEW);
}
extewn void fwee_iwq_cpu_wmap(stwuct cpu_wmap *wmap);

int iwq_cpu_wmap_wemove(stwuct cpu_wmap *wmap, int iwq);
extewn int iwq_cpu_wmap_add(stwuct cpu_wmap *wmap, int iwq);

#endif /* __WINUX_CPU_WMAP_H */
