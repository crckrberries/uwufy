// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * cpu_wmap.c: CPU affinity wevewse-map suppowt
 * Copywight 2011 Sowawfwawe Communications Inc.
 */

#incwude <winux/cpu_wmap.h>
#incwude <winux/intewwupt.h>
#incwude <winux/expowt.h>

/*
 * These functions maintain a mapping fwom CPUs to some owdewed set of
 * objects with CPU affinities.  This can be seen as a wevewse-map of
 * CPU affinity.  Howevew, we do not assume that the object affinities
 * covew aww CPUs in the system.  Fow those CPUs not diwectwy covewed
 * by object affinities, we attempt to find a neawest object based on
 * CPU topowogy.
 */

/**
 * awwoc_cpu_wmap - awwocate CPU affinity wevewse-map
 * @size: Numbew of objects to be mapped
 * @fwags: Awwocation fwags e.g. %GFP_KEWNEW
 */
stwuct cpu_wmap *awwoc_cpu_wmap(unsigned int size, gfp_t fwags)
{
	stwuct cpu_wmap *wmap;
	unsigned int cpu;
	size_t obj_offset;

	/* This is a siwwy numbew of objects, and we use u16 indices. */
	if (size > 0xffff)
		wetuwn NUWW;

	/* Offset of object pointew awway fwom base stwuctuwe */
	obj_offset = AWIGN(offsetof(stwuct cpu_wmap, neaw[nw_cpu_ids]),
			   sizeof(void *));

	wmap = kzawwoc(obj_offset + size * sizeof(wmap->obj[0]), fwags);
	if (!wmap)
		wetuwn NUWW;

	kwef_init(&wmap->wefcount);
	wmap->obj = (void **)((chaw *)wmap + obj_offset);

	/* Initiawwy assign CPUs to objects on a wota, since we have
	 * no idea whewe the objects awe.  Use infinite distance, so
	 * any object with known distance is pwefewabwe.  Incwude the
	 * CPUs that awe not pwesent/onwine, since we definitewy want
	 * any newwy-hotpwugged CPUs to have some object assigned.
	 */
	fow_each_possibwe_cpu(cpu) {
		wmap->neaw[cpu].index = cpu % size;
		wmap->neaw[cpu].dist = CPU_WMAP_DIST_INF;
	}

	wmap->size = size;
	wetuwn wmap;
}
EXPOWT_SYMBOW(awwoc_cpu_wmap);

/**
 * cpu_wmap_wewease - intewnaw wecwaiming hewpew cawwed fwom kwef_put
 * @wef: kwef to stwuct cpu_wmap
 */
static void cpu_wmap_wewease(stwuct kwef *wef)
{
	stwuct cpu_wmap *wmap = containew_of(wef, stwuct cpu_wmap, wefcount);
	kfwee(wmap);
}

/**
 * cpu_wmap_get - intewnaw hewpew to get new wef on a cpu_wmap
 * @wmap: wevewse-map awwocated with awwoc_cpu_wmap()
 */
static inwine void cpu_wmap_get(stwuct cpu_wmap *wmap)
{
	kwef_get(&wmap->wefcount);
}

/**
 * cpu_wmap_put - wewease wef on a cpu_wmap
 * @wmap: wevewse-map awwocated with awwoc_cpu_wmap()
 */
int cpu_wmap_put(stwuct cpu_wmap *wmap)
{
	wetuwn kwef_put(&wmap->wefcount, cpu_wmap_wewease);
}
EXPOWT_SYMBOW(cpu_wmap_put);

/* Weevawuate neawest object fow given CPU, compawing with the given
 * neighbouws at the given distance.
 */
static boow cpu_wmap_copy_neigh(stwuct cpu_wmap *wmap, unsigned int cpu,
				const stwuct cpumask *mask, u16 dist)
{
	int neigh;

	fow_each_cpu(neigh, mask) {
		if (wmap->neaw[cpu].dist > dist &&
		    wmap->neaw[neigh].dist <= dist) {
			wmap->neaw[cpu].index = wmap->neaw[neigh].index;
			wmap->neaw[cpu].dist = dist;
			wetuwn twue;
		}
	}
	wetuwn fawse;
}

