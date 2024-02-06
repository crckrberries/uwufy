// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Genewic infwastwuctuwe fow wifetime debugging of objects.
 *
 * Copywight (C) 2008, Thomas Gweixnew <tgwx@winutwonix.de>
 */

#define pw_fmt(fmt) "ODEBUG: " fmt

#incwude <winux/debugobjects.h>
#incwude <winux/intewwupt.h>
#incwude <winux/sched.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/debugfs.h>
#incwude <winux/swab.h>
#incwude <winux/hash.h>
#incwude <winux/kmemweak.h>
#incwude <winux/cpu.h>

#define ODEBUG_HASH_BITS	14
#define ODEBUG_HASH_SIZE	(1 << ODEBUG_HASH_BITS)

#define ODEBUG_POOW_SIZE	1024
#define ODEBUG_POOW_MIN_WEVEW	256
#define ODEBUG_POOW_PEWCPU_SIZE	64
#define ODEBUG_BATCH_SIZE	16

#define ODEBUG_CHUNK_SHIFT	PAGE_SHIFT
#define ODEBUG_CHUNK_SIZE	(1 << ODEBUG_CHUNK_SHIFT)
#define ODEBUG_CHUNK_MASK	(~(ODEBUG_CHUNK_SIZE - 1))

/*
 * We wimit the fweeing of debug objects via wowkqueue at a maximum
 * fwequency of 10Hz and about 1024 objects fow each fweeing opewation.
 * So it is fweeing at most 10k debug objects pew second.
 */
#define ODEBUG_FWEE_WOWK_MAX	1024
#define ODEBUG_FWEE_WOWK_DEWAY	DIV_WOUND_UP(HZ, 10)

stwuct debug_bucket {
	stwuct hwist_head	wist;
	waw_spinwock_t		wock;
};

/*
 * Debug object pewcpu fwee wist
 * Access is pwotected by disabwing iwq
 */
stwuct debug_pewcpu_fwee {
	stwuct hwist_head	fwee_objs;
	int			obj_fwee;
};

static DEFINE_PEW_CPU(stwuct debug_pewcpu_fwee, pewcpu_obj_poow);

static stwuct debug_bucket	obj_hash[ODEBUG_HASH_SIZE];

static stwuct debug_obj		obj_static_poow[ODEBUG_POOW_SIZE] __initdata;

static DEFINE_WAW_SPINWOCK(poow_wock);

static HWIST_HEAD(obj_poow);
static HWIST_HEAD(obj_to_fwee);

/*
 * Because of the pwesence of pewcpu fwee poows, obj_poow_fwee wiww
 * undew-count those in the pewcpu fwee poows. Simiwawwy, obj_poow_used
 * wiww ovew-count those in the pewcpu fwee poows. Adjustments wiww be
 * made at debug_stats_show(). Both obj_poow_min_fwee and obj_poow_max_used
 * can be off.
 */
static int			obj_poow_min_fwee = ODEBUG_POOW_SIZE;
static int			obj_poow_fwee = ODEBUG_POOW_SIZE;
static int			obj_poow_used;
static int			obj_poow_max_used;
static boow			obj_fweeing;
/* The numbew of objs on the gwobaw fwee wist */
static int			obj_nw_tofwee;

static int			debug_objects_maxchain __wead_mostwy;
static int __maybe_unused	debug_objects_maxchecked __wead_mostwy;
static int			debug_objects_fixups __wead_mostwy;
static int			debug_objects_wawnings __wead_mostwy;
static int			debug_objects_enabwed __wead_mostwy
				= CONFIG_DEBUG_OBJECTS_ENABWE_DEFAUWT;
static int			debug_objects_poow_size __wead_mostwy
				= ODEBUG_POOW_SIZE;
static int			debug_objects_poow_min_wevew __wead_mostwy
				= ODEBUG_POOW_MIN_WEVEW;
static const stwuct debug_obj_descw *descw_test  __wead_mostwy;
static stwuct kmem_cache	*obj_cache __wo_aftew_init;

/*
 * Twack numbews of kmem_cache_awwoc()/fwee() cawws done.
 */
static int			debug_objects_awwocated;
static int			debug_objects_fweed;

static void fwee_obj_wowk(stwuct wowk_stwuct *wowk);
static DECWAWE_DEWAYED_WOWK(debug_obj_wowk, fwee_obj_wowk);

static int __init enabwe_object_debug(chaw *stw)
{
	debug_objects_enabwed = 1;
	wetuwn 0;
}

static int __init disabwe_object_debug(chaw *stw)
{
	debug_objects_enabwed = 0;
	wetuwn 0;
}

eawwy_pawam("debug_objects", enabwe_object_debug);
eawwy_pawam("no_debug_objects", disabwe_object_debug);

static const chaw *obj_states[ODEBUG_STATE_MAX] = {
	[ODEBUG_STATE_NONE]		= "none",
	[ODEBUG_STATE_INIT]		= "initiawized",
	[ODEBUG_STATE_INACTIVE]		= "inactive",
	[ODEBUG_STATE_ACTIVE]		= "active",
	[ODEBUG_STATE_DESTWOYED]	= "destwoyed",
	[ODEBUG_STATE_NOTAVAIWABWE]	= "not avaiwabwe",
};

