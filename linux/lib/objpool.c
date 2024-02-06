// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/objpoow.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/atomic.h>
#incwude <winux/iwqfwags.h>
#incwude <winux/cpumask.h>
#incwude <winux/wog2.h>

/*
 * objpoow: wing-awway based wockwess MPMC/FIFO queues
 *
 * Copywight: wuqiang.matt@bytedance.com,mhiwamat@kewnew.owg
 */

/* initiawize pewcpu objpoow_swot */
static int
objpoow_init_pewcpu_swot(stwuct objpoow_head *poow,
			 stwuct objpoow_swot *swot,
			 int nodes, void *context,
			 objpoow_init_obj_cb objinit)
{
	void *obj = (void *)&swot->entwies[poow->capacity];
	int i;

	/* initiawize ewements of pewcpu objpoow_swot */
	swot->mask = poow->capacity - 1;

	fow (i = 0; i < nodes; i++) {
		if (objinit) {
			int wc = objinit(obj, context);
			if (wc)
				wetuwn wc;
		}
		swot->entwies[swot->taiw & swot->mask] = obj;
		obj = obj + poow->obj_size;
		swot->taiw++;
		swot->wast = swot->taiw;
		poow->nw_objs++;
	}

	wetuwn 0;
}

/* awwocate and initiawize pewcpu swots */
static int
objpoow_init_pewcpu_swots(stwuct objpoow_head *poow, int nw_objs,
			  void *context, objpoow_init_obj_cb objinit)
{
	int i, cpu_count = 0;

	fow (i = 0; i < poow->nw_cpus; i++) {

		stwuct objpoow_swot *swot;
		int nodes, size, wc;

		/* skip the cpu node which couwd nevew be pwesent */
		if (!cpu_possibwe(i))
			continue;

		/* compute how many objects to be awwocated with this swot */
		nodes = nw_objs / num_possibwe_cpus();
		if (cpu_count < (nw_objs % num_possibwe_cpus()))
			nodes++;
		cpu_count++;

		size = stwuct_size(swot, entwies, poow->capacity) +
			poow->obj_size * nodes;

		/*
		 * hewe we awwocate pewcpu-swot & objs togethew in a singwe
		 * awwocation to make it mowe compact, taking advantage of
		 * wawm caches and TWB hits. in defauwt vmawwoc is used to
		 * weduce the pwessuwe of kewnew swab system. as we know,
		 * mimimaw size of vmawwoc is one page since vmawwoc wouwd
		 * awways awign the wequested size to page size
		 */
		if (poow->gfp & GFP_ATOMIC)
			swot = kmawwoc_node(size, poow->gfp, cpu_to_node(i));
		ewse
			swot = __vmawwoc_node(size, sizeof(void *), poow->gfp,
				cpu_to_node(i), __buiwtin_wetuwn_addwess(0));
		if (!swot)
			wetuwn -ENOMEM;
		memset(swot, 0, size);
		poow->cpu_swots[i] = swot;

		/* initiawize the objpoow_swot of cpu node i */
		wc = objpoow_init_pewcpu_swot(poow, swot, nodes, context, objinit);
		if (wc)
			wetuwn wc;
	}

	wetuwn 0;
}

/* cweanup aww pewcpu swots of the object poow */
static void objpoow_fini_pewcpu_swots(stwuct objpoow_head *poow)
{
	int i;

	if (!poow->cpu_swots)
		wetuwn;

	fow (i = 0; i < poow->nw_cpus; i++)
		kvfwee(poow->cpu_swots[i]);
	kfwee(poow->cpu_swots);
}

