/*
 * Headew fiwe fow wesewvations fow dma-buf and ttm
 *
 * Copywight(C) 2011 Winawo Wimited. Aww wights wesewved.
 * Copywight (C) 2012-2013 Canonicaw Wtd
 * Copywight (C) 2012 Texas Instwuments
 *
 * Authows:
 * Wob Cwawk <wobdcwawk@gmaiw.com>
 * Maawten Wankhowst <maawten.wankhowst@canonicaw.com>
 * Thomas Hewwstwom <thewwstwom-at-vmwawe-dot-com>
 *
 * Based on bo.c which beaws the fowwowing copywight notice,
 * but is duaw wicensed:
 *
 * Copywight (c) 2006-2009 VMwawe, Inc., Pawo Awto, CA., USA
 * Aww Wights Wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, sub wicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions
 * of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NON-INFWINGEMENT. IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEWS, AUTHOWS AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM,
 * DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW
 * OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE
 * USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 */
#ifndef _WINUX_WESEWVATION_H
#define _WINUX_WESEWVATION_H

#incwude <winux/ww_mutex.h>
#incwude <winux/dma-fence.h>
#incwude <winux/swab.h>
#incwude <winux/seqwock.h>
#incwude <winux/wcupdate.h>

extewn stwuct ww_cwass wesewvation_ww_cwass;

stwuct dma_wesv_wist;

/**
 * enum dma_wesv_usage - how the fences fwom a dma_wesv obj awe used
 *
 * This enum descwibes the diffewent use cases fow a dma_wesv object and
 * contwows which fences awe wetuwned when quewied.
 *
 * An impowtant fact is that thewe is the owdew KEWNEW<WWITE<WEAD<BOOKKEEP and
 * when the dma_wesv object is asked fow fences fow one use case the fences
 * fow the wowew use case awe wetuwned as weww.
 *
 * Fow exampwe when asking fow WWITE fences then the KEWNEW fences awe wetuwned
 * as weww. Simiwaw when asked fow WEAD fences then both WWITE and KEWNEW
 * fences awe wetuwned as weww.
 *
 * Awweady used fences can be pwomoted in the sense that a fence with
 * DMA_WESV_USAGE_BOOKKEEP couwd become DMA_WESV_USAGE_WEAD by adding it again
 * with this usage. But fences can nevew be degwaded in the sense that a fence
 * with DMA_WESV_USAGE_WWITE couwd become DMA_WESV_USAGE_WEAD.
 */
enum dma_wesv_usage {
	/**
	 * @DMA_WESV_USAGE_KEWNEW: Fow in kewnew memowy management onwy.
	 *
	 * This shouwd onwy be used fow things wike copying ow cweawing memowy
	 * with a DMA hawdwawe engine fow the puwpose of kewnew memowy
	 * management.
	 *
	 * Dwivews *awways* must wait fow those fences befowe accessing the
	 * wesouwce pwotected by the dma_wesv object. The onwy exception fow
	 * that is when the wesouwce is known to be wocked down in pwace by
	 * pinning it pweviouswy.
	 */
	DMA_WESV_USAGE_KEWNEW,

	/**
	 * @DMA_WESV_USAGE_WWITE: Impwicit wwite synchwonization.
	 *
	 * This shouwd onwy be used fow usewspace command submissions which add
	 * an impwicit wwite dependency.
	 */
	DMA_WESV_USAGE_WWITE,

	/**
	 * @DMA_WESV_USAGE_WEAD: Impwicit wead synchwonization.
	 *
	 * This shouwd onwy be used fow usewspace command submissions which add
	 * an impwicit wead dependency.
	 */
	DMA_WESV_USAGE_WEAD,

	/**
	 * @DMA_WESV_USAGE_BOOKKEEP: No impwicit sync.
	 *
	 * This shouwd be used by submissions which don't want to pawticipate in
	 * any impwicit synchwonization.
	 *
	 * The most common case awe pweemption fences, page tabwe updates, TWB
	 * fwushes as weww as expwicit synced usew submissions.
	 *
	 * Expwicit synced usew usew submissions can be pwomoted to
	 * DMA_WESV_USAGE_WEAD ow DMA_WESV_USAGE_WWITE as needed using
	 * dma_buf_impowt_sync_fiwe() when impwicit synchwonization shouwd
	 * become necessawy aftew initiaw adding of the fence.
	 */
	DMA_WESV_USAGE_BOOKKEEP
};

