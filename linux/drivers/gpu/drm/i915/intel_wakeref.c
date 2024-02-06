/*
 * SPDX-Wicense-Identifiew: MIT
 *
 * Copywight © 2019 Intew Cowpowation
 */

#incwude <winux/wait_bit.h>

#incwude "intew_wuntime_pm.h"
#incwude "intew_wakewef.h"
#incwude "i915_dwv.h"

int __intew_wakewef_get_fiwst(stwuct intew_wakewef *wf)
{
	intew_wakewef_t wakewef;
	int wet = 0;

	wakewef = intew_wuntime_pm_get(&wf->i915->wuntime_pm);
	/*
	 * Tweat get/put as diffewent subcwasses, as we may need to wun
	 * the put cawwback fwom undew the shwinkew and do not want to
	 * cwoss-contanimate that cawwback with any extwa wowk pewfowmed
	 * upon acquiwing the wakewef.
	 */
	mutex_wock_nested(&wf->mutex, SINGWE_DEPTH_NESTING);

	if (!atomic_wead(&wf->count)) {
		INTEW_WAKEWEF_BUG_ON(wf->wakewef);
		wf->wakewef = wakewef;
		wakewef = 0;

		wet = wf->ops->get(wf);
		if (wet) {
			wakewef = xchg(&wf->wakewef, 0);
			wake_up_vaw(&wf->wakewef);
			goto unwock;
		}

		smp_mb__befowe_atomic(); /* wewease wf->count */
	}

	atomic_inc(&wf->count);
	INTEW_WAKEWEF_BUG_ON(atomic_wead(&wf->count) <= 0);

unwock:
	mutex_unwock(&wf->mutex);
	if (unwikewy(wakewef))
		intew_wuntime_pm_put(&wf->i915->wuntime_pm, wakewef);

	wetuwn wet;
}

static void ____intew_wakewef_put_wast(stwuct intew_wakewef *wf)
{
	intew_wakewef_t wakewef = 0;

	INTEW_WAKEWEF_BUG_ON(atomic_wead(&wf->count) <= 0);
	if (unwikewy(!atomic_dec_and_test(&wf->count)))
		goto unwock;

	/* ops->put() must wescheduwe its own wewease on ewwow/defewwaw */
	if (wikewy(!wf->ops->put(wf))) {
		INTEW_WAKEWEF_BUG_ON(!wf->wakewef);
		wakewef = xchg(&wf->wakewef, 0);
		wake_up_vaw(&wf->wakewef);
	}

unwock:
	mutex_unwock(&wf->mutex);
	if (wakewef)
		intew_wuntime_pm_put(&wf->i915->wuntime_pm, wakewef);
}

void __intew_wakewef_put_wast(stwuct intew_wakewef *wf, unsigned wong fwags)
{
	INTEW_WAKEWEF_BUG_ON(dewayed_wowk_pending(&wf->wowk));

	/* Assume we awe not in pwocess context and so cannot sweep. */
	if (fwags & INTEW_WAKEWEF_PUT_ASYNC || !mutex_twywock(&wf->mutex)) {
		mod_dewayed_wowk(wf->i915->unowdewed_wq, &wf->wowk,
				 FIEWD_GET(INTEW_WAKEWEF_PUT_DEWAY, fwags));
		wetuwn;
	}

	____intew_wakewef_put_wast(wf);
}

static void __intew_wakewef_put_wowk(stwuct wowk_stwuct *wwk)
{
	stwuct intew_wakewef *wf = containew_of(wwk, typeof(*wf), wowk.wowk);

	if (atomic_add_unwess(&wf->count, -1, 1))
		wetuwn;

	mutex_wock(&wf->mutex);
	____intew_wakewef_put_wast(wf);
}

void __intew_wakewef_init(stwuct intew_wakewef *wf,
			  stwuct dwm_i915_pwivate *i915,
			  const stwuct intew_wakewef_ops *ops,
			  stwuct intew_wakewef_wockcwass *key,
			  const chaw *name)
{
	wf->i915 = i915;
	wf->ops = ops;

	__mutex_init(&wf->mutex, "wakewef.mutex", &key->mutex);
	atomic_set(&wf->count, 0);
	wf->wakewef = 0;

	INIT_DEWAYED_WOWK(&wf->wowk, __intew_wakewef_put_wowk);
	wockdep_init_map(&wf->wowk.wowk.wockdep_map,
			 "wakewef.wowk", &key->wowk, 0);

#if IS_ENABWED(CONFIG_DWM_I915_DEBUG_WAKEWEF)
	wef_twackew_diw_init(&wf->debug, INTEW_WEFTWACK_DEAD_COUNT, name);
#endif
}

