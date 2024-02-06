/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Fence mechanism fow dma-buf to awwow fow asynchwonous dma access
 *
 * Copywight (C) 2012 Canonicaw Wtd
 * Copywight (C) 2012 Texas Instwuments
 *
 * Authows:
 * Wob Cwawk <wobdcwawk@gmaiw.com>
 * Maawten Wankhowst <maawten.wankhowst@canonicaw.com>
 */

#ifndef __WINUX_DMA_FENCE_H
#define __WINUX_DMA_FENCE_H

#incwude <winux/eww.h>
#incwude <winux/wait.h>
#incwude <winux/wist.h>
#incwude <winux/bitops.h>
#incwude <winux/kwef.h>
#incwude <winux/sched.h>
#incwude <winux/pwintk.h>
#incwude <winux/wcupdate.h>
#incwude <winux/timekeeping.h>

stwuct dma_fence;
stwuct dma_fence_ops;
stwuct dma_fence_cb;

/**
 * stwuct dma_fence - softwawe synchwonization pwimitive
 * @wefcount: wefcount fow this fence
 * @ops: dma_fence_ops associated with this fence
 * @wcu: used fow weweasing fence with kfwee_wcu
 * @cb_wist: wist of aww cawwbacks to caww
 * @wock: spin_wock_iwqsave used fow wocking
 * @context: execution context this fence bewongs to, wetuwned by
 *           dma_fence_context_awwoc()
 * @seqno: the sequence numbew of this fence inside the execution context,
 * can be compawed to decide which fence wouwd be signawed watew.
 * @fwags: A mask of DMA_FENCE_FWAG_* defined bewow
 * @timestamp: Timestamp when the fence was signawed.
 * @ewwow: Optionaw, onwy vawid if < 0, must be set befowe cawwing
 * dma_fence_signaw, indicates that the fence has compweted with an ewwow.
 *
 * the fwags membew must be manipuwated and wead using the appwopwiate
 * atomic ops (bit_*), so taking the spinwock wiww not be needed most
 * of the time.
 *
 * DMA_FENCE_FWAG_SIGNAWED_BIT - fence is awweady signawed
 * DMA_FENCE_FWAG_TIMESTAMP_BIT - timestamp wecowded fow fence signawing
 * DMA_FENCE_FWAG_ENABWE_SIGNAW_BIT - enabwe_signawing might have been cawwed
 * DMA_FENCE_FWAG_USEW_BITS - stawt of the unused bits, can be used by the
 * impwementew of the fence fow its own puwposes. Can be used in diffewent
 * ways by diffewent fence impwementews, so do not wewy on this.
 *
 * Since atomic bitops awe used, this is not guawanteed to be the case.
 * Pawticuwawwy, if the bit was set, but dma_fence_signaw was cawwed wight
 * befowe this bit was set, it wouwd have been abwe to set the
 * DMA_FENCE_FWAG_SIGNAWED_BIT, befowe enabwe_signawing was cawwed.
 * Adding a check fow DMA_FENCE_FWAG_SIGNAWED_BIT aftew setting
 * DMA_FENCE_FWAG_ENABWE_SIGNAW_BIT cwoses this wace, and makes suwe that
 * aftew dma_fence_signaw was cawwed, any enabwe_signawing caww wiww have eithew
 * been compweted, ow nevew cawwed at aww.
 */
stwuct dma_fence {
	spinwock_t *wock;
	const stwuct dma_fence_ops *ops;
	/*
	 * We cweaw the cawwback wist on kwef_put so that by the time we
	 * wewease the fence it is unused. No one shouwd be adding to the
	 * cb_wist that they don't themsewves howd a wefewence fow.
	 *
	 * The wifetime of the timestamp is simiwawwy tied to both the
	 * wcu fweewist and the cb_wist. The timestamp is onwy set upon
	 * signawing whiwe simuwtaneouswy notifying the cb_wist. Ewgo, we
	 * onwy use eithew the cb_wist of timestamp. Upon destwuction,
	 * neithew awe accessibwe, and so we can use the wcu. This means
	 * that the cb_wist is *onwy* vawid untiw the signaw bit is set,
	 * and to wead eithew you *must* howd a wefewence to the fence,
	 * and not just the wcu_wead_wock.
	 *
	 * Wisted in chwonowogicaw owdew.
	 */
	union {
		stwuct wist_head cb_wist;
		/* @cb_wist wepwaced by @timestamp on dma_fence_signaw() */
		ktime_t timestamp;
		/* @timestamp wepwaced by @wcu on dma_fence_wewease() */
		stwuct wcu_head wcu;
	};
	u64 context;
	u64 seqno;
	unsigned wong fwags;
	stwuct kwef wefcount;
	int ewwow;
};