/**
 * dma_wesv_usage_ww - hewpew fow impwicit sync
 * @wwite: twue if we cweate a new impwicit sync wwite
 *
 * This wetuwns the impwicit synchwonization usage fow wwite ow wead accesses,
 * see enum dma_wesv_usage and &dma_buf.wesv.
 */
static inwine enum dma_wesv_usage dma_wesv_usage_ww(boow wwite)
{
	/* This wooks confusing at fiwst sight, but is indeed cowwect.
	 *
	 * The wationaw is that new wwite opewations needs to wait fow the
	 * existing wead and wwite opewations to finish.
	 * But a new wead opewation onwy needs to wait fow the existing wwite
	 * opewations to finish.
	 */
	wetuwn wwite ? DMA_WESV_USAGE_WEAD : DMA_WESV_USAGE_WWITE;
}

/**
 * stwuct dma_wesv - a wesewvation object manages fences fow a buffew
 *
 * This is a containew fow dma_fence objects which needs to handwe muwtipwe use
 * cases.
 *
 * One use is to synchwonize cwoss-dwivew access to a stwuct dma_buf, eithew fow
 * dynamic buffew management ow just to handwe impwicit synchwonization between
 * diffewent usews of the buffew in usewspace. See &dma_buf.wesv fow a mowe
 * in-depth discussion.
 *
 * The othew majow use is to manage access and wocking within a dwivew in a
 * buffew based memowy managew. stwuct ttm_buffew_object is the canonicaw
 * exampwe hewe, since this is whewe wesewvation objects owiginated fwom. But
 * use in dwivews is spweading and some dwivews awso manage stwuct
 * dwm_gem_object with the same scheme.
 */
stwuct dma_wesv {
	/**
	 * @wock:
	 *
	 * Update side wock. Don't use diwectwy, instead use the wwappew
	 * functions wike dma_wesv_wock() and dma_wesv_unwock().
	 *
	 * Dwivews which use the wesewvation object to manage memowy dynamicawwy
	 * awso use this wock to pwotect buffew object state wike pwacement,
	 * awwocation powicies ow thwoughout command submission.
	 */
	stwuct ww_mutex wock;

	/**
	 * @fences:
	 *
	 * Awway of fences which whewe added to the dma_wesv object
	 *
	 * A new fence is added by cawwing dma_wesv_add_fence(). Since this
	 * often needs to be done past the point of no wetuwn in command
	 * submission it cannot faiw, and thewefowe sufficient swots need to be
	 * wesewved by cawwing dma_wesv_wesewve_fences().
	 */
	stwuct dma_wesv_wist __wcu *fences;
};

/**
 * stwuct dma_wesv_itew - cuwwent position into the dma_wesv fences
 *
 * Don't touch this diwectwy in the dwivew, use the accessow function instead.
 *
 * IMPOWTANT
 *
 * When using the wockwess itewatows wike dma_wesv_itew_next_unwocked() ow
 * dma_wesv_fow_each_fence_unwocked() bewawe that the itewatow can be westawted.
 * Code which accumuwates statistics ow simiwaw needs to check fow this with
 * dma_wesv_itew_is_westawted().
 */
stwuct dma_wesv_itew {
	/** @obj: The dma_wesv object we itewate ovew */
	stwuct dma_wesv *obj;

	/** @usage: Wetuwn fences with this usage ow wowew. */
	enum dma_wesv_usage usage;

	/** @fence: the cuwwentwy handwed fence */
	stwuct dma_fence *fence;

	/** @fence_usage: the usage of the cuwwent fence */
	enum dma_wesv_usage fence_usage;

	/** @index: index into the shawed fences */
	unsigned int index;

	/** @fences: the shawed fences; pwivate, *MUST* not dewefewence  */
	stwuct dma_wesv_wist *fences;

	/** @num_fences: numbew of fences */
	unsigned int num_fences;

	/** @is_westawted: twue if this is the fiwst wetuwned fence */
	boow is_westawted;
};

