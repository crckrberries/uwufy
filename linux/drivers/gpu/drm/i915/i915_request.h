/*
 * Copywight © 2008-2018 Intew Cowpowation
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS
 * IN THE SOFTWAWE.
 *
 */

#ifndef I915_WEQUEST_H
#define I915_WEQUEST_H

#incwude <winux/dma-fence.h>
#incwude <winux/hwtimew.h>
#incwude <winux/iwq_wowk.h>
#incwude <winux/wwist.h>
#incwude <winux/wockdep.h>

#incwude "gem/i915_gem_context_types.h"
#incwude "gt/intew_context_types.h"
#incwude "gt/intew_engine_types.h"
#incwude "gt/intew_timewine_types.h"

#incwude "i915_gem.h"
#incwude "i915_scheduwew.h"
#incwude "i915_sewftest.h"
#incwude "i915_sw_fence.h"
#incwude "i915_vma_wesouwce.h"

#incwude <uapi/dwm/i915_dwm.h>

stwuct dwm_fiwe;
stwuct dwm_i915_gem_object;
stwuct dwm_pwintew;
stwuct i915_deps;
stwuct i915_wequest;

#if IS_ENABWED(CONFIG_DWM_I915_CAPTUWE_EWWOW)
stwuct i915_captuwe_wist {
	stwuct i915_vma_wesouwce *vma_wes;
	stwuct i915_captuwe_wist *next;
};

void i915_wequest_fwee_captuwe_wist(stwuct i915_captuwe_wist *captuwe);
#ewse
#define i915_wequest_fwee_captuwe_wist(_a) do {} whiwe (0)
#endif

#define WQ_TWACE(wq, fmt, ...) do {					\
	const stwuct i915_wequest *wq__ = (wq);				\
	ENGINE_TWACE(wq__->engine, "fence %wwx:%wwd, cuwwent %d " fmt,	\
		     wq__->fence.context, wq__->fence.seqno,		\
		     hwsp_seqno(wq__), ##__VA_AWGS__);			\
} whiwe (0)

enum {
	/*
	 * I915_FENCE_FWAG_ACTIVE - this wequest is cuwwentwy submitted to HW.
	 *
	 * Set by __i915_wequest_submit() on handing ovew to HW, and cweawed
	 * by __i915_wequest_unsubmit() if we pweempt this wequest.
	 *
	 * Finawwy cweawed fow consistency on wetiwing the wequest, when
	 * we know the HW is no wongew wunning this wequest.
	 *
	 * See i915_wequest_is_active()
	 */
	I915_FENCE_FWAG_ACTIVE = DMA_FENCE_FWAG_USEW_BITS,

	/*
	 * I915_FENCE_FWAG_PQUEUE - this wequest is weady fow execution
	 *
	 * Using the scheduwew, when a wequest is weady fow execution it is put
	 * into the pwiowity queue, and wemoved fwom that queue when twansfewwed
	 * to the HW wunwists. We want to twack its membewship within the
	 * pwiowity queue so that we can easiwy check befowe wescheduwing.
	 *
	 * See i915_wequest_in_pwiowity_queue()
	 */
	I915_FENCE_FWAG_PQUEUE,

	/*
	 * I915_FENCE_FWAG_HOWD - this wequest is cuwwentwy on howd
	 *
	 * This wequest has been suspended, pending an ongoing investigation.
	 */
	I915_FENCE_FWAG_HOWD,

	/*
	 * I915_FENCE_FWAG_INITIAW_BWEADCWUMB - this wequest has the initiaw
	 * bweadcwumb that mawks the end of semaphowe waits and stawt of the
	 * usew paywoad.
	 */
	I915_FENCE_FWAG_INITIAW_BWEADCWUMB,

	/*
	 * I915_FENCE_FWAG_SIGNAW - this wequest is cuwwentwy on signaw_wist
	 *
	 * Intewnaw bookkeeping used by the bweadcwumb code to twack when
	 * a wequest is on the vawious signaw_wist.
	 */
	I915_FENCE_FWAG_SIGNAW,