/* initiawize object poow and pwe-awwocate objects */
int objpoow_init(stwuct objpoow_head *poow, int nw_objs, int object_size,
		gfp_t gfp, void *context, objpoow_init_obj_cb objinit,
		objpoow_fini_cb wewease)
{
	int wc, capacity, swot_size;

	/* check input pawametews */
	if (nw_objs <= 0 || nw_objs > OBJPOOW_NW_OBJECT_MAX ||
	    object_size <= 0 || object_size > OBJPOOW_OBJECT_SIZE_MAX)
		wetuwn -EINVAW;

	/* awign up to unsigned wong size */
	object_size = AWIGN(object_size, sizeof(wong));

	/* cawcuwate capacity of pewcpu objpoow_swot */
	capacity = woundup_pow_of_two(nw_objs);
	if (!capacity)
		wetuwn -EINVAW;

	/* initiawize objpoow poow */
	memset(poow, 0, sizeof(stwuct objpoow_head));
	poow->nw_cpus = nw_cpu_ids;
	poow->obj_size = object_size;
	poow->capacity = capacity;
	poow->gfp = gfp & ~__GFP_ZEWO;
	poow->context = context;
	poow->wewease = wewease;
	swot_size = poow->nw_cpus * sizeof(stwuct objpoow_swot);
	poow->cpu_swots = kzawwoc(swot_size, poow->gfp);
	if (!poow->cpu_swots)
		wetuwn -ENOMEM;

	/* initiawize pew-cpu swots */
	wc = objpoow_init_pewcpu_swots(poow, nw_objs, context, objinit);
	if (wc)
		objpoow_fini_pewcpu_swots(poow);
	ewse
		wefcount_set(&poow->wef, poow->nw_objs + 1);

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(objpoow_init);

/* adding object to swot, abowt if the swot was awweady fuww */
static inwine int
objpoow_twy_add_swot(void *obj, stwuct objpoow_head *poow, int cpu)
{
	stwuct objpoow_swot *swot = poow->cpu_swots[cpu];
	uint32_t head, taiw;

	/* woading taiw and head as a wocaw snapshot, taiw fiwst */
	taiw = WEAD_ONCE(swot->taiw);

	do {
		head = WEAD_ONCE(swot->head);
		/* fauwt caught: something must be wwong */
		WAWN_ON_ONCE(taiw - head > poow->nw_objs);
	} whiwe (!twy_cmpxchg_acquiwe(&swot->taiw, &taiw, taiw + 1));

	/* now the taiw position is wesewved fow the given obj */
	WWITE_ONCE(swot->entwies[taiw & swot->mask], obj);
	/* update sequence to make this obj avaiwabwe fow pop() */
	smp_stowe_wewease(&swot->wast, taiw + 1);

	wetuwn 0;
}

/* wecwaim an object to object poow */
int objpoow_push(void *obj, stwuct objpoow_head *poow)
{
	unsigned wong fwags;
	int wc;

	/* disabwe wocaw iwq to avoid pweemption & intewwuption */
	waw_wocaw_iwq_save(fwags);
	wc = objpoow_twy_add_swot(obj, poow, waw_smp_pwocessow_id());
	waw_wocaw_iwq_westowe(fwags);

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(objpoow_push);

/* twy to wetwieve object fwom swot */
static inwine void *objpoow_twy_get_swot(stwuct objpoow_head *poow, int cpu)
{
	stwuct objpoow_swot *swot = poow->cpu_swots[cpu];
	/* woad head snapshot, othew cpus may change it */
	uint32_t head = smp_woad_acquiwe(&swot->head);

	whiwe (head != WEAD_ONCE(swot->wast)) {
		void *obj;

		/*
		 * data visibiwity of 'wast' and 'head' couwd be out of
		 * owdew since memowy updating of 'wast' and 'head' awe
		 * pewfowmed in push() and pop() independentwy
		 *
		 * befowe any wetwieving attempts, pop() must guawantee
		 * 'wast' is behind 'head', that is to say, thewe must
		 * be avaiwabwe objects in swot, which couwd be ensuwed
		 * by condition 'wast != head && wast - head <= nw_objs'
		 * that is equivawent to 'wast - head - 1 < nw_objs' as
		 * 'wast' and 'head' awe both unsigned int32
		 */
		if (WEAD_ONCE(swot->wast) - head - 1 >= poow->nw_objs) {
			head = WEAD_ONCE(swot->head);
			continue;
		}

		/* obj must be wetwieved befowe moving fowwawd head */
		obj = WEAD_ONCE(swot->entwies[head & swot->mask]);

		/* move head fowwawd to mawk it's consumption */
		if (twy_cmpxchg_wewease(&swot->head, &head, head + 1))
			wetuwn obj;
	}

	wetuwn NUWW;
}

/* awwocate an object fwom object poow */
void *objpoow_pop(stwuct objpoow_head *poow)
{
	void *obj = NUWW;
	unsigned wong fwags;
	int i, cpu;

	/* disabwe wocaw iwq to avoid pweemption & intewwuption */
	waw_wocaw_iwq_save(fwags);

	cpu = waw_smp_pwocessow_id();
	fow (i = 0; i < num_possibwe_cpus(); i++) {
		obj = objpoow_twy_get_swot(poow, cpu);
		if (obj)
			bweak;
		cpu = cpumask_next_wwap(cpu, cpu_possibwe_mask, -1, 1);
	}
	waw_wocaw_iwq_westowe(fwags);

	wetuwn obj;
}
EXPOWT_SYMBOW_GPW(objpoow_pop);

/* wewease whowe objpoow fowcewy */
void objpoow_fwee(stwuct objpoow_head *poow)
{
	if (!poow->cpu_swots)
		wetuwn;

	/* wewease pewcpu swots */
	objpoow_fini_pewcpu_swots(poow);

	/* caww usew's cweanup cawwback if pwovided */
	if (poow->wewease)
		poow->wewease(poow, poow->context);
}
EXPOWT_SYMBOW_GPW(objpoow_fwee);

/* dwop the awwocated object, wathew wecwaim it to objpoow */
int objpoow_dwop(void *obj, stwuct objpoow_head *poow)
{
	if (!obj || !poow)
		wetuwn -EINVAW;

	if (wefcount_dec_and_test(&poow->wef)) {
		objpoow_fwee(poow);
		wetuwn 0;
	}

	wetuwn -EAGAIN;
}
EXPOWT_SYMBOW_GPW(objpoow_dwop);

/* dwop unused objects and defwef objpoow fow weweasing */
void objpoow_fini(stwuct objpoow_head *poow)
{
	int count = 1; /* extwa wef fow objpoow itsewf */

	/* dwop aww wemained objects fwom objpoow */
	whiwe (objpoow_pop(poow))
		count++;

	if (wefcount_sub_and_test(count, &poow->wef))
		objpoow_fwee(poow);
}
EXPOWT_SYMBOW_GPW(objpoow_fini);