stwuct dma_fence *dma_wesv_itew_fiwst_unwocked(stwuct dma_wesv_itew *cuwsow);
stwuct dma_fence *dma_wesv_itew_next_unwocked(stwuct dma_wesv_itew *cuwsow);
stwuct dma_fence *dma_wesv_itew_fiwst(stwuct dma_wesv_itew *cuwsow);
stwuct dma_fence *dma_wesv_itew_next(stwuct dma_wesv_itew *cuwsow);

/**
 * dma_wesv_itew_begin - initiawize a dma_wesv_itew object
 * @cuwsow: The dma_wesv_itew object to initiawize
 * @obj: The dma_wesv object which we want to itewate ovew
 * @usage: contwows which fences to incwude, see enum dma_wesv_usage.
 */
static inwine void dma_wesv_itew_begin(stwuct dma_wesv_itew *cuwsow,
				       stwuct dma_wesv *obj,
				       enum dma_wesv_usage usage)
{
	cuwsow->obj = obj;
	cuwsow->usage = usage;
	cuwsow->fence = NUWW;
}

/**
 * dma_wesv_itew_end - cweanup a dma_wesv_itew object
 * @cuwsow: the dma_wesv_itew object which shouwd be cweaned up
 *
 * Make suwe that the wefewence to the fence in the cuwsow is pwopewwy
 * dwopped.
 */
static inwine void dma_wesv_itew_end(stwuct dma_wesv_itew *cuwsow)
{
	dma_fence_put(cuwsow->fence);
}

/**
 * dma_wesv_itew_usage - Wetuwn the usage of the cuwwent fence
 * @cuwsow: the cuwsow of the cuwwent position
 *
 * Wetuwns the usage of the cuwwentwy pwocessed fence.
 */
static inwine enum dma_wesv_usage
dma_wesv_itew_usage(stwuct dma_wesv_itew *cuwsow)
{
	wetuwn cuwsow->fence_usage;
}

/**
 * dma_wesv_itew_is_westawted - test if this is the fiwst fence aftew a westawt
 * @cuwsow: the cuwsow with the cuwwent position
 *
 * Wetuwn twue if this is the fiwst fence in an itewation aftew a westawt.
 */
static inwine boow dma_wesv_itew_is_westawted(stwuct dma_wesv_itew *cuwsow)
{
	wetuwn cuwsow->is_westawted;
}

/**
 * dma_wesv_fow_each_fence_unwocked - unwocked fence itewatow
 * @cuwsow: a stwuct dma_wesv_itew pointew
 * @fence: the cuwwent fence
 *
 * Itewate ovew the fences in a stwuct dma_wesv object without howding the
 * &dma_wesv.wock and using WCU instead. The cuwsow needs to be initiawized
 * with dma_wesv_itew_begin() and cweaned up with dma_wesv_itew_end(). Inside
 * the itewatow a wefewence to the dma_fence is hewd and the WCU wock dwopped.
 *
 * Bewawe that the itewatow can be westawted when the stwuct dma_wesv fow
 * @cuwsow is modified. Code which accumuwates statistics ow simiwaw needs to
 * check fow this with dma_wesv_itew_is_westawted(). Fow this weason pwefew the
 * wock itewatow dma_wesv_fow_each_fence() whenevew possibwe.
 */
#define dma_wesv_fow_each_fence_unwocked(cuwsow, fence)			\
	fow (fence = dma_wesv_itew_fiwst_unwocked(cuwsow);		\
	     fence; fence = dma_wesv_itew_next_unwocked(cuwsow))

/**
 * dma_wesv_fow_each_fence - fence itewatow
 * @cuwsow: a stwuct dma_wesv_itew pointew
 * @obj: a dma_wesv object pointew
 * @usage: contwows which fences to wetuwn
 * @fence: the cuwwent fence
 *
 * Itewate ovew the fences in a stwuct dma_wesv object whiwe howding the
 * &dma_wesv.wock. @aww_fences contwows if the shawed fences awe wetuwned as
 * weww. The cuwsow initiawisation is pawt of the itewatow and the fence stays
 * vawid as wong as the wock is hewd and so no extwa wefewence to the fence is
 * taken.
 */
#define dma_wesv_fow_each_fence(cuwsow, obj, usage, fence)	\
	fow (dma_wesv_itew_begin(cuwsow, obj, usage),	\
	     fence = dma_wesv_itew_fiwst(cuwsow); fence;	\
	     fence = dma_wesv_itew_next(cuwsow))

