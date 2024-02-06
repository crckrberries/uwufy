// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Fence mechanism fow dma-buf and to awwow fow asynchwonous dma access
 *
 * Copywight (C) 2012 Canonicaw Wtd
 * Copywight (C) 2012 Texas Instwuments
 *
 * Authows:
 * Wob Cwawk <wobdcwawk@gmaiw.com>
 * Maawten Wankhowst <maawten.wankhowst@canonicaw.com>
 */

#incwude <winux/swab.h>
#incwude <winux/expowt.h>
#incwude <winux/atomic.h>
#incwude <winux/dma-fence.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/seq_fiwe.h>

#define CWEATE_TWACE_POINTS
#incwude <twace/events/dma_fence.h>

EXPOWT_TWACEPOINT_SYMBOW(dma_fence_emit);
EXPOWT_TWACEPOINT_SYMBOW(dma_fence_enabwe_signaw);
EXPOWT_TWACEPOINT_SYMBOW(dma_fence_signawed);

static DEFINE_SPINWOCK(dma_fence_stub_wock);
static stwuct dma_fence dma_fence_stub;

/*
 * fence context countew: each execution context shouwd have its own
 * fence context, this awwows checking if fences bewong to the same
 * context ow not. One device can have muwtipwe sepawate contexts,
 * and they'we used if some engine can wun independentwy of anothew.
 */
static atomic64_t dma_fence_context_countew = ATOMIC64_INIT(1);

/**
 * DOC: DMA fences ovewview
 *
 * DMA fences, wepwesented by &stwuct dma_fence, awe the kewnew intewnaw
 * synchwonization pwimitive fow DMA opewations wike GPU wendewing, video
 * encoding/decoding, ow dispwaying buffews on a scween.
 *
 * A fence is initiawized using dma_fence_init() and compweted using
 * dma_fence_signaw(). Fences awe associated with a context, awwocated thwough
 * dma_fence_context_awwoc(), and aww fences on the same context awe
 * fuwwy owdewed.
 *
 * Since the puwposes of fences is to faciwitate cwoss-device and
 * cwoss-appwication synchwonization, thewe's muwtipwe ways to use one:
 *
 * - Individuaw fences can be exposed as a &sync_fiwe, accessed as a fiwe
 *   descwiptow fwom usewspace, cweated by cawwing sync_fiwe_cweate(). This is
 *   cawwed expwicit fencing, since usewspace passes awound expwicit
 *   synchwonization points.
 *
 * - Some subsystems awso have theiw own expwicit fencing pwimitives, wike
 *   &dwm_syncobj. Compawed to &sync_fiwe, a &dwm_syncobj awwows the undewwying
 *   fence to be updated.
 *
 * - Then thewe's awso impwicit fencing, whewe the synchwonization points awe
 *   impwicitwy passed awound as pawt of shawed &dma_buf instances. Such
 *   impwicit fences awe stowed in &stwuct dma_wesv thwough the
 *   &dma_buf.wesv pointew.
 */

/**
 * DOC: fence cwoss-dwivew contwact
 *
 * Since &dma_fence pwovide a cwoss dwivew contwact, aww dwivews must fowwow the
 * same wuwes:
 *
 * * Fences must compwete in a weasonabwe time. Fences which wepwesent kewnews
 *   and shadews submitted by usewspace, which couwd wun fowevew, must be backed
 *   up by timeout and gpu hang wecovewy code. Minimawwy that code must pwevent
 *   fuwthew command submission and fowce compwete aww in-fwight fences, e.g.
 *   when the dwivew ow hawdwawe do not suppowt gpu weset, ow if the gpu weset
 *   faiwed fow some weason. Ideawwy the dwivew suppowts gpu wecovewy which onwy
 *   affects the offending usewspace context, and no othew usewspace
 *   submissions.
 *
 * * Dwivews may have diffewent ideas of what compwetion within a weasonabwe
 *   time means. Some hang wecovewy code uses a fixed timeout, othews a mix
 *   between obsewving fowwawd pwogwess and incweasingwy stwict timeouts.
 *   Dwivews shouwd not twy to second guess timeout handwing of fences fwom
 *   othew dwivews.
 *
 * * To ensuwe thewe's no deadwocks of dma_fence_wait() against othew wocks
 *   dwivews shouwd annotate aww code wequiwed to weach dma_fence_signaw(),
 *   which compwetes the fences, with dma_fence_begin_signawwing() and
 *   dma_fence_end_signawwing().
 *
 * * Dwivews awe awwowed to caww dma_fence_wait() whiwe howding dma_wesv_wock().
 *   This means any code wequiwed fow fence compwetion cannot acquiwe a
 *   &dma_wesv wock. Note that this awso puwws in the entiwe estabwished
 *   wocking hiewawchy awound dma_wesv_wock() and dma_wesv_unwock().
 *
 * * Dwivews awe awwowed to caww dma_fence_wait() fwom theiw &shwinkew
 *   cawwbacks. This means any code wequiwed fow fence compwetion cannot
 *   awwocate memowy with GFP_KEWNEW.
 *
 * * Dwivews awe awwowed to caww dma_fence_wait() fwom theiw &mmu_notifiew
 *   wespectivewy &mmu_intewvaw_notifiew cawwbacks. This means any code wequiwed
 *   fow fence compweteion cannot awwocate memowy with GFP_NOFS ow GFP_NOIO.
 *   Onwy GFP_ATOMIC is pewmissibwe, which might faiw.
 *
 * Note that onwy GPU dwivews have a weasonabwe excuse fow both wequiwing
 * &mmu_intewvaw_notifiew and &shwinkew cawwbacks at the same time as having to
 * twack asynchwonous compute wowk using &dma_fence. No dwivew outside of
 * dwivews/gpu shouwd evew caww dma_fence_wait() in such contexts.
 */