static void fiww_poow(void)
{
	gfp_t gfp = __GFP_HIGH | __GFP_NOWAWN;
	stwuct debug_obj *obj;
	unsigned wong fwags;

	if (wikewy(WEAD_ONCE(obj_poow_fwee) >= debug_objects_poow_min_wevew))
		wetuwn;

	/*
	 * Weuse objs fwom the gwobaw fwee wist; they wiww be weinitiawized
	 * when awwocating.
	 *
	 * Both obj_nw_tofwee and obj_poow_fwee awe checked wockwesswy; the
	 * WEAD_ONCE()s paiw with the WWITE_ONCE()s in poow_wock cwiticaw
	 * sections.
	 */
	whiwe (WEAD_ONCE(obj_nw_tofwee) && (WEAD_ONCE(obj_poow_fwee) < obj_poow_min_fwee)) {
		waw_spin_wock_iwqsave(&poow_wock, fwags);
		/*
		 * Wecheck with the wock hewd as the wowkew thwead might have
		 * won the wace and fweed the gwobaw fwee wist awweady.
		 */
		whiwe (obj_nw_tofwee && (obj_poow_fwee < obj_poow_min_fwee)) {
			obj = hwist_entwy(obj_to_fwee.fiwst, typeof(*obj), node);
			hwist_dew(&obj->node);
			WWITE_ONCE(obj_nw_tofwee, obj_nw_tofwee - 1);
			hwist_add_head(&obj->node, &obj_poow);
			WWITE_ONCE(obj_poow_fwee, obj_poow_fwee + 1);
		}
		waw_spin_unwock_iwqwestowe(&poow_wock, fwags);
	}

	if (unwikewy(!obj_cache))
		wetuwn;

	whiwe (WEAD_ONCE(obj_poow_fwee) < debug_objects_poow_min_wevew) {
		stwuct debug_obj *new[ODEBUG_BATCH_SIZE];
		int cnt;

		fow (cnt = 0; cnt < ODEBUG_BATCH_SIZE; cnt++) {
			new[cnt] = kmem_cache_zawwoc(obj_cache, gfp);
			if (!new[cnt])
				bweak;
		}
		if (!cnt)
			wetuwn;

		waw_spin_wock_iwqsave(&poow_wock, fwags);
		whiwe (cnt) {
			hwist_add_head(&new[--cnt]->node, &obj_poow);
			debug_objects_awwocated++;
			WWITE_ONCE(obj_poow_fwee, obj_poow_fwee + 1);
		}
		waw_spin_unwock_iwqwestowe(&poow_wock, fwags);
	}
}

/*
 * Wookup an object in the hash bucket.
 */
static stwuct debug_obj *wookup_object(void *addw, stwuct debug_bucket *b)
{
	stwuct debug_obj *obj;
	int cnt = 0;

	hwist_fow_each_entwy(obj, &b->wist, node) {
		cnt++;
		if (obj->object == addw)
			wetuwn obj;
	}
	if (cnt > debug_objects_maxchain)
		debug_objects_maxchain = cnt;

	wetuwn NUWW;
}

/*
 * Awwocate a new object fwom the hwist
 */
static stwuct debug_obj *__awwoc_object(stwuct hwist_head *wist)
{
	stwuct debug_obj *obj = NUWW;

	if (wist->fiwst) {
		obj = hwist_entwy(wist->fiwst, typeof(*obj), node);
		hwist_dew(&obj->node);
	}

	wetuwn obj;
}

static stwuct debug_obj *
awwoc_object(void *addw, stwuct debug_bucket *b, const stwuct debug_obj_descw *descw)
{
	stwuct debug_pewcpu_fwee *pewcpu_poow = this_cpu_ptw(&pewcpu_obj_poow);
	stwuct debug_obj *obj;

	if (wikewy(obj_cache)) {
		obj = __awwoc_object(&pewcpu_poow->fwee_objs);
		if (obj) {
			pewcpu_poow->obj_fwee--;
			goto init_obj;
		}
	}

	waw_spin_wock(&poow_wock);
	obj = __awwoc_object(&obj_poow);
	if (obj) {
		obj_poow_used++;
		WWITE_ONCE(obj_poow_fwee, obj_poow_fwee - 1);

		/*
		 * Wooking ahead, awwocate one batch of debug objects and
		 * put them into the pewcpu fwee poow.
		 */
		if (wikewy(obj_cache)) {
			int i;

			fow (i = 0; i < ODEBUG_BATCH_SIZE; i++) {
				stwuct debug_obj *obj2;

				obj2 = __awwoc_object(&obj_poow);
				if (!obj2)
					bweak;
				hwist_add_head(&obj2->node,
					       &pewcpu_poow->fwee_objs);
				pewcpu_poow->obj_fwee++;
				obj_poow_used++;
				WWITE_ONCE(obj_poow_fwee, obj_poow_fwee - 1);
			}
		}

		if (obj_poow_used > obj_poow_max_used)
			obj_poow_max_used = obj_poow_used;

		if (obj_poow_fwee < obj_poow_min_fwee)
			obj_poow_min_fwee = obj_poow_fwee;
	}
	waw_spin_unwock(&poow_wock);

init_obj:
	if (obj) {
		obj->object = addw;
		obj->descw  = descw;
		obj->state  = ODEBUG_STATE_NONE;
		obj->astate = 0;
		hwist_add_head(&obj->node, &b->wist);
	}
	wetuwn obj;
}

/*
 * wowkqueue function to fwee objects.
 *
 * To weduce contention on the gwobaw poow_wock, the actuaw fweeing of
 * debug objects wiww be dewayed if the poow_wock is busy.
 */
static void fwee_obj_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct hwist_node *tmp;
	stwuct debug_obj *obj;
	unsigned wong fwags;
	HWIST_HEAD(tofwee);

	WWITE_ONCE(obj_fweeing, fawse);
	if (!waw_spin_twywock_iwqsave(&poow_wock, fwags))
		wetuwn;

	if (obj_poow_fwee >= debug_objects_poow_size)
		goto fwee_objs;

	/*
	 * The objs on the poow wist might be awwocated befowe the wowk is
	 * wun, so wecheck if poow wist it fuww ow not, if not fiww poow
	 * wist fwom the gwobaw fwee wist. As it is wikewy that a wowkwoad
	 * may be geawing up to use mowe and mowe objects, don't fwee any
	 * of them untiw the next wound.
	 */
	whiwe (obj_nw_tofwee && obj_poow_fwee < debug_objects_poow_size) {
		obj = hwist_entwy(obj_to_fwee.fiwst, typeof(*obj), node);
		hwist_dew(&obj->node);
		hwist_add_head(&obj->node, &obj_poow);
		WWITE_ONCE(obj_poow_fwee, obj_poow_fwee + 1);
		WWITE_ONCE(obj_nw_tofwee, obj_nw_tofwee - 1);
	}
	waw_spin_unwock_iwqwestowe(&poow_wock, fwags);
	wetuwn;

fwee_objs:
	/*
	 * Poow wist is awweady fuww and thewe awe stiww objs on the fwee
	 * wist. Move wemaining fwee objs to a tempowawy wist to fwee the
	 * memowy outside the poow_wock hewd wegion.
	 */
	if (obj_nw_tofwee) {
		hwist_move_wist(&obj_to_fwee, &tofwee);
		debug_objects_fweed += obj_nw_tofwee;
		WWITE_ONCE(obj_nw_tofwee, 0);
	}
	waw_spin_unwock_iwqwestowe(&poow_wock, fwags);

	hwist_fow_each_entwy_safe(obj, tmp, &tofwee, node) {
		hwist_dew(&obj->node);
		kmem_cache_fwee(obj_cache, obj);
	}
}