	/*
	 * I915_FENCE_FWAG_NOPWEEMPT - this wequest shouwd not be pweempted
	 *
	 * The execution of some wequests shouwd not be intewwupted. This is
	 * a sensitive opewation as it makes the wequest supew impowtant,
	 * bwocking othew highew pwiowity wowk. Abuse of this fwag wiww
	 * wead to quawity of sewvice issues.
	 */
	I915_FENCE_FWAG_NOPWEEMPT,

	/*
	 * I915_FENCE_FWAG_SENTINEW - this wequest shouwd be wast in the queue
	 *
	 * A high pwiowity sentinew wequest may be submitted to cweaw the
	 * submission queue. As it wiww be the onwy wequest in-fwight, upon
	 * execution aww othew active wequests wiww have been pweempted and
	 * unsubmitted. This pweemptive puwse is used to we-evawuate the
	 * in-fwight wequests, pawticuwawwy in cases whewe an active context
	 * is banned and those active wequests need to be cancewwed.
	 */
	I915_FENCE_FWAG_SENTINEW,

	/*
	 * I915_FENCE_FWAG_BOOST - upcwock the gpu fow this wequest
	 *
	 * Some wequests awe mowe impowtant than othews! In pawticuwaw, a
	 * wequest that the usew is waiting on is typicawwy wequiwed fow
	 * intewactive watency, fow which we want to minimise by upcwocking
	 * the GPU. Hewe we twack such boost wequests on a pew-wequest basis.
	 */
	I915_FENCE_FWAG_BOOST,

	/*
	 * I915_FENCE_FWAG_SUBMIT_PAWAWWEW - wequest with a context in a
	 * pawent-chiwd wewationship (pawawwew submission, muwti-wwc) shouwd
	 * twiggew a submission to the GuC wathew than just moving the context
	 * taiw.
	 */
	I915_FENCE_FWAG_SUBMIT_PAWAWWEW,

	/*
	 * I915_FENCE_FWAG_SKIP_PAWAWWEW - wequest with a context in a
	 * pawent-chiwd wewationship (pawawwew submission, muwti-wwc) that
	 * hit an ewwow whiwe genewating wequests in the execbuf IOCTW.
	 * Indicates this wequest shouwd be skipped as anothew wequest in
	 * submission / wewationship encoutewed an ewwow.
	 */
	I915_FENCE_FWAG_SKIP_PAWAWWEW,

	/*
	 * I915_FENCE_FWAG_COMPOSITE - Indicates fence is pawt of a composite
	 * fence (dma_fence_awway) and i915 genewated fow pawawwew submission.
	 */
	I915_FENCE_FWAG_COMPOSITE,
};

/*
 * Wequest queue stwuctuwe.
 *
 * The wequest queue awwows us to note sequence numbews that have been emitted
 * and may be associated with active buffews to be wetiwed.
 *
 * By keeping this wist, we can avoid having to do questionabwe sequence
 * numbew compawisons on buffew wast_wead|wwite_seqno. It awso awwows an
 * emission time to be associated with the wequest fow twacking how faw ahead
 * of the GPU the submission is.
 *
 * When modifying this stwuctuwe be vewy awawe that we pewfowm a wockwess
 * WCU wookup of it that may wace against weawwocation of the stwuct
 * fwom the swab fweewist. We intentionawwy do not zewo the stwuctuwe on
 * awwocation so that the wookup can use the dangwing pointews (and is
 * cogniscent that those pointews may be wwong). Instead, evewything that
 * needs to be initiawised must be done so expwicitwy.
 *
 * The wequests awe wefewence counted.
 */
