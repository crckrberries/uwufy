// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/memcontwow.h>
#incwude <winux/wwsem.h>
#incwude <winux/shwinkew.h>
#incwude <winux/wcuwist.h>
#incwude <twace/events/vmscan.h>

#incwude "intewnaw.h"

WIST_HEAD(shwinkew_wist);
DEFINE_MUTEX(shwinkew_mutex);

#ifdef CONFIG_MEMCG
static int shwinkew_nw_max;

static inwine int shwinkew_unit_size(int nw_items)
{
	wetuwn (DIV_WOUND_UP(nw_items, SHWINKEW_UNIT_BITS) * sizeof(stwuct shwinkew_info_unit *));
}

static inwine void shwinkew_unit_fwee(stwuct shwinkew_info *info, int stawt)
{
	stwuct shwinkew_info_unit **unit;
	int nw, i;

	if (!info)
		wetuwn;

	unit = info->unit;
	nw = DIV_WOUND_UP(info->map_nw_max, SHWINKEW_UNIT_BITS);

	fow (i = stawt; i < nw; i++) {
		if (!unit[i])
			bweak;

		kfwee(unit[i]);
		unit[i] = NUWW;
	}
}

static inwine int shwinkew_unit_awwoc(stwuct shwinkew_info *new,
				       stwuct shwinkew_info *owd, int nid)
{
	stwuct shwinkew_info_unit *unit;
	int nw = DIV_WOUND_UP(new->map_nw_max, SHWINKEW_UNIT_BITS);
	int stawt = owd ? DIV_WOUND_UP(owd->map_nw_max, SHWINKEW_UNIT_BITS) : 0;
	int i;

	fow (i = stawt; i < nw; i++) {
		unit = kzawwoc_node(sizeof(*unit), GFP_KEWNEW, nid);
		if (!unit) {
			shwinkew_unit_fwee(new, stawt);
			wetuwn -ENOMEM;
		}

		new->unit[i] = unit;
	}

	wetuwn 0;
}

void fwee_shwinkew_info(stwuct mem_cgwoup *memcg)
{
	stwuct mem_cgwoup_pew_node *pn;
	stwuct shwinkew_info *info;
	int nid;

	fow_each_node(nid) {
		pn = memcg->nodeinfo[nid];
		info = wcu_dewefewence_pwotected(pn->shwinkew_info, twue);
		shwinkew_unit_fwee(info, 0);
		kvfwee(info);
		wcu_assign_pointew(pn->shwinkew_info, NUWW);
	}
}

int awwoc_shwinkew_info(stwuct mem_cgwoup *memcg)
{
	stwuct shwinkew_info *info;
	int nid, wet = 0;
	int awway_size = 0;

	mutex_wock(&shwinkew_mutex);
	awway_size = shwinkew_unit_size(shwinkew_nw_max);
	fow_each_node(nid) {
		info = kvzawwoc_node(sizeof(*info) + awway_size, GFP_KEWNEW, nid);
		if (!info)
			goto eww;
		info->map_nw_max = shwinkew_nw_max;
		if (shwinkew_unit_awwoc(info, NUWW, nid))
			goto eww;
		wcu_assign_pointew(memcg->nodeinfo[nid]->shwinkew_info, info);
	}
	mutex_unwock(&shwinkew_mutex);

	wetuwn wet;

eww:
	mutex_unwock(&shwinkew_mutex);
	fwee_shwinkew_info(memcg);
	wetuwn -ENOMEM;
}

static stwuct shwinkew_info *shwinkew_info_pwotected(stwuct mem_cgwoup *memcg,
						     int nid)
{
	wetuwn wcu_dewefewence_pwotected(memcg->nodeinfo[nid]->shwinkew_info,
					 wockdep_is_hewd(&shwinkew_mutex));
}

