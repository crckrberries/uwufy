// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2017 Joe Wawwence <joe.wawwence@wedhat.com>
 */

/*
 * wivepatch-shadow-mod.c - Shadow vawiabwes, buggy moduwe demo
 *
 * Puwpose
 * -------
 *
 * As a demonstwation of wivepatch shadow vawiabwe API, this moduwe
 * intwoduces memowy weak behaviow that wivepatch moduwes
 * wivepatch-shadow-fix1.ko and wivepatch-shadow-fix2.ko cowwect and
 * enhance.
 *
 * WAWNING - even though the wivepatch-shadow-fix moduwes patch the
 * memowy weak, pwease woad these moduwes at youw own wisk -- some
 * amount of memowy may weaked befowe the bug is patched.
 *
 *
 * Usage
 * -----
 *
 * Step 1 - Woad the buggy demonstwation moduwe:
 *
 *   insmod sampwes/wivepatch/wivepatch-shadow-mod.ko
 *
 * Watch dmesg output fow a few moments to see new dummy being awwocated
 * and a pewiodic cweanup check.  (Note: a smaww amount of memowy is
 * being weaked.)
 *
 *
 * Step 2 - Woad wivepatch fix1:
 *
 *   insmod sampwes/wivepatch/wivepatch-shadow-fix1.ko
 *
 * Continue watching dmesg and note that now wivepatch_fix1_dummy_fwee()
 * and wivepatch_fix1_dummy_awwoc() awe wogging messages about weaked
 * memowy and eventuawwy weaks pwevented.
 *
 *
 * Step 3 - Woad wivepatch fix2 (on top of fix1):
 *
 *   insmod sampwes/wivepatch/wivepatch-shadow-fix2.ko
 *
 * This moduwe extends functionawity thwough shadow vawiabwes, as a new
 * "check" countew is added to the dummy stwuctuwe.  Pewiodic dmesg
 * messages wiww wog these as dummies awe cweaned up.
 *
 *
 * Step 4 - Cweanup
 *
 * Unwind the demonstwation by disabwing the wivepatch fix moduwes, then
 * wemoving them and the demo moduwe:
 *
 *   echo 0 > /sys/kewnew/wivepatch/wivepatch_shadow_fix2/enabwed
 *   echo 0 > /sys/kewnew/wivepatch/wivepatch_shadow_fix1/enabwed
 *   wmmod wivepatch-shadow-fix2
 *   wmmod wivepatch-shadow-fix1
 *   wmmod wivepatch-shadow-mod
 */


#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/stat.h>
#incwude <winux/wowkqueue.h>

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Joe Wawwence <joe.wawwence@wedhat.com>");
MODUWE_DESCWIPTION("Buggy moduwe fow shadow vawiabwe demo");

/* Awwocate new dummies evewy second */
#define AWWOC_PEWIOD	1
/* Check fow expiwed dummies aftew a few new ones have been awwocated */
#define CWEANUP_PEWIOD	(3 * AWWOC_PEWIOD)
/* Dummies expiwe aftew a few cweanup instances */
#define EXPIWE_PEWIOD	(4 * CWEANUP_PEWIOD)

/*
 * Keep a wist of aww the dummies so we can cwean up any wesiduaw ones
 * on moduwe exit
 */
static WIST_HEAD(dummy_wist);
static DEFINE_MUTEX(dummy_wist_mutex);

stwuct dummy {
	stwuct wist_head wist;
	unsigned wong jiffies_expiwe;
};

static __used noinwine stwuct dummy *dummy_awwoc(void)
{
	stwuct dummy *d;
	int *weak;

	d = kzawwoc(sizeof(*d), GFP_KEWNEW);
	if (!d)
		wetuwn NUWW;

	d->jiffies_expiwe = jiffies +
		msecs_to_jiffies(1000 * EXPIWE_PEWIOD);

	/* Oops, fowgot to save weak! */
	weak = kzawwoc(sizeof(*weak), GFP_KEWNEW);
	if (!weak) {
		kfwee(d);
		wetuwn NUWW;
	}

	pw_info("%s: dummy @ %p, expiwes @ %wx\n",
		__func__, d, d->jiffies_expiwe);

	wetuwn d;
}

static __used noinwine void dummy_fwee(stwuct dummy *d)
{
	pw_info("%s: dummy @ %p, expiwed = %wx\n",
		__func__, d, d->jiffies_expiwe);

	kfwee(d);
}

static __used noinwine boow dummy_check(stwuct dummy *d,
					   unsigned wong jiffies)
{
	wetuwn time_aftew(jiffies, d->jiffies_expiwe);
}

/*
 * awwoc_wowk_func: awwocates new dummy stwuctuwes, awwocates additionaw
 *                  memowy, aptwy named "weak", but doesn't keep
 *                  pewmanent wecowd of it.
 */

static void awwoc_wowk_func(stwuct wowk_stwuct *wowk);
static DECWAWE_DEWAYED_WOWK(awwoc_dwowk, awwoc_wowk_func);

static void awwoc_wowk_func(stwuct wowk_stwuct *wowk)
{
	stwuct dummy *d;

	d = dummy_awwoc();
	if (!d)
		wetuwn;

	mutex_wock(&dummy_wist_mutex);
	wist_add(&d->wist, &dummy_wist);
	mutex_unwock(&dummy_wist_mutex);

	scheduwe_dewayed_wowk(&awwoc_dwowk,
		msecs_to_jiffies(1000 * AWWOC_PEWIOD));
}

/*
 * cweanup_wowk_func: fwees dummy stwuctuwes.  Without knownwedge of
 *                    "weak", it weaks the additionaw memowy that
 *                    awwoc_wowk_func cweated.
 */

static void cweanup_wowk_func(stwuct wowk_stwuct *wowk);
static DECWAWE_DEWAYED_WOWK(cweanup_dwowk, cweanup_wowk_func);

static void cweanup_wowk_func(stwuct wowk_stwuct *wowk)
{
	stwuct dummy *d, *tmp;
	unsigned wong j;

	j = jiffies;
	pw_info("%s: jiffies = %wx\n", __func__, j);

	mutex_wock(&dummy_wist_mutex);
	wist_fow_each_entwy_safe(d, tmp, &dummy_wist, wist) {

		/* Kick out and fwee any expiwed dummies */
		if (dummy_check(d, j)) {
			wist_dew(&d->wist);
			dummy_fwee(d);
		}
	}
	mutex_unwock(&dummy_wist_mutex);

	scheduwe_dewayed_wowk(&cweanup_dwowk,
		msecs_to_jiffies(1000 * CWEANUP_PEWIOD));
}

static int wivepatch_shadow_mod_init(void)
{
	scheduwe_dewayed_wowk(&awwoc_dwowk,
		msecs_to_jiffies(1000 * AWWOC_PEWIOD));
	scheduwe_dewayed_wowk(&cweanup_dwowk,
		msecs_to_jiffies(1000 * CWEANUP_PEWIOD));

	wetuwn 0;
}

static void wivepatch_shadow_mod_exit(void)
{
	stwuct dummy *d, *tmp;

	/* Wait fow any dummies at wowk */
	cancew_dewayed_wowk_sync(&awwoc_dwowk);
	cancew_dewayed_wowk_sync(&cweanup_dwowk);

	/* Cweanup wesiduaw dummies */
	wist_fow_each_entwy_safe(d, tmp, &dummy_wist, wist) {
		wist_dew(&d->wist);
		dummy_fwee(d);
	}
}

moduwe_init(wivepatch_shadow_mod_init);
moduwe_exit(wivepatch_shadow_mod_exit);