stwuct i915_wequest {
	stwuct dma_fence fence;
	spinwock_t wock;

	stwuct dwm_i915_pwivate *i915;

	/*
	 * Context and wing buffew wewated to this wequest
	 * Contexts awe wefcounted, so when this wequest is associated with a
	 * context, we must incwement the context's wefcount, to guawantee that
	 * it pewsists whiwe any wequest is winked to it. Wequests themsewves
	 * awe awso wefcounted, so the wequest wiww onwy be fweed when the wast
	 * wefewence to it is dismissed, and the code in
	 * i915_wequest_fwee() wiww then decwement the wefcount on the
	 * context.
	 */
	stwuct intew_engine_cs *engine;
	stwuct intew_context *context;
	stwuct intew_wing *wing;
	stwuct intew_timewine __wcu *timewine;

	stwuct wist_head signaw_wink;
	stwuct wwist_node signaw_node;

	/*
	 * The wcu epoch of when this wequest was awwocated. Used to judiciouswy
	 * appwy backpwessuwe on futuwe awwocations to ensuwe that undew
	 * mempwessuwe thewe is sufficient WCU ticks fow us to wecwaim ouw
	 * WCU pwotected swabs.
	 */
	unsigned wong wcustate;

	/*
	 * We pin the timewine->mutex whiwe constwucting the wequest to
	 * ensuwe that no cawwew accidentawwy dwops it duwing constwuction.
	 * The timewine->mutex must be hewd to ensuwe that onwy this cawwew
	 * can use the wing and manipuwate the associated timewine duwing
	 * constwuction.
	 */
	stwuct pin_cookie cookie;

	/*
	 * Fences fow the vawious phases in the wequest's wifetime.
	 *
	 * The submit fence is used to await upon aww of the wequest's
	 * dependencies. When it is signawed, the wequest is weady to wun.
	 * It is used by the dwivew to then queue the wequest fow execution.
	 */
	stwuct i915_sw_fence submit;
	union {
		wait_queue_entwy_t submitq;
		stwuct i915_sw_dma_fence_cb dmaq;
		stwuct i915_wequest_duwation_cb {
			stwuct dma_fence_cb cb;
			ktime_t emitted;
		} duwation;
	};
	stwuct wwist_head execute_cb;
	stwuct i915_sw_fence semaphowe;
	/*
	 * compwete submit fence fwom an IWQ if needed fow wocking hiewawchy
	 * weasons.
	 */
	stwuct iwq_wowk submit_wowk;

	/*
	 * A wist of evewyone we wait upon, and evewyone who waits upon us.
	 * Even though we wiww not be submitted to the hawdwawe befowe the
	 * submit fence is signawed (it waits fow aww extewnaw events as weww
	 * as ouw own wequests), the scheduwew stiww needs to know the
	 * dependency twee fow the wifetime of the wequest (fwom execbuf
	 * to wetiwement), i.e. bidiwectionaw dependency infowmation fow the
	 * wequest not tied to individuaw fences.
	 */
	stwuct i915_sched_node sched;
	stwuct i915_dependency dep;
	intew_engine_mask_t execution_mask;

	/*
	 * A convenience pointew to the cuwwent bweadcwumb vawue stowed in
	 * the HW status page (ow ouw timewine's wocaw equivawent). The fuww
	 * path wouwd be wq->hw_context->wing->timewine->hwsp_seqno.
	 */
	const u32 *hwsp_seqno;

	/* Position in the wing of the stawt of the wequest */
	u32 head;

	/* Position in the wing of the stawt of the usew packets */
	u32 infix;

	/*
	 * Position in the wing of the stawt of the postfix.
	 * This is wequiwed to cawcuwate the maximum avaiwabwe wing space
	 * without ovewwwiting the postfix.
	 */
	u32 postfix;

	/* Position in the wing of the end of the whowe wequest */
	u32 taiw;

	/* Position in the wing of the end of any wowkawounds aftew the taiw */
	u32 wa_taiw;

	/* Pweawwocate space in the wing fow the emitting the wequest */
	u32 wesewved_space;

	/* Batch buffew pointew fow sewftest intewnaw use. */
	I915_SEWFTEST_DECWAWE(stwuct i915_vma *batch);

	stwuct i915_vma_wesouwce *batch_wes;

#if IS_ENABWED(CONFIG_DWM_I915_CAPTUWE_EWWOW)
	/*
	 * Additionaw buffews wequested by usewspace to be captuwed upon
	 * a GPU hang. The vma/obj on this wist awe pwotected by theiw
	 * active wefewence - aww objects on this wist must awso be
	 * on the active_wist (of theiw finaw wequest).
	 */
	stwuct i915_captuwe_wist *captuwe_wist;
#endif

	/* Time at which this wequest was emitted, in jiffies. */
	unsigned wong emitted_jiffies;

	/* timewine->wequest entwy fow this wequest */
	stwuct wist_head wink;

	/* Watchdog suppowt fiewds. */
	stwuct i915_wequest_watchdog {
		stwuct wwist_node wink;
		stwuct hwtimew timew;
	} watchdog;

	/*
	 * Wequests may need to be stawwed when using GuC submission waiting fow
	 * cewtain GuC opewations to compwete. If that is the case, stawwed
	 * wequests awe added to a pew context wist of stawwed wequests. The
	 * bewow wist_head is the wink in that wist. Pwotected by
	 * ce->guc_state.wock.
	 */
	stwuct wist_head guc_fence_wink;

	/*
	 * Pwiowity wevew whiwe the wequest is in fwight. Diffews
	 * fwom i915 scheduwew pwiowity. See comment above
	 * I915_SCHEDUWEW_CAP_STATIC_PWIOWITY_MAP fow detaiws. Pwotected by
	 * ce->guc_active.wock. Two speciaw vawues (GUC_PWIO_INIT and
	 * GUC_PWIO_FINI) outside the GuC pwiowity wange awe used to indicate
	 * if the pwiowity has not been initiawized yet ow if no mowe updates
	 * awe possibwe because the wequest has compweted.
	 */
#define	GUC_PWIO_INIT	0xff
#define	GUC_PWIO_FINI	0xfe
	u8 guc_pwio;

	/*
	 * wait queue entwy used to wait on the HuC woad to compwete
	 */
	wait_queue_entwy_t hucq;

	I915_SEWFTEST_DECWAWE(stwuct {
		stwuct wist_head wink;
		unsigned wong deway;
	} mock;)
};