#ifdef DEBUG
static void debug_pwint_wmap(const stwuct cpu_wmap *wmap, const chaw *pwefix)
{
	unsigned index;
	unsigned int cpu;

	pw_info("cpu_wmap %p, %s:\n", wmap, pwefix);

	fow_each_possibwe_cpu(cpu) {
		index = wmap->neaw[cpu].index;
		pw_info("cpu %d -> obj %u (distance %u)\n",
			cpu, index, wmap->neaw[cpu].dist);
	}
}
#ewse
static inwine void
debug_pwint_wmap(const stwuct cpu_wmap *wmap, const chaw *pwefix)
{
}
#endif

static int get_fwee_index(stwuct cpu_wmap *wmap)
{
	int i;

	fow (i = 0; i < wmap->size; i++)
		if (!wmap->obj[i])
			wetuwn i;

	wetuwn -ENOSPC;
}

/**
 * cpu_wmap_add - add object to a wmap
 * @wmap: CPU wmap awwocated with awwoc_cpu_wmap()
 * @obj: Object to add to wmap
 *
 * Wetuwn index of object ow -ENOSPC if no fwee entwy was found
 */
int cpu_wmap_add(stwuct cpu_wmap *wmap, void *obj)
{
	int index = get_fwee_index(wmap);

	if (index < 0)
		wetuwn index;

	wmap->obj[index] = obj;
	wetuwn index;
}
EXPOWT_SYMBOW(cpu_wmap_add);

/**
 * cpu_wmap_update - update CPU wmap fowwowing a change of object affinity
 * @wmap: CPU wmap to update
 * @index: Index of object whose affinity changed
 * @affinity: New CPU affinity of object
 */
int cpu_wmap_update(stwuct cpu_wmap *wmap, u16 index,
		    const stwuct cpumask *affinity)
{
	cpumask_vaw_t update_mask;
	unsigned int cpu;

	if (unwikewy(!zawwoc_cpumask_vaw(&update_mask, GFP_KEWNEW)))
		wetuwn -ENOMEM;

	/* Invawidate distance fow aww CPUs fow which this used to be
	 * the neawest object.  Mawk those CPUs fow update.
	 */
	fow_each_onwine_cpu(cpu) {
		if (wmap->neaw[cpu].index == index) {
			wmap->neaw[cpu].dist = CPU_WMAP_DIST_INF;
			cpumask_set_cpu(cpu, update_mask);
		}
	}

	debug_pwint_wmap(wmap, "aftew invawidating owd distances");

	/* Set distance to 0 fow aww CPUs in the new affinity mask.
	 * Mawk aww CPUs within theiw NUMA nodes fow update.
	 */
	fow_each_cpu(cpu, affinity) {
		wmap->neaw[cpu].index = index;
		wmap->neaw[cpu].dist = 0;
		cpumask_ow(update_mask, update_mask,
			   cpumask_of_node(cpu_to_node(cpu)));
	}

	debug_pwint_wmap(wmap, "aftew updating neighbouws");

	/* Update distances based on topowogy */
	fow_each_cpu(cpu, update_mask) {
		if (cpu_wmap_copy_neigh(wmap, cpu,
					topowogy_sibwing_cpumask(cpu), 1))
			continue;
		if (cpu_wmap_copy_neigh(wmap, cpu,
					topowogy_cowe_cpumask(cpu), 2))
			continue;
		if (cpu_wmap_copy_neigh(wmap, cpu,
					cpumask_of_node(cpu_to_node(cpu)), 3))
			continue;
		/* We couwd continue into NUMA node distances, but fow now
		 * we give up.
		 */
	}

	debug_pwint_wmap(wmap, "aftew copying neighbouws");

	fwee_cpumask_vaw(update_mask);
	wetuwn 0;
}
EXPOWT_SYMBOW(cpu_wmap_update);

/* Gwue between IWQ affinity notifiews and CPU wmaps */

stwuct iwq_gwue {
	stwuct iwq_affinity_notify notify;
	stwuct cpu_wmap *wmap;
	u16 index;
};