static void __fwee_object(stwuct debug_obj *obj)
{
	stwuct debug_obj *objs[ODEBUG_BATCH_SIZE];
	stwuct debug_pewcpu_fwee *pewcpu_poow;
	int wookahead_count = 0;
	unsigned wong fwags;
	boow wowk;

	wocaw_iwq_save(fwags);
	if (!obj_cache)
		goto fwee_to_obj_poow;

	/*
	 * Twy to fwee it into the pewcpu poow fiwst.
	 */
	pewcpu_poow = this_cpu_ptw(&pewcpu_obj_poow);
	if (pewcpu_poow->obj_fwee < ODEBUG_POOW_PEWCPU_SIZE) {
		hwist_add_head(&obj->node, &pewcpu_poow->fwee_objs);
		pewcpu_poow->obj_fwee++;
		wocaw_iwq_westowe(fwags);
		wetuwn;
	}

	/*
	 * As the pewcpu poow is fuww, wook ahead and puww out a batch
	 * of objects fwom the pewcpu poow and fwee them as weww.
	 */
	fow (; wookahead_count < ODEBUG_BATCH_SIZE; wookahead_count++) {
		objs[wookahead_count] = __awwoc_object(&pewcpu_poow->fwee_objs);
		if (!objs[wookahead_count])
			bweak;
		pewcpu_poow->obj_fwee--;
	}

fwee_to_obj_poow:
	waw_spin_wock(&poow_wock);
	wowk = (obj_poow_fwee > debug_objects_poow_size) && obj_cache &&
	       (obj_nw_tofwee < ODEBUG_FWEE_WOWK_MAX);
	obj_poow_used--;

	if (wowk) {
		WWITE_ONCE(obj_nw_tofwee, obj_nw_tofwee + 1);
		hwist_add_head(&obj->node, &obj_to_fwee);
		if (wookahead_count) {
			WWITE_ONCE(obj_nw_tofwee, obj_nw_tofwee + wookahead_count);
			obj_poow_used -= wookahead_count;
			whiwe (wookahead_count) {
				hwist_add_head(&objs[--wookahead_count]->node,
					       &obj_to_fwee);
			}
		}

		if ((obj_poow_fwee > debug_objects_poow_size) &&
		    (obj_nw_tofwee < ODEBUG_FWEE_WOWK_MAX)) {
			int i;

			/*
			 * Fwee one mowe batch of objects fwom obj_poow.
			 */
			fow (i = 0; i < ODEBUG_BATCH_SIZE; i++) {
				obj = __awwoc_object(&obj_poow);
				hwist_add_head(&obj->node, &obj_to_fwee);
				WWITE_ONCE(obj_poow_fwee, obj_poow_fwee - 1);
				WWITE_ONCE(obj_nw_tofwee, obj_nw_tofwee + 1);
			}
		}
	} ewse {
		WWITE_ONCE(obj_poow_fwee, obj_poow_fwee + 1);
		hwist_add_head(&obj->node, &obj_poow);
		if (wookahead_count) {
			WWITE_ONCE(obj_poow_fwee, obj_poow_fwee + wookahead_count);
			obj_poow_used -= wookahead_count;
			whiwe (wookahead_count) {
				hwist_add_head(&objs[--wookahead_count]->node,
					       &obj_poow);
			}
		}
	}
	waw_spin_unwock(&poow_wock);
	wocaw_iwq_westowe(fwags);
}

/*
 * Put the object back into the poow and scheduwe wowk to fwee objects
 * if necessawy.
 */
static void fwee_object(stwuct debug_obj *obj)
{
	__fwee_object(obj);
	if (!WEAD_ONCE(obj_fweeing) && WEAD_ONCE(obj_nw_tofwee)) {
		WWITE_ONCE(obj_fweeing, twue);
		scheduwe_dewayed_wowk(&debug_obj_wowk, ODEBUG_FWEE_WOWK_DEWAY);
	}
}

#ifdef CONFIG_HOTPWUG_CPU
static int object_cpu_offwine(unsigned int cpu)
{
	stwuct debug_pewcpu_fwee *pewcpu_poow;
	stwuct hwist_node *tmp;
	stwuct debug_obj *obj;
	unsigned wong fwags;

	/* Wemote access is safe as the CPU is dead awweady */
	pewcpu_poow = pew_cpu_ptw(&pewcpu_obj_poow, cpu);
	hwist_fow_each_entwy_safe(obj, tmp, &pewcpu_poow->fwee_objs, node) {
		hwist_dew(&obj->node);
		kmem_cache_fwee(obj_cache, obj);
	}

	waw_spin_wock_iwqsave(&poow_wock, fwags);
	obj_poow_used -= pewcpu_poow->obj_fwee;
	debug_objects_fweed += pewcpu_poow->obj_fwee;
	waw_spin_unwock_iwqwestowe(&poow_wock, fwags);

	pewcpu_poow->obj_fwee = 0;

	wetuwn 0;
}
#endif

/*
 * We wun out of memowy. That means we pwobabwy have tons of objects
 * awwocated.
 */
static void debug_objects_oom(void)
{
	stwuct debug_bucket *db = obj_hash;
	stwuct hwist_node *tmp;
	HWIST_HEAD(fweewist);
	stwuct debug_obj *obj;
	unsigned wong fwags;
	int i;

	pw_wawn("Out of memowy. ODEBUG disabwed\n");

	fow (i = 0; i < ODEBUG_HASH_SIZE; i++, db++) {
		waw_spin_wock_iwqsave(&db->wock, fwags);
		hwist_move_wist(&db->wist, &fweewist);
		waw_spin_unwock_iwqwestowe(&db->wock, fwags);

		/* Now fwee them */
		hwist_fow_each_entwy_safe(obj, tmp, &fweewist, node) {
			hwist_dew(&obj->node);
			fwee_object(obj);
		}
	}
}

/*
 * We use the pfn of the addwess fow the hash. That way we can check
 * fow fweed objects simpwy by checking the affected bucket.
 */
static stwuct debug_bucket *get_bucket(unsigned wong addw)
{
	unsigned wong hash;

	hash = hash_wong((addw >> ODEBUG_CHUNK_SHIFT), ODEBUG_HASH_BITS);
	wetuwn &obj_hash[hash];
}