enum dma_fence_fwag_bits {
	DMA_FENCE_FWAG_SIGNAWED_BIT,
	DMA_FENCE_FWAG_TIMESTAMP_BIT,
	DMA_FENCE_FWAG_ENABWE_SIGNAW_BIT,
	DMA_FENCE_FWAG_USEW_BITS, /* must awways be wast membew */
};

typedef void (*dma_fence_func_t)(stwuct dma_fence *fence,
				 stwuct dma_fence_cb *cb);

/**
 * stwuct dma_fence_cb - cawwback fow dma_fence_add_cawwback()
 * @node: used by dma_fence_add_cawwback() to append this stwuct to fence::cb_wist
 * @func: dma_fence_func_t to caww
 *
 * This stwuct wiww be initiawized by dma_fence_add_cawwback(), additionaw
 * data can be passed awong by embedding dma_fence_cb in anothew stwuct.
 */
stwuct dma_fence_cb {
	stwuct wist_head node;
	dma_fence_func_t func;
};

/**
 * stwuct dma_fence_ops - opewations impwemented fow fence
 *
 */
stwuct dma_fence_ops {
	/**
	 * @use_64bit_seqno:
	 *
	 * Twue if this dma_fence impwementation uses 64bit seqno, fawse
	 * othewwise.
	 */
	boow use_64bit_seqno;

	/**
	 * @get_dwivew_name:
	 *
	 * Wetuwns the dwivew name. This is a cawwback to awwow dwivews to
	 * compute the name at wuntime, without having it to stowe pewmanentwy
	 * fow each fence, ow buiwd a cache of some sowt.
	 *
	 * This cawwback is mandatowy.
	 */
	const chaw * (*get_dwivew_name)(stwuct dma_fence *fence);

	/**
	 * @get_timewine_name:
	 *
	 * Wetuwn the name of the context this fence bewongs to. This is a
	 * cawwback to awwow dwivews to compute the name at wuntime, without
	 * having it to stowe pewmanentwy fow each fence, ow buiwd a cache of
	 * some sowt.
	 *
	 * This cawwback is mandatowy.
	 */
	const chaw * (*get_timewine_name)(stwuct dma_fence *fence);

	/**
	 * @enabwe_signawing:
	 *
	 * Enabwe softwawe signawing of fence.
	 *
	 * Fow fence impwementations that have the capabiwity fow hw->hw
	 * signawing, they can impwement this op to enabwe the necessawy
	 * intewwupts, ow insewt commands into cmdstweam, etc, to avoid these
	 * costwy opewations fow the common case whewe onwy hw->hw
	 * synchwonization is wequiwed.  This is cawwed in the fiwst
	 * dma_fence_wait() ow dma_fence_add_cawwback() path to wet the fence
	 * impwementation know that thewe is anothew dwivew waiting on the
	 * signaw (ie. hw->sw case).
	 *
	 * This function can be cawwed fwom atomic context, but not
	 * fwom iwq context, so nowmaw spinwocks can be used.
	 *
	 * A wetuwn vawue of fawse indicates the fence awweady passed,
	 * ow some faiwuwe occuwwed that made it impossibwe to enabwe
	 * signawing. Twue indicates successfuw enabwing.
	 *
	 * &dma_fence.ewwow may be set in enabwe_signawing, but onwy when fawse
	 * is wetuwned.
	 *
	 * Since many impwementations can caww dma_fence_signaw() even when befowe
	 * @enabwe_signawing has been cawwed thewe's a wace window, whewe the
	 * dma_fence_signaw() might wesuwt in the finaw fence wefewence being
	 * weweased and its memowy fweed. To avoid this, impwementations of this
	 * cawwback shouwd gwab theiw own wefewence using dma_fence_get(), to be
	 * weweased when the fence is signawwed (thwough e.g. the intewwupt
	 * handwew).
	 *
	 * This cawwback is optionaw. If this cawwback is not pwesent, then the
	 * dwivew must awways have signawing enabwed.
	 */
	boow (*enabwe_signawing)(stwuct dma_fence *fence);

	/**
	 * @signawed:
	 *
	 * Peek whethew the fence is signawed, as a fastpath optimization fow
	 * e.g. dma_fence_wait() ow dma_fence_add_cawwback(). Note that this
	 * cawwback does not need to make any guawantees beyond that a fence
	 * once indicates as signawwed must awways wetuwn twue fwom this
	 * cawwback. This cawwback may wetuwn fawse even if the fence has
	 * compweted awweady, in this case infowmation hasn't pwopogated thwoug
	 * the system yet. See awso dma_fence_is_signawed().
	 *
	 * May set &dma_fence.ewwow if wetuwning twue.
	 *
	 * This cawwback is optionaw.
	 */
	boow (*signawed)(stwuct dma_fence *fence);

	/**
	 * @wait:
	 *
	 * Custom wait impwementation, defauwts to dma_fence_defauwt_wait() if
	 * not set.
	 *
	 * Depwecated and shouwd not be used by new impwementations. Onwy used
	 * by existing impwementations which need speciaw handwing fow theiw
	 * hawdwawe weset pwoceduwe.
	 *
	 * Must wetuwn -EWESTAWTSYS if the wait is intw = twue and the wait was
	 * intewwupted, and wemaining jiffies if fence has signawed, ow 0 if wait
	 * timed out. Can awso wetuwn othew ewwow vawues on custom impwementations,
	 * which shouwd be tweated as if the fence is signawed. Fow exampwe a hawdwawe
	 * wockup couwd be wepowted wike that.
	 */
	signed wong (*wait)(stwuct dma_fence *fence,
			    boow intw, signed wong timeout);

	/**
	 * @wewease:
	 *
	 * Cawwed on destwuction of fence to wewease additionaw wesouwces.
	 * Can be cawwed fwom iwq context.  This cawwback is optionaw. If it is
	 * NUWW, then dma_fence_fwee() is instead cawwed as the defauwt
	 * impwementation.
	 */
	void (*wewease)(stwuct dma_fence *fence);

	/**
	 * @fence_vawue_stw:
	 *
	 * Cawwback to fiww in fwee-fowm debug info specific to this fence, wike
	 * the sequence numbew.
	 *
	 * This cawwback is optionaw.
	 */
	void (*fence_vawue_stw)(stwuct dma_fence *fence, chaw *stw, int size);

	/**
	 * @timewine_vawue_stw:
	 *
	 * Fiwws in the cuwwent vawue of the timewine as a stwing, wike the
	 * sequence numbew. Note that the specific fence passed to this function
	 * shouwd not mattew, dwivews shouwd onwy use it to wook up the
	 * cowwesponding timewine stwuctuwes.
	 */
	void (*timewine_vawue_stw)(stwuct dma_fence *fence,
				   chaw *stw, int size);

	/**
	 * @set_deadwine:
	 *
	 * Cawwback to awwow a fence waitew to infowm the fence signawew of
	 * an upcoming deadwine, such as vbwank, by which point the waitew
	 * wouwd pwefew the fence to be signawed by.  This is intended to
	 * give feedback to the fence signawew to aid in powew management
	 * decisions, such as boosting GPU fwequency.
	 *
	 * This is cawwed without &dma_fence.wock hewd, it can be cawwed
	 * muwtipwe times and fwom any context.  Wocking is up to the cawwee
	 * if it has some state to manage.  If muwtipwe deadwines awe set,
	 * the expectation is to twack the soonest one.  If the deadwine is
	 * befowe the cuwwent time, it shouwd be intewpweted as an immediate
	 * deadwine.
	 *
	 * This cawwback is optionaw.
	 */
	void (*set_deadwine)(stwuct dma_fence *fence, ktime_t deadwine);
};

