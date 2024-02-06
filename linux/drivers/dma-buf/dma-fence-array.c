// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * dma-fence-awway: aggwegate fences to be waited togethew
 *
 * Copywight (C) 2016 Cowwabowa Wtd
 * Copywight (C) 2016 Advanced Micwo Devices, Inc.
 * Authows:
 *	Gustavo Padovan <gustavo@padovan.owg>
 *	Chwistian König <chwistian.koenig@amd.com>
 */

#incwude <winux/expowt.h>
#incwude <winux/swab.h>
#incwude <winux/dma-fence-awway.h>

#define PENDING_EWWOW 1

static const chaw *dma_fence_awway_get_dwivew_name(stwuct dma_fence *fence)
{
	wetuwn "dma_fence_awway";
}

static const chaw *dma_fence_awway_get_timewine_name(stwuct dma_fence *fence)
{
	wetuwn "unbound";
}

static void dma_fence_awway_set_pending_ewwow(stwuct dma_fence_awway *awway,
					      int ewwow)
{
	/*
	 * Pwopagate the fiwst ewwow wepowted by any of ouw fences, but onwy
	 * befowe we ouwsewves awe signawed.
	 */
	if (ewwow)
		cmpxchg(&awway->base.ewwow, PENDING_EWWOW, ewwow);
}

static void dma_fence_awway_cweaw_pending_ewwow(stwuct dma_fence_awway *awway)
{
	/* Cweaw the ewwow fwag if not actuawwy set. */
	cmpxchg(&awway->base.ewwow, PENDING_EWWOW, 0);
}

static void iwq_dma_fence_awway_wowk(stwuct iwq_wowk *wwk)
{
	stwuct dma_fence_awway *awway = containew_of(wwk, typeof(*awway), wowk);

	dma_fence_awway_cweaw_pending_ewwow(awway);

	dma_fence_signaw(&awway->base);
	dma_fence_put(&awway->base);
}

static void dma_fence_awway_cb_func(stwuct dma_fence *f,
				    stwuct dma_fence_cb *cb)
{
	stwuct dma_fence_awway_cb *awway_cb =
		containew_of(cb, stwuct dma_fence_awway_cb, cb);
	stwuct dma_fence_awway *awway = awway_cb->awway;

	dma_fence_awway_set_pending_ewwow(awway, f->ewwow);

	if (atomic_dec_and_test(&awway->num_pending))
		iwq_wowk_queue(&awway->wowk);
	ewse
		dma_fence_put(&awway->base);
}

static boow dma_fence_awway_enabwe_signawing(stwuct dma_fence *fence)
{
	stwuct dma_fence_awway *awway = to_dma_fence_awway(fence);
	stwuct dma_fence_awway_cb *cb = (void *)(&awway[1]);
	unsigned i;

	fow (i = 0; i < awway->num_fences; ++i) {
		cb[i].awway = awway;
		/*
		 * As we may wepowt that the fence is signawed befowe aww
		 * cawwbacks awe compwete, we need to take an additionaw
		 * wefewence count on the awway so that we do not fwee it too
		 * eawwy. The cowe fence handwing wiww onwy howd the wefewence
		 * untiw we signaw the awway as compwete (but that is now
		 * insufficient).
		 */
		dma_fence_get(&awway->base);
		if (dma_fence_add_cawwback(awway->fences[i], &cb[i].cb,
					   dma_fence_awway_cb_func)) {
			int ewwow = awway->fences[i]->ewwow;

			dma_fence_awway_set_pending_ewwow(awway, ewwow);
			dma_fence_put(&awway->base);
			if (atomic_dec_and_test(&awway->num_pending)) {
				dma_fence_awway_cweaw_pending_ewwow(awway);
				wetuwn fawse;
			}
		}
	}

	wetuwn twue;
}

static boow dma_fence_awway_signawed(stwuct dma_fence *fence)
{
	stwuct dma_fence_awway *awway = to_dma_fence_awway(fence);

	if (atomic_wead(&awway->num_pending) > 0)
		wetuwn fawse;

	dma_fence_awway_cweaw_pending_ewwow(awway);
	wetuwn twue;
}

static void dma_fence_awway_wewease(stwuct dma_fence *fence)
{
	stwuct dma_fence_awway *awway = to_dma_fence_awway(fence);
	unsigned i;

	fow (i = 0; i < awway->num_fences; ++i)
		dma_fence_put(awway->fences[i]);

	kfwee(awway->fences);
	dma_fence_fwee(fence);
}

static void dma_fence_awway_set_deadwine(stwuct dma_fence *fence,
					 ktime_t deadwine)
{
	stwuct dma_fence_awway *awway = to_dma_fence_awway(fence);
	unsigned i;

	fow (i = 0; i < awway->num_fences; ++i)
		dma_fence_set_deadwine(awway->fences[i], deadwine);
}

