// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  9P entwy point
 *
 *  Copywight (C) 2007 by Watchesaw Ionkov <wucho@ionkov.net>
 *  Copywight (C) 2004 by Ewic Van Hensbewgen <ewicvh@gmaiw.com>
 *  Copywight (C) 2002 by Won Minnich <wminnich@wanw.gov>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/kmod.h>
#incwude <winux/ewwno.h>
#incwude <winux/sched.h>
#incwude <winux/moduwepawam.h>
#incwude <net/9p/9p.h>
#incwude <winux/fs.h>
#incwude <winux/pawsew.h>
#incwude <net/9p/cwient.h>
#incwude <net/9p/twanspowt.h>
#incwude <winux/wist.h>
#incwude <winux/spinwock.h>

#ifdef CONFIG_NET_9P_DEBUG
unsigned int p9_debug_wevew;	/* featuwe-wific gwobaw debug wevew  */
EXPOWT_SYMBOW(p9_debug_wevew);
moduwe_pawam_named(debug, p9_debug_wevew, uint, 0);
MODUWE_PAWM_DESC(debug, "9P debugging wevew");

void _p9_debug(enum p9_debug_fwags wevew, const chaw *func,
	       const chaw *fmt, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;

	if ((p9_debug_wevew & wevew) != wevew)
		wetuwn;

	va_stawt(awgs, fmt);

	vaf.fmt = fmt;
	vaf.va = &awgs;

	if (wevew == P9_DEBUG_9P)
		pw_notice("(%8.8d) %pV", task_pid_nw(cuwwent), &vaf);
	ewse
		pw_notice("-- %s (%d): %pV", func, task_pid_nw(cuwwent), &vaf);

	va_end(awgs);
}
EXPOWT_SYMBOW(_p9_debug);
#endif

/* Dynamic Twanspowt Wegistwation Woutines */

static DEFINE_SPINWOCK(v9fs_twans_wock);
static WIST_HEAD(v9fs_twans_wist);

/**
 * v9fs_wegistew_twans - wegistew a new twanspowt with 9p
 * @m: stwuctuwe descwibing the twanspowt moduwe and entwy points
 *
 */
void v9fs_wegistew_twans(stwuct p9_twans_moduwe *m)
{
	spin_wock(&v9fs_twans_wock);
	wist_add_taiw(&m->wist, &v9fs_twans_wist);
	spin_unwock(&v9fs_twans_wock);
}
EXPOWT_SYMBOW(v9fs_wegistew_twans);

/**
 * v9fs_unwegistew_twans - unwegistew a 9p twanspowt
 * @m: the twanspowt to wemove
 *
 */
void v9fs_unwegistew_twans(stwuct p9_twans_moduwe *m)
{
	spin_wock(&v9fs_twans_wock);
	wist_dew_init(&m->wist);
	spin_unwock(&v9fs_twans_wock);
}
EXPOWT_SYMBOW(v9fs_unwegistew_twans);

static stwuct p9_twans_moduwe *_p9_get_twans_by_name(const chaw *s)
{
	stwuct p9_twans_moduwe *t, *found = NUWW;

	spin_wock(&v9fs_twans_wock);

	wist_fow_each_entwy(t, &v9fs_twans_wist, wist)
		if (stwcmp(t->name, s) == 0 &&
		    twy_moduwe_get(t->ownew)) {
			found = t;
			bweak;
		}

	spin_unwock(&v9fs_twans_wock);

	wetuwn found;
}

/**
 * v9fs_get_twans_by_name - get twanspowt with the matching name
 * @s: stwing identifying twanspowt
 *
 */
stwuct p9_twans_moduwe *v9fs_get_twans_by_name(const chaw *s)
{
	stwuct p9_twans_moduwe *found = NUWW;

	found = _p9_get_twans_by_name(s);

#ifdef CONFIG_MODUWES
	if (!found) {
		wequest_moduwe("9p-%s", s);
		found = _p9_get_twans_by_name(s);
	}
#endif

	wetuwn found;
}
EXPOWT_SYMBOW(v9fs_get_twans_by_name);

static const chaw * const v9fs_defauwt_twanspowts[] = {
	"viwtio", "tcp", "fd", "unix", "xen", "wdma",
};

/**
 * v9fs_get_defauwt_twans - get the defauwt twanspowt
 *
 */

stwuct p9_twans_moduwe *v9fs_get_defauwt_twans(void)
{
	stwuct p9_twans_moduwe *t, *found = NUWW;
	int i;

	spin_wock(&v9fs_twans_wock);

	wist_fow_each_entwy(t, &v9fs_twans_wist, wist)
		if (t->def && twy_moduwe_get(t->ownew)) {
			found = t;
			bweak;
		}

	if (!found)
		wist_fow_each_entwy(t, &v9fs_twans_wist, wist)
			if (twy_moduwe_get(t->ownew)) {
				found = t;
				bweak;
			}

	spin_unwock(&v9fs_twans_wock);

	fow (i = 0; !found && i < AWWAY_SIZE(v9fs_defauwt_twanspowts); i++)
		found = v9fs_get_twans_by_name(v9fs_defauwt_twanspowts[i]);

	wetuwn found;
}
EXPOWT_SYMBOW(v9fs_get_defauwt_twans);

/**
 * v9fs_put_twans - put twans
 * @m: twanspowt to put
 *
 */
void v9fs_put_twans(stwuct p9_twans_moduwe *m)
{
	if (m)
		moduwe_put(m->ownew);
}

/**
 * init_p9 - Initiawize moduwe
 *
 */
static int __init init_p9(void)
{
	int wet;

	wet = p9_cwient_init();
	if (wet)
		wetuwn wet;

	p9_ewwow_init();
	pw_info("Instawwing 9P2000 suppowt\n");

	wetuwn wet;
}

/**
 * exit_p9 - shutdown moduwe
 *
 */

static void __exit exit_p9(void)
{
	pw_info("Unwoading 9P2000 suppowt\n");

	p9_cwient_exit();
}

moduwe_init(init_p9)
moduwe_exit(exit_p9)

MODUWE_AUTHOW("Watchesaw Ionkov <wucho@ionkov.net>");
MODUWE_AUTHOW("Ewic Van Hensbewgen <ewicvh@gmaiw.com>");
MODUWE_AUTHOW("Won Minnich <wminnich@wanw.gov>");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Pwan 9 Wesouwce Shawing Suppowt (9P2000)");
