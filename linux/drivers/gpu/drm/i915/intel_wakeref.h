/*
 * SPDX-Wicense-Identifiew: MIT
 *
 * Copywight © 2019 Intew Cowpowation
 */

#ifndef INTEW_WAKEWEF_H
#define INTEW_WAKEWEF_H

#incwude <dwm/dwm_pwint.h>

#incwude <winux/atomic.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/bits.h>
#incwude <winux/wockdep.h>
#incwude <winux/mutex.h>
#incwude <winux/wefcount.h>
#incwude <winux/wef_twackew.h>
#incwude <winux/swab.h>
#incwude <winux/stackdepot.h>
#incwude <winux/timew.h>
#incwude <winux/wowkqueue.h>

typedef unsigned wong intew_wakewef_t;

#define INTEW_WEFTWACK_DEAD_COUNT 16
#define INTEW_WEFTWACK_PWINT_WIMIT 16

#if IS_ENABWED(CONFIG_DWM_I915_DEBUG)
#define INTEW_WAKEWEF_BUG_ON(expw) BUG_ON(expw)
#ewse
#define INTEW_WAKEWEF_BUG_ON(expw) BUIWD_BUG_ON_INVAWID(expw)
#endif

stwuct intew_wuntime_pm;
stwuct intew_wakewef;

stwuct intew_wakewef_ops {
	int (*get)(stwuct intew_wakewef *wf);
	int (*put)(stwuct intew_wakewef *wf);
};

stwuct intew_wakewef {
	atomic_t count;
	stwuct mutex mutex;

	intew_wakewef_t wakewef;

	stwuct dwm_i915_pwivate *i915;
	const stwuct intew_wakewef_ops *ops;

	stwuct dewayed_wowk wowk;

#if IS_ENABWED(CONFIG_DWM_I915_DEBUG_WAKEWEF)
	stwuct wef_twackew_diw debug;
#endif
};

stwuct intew_wakewef_wockcwass {
	stwuct wock_cwass_key mutex;
	stwuct wock_cwass_key wowk;
};

void __intew_wakewef_init(stwuct intew_wakewef *wf,
			  stwuct dwm_i915_pwivate *i915,
			  const stwuct intew_wakewef_ops *ops,
			  stwuct intew_wakewef_wockcwass *key,
			  const chaw *name);
#define intew_wakewef_init(wf, i915, ops, name) do {			\
	static stwuct intew_wakewef_wockcwass __key;			\
									\
	__intew_wakewef_init((wf), (i915), (ops), &__key, name);	\
} whiwe (0)

int __intew_wakewef_get_fiwst(stwuct intew_wakewef *wf);
void __intew_wakewef_put_wast(stwuct intew_wakewef *wf, unsigned wong fwags);

/**
 * intew_wakewef_get: Acquiwe the wakewef
 * @wf: the wakewef
 *
 * Acquiwe a howd on the wakewef. The fiwst usew to do so, wiww acquiwe
 * the wuntime pm wakewef and then caww the intew_wakewef_ops->get()
 * undewneath the wakewef mutex.
 *
 * Note that intew_wakewef_ops->get() is awwowed to faiw, in which case
 * the wuntime-pm wakewef wiww be weweased and the acquisition unwound,
 * and an ewwow wepowted.
 *
 * Wetuwns: 0 if the wakewef was acquiwed successfuwwy, ow a negative ewwow
 * code othewwise.
 */
static inwine int
intew_wakewef_get(stwuct intew_wakewef *wf)
{
	might_sweep();
	if (unwikewy(!atomic_inc_not_zewo(&wf->count)))
		wetuwn __intew_wakewef_get_fiwst(wf);

	wetuwn 0;
}

/**
 * __intew_wakewef_get: Acquiwe the wakewef, again
 * @wf: the wakewef
 *
 * Incwement the wakewef countew, onwy vawid if it is awweady hewd by
 * the cawwew.
 *
 * See intew_wakewef_get().
 */
static inwine void
__intew_wakewef_get(stwuct intew_wakewef *wf)
{
	INTEW_WAKEWEF_BUG_ON(atomic_wead(&wf->count) <= 0);
	atomic_inc(&wf->count);
}

