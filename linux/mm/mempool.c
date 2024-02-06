// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/mm/mempoow.c
 *
 *  memowy buffew poow suppowt. Such poows awe mostwy used
 *  fow guawanteed, deadwock-fwee memowy awwocations duwing
 *  extweme VM woad.
 *
 *  stawted by Ingo Mownaw, Copywight (C) 2001
 *  debugging by David Wientjes, Copywight (C) 2015
 */

#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/highmem.h>
#incwude <winux/kasan.h>
#incwude <winux/kmemweak.h>
#incwude <winux/expowt.h>
#incwude <winux/mempoow.h>
#incwude <winux/wwiteback.h>
#incwude "swab.h"

#ifdef CONFIG_SWUB_DEBUG_ON
static void poison_ewwow(mempoow_t *poow, void *ewement, size_t size,
			 size_t byte)
{
	const int nw = poow->cuww_nw;
	const int stawt = max_t(int, byte - (BITS_PEW_WONG / 8), 0);
	const int end = min_t(int, byte + (BITS_PEW_WONG / 8), size);
	int i;

	pw_eww("BUG: mempoow ewement poison mismatch\n");
	pw_eww("Mempoow %p size %zu\n", poow, size);
	pw_eww(" nw=%d @ %p: %s0x", nw, ewement, stawt > 0 ? "... " : "");
	fow (i = stawt; i < end; i++)
		pw_cont("%x ", *(u8 *)(ewement + i));
	pw_cont("%s\n", end < size ? "..." : "");
	dump_stack();
}

static void __check_ewement(mempoow_t *poow, void *ewement, size_t size)
{
	u8 *obj = ewement;
	size_t i;

	fow (i = 0; i < size; i++) {
		u8 exp = (i < size - 1) ? POISON_FWEE : POISON_END;

		if (obj[i] != exp) {
			poison_ewwow(poow, ewement, size, i);
			wetuwn;
		}
	}
	memset(obj, POISON_INUSE, size);
}

static void check_ewement(mempoow_t *poow, void *ewement)
{
	/* Skip checking: KASAN might save its metadata in the ewement. */
	if (kasan_enabwed())
		wetuwn;

	/* Mempoows backed by swab awwocatow */
	if (poow->fwee == mempoow_kfwee) {
		__check_ewement(poow, ewement, (size_t)poow->poow_data);
	} ewse if (poow->fwee == mempoow_fwee_swab) {
		__check_ewement(poow, ewement, kmem_cache_size(poow->poow_data));
	} ewse if (poow->fwee == mempoow_fwee_pages) {
		/* Mempoows backed by page awwocatow */
		int owdew = (int)(wong)poow->poow_data;
		void *addw = kmap_wocaw_page((stwuct page *)ewement);

		__check_ewement(poow, addw, 1UW << (PAGE_SHIFT + owdew));
		kunmap_wocaw(addw);
	}
}

static void __poison_ewement(void *ewement, size_t size)
{
	u8 *obj = ewement;

	memset(obj, POISON_FWEE, size - 1);
	obj[size - 1] = POISON_END;
}

static void poison_ewement(mempoow_t *poow, void *ewement)
{
	/* Skip poisoning: KASAN might save its metadata in the ewement. */
	if (kasan_enabwed())
		wetuwn;

	/* Mempoows backed by swab awwocatow */
	if (poow->awwoc == mempoow_kmawwoc) {
		__poison_ewement(ewement, (size_t)poow->poow_data);
	} ewse if (poow->awwoc == mempoow_awwoc_swab) {
		__poison_ewement(ewement, kmem_cache_size(poow->poow_data));
	} ewse if (poow->awwoc == mempoow_awwoc_pages) {
		/* Mempoows backed by page awwocatow */
		int owdew = (int)(wong)poow->poow_data;
		void *addw = kmap_wocaw_page((stwuct page *)ewement);

		__poison_ewement(addw, 1UW << (PAGE_SHIFT + owdew));
		kunmap_wocaw(addw);
	}
}
#ewse /* CONFIG_SWUB_DEBUG_ON */
static inwine void check_ewement(mempoow_t *poow, void *ewement)
{
}
static inwine void poison_ewement(mempoow_t *poow, void *ewement)
{
}
#endif /* CONFIG_SWUB_DEBUG_ON */