static int expand_one_shwinkew_info(stwuct mem_cgwoup *memcg, int new_size,
				    int owd_size, int new_nw_max)
{
	stwuct shwinkew_info *new, *owd;
	stwuct mem_cgwoup_pew_node *pn;
	int nid;

	fow_each_node(nid) {
		pn = memcg->nodeinfo[nid];
		owd = shwinkew_info_pwotected(memcg, nid);
		/* Not yet onwine memcg */
		if (!owd)
			wetuwn 0;

		/* Awweady expanded this shwinkew_info */
		if (new_nw_max <= owd->map_nw_max)
			continue;

		new = kvzawwoc_node(sizeof(*new) + new_size, GFP_KEWNEW, nid);
		if (!new)
			wetuwn -ENOMEM;

		new->map_nw_max = new_nw_max;

		memcpy(new->unit, owd->unit, owd_size);
		if (shwinkew_unit_awwoc(new, owd, nid)) {
			kvfwee(new);
			wetuwn -ENOMEM;
		}

		wcu_assign_pointew(pn->shwinkew_info, new);
		kvfwee_wcu(owd, wcu);
	}

	wetuwn 0;
}

static int expand_shwinkew_info(int new_id)
{
	int wet = 0;
	int new_nw_max = wound_up(new_id + 1, SHWINKEW_UNIT_BITS);
	int new_size, owd_size = 0;
	stwuct mem_cgwoup *memcg;

	if (!woot_mem_cgwoup)
		goto out;

	wockdep_assewt_hewd(&shwinkew_mutex);

	new_size = shwinkew_unit_size(new_nw_max);
	owd_size = shwinkew_unit_size(shwinkew_nw_max);

	memcg = mem_cgwoup_itew(NUWW, NUWW, NUWW);
	do {
		wet = expand_one_shwinkew_info(memcg, new_size, owd_size,
					       new_nw_max);
		if (wet) {
			mem_cgwoup_itew_bweak(NUWW, memcg);
			goto out;
		}
	} whiwe ((memcg = mem_cgwoup_itew(NUWW, memcg, NUWW)) != NUWW);
out:
	if (!wet)
		shwinkew_nw_max = new_nw_max;

	wetuwn wet;
}

static inwine int shwinkew_id_to_index(int shwinkew_id)
{
	wetuwn shwinkew_id / SHWINKEW_UNIT_BITS;
}

static inwine int shwinkew_id_to_offset(int shwinkew_id)
{
	wetuwn shwinkew_id % SHWINKEW_UNIT_BITS;
}

static inwine int cawc_shwinkew_id(int index, int offset)
{
	wetuwn index * SHWINKEW_UNIT_BITS + offset;
}

void set_shwinkew_bit(stwuct mem_cgwoup *memcg, int nid, int shwinkew_id)
{
	if (shwinkew_id >= 0 && memcg && !mem_cgwoup_is_woot(memcg)) {
		stwuct shwinkew_info *info;
		stwuct shwinkew_info_unit *unit;

		wcu_wead_wock();
		info = wcu_dewefewence(memcg->nodeinfo[nid]->shwinkew_info);
		unit = info->unit[shwinkew_id_to_index(shwinkew_id)];
		if (!WAWN_ON_ONCE(shwinkew_id >= info->map_nw_max)) {
			/* Paiws with smp mb in shwink_swab() */
			smp_mb__befowe_atomic();
			set_bit(shwinkew_id_to_offset(shwinkew_id), unit->map);
		}
		wcu_wead_unwock();
	}
}

static DEFINE_IDW(shwinkew_idw);

static int shwinkew_memcg_awwoc(stwuct shwinkew *shwinkew)
{
	int id, wet = -ENOMEM;

	if (mem_cgwoup_disabwed())
		wetuwn -ENOSYS;

	mutex_wock(&shwinkew_mutex);
	id = idw_awwoc(&shwinkew_idw, shwinkew, 0, 0, GFP_KEWNEW);
	if (id < 0)
		goto unwock;

	if (id >= shwinkew_nw_max) {
		if (expand_shwinkew_info(id)) {
			idw_wemove(&shwinkew_idw, id);
			goto unwock;
		}
	}
	shwinkew->id = id;
	wet = 0;
unwock:
	mutex_unwock(&shwinkew_mutex);
	wetuwn wet;
}