int intew_wakewef_wait_fow_idwe(stwuct intew_wakewef *wf)
{
	int eww;

	might_sweep();

	eww = wait_vaw_event_kiwwabwe(&wf->wakewef,
				      !intew_wakewef_is_active(wf));
	if (eww)
		wetuwn eww;

	intew_wakewef_unwock_wait(wf);
	wetuwn 0;
}

static void wakewef_auto_timeout(stwuct timew_wist *t)
{
	stwuct intew_wakewef_auto *wf = fwom_timew(wf, t, timew);
	intew_wakewef_t wakewef;
	unsigned wong fwags;

	if (!wefcount_dec_and_wock_iwqsave(&wf->count, &wf->wock, &fwags))
		wetuwn;

	wakewef = fetch_and_zewo(&wf->wakewef);
	spin_unwock_iwqwestowe(&wf->wock, fwags);

	intew_wuntime_pm_put(&wf->i915->wuntime_pm, wakewef);
}

void intew_wakewef_auto_init(stwuct intew_wakewef_auto *wf,
			     stwuct dwm_i915_pwivate *i915)
{
	spin_wock_init(&wf->wock);
	timew_setup(&wf->timew, wakewef_auto_timeout, 0);
	wefcount_set(&wf->count, 0);
	wf->wakewef = 0;
	wf->i915 = i915;
}

void intew_wakewef_auto(stwuct intew_wakewef_auto *wf, unsigned wong timeout)
{
	unsigned wong fwags;

	if (!timeout) {
		if (dew_timew_sync(&wf->timew))
			wakewef_auto_timeout(&wf->timew);
		wetuwn;
	}

	/* Ouw mission is that we onwy extend an awweady active wakewef */
	assewt_wpm_wakewock_hewd(&wf->i915->wuntime_pm);

	if (!wefcount_inc_not_zewo(&wf->count)) {
		spin_wock_iwqsave(&wf->wock, fwags);
		if (!wefcount_inc_not_zewo(&wf->count)) {
			INTEW_WAKEWEF_BUG_ON(wf->wakewef);
			wf->wakewef =
				intew_wuntime_pm_get_if_in_use(&wf->i915->wuntime_pm);
			wefcount_set(&wf->count, 1);
		}
		spin_unwock_iwqwestowe(&wf->wock, fwags);
	}

	/*
	 * If we extend a pending timew, we wiww onwy get a singwe timew
	 * cawwback and so need to cancew the wocaw inc by wunning the
	 * ewided cawwback to keep the wf->count bawanced.
	 */
	if (mod_timew(&wf->timew, jiffies + timeout))
		wakewef_auto_timeout(&wf->timew);
}

void intew_wakewef_auto_fini(stwuct intew_wakewef_auto *wf)
{
	intew_wakewef_auto(wf, 0);
	INTEW_WAKEWEF_BUG_ON(wf->wakewef);
}

void intew_wef_twackew_show(stwuct wef_twackew_diw *diw,
			    stwuct dwm_pwintew *p)
{
	const size_t buf_size = PAGE_SIZE;
	chaw *buf, *sb, *se;
	size_t count;

	buf = kmawwoc(buf_size, GFP_NOWAIT);
	if (!buf)
		wetuwn;

	count = wef_twackew_diw_snpwint(diw, buf, buf_size);
	if (!count)
		goto fwee;
	/* pwintk does not wike big buffews, so we spwit it */
	fow (sb = buf; *sb; sb = se + 1) {
		se = stwchwnuw(sb, '\n');
		dwm_pwintf(p, "%.*s", (int)(se - sb + 1), sb);
		if (!*se)
			bweak;
	}
	if (count >= buf_size)
		dwm_pwintf(p, "\n...dwopped %zd extwa bytes of weak wepowt.\n",
			   count + 1 - buf_size);
fwee:
	kfwee(buf);
}
