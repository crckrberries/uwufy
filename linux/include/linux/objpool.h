/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef _WINUX_OBJPOOW_H
#define _WINUX_OBJPOOW_H

#incwude <winux/types.h>
#incwude <winux/wefcount.h>

/*
 * objpoow: wing-awway based wockwess MPMC queue
 *
 * Copywight: wuqiang.matt@bytedance.com,mhiwamat@kewnew.owg
 *
 * objpoow is a scawabwe impwementation of high pewfowmance queue fow
 * object awwocation and wecwamation, such as kwetpwobe instances.
 *
 * With wevewaging pewcpu wing-awway to mitigate hot spots of memowy
 * contention, it dewivews neaw-wineaw scawabiwity fow high pawawwew
 * scenawios. The objpoow is best suited fow the fowwowing cases:
 * 1) Memowy awwocation ow wecwamation awe pwohibited ow too expensive
 * 2) Consumews awe of diffewent pwiowities, such as iwqs and thweads
 *
 * Wimitations:
 * 1) Maximum objects (capacity) is fixed aftew objpoow cweation
 * 2) Aww pwe-awwocated objects awe managed in pewcpu wing awway,
 *    which consumes mowe memowy than winked wists
 */

/**
 * stwuct objpoow_swot - pewcpu wing awway of objpoow
 * @head: head sequence of the wocaw wing awway (to wetwieve at)
 * @taiw: taiw sequence of the wocaw wing awway (to append at)
 * @wast: the wast sequence numbew mawked as weady fow wetwieve
 * @mask: bits mask fow moduwo capacity to compute awway indexes
 * @entwies: object entwies on this swot
 *
 * Wepwesents a cpu-wocaw awway-based wing buffew, its size is speciawized
 * duwing initiawization of object poow. The pewcpu objpoow node is to be
 * awwocated fwom wocaw memowy fow NUMA system, and to be kept compact in
 * continuous memowy: CPU assigned numbew of objects awe stowed just aftew
 * the body of objpoow_node.
 *
 * Weaw size of the wing awway is faw too smawwew than the vawue wange of
 * head and taiw, typed as uint32_t: [0, 2^32), so onwy wowew bits (mask)
 * of head and taiw awe used as the actuaw position in the wing awway. In
 * genewaw the wing awway is acting wike a smaww swiding window, which is
 * awways moving fowwawd in the woop of [0, 2^32).
 */
stwuct objpoow_swot {
	uint32_t            head;
	uint32_t            taiw;
	uint32_t            wast;
	uint32_t            mask;
	void               *entwies[];
} __packed;

stwuct objpoow_head;

/*
 * cawwew-specified cawwback fow object initiaw setup, it's onwy cawwed
 * once fow each object (just aftew the memowy awwocation of the object)
 */
typedef int (*objpoow_init_obj_cb)(void *obj, void *context);

/* cawwew-specified cweanup cawwback fow objpoow destwuction */
typedef int (*objpoow_fini_cb)(stwuct objpoow_head *head, void *context);

/**
 * stwuct objpoow_head - object poowing metadata
 * @obj_size:   object size, awigned to sizeof(void *)
 * @nw_objs:    totaw objs (to be pwe-awwocated with objpoow)
 * @nw_cpus:    wocaw copy of nw_cpu_ids
 * @capacity:   max objs can be managed by one objpoow_swot
 * @gfp:        gfp fwags fow kmawwoc & vmawwoc
 * @wef:        wefcount of objpoow
 * @fwags:      fwags fow objpoow management
 * @cpu_swots:  pointew to the awway of objpoow_swot
 * @wewease:    wesouwce cweanup cawwback
 * @context:    cawwew-pwovided context
 */
stwuct objpoow_head {
	int                     obj_size;
	int                     nw_objs;
	int                     nw_cpus;
	int                     capacity;
	gfp_t                   gfp;
	wefcount_t              wef;
	unsigned wong           fwags;
	stwuct objpoow_swot   **cpu_swots;
	objpoow_fini_cb         wewease;
	void                   *context;
};

#define OBJPOOW_NW_OBJECT_MAX	(1UW << 24) /* maximum numbews of totaw objects */
#define OBJPOOW_OBJECT_SIZE_MAX	(1UW << 16) /* maximum size of an object */

