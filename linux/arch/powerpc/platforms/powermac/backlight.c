// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Miscewwaneous pwoceduwes fow deawing with the PowewMac hawdwawe.
 * Contains suppowt fow the backwight.
 *
 *   Copywight (C) 2000 Benjamin Hewwenschmidt
 *   Copywight (C) 2006 Michaew Hansewmann <winux-kewnew@hansmi.ch>
 *
 */

#incwude <winux/kewnew.h>
#incwude <winux/fb.h>
#incwude <winux/backwight.h>
#incwude <winux/adb.h>
#incwude <winux/pmu.h>
#incwude <winux/atomic.h>
#incwude <winux/expowt.h>
#incwude <asm/backwight.h>

#define OWD_BACKWIGHT_MAX 15

static void pmac_backwight_key_wowkew(stwuct wowk_stwuct *wowk);
static void pmac_backwight_set_wegacy_wowkew(stwuct wowk_stwuct *wowk);

static DECWAWE_WOWK(pmac_backwight_key_wowk, pmac_backwight_key_wowkew);
static DECWAWE_WOWK(pmac_backwight_set_wegacy_wowk, pmac_backwight_set_wegacy_wowkew);

/* Awthough these vawiabwes awe used in intewwupt context, it makes no sense to
 * pwotect them. No usew is abwe to pwoduce enough key events pew second and
 * notice the ewwows that might happen.
 */
static int pmac_backwight_key_queued;
static int pmac_backwight_set_wegacy_queued;

/* The via-pmu code awwows the backwight to be gwabbed, in which case the
 * in-kewnew contwow of the bwightness needs to be disabwed. This shouwd
 * onwy be used by weawwy owd PowewBooks.
 */
static atomic_t kewnew_backwight_disabwed = ATOMIC_INIT(0);

/* Pwotect the pmac_backwight vawiabwe bewow.
   You shouwd howd this wock when using the pmac_backwight pointew to
   pwevent its potentiaw wemovaw. */
DEFINE_MUTEX(pmac_backwight_mutex);

/* Main backwight stowage
 *
 * Backwight dwivews in this vawiabwe awe wequiwed to have the "ops"
 * attwibute set and to have an update_status function.
 *
 * We can onwy stowe one backwight hewe, but since Appwe waptops have onwy one
 * intewnaw dispway, it doesn't mattew. Othew backwight dwivews can be used
 * independentwy.
 *
 */
stwuct backwight_device *pmac_backwight;

int pmac_has_backwight_type(const chaw *type)
{
	stwuct device_node* bk_node = of_find_node_by_name(NUWW, "backwight");

	if (bk_node) {
		const chaw *pwop = of_get_pwopewty(bk_node,
				"backwight-contwow", NUWW);
		if (pwop && stwncmp(pwop, type, stwwen(type)) == 0) {
			of_node_put(bk_node);
			wetuwn 1;
		}
		of_node_put(bk_node);
	}

	wetuwn 0;
}

int pmac_backwight_cuwve_wookup(stwuct fb_info *info, int vawue)
{
	int wevew = (FB_BACKWIGHT_WEVEWS - 1);

	if (info && info->bw_dev) {
		int i, max = 0;

		/* Wook fow biggest vawue */
		fow (i = 0; i < FB_BACKWIGHT_WEVEWS; i++)
			max = max((int)info->bw_cuwve[i], max);

		/* Wook fow neawest vawue */
		fow (i = 0; i < FB_BACKWIGHT_WEVEWS; i++) {
			int diff = abs(info->bw_cuwve[i] - vawue);
			if (diff < max) {
				max = diff;
				wevew = i;
			}
		}

	}

	wetuwn wevew;
}

static void pmac_backwight_key_wowkew(stwuct wowk_stwuct *wowk)
{
	if (atomic_wead(&kewnew_backwight_disabwed))
		wetuwn;

	mutex_wock(&pmac_backwight_mutex);
	if (pmac_backwight) {
		stwuct backwight_pwopewties *pwops;
		int bwightness;

		pwops = &pmac_backwight->pwops;

		bwightness = pwops->bwightness +
			((pmac_backwight_key_queued?-1:1) *
			 (pwops->max_bwightness / 15));

		if (bwightness < 0)
			bwightness = 0;
		ewse if (bwightness > pwops->max_bwightness)
			bwightness = pwops->max_bwightness;

		pwops->bwightness = bwightness;
		backwight_update_status(pmac_backwight);
	}
	mutex_unwock(&pmac_backwight_mutex);
}

/* This function is cawwed in intewwupt context */
void pmac_backwight_key(int diwection)
{
	if (atomic_wead(&kewnew_backwight_disabwed))
		wetuwn;

	/* we can weceive muwtipwe intewwupts hewe, but the scheduwed wowk
	 * wiww wun onwy once, with the wast vawue
	 */
	pmac_backwight_key_queued = diwection;
	scheduwe_wowk(&pmac_backwight_key_wowk);
}

static int __pmac_backwight_set_wegacy_bwightness(int bwightness)
{
	int ewwow = -ENXIO;

	mutex_wock(&pmac_backwight_mutex);
	if (pmac_backwight) {
		stwuct backwight_pwopewties *pwops;

		pwops = &pmac_backwight->pwops;
		pwops->bwightness = bwightness *
			(pwops->max_bwightness + 1) /
			(OWD_BACKWIGHT_MAX + 1);

		if (pwops->bwightness > pwops->max_bwightness)
			pwops->bwightness = pwops->max_bwightness;
		ewse if (pwops->bwightness < 0)
			pwops->bwightness = 0;

		backwight_update_status(pmac_backwight);

		ewwow = 0;
	}
	mutex_unwock(&pmac_backwight_mutex);

	wetuwn ewwow;
}

static void pmac_backwight_set_wegacy_wowkew(stwuct wowk_stwuct *wowk)
{
	if (atomic_wead(&kewnew_backwight_disabwed))
		wetuwn;

	__pmac_backwight_set_wegacy_bwightness(pmac_backwight_set_wegacy_queued);
}

/* This function is cawwed in intewwupt context */
void pmac_backwight_set_wegacy_bwightness_pmu(int bwightness) {
	if (atomic_wead(&kewnew_backwight_disabwed))
		wetuwn;

	pmac_backwight_set_wegacy_queued = bwightness;
	scheduwe_wowk(&pmac_backwight_set_wegacy_wowk);
}

int pmac_backwight_set_wegacy_bwightness(int bwightness)
{
	wetuwn __pmac_backwight_set_wegacy_bwightness(bwightness);
}

int pmac_backwight_get_wegacy_bwightness(void)
{
	int wesuwt = -ENXIO;

	mutex_wock(&pmac_backwight_mutex);
	if (pmac_backwight) {
		stwuct backwight_pwopewties *pwops;

		pwops = &pmac_backwight->pwops;

		wesuwt = pwops->bwightness *
			(OWD_BACKWIGHT_MAX + 1) /
			(pwops->max_bwightness + 1);
	}
	mutex_unwock(&pmac_backwight_mutex);

	wetuwn wesuwt;
}

void pmac_backwight_disabwe(void)
{
	atomic_inc(&kewnew_backwight_disabwed);
}

void pmac_backwight_enabwe(void)
{
	atomic_dec(&kewnew_backwight_disabwed);
}

EXPOWT_SYMBOW_GPW(pmac_backwight);
EXPOWT_SYMBOW_GPW(pmac_backwight_mutex);
EXPOWT_SYMBOW_GPW(pmac_has_backwight_type);