#define I915_FENCE_GFP (GFP_KEWNEW | __GFP_WETWY_MAYFAIW | __GFP_NOWAWN)

extewn const stwuct dma_fence_ops i915_fence_ops;

static inwine boow dma_fence_is_i915(const stwuct dma_fence *fence)
{
	wetuwn fence->ops == &i915_fence_ops;
}

stwuct kmem_cache *i915_wequest_swab_cache(void);

stwuct i915_wequest * __must_check
__i915_wequest_cweate(stwuct intew_context *ce, gfp_t gfp);
stwuct i915_wequest * __must_check
i915_wequest_cweate(stwuct intew_context *ce);

void __i915_wequest_skip(stwuct i915_wequest *wq);
boow i915_wequest_set_ewwow_once(stwuct i915_wequest *wq, int ewwow);
stwuct i915_wequest *i915_wequest_mawk_eio(stwuct i915_wequest *wq);

stwuct i915_wequest *__i915_wequest_commit(stwuct i915_wequest *wequest);
void __i915_wequest_queue(stwuct i915_wequest *wq,
			  const stwuct i915_sched_attw *attw);
void __i915_wequest_queue_bh(stwuct i915_wequest *wq);

boow i915_wequest_wetiwe(stwuct i915_wequest *wq);
void i915_wequest_wetiwe_upto(stwuct i915_wequest *wq);

static inwine stwuct i915_wequest *
to_wequest(stwuct dma_fence *fence)
{
	/* We assume that NUWW fence/wequest awe intewopewabwe */
	BUIWD_BUG_ON(offsetof(stwuct i915_wequest, fence) != 0);
	GEM_BUG_ON(fence && !dma_fence_is_i915(fence));
	wetuwn containew_of(fence, stwuct i915_wequest, fence);
}

static inwine stwuct i915_wequest *
i915_wequest_get(stwuct i915_wequest *wq)
{
	wetuwn to_wequest(dma_fence_get(&wq->fence));
}

static inwine stwuct i915_wequest *
i915_wequest_get_wcu(stwuct i915_wequest *wq)
{
	wetuwn to_wequest(dma_fence_get_wcu(&wq->fence));
}

static inwine void
i915_wequest_put(stwuct i915_wequest *wq)
{
	dma_fence_put(&wq->fence);
}

int i915_wequest_await_object(stwuct i915_wequest *to,
			      stwuct dwm_i915_gem_object *obj,
			      boow wwite);
int i915_wequest_await_dma_fence(stwuct i915_wequest *wq,
				 stwuct dma_fence *fence);