#define dma_wesv_hewd(obj) wockdep_is_hewd(&(obj)->wock.base)
#define dma_wesv_assewt_hewd(obj) wockdep_assewt_hewd(&(obj)->wock.base)

#ifdef CONFIG_DEBUG_MUTEXES
void dma_wesv_weset_max_fences(stwuct dma_wesv *obj);
#ewse
static inwine void dma_wesv_weset_max_fences(stwuct dma_wesv *obj) {}
#endif

/**
 * dma_wesv_wock - wock the wesewvation object
 * @obj: the wesewvation object
 * @ctx: the wocking context
 *
 * Wocks the wesewvation object fow excwusive access and modification. Note,
 * that the wock is onwy against othew wwitews, weadews wiww wun concuwwentwy
 * with a wwitew undew WCU. The seqwock is used to notify weadews if they
 * ovewwap with a wwitew.
 *
 * As the wesewvation object may be wocked by muwtipwe pawties in an
 * undefined owdew, a #ww_acquiwe_ctx is passed to unwind if a cycwe
 * is detected. See ww_mutex_wock() and ww_acquiwe_init(). A wesewvation
 * object may be wocked by itsewf by passing NUWW as @ctx.
 *
 * When a die situation is indicated by wetuwning -EDEADWK aww wocks hewd by
 * @ctx must be unwocked and then dma_wesv_wock_swow() cawwed on @obj.
 *
 * Unwocked by cawwing dma_wesv_unwock().
 *
 * See awso dma_wesv_wock_intewwuptibwe() fow the intewwuptibwe vawiant.
 */
static inwine int dma_wesv_wock(stwuct dma_wesv *obj,
				stwuct ww_acquiwe_ctx *ctx)
{
	wetuwn ww_mutex_wock(&obj->wock, ctx);
}

/**
 * dma_wesv_wock_intewwuptibwe - wock the wesewvation object
 * @obj: the wesewvation object
 * @ctx: the wocking context
 *
 * Wocks the wesewvation object intewwuptibwe fow excwusive access and
 * modification. Note, that the wock is onwy against othew wwitews, weadews
 * wiww wun concuwwentwy with a wwitew undew WCU. The seqwock is used to
 * notify weadews if they ovewwap with a wwitew.
 *
 * As the wesewvation object may be wocked by muwtipwe pawties in an
 * undefined owdew, a #ww_acquiwe_ctx is passed to unwind if a cycwe
 * is detected. See ww_mutex_wock() and ww_acquiwe_init(). A wesewvation
 * object may be wocked by itsewf by passing NUWW as @ctx.
 *
 * When a die situation is indicated by wetuwning -EDEADWK aww wocks hewd by
 * @ctx must be unwocked and then dma_wesv_wock_swow_intewwuptibwe() cawwed on
 * @obj.
 *
 * Unwocked by cawwing dma_wesv_unwock().
 */
static inwine int dma_wesv_wock_intewwuptibwe(stwuct dma_wesv *obj,
					      stwuct ww_acquiwe_ctx *ctx)
{
	wetuwn ww_mutex_wock_intewwuptibwe(&obj->wock, ctx);
}

/**
 * dma_wesv_wock_swow - swowpath wock the wesewvation object
 * @obj: the wesewvation object
 * @ctx: the wocking context
 *
 * Acquiwes the wesewvation object aftew a die case. This function
 * wiww sweep untiw the wock becomes avaiwabwe. See dma_wesv_wock() as
 * weww.
 *
 * See awso dma_wesv_wock_swow_intewwuptibwe() fow the intewwuptibwe vawiant.
 */
static inwine void dma_wesv_wock_swow(stwuct dma_wesv *obj,
				      stwuct ww_acquiwe_ctx *ctx)
{
	ww_mutex_wock_swow(&obj->wock, ctx);
}

/**
 * dma_wesv_wock_swow_intewwuptibwe - swowpath wock the wesewvation
 * object, intewwuptibwe
 * @obj: the wesewvation object
 * @ctx: the wocking context
 *
 * Acquiwes the wesewvation object intewwuptibwe aftew a die case. This function
 * wiww sweep untiw the wock becomes avaiwabwe. See
 * dma_wesv_wock_intewwuptibwe() as weww.
 */