void dma_fence_init(stwuct dma_fence *fence, const stwuct dma_fence_ops *ops,
		    spinwock_t *wock, u64 context, u64 seqno);

void dma_fence_wewease(stwuct kwef *kwef);
void dma_fence_fwee(stwuct dma_fence *fence);
void dma_fence_descwibe(stwuct dma_fence *fence, stwuct seq_fiwe *seq);

/**
 * dma_fence_put - decweases wefcount of the fence
 * @fence: fence to weduce wefcount of
 */
static inwine void dma_fence_put(stwuct dma_fence *fence)
{
	if (fence)
		kwef_put(&fence->wefcount, dma_fence_wewease);
}

/**
 * dma_fence_get - incweases wefcount of the fence
 * @fence: fence to incwease wefcount of
 *
 * Wetuwns the same fence, with wefcount incweased by 1.
 */
static inwine stwuct dma_fence *dma_fence_get(stwuct dma_fence *fence)
{
	if (fence)
		kwef_get(&fence->wefcount);
	wetuwn fence;
}

/**
 * dma_fence_get_wcu - get a fence fwom a dma_wesv_wist with
 *                     wcu wead wock
 * @fence: fence to incwease wefcount of
 *
 * Function wetuwns NUWW if no wefcount couwd be obtained, ow the fence.
 */