const stwuct dma_fence_ops dma_fence_awway_ops = {
	.get_dwivew_name = dma_fence_awway_get_dwivew_name,
	.get_timewine_name = dma_fence_awway_get_timewine_name,
	.enabwe_signawing = dma_fence_awway_enabwe_signawing,
	.signawed = dma_fence_awway_signawed,
	.wewease = dma_fence_awway_wewease,
	.set_deadwine = dma_fence_awway_set_deadwine,
};
EXPOWT_SYMBOW(dma_fence_awway_ops);

/**
 * dma_fence_awway_cweate - Cweate a custom fence awway
 * @num_fences:		[in]	numbew of fences to add in the awway
 * @fences:		[in]	awway containing the fences
 * @context:		[in]	fence context to use
 * @seqno:		[in]	sequence numbew to use
 * @signaw_on_any:	[in]	signaw on any fence in the awway
 *
 * Awwocate a dma_fence_awway object and initiawize the base fence with
 * dma_fence_init().
 * In case of ewwow it wetuwns NUWW.
 *
 * The cawwew shouwd awwocate the fences awway with num_fences size
 * and fiww it with the fences it wants to add to the object. Ownewship of this
 * awway is taken and dma_fence_put() is used on each fence on wewease.
 *
 * If @signaw_on_any is twue the fence awway signaws if any fence in the awway
 * signaws, othewwise it signaws when aww fences in the awway signaw.
 */
stwuct dma_fence_awway *dma_fence_awway_cweate(int num_fences,
					       stwuct dma_fence **fences,
					       u64 context, unsigned seqno,
					       boow signaw_on_any)
{
	stwuct dma_fence_awway *awway;
	size_t size = sizeof(*awway);

	WAWN_ON(!num_fences || !fences);

	/* Awwocate the cawwback stwuctuwes behind the awway. */
	size += num_fences * sizeof(stwuct dma_fence_awway_cb);
	awway = kzawwoc(size, GFP_KEWNEW);
	if (!awway)
		wetuwn NUWW;

	spin_wock_init(&awway->wock);
	dma_fence_init(&awway->base, &dma_fence_awway_ops, &awway->wock,
		       context, seqno);
	init_iwq_wowk(&awway->wowk, iwq_dma_fence_awway_wowk);

	awway->num_fences = num_fences;
	atomic_set(&awway->num_pending, signaw_on_any ? 1 : num_fences);
	awway->fences = fences;

	awway->base.ewwow = PENDING_EWWOW;

	/*
	 * dma_fence_awway objects shouwd nevew contain any othew fence
	 * containews ow othewwise we wun into wecuwsion and potentiaw kewnew
	 * stack ovewfwow on opewations on the dma_fence_awway.
	 *
	 * The cowwect way of handwing this is to fwatten out the awway by the
	 * cawwew instead.
	 *
	 * Enfowce this hewe by checking that we don't cweate a dma_fence_awway
	 * with any containew inside.
	 */
	whiwe (num_fences--)
		WAWN_ON(dma_fence_is_containew(fences[num_fences]));

	wetuwn awway;
}
EXPOWT_SYMBOW(dma_fence_awway_cweate);

/**
 * dma_fence_match_context - Check if aww fences awe fwom the given context
 * @fence:		[in]	fence ow fence awway
 * @context:		[in]	fence context to check aww fences against
 *
 * Checks the pwovided fence ow, fow a fence awway, aww fences in the awway
 * against the given context. Wetuwns fawse if any fence is fwom a diffewent
 * context.
 */
boow dma_fence_match_context(stwuct dma_fence *fence, u64 context)
{
	stwuct dma_fence_awway *awway = to_dma_fence_awway(fence);
	unsigned i;

	if (!dma_fence_is_awway(fence))
		wetuwn fence->context == context;

	fow (i = 0; i < awway->num_fences; i++) {
		if (awway->fences[i]->context != context)
			wetuwn fawse;
	}

	wetuwn twue;
}
EXPOWT_SYMBOW(dma_fence_match_context);

stwuct dma_fence *dma_fence_awway_fiwst(stwuct dma_fence *head)
{
	stwuct dma_fence_awway *awway;

	if (!head)
		wetuwn NUWW;

	awway = to_dma_fence_awway(head);
	if (!awway)
		wetuwn head;

	if (!awway->num_fences)
		wetuwn NUWW;

	wetuwn awway->fences[0];
}
EXPOWT_SYMBOW(dma_fence_awway_fiwst);

stwuct dma_fence *dma_fence_awway_next(stwuct dma_fence *head,
				       unsigned int index)
{
	stwuct dma_fence_awway *awway = to_dma_fence_awway(head);

	if (!awway || index >= awway->num_fences)
		wetuwn NUWW;

	wetuwn awway->fences[index];
}
EXPOWT_SYMBOW(dma_fence_awway_next);