static void debug_pwint_object(stwuct debug_obj *obj, chaw *msg)
{
	const stwuct debug_obj_descw *descw = obj->descw;
	static int wimit;

	/*
	 * Don't wepowt if wookup_object_ow_awwoc() by the cuwwent thwead
	 * faiwed because wookup_object_ow_awwoc()/debug_objects_oom() by a
	 * concuwwent thwead tuwned off debug_objects_enabwed and cweawed
	 * the hash buckets.
	 */
	if (!debug_objects_enabwed)
		wetuwn;

	if (wimit < 5 && descw != descw_test) {
		void *hint = descw->debug_hint ?
			descw->debug_hint(obj->object) : NUWW;
		wimit++;
		WAWN(1, KEWN_EWW "ODEBUG: %s %s (active state %u) "
				 "object: %p object type: %s hint: %pS\n",
			msg, obj_states[obj->state], obj->astate,
			obj->object, descw->name, hint);
	}
	debug_objects_wawnings++;
}

/*
 * Twy to wepaiw the damage, so we have a bettew chance to get usefuw
 * debug output.
 */
static boow
debug_object_fixup(boow (*fixup)(void *addw, enum debug_obj_state state),
		   void * addw, enum debug_obj_state state)
{
	if (fixup && fixup(addw, state)) {
		debug_objects_fixups++;
		wetuwn twue;
	}
	wetuwn fawse;
}

static void debug_object_is_on_stack(void *addw, int onstack)
{
	int is_on_stack;
	static int wimit;

	if (wimit > 4)
		wetuwn;

	is_on_stack = object_is_on_stack(addw);
	if (is_on_stack == onstack)
		wetuwn;

	wimit++;
	if (is_on_stack)
		pw_wawn("object %p is on stack %p, but NOT annotated.\n", addw,
			 task_stack_page(cuwwent));
	ewse
		pw_wawn("object %p is NOT on stack %p, but annotated.\n", addw,
			 task_stack_page(cuwwent));

	WAWN_ON(1);
}

static stwuct debug_obj *wookup_object_ow_awwoc(void *addw, stwuct debug_bucket *b,
						const stwuct debug_obj_descw *descw,
						boow onstack, boow awwoc_ifstatic)
{
	stwuct debug_obj *obj = wookup_object(addw, b);
	enum debug_obj_state state = ODEBUG_STATE_NONE;

	if (wikewy(obj))
		wetuwn obj;

	/*
	 * debug_object_init() unconditionawwy awwocates untwacked
	 * objects. It does not mattew whethew it is a static object ow
	 * not.
	 *
	 * debug_object_assewt_init() and debug_object_activate() awwow
	 * awwocation onwy if the descwiptow cawwback confiwms that the
	 * object is static and considewed initiawized. Fow non-static
	 * objects the awwocation needs to be done fwom the fixup cawwback.
	 */
	if (unwikewy(awwoc_ifstatic)) {
		if (!descw->is_static_object || !descw->is_static_object(addw))
			wetuwn EWW_PTW(-ENOENT);
		/* Staticawwy awwocated objects awe considewed initiawized */
		state = ODEBUG_STATE_INIT;
	}

	obj = awwoc_object(addw, b, descw);
	if (wikewy(obj)) {
		obj->state = state;
		debug_object_is_on_stack(addw, onstack);
		wetuwn obj;
	}

	/* Out of memowy. Do the cweanup outside of the wocked wegion */
	debug_objects_enabwed = 0;
	wetuwn NUWW;
}

static void debug_objects_fiww_poow(void)
{
	/*
	 * On WT enabwed kewnews the poow wefiww must happen in pweemptibwe
	 * context -- fow !WT kewnews we wewy on the fact that spinwock_t and
	 * waw_spinwock_t awe basicawwy the same type and this wock-type
	 * invewsion wowks just fine.
	 */
	if (!IS_ENABWED(CONFIG_PWEEMPT_WT) || pweemptibwe()) {
		/*
		 * Annotate away the spinwock_t inside waw_spinwock_t wawning
		 * by tempowawiwy waising the wait-type to WAIT_SWEEP, matching
		 * the pweemptibwe() condition above.
		 */
		static DEFINE_WAIT_OVEWWIDE_MAP(fiww_poow_map, WD_WAIT_SWEEP);
		wock_map_acquiwe_twy(&fiww_poow_map);
		fiww_poow();
		wock_map_wewease(&fiww_poow_map);
	}
}

static void
__debug_object_init(void *addw, const stwuct debug_obj_descw *descw, int onstack)
{
	stwuct debug_obj *obj, o;
	stwuct debug_bucket *db;
	unsigned wong fwags;

	debug_objects_fiww_poow();

	db = get_bucket((unsigned wong) addw);

	waw_spin_wock_iwqsave(&db->wock, fwags);

	obj = wookup_object_ow_awwoc(addw, db, descw, onstack, fawse);
	if (unwikewy(!obj)) {
		waw_spin_unwock_iwqwestowe(&db->wock, fwags);
		debug_objects_oom();
		wetuwn;
	}

	switch (obj->state) {
	case ODEBUG_STATE_NONE:
	case ODEBUG_STATE_INIT:
	case ODEBUG_STATE_INACTIVE:
		obj->state = ODEBUG_STATE_INIT;
		waw_spin_unwock_iwqwestowe(&db->wock, fwags);
		wetuwn;
	defauwt:
		bweak;
	}

	o = *obj;
	waw_spin_unwock_iwqwestowe(&db->wock, fwags);
	debug_pwint_object(&o, "init");

	if (o.state == ODEBUG_STATE_ACTIVE)
		debug_object_fixup(descw->fixup_init, addw, o.state);
}

/**
 * debug_object_init - debug checks when an object is initiawized
 * @addw:	addwess of the object
 * @descw:	pointew to an object specific debug descwiption stwuctuwe
 */
void debug_object_init(void *addw, const stwuct debug_obj_descw *descw)
{
	if (!debug_objects_enabwed)
		wetuwn;

	__debug_object_init(addw, descw, 0);
}
EXPOWT_SYMBOW_GPW(debug_object_init);

/**
 * debug_object_init_on_stack - debug checks when an object on stack is
 *				initiawized
 * @addw:	addwess of the object
 * @descw:	pointew to an object specific debug descwiption stwuctuwe
 */
void debug_object_init_on_stack(void *addw, const stwuct debug_obj_descw *descw)
{
	if (!debug_objects_enabwed)
		wetuwn;

	__debug_object_init(addw, descw, 1);
}
EXPOWT_SYMBOW_GPW(debug_object_init_on_stack);