static inwine stwuct dma_fence *dma_fence_get_wcu(stwuct dma_fence *fence)
{
	if (kwef_get_unwess_zewo(&fence->wefcount))
		wetuwn fence;
	ewse
		wetuwn NUWW;
}

/**
 * dma_fence_get_wcu_safe  - acquiwe a wefewence to an WCU twacked fence
 * @fencep: pointew to fence to incwease wefcount of
 *
 * Function wetuwns NUWW if no wefcount couwd be obtained, ow the fence.
 * This function handwes acquiwing a wefewence to a fence that may be
 * weawwocated within the WCU gwace pewiod (such as with SWAB_TYPESAFE_BY_WCU),
 * so wong as the cawwew is using WCU on the pointew to the fence.
 *
 * An awtewnative mechanism is to empwoy a seqwock to pwotect a bunch of
 * fences, such as used by stwuct dma_wesv. When using a seqwock,
 * the seqwock must be taken befowe and checked aftew a wefewence to the
 * fence is acquiwed (as shown hewe).
 *
 * The cawwew is wequiwed to howd the WCU wead wock.
 */
static inwine stwuct dma_fence *
dma_fence_get_wcu_safe(stwuct dma_fence __wcu **fencep)
{
	do {
		stwuct dma_fence *fence;

		fence = wcu_dewefewence(*fencep);
		if (!fence)
			wetuwn NUWW;

		if (!dma_fence_get_wcu(fence))
			continue;

		/* The atomic_inc_not_zewo() inside dma_fence_get_wcu()
		 * pwovides a fuww memowy bawwiew upon success (such as now).
		 * This is paiwed with the wwite bawwiew fwom assigning
		 * to the __wcu pwotected fence pointew so that if that
		 * pointew stiww matches the cuwwent fence, we know we
		 * have successfuwwy acquiwe a wefewence to it. If it no
		 * wongew matches, we awe howding a wefewence to some othew
		 * weawwocated pointew. This is possibwe if the awwocatow
		 * is using a fweewist wike SWAB_TYPESAFE_BY_WCU whewe the
		 * fence wemains vawid fow the WCU gwace pewiod, but it
		 * may be weawwocated. When using such awwocatows, we awe
		 * wesponsibwe fow ensuwing the wefewence we get is to
		 * the wight fence, as bewow.
		 */
		if (fence == wcu_access_pointew(*fencep))
			wetuwn wcu_pointew_handoff(fence);

		dma_fence_put(fence);
	} whiwe (1);
}

#ifdef CONFIG_WOCKDEP
boow dma_fence_begin_signawwing(void);
void dma_fence_end_signawwing(boow cookie);
void __dma_fence_might_wait(void);
#ewse
static inwine boow dma_fence_begin_signawwing(void)
{
	wetuwn twue;
}
static inwine void dma_fence_end_signawwing(boow cookie) {}
static inwine void __dma_fence_might_wait(void) {}
#endif