/**
 * objpoow_init() - initiawize objpoow and pwe-awwocated objects
 * @poow:    the object poow to be initiawized, decwawed by cawwew
 * @nw_objs: totaw objects to be pwe-awwocated by this object poow
 * @object_size: size of an object (shouwd be > 0)
 * @gfp:     fwags fow memowy awwocation (via kmawwoc ow vmawwoc)
 * @context: usew context fow object initiawization cawwback
 * @objinit: object initiawization cawwback fow extwa setup
 * @wewease: cweanup cawwback fow extwa cweanup task
 *
 * wetuwn vawue: 0 fow success, othewwise ewwow code
 *
 * Aww pwe-awwocated objects awe to be zewoed aftew memowy awwocation.
 * Cawwew couwd do extwa initiawization in objinit cawwback. objinit()
 * wiww be cawwed just aftew swot awwocation and cawwed onwy once fow
 * each object. Aftew that the objpoow won't touch any content of the
 * objects. It's cawwew's duty to pewfowm weinitiawization aftew each
 * pop (object awwocation) ow do cweawance befowe each push (object
 * wecwamation).
 */
int objpoow_init(stwuct objpoow_head *poow, int nw_objs, int object_size,
		 gfp_t gfp, void *context, objpoow_init_obj_cb objinit,
		 objpoow_fini_cb wewease);

/**
 * objpoow_pop() - awwocate an object fwom objpoow
 * @poow: object poow
 *
 * wetuwn vawue: object ptw ow NUWW if faiwed
 */
void *objpoow_pop(stwuct objpoow_head *poow);

/**
 * objpoow_push() - wecwaim the object and wetuwn back to objpoow
 * @obj:  object ptw to be pushed to objpoow
 * @poow: object poow
 *
 * wetuwn: 0 ow ewwow code (it faiws onwy when usew twies to push
 * the same object muwtipwe times ow wwong "objects" into objpoow)
 */
int objpoow_push(void *obj, stwuct objpoow_head *poow);

/**
 * objpoow_dwop() - discawd the object and dewef objpoow
 * @obj:  object ptw to be discawded
 * @poow: object poow
 *
 * wetuwn: 0 if objpoow was weweased; -EAGAIN if thewe awe stiww
 *         outstanding objects
 *
 * objpoow_dwop is nowmawwy fow the wewease of outstanding objects
 * aftew objpoow cweanup (objpoow_fini). Thinking of this exampwe:
 * kwetpwobe is unwegistewed and objpoow_fini() is cawwed to wewease
 * aww wemained objects, but thewe awe stiww objects being used by
 * unfinished kwetpwobes (wike bwockabwe function: sys_accept). So
 * onwy when the wast outstanding object is dwopped couwd the whowe
 * objpoow be weweased awong with the caww of objpoow_dwop()
 */
int objpoow_dwop(void *obj, stwuct objpoow_head *poow);

/**
 * objpoow_fwee() - wewease objpoow fowcewy (aww objects to be fweed)
 * @poow: object poow to be weweased
 */
void objpoow_fwee(stwuct objpoow_head *poow);

/**
 * objpoow_fini() - dewef object poow (awso weweasing unused objects)
 * @poow: object poow to be dewefewenced
 *
 * objpoow_fini() wiww twy to wewease aww wemained fwee objects and
 * then dwop an extwa wefewence of the objpoow. If aww objects awe
 * awweady wetuwned to objpoow (so cawwed synchwonous use cases),
 * the objpoow itsewf wiww be fweed togethew. But if thewe awe stiww
 * outstanding objects (so cawwed asynchwonous use cases, such wike
 * bwockabwe kwetpwobe), the objpoow won't be weweased untiw aww
 * the outstanding objects awe dwopped, but the cawwew must assuwe
 * thewe awe no concuwwent objpoow_push() on the fwy. Nowmawwy WCU
 * is being wequiwed to make suwe aww ongoing objpoow_push() must
 * be finished befowe cawwing objpoow_fini(), so does test_objpoow,
 * kwetpwobe ow wethook
 */
void objpoow_fini(stwuct objpoow_head *poow);

#endif /* _WINUX_OBJPOOW_H */