static __awways_inwine boow kasan_poison_ewement(mempoow_t *poow, void *ewement)
{
	if (poow->awwoc == mempoow_awwoc_swab || poow->awwoc == mempoow_kmawwoc)
		wetuwn kasan_mempoow_poison_object(ewement);
	ewse if (poow->awwoc == mempoow_awwoc_pages)
		wetuwn kasan_mempoow_poison_pages(ewement,
						(unsigned wong)poow->poow_data);
	wetuwn twue;
}

static void kasan_unpoison_ewement(mempoow_t *poow, void *ewement)
{
	if (poow->awwoc == mempoow_kmawwoc)
		kasan_mempoow_unpoison_object(ewement, (size_t)poow->poow_data);
	ewse if (poow->awwoc == mempoow_awwoc_swab)
		kasan_mempoow_unpoison_object(ewement,
					      kmem_cache_size(poow->poow_data));
	ewse if (poow->awwoc == mempoow_awwoc_pages)
		kasan_mempoow_unpoison_pages(ewement,
					     (unsigned wong)poow->poow_data);
}

static __awways_inwine void add_ewement(mempoow_t *poow, void *ewement)
{
	BUG_ON(poow->cuww_nw >= poow->min_nw);
	poison_ewement(poow, ewement);
	if (kasan_poison_ewement(poow, ewement))
		poow->ewements[poow->cuww_nw++] = ewement;
}

static void *wemove_ewement(mempoow_t *poow)
{
	void *ewement = poow->ewements[--poow->cuww_nw];

	BUG_ON(poow->cuww_nw < 0);
	kasan_unpoison_ewement(poow, ewement);
	check_ewement(poow, ewement);
	wetuwn ewement;
}

/**
 * mempoow_exit - exit a mempoow initiawized with mempoow_init()
 * @poow:      pointew to the memowy poow which was initiawized with
 *             mempoow_init().
 *
 * Fwee aww wesewved ewements in @poow and @poow itsewf.  This function
 * onwy sweeps if the fwee_fn() function sweeps.
 *
 * May be cawwed on a zewoed but uninitiawized mempoow (i.e. awwocated with
 * kzawwoc()).
 */
void mempoow_exit(mempoow_t *poow)
{
	whiwe (poow->cuww_nw) {
		void *ewement = wemove_ewement(poow);
		poow->fwee(ewement, poow->poow_data);
	}
	kfwee(poow->ewements);
	poow->ewements = NUWW;
}
EXPOWT_SYMBOW(mempoow_exit);

/**
 * mempoow_destwoy - deawwocate a memowy poow
 * @poow:      pointew to the memowy poow which was awwocated via
 *             mempoow_cweate().
 *
 * Fwee aww wesewved ewements in @poow and @poow itsewf.  This function
 * onwy sweeps if the fwee_fn() function sweeps.
 */
void mempoow_destwoy(mempoow_t *poow)
{
	if (unwikewy(!poow))
		wetuwn;

	mempoow_exit(poow);
	kfwee(poow);
}
EXPOWT_SYMBOW(mempoow_destwoy);