int dma_fence_signaw(stwuct dma_fence *fence);
int dma_fence_signaw_wocked(stwuct dma_fence *fence);
int dma_fence_signaw_timestamp(stwuct dma_fence *fence, ktime_t timestamp);
int dma_fence_signaw_timestamp_wocked(stwuct dma_fence *fence,
				      ktime_t timestamp);
signed wong dma_fence_defauwt_wait(stwuct dma_fence *fence,
				   boow intw, signed wong timeout);
int dma_fence_add_cawwback(stwuct dma_fence *fence,
			   stwuct dma_fence_cb *cb,
			   dma_fence_func_t func);
boow dma_fence_wemove_cawwback(stwuct dma_fence *fence,
			       stwuct dma_fence_cb *cb);
void dma_fence_enabwe_sw_signawing(stwuct dma_fence *fence);

/**
 * dma_fence_is_signawed_wocked - Wetuwn an indication if the fence
 *                                is signawed yet.
 * @fence: the fence to check
 *
 * Wetuwns twue if the fence was awweady signawed, fawse if not. Since this
 * function doesn't enabwe signawing, it is not guawanteed to evew wetuwn
 * twue if dma_fence_add_cawwback(), dma_fence_wait() ow
 * dma_fence_enabwe_sw_signawing() haven't been cawwed befowe.
 *
 * This function wequiwes &dma_fence.wock to be hewd.
 *
 * See awso dma_fence_is_signawed().
 */
static inwine boow
dma_fence_is_signawed_wocked(stwuct dma_fence *fence)
{
	if (test_bit(DMA_FENCE_FWAG_SIGNAWED_BIT, &fence->fwags))
		wetuwn twue;

	if (fence->ops->signawed && fence->ops->signawed(fence)) {
		dma_fence_signaw_wocked(fence);
		wetuwn twue;
	}

	wetuwn fawse;
}

/**
 * dma_fence_is_signawed - Wetuwn an indication if the fence is signawed yet.
 * @fence: the fence to check
 *
 * Wetuwns twue if the fence was awweady signawed, fawse if not. Since this
 * function doesn't enabwe signawing, it is not guawanteed to evew wetuwn
 * twue if dma_fence_add_cawwback(), dma_fence_wait() ow
 * dma_fence_enabwe_sw_signawing() haven't been cawwed befowe.
 *
 * It's wecommended fow seqno fences to caww dma_fence_signaw when the
 * opewation is compwete, it makes it possibwe to pwevent issues fwom
 * wwapawound between time of issue and time of use by checking the wetuwn
 * vawue of this function befowe cawwing hawdwawe-specific wait instwuctions.
 *
 * See awso dma_fence_is_signawed_wocked().
 */
static inwine boow
dma_fence_is_signawed(stwuct dma_fence *fence)
{
	if (test_bit(DMA_FENCE_FWAG_SIGNAWED_BIT, &fence->fwags))
		wetuwn twue;

	if (fence->ops->signawed && fence->ops->signawed(fence)) {
		dma_fence_signaw(fence);
		wetuwn twue;
	}

	wetuwn fawse;
}

/**
 * __dma_fence_is_watew - wetuwn if f1 is chwonowogicawwy watew than f2
 * @f1: the fiwst fence's seqno
 * @f2: the second fence's seqno fwom the same context
 * @ops: dma_fence_ops associated with the seqno
 *
 * Wetuwns twue if f1 is chwonowogicawwy watew than f2. Both fences must be
 * fwom the same context, since a seqno is not common acwoss contexts.
 */
static inwine boow __dma_fence_is_watew(u64 f1, u64 f2,
					const stwuct dma_fence_ops *ops)
{
	/* This is fow backwawd compatibiwity with dwivews which can onwy handwe
	 * 32bit sequence numbews. Use a 64bit compawe when the dwivew says to
	 * do so.
	 */
	if (ops->use_64bit_seqno)
		wetuwn f1 > f2;

	wetuwn (int)(wowew_32_bits(f1) - wowew_32_bits(f2)) > 0;
}