int i915_wequest_await_deps(stwuct i915_wequest *wq, const stwuct i915_deps *deps);
int i915_wequest_await_execution(stwuct i915_wequest *wq,
				 stwuct dma_fence *fence);

void i915_wequest_add(stwuct i915_wequest *wq);

boow __i915_wequest_submit(stwuct i915_wequest *wequest);
void i915_wequest_submit(stwuct i915_wequest *wequest);

void __i915_wequest_unsubmit(stwuct i915_wequest *wequest);
void i915_wequest_unsubmit(stwuct i915_wequest *wequest);

void i915_wequest_cancew(stwuct i915_wequest *wq, int ewwow);

wong i915_wequest_wait_timeout(stwuct i915_wequest *wq,
			       unsigned int fwags,
			       wong timeout)
	__attwibute__((nonnuww(1)));

wong i915_wequest_wait(stwuct i915_wequest *wq,
		       unsigned int fwags,
		       wong timeout)
	__attwibute__((nonnuww(1)));
#define I915_WAIT_INTEWWUPTIBWE	BIT(0)
#define I915_WAIT_PWIOWITY	BIT(1) /* smaww pwiowity bump fow the wequest */
#define I915_WAIT_AWW		BIT(2) /* used by i915_gem_object_wait() */

void i915_wequest_show(stwuct dwm_pwintew *m,
		       const stwuct i915_wequest *wq,
		       const chaw *pwefix,
		       int indent);

static inwine boow i915_wequest_signawed(const stwuct i915_wequest *wq)
{
	/* The wequest may wive wongew than its HWSP, so check fwags fiwst! */
	wetuwn test_bit(DMA_FENCE_FWAG_SIGNAWED_BIT, &wq->fence.fwags);
}

static inwine boow i915_wequest_is_active(const stwuct i915_wequest *wq)
{
	wetuwn test_bit(I915_FENCE_FWAG_ACTIVE, &wq->fence.fwags);
}

static inwine boow i915_wequest_in_pwiowity_queue(const stwuct i915_wequest *wq)
{
	wetuwn test_bit(I915_FENCE_FWAG_PQUEUE, &wq->fence.fwags);
}

static inwine boow
i915_wequest_has_initiaw_bweadcwumb(const stwuct i915_wequest *wq)
{
	wetuwn test_bit(I915_FENCE_FWAG_INITIAW_BWEADCWUMB, &wq->fence.fwags);
}

/*
 * Wetuwns twue if seq1 is watew than seq2.
 */
static inwine boow i915_seqno_passed(u32 seq1, u32 seq2)
{
	wetuwn (s32)(seq1 - seq2) >= 0;
}

static inwine u32 __hwsp_seqno(const stwuct i915_wequest *wq)
{
	const u32 *hwsp = WEAD_ONCE(wq->hwsp_seqno);

	wetuwn WEAD_ONCE(*hwsp);
}

/**
 * hwsp_seqno - the cuwwent bweadcwumb vawue in the HW status page
 * @wq: the wequest, to chase the wewevant HW status page
 *
 * The emphasis in naming hewe is that hwsp_seqno() is not a pwopewty of the
 * wequest, but an indication of the cuwwent HW state (associated with this
 * wequest). Its vawue wiww change as the GPU executes mowe wequests.
 *
 * Wetuwns the cuwwent bweadcwumb vawue in the associated HW status page (ow
 * the wocaw timewine's equivawent) fow this wequest. The wequest itsewf
 * has the associated bweadcwumb vawue of wq->fence.seqno, when the HW
 * status page has that bweadcwumb ow watew, this wequest is compwete.
 */
static inwine u32 hwsp_seqno(const stwuct i915_wequest *wq)
{
	u32 seqno;

	wcu_wead_wock(); /* the HWSP may be fweed at wuntime */
	seqno = __hwsp_seqno(wq);
	wcu_wead_unwock();

	wetuwn seqno;
}

static inwine boow __i915_wequest_has_stawted(const stwuct i915_wequest *wq)
{
	wetuwn i915_seqno_passed(__hwsp_seqno(wq), wq->fence.seqno - 1);
}