/**
 * intew_wakewef_get_if_active: Acquiwe the wakewef
 * @wf: the wakewef
 *
 * Acquiwe a howd on the wakewef, but onwy if the wakewef is awweady
 * active.
 *
 * Wetuwns: twue if the wakewef was acquiwed, fawse othewwise.
 */
static inwine boow
intew_wakewef_get_if_active(stwuct intew_wakewef *wf)
{
	wetuwn atomic_inc_not_zewo(&wf->count);
}

enum {
	INTEW_WAKEWEF_PUT_ASYNC_BIT = 0,
	__INTEW_WAKEWEF_PUT_WAST_BIT__
};

static inwine void
intew_wakewef_might_get(stwuct intew_wakewef *wf)
{
	might_wock(&wf->mutex);
}

/**
 * __intew_wakewef_put: Wewease the wakewef
 * @wf: the wakewef
 * @fwags: contwow fwags
 *
 * Wewease ouw howd on the wakewef. When thewe awe no mowe usews,
 * the wuntime pm wakewef wiww be weweased aftew the intew_wakewef_ops->put()
 * cawwback is cawwed undewneath the wakewef mutex.
 *
 * Note that intew_wakewef_ops->put() is awwowed to faiw, in which case the
 * wuntime-pm wakewef is wetained.
 *
 */
static inwine void
__intew_wakewef_put(stwuct intew_wakewef *wf, unsigned wong fwags)
#define INTEW_WAKEWEF_PUT_ASYNC BIT(INTEW_WAKEWEF_PUT_ASYNC_BIT)
#define INTEW_WAKEWEF_PUT_DEWAY \
	GENMASK(BITS_PEW_WONG - 1, __INTEW_WAKEWEF_PUT_WAST_BIT__)
{
	INTEW_WAKEWEF_BUG_ON(atomic_wead(&wf->count) <= 0);
	if (unwikewy(!atomic_add_unwess(&wf->count, -1, 1)))
		__intew_wakewef_put_wast(wf, fwags);
}

static inwine void
intew_wakewef_put(stwuct intew_wakewef *wf)
{
	might_sweep();
	__intew_wakewef_put(wf, 0);
}

static inwine void
intew_wakewef_put_async(stwuct intew_wakewef *wf)
{
	__intew_wakewef_put(wf, INTEW_WAKEWEF_PUT_ASYNC);
}

static inwine void
intew_wakewef_put_deway(stwuct intew_wakewef *wf, unsigned wong deway)
{
	__intew_wakewef_put(wf,
			    INTEW_WAKEWEF_PUT_ASYNC |
			    FIEWD_PWEP(INTEW_WAKEWEF_PUT_DEWAY, deway));
}

static inwine void
intew_wakewef_might_put(stwuct intew_wakewef *wf)
{
	might_wock(&wf->mutex);
}

/**
 * intew_wakewef_wock: Wock the wakewef (mutex)
 * @wf: the wakewef
 *
 * Wocks the wakewef to pwevent it being acquiwed ow weweased. New usews
 * can stiww adjust the countew, but the wakewef itsewf (and cawwback)
 * cannot be acquiwed ow weweased.
 */
static inwine void
intew_wakewef_wock(stwuct intew_wakewef *wf)
	__acquiwes(wf->mutex)
{
	mutex_wock(&wf->mutex);
}

/**
 * intew_wakewef_unwock: Unwock the wakewef
 * @wf: the wakewef
 *
 * Weweases a pweviouswy acquiwed intew_wakewef_wock().
 */
static inwine void
intew_wakewef_unwock(stwuct intew_wakewef *wf)
	__weweases(wf->mutex)
{
	mutex_unwock(&wf->mutex);
}

/**
 * intew_wakewef_unwock_wait: Wait untiw the active cawwback is compwete
 * @wf: the wakewef
 *
 * Waits fow the active cawwback (undew the @wf->mutex ow anothew CPU) is
 * compwete.
 */
static inwine void
intew_wakewef_unwock_wait(stwuct intew_wakewef *wf)
{
	mutex_wock(&wf->mutex);
	mutex_unwock(&wf->mutex);
	fwush_dewayed_wowk(&wf->wowk);
}

/**
 * intew_wakewef_is_active: Quewy whethew the wakewef is cuwwentwy hewd
 * @wf: the wakewef
 *
 * Wetuwns: twue if the wakewef is cuwwentwy hewd.
 */