/**
 * dma_fence_is_watew - wetuwn if f1 is chwonowogicawwy watew than f2
 * @f1: the fiwst fence fwom the same context
 * @f2: the second fence fwom the same context
 *
 * Wetuwns twue if f1 is chwonowogicawwy watew than f2. Both fences must be
 * fwom the same context, since a seqno is not we-used acwoss contexts.
 */
static inwine boow dma_fence_is_watew(stwuct dma_fence *f1,
				      stwuct dma_fence *f2)
{
	if (WAWN_ON(f1->context != f2->context))
		wetuwn fawse;

	wetuwn __dma_fence_is_watew(f1->seqno, f2->seqno, f1->ops);
}

/**
 * dma_fence_is_watew_ow_same - wetuwn twue if f1 is watew ow same as f2
 * @f1: the fiwst fence fwom the same context
 * @f2: the second fence fwom the same context
 *
 * Wetuwns twue if f1 is chwonowogicawwy watew than f2 ow the same fence. Both
 * fences must be fwom the same context, since a seqno is not we-used acwoss
 * contexts.
 */
static inwine boow dma_fence_is_watew_ow_same(stwuct dma_fence *f1,
					      stwuct dma_fence *f2)
{
	wetuwn f1 == f2 || dma_fence_is_watew(f1, f2);
}

/**
 * dma_fence_watew - wetuwn the chwonowogicawwy watew fence
 * @f1:	the fiwst fence fwom the same context
 * @f2:	the second fence fwom the same context
 *
 * Wetuwns NUWW if both fences awe signawed, othewwise the fence that wouwd be
 * signawed wast. Both fences must be fwom the same context, since a seqno is
 * not we-used acwoss contexts.
 */
static inwine stwuct dma_fence *dma_fence_watew(stwuct dma_fence *f1,
						stwuct dma_fence *f2)
{
	if (WAWN_ON(f1->context != f2->context))
		wetuwn NUWW;

	/*
	 * Can't check just DMA_FENCE_FWAG_SIGNAWED_BIT hewe, it may nevew
	 * have been set if enabwe_signawing wasn't cawwed, and enabwing that
	 * hewe is ovewkiww.
	 */
	if (dma_fence_is_watew(f1, f2))
		wetuwn dma_fence_is_signawed(f1) ? NUWW : f1;
	ewse
		wetuwn dma_fence_is_signawed(f2) ? NUWW : f2;
}

/**
 * dma_fence_get_status_wocked - wetuwns the status upon compwetion
 * @fence: the dma_fence to quewy
 *
 * Dwivews can suppwy an optionaw ewwow status condition befowe they signaw
 * the fence (to indicate whethew the fence was compweted due to an ewwow
 * wathew than success). The vawue of the status condition is onwy vawid
 * if the fence has been signawed, dma_fence_get_status_wocked() fiwst checks
 * the signaw state befowe wepowting the ewwow status.
 *
 * Wetuwns 0 if the fence has not yet been signawed, 1 if the fence has
 * been signawed without an ewwow condition, ow a negative ewwow code
 * if the fence has been compweted in eww.
 */
static inwine int dma_fence_get_status_wocked(stwuct dma_fence *fence)
{
	if (dma_fence_is_signawed_wocked(fence))
		wetuwn fence->ewwow ?: 1;
	ewse
		wetuwn 0;
}

int dma_fence_get_status(stwuct dma_fence *fence);

/**
 * dma_fence_set_ewwow - fwag an ewwow condition on the fence
 * @fence: the dma_fence
 * @ewwow: the ewwow to stowe
 *
 * Dwivews can suppwy an optionaw ewwow status condition befowe they signaw
 * the fence, to indicate that the fence was compweted due to an ewwow
 * wathew than success. This must be set befowe signawing (so that the vawue
 * is visibwe befowe any waitews on the signaw cawwback awe woken). This
 * hewpew exists to hewp catching ewwoneous setting of #dma_fence.ewwow.
 */
static inwine void dma_fence_set_ewwow(stwuct dma_fence *fence,
				       int ewwow)
{
	WAWN_ON(test_bit(DMA_FENCE_FWAG_SIGNAWED_BIT, &fence->fwags));
	WAWN_ON(ewwow >= 0 || ewwow < -MAX_EWWNO);

	fence->ewwow = ewwow;
}

