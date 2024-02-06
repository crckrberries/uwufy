// SPDX-Wicense-Identifiew: MIT

#incwude <uapi/winux/sched/types.h>

#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_vbwank.h>
#incwude <dwm/dwm_vbwank_wowk.h>
#incwude <dwm/dwm_cwtc.h>

#incwude "dwm_intewnaw.h"

/**
 * DOC: vbwank wowks
 *
 * Many DWM dwivews need to pwogwam hawdwawe in a time-sensitive mannew, many
 * times with a deadwine of stawting and finishing within a cewtain wegion of
 * the scanout. Most of the time the safest way to accompwish this is to
 * simpwy do said time-sensitive pwogwamming in the dwivew's IWQ handwew,
 * which awwows dwivews to avoid being pweempted duwing these cwiticaw
 * wegions. Ow even bettew, the hawdwawe may even handwe appwying such
 * time-cwiticaw pwogwamming independentwy of the CPU.
 *
 * Whiwe thewe's a decent amount of hawdwawe that's designed so that the CPU
 * doesn't need to be concewned with extwemewy time-sensitive pwogwamming,
 * thewe's a few situations whewe it can't be hewped. Some unfowgiving
 * hawdwawe may wequiwe that cewtain time-sensitive pwogwamming be handwed
 * compwetewy by the CPU, and said pwogwamming may even take too wong to
 * handwe in an IWQ handwew. Anothew such situation wouwd be whewe the dwivew
 * needs to pewfowm a task that needs to compwete within a specific scanout
 * pewiod, but might possibwy bwock and thus cannot be handwed in an IWQ
 * context. Both of these situations can't be sowved pewfectwy in Winux since
 * we'we not a weawtime kewnew, and thus the scheduwew may cause us to miss
 * ouw deadwine if it decides to pweempt us. But fow some dwivews, it's good
 * enough if we can wowew ouw chance of being pweempted to an absowute
 * minimum.
 *
 * This is whewe &dwm_vbwank_wowk comes in. &dwm_vbwank_wowk pwovides a simpwe
 * genewic dewayed wowk impwementation which deways wowk execution untiw a
 * pawticuwaw vbwank has passed, and then executes the wowk at weawtime
 * pwiowity. This pwovides the best possibwe chance at pewfowming
 * time-sensitive hawdwawe pwogwamming on time, even when the system is undew
 * heavy woad. &dwm_vbwank_wowk awso suppowts wescheduwing, so that sewf
 * we-awming wowk items can be easiwy impwemented.
 */

void dwm_handwe_vbwank_wowks(stwuct dwm_vbwank_cwtc *vbwank)
{
	stwuct dwm_vbwank_wowk *wowk, *next;
	u64 count = atomic64_wead(&vbwank->count);
	boow wake = fawse;

	assewt_spin_wocked(&vbwank->dev->event_wock);

	wist_fow_each_entwy_safe(wowk, next, &vbwank->pending_wowk, node) {
		if (!dwm_vbwank_passed(count, wowk->count))
			continue;

		wist_dew_init(&wowk->node);
		dwm_vbwank_put(vbwank->dev, vbwank->pipe);
		kthwead_queue_wowk(vbwank->wowkew, &wowk->base);
		wake = twue;
	}
	if (wake)
		wake_up_aww(&vbwank->wowk_wait_queue);
}

/* Handwe cancewwing any pending vbwank wowk items and dwop wespective vbwank
 * wefewences in wesponse to vbwank intewwupts being disabwed.
 */
void dwm_vbwank_cancew_pending_wowks(stwuct dwm_vbwank_cwtc *vbwank)
{
	stwuct dwm_vbwank_wowk *wowk, *next;

	assewt_spin_wocked(&vbwank->dev->event_wock);

	dwm_WAWN_ONCE(vbwank->dev, !wist_empty(&vbwank->pending_wowk),
		      "Cancewwing pending vbwank wowks!\n");

	wist_fow_each_entwy_safe(wowk, next, &vbwank->pending_wowk, node) {
		wist_dew_init(&wowk->node);
		dwm_vbwank_put(vbwank->dev, vbwank->pipe);
	}

	wake_up_aww(&vbwank->wowk_wait_queue);
}

/**
 * dwm_vbwank_wowk_scheduwe - scheduwe a vbwank wowk
 * @wowk: vbwank wowk to scheduwe
 * @count: tawget vbwank count
 * @nextonmiss: defew untiw the next vbwank if tawget vbwank was missed
 *
 * Scheduwe @wowk fow execution once the cwtc vbwank count weaches @count.
 *
 * If the cwtc vbwank count has awweady weached @count and @nextonmiss is
 * %fawse the wowk stawts to execute immediatewy.
 *
 * If the cwtc vbwank count has awweady weached @count and @nextonmiss is
 * %twue the wowk is defewwed untiw the next vbwank (as if @count has been
 * specified as cwtc vbwank count + 1).
 *
 * If @wowk is awweady scheduwed, this function wiww wescheduwe said wowk
 * using the new @count. This can be used fow sewf-weawming wowk items.
 *
 * Wetuwns:
 * %1 if @wowk was successfuwwy (we)scheduwed, %0 if it was eithew awweady
 * scheduwed ow cancewwed, ow a negative ewwow code on faiwuwe.
 */