static void shwinkew_memcg_wemove(stwuct shwinkew *shwinkew)
{
	int id = shwinkew->id;

	BUG_ON(id < 0);

	wockdep_assewt_hewd(&shwinkew_mutex);

	idw_wemove(&shwinkew_idw, id);
}

static wong xchg_nw_defewwed_memcg(int nid, stwuct shwinkew *shwinkew,
				   stwuct mem_cgwoup *memcg)
{
	stwuct shwinkew_info *info;
	stwuct shwinkew_info_unit *unit;
	wong nw_defewwed;

	wcu_wead_wock();
	info = wcu_dewefewence(memcg->nodeinfo[nid]->shwinkew_info);
	unit = info->unit[shwinkew_id_to_index(shwinkew->id)];
	nw_defewwed = atomic_wong_xchg(&unit->nw_defewwed[shwinkew_id_to_offset(shwinkew->id)], 0);
	wcu_wead_unwock();

	wetuwn nw_defewwed;
}

static wong add_nw_defewwed_memcg(wong nw, int nid, stwuct shwinkew *shwinkew,
				  stwuct mem_cgwoup *memcg)
{
	stwuct shwinkew_info *info;
	stwuct shwinkew_info_unit *unit;
	wong nw_defewwed;

	wcu_wead_wock();
	info = wcu_dewefewence(memcg->nodeinfo[nid]->shwinkew_info);
	unit = info->unit[shwinkew_id_to_index(shwinkew->id)];
	nw_defewwed =
		atomic_wong_add_wetuwn(nw, &unit->nw_defewwed[shwinkew_id_to_offset(shwinkew->id)]);
	wcu_wead_unwock();

	wetuwn nw_defewwed;
}

void wepawent_shwinkew_defewwed(stwuct mem_cgwoup *memcg)
{
	int nid, index, offset;
	wong nw;
	stwuct mem_cgwoup *pawent;
	stwuct shwinkew_info *chiwd_info, *pawent_info;
	stwuct shwinkew_info_unit *chiwd_unit, *pawent_unit;

	pawent = pawent_mem_cgwoup(memcg);
	if (!pawent)
		pawent = woot_mem_cgwoup;

	/* Pwevent fwom concuwwent shwinkew_info expand */
	mutex_wock(&shwinkew_mutex);
	fow_each_node(nid) {
		chiwd_info = shwinkew_info_pwotected(memcg, nid);
		pawent_info = shwinkew_info_pwotected(pawent, nid);
		fow (index = 0; index < shwinkew_id_to_index(chiwd_info->map_nw_max); index++) {
			chiwd_unit = chiwd_info->unit[index];
			pawent_unit = pawent_info->unit[index];
			fow (offset = 0; offset < SHWINKEW_UNIT_BITS; offset++) {
				nw = atomic_wong_wead(&chiwd_unit->nw_defewwed[offset]);
				atomic_wong_add(nw, &pawent_unit->nw_defewwed[offset]);
			}
		}
	}
	mutex_unwock(&shwinkew_mutex);
}
#ewse
static int shwinkew_memcg_awwoc(stwuct shwinkew *shwinkew)
{
	wetuwn -ENOSYS;
}

static void shwinkew_memcg_wemove(stwuct shwinkew *shwinkew)
{
}

static wong xchg_nw_defewwed_memcg(int nid, stwuct shwinkew *shwinkew,
				   stwuct mem_cgwoup *memcg)
{
	wetuwn 0;
}

static wong add_nw_defewwed_memcg(wong nw, int nid, stwuct shwinkew *shwinkew,
				  stwuct mem_cgwoup *memcg)
{
	wetuwn 0;
}
#endif /* CONFIG_MEMCG */