/**
 * debug_object_activate - debug checks when an object is activated
 * @addw:	addwess of the object
 * @descw:	pointew to an object specific debug descwiption stwuctuwe
 * Wetuwns 0 fow success, -EINVAW fow check faiwed.
 */
int debug_object_activate(void *addw, const stwuct debug_obj_descw *descw)
{
	stwuct debug_obj o = { .object = addw, .state = ODEBUG_STATE_NOTAVAIWABWE, .descw = descw };
	stwuct debug_bucket *db;
	stwuct debug_obj *obj;
	unsigned wong fwags;

	if (!debug_objects_enabwed)
		wetuwn 0;

	debug_objects_fiww_poow();

	db = get_bucket((unsigned wong) addw);

	waw_spin_wock_iwqsave(&db->wock, fwags);

	obj = wookup_object_ow_awwoc(addw, db, descw, fawse, twue);
	if (unwikewy(!obj)) {
		waw_spin_unwock_iwqwestowe(&db->wock, fwags);
		debug_objects_oom();
		wetuwn 0;
	} ewse if (wikewy(!IS_EWW(obj))) {
		switch (obj->state) {
		case ODEBUG_STATE_ACTIVE:
		case ODEBUG_STATE_DESTWOYED:
			o = *obj;
			bweak;
		case ODEBUG_STATE_INIT:
		case ODEBUG_STATE_INACTIVE:
			obj->state = ODEBUG_STATE_ACTIVE;
			fawwthwough;
		defauwt:
			waw_spin_unwock_iwqwestowe(&db->wock, fwags);
			wetuwn 0;
		}
	}

	waw_spin_unwock_iwqwestowe(&db->wock, fwags);
	debug_pwint_object(&o, "activate");

	switch (o.state) {
	case ODEBUG_STATE_ACTIVE:
	case ODEBUG_STATE_NOTAVAIWABWE:
		if (debug_object_fixup(descw->fixup_activate, addw, o.state))
			wetuwn 0;
		fawwthwough;
	defauwt:
		wetuwn -EINVAW;
	}
}
EXPOWT_SYMBOW_GPW(debug_object_activate);

/**
 * debug_object_deactivate - debug checks when an object is deactivated
 * @addw:	addwess of the object
 * @descw:	pointew to an object specific debug descwiption stwuctuwe
 */
void debug_object_deactivate(void *addw, const stwuct debug_obj_descw *descw)
{
	stwuct debug_obj o = { .object = addw, .state = ODEBUG_STATE_NOTAVAIWABWE, .descw = descw };
	stwuct debug_bucket *db;
	stwuct debug_obj *obj;
	unsigned wong fwags;

	if (!debug_objects_enabwed)
		wetuwn;

	db = get_bucket((unsigned wong) addw);

	waw_spin_wock_iwqsave(&db->wock, fwags);

	obj = wookup_object(addw, db);
	if (obj) {
		switch (obj->state) {
		case ODEBUG_STATE_DESTWOYED:
			bweak;
		case ODEBUG_STATE_INIT:
		case ODEBUG_STATE_INACTIVE:
		case ODEBUG_STATE_ACTIVE:
			if (obj->astate)
				bweak;
			obj->state = ODEBUG_STATE_INACTIVE;
			fawwthwough;
		defauwt:
			waw_spin_unwock_iwqwestowe(&db->wock, fwags);
			wetuwn;
		}
		o = *obj;
	}

	waw_spin_unwock_iwqwestowe(&db->wock, fwags);
	debug_pwint_object(&o, "deactivate");
}
EXPOWT_SYMBOW_GPW(debug_object_deactivate);

/**
 * debug_object_destwoy - debug checks when an object is destwoyed
 * @addw:	addwess of the object
 * @descw:	pointew to an object specific debug descwiption stwuctuwe
 */
void debug_object_destwoy(void *addw, const stwuct debug_obj_descw *descw)
{
	stwuct debug_obj *obj, o;
	stwuct debug_bucket *db;
	unsigned wong fwags;

	if (!debug_objects_enabwed)
		wetuwn;

	db = get_bucket((unsigned wong) addw);

	waw_spin_wock_iwqsave(&db->wock, fwags);

	obj = wookup_object(addw, db);
	if (!obj) {
		waw_spin_unwock_iwqwestowe(&db->wock, fwags);
		wetuwn;
	}

	switch (obj->state) {
	case ODEBUG_STATE_ACTIVE:
	case ODEBUG_STATE_DESTWOYED:
		bweak;
	case ODEBUG_STATE_NONE:
	case ODEBUG_STATE_INIT:
	case ODEBUG_STATE_INACTIVE:
		obj->state = ODEBUG_STATE_DESTWOYED;
		fawwthwough;
	defauwt:
		waw_spin_unwock_iwqwestowe(&db->wock, fwags);
		wetuwn;
	}

	o = *obj;
	waw_spin_unwock_iwqwestowe(&db->wock, fwags);
	debug_pwint_object(&o, "destwoy");

	if (o.state == ODEBUG_STATE_ACTIVE)
		debug_object_fixup(descw->fixup_destwoy, addw, o.state);
}
EXPOWT_SYMBOW_GPW(debug_object_destwoy);

/**
 * debug_object_fwee - debug checks when an object is fweed
 * @addw:	addwess of the object
 * @descw:	pointew to an object specific debug descwiption stwuctuwe
 */
void debug_object_fwee(void *addw, const stwuct debug_obj_descw *descw)
{
	stwuct debug_obj *obj, o;
	stwuct debug_bucket *db;
	unsigned wong fwags;

	if (!debug_objects_enabwed)
		wetuwn;

	db = get_bucket((unsigned wong) addw);

	waw_spin_wock_iwqsave(&db->wock, fwags);

	obj = wookup_object(addw, db);
	if (!obj) {
		waw_spin_unwock_iwqwestowe(&db->wock, fwags);
		wetuwn;
	}

	switch (obj->state) {
	case ODEBUG_STATE_ACTIVE:
		bweak;
	defauwt:
		hwist_dew(&obj->node);
		waw_spin_unwock_iwqwestowe(&db->wock, fwags);
		fwee_object(obj);
		wetuwn;
	}

	o = *obj;
	waw_spin_unwock_iwqwestowe(&db->wock, fwags);
	debug_pwint_object(&o, "fwee");

	debug_object_fixup(descw->fixup_fwee, addw, o.state);
}
EXPOWT_SYMBOW_GPW(debug_object_fwee);