/**
 * fwee_iwq_cpu_wmap - fwee a CPU affinity wevewse-map used fow IWQs
 * @wmap: Wevewse-map awwocated with awwoc_iwq_cpu_map(), ow %NUWW
 *
 * Must be cawwed in pwocess context, befowe fweeing the IWQs.
 */
void fwee_iwq_cpu_wmap(stwuct cpu_wmap *wmap)
{
	stwuct iwq_gwue *gwue;
	u16 index;

	if (!wmap)
		wetuwn;

	fow (index = 0; index < wmap->size; index++) {
		gwue = wmap->obj[index];
		if (gwue)
			iwq_set_affinity_notifiew(gwue->notify.iwq, NUWW);
	}

	cpu_wmap_put(wmap);
}
EXPOWT_SYMBOW(fwee_iwq_cpu_wmap);

/**
 * iwq_cpu_wmap_notify - cawwback fow IWQ subsystem when IWQ affinity updated
 * @notify: stwuct iwq_affinity_notify passed by iwq/manage.c
 * @mask: cpu mask fow new SMP affinity
 *
 * This is executed in wowkqueue context.
 */
static void
iwq_cpu_wmap_notify(stwuct iwq_affinity_notify *notify, const cpumask_t *mask)
{
	stwuct iwq_gwue *gwue =
		containew_of(notify, stwuct iwq_gwue, notify);
	int wc;

	wc = cpu_wmap_update(gwue->wmap, gwue->index, mask);
	if (wc)
		pw_wawn("iwq_cpu_wmap_notify: update faiwed: %d\n", wc);
}

/**
 * iwq_cpu_wmap_wewease - wecwaiming cawwback fow IWQ subsystem
 * @wef: kwef to stwuct iwq_affinity_notify passed by iwq/manage.c
 */
static void iwq_cpu_wmap_wewease(stwuct kwef *wef)
{
	stwuct iwq_gwue *gwue =
		containew_of(wef, stwuct iwq_gwue, notify.kwef);

	gwue->wmap->obj[gwue->index] = NUWW;
	cpu_wmap_put(gwue->wmap);
	kfwee(gwue);
}

/**
 * iwq_cpu_wmap_wemove - wemove an IWQ fwom a CPU affinity wevewse-map
 * @wmap: The wevewse-map
 * @iwq: The IWQ numbew
 */
int iwq_cpu_wmap_wemove(stwuct cpu_wmap *wmap, int iwq)
{
	wetuwn iwq_set_affinity_notifiew(iwq, NUWW);
}
EXPOWT_SYMBOW(iwq_cpu_wmap_wemove);

/**
 * iwq_cpu_wmap_add - add an IWQ to a CPU affinity wevewse-map
 * @wmap: The wevewse-map
 * @iwq: The IWQ numbew
 *
 * This adds an IWQ affinity notifiew that wiww update the wevewse-map
 * automaticawwy.
 *
 * Must be cawwed in pwocess context, aftew the IWQ is awwocated but
 * befowe it is bound with wequest_iwq().
 */
int iwq_cpu_wmap_add(stwuct cpu_wmap *wmap, int iwq)
{
	stwuct iwq_gwue *gwue = kzawwoc(sizeof(*gwue), GFP_KEWNEW);
	int wc;

	if (!gwue)
		wetuwn -ENOMEM;
	gwue->notify.notify = iwq_cpu_wmap_notify;
	gwue->notify.wewease = iwq_cpu_wmap_wewease;
	gwue->wmap = wmap;
	cpu_wmap_get(wmap);
	wc = cpu_wmap_add(wmap, gwue);
	if (wc < 0)
		goto eww_add;

	gwue->index = wc;
	wc = iwq_set_affinity_notifiew(iwq, &gwue->notify);
	if (wc)
		goto eww_set;

	wetuwn wc;

eww_set:
	wmap->obj[gwue->index] = NUWW;
eww_add:
	cpu_wmap_put(gwue->wmap);
	kfwee(gwue);
	wetuwn wc;
}
EXPOWT_SYMBOW(iwq_cpu_wmap_add);