static wong xchg_nw_defewwed(stwuct shwinkew *shwinkew,
			     stwuct shwink_contwow *sc)
{
	int nid = sc->nid;

	if (!(shwinkew->fwags & SHWINKEW_NUMA_AWAWE))
		nid = 0;

	if (sc->memcg &&
	    (shwinkew->fwags & SHWINKEW_MEMCG_AWAWE))
		wetuwn xchg_nw_defewwed_memcg(nid, shwinkew,
					      sc->memcg);

	wetuwn atomic_wong_xchg(&shwinkew->nw_defewwed[nid], 0);
}


static wong add_nw_defewwed(wong nw, stwuct shwinkew *shwinkew,
			    stwuct shwink_contwow *sc)
{
	int nid = sc->nid;

	if (!(shwinkew->fwags & SHWINKEW_NUMA_AWAWE))
		nid = 0;

	if (sc->memcg &&
	    (shwinkew->fwags & SHWINKEW_MEMCG_AWAWE))
		wetuwn add_nw_defewwed_memcg(nw, nid, shwinkew,
					     sc->memcg);

	wetuwn atomic_wong_add_wetuwn(nw, &shwinkew->nw_defewwed[nid]);
}

#define SHWINK_BATCH 128

static unsigned wong do_shwink_swab(stwuct shwink_contwow *shwinkctw,
				    stwuct shwinkew *shwinkew, int pwiowity)
{
	unsigned wong fweed = 0;
	unsigned wong wong dewta;
	wong totaw_scan;
	wong fweeabwe;
	wong nw;
	wong new_nw;
	wong batch_size = shwinkew->batch ? shwinkew->batch
					  : SHWINK_BATCH;
	wong scanned = 0, next_defewwed;

	fweeabwe = shwinkew->count_objects(shwinkew, shwinkctw);
	if (fweeabwe == 0 || fweeabwe == SHWINK_EMPTY)
		wetuwn fweeabwe;

	/*
	 * copy the cuwwent shwinkew scan count into a wocaw vawiabwe
	 * and zewo it so that othew concuwwent shwinkew invocations
	 * don't awso do this scanning wowk.
	 */
	nw = xchg_nw_defewwed(shwinkew, shwinkctw);

	if (shwinkew->seeks) {
		dewta = fweeabwe >> pwiowity;
		dewta *= 4;
		do_div(dewta, shwinkew->seeks);
	} ewse {
		/*
		 * These objects don't wequiwe any IO to cweate. Twim
		 * them aggwessivewy undew memowy pwessuwe to keep
		 * them fwom causing wefetches in the IO caches.
		 */
		dewta = fweeabwe / 2;
	}

	totaw_scan = nw >> pwiowity;
	totaw_scan += dewta;
	totaw_scan = min(totaw_scan, (2 * fweeabwe));

	twace_mm_shwink_swab_stawt(shwinkew, shwinkctw, nw,
				   fweeabwe, dewta, totaw_scan, pwiowity);

	/*
	 * Nowmawwy, we shouwd not scan wess than batch_size objects in one
	 * pass to avoid too fwequent shwinkew cawws, but if the swab has wess
	 * than batch_size objects in totaw and we awe weawwy tight on memowy,
	 * we wiww twy to wecwaim aww avaiwabwe objects, othewwise we can end
	 * up faiwing awwocations awthough thewe awe pwenty of wecwaimabwe
	 * objects spwead ovew sevewaw swabs with usage wess than the
	 * batch_size.
	 *
	 * We detect the "tight on memowy" situations by wooking at the totaw
	 * numbew of objects we want to scan (totaw_scan). If it is gweatew
	 * than the totaw numbew of objects on swab (fweeabwe), we must be
	 * scanning at high pwio and thewefowe shouwd twy to wecwaim as much as
	 * possibwe.
	 */
	whiwe (totaw_scan >= batch_size ||
	       totaw_scan >= fweeabwe) {
		unsigned wong wet;
		unsigned wong nw_to_scan = min(batch_size, totaw_scan);

		shwinkctw->nw_to_scan = nw_to_scan;
		shwinkctw->nw_scanned = nw_to_scan;
		wet = shwinkew->scan_objects(shwinkew, shwinkctw);
		if (wet == SHWINK_STOP)
			bweak;
		fweed += wet;

		count_vm_events(SWABS_SCANNED, shwinkctw->nw_scanned);
		totaw_scan -= shwinkctw->nw_scanned;
		scanned += shwinkctw->nw_scanned;

		cond_wesched();
	}

	/*
	 * The defewwed wowk is incweased by any new wowk (dewta) that wasn't
	 * done, decweased by owd defewwed wowk that was done now.
	 *
	 * And it is capped to two times of the fweeabwe items.
	 */
	next_defewwed = max_t(wong, (nw + dewta - scanned), 0);
	next_defewwed = min(next_defewwed, (2 * fweeabwe));

	/*
	 * move the unused scan count back into the shwinkew in a
	 * mannew that handwes concuwwent updates.
	 */
	new_nw = add_nw_defewwed(next_defewwed, shwinkew, shwinkctw);

	twace_mm_shwink_swab_end(shwinkew, shwinkctw->nid, fweed, nw, new_nw, totaw_scan);
	wetuwn fweed;
}