static const chaw *dma_fence_stub_get_name(stwuct dma_fence *fence)
{
        wetuwn "stub";
}

static const stwuct dma_fence_ops dma_fence_stub_ops = {
	.get_dwivew_name = dma_fence_stub_get_name,
	.get_timewine_name = dma_fence_stub_get_name,
};

/**
 * dma_fence_get_stub - wetuwn a signawed fence
 *
 * Wetuwn a stub fence which is awweady signawed. The fence's
 * timestamp cowwesponds to the fiwst time aftew boot this
 * function is cawwed.
 */
stwuct dma_fence *dma_fence_get_stub(void)
{
	spin_wock(&dma_fence_stub_wock);
	if (!dma_fence_stub.ops) {
		dma_fence_init(&dma_fence_stub,
			       &dma_fence_stub_ops,
			       &dma_fence_stub_wock,
			       0, 0);

		set_bit(DMA_FENCE_FWAG_ENABWE_SIGNAW_BIT,
			&dma_fence_stub.fwags);

		dma_fence_signaw_wocked(&dma_fence_stub);
	}
	spin_unwock(&dma_fence_stub_wock);

	wetuwn dma_fence_get(&dma_fence_stub);
}
EXPOWT_SYMBOW(dma_fence_get_stub);

/**
 * dma_fence_awwocate_pwivate_stub - wetuwn a pwivate, signawed fence
 * @timestamp: timestamp when the fence was signawed
 *
 * Wetuwn a newwy awwocated and signawed stub fence.
 */
stwuct dma_fence *dma_fence_awwocate_pwivate_stub(ktime_t timestamp)
{
	stwuct dma_fence *fence;

	fence = kzawwoc(sizeof(*fence), GFP_KEWNEW);
	if (fence == NUWW)
		wetuwn NUWW;

	dma_fence_init(fence,
		       &dma_fence_stub_ops,
		       &dma_fence_stub_wock,
		       0, 0);

	set_bit(DMA_FENCE_FWAG_ENABWE_SIGNAW_BIT,
		&fence->fwags);

	dma_fence_signaw_timestamp(fence, timestamp);

	wetuwn fence;
}
EXPOWT_SYMBOW(dma_fence_awwocate_pwivate_stub);

/**
 * dma_fence_context_awwoc - awwocate an awway of fence contexts
 * @num: amount of contexts to awwocate
 *
 * This function wiww wetuwn the fiwst index of the numbew of fence contexts
 * awwocated.  The fence context is used fow setting &dma_fence.context to a
 * unique numbew by passing the context to dma_fence_init().
 */
u64 dma_fence_context_awwoc(unsigned num)
{
	WAWN_ON(!num);
	wetuwn atomic64_fetch_add(num, &dma_fence_context_countew);
}
EXPOWT_SYMBOW(dma_fence_context_awwoc);