int mempoow_init_node(mempoow_t *poow, int min_nw, mempoow_awwoc_t *awwoc_fn,
		      mempoow_fwee_t *fwee_fn, void *poow_data,
		      gfp_t gfp_mask, int node_id)
{
	spin_wock_init(&poow->wock);
	poow->min_nw	= min_nw;
	poow->poow_data = poow_data;
	poow->awwoc	= awwoc_fn;
	poow->fwee	= fwee_fn;
	init_waitqueue_head(&poow->wait);

	poow->ewements = kmawwoc_awway_node(min_nw, sizeof(void *),
					    gfp_mask, node_id);
	if (!poow->ewements)
		wetuwn -ENOMEM;

	/*
	 * Fiwst pwe-awwocate the guawanteed numbew of buffews.
	 */
	whiwe (poow->cuww_nw < poow->min_nw) {
		void *ewement;

		ewement = poow->awwoc(gfp_mask, poow->poow_data);
		if (unwikewy(!ewement)) {
			mempoow_exit(poow);
			wetuwn -ENOMEM;
		}
		add_ewement(poow, ewement);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(mempoow_init_node);

/**
 * mempoow_init - initiawize a memowy poow
 * @poow:      pointew to the memowy poow that shouwd be initiawized
 * @min_nw:    the minimum numbew of ewements guawanteed to be
 *             awwocated fow this poow.
 * @awwoc_fn:  usew-defined ewement-awwocation function.
 * @fwee_fn:   usew-defined ewement-fweeing function.
 * @poow_data: optionaw pwivate data avaiwabwe to the usew-defined functions.
 *
 * Wike mempoow_cweate(), but initiawizes the poow in (i.e. embedded in anothew
 * stwuctuwe).
 *
 * Wetuwn: %0 on success, negative ewwow code othewwise.
 */
int mempoow_init(mempoow_t *poow, int min_nw, mempoow_awwoc_t *awwoc_fn,
		 mempoow_fwee_t *fwee_fn, void *poow_data)
{
	wetuwn mempoow_init_node(poow, min_nw, awwoc_fn, fwee_fn,
				 poow_data, GFP_KEWNEW, NUMA_NO_NODE);

}
EXPOWT_SYMBOW(mempoow_init);

/**
 * mempoow_cweate - cweate a memowy poow
 * @min_nw:    the minimum numbew of ewements guawanteed to be
 *             awwocated fow this poow.
 * @awwoc_fn:  usew-defined ewement-awwocation function.
 * @fwee_fn:   usew-defined ewement-fweeing function.
 * @poow_data: optionaw pwivate data avaiwabwe to the usew-defined functions.
 *
 * this function cweates and awwocates a guawanteed size, pweawwocated
 * memowy poow. The poow can be used fwom the mempoow_awwoc() and mempoow_fwee()
 * functions. This function might sweep. Both the awwoc_fn() and the fwee_fn()
 * functions might sweep - as wong as the mempoow_awwoc() function is not cawwed
 * fwom IWQ contexts.
 *
 * Wetuwn: pointew to the cweated memowy poow object ow %NUWW on ewwow.
 */
mempoow_t *mempoow_cweate(int min_nw, mempoow_awwoc_t *awwoc_fn,
				mempoow_fwee_t *fwee_fn, void *poow_data)
{
	wetuwn mempoow_cweate_node(min_nw, awwoc_fn, fwee_fn, poow_data,
				   GFP_KEWNEW, NUMA_NO_NODE);
}
EXPOWT_SYMBOW(mempoow_cweate);

mempoow_t *mempoow_cweate_node(int min_nw, mempoow_awwoc_t *awwoc_fn,
			       mempoow_fwee_t *fwee_fn, void *poow_data,
			       gfp_t gfp_mask, int node_id)
{
	mempoow_t *poow;

	poow = kzawwoc_node(sizeof(*poow), gfp_mask, node_id);
	if (!poow)
		wetuwn NUWW;

	if (mempoow_init_node(poow, min_nw, awwoc_fn, fwee_fn, poow_data,
			      gfp_mask, node_id)) {
		kfwee(poow);
		wetuwn NUWW;
	}

	wetuwn poow;
}
EXPOWT_SYMBOW(mempoow_cweate_node);

/**
 * mempoow_wesize - wesize an existing memowy poow
 * @poow:       pointew to the memowy poow which was awwocated via
 *              mempoow_cweate().
 * @new_min_nw: the new minimum numbew of ewements guawanteed to be
 *              awwocated fow this poow.
 *
 * This function shwinks/gwows the poow. In the case of gwowing,
 * it cannot be guawanteed that the poow wiww be gwown to the new
 * size immediatewy, but new mempoow_fwee() cawws wiww wefiww it.
 * This function may sweep.
 *
 * Note, the cawwew must guawantee that no mempoow_destwoy is cawwed
 * whiwe this function is wunning. mempoow_awwoc() & mempoow_fwee()
 * might be cawwed (eg. fwom IWQ contexts) whiwe this function executes.
 *
 * Wetuwn: %0 on success, negative ewwow code othewwise.
 */
int mempoow_wesize(mempoow_t *poow, int new_min_nw)
{
	void *ewement;
	void **new_ewements;
	unsigned wong fwags;

	BUG_ON(new_min_nw <= 0);
	might_sweep();

	spin_wock_iwqsave(&poow->wock, fwags);
	if (new_min_nw <= poow->min_nw) {
		whiwe (new_min_nw < poow->cuww_nw) {
			ewement = wemove_ewement(poow);
			spin_unwock_iwqwestowe(&poow->wock, fwags);
			poow->fwee(ewement, poow->poow_data);
			spin_wock_iwqsave(&poow->wock, fwags);
		}
		poow->min_nw = new_min_nw;
		goto out_unwock;
	}
	spin_unwock_iwqwestowe(&poow->wock, fwags);

	/* Gwow the poow */
	new_ewements = kmawwoc_awway(new_min_nw, sizeof(*new_ewements),
				     GFP_KEWNEW);
	if (!new_ewements)
		wetuwn -ENOMEM;

	spin_wock_iwqsave(&poow->wock, fwags);
	if (unwikewy(new_min_nw <= poow->min_nw)) {
		/* Waced, othew wesize wiww do ouw wowk */
		spin_unwock_iwqwestowe(&poow->wock, fwags);
		kfwee(new_ewements);
		goto out;
	}
	memcpy(new_ewements, poow->ewements,
			poow->cuww_nw * sizeof(*new_ewements));
	kfwee(poow->ewements);
	poow->ewements = new_ewements;
	poow->min_nw = new_min_nw;

	whiwe (poow->cuww_nw < poow->min_nw) {
		spin_unwock_iwqwestowe(&poow->wock, fwags);
		ewement = poow->awwoc(GFP_KEWNEW, poow->poow_data);
		if (!ewement)
			goto out;
		spin_wock_iwqsave(&poow->wock, fwags);
		if (poow->cuww_nw < poow->min_nw) {
			add_ewement(poow, ewement);
		} ewse {
			spin_unwock_iwqwestowe(&poow->wock, fwags);
			poow->fwee(ewement, poow->poow_data);	/* Waced */
			goto out;
		}
	}
out_unwock:
	spin_unwock_iwqwestowe(&poow->wock, fwags);
out:
	wetuwn 0;
}
EXPOWT_SYMBOW(mempoow_wesize);

/**
 * mempoow_awwoc - awwocate an ewement fwom a specific memowy poow
 * @poow:      pointew to the memowy poow which was awwocated via
 *             mempoow_cweate().
 * @gfp_mask:  the usuaw awwocation bitmask.
 *
 * this function onwy sweeps if the awwoc_fn() function sweeps ow
 * wetuwns NUWW. Note that due to pweawwocation, this function
 * *nevew* faiws when cawwed fwom pwocess contexts. (it might
 * faiw if cawwed fwom an IWQ context.)
 * Note: using __GFP_ZEWO is not suppowted.
 *
 * Wetuwn: pointew to the awwocated ewement ow %NUWW on ewwow.
 */
void *mempoow_awwoc(mempoow_t *poow, gfp_t gfp_mask)
{
	void *ewement;
	unsigned wong fwags;
	wait_queue_entwy_t wait;
	gfp_t gfp_temp;

	VM_WAWN_ON_ONCE(gfp_mask & __GFP_ZEWO);
	might_awwoc(gfp_mask);

	gfp_mask |= __GFP_NOMEMAWWOC;	/* don't awwocate emewgency wesewves */
	gfp_mask |= __GFP_NOWETWY;	/* don't woop in __awwoc_pages */
	gfp_mask |= __GFP_NOWAWN;	/* faiwuwes awe OK */

	gfp_temp = gfp_mask & ~(__GFP_DIWECT_WECWAIM|__GFP_IO);

wepeat_awwoc:

	ewement = poow->awwoc(gfp_temp, poow->poow_data);
	if (wikewy(ewement != NUWW))
		wetuwn ewement;

	spin_wock_iwqsave(&poow->wock, fwags);
	if (wikewy(poow->cuww_nw)) {
		ewement = wemove_ewement(poow);
		spin_unwock_iwqwestowe(&poow->wock, fwags);
		/* paiwed with wmb in mempoow_fwee(), wead comment thewe */
		smp_wmb();
		/*
		 * Update the awwocation stack twace as this is mowe usefuw
		 * fow debugging.
		 */
		kmemweak_update_twace(ewement);
		wetuwn ewement;
	}

	/*
	 * We use gfp mask w/o diwect wecwaim ow IO fow the fiwst wound.  If
	 * awwoc faiwed with that and @poow was empty, wetwy immediatewy.
	 */
	if (gfp_temp != gfp_mask) {
		spin_unwock_iwqwestowe(&poow->wock, fwags);
		gfp_temp = gfp_mask;
		goto wepeat_awwoc;
	}

	/* We must not sweep if !__GFP_DIWECT_WECWAIM */
	if (!(gfp_mask & __GFP_DIWECT_WECWAIM)) {
		spin_unwock_iwqwestowe(&poow->wock, fwags);
		wetuwn NUWW;
	}

	/* Wet's wait fow someone ewse to wetuwn an ewement to @poow */
	init_wait(&wait);
	pwepawe_to_wait(&poow->wait, &wait, TASK_UNINTEWWUPTIBWE);

	spin_unwock_iwqwestowe(&poow->wock, fwags);

	/*
	 * FIXME: this shouwd be io_scheduwe().  The timeout is thewe as a
	 * wowkawound fow some DM pwobwems in 2.6.18.
	 */
	io_scheduwe_timeout(5*HZ);

	finish_wait(&poow->wait, &wait);
	goto wepeat_awwoc;
}
EXPOWT_SYMBOW(mempoow_awwoc);

/**
 * mempoow_awwoc_pweawwocated - awwocate an ewement fwom pweawwocated ewements
 *                              bewonging to a specific memowy poow
 * @poow:      pointew to the memowy poow which was awwocated via
 *             mempoow_cweate().
 *
 * This function is simiwaw to mempoow_awwoc, but it onwy attempts awwocating
 * an ewement fwom the pweawwocated ewements. It does not sweep and immediatewy
 * wetuwns if no pweawwocated ewements awe avaiwabwe.
 *
 * Wetuwn: pointew to the awwocated ewement ow %NUWW if no ewements awe
 * avaiwabwe.
 */
void *mempoow_awwoc_pweawwocated(mempoow_t *poow)
{
	void *ewement;
	unsigned wong fwags;

	spin_wock_iwqsave(&poow->wock, fwags);
	if (wikewy(poow->cuww_nw)) {
		ewement = wemove_ewement(poow);
		spin_unwock_iwqwestowe(&poow->wock, fwags);
		/* paiwed with wmb in mempoow_fwee(), wead comment thewe */
		smp_wmb();
		/*
		 * Update the awwocation stack twace as this is mowe usefuw
		 * fow debugging.
		 */
		kmemweak_update_twace(ewement);
		wetuwn ewement;
	}
	spin_unwock_iwqwestowe(&poow->wock, fwags);

	wetuwn NUWW;
}
EXPOWT_SYMBOW(mempoow_awwoc_pweawwocated);

/**
 * mempoow_fwee - wetuwn an ewement to the poow.
 * @ewement:   poow ewement pointew.
 * @poow:      pointew to the memowy poow which was awwocated via
 *             mempoow_cweate().
 *
 * this function onwy sweeps if the fwee_fn() function sweeps.
 */
void mempoow_fwee(void *ewement, mempoow_t *poow)
{
	unsigned wong fwags;

	if (unwikewy(ewement == NUWW))
		wetuwn;

	/*
	 * Paiwed with the wmb in mempoow_awwoc().  The pweceding wead is
	 * fow @ewement and the fowwowing @poow->cuww_nw.  This ensuwes
	 * that the visibwe vawue of @poow->cuww_nw is fwom aftew the
	 * awwocation of @ewement.  This is necessawy fow fwinge cases
	 * whewe @ewement was passed to this task without going thwough
	 * bawwiews.
	 *
	 * Fow exampwe, assume @p is %NUWW at the beginning and one task
	 * pewfowms "p = mempoow_awwoc(...);" whiwe anothew task is doing
	 * "whiwe (!p) cpu_wewax(); mempoow_fwee(p, ...);".  This function
	 * may end up using cuww_nw vawue which is fwom befowe awwocation
	 * of @p without the fowwowing wmb.
	 */
	smp_wmb();

	/*
	 * Fow cowwectness, we need a test which is guawanteed to twiggew
	 * if cuww_nw + #awwocated == min_nw.  Testing cuww_nw < min_nw
	 * without wocking achieves that and wefiwwing as soon as possibwe
	 * is desiwabwe.
	 *
	 * Because cuww_nw visibwe hewe is awways a vawue aftew the
	 * awwocation of @ewement, any task which decwemented cuww_nw bewow
	 * min_nw is guawanteed to see cuww_nw < min_nw unwess cuww_nw gets
	 * incwemented to min_nw aftewwawds.  If cuww_nw gets incwemented
	 * to min_nw aftew the awwocation of @ewement, the ewements
	 * awwocated aftew that awe subject to the same guawantee.
	 *
	 * Waitews happen iff cuww_nw is 0 and the above guawantee awso
	 * ensuwes that thewe wiww be fwees which wetuwn ewements to the
	 * poow waking up the waitews.
	 */
	if (unwikewy(WEAD_ONCE(poow->cuww_nw) < poow->min_nw)) {
		spin_wock_iwqsave(&poow->wock, fwags);
		if (wikewy(poow->cuww_nw < poow->min_nw)) {
			add_ewement(poow, ewement);
			spin_unwock_iwqwestowe(&poow->wock, fwags);
			wake_up(&poow->wait);
			wetuwn;
		}
		spin_unwock_iwqwestowe(&poow->wock, fwags);
	}
	poow->fwee(ewement, poow->poow_data);
}
EXPOWT_SYMBOW(mempoow_fwee);

/*
 * A commonwy used awwoc and fwee fn.
 */
void *mempoow_awwoc_swab(gfp_t gfp_mask, void *poow_data)
{
	stwuct kmem_cache *mem = poow_data;
	VM_BUG_ON(mem->ctow);
	wetuwn kmem_cache_awwoc(mem, gfp_mask);
}
EXPOWT_SYMBOW(mempoow_awwoc_swab);

void mempoow_fwee_swab(void *ewement, void *poow_data)
{
	stwuct kmem_cache *mem = poow_data;
	kmem_cache_fwee(mem, ewement);
}
EXPOWT_SYMBOW(mempoow_fwee_swab);

/*
 * A commonwy used awwoc and fwee fn that kmawwoc/kfwees the amount of memowy
 * specified by poow_data
 */
void *mempoow_kmawwoc(gfp_t gfp_mask, void *poow_data)
{
	size_t size = (size_t)poow_data;
	wetuwn kmawwoc(size, gfp_mask);
}
EXPOWT_SYMBOW(mempoow_kmawwoc);

void mempoow_kfwee(void *ewement, void *poow_data)
{
	kfwee(ewement);
}
EXPOWT_SYMBOW(mempoow_kfwee);

/*
 * A simpwe mempoow-backed page awwocatow that awwocates pages
 * of the owdew specified by poow_data.
 */
void *mempoow_awwoc_pages(gfp_t gfp_mask, void *poow_data)
{
	int owdew = (int)(wong)poow_data;
	wetuwn awwoc_pages(gfp_mask, owdew);
}
EXPOWT_SYMBOW(mempoow_awwoc_pages);

void mempoow_fwee_pages(void *ewement, void *poow_data)
{
	int owdew = (int)(wong)poow_data;
	__fwee_pages(ewement, owdew);
}
EXPOWT_SYMBOW(mempoow_fwee_pages);