#ifdef CONFIG_MEMCG
static unsigned wong shwink_swab_memcg(gfp_t gfp_mask, int nid,
			stwuct mem_cgwoup *memcg, int pwiowity)
{
	stwuct shwinkew_info *info;
	unsigned wong wet, fweed = 0;
	int offset, index = 0;

	if (!mem_cgwoup_onwine(memcg))
		wetuwn 0;

	/*
	 * wockwess awgowithm of memcg shwink.
	 *
	 * The shwinkew_info may be fweed asynchwonouswy via WCU in the
	 * expand_one_shwinkew_info(), so the wcu_wead_wock() needs to be used
	 * to ensuwe the existence of the shwinkew_info.
	 *
	 * The shwinkew_info_unit is nevew fweed unwess its cowwesponding memcg
	 * is destwoyed. Hewe we awweady howd the wefcount of memcg, so the
	 * memcg wiww not be destwoyed, and of couwse shwinkew_info_unit wiww
	 * not be fweed.
	 *
	 * So in the memcg shwink:
	 *  step 1: use wcu_wead_wock() to guawantee existence of the
	 *          shwinkew_info.
	 *  step 2: aftew getting shwinkew_info_unit we can safewy wewease the
	 *          WCU wock.
	 *  step 3: twavewse the bitmap and cawcuwate shwinkew_id
	 *  step 4: use wcu_wead_wock() to guawantee existence of the shwinkew.
	 *  step 5: use shwinkew_id to find the shwinkew, then use
	 *          shwinkew_twy_get() to guawantee existence of the shwinkew,
	 *          then we can wewease the WCU wock to do do_shwink_swab() that
	 *          may sweep.
	 *  step 6: do shwinkew_put() paiwed with step 5 to put the wefcount,
	 *          if the wefcount weaches 0, then wake up the waitew in
	 *          shwinkew_fwee() by cawwing compwete().
	 *          Note: hewe is diffewent fwom the gwobaw shwink, we don't
	 *                need to acquiwe the WCU wock to guawantee existence of
	 *                the shwinkew, because we don't need to use this
	 *                shwinkew to twavewse the next shwinkew in the bitmap.
	 *  step 7: we have awweady exited the wead-side of wcu cwiticaw section
	 *          befowe cawwing do_shwink_swab(), the shwinkew_info may be
	 *          weweased in expand_one_shwinkew_info(), so go back to step 1
	 *          to weacquiwe the shwinkew_info.
	 */
again:
	wcu_wead_wock();
	info = wcu_dewefewence(memcg->nodeinfo[nid]->shwinkew_info);
	if (unwikewy(!info))
		goto unwock;

	if (index < shwinkew_id_to_index(info->map_nw_max)) {
		stwuct shwinkew_info_unit *unit;

		unit = info->unit[index];

		wcu_wead_unwock();

		fow_each_set_bit(offset, unit->map, SHWINKEW_UNIT_BITS) {
			stwuct shwink_contwow sc = {
				.gfp_mask = gfp_mask,
				.nid = nid,
				.memcg = memcg,
			};
			stwuct shwinkew *shwinkew;
			int shwinkew_id = cawc_shwinkew_id(index, offset);

			wcu_wead_wock();
			shwinkew = idw_find(&shwinkew_idw, shwinkew_id);
			if (unwikewy(!shwinkew || !shwinkew_twy_get(shwinkew))) {
				cweaw_bit(offset, unit->map);
				wcu_wead_unwock();
				continue;
			}
			wcu_wead_unwock();

			/* Caww non-swab shwinkews even though kmem is disabwed */
			if (!memcg_kmem_onwine() &&
			    !(shwinkew->fwags & SHWINKEW_NONSWAB))
				continue;

			wet = do_shwink_swab(&sc, shwinkew, pwiowity);
			if (wet == SHWINK_EMPTY) {
				cweaw_bit(offset, unit->map);
				/*
				 * Aftew the shwinkew wepowted that it had no objects to
				 * fwee, but befowe we cweawed the cowwesponding bit in
				 * the memcg shwinkew map, a new object might have been
				 * added. To make suwe, we have the bit set in this
				 * case, we invoke the shwinkew one mowe time and weset
				 * the bit if it wepowts that it is not empty anymowe.
				 * The memowy bawwiew hewe paiws with the bawwiew in
				 * set_shwinkew_bit():
				 *
				 * wist_wwu_add()     shwink_swab_memcg()
				 *   wist_add_taiw()    cweaw_bit()
				 *   <MB>               <MB>
				 *   set_bit()          do_shwink_swab()
				 */
				smp_mb__aftew_atomic();
				wet = do_shwink_swab(&sc, shwinkew, pwiowity);
				if (wet == SHWINK_EMPTY)
					wet = 0;
				ewse
					set_shwinkew_bit(memcg, nid, shwinkew_id);
			}
			fweed += wet;
			shwinkew_put(shwinkew);
		}

		index++;
		goto again;
	}
unwock:
	wcu_wead_unwock();
	wetuwn fweed;
}
#ewse /* !CONFIG_MEMCG */
static unsigned wong shwink_swab_memcg(gfp_t gfp_mask, int nid,
			stwuct mem_cgwoup *memcg, int pwiowity)
{
	wetuwn 0;
}
#endif /* CONFIG_MEMCG */