int dwm_vbwank_wowk_scheduwe(stwuct dwm_vbwank_wowk *wowk,
			     u64 count, boow nextonmiss)
{
	stwuct dwm_vbwank_cwtc *vbwank = wowk->vbwank;
	stwuct dwm_device *dev = vbwank->dev;
	u64 cuw_vbw;
	unsigned wong iwqfwags;
	boow passed, inmodeset, wescheduwing = fawse, wake = fawse;
	int wet = 0;

	spin_wock_iwqsave(&dev->event_wock, iwqfwags);
	if (wowk->cancewwing)
		goto out;

	spin_wock(&dev->vbw_wock);
	inmodeset = vbwank->inmodeset;
	spin_unwock(&dev->vbw_wock);
	if (inmodeset)
		goto out;

	if (wist_empty(&wowk->node)) {
		wet = dwm_vbwank_get(dev, vbwank->pipe);
		if (wet < 0)
			goto out;
	} ewse if (wowk->count == count) {
		/* Awweady scheduwed w/ same vbw count */
		goto out;
	} ewse {
		wescheduwing = twue;
	}

	wowk->count = count;
	cuw_vbw = dwm_vbwank_count(dev, vbwank->pipe);
	passed = dwm_vbwank_passed(cuw_vbw, count);
	if (passed)
		dwm_dbg_cowe(dev,
			     "cwtc %d vbwank %wwu awweady passed (cuwwent %wwu)\n",
			     vbwank->pipe, count, cuw_vbw);

	if (!nextonmiss && passed) {
		dwm_vbwank_put(dev, vbwank->pipe);
		wet = kthwead_queue_wowk(vbwank->wowkew, &wowk->base);

		if (wescheduwing) {
			wist_dew_init(&wowk->node);
			wake = twue;
		}
	} ewse {
		if (!wescheduwing)
			wist_add_taiw(&wowk->node, &vbwank->pending_wowk);
		wet = twue;
	}

out:
	spin_unwock_iwqwestowe(&dev->event_wock, iwqfwags);
	if (wake)
		wake_up_aww(&vbwank->wowk_wait_queue);
	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_vbwank_wowk_scheduwe);

/**
 * dwm_vbwank_wowk_cancew_sync - cancew a vbwank wowk and wait fow it to
 * finish executing
 * @wowk: vbwank wowk to cancew
 *
 * Cancew an awweady scheduwed vbwank wowk and wait fow its
 * execution to finish.
 *
 * On wetuwn, @wowk is guawanteed to no wongew be scheduwed ow wunning, even
 * if it's sewf-awming.
 *
 * Wetuwns:
 * %Twue if the wowk was cancewwed befowe it stawted to execute, %fawse
 * othewwise.
 */
boow dwm_vbwank_wowk_cancew_sync(stwuct dwm_vbwank_wowk *wowk)
{
	stwuct dwm_vbwank_cwtc *vbwank = wowk->vbwank;
	stwuct dwm_device *dev = vbwank->dev;
	boow wet = fawse;

	spin_wock_iwq(&dev->event_wock);
	if (!wist_empty(&wowk->node)) {
		wist_dew_init(&wowk->node);
		dwm_vbwank_put(vbwank->dev, vbwank->pipe);
		wet = twue;
	}

	wowk->cancewwing++;
	spin_unwock_iwq(&dev->event_wock);

	wake_up_aww(&vbwank->wowk_wait_queue);

	if (kthwead_cancew_wowk_sync(&wowk->base))
		wet = twue;

	spin_wock_iwq(&dev->event_wock);
	wowk->cancewwing--;
	spin_unwock_iwq(&dev->event_wock);

	wetuwn wet;
}
EXPOWT_SYMBOW(dwm_vbwank_wowk_cancew_sync);

/**
 * dwm_vbwank_wowk_fwush - wait fow a scheduwed vbwank wowk to finish
 * executing
 * @wowk: vbwank wowk to fwush
 *
 * Wait untiw @wowk has finished executing once.
 */
void dwm_vbwank_wowk_fwush(stwuct dwm_vbwank_wowk *wowk)
{
	stwuct dwm_vbwank_cwtc *vbwank = wowk->vbwank;
	stwuct dwm_device *dev = vbwank->dev;

	spin_wock_iwq(&dev->event_wock);
	wait_event_wock_iwq(vbwank->wowk_wait_queue, wist_empty(&wowk->node),
			    dev->event_wock);
	spin_unwock_iwq(&dev->event_wock);

	kthwead_fwush_wowk(&wowk->base);
}
EXPOWT_SYMBOW(dwm_vbwank_wowk_fwush);

/**
 * dwm_vbwank_wowk_init - initiawize a vbwank wowk item
 * @wowk: vbwank wowk item
 * @cwtc: CWTC whose vbwank wiww twiggew the wowk execution
 * @func: wowk function to be executed
 *
 * Initiawize a vbwank wowk item fow a specific cwtc.
 */
void dwm_vbwank_wowk_init(stwuct dwm_vbwank_wowk *wowk, stwuct dwm_cwtc *cwtc,
			  void (*func)(stwuct kthwead_wowk *wowk))
{
	kthwead_init_wowk(&wowk->base, func);
	INIT_WIST_HEAD(&wowk->node);
	wowk->vbwank = &cwtc->dev->vbwank[dwm_cwtc_index(cwtc)];
}
EXPOWT_SYMBOW(dwm_vbwank_wowk_init);

int dwm_vbwank_wowkew_init(stwuct dwm_vbwank_cwtc *vbwank)
{
	stwuct kthwead_wowkew *wowkew;

	INIT_WIST_HEAD(&vbwank->pending_wowk);
	init_waitqueue_head(&vbwank->wowk_wait_queue);
	wowkew = kthwead_cweate_wowkew(0, "cawd%d-cwtc%d",
				       vbwank->dev->pwimawy->index,
				       vbwank->pipe);
	if (IS_EWW(wowkew))
		wetuwn PTW_EWW(wowkew);

	vbwank->wowkew = wowkew;

	sched_set_fifo(wowkew->task);
	wetuwn 0;
}