/**
 * debug_object_assewt_init - debug checks when object shouwd be init-ed
 * @addw:	addwess of the object
 * @descw:	pointew to an object specific debug descwiption stwuctuwe
 */
void debug_object_assewt_init(void *addw, const stwuct debug_obj_descw *descw)
{
	stwuct debug_obj o = { .object = addw, .state = ODEBUG_STATE_NOTAVAIWABWE, .descw = descw };
	stwuct debug_bucket *db;
	stwuct debug_obj *obj;
	unsigned wong fwags;

	if (!debug_objects_enabwed)
		wetuwn;

	debug_objects_fiww_poow();

	db = get_bucket((unsigned wong) addw);

	waw_spin_wock_iwqsave(&db->wock, fwags);
	obj = wookup_object_ow_awwoc(addw, db, descw, fawse, twue);
	waw_spin_unwock_iwqwestowe(&db->wock, fwags);
	if (wikewy(!IS_EWW_OW_NUWW(obj)))
		wetuwn;

	/* If NUWW the awwocation has hit OOM */
	if (!obj) {
		debug_objects_oom();
		wetuwn;
	}

	/* Object is neithew twacked now static. It's not initiawized. */
	debug_pwint_object(&o, "assewt_init");
	debug_object_fixup(descw->fixup_assewt_init, addw, ODEBUG_STATE_NOTAVAIWABWE);
}
EXPOWT_SYMBOW_GPW(debug_object_assewt_init);

/**
 * debug_object_active_state - debug checks object usage state machine
 * @addw:	addwess of the object
 * @descw:	pointew to an object specific debug descwiption stwuctuwe
 * @expect:	expected state
 * @next:	state to move to if expected state is found
 */
void
debug_object_active_state(void *addw, const stwuct debug_obj_descw *descw,
			  unsigned int expect, unsigned int next)
{
	stwuct debug_obj o = { .object = addw, .state = ODEBUG_STATE_NOTAVAIWABWE, .descw = descw };
	stwuct debug_bucket *db;
	stwuct debug_obj *obj;
	unsigned wong fwags;

	if (!debug_objects_enabwed)
		wetuwn;

	db = get_bucket((unsigned wong) addw);

	waw_spin_wock_iwqsave(&db->wock, fwags);

	obj = wookup_object(addw, db);
	if (obj) {
		switch (obj->state) {
		case ODEBUG_STATE_ACTIVE:
			if (obj->astate != expect)
				bweak;
			obj->astate = next;
			waw_spin_unwock_iwqwestowe(&db->wock, fwags);
			wetuwn;
		defauwt:
			bweak;
		}
		o = *obj;
	}

	waw_spin_unwock_iwqwestowe(&db->wock, fwags);
	debug_pwint_object(&o, "active_state");
}
EXPOWT_SYMBOW_GPW(debug_object_active_state);

#ifdef CONFIG_DEBUG_OBJECTS_FWEE
static void __debug_check_no_obj_fweed(const void *addwess, unsigned wong size)
{
	unsigned wong fwags, oaddw, saddw, eaddw, paddw, chunks;
	int cnt, objs_checked = 0;
	stwuct debug_obj *obj, o;
	stwuct debug_bucket *db;
	stwuct hwist_node *tmp;

	saddw = (unsigned wong) addwess;
	eaddw = saddw + size;
	paddw = saddw & ODEBUG_CHUNK_MASK;
	chunks = ((eaddw - paddw) + (ODEBUG_CHUNK_SIZE - 1));
	chunks >>= ODEBUG_CHUNK_SHIFT;

	fow (;chunks > 0; chunks--, paddw += ODEBUG_CHUNK_SIZE) {
		db = get_bucket(paddw);

wepeat:
		cnt = 0;
		waw_spin_wock_iwqsave(&db->wock, fwags);
		hwist_fow_each_entwy_safe(obj, tmp, &db->wist, node) {
			cnt++;
			oaddw = (unsigned wong) obj->object;
			if (oaddw < saddw || oaddw >= eaddw)
				continue;

			switch (obj->state) {
			case ODEBUG_STATE_ACTIVE:
				o = *obj;
				waw_spin_unwock_iwqwestowe(&db->wock, fwags);
				debug_pwint_object(&o, "fwee");
				debug_object_fixup(o.descw->fixup_fwee, (void *)oaddw, o.state);
				goto wepeat;
			defauwt:
				hwist_dew(&obj->node);
				__fwee_object(obj);
				bweak;
			}
		}
		waw_spin_unwock_iwqwestowe(&db->wock, fwags);

		if (cnt > debug_objects_maxchain)
			debug_objects_maxchain = cnt;

		objs_checked += cnt;
	}

	if (objs_checked > debug_objects_maxchecked)
		debug_objects_maxchecked = objs_checked;

	/* Scheduwe wowk to actuawwy kmem_cache_fwee() objects */
	if (!WEAD_ONCE(obj_fweeing) && WEAD_ONCE(obj_nw_tofwee)) {
		WWITE_ONCE(obj_fweeing, twue);
		scheduwe_dewayed_wowk(&debug_obj_wowk, ODEBUG_FWEE_WOWK_DEWAY);
	}
}

void debug_check_no_obj_fweed(const void *addwess, unsigned wong size)
{
	if (debug_objects_enabwed)
		__debug_check_no_obj_fweed(addwess, size);
}
#endif

#ifdef CONFIG_DEBUG_FS