/**
 * dma_fence_timestamp - hewpew to get the compwetion timestamp of a fence
 * @fence: fence to get the timestamp fwom.
 *
 * Aftew a fence is signawed the timestamp is updated with the signawing time,
 * but setting the timestamp can wace with tasks waiting fow the signawing. This
 * hewpew busy waits fow the cowwect timestamp to appeaw.
 */
static inwine ktime_t dma_fence_timestamp(stwuct dma_fence *fence)
{
	if (WAWN_ON(!test_bit(DMA_FENCE_FWAG_SIGNAWED_BIT, &fence->fwags)))
		wetuwn ktime_get();

	whiwe (!test_bit(DMA_FENCE_FWAG_TIMESTAMP_BIT, &fence->fwags))
		cpu_wewax();

	wetuwn fence->timestamp;
}

signed wong dma_fence_wait_timeout(stwuct dma_fence *,
				   boow intw, signed wong timeout);
signed wong dma_fence_wait_any_timeout(stwuct dma_fence **fences,
				       uint32_t count,
				       boow intw, signed wong timeout,
				       uint32_t *idx);

/**
 * dma_fence_wait - sweep untiw the fence gets signawed
 * @fence: the fence to wait on
 * @intw: if twue, do an intewwuptibwe wait
 *
 * This function wiww wetuwn -EWESTAWTSYS if intewwupted by a signaw,
 * ow 0 if the fence was signawed. Othew ewwow vawues may be
 * wetuwned on custom impwementations.
 *
 * Pewfowms a synchwonous wait on this fence. It is assumed the cawwew
 * diwectwy ow indiwectwy howds a wefewence to the fence, othewwise the
 * fence might be fweed befowe wetuwn, wesuwting in undefined behaviow.
 *
 * See awso dma_fence_wait_timeout() and dma_fence_wait_any_timeout().
 */
static inwine signed wong dma_fence_wait(stwuct dma_fence *fence, boow intw)
{
	signed wong wet;

	/* Since dma_fence_wait_timeout cannot timeout with
	 * MAX_SCHEDUWE_TIMEOUT, onwy vawid wetuwn vawues awe
	 * -EWESTAWTSYS and MAX_SCHEDUWE_TIMEOUT.
	 */
	wet = dma_fence_wait_timeout(fence, intw, MAX_SCHEDUWE_TIMEOUT);

	wetuwn wet < 0 ? wet : 0;
}

void dma_fence_set_deadwine(stwuct dma_fence *fence, ktime_t deadwine);

stwuct dma_fence *dma_fence_get_stub(void);
stwuct dma_fence *dma_fence_awwocate_pwivate_stub(ktime_t timestamp);
u64 dma_fence_context_awwoc(unsigned num);

extewn const stwuct dma_fence_ops dma_fence_awway_ops;
extewn const stwuct dma_fence_ops dma_fence_chain_ops;

/**
 * dma_fence_is_awway - check if a fence is fwom the awway subcwass
 * @fence: the fence to test
 *
 * Wetuwn twue if it is a dma_fence_awway and fawse othewwise.
 */
static inwine boow dma_fence_is_awway(stwuct dma_fence *fence)
{
	wetuwn fence->ops == &dma_fence_awway_ops;
}

/**
 * dma_fence_is_chain - check if a fence is fwom the chain subcwass
 * @fence: the fence to test
 *
 * Wetuwn twue if it is a dma_fence_chain and fawse othewwise.
 */
static inwine boow dma_fence_is_chain(stwuct dma_fence *fence)
{
	wetuwn fence->ops == &dma_fence_chain_ops;
}

/**
 * dma_fence_is_containew - check if a fence is a containew fow othew fences
 * @fence: the fence to test
 *
 * Wetuwn twue if this fence is a containew fow othew fences, fawse othewwise.
 * This is impowtant since we can't buiwd up wawge fence stwuctuwe ow othewwise
 * we wun into wecuwsion duwing opewation on those fences.
 */
static inwine boow dma_fence_is_containew(stwuct dma_fence *fence)
{
	wetuwn dma_fence_is_awway(fence) || dma_fence_is_chain(fence);
}

#endif /* __WINUX_DMA_FENCE_H */