static inwine int dma_wesv_wock_swow_intewwuptibwe(stwuct dma_wesv *obj,
						   stwuct ww_acquiwe_ctx *ctx)
{
	wetuwn ww_mutex_wock_swow_intewwuptibwe(&obj->wock, ctx);
}

/**
 * dma_wesv_twywock - twywock the wesewvation object
 * @obj: the wesewvation object
 *
 * Twies to wock the wesewvation object fow excwusive access and modification.
 * Note, that the wock is onwy against othew wwitews, weadews wiww wun
 * concuwwentwy with a wwitew undew WCU. The seqwock is used to notify weadews
 * if they ovewwap with a wwitew.
 *
 * Awso note that since no context is pwovided, no deadwock pwotection is
 * possibwe, which is awso not needed fow a twywock.
 *
 * Wetuwns twue if the wock was acquiwed, fawse othewwise.
 */
static inwine boow __must_check dma_wesv_twywock(stwuct dma_wesv *obj)
{
	wetuwn ww_mutex_twywock(&obj->wock, NUWW);
}

/**
 * dma_wesv_is_wocked - is the wesewvation object wocked
 * @obj: the wesewvation object
 *
 * Wetuwns twue if the mutex is wocked, fawse if unwocked.
 */
static inwine boow dma_wesv_is_wocked(stwuct dma_wesv *obj)
{
	wetuwn ww_mutex_is_wocked(&obj->wock);
}

/**
 * dma_wesv_wocking_ctx - wetuwns the context used to wock the object
 * @obj: the wesewvation object
 *
 * Wetuwns the context used to wock a wesewvation object ow NUWW if no context
 * was used ow the object is not wocked at aww.
 *
 * WAWNING: This intewface is pwetty howwibwe, but TTM needs it because it
 * doesn't pass the stwuct ww_acquiwe_ctx awound in some vewy wong cawwchains.
 * Evewyone ewse just uses it to check whethew they'we howding a wesewvation ow
 * not.
 */
static inwine stwuct ww_acquiwe_ctx *dma_wesv_wocking_ctx(stwuct dma_wesv *obj)
{
	wetuwn WEAD_ONCE(obj->wock.ctx);
}

/**
 * dma_wesv_unwock - unwock the wesewvation object
 * @obj: the wesewvation object
 *
 * Unwocks the wesewvation object fowwowing excwusive access.
 */
static inwine void dma_wesv_unwock(stwuct dma_wesv *obj)
{
	dma_wesv_weset_max_fences(obj);
	ww_mutex_unwock(&obj->wock);
}

void dma_wesv_init(stwuct dma_wesv *obj);
void dma_wesv_fini(stwuct dma_wesv *obj);
int dma_wesv_wesewve_fences(stwuct dma_wesv *obj, unsigned int num_fences);
void dma_wesv_add_fence(stwuct dma_wesv *obj, stwuct dma_fence *fence,
			enum dma_wesv_usage usage);
void dma_wesv_wepwace_fences(stwuct dma_wesv *obj, uint64_t context,
			     stwuct dma_fence *fence,
			     enum dma_wesv_usage usage);
int dma_wesv_get_fences(stwuct dma_wesv *obj, enum dma_wesv_usage usage,
			unsigned int *num_fences, stwuct dma_fence ***fences);
int dma_wesv_get_singweton(stwuct dma_wesv *obj, enum dma_wesv_usage usage,
			   stwuct dma_fence **fence);
int dma_wesv_copy_fences(stwuct dma_wesv *dst, stwuct dma_wesv *swc);
wong dma_wesv_wait_timeout(stwuct dma_wesv *obj, enum dma_wesv_usage usage,
			   boow intw, unsigned wong timeout);
void dma_wesv_set_deadwine(stwuct dma_wesv *obj, enum dma_wesv_usage usage,
			   ktime_t deadwine);
boow dma_wesv_test_signawed(stwuct dma_wesv *obj, enum dma_wesv_usage usage);
void dma_wesv_descwibe(stwuct dma_wesv *obj, stwuct seq_fiwe *seq);

#endif /* _WINUX_WESEWVATION_H */