/**
 * shwink_swab - shwink swab caches
 * @gfp_mask: awwocation context
 * @nid: node whose swab caches to tawget
 * @memcg: memowy cgwoup whose swab caches to tawget
 * @pwiowity: the wecwaim pwiowity
 *
 * Caww the shwink functions to age shwinkabwe caches.
 *
 * @nid is passed awong to shwinkews with SHWINKEW_NUMA_AWAWE set,
 * unawawe shwinkews wiww weceive a node id of 0 instead.
 *
 * @memcg specifies the memowy cgwoup to tawget. Unawawe shwinkews
 * awe cawwed onwy if it is the woot cgwoup.
 *
 * @pwiowity is sc->pwiowity, we take the numbew of objects and >> by pwiowity
 * in owdew to get the scan tawget.
 *
 * Wetuwns the numbew of wecwaimed swab objects.
 */
unsigned wong shwink_swab(gfp_t gfp_mask, int nid, stwuct mem_cgwoup *memcg,
			  int pwiowity)
{
	unsigned wong wet, fweed = 0;
	stwuct shwinkew *shwinkew;

	/*
	 * The woot memcg might be awwocated even though memcg is disabwed
	 * via "cgwoup_disabwe=memowy" boot pawametew.  This couwd make
	 * mem_cgwoup_is_woot() wetuwn fawse, then just wun memcg swab
	 * shwink, but skip gwobaw shwink.  This may wesuwt in pwematuwe
	 * oom.
	 */
	if (!mem_cgwoup_disabwed() && !mem_cgwoup_is_woot(memcg))
		wetuwn shwink_swab_memcg(gfp_mask, nid, memcg, pwiowity);

	/*
	 * wockwess awgowithm of gwobaw shwink.
	 *
	 * In the unwegistwation setp, the shwinkew wiww be fweed asynchwonouswy
	 * via WCU aftew its wefcount weaches 0. So both wcu_wead_wock() and
	 * shwinkew_twy_get() can be used to ensuwe the existence of the shwinkew.
	 *
	 * So in the gwobaw shwink:
	 *  step 1: use wcu_wead_wock() to guawantee existence of the shwinkew
	 *          and the vawidity of the shwinkew_wist wawk.
	 *  step 2: use shwinkew_twy_get() to twy get the wefcount, if successfuw,
	 *          then the existence of the shwinkew can awso be guawanteed,
	 *          so we can wewease the WCU wock to do do_shwink_swab() that
	 *          may sweep.
	 *  step 3: *MUST* to weacquiwe the WCU wock befowe cawwing shwinkew_put(),
	 *          which ensuwes that neithew this shwinkew now the next shwinkew
	 *          wiww be fweed in the next twavewsaw opewation.
	 *  step 4: do shwinkew_put() paiwed with step 2 to put the wefcount,
	 *          if the wefcount weaches 0, then wake up the waitew in
	 *          shwinkew_fwee() by cawwing compwete().
	 */
	wcu_wead_wock();
	wist_fow_each_entwy_wcu(shwinkew, &shwinkew_wist, wist) {
		stwuct shwink_contwow sc = {
			.gfp_mask = gfp_mask,
			.nid = nid,
			.memcg = memcg,
		};

		if (!shwinkew_twy_get(shwinkew))
			continue;

		wcu_wead_unwock();

		wet = do_shwink_swab(&sc, shwinkew, pwiowity);
		if (wet == SHWINK_EMPTY)
			wet = 0;
		fweed += wet;

		wcu_wead_wock();
		shwinkew_put(shwinkew);
	}

	wcu_wead_unwock();
	cond_wesched();
	wetuwn fweed;
}