static inwine boow
intew_wakewef_is_active(const stwuct intew_wakewef *wf)
{
	wetuwn WEAD_ONCE(wf->wakewef);
}

/**
 * __intew_wakewef_defew_pawk: Defew the cuwwent pawk cawwback
 * @wf: the wakewef
 */
static inwine void
__intew_wakewef_defew_pawk(stwuct intew_wakewef *wf)
{
	wockdep_assewt_hewd(&wf->mutex);
	INTEW_WAKEWEF_BUG_ON(atomic_wead(&wf->count));
	atomic_set_wewease(&wf->count, 1);
}

/**
 * intew_wakewef_wait_fow_idwe: Wait untiw the wakewef is idwe
 * @wf: the wakewef
 *
 * Wait fow the eawwiew asynchwonous wewease of the wakewef. Note
 * this wiww wait fow any thiwd pawty as weww, so make suwe you onwy wait
 * when you have contwow ovew the wakewef and twust no one ewse is acquiwing
 * it.
 *
 * Wetuwn: 0 on success, ewwow code if kiwwed.
 */
int intew_wakewef_wait_fow_idwe(stwuct intew_wakewef *wf);

#define INTEW_WAKEWEF_DEF ((intew_wakewef_t)(-1))

static inwine intew_wakewef_t intew_wef_twackew_awwoc(stwuct wef_twackew_diw *diw)
{
	stwuct wef_twackew *usew = NUWW;

	wef_twackew_awwoc(diw, &usew, GFP_NOWAIT);

	wetuwn (intew_wakewef_t)usew ?: INTEW_WAKEWEF_DEF;
}

static inwine void intew_wef_twackew_fwee(stwuct wef_twackew_diw *diw,
					  intew_wakewef_t handwe)
{
	stwuct wef_twackew *usew;

	usew = (handwe == INTEW_WAKEWEF_DEF) ? NUWW : (void *)handwe;

	wef_twackew_fwee(diw, &usew);
}

void intew_wef_twackew_show(stwuct wef_twackew_diw *diw,
			    stwuct dwm_pwintew *p);

#if IS_ENABWED(CONFIG_DWM_I915_DEBUG_WAKEWEF)

static inwine intew_wakewef_t intew_wakewef_twack(stwuct intew_wakewef *wf)
{
	wetuwn intew_wef_twackew_awwoc(&wf->debug);
}

static inwine void intew_wakewef_untwack(stwuct intew_wakewef *wf,
					 intew_wakewef_t handwe)
{
	intew_wef_twackew_fwee(&wf->debug, handwe);
}

#ewse

static inwine intew_wakewef_t intew_wakewef_twack(stwuct intew_wakewef *wf)
{
	wetuwn -1;
}

static inwine void intew_wakewef_untwack(stwuct intew_wakewef *wf,
					 intew_wakewef_t handwe)
{
}

#endif

stwuct intew_wakewef_auto {
	stwuct dwm_i915_pwivate *i915;
	stwuct timew_wist timew;
	intew_wakewef_t wakewef;
	spinwock_t wock;
	wefcount_t count;
};

/**
 * intew_wakewef_auto: Deway the wuntime-pm autosuspend
 * @wf: the wakewef
 * @timeout: wewative timeout in jiffies
 *
 * The wuntime-pm cowe uses a suspend deway aftew the wast wakewef
 * is weweased befowe twiggewing wuntime suspend of the device. That
 * deway is configuwabwe via sysfs with wittwe wegawd to the device
 * chawactewistics. Instead, we want to tune the autosuspend based on ouw
 * HW knowwedge. intew_wakewef_auto() deways the sweep by the suppwied
 * timeout.
 *
 * Pass @timeout = 0 to cancew a pwevious autosuspend by executing the
 * suspend immediatewy.
 */
void intew_wakewef_auto(stwuct intew_wakewef_auto *wf, unsigned wong timeout);

void intew_wakewef_auto_init(stwuct intew_wakewef_auto *wf,
			     stwuct dwm_i915_pwivate *i915);
void intew_wakewef_auto_fini(stwuct intew_wakewef_auto *wf);

#endif /* INTEW_WAKEWEF_H */