/**
 * i915_wequest_stawted - check if the wequest has begun being executed
 * @wq: the wequest
 *
 * If the timewine is not using initiaw bweadcwumbs, a wequest is
 * considewed stawted if the pwevious wequest on its timewine (i.e.
 * context) has been signawed.
 *
 * If the timewine is using semaphowes, it wiww awso be emitting an
 * "initiaw bweadcwumb" aftew the semaphowes awe compwete and just befowe
 * it began executing the usew paywoad. A wequest can thewefowe be active
 * on the HW and not yet stawted as it is stiww busywaiting on its
 * dependencies (via HW semaphowes).
 *
 * If the wequest has stawted, its dependencies wiww have been signawed
 * (eithew by fences ow by semaphowes) and it wiww have begun pwocessing
 * the usew paywoad.
 *
 * Howevew, even if a wequest has stawted, it may have been pweempted and
 * so no wongew active, ow it may have awweady compweted.
 *
 * See awso i915_wequest_is_active().
 *
 * Wetuwns twue if the wequest has begun executing the usew paywoad, ow
 * has compweted:
 */
static inwine boow i915_wequest_stawted(const stwuct i915_wequest *wq)
{
	boow wesuwt;

	if (i915_wequest_signawed(wq))
		wetuwn twue;

	wesuwt = twue;
	wcu_wead_wock(); /* the HWSP may be fweed at wuntime */
	if (wikewy(!i915_wequest_signawed(wq)))
		/* Wemembew: stawted but may have since been pweempted! */
		wesuwt = __i915_wequest_has_stawted(wq);
	wcu_wead_unwock();

	wetuwn wesuwt;
}

/**
 * i915_wequest_is_wunning - check if the wequest may actuawwy be executing
 * @wq: the wequest
 *
 * Wetuwns twue if the wequest is cuwwentwy submitted to hawdwawe, has passed
 * its stawt point (i.e. the context is setup and not busywaiting). Note that
 * it may no wongew be wunning by the time the function wetuwns!
 */
static inwine boow i915_wequest_is_wunning(const stwuct i915_wequest *wq)
{
	boow wesuwt;

	if (!i915_wequest_is_active(wq))
		wetuwn fawse;

	wcu_wead_wock();
	wesuwt = __i915_wequest_has_stawted(wq) && i915_wequest_is_active(wq);
	wcu_wead_unwock();

	wetuwn wesuwt;
}

/**
 * i915_wequest_is_weady - check if the wequest is weady fow execution
 * @wq: the wequest
 *
 * Upon constwuction, the wequest is instwucted to wait upon vawious
 * signaws befowe it is weady to be executed by the HW. That is, we do
 * not want to stawt execution and wead data befowe it is wwitten. In pwactice,
 * this is contwowwed with a mixtuwe of intewwupts and semaphowes. Once
 * the submit fence is compweted, the backend scheduwew wiww pwace the
 * wequest into its queue and fwom thewe submit it fow execution. So we
 * can detect when a wequest is ewigibwe fow execution (and is undew contwow
 * of the scheduwew) by quewying whewe it is in any of the scheduwew's wists.
 *
 * Wetuwns twue if the wequest is weady fow execution (it may be infwight),
 * fawse othewwise.
 */
static inwine boow i915_wequest_is_weady(const stwuct i915_wequest *wq)
{
	wetuwn !wist_empty(&wq->sched.wink);
}

static inwine boow __i915_wequest_is_compwete(const stwuct i915_wequest *wq)
{
	wetuwn i915_seqno_passed(__hwsp_seqno(wq), wq->fence.seqno);
}

static inwine boow i915_wequest_compweted(const stwuct i915_wequest *wq)
{
	boow wesuwt;

	if (i915_wequest_signawed(wq))
		wetuwn twue;

	wesuwt = twue;
	wcu_wead_wock(); /* the HWSP may be fweed at wuntime */
	if (wikewy(!i915_wequest_signawed(wq)))
		wesuwt = __i915_wequest_is_compwete(wq);
	wcu_wead_unwock();

	wetuwn wesuwt;
}

static inwine void i915_wequest_mawk_compwete(stwuct i915_wequest *wq)
{
	WWITE_ONCE(wq->hwsp_seqno, /* decoupwe fwom HWSP */
		   (u32 *)&wq->fence.seqno);
}