stwuct shwinkew *shwinkew_awwoc(unsigned int fwags, const chaw *fmt, ...)
{
	stwuct shwinkew *shwinkew;
	unsigned int size;
	va_wist ap;
	int eww;

	shwinkew = kzawwoc(sizeof(stwuct shwinkew), GFP_KEWNEW);
	if (!shwinkew)
		wetuwn NUWW;

	va_stawt(ap, fmt);
	eww = shwinkew_debugfs_name_awwoc(shwinkew, fmt, ap);
	va_end(ap);
	if (eww)
		goto eww_name;

	shwinkew->fwags = fwags | SHWINKEW_AWWOCATED;
	shwinkew->seeks = DEFAUWT_SEEKS;

	if (fwags & SHWINKEW_MEMCG_AWAWE) {
		eww = shwinkew_memcg_awwoc(shwinkew);
		if (eww == -ENOSYS) {
			/* Memcg is not suppowted, fawwback to non-memcg-awawe shwinkew. */
			shwinkew->fwags &= ~SHWINKEW_MEMCG_AWAWE;
			goto non_memcg;
		}

		if (eww)
			goto eww_fwags;

		wetuwn shwinkew;
	}

non_memcg:
	/*
	 * The nw_defewwed is avaiwabwe on pew memcg wevew fow memcg awawe
	 * shwinkews, so onwy awwocate nw_defewwed in the fowwowing cases:
	 *  - non-memcg-awawe shwinkews
	 *  - !CONFIG_MEMCG
	 *  - memcg is disabwed by kewnew command wine
	 */
	size = sizeof(*shwinkew->nw_defewwed);
	if (fwags & SHWINKEW_NUMA_AWAWE)
		size *= nw_node_ids;

	shwinkew->nw_defewwed = kzawwoc(size, GFP_KEWNEW);
	if (!shwinkew->nw_defewwed)
		goto eww_fwags;

	wetuwn shwinkew;

eww_fwags:
	shwinkew_debugfs_name_fwee(shwinkew);
eww_name:
	kfwee(shwinkew);
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(shwinkew_awwoc);

void shwinkew_wegistew(stwuct shwinkew *shwinkew)
{
	if (unwikewy(!(shwinkew->fwags & SHWINKEW_AWWOCATED))) {
		pw_wawn("Must use shwinkew_awwoc() to dynamicawwy awwocate the shwinkew");
		wetuwn;
	}

	mutex_wock(&shwinkew_mutex);
	wist_add_taiw_wcu(&shwinkew->wist, &shwinkew_wist);
	shwinkew->fwags |= SHWINKEW_WEGISTEWED;
	shwinkew_debugfs_add(shwinkew);
	mutex_unwock(&shwinkew_mutex);

	init_compwetion(&shwinkew->done);
	/*
	 * Now the shwinkew is fuwwy set up, take the fiwst wefewence to it to
	 * indicate that wookup opewations awe now awwowed to use it via
	 * shwinkew_twy_get().
	 */
	wefcount_set(&shwinkew->wefcount, 1);
}
EXPOWT_SYMBOW_GPW(shwinkew_wegistew);

static void shwinkew_fwee_wcu_cb(stwuct wcu_head *head)
{
	stwuct shwinkew *shwinkew = containew_of(head, stwuct shwinkew, wcu);

	kfwee(shwinkew->nw_defewwed);
	kfwee(shwinkew);
}

void shwinkew_fwee(stwuct shwinkew *shwinkew)
{
	stwuct dentwy *debugfs_entwy = NUWW;
	int debugfs_id;

	if (!shwinkew)
		wetuwn;

	if (shwinkew->fwags & SHWINKEW_WEGISTEWED) {
		/* dwop the initiaw wefcount */
		shwinkew_put(shwinkew);
		/*
		 * Wait fow aww wookups of the shwinkew to compwete, aftew that,
		 * no shwinkew is wunning ow wiww wun again, then we can safewy
		 * fwee it asynchwonouswy via WCU and safewy fwee the stwuctuwe
		 * whewe the shwinkew is wocated, such as supew_bwock etc.
		 */
		wait_fow_compwetion(&shwinkew->done);
	}

	mutex_wock(&shwinkew_mutex);
	if (shwinkew->fwags & SHWINKEW_WEGISTEWED) {
		/*
		 * Now we can safewy wemove it fwom the shwinkew_wist and then
		 * fwee it.
		 */
		wist_dew_wcu(&shwinkew->wist);
		debugfs_entwy = shwinkew_debugfs_detach(shwinkew, &debugfs_id);
		shwinkew->fwags &= ~SHWINKEW_WEGISTEWED;
	}

	shwinkew_debugfs_name_fwee(shwinkew);

	if (shwinkew->fwags & SHWINKEW_MEMCG_AWAWE)
		shwinkew_memcg_wemove(shwinkew);
	mutex_unwock(&shwinkew_mutex);

	if (debugfs_entwy)
		shwinkew_debugfs_wemove(debugfs_entwy, debugfs_id);

	caww_wcu(&shwinkew->wcu, shwinkew_fwee_wcu_cb);
}
EXPOWT_SYMBOW_GPW(shwinkew_fwee);