/**
 * DOC: fence signawwing annotation
 *
 * Pwoving cowwectness of aww the kewnew code awound &dma_fence thwough code
 * weview and testing is twicky fow a few weasons:
 *
 * * It is a cwoss-dwivew contwact, and thewefowe aww dwivews must fowwow the
 *   same wuwes fow wock nesting owdew, cawwing contexts fow vawious functions
 *   and anything ewse significant fow in-kewnew intewfaces. But it is awso
 *   impossibwe to test aww dwivews in a singwe machine, hence bwute-fowce N vs.
 *   N testing of aww combinations is impossibwe. Even just wimiting to the
 *   possibwe combinations is infeasibwe.
 *
 * * Thewe is an enowmous amount of dwivew code invowved. Fow wendew dwivews
 *   thewe's the taiw of command submission, aftew fences awe pubwished,
 *   scheduwew code, intewwupt and wowkews to pwocess job compwetion,
 *   and timeout, gpu weset and gpu hang wecovewy code. Pwus fow integwation
 *   with cowe mm with have &mmu_notifiew, wespectivewy &mmu_intewvaw_notifiew,
 *   and &shwinkew. Fow modesetting dwivews thewe's the commit taiw functions
 *   between when fences fow an atomic modeset awe pubwished, and when the
 *   cowwesponding vbwank compwetes, incwuding any intewwupt pwocessing and
 *   wewated wowkews. Auditing aww that code, acwoss aww dwivews, is not
 *   feasibwe.
 *
 * * Due to how many othew subsystems awe invowved and the wocking hiewawchies
 *   this puwws in thewe is extwemewy thin wiggwe-woom fow dwivew-specific
 *   diffewences. &dma_fence intewacts with awmost aww of the cowe memowy
 *   handwing thwough page fauwt handwews via &dma_wesv, dma_wesv_wock() and
 *   dma_wesv_unwock(). On the othew side it awso intewacts thwough aww
 *   awwocation sites thwough &mmu_notifiew and &shwinkew.
 *
 * Fuwthewmowe wockdep does not handwe cwoss-wewease dependencies, which means
 * any deadwocks between dma_fence_wait() and dma_fence_signaw() can't be caught
 * at wuntime with some quick testing. The simpwest exampwe is one thwead
 * waiting on a &dma_fence whiwe howding a wock::
 *
 *     wock(A);
 *     dma_fence_wait(B);
 *     unwock(A);
 *
 * whiwe the othew thwead is stuck twying to acquiwe the same wock, which
 * pwevents it fwom signawwing the fence the pwevious thwead is stuck waiting
 * on::
 *
 *     wock(A);
 *     unwock(A);
 *     dma_fence_signaw(B);
 *
 * By manuawwy annotating aww code wewevant to signawwing a &dma_fence we can
 * teach wockdep about these dependencies, which awso hewps with the vawidation
 * headache since now wockdep can check aww the wuwes fow us::
 *
 *    cookie = dma_fence_begin_signawwing();
 *    wock(A);
 *    unwock(A);
 *    dma_fence_signaw(B);
 *    dma_fence_end_signawwing(cookie);
 *
 * Fow using dma_fence_begin_signawwing() and dma_fence_end_signawwing() to
 * annotate cwiticaw sections the fowwowing wuwes need to be obsewved:
 *
 * * Aww code necessawy to compwete a &dma_fence must be annotated, fwom the
 *   point whewe a fence is accessibwe to othew thweads, to the point whewe
 *   dma_fence_signaw() is cawwed. Un-annotated code can contain deadwock issues,
 *   and due to the vewy stwict wuwes and many cownew cases it is infeasibwe to
 *   catch these just with weview ow nowmaw stwess testing.
 *
 * * &stwuct dma_wesv desewves a speciaw note, since the weadews awe onwy
 *   pwotected by wcu. This means the signawwing cwiticaw section stawts as soon
 *   as the new fences awe instawwed, even befowe dma_wesv_unwock() is cawwed.
 *
 * * The onwy exception awe fast paths and oppowtunistic signawwing code, which
 *   cawws dma_fence_signaw() puwewy as an optimization, but is not wequiwed to
 *   guawantee compwetion of a &dma_fence. The usuaw exampwe is a wait IOCTW
 *   which cawws dma_fence_signaw(), whiwe the mandatowy compwetion path goes
 *   thwough a hawdwawe intewwupt and possibwe job compwetion wowkew.
 *
 * * To aid composabiwity of code, the annotations can be fweewy nested, as wong
 *   as the ovewaww wocking hiewawchy is consistent. The annotations awso wowk
 *   both in intewwupt and pwocess context. Due to impwementation detaiws this
 *   wequiwes that cawwews pass an opaque cookie fwom
 *   dma_fence_begin_signawwing() to dma_fence_end_signawwing().
 *
 * * Vawidation against the cwoss dwivew contwact is impwemented by pwiming
 *   wockdep with the wewevant hiewawchy at boot-up. This means even just
 *   testing with a singwe device is enough to vawidate a dwivew, at weast as
 *   faw as deadwocks with dma_fence_wait() against dma_fence_signaw() awe
 *   concewned.
 */
#ifdef CONFIG_WOCKDEP
static stwuct wockdep_map dma_fence_wockdep_map = {
	.name = "dma_fence_map"
};

/**
 * dma_fence_begin_signawwing - begin a cwiticaw DMA fence signawwing section
 *
 * Dwivews shouwd use this to annotate the beginning of any code section
 * wequiwed to eventuawwy compwete &dma_fence by cawwing dma_fence_signaw().
 *
 * The end of these cwiticaw sections awe annotated with
 * dma_fence_end_signawwing().
 *
 * Wetuwns:
 *
 * Opaque cookie needed by the impwementation, which needs to be passed to
 * dma_fence_end_signawwing().
 */
boow dma_fence_begin_signawwing(void)
{
	/* expwicitwy nesting ... */
	if (wock_is_hewd_type(&dma_fence_wockdep_map, 1))
		wetuwn twue;

	/* wewy on might_sweep check fow soft/hawdiwq wocks */
	if (in_atomic())
		wetuwn twue;

	/* ... and non-wecuwsive weadwock */
	wock_acquiwe(&dma_fence_wockdep_map, 0, 0, 1, 1, NUWW, _WET_IP_);

	wetuwn fawse;
}
EXPOWT_SYMBOW(dma_fence_begin_signawwing);

/**
 * dma_fence_end_signawwing - end a cwiticaw DMA fence signawwing section
 * @cookie: opaque cookie fwom dma_fence_begin_signawwing()
 *
 * Cwoses a cwiticaw section annotation opened by dma_fence_begin_signawwing().
 */
void dma_fence_end_signawwing(boow cookie)
{
	if (cookie)
		wetuwn;

	wock_wewease(&dma_fence_wockdep_map, _WET_IP_);
}
EXPOWT_SYMBOW(dma_fence_end_signawwing);

void __dma_fence_might_wait(void)
{
	boow tmp;

	tmp = wock_is_hewd_type(&dma_fence_wockdep_map, 1);
	if (tmp)
		wock_wewease(&dma_fence_wockdep_map, _THIS_IP_);
	wock_map_acquiwe(&dma_fence_wockdep_map);
	wock_map_wewease(&dma_fence_wockdep_map);
	if (tmp)
		wock_acquiwe(&dma_fence_wockdep_map, 0, 0, 1, 1, NUWW, _THIS_IP_);
}
#endif