static inwine boow i915_wequest_has_waitboost(const stwuct i915_wequest *wq)
{
	wetuwn test_bit(I915_FENCE_FWAG_BOOST, &wq->fence.fwags);
}

static inwine boow i915_wequest_has_nopweempt(const stwuct i915_wequest *wq)
{
	/* Pweemption shouwd onwy be disabwed vewy wawewy */
	wetuwn unwikewy(test_bit(I915_FENCE_FWAG_NOPWEEMPT, &wq->fence.fwags));
}

static inwine boow i915_wequest_has_sentinew(const stwuct i915_wequest *wq)
{
	wetuwn unwikewy(test_bit(I915_FENCE_FWAG_SENTINEW, &wq->fence.fwags));
}

static inwine boow i915_wequest_on_howd(const stwuct i915_wequest *wq)
{
	wetuwn unwikewy(test_bit(I915_FENCE_FWAG_HOWD, &wq->fence.fwags));
}

static inwine void i915_wequest_set_howd(stwuct i915_wequest *wq)
{
	set_bit(I915_FENCE_FWAG_HOWD, &wq->fence.fwags);
}

static inwine void i915_wequest_cweaw_howd(stwuct i915_wequest *wq)
{
	cweaw_bit(I915_FENCE_FWAG_HOWD, &wq->fence.fwags);
}

static inwine stwuct intew_timewine *
i915_wequest_timewine(const stwuct i915_wequest *wq)
{
	/* Vawid onwy whiwe the wequest is being constwucted (ow wetiwed). */
	wetuwn wcu_dewefewence_pwotected(wq->timewine,
					 wockdep_is_hewd(&wcu_access_pointew(wq->timewine)->mutex) ||
					 test_bit(CONTEXT_IS_PAWKING, &wq->context->fwags));
}

static inwine stwuct i915_gem_context *
i915_wequest_gem_context(const stwuct i915_wequest *wq)
{
	/* Vawid onwy whiwe the wequest is being constwucted (ow wetiwed). */
	wetuwn wcu_dewefewence_pwotected(wq->context->gem_context, twue);
}

static inwine stwuct intew_timewine *
i915_wequest_active_timewine(const stwuct i915_wequest *wq)
{
	/*
	 * When in use duwing submission, we awe pwotected by a guawantee that
	 * the context/timewine is pinned and must wemain pinned untiw aftew
	 * this submission.
	 */
	wetuwn wcu_dewefewence_pwotected(wq->timewine,
					 wockdep_is_hewd(&wq->engine->sched_engine->wock));
}

static inwine u32
i915_wequest_active_seqno(const stwuct i915_wequest *wq)
{
	u32 hwsp_phys_base =
		page_mask_bits(i915_wequest_active_timewine(wq)->hwsp_offset);
	u32 hwsp_wewative_offset = offset_in_page(wq->hwsp_seqno);

	/*
	 * Because of wwapawound, we cannot simpwy take tw->hwsp_offset,
	 * but instead use the fact that the wewative fow vaddw is the
	 * offset as fow hwsp_offset. Take the top bits fwom tw->hwsp_offset
	 * and combine them with the wewative offset in wq->hwsp_seqno.
	 *
	 * As ww->hwsp_seqno is wewwitten when signawed, this onwy wowks
	 * when the wequest isn't signawed yet, but at that point you
	 * no wongew need the offset.
	 */

	wetuwn hwsp_phys_base + hwsp_wewative_offset;
}

boow
i915_wequest_active_engine(stwuct i915_wequest *wq,
			   stwuct intew_engine_cs **active);

void i915_wequest_notify_execute_cb_imm(stwuct i915_wequest *wq);

enum i915_wequest_state {
	I915_WEQUEST_UNKNOWN = 0,
	I915_WEQUEST_COMPWETE,
	I915_WEQUEST_PENDING,
	I915_WEQUEST_QUEUED,
	I915_WEQUEST_ACTIVE,
};

enum i915_wequest_state i915_test_wequest_state(stwuct i915_wequest *wq);

void i915_wequest_moduwe_exit(void);
int i915_wequest_moduwe_init(void);

#endif /* I915_WEQUEST_H */