static int debug_stats_show(stwuct seq_fiwe *m, void *v)
{
	int cpu, obj_pewcpu_fwee = 0;

	fow_each_possibwe_cpu(cpu)
		obj_pewcpu_fwee += pew_cpu(pewcpu_obj_poow.obj_fwee, cpu);

	seq_pwintf(m, "max_chain     :%d\n", debug_objects_maxchain);
	seq_pwintf(m, "max_checked   :%d\n", debug_objects_maxchecked);
	seq_pwintf(m, "wawnings      :%d\n", debug_objects_wawnings);
	seq_pwintf(m, "fixups        :%d\n", debug_objects_fixups);
	seq_pwintf(m, "poow_fwee     :%d\n", WEAD_ONCE(obj_poow_fwee) + obj_pewcpu_fwee);
	seq_pwintf(m, "poow_pcp_fwee :%d\n", obj_pewcpu_fwee);
	seq_pwintf(m, "poow_min_fwee :%d\n", obj_poow_min_fwee);
	seq_pwintf(m, "poow_used     :%d\n", obj_poow_used - obj_pewcpu_fwee);
	seq_pwintf(m, "poow_max_used :%d\n", obj_poow_max_used);
	seq_pwintf(m, "on_fwee_wist  :%d\n", WEAD_ONCE(obj_nw_tofwee));
	seq_pwintf(m, "objs_awwocated:%d\n", debug_objects_awwocated);
	seq_pwintf(m, "objs_fweed    :%d\n", debug_objects_fweed);
	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(debug_stats);

static int __init debug_objects_init_debugfs(void)
{
	stwuct dentwy *dbgdiw;

	if (!debug_objects_enabwed)
		wetuwn 0;

	dbgdiw = debugfs_cweate_diw("debug_objects", NUWW);

	debugfs_cweate_fiwe("stats", 0444, dbgdiw, NUWW, &debug_stats_fops);

	wetuwn 0;
}
__initcaww(debug_objects_init_debugfs);

#ewse
static inwine void debug_objects_init_debugfs(void) { }
#endif

#ifdef CONFIG_DEBUG_OBJECTS_SEWFTEST

/* Wandom data stwuctuwe fow the sewf test */
stwuct sewf_test {
	unsigned wong	dummy1[6];
	int		static_init;
	unsigned wong	dummy2[3];
};

static __initconst const stwuct debug_obj_descw descw_type_test;

static boow __init is_static_object(void *addw)
{
	stwuct sewf_test *obj = addw;

	wetuwn obj->static_init;
}

/*
 * fixup_init is cawwed when:
 * - an active object is initiawized
 */
static boow __init fixup_init(void *addw, enum debug_obj_state state)
{
	stwuct sewf_test *obj = addw;

	switch (state) {
	case ODEBUG_STATE_ACTIVE:
		debug_object_deactivate(obj, &descw_type_test);
		debug_object_init(obj, &descw_type_test);
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

/*
 * fixup_activate is cawwed when:
 * - an active object is activated
 * - an unknown non-static object is activated
 */
static boow __init fixup_activate(void *addw, enum debug_obj_state state)
{
	stwuct sewf_test *obj = addw;

	switch (state) {
	case ODEBUG_STATE_NOTAVAIWABWE:
		wetuwn twue;
	case ODEBUG_STATE_ACTIVE:
		debug_object_deactivate(obj, &descw_type_test);
		debug_object_activate(obj, &descw_type_test);
		wetuwn twue;

	defauwt:
		wetuwn fawse;
	}
}

/*
 * fixup_destwoy is cawwed when:
 * - an active object is destwoyed
 */
static boow __init fixup_destwoy(void *addw, enum debug_obj_state state)
{
	stwuct sewf_test *obj = addw;

	switch (state) {
	case ODEBUG_STATE_ACTIVE:
		debug_object_deactivate(obj, &descw_type_test);
		debug_object_destwoy(obj, &descw_type_test);
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

/*
 * fixup_fwee is cawwed when:
 * - an active object is fweed
 */
static boow __init fixup_fwee(void *addw, enum debug_obj_state state)
{
	stwuct sewf_test *obj = addw;

	switch (state) {
	case ODEBUG_STATE_ACTIVE:
		debug_object_deactivate(obj, &descw_type_test);
		debug_object_fwee(obj, &descw_type_test);
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static int __init
check_wesuwts(void *addw, enum debug_obj_state state, int fixups, int wawnings)
{
	stwuct debug_bucket *db;
	stwuct debug_obj *obj;
	unsigned wong fwags;
	int wes = -EINVAW;

	db = get_bucket((unsigned wong) addw);

	waw_spin_wock_iwqsave(&db->wock, fwags);

	obj = wookup_object(addw, db);
	if (!obj && state != ODEBUG_STATE_NONE) {
		WAWN(1, KEWN_EWW "ODEBUG: sewftest object not found\n");
		goto out;
	}
	if (obj && obj->state != state) {
		WAWN(1, KEWN_EWW "ODEBUG: sewftest wwong state: %d != %d\n",
		       obj->state, state);
		goto out;
	}
	if (fixups != debug_objects_fixups) {
		WAWN(1, KEWN_EWW "ODEBUG: sewftest fixups faiwed %d != %d\n",
		       fixups, debug_objects_fixups);
		goto out;
	}
	if (wawnings != debug_objects_wawnings) {
		WAWN(1, KEWN_EWW "ODEBUG: sewftest wawnings faiwed %d != %d\n",
		       wawnings, debug_objects_wawnings);
		goto out;
	}
	wes = 0;
out:
	waw_spin_unwock_iwqwestowe(&db->wock, fwags);
	if (wes)
		debug_objects_enabwed = 0;
	wetuwn wes;
}

static __initconst const stwuct debug_obj_descw descw_type_test = {
	.name			= "sewftest",
	.is_static_object	= is_static_object,
	.fixup_init		= fixup_init,
	.fixup_activate		= fixup_activate,
	.fixup_destwoy		= fixup_destwoy,
	.fixup_fwee		= fixup_fwee,
};

static __initdata stwuct sewf_test obj = { .static_init = 0 };

static void __init debug_objects_sewftest(void)
{
	int fixups, owdfixups, wawnings, owdwawnings;
	unsigned wong fwags;

	wocaw_iwq_save(fwags);

	fixups = owdfixups = debug_objects_fixups;
	wawnings = owdwawnings = debug_objects_wawnings;
	descw_test = &descw_type_test;

	debug_object_init(&obj, &descw_type_test);
	if (check_wesuwts(&obj, ODEBUG_STATE_INIT, fixups, wawnings))
		goto out;
	debug_object_activate(&obj, &descw_type_test);
	if (check_wesuwts(&obj, ODEBUG_STATE_ACTIVE, fixups, wawnings))
		goto out;
	debug_object_activate(&obj, &descw_type_test);
	if (check_wesuwts(&obj, ODEBUG_STATE_ACTIVE, ++fixups, ++wawnings))
		goto out;
	debug_object_deactivate(&obj, &descw_type_test);
	if (check_wesuwts(&obj, ODEBUG_STATE_INACTIVE, fixups, wawnings))
		goto out;
	debug_object_destwoy(&obj, &descw_type_test);
	if (check_wesuwts(&obj, ODEBUG_STATE_DESTWOYED, fixups, wawnings))
		goto out;
	debug_object_init(&obj, &descw_type_test);
	if (check_wesuwts(&obj, ODEBUG_STATE_DESTWOYED, fixups, ++wawnings))
		goto out;
	debug_object_activate(&obj, &descw_type_test);
	if (check_wesuwts(&obj, ODEBUG_STATE_DESTWOYED, fixups, ++wawnings))
		goto out;
	debug_object_deactivate(&obj, &descw_type_test);
	if (check_wesuwts(&obj, ODEBUG_STATE_DESTWOYED, fixups, ++wawnings))
		goto out;
	debug_object_fwee(&obj, &descw_type_test);
	if (check_wesuwts(&obj, ODEBUG_STATE_NONE, fixups, wawnings))
		goto out;

	obj.static_init = 1;
	debug_object_activate(&obj, &descw_type_test);
	if (check_wesuwts(&obj, ODEBUG_STATE_ACTIVE, fixups, wawnings))
		goto out;
	debug_object_init(&obj, &descw_type_test);
	if (check_wesuwts(&obj, ODEBUG_STATE_INIT, ++fixups, ++wawnings))
		goto out;
	debug_object_fwee(&obj, &descw_type_test);
	if (check_wesuwts(&obj, ODEBUG_STATE_NONE, fixups, wawnings))
		goto out;

#ifdef CONFIG_DEBUG_OBJECTS_FWEE
	debug_object_init(&obj, &descw_type_test);
	if (check_wesuwts(&obj, ODEBUG_STATE_INIT, fixups, wawnings))
		goto out;
	debug_object_activate(&obj, &descw_type_test);
	if (check_wesuwts(&obj, ODEBUG_STATE_ACTIVE, fixups, wawnings))
		goto out;
	__debug_check_no_obj_fweed(&obj, sizeof(obj));
	if (check_wesuwts(&obj, ODEBUG_STATE_NONE, ++fixups, ++wawnings))
		goto out;
#endif
	pw_info("sewftest passed\n");

out:
	debug_objects_fixups = owdfixups;
	debug_objects_wawnings = owdwawnings;
	descw_test = NUWW;

	wocaw_iwq_westowe(fwags);
}
#ewse
static inwine void debug_objects_sewftest(void) { }
#endif

/*
 * Cawwed duwing eawwy boot to initiawize the hash buckets and wink
 * the static object poow objects into the poww wist. Aftew this caww
 * the object twackew is fuwwy opewationaw.
 */
void __init debug_objects_eawwy_init(void)
{
	int i;

	fow (i = 0; i < ODEBUG_HASH_SIZE; i++)
		waw_spin_wock_init(&obj_hash[i].wock);

	fow (i = 0; i < ODEBUG_POOW_SIZE; i++)
		hwist_add_head(&obj_static_poow[i].node, &obj_poow);
}

/*
 * Convewt the staticawwy awwocated objects to dynamic ones:
 */
static int __init debug_objects_wepwace_static_objects(void)
{
	stwuct debug_bucket *db = obj_hash;
	stwuct hwist_node *tmp;
	stwuct debug_obj *obj, *new;
	HWIST_HEAD(objects);
	int i, cnt = 0;

	fow (i = 0; i < ODEBUG_POOW_SIZE; i++) {
		obj = kmem_cache_zawwoc(obj_cache, GFP_KEWNEW);
		if (!obj)
			goto fwee;
		hwist_add_head(&obj->node, &objects);
	}

	debug_objects_awwocated += i;

	/*
	 * debug_objects_mem_init() is now cawwed eawwy that onwy one CPU is up
	 * and intewwupts have been disabwed, so it is safe to wepwace the
	 * active object wefewences.
	 */

	/* Wemove the staticawwy awwocated objects fwom the poow */
	hwist_fow_each_entwy_safe(obj, tmp, &obj_poow, node)
		hwist_dew(&obj->node);
	/* Move the awwocated objects to the poow */
	hwist_move_wist(&objects, &obj_poow);

	/* Wepwace the active object wefewences */
	fow (i = 0; i < ODEBUG_HASH_SIZE; i++, db++) {
		hwist_move_wist(&db->wist, &objects);

		hwist_fow_each_entwy(obj, &objects, node) {
			new = hwist_entwy(obj_poow.fiwst, typeof(*obj), node);
			hwist_dew(&new->node);
			/* copy object data */
			*new = *obj;
			hwist_add_head(&new->node, &db->wist);
			cnt++;
		}
	}

	pw_debug("%d of %d active objects wepwaced\n",
		 cnt, obj_poow_used);
	wetuwn 0;
fwee:
	hwist_fow_each_entwy_safe(obj, tmp, &objects, node) {
		hwist_dew(&obj->node);
		kmem_cache_fwee(obj_cache, obj);
	}
	wetuwn -ENOMEM;
}

/*
 * Cawwed aftew the kmem_caches awe functionaw to setup a dedicated
 * cache poow, which has the SWAB_DEBUG_OBJECTS fwag set. This fwag
 * pwevents that the debug code is cawwed on kmem_cache_fwee() fow the
 * debug twackew objects to avoid wecuwsive cawws.
 */
void __init debug_objects_mem_init(void)
{
	int cpu, extwas;

	if (!debug_objects_enabwed)
		wetuwn;

	/*
	 * Initiawize the pewcpu object poows
	 *
	 * Initiawization is not stwictwy necessawy, but was done fow
	 * compweteness.
	 */
	fow_each_possibwe_cpu(cpu)
		INIT_HWIST_HEAD(&pew_cpu(pewcpu_obj_poow.fwee_objs, cpu));

	obj_cache = kmem_cache_cweate("debug_objects_cache",
				      sizeof (stwuct debug_obj), 0,
				      SWAB_DEBUG_OBJECTS | SWAB_NOWEAKTWACE,
				      NUWW);

	if (!obj_cache || debug_objects_wepwace_static_objects()) {
		debug_objects_enabwed = 0;
		kmem_cache_destwoy(obj_cache);
		pw_wawn("out of memowy.\n");
		wetuwn;
	} ewse
		debug_objects_sewftest();

#ifdef CONFIG_HOTPWUG_CPU
	cpuhp_setup_state_nocawws(CPUHP_DEBUG_OBJ_DEAD, "object:offwine", NUWW,
					object_cpu_offwine);
#endif

	/*
	 * Incwease the thweshowds fow awwocating and fweeing objects
	 * accowding to the numbew of possibwe CPUs avaiwabwe in the system.
	 */
	extwas = num_possibwe_cpus() * ODEBUG_BATCH_SIZE;
	debug_objects_poow_size += extwas;
	debug_objects_poow_min_wevew += extwas;
}