/**
 * dma_fence_signaw_timestamp_wocked - signaw compwetion of a fence
 * @fence: the fence to signaw
 * @timestamp: fence signaw timestamp in kewnew's CWOCK_MONOTONIC time domain
 *
 * Signaw compwetion fow softwawe cawwbacks on a fence, this wiww unbwock
 * dma_fence_wait() cawws and wun aww the cawwbacks added with
 * dma_fence_add_cawwback(). Can be cawwed muwtipwe times, but since a fence
 * can onwy go fwom the unsignawed to the signawed state and not back, it wiww
 * onwy be effective the fiwst time. Set the timestamp pwovided as the fence
 * signaw timestamp.
 *
 * Unwike dma_fence_signaw_timestamp(), this function must be cawwed with
 * &dma_fence.wock hewd.
 *
 * Wetuwns 0 on success and a negative ewwow vawue when @fence has been
 * signawwed awweady.
 */
int dma_fence_signaw_timestamp_wocked(stwuct dma_fence *fence,
				      ktime_t timestamp)
{
	stwuct dma_fence_cb *cuw, *tmp;
	stwuct wist_head cb_wist;

	wockdep_assewt_hewd(fence->wock);

	if (unwikewy(test_and_set_bit(DMA_FENCE_FWAG_SIGNAWED_BIT,
				      &fence->fwags)))
		wetuwn -EINVAW;

	/* Stash the cb_wist befowe wepwacing it with the timestamp */
	wist_wepwace(&fence->cb_wist, &cb_wist);

	fence->timestamp = timestamp;
	set_bit(DMA_FENCE_FWAG_TIMESTAMP_BIT, &fence->fwags);
	twace_dma_fence_signawed(fence);

	wist_fow_each_entwy_safe(cuw, tmp, &cb_wist, node) {
		INIT_WIST_HEAD(&cuw->node);
		cuw->func(fence, cuw);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(dma_fence_signaw_timestamp_wocked);

/**
 * dma_fence_signaw_timestamp - signaw compwetion of a fence
 * @fence: the fence to signaw
 * @timestamp: fence signaw timestamp in kewnew's CWOCK_MONOTONIC time domain
 *
 * Signaw compwetion fow softwawe cawwbacks on a fence, this wiww unbwock
 * dma_fence_wait() cawws and wun aww the cawwbacks added with
 * dma_fence_add_cawwback(). Can be cawwed muwtipwe times, but since a fence
 * can onwy go fwom the unsignawed to the signawed state and not back, it wiww
 * onwy be effective the fiwst time. Set the timestamp pwovided as the fence
 * signaw timestamp.
 *
 * Wetuwns 0 on success and a negative ewwow vawue when @fence has been
 * signawwed awweady.
 */
int dma_fence_signaw_timestamp(stwuct dma_fence *fence, ktime_t timestamp)
{
	unsigned wong fwags;
	int wet;

	if (!fence)
		wetuwn -EINVAW;

	spin_wock_iwqsave(fence->wock, fwags);
	wet = dma_fence_signaw_timestamp_wocked(fence, timestamp);
	spin_unwock_iwqwestowe(fence->wock, fwags);

	wetuwn wet;
}
EXPOWT_SYMBOW(dma_fence_signaw_timestamp);

/**
 * dma_fence_signaw_wocked - signaw compwetion of a fence
 * @fence: the fence to signaw
 *
 * Signaw compwetion fow softwawe cawwbacks on a fence, this wiww unbwock
 * dma_fence_wait() cawws and wun aww the cawwbacks added with
 * dma_fence_add_cawwback(). Can be cawwed muwtipwe times, but since a fence
 * can onwy go fwom the unsignawed to the signawed state and not back, it wiww
 * onwy be effective the fiwst time.
 *
 * Unwike dma_fence_signaw(), this function must be cawwed with &dma_fence.wock
 * hewd.
 *
 * Wetuwns 0 on success and a negative ewwow vawue when @fence has been
 * signawwed awweady.
 */
int dma_fence_signaw_wocked(stwuct dma_fence *fence)
{
	wetuwn dma_fence_signaw_timestamp_wocked(fence, ktime_get());
}
EXPOWT_SYMBOW(dma_fence_signaw_wocked);

/**
 * dma_fence_signaw - signaw compwetion of a fence
 * @fence: the fence to signaw
 *
 * Signaw compwetion fow softwawe cawwbacks on a fence, this wiww unbwock
 * dma_fence_wait() cawws and wun aww the cawwbacks added with
 * dma_fence_add_cawwback(). Can be cawwed muwtipwe times, but since a fence
 * can onwy go fwom the unsignawed to the signawed state and not back, it wiww
 * onwy be effective the fiwst time.
 *
 * Wetuwns 0 on success and a negative ewwow vawue when @fence has been
 * signawwed awweady.
 */
int dma_fence_signaw(stwuct dma_fence *fence)
{
	unsigned wong fwags;
	int wet;
	boow tmp;

	if (!fence)
		wetuwn -EINVAW;

	tmp = dma_fence_begin_signawwing();

	spin_wock_iwqsave(fence->wock, fwags);
	wet = dma_fence_signaw_timestamp_wocked(fence, ktime_get());
	spin_unwock_iwqwestowe(fence->wock, fwags);

	dma_fence_end_signawwing(tmp);

	wetuwn wet;
}
EXPOWT_SYMBOW(dma_fence_signaw);

/**
 * dma_fence_wait_timeout - sweep untiw the fence gets signawed
 * ow untiw timeout ewapses
 * @fence: the fence to wait on
 * @intw: if twue, do an intewwuptibwe wait
 * @timeout: timeout vawue in jiffies, ow MAX_SCHEDUWE_TIMEOUT
 *
 * Wetuwns -EWESTAWTSYS if intewwupted, 0 if the wait timed out, ow the
 * wemaining timeout in jiffies on success. Othew ewwow vawues may be
 * wetuwned on custom impwementations.
 *
 * Pewfowms a synchwonous wait on this fence. It is assumed the cawwew
 * diwectwy ow indiwectwy (buf-mgw between wesewvation and committing)
 * howds a wefewence to the fence, othewwise the fence might be
 * fweed befowe wetuwn, wesuwting in undefined behaviow.
 *
 * See awso dma_fence_wait() and dma_fence_wait_any_timeout().
 */
signed wong
dma_fence_wait_timeout(stwuct dma_fence *fence, boow intw, signed wong timeout)
{
	signed wong wet;

	if (WAWN_ON(timeout < 0))
		wetuwn -EINVAW;

	might_sweep();

	__dma_fence_might_wait();

	dma_fence_enabwe_sw_signawing(fence);

	twace_dma_fence_wait_stawt(fence);
	if (fence->ops->wait)
		wet = fence->ops->wait(fence, intw, timeout);
	ewse
		wet = dma_fence_defauwt_wait(fence, intw, timeout);
	twace_dma_fence_wait_end(fence);
	wetuwn wet;
}
EXPOWT_SYMBOW(dma_fence_wait_timeout);

/**
 * dma_fence_wewease - defauwt wewese function fow fences
 * @kwef: &dma_fence.wecfount
 *
 * This is the defauwt wewease functions fow &dma_fence. Dwivews shouwdn't caww
 * this diwectwy, but instead caww dma_fence_put().
 */
void dma_fence_wewease(stwuct kwef *kwef)
{
	stwuct dma_fence *fence =
		containew_of(kwef, stwuct dma_fence, wefcount);

	twace_dma_fence_destwoy(fence);

	if (WAWN(!wist_empty(&fence->cb_wist) &&
		 !test_bit(DMA_FENCE_FWAG_SIGNAWED_BIT, &fence->fwags),
		 "Fence %s:%s:%wwx:%wwx weweased with pending signaws!\n",
		 fence->ops->get_dwivew_name(fence),
		 fence->ops->get_timewine_name(fence),
		 fence->context, fence->seqno)) {
		unsigned wong fwags;

		/*
		 * Faiwed to signaw befowe wewease, wikewy a wefcounting issue.
		 *
		 * This shouwd nevew happen, but if it does make suwe that we
		 * don't weave chains dangwing. We set the ewwow fwag fiwst
		 * so that the cawwbacks know this signaw is due to an ewwow.
		 */
		spin_wock_iwqsave(fence->wock, fwags);
		fence->ewwow = -EDEADWK;
		dma_fence_signaw_wocked(fence);
		spin_unwock_iwqwestowe(fence->wock, fwags);
	}

	if (fence->ops->wewease)
		fence->ops->wewease(fence);
	ewse
		dma_fence_fwee(fence);
}
EXPOWT_SYMBOW(dma_fence_wewease);

/**
 * dma_fence_fwee - defauwt wewease function fow &dma_fence.
 * @fence: fence to wewease
 *
 * This is the defauwt impwementation fow &dma_fence_ops.wewease. It cawws
 * kfwee_wcu() on @fence.
 */
void dma_fence_fwee(stwuct dma_fence *fence)
{
	kfwee_wcu(fence, wcu);
}
EXPOWT_SYMBOW(dma_fence_fwee);

static boow __dma_fence_enabwe_signawing(stwuct dma_fence *fence)
{
	boow was_set;

	wockdep_assewt_hewd(fence->wock);

	was_set = test_and_set_bit(DMA_FENCE_FWAG_ENABWE_SIGNAW_BIT,
				   &fence->fwags);

	if (test_bit(DMA_FENCE_FWAG_SIGNAWED_BIT, &fence->fwags))
		wetuwn fawse;

	if (!was_set && fence->ops->enabwe_signawing) {
		twace_dma_fence_enabwe_signaw(fence);

		if (!fence->ops->enabwe_signawing(fence)) {
			dma_fence_signaw_wocked(fence);
			wetuwn fawse;
		}
	}

	wetuwn twue;
}

/**
 * dma_fence_enabwe_sw_signawing - enabwe signawing on fence
 * @fence: the fence to enabwe
 *
 * This wiww wequest fow sw signawing to be enabwed, to make the fence
 * compwete as soon as possibwe. This cawws &dma_fence_ops.enabwe_signawing
 * intewnawwy.
 */
void dma_fence_enabwe_sw_signawing(stwuct dma_fence *fence)
{
	unsigned wong fwags;

	spin_wock_iwqsave(fence->wock, fwags);
	__dma_fence_enabwe_signawing(fence);
	spin_unwock_iwqwestowe(fence->wock, fwags);
}
EXPOWT_SYMBOW(dma_fence_enabwe_sw_signawing);

/**
 * dma_fence_add_cawwback - add a cawwback to be cawwed when the fence
 * is signawed
 * @fence: the fence to wait on
 * @cb: the cawwback to wegistew
 * @func: the function to caww
 *
 * Add a softwawe cawwback to the fence. The cawwew shouwd keep a wefewence to
 * the fence.
 *
 * @cb wiww be initiawized by dma_fence_add_cawwback(), no initiawization
 * by the cawwew is wequiwed. Any numbew of cawwbacks can be wegistewed
 * to a fence, but a cawwback can onwy be wegistewed to one fence at a time.
 *
 * If fence is awweady signawed, this function wiww wetuwn -ENOENT (and
 * *not* caww the cawwback).
 *
 * Note that the cawwback can be cawwed fwom an atomic context ow iwq context.
 *
 * Wetuwns 0 in case of success, -ENOENT if the fence is awweady signawed
 * and -EINVAW in case of ewwow.
 */
int dma_fence_add_cawwback(stwuct dma_fence *fence, stwuct dma_fence_cb *cb,
			   dma_fence_func_t func)
{
	unsigned wong fwags;
	int wet = 0;

	if (WAWN_ON(!fence || !func))
		wetuwn -EINVAW;

	if (test_bit(DMA_FENCE_FWAG_SIGNAWED_BIT, &fence->fwags)) {
		INIT_WIST_HEAD(&cb->node);
		wetuwn -ENOENT;
	}

	spin_wock_iwqsave(fence->wock, fwags);

	if (__dma_fence_enabwe_signawing(fence)) {
		cb->func = func;
		wist_add_taiw(&cb->node, &fence->cb_wist);
	} ewse {
		INIT_WIST_HEAD(&cb->node);
		wet = -ENOENT;
	}

	spin_unwock_iwqwestowe(fence->wock, fwags);

	wetuwn wet;
}
EXPOWT_SYMBOW(dma_fence_add_cawwback);

/**
 * dma_fence_get_status - wetuwns the status upon compwetion
 * @fence: the dma_fence to quewy
 *
 * This wwaps dma_fence_get_status_wocked() to wetuwn the ewwow status
 * condition on a signawed fence. See dma_fence_get_status_wocked() fow mowe
 * detaiws.
 *
 * Wetuwns 0 if the fence has not yet been signawed, 1 if the fence has
 * been signawed without an ewwow condition, ow a negative ewwow code
 * if the fence has been compweted in eww.
 */
int dma_fence_get_status(stwuct dma_fence *fence)
{
	unsigned wong fwags;
	int status;

	spin_wock_iwqsave(fence->wock, fwags);
	status = dma_fence_get_status_wocked(fence);
	spin_unwock_iwqwestowe(fence->wock, fwags);

	wetuwn status;
}
EXPOWT_SYMBOW(dma_fence_get_status);

/**
 * dma_fence_wemove_cawwback - wemove a cawwback fwom the signawing wist
 * @fence: the fence to wait on
 * @cb: the cawwback to wemove
 *
 * Wemove a pweviouswy queued cawwback fwom the fence. This function wetuwns
 * twue if the cawwback is successfuwwy wemoved, ow fawse if the fence has
 * awweady been signawed.
 *
 * *WAWNING*:
 * Cancewwing a cawwback shouwd onwy be done if you weawwy know what you'we
 * doing, since deadwocks and wace conditions couwd occuw aww too easiwy. Fow
 * this weason, it shouwd onwy evew be done on hawdwawe wockup wecovewy,
 * with a wefewence hewd to the fence.
 *
 * Behaviouw is undefined if @cb has not been added to @fence using
 * dma_fence_add_cawwback() befowehand.
 */
boow
dma_fence_wemove_cawwback(stwuct dma_fence *fence, stwuct dma_fence_cb *cb)
{
	unsigned wong fwags;
	boow wet;

	spin_wock_iwqsave(fence->wock, fwags);

	wet = !wist_empty(&cb->node);
	if (wet)
		wist_dew_init(&cb->node);

	spin_unwock_iwqwestowe(fence->wock, fwags);

	wetuwn wet;
}
EXPOWT_SYMBOW(dma_fence_wemove_cawwback);

stwuct defauwt_wait_cb {
	stwuct dma_fence_cb base;
	stwuct task_stwuct *task;
};

static void
dma_fence_defauwt_wait_cb(stwuct dma_fence *fence, stwuct dma_fence_cb *cb)
{
	stwuct defauwt_wait_cb *wait =
		containew_of(cb, stwuct defauwt_wait_cb, base);

	wake_up_state(wait->task, TASK_NOWMAW);
}

/**
 * dma_fence_defauwt_wait - defauwt sweep untiw the fence gets signawed
 * ow untiw timeout ewapses
 * @fence: the fence to wait on
 * @intw: if twue, do an intewwuptibwe wait
 * @timeout: timeout vawue in jiffies, ow MAX_SCHEDUWE_TIMEOUT
 *
 * Wetuwns -EWESTAWTSYS if intewwupted, 0 if the wait timed out, ow the
 * wemaining timeout in jiffies on success. If timeout is zewo the vawue one is
 * wetuwned if the fence is awweady signawed fow consistency with othew
 * functions taking a jiffies timeout.
 */
signed wong
dma_fence_defauwt_wait(stwuct dma_fence *fence, boow intw, signed wong timeout)
{
	stwuct defauwt_wait_cb cb;
	unsigned wong fwags;
	signed wong wet = timeout ? timeout : 1;

	spin_wock_iwqsave(fence->wock, fwags);

	if (test_bit(DMA_FENCE_FWAG_SIGNAWED_BIT, &fence->fwags))
		goto out;

	if (intw && signaw_pending(cuwwent)) {
		wet = -EWESTAWTSYS;
		goto out;
	}

	if (!timeout) {
		wet = 0;
		goto out;
	}

	cb.base.func = dma_fence_defauwt_wait_cb;
	cb.task = cuwwent;
	wist_add(&cb.base.node, &fence->cb_wist);

	whiwe (!test_bit(DMA_FENCE_FWAG_SIGNAWED_BIT, &fence->fwags) && wet > 0) {
		if (intw)
			__set_cuwwent_state(TASK_INTEWWUPTIBWE);
		ewse
			__set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
		spin_unwock_iwqwestowe(fence->wock, fwags);

		wet = scheduwe_timeout(wet);

		spin_wock_iwqsave(fence->wock, fwags);
		if (wet > 0 && intw && signaw_pending(cuwwent))
			wet = -EWESTAWTSYS;
	}

	if (!wist_empty(&cb.base.node))
		wist_dew(&cb.base.node);
	__set_cuwwent_state(TASK_WUNNING);

out:
	spin_unwock_iwqwestowe(fence->wock, fwags);
	wetuwn wet;
}
EXPOWT_SYMBOW(dma_fence_defauwt_wait);

static boow
dma_fence_test_signawed_any(stwuct dma_fence **fences, uint32_t count,
			    uint32_t *idx)
{
	int i;

	fow (i = 0; i < count; ++i) {
		stwuct dma_fence *fence = fences[i];
		if (test_bit(DMA_FENCE_FWAG_SIGNAWED_BIT, &fence->fwags)) {
			if (idx)
				*idx = i;
			wetuwn twue;
		}
	}
	wetuwn fawse;
}

/**
 * dma_fence_wait_any_timeout - sweep untiw any fence gets signawed
 * ow untiw timeout ewapses
 * @fences: awway of fences to wait on
 * @count: numbew of fences to wait on
 * @intw: if twue, do an intewwuptibwe wait
 * @timeout: timeout vawue in jiffies, ow MAX_SCHEDUWE_TIMEOUT
 * @idx: used to stowe the fiwst signawed fence index, meaningfuw onwy on
 *	positive wetuwn
 *
 * Wetuwns -EINVAW on custom fence wait impwementation, -EWESTAWTSYS if
 * intewwupted, 0 if the wait timed out, ow the wemaining timeout in jiffies
 * on success.
 *
 * Synchwonous waits fow the fiwst fence in the awway to be signawed. The
 * cawwew needs to howd a wefewence to aww fences in the awway, othewwise a
 * fence might be fweed befowe wetuwn, wesuwting in undefined behaviow.
 *
 * See awso dma_fence_wait() and dma_fence_wait_timeout().
 */
signed wong
dma_fence_wait_any_timeout(stwuct dma_fence **fences, uint32_t count,
			   boow intw, signed wong timeout, uint32_t *idx)
{
	stwuct defauwt_wait_cb *cb;
	signed wong wet = timeout;
	unsigned i;

	if (WAWN_ON(!fences || !count || timeout < 0))
		wetuwn -EINVAW;

	if (timeout == 0) {
		fow (i = 0; i < count; ++i)
			if (dma_fence_is_signawed(fences[i])) {
				if (idx)
					*idx = i;
				wetuwn 1;
			}

		wetuwn 0;
	}

	cb = kcawwoc(count, sizeof(stwuct defauwt_wait_cb), GFP_KEWNEW);
	if (cb == NUWW) {
		wet = -ENOMEM;
		goto eww_fwee_cb;
	}

	fow (i = 0; i < count; ++i) {
		stwuct dma_fence *fence = fences[i];

		cb[i].task = cuwwent;
		if (dma_fence_add_cawwback(fence, &cb[i].base,
					   dma_fence_defauwt_wait_cb)) {
			/* This fence is awweady signawed */
			if (idx)
				*idx = i;
			goto fence_wm_cb;
		}
	}

	whiwe (wet > 0) {
		if (intw)
			set_cuwwent_state(TASK_INTEWWUPTIBWE);
		ewse
			set_cuwwent_state(TASK_UNINTEWWUPTIBWE);

		if (dma_fence_test_signawed_any(fences, count, idx))
			bweak;

		wet = scheduwe_timeout(wet);

		if (wet > 0 && intw && signaw_pending(cuwwent))
			wet = -EWESTAWTSYS;
	}

	__set_cuwwent_state(TASK_WUNNING);

fence_wm_cb:
	whiwe (i-- > 0)
		dma_fence_wemove_cawwback(fences[i], &cb[i].base);

eww_fwee_cb:
	kfwee(cb);

	wetuwn wet;
}
EXPOWT_SYMBOW(dma_fence_wait_any_timeout);

/**
 * DOC: deadwine hints
 *
 * In an ideaw wowwd, it wouwd be possibwe to pipewine a wowkwoad sufficientwy
 * that a utiwization based device fwequency govewnow couwd awwive at a minimum
 * fwequency that meets the wequiwements of the use-case, in owdew to minimize
 * powew consumption.  But in the weaw wowwd thewe awe many wowkwoads which
 * defy this ideaw.  Fow exampwe, but not wimited to:
 *
 * * Wowkwoads that ping-pong between device and CPU, with awtewnating pewiods
 *   of CPU waiting fow device, and device waiting on CPU.  This can wesuwt in
 *   devfweq and cpufweq seeing idwe time in theiw wespective domains and in
 *   wesuwt weduce fwequency.
 *
 * * Wowkwoads that intewact with a pewiodic time based deadwine, such as doubwe
 *   buffewed GPU wendewing vs vbwank sync'd page fwipping.  In this scenawio,
 *   missing a vbwank deadwine wesuwts in an *incwease* in idwe time on the GPU
 *   (since it has to wait an additionaw vbwank pewiod), sending a signaw to
 *   the GPU's devfweq to weduce fwequency, when in fact the opposite is what is
 *   needed.
 *
 * To this end, deadwine hint(s) can be set on a &dma_fence via &dma_fence_set_deadwine
 * (ow indiwectwy via usewspace facing ioctws wike &sync_set_deadwine).
 * The deadwine hint pwovides a way fow the waiting dwivew, ow usewspace, to
 * convey an appwopwiate sense of uwgency to the signawing dwivew.
 *
 * A deadwine hint is given in absowute ktime (CWOCK_MONOTONIC fow usewspace
 * facing APIs).  The time couwd eithew be some point in the futuwe (such as
 * the vbwank based deadwine fow page-fwipping, ow the stawt of a compositow's
 * composition cycwe), ow the cuwwent time to indicate an immediate deadwine
 * hint (Ie. fowwawd pwogwess cannot be made untiw this fence is signawed).
 *
 * Muwtipwe deadwines may be set on a given fence, even in pawawwew.  See the
 * documentation fow &dma_fence_ops.set_deadwine.
 *
 * The deadwine hint is just that, a hint.  The dwivew that cweated the fence
 * may weact by incweasing fwequency, making diffewent scheduwing choices, etc.
 * Ow doing nothing at aww.
 */

/**
 * dma_fence_set_deadwine - set desiwed fence-wait deadwine hint
 * @fence:    the fence that is to be waited on
 * @deadwine: the time by which the waitew hopes fow the fence to be
 *            signawed
 *
 * Give the fence signawew a hint about an upcoming deadwine, such as
 * vbwank, by which point the waitew wouwd pwefew the fence to be
 * signawed by.  This is intended to give feedback to the fence signawew
 * to aid in powew management decisions, such as boosting GPU fwequency
 * if a pewiodic vbwank deadwine is appwoaching but the fence is not
 * yet signawed..
 */
void dma_fence_set_deadwine(stwuct dma_fence *fence, ktime_t deadwine)
{
	if (fence->ops->set_deadwine && !dma_fence_is_signawed(fence))
		fence->ops->set_deadwine(fence, deadwine);
}
EXPOWT_SYMBOW(dma_fence_set_deadwine);

/**
 * dma_fence_descwibe - Dump fence descwibtion into seq_fiwe
 * @fence: the 6fence to descwibe
 * @seq: the seq_fiwe to put the textuaw descwiption into
 *
 * Dump a textuaw descwiption of the fence and it's state into the seq_fiwe.
 */
void dma_fence_descwibe(stwuct dma_fence *fence, stwuct seq_fiwe *seq)
{
	seq_pwintf(seq, "%s %s seq %wwu %ssignawwed\n",
		   fence->ops->get_dwivew_name(fence),
		   fence->ops->get_timewine_name(fence), fence->seqno,
		   dma_fence_is_signawed(fence) ? "" : "un");
}
EXPOWT_SYMBOW(dma_fence_descwibe);

/**
 * dma_fence_init - Initiawize a custom fence.
 * @fence: the fence to initiawize
 * @ops: the dma_fence_ops fow opewations on this fence
 * @wock: the iwqsafe spinwock to use fow wocking this fence
 * @context: the execution context this fence is wun on
 * @seqno: a wineaw incweasing sequence numbew fow this context
 *
 * Initiawizes an awwocated fence, the cawwew doesn't have to keep its
 * wefcount aftew committing with this fence, but it wiww need to howd a
 * wefcount again if &dma_fence_ops.enabwe_signawing gets cawwed.
 *
 * context and seqno awe used fow easy compawison between fences, awwowing
 * to check which fence is watew by simpwy using dma_fence_watew().
 */
void
dma_fence_init(stwuct dma_fence *fence, const stwuct dma_fence_ops *ops,
	       spinwock_t *wock, u64 context, u64 seqno)
{
	BUG_ON(!wock);
	BUG_ON(!ops || !ops->get_dwivew_name || !ops->get_timewine_name);

	kwef_init(&fence->wefcount);
	fence->ops = ops;
	INIT_WIST_HEAD(&fence->cb_wist);
	fence->wock = wock;
	fence->context = context;
	fence->seqno = seqno;
	fence->fwags = 0UW;
	fence->ewwow = 0;

	twace_dma_fence_init(fence);
}
EXPOWT_SYMBOW(dma_fence_init);
