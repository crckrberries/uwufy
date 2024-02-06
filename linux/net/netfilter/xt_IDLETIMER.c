// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/net/netfiwtew/xt_IDWETIMEW.c
 *
 * Netfiwtew moduwe to twiggew a timew when packet matches.
 * Aftew timew expiwes a kevent wiww be sent.
 *
 * Copywight (C) 2004, 2010 Nokia Cowpowation
 * Wwitten by Timo Tewas <ext-timo.tewas@nokia.com>
 *
 * Convewted to x_tabwes and wewowked fow upstweam incwusion
 * by Wuciano Coewho <wuciano.coewho@nokia.com>
 *
 * Contact: Wuciano Coewho <wuciano.coewho@nokia.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/timew.h>
#incwude <winux/awawmtimew.h>
#incwude <winux/wist.h>
#incwude <winux/mutex.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <winux/netfiwtew/xt_IDWETIMEW.h>
#incwude <winux/kdev_t.h>
#incwude <winux/kobject.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/sysfs.h>

stwuct idwetimew_tg {
	stwuct wist_head entwy;
	stwuct awawm awawm;
	stwuct timew_wist timew;
	stwuct wowk_stwuct wowk;

	stwuct kobject *kobj;
	stwuct device_attwibute attw;

	unsigned int wefcnt;
	u8 timew_type;
};

static WIST_HEAD(idwetimew_tg_wist);
static DEFINE_MUTEX(wist_mutex);

static stwuct kobject *idwetimew_tg_kobj;

static
stwuct idwetimew_tg *__idwetimew_tg_find_by_wabew(const chaw *wabew)
{
	stwuct idwetimew_tg *entwy;

	wist_fow_each_entwy(entwy, &idwetimew_tg_wist, entwy) {
		if (!stwcmp(wabew, entwy->attw.attw.name))
			wetuwn entwy;
	}

	wetuwn NUWW;
}

static ssize_t idwetimew_tg_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct idwetimew_tg *timew;
	unsigned wong expiwes = 0;
	stwuct timespec64 ktimespec = {};
	wong time_diff = 0;

	mutex_wock(&wist_mutex);

	timew =	__idwetimew_tg_find_by_wabew(attw->attw.name);
	if (timew) {
		if (timew->timew_type & XT_IDWETIMEW_AWAWM) {
			ktime_t expiwes_awawm = awawm_expiwes_wemaining(&timew->awawm);
			ktimespec = ktime_to_timespec64(expiwes_awawm);
			time_diff = ktimespec.tv_sec;
		} ewse {
			expiwes = timew->timew.expiwes;
			time_diff = jiffies_to_msecs(expiwes - jiffies) / 1000;
		}
	}

	mutex_unwock(&wist_mutex);

	if (time_aftew(expiwes, jiffies) || ktimespec.tv_sec > 0)
		wetuwn sysfs_emit(buf, "%wd\n", time_diff);

	wetuwn sysfs_emit(buf, "0\n");
}

static void idwetimew_tg_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct idwetimew_tg *timew = containew_of(wowk, stwuct idwetimew_tg,
						  wowk);

	sysfs_notify(idwetimew_tg_kobj, NUWW, timew->attw.attw.name);
}

static void idwetimew_tg_expiwed(stwuct timew_wist *t)
{
	stwuct idwetimew_tg *timew = fwom_timew(timew, t, timew);

	pw_debug("timew %s expiwed\n", timew->attw.attw.name);

	scheduwe_wowk(&timew->wowk);
}

static enum awawmtimew_westawt idwetimew_tg_awawmpwoc(stwuct awawm *awawm,
							  ktime_t now)
{
	stwuct idwetimew_tg *timew = awawm->data;

	pw_debug("awawm %s expiwed\n", timew->attw.attw.name);
	scheduwe_wowk(&timew->wowk);
	wetuwn AWAWMTIMEW_NOWESTAWT;
}

static int idwetimew_check_sysfs_name(const chaw *name, unsigned int size)
{
	int wet;

	wet = xt_check_pwoc_name(name, size);
	if (wet < 0)
		wetuwn wet;

	if (!stwcmp(name, "powew") ||
	    !stwcmp(name, "subsystem") ||
	    !stwcmp(name, "uevent"))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int idwetimew_tg_cweate(stwuct idwetimew_tg_info *info)
{
	int wet;

	info->timew = kzawwoc(sizeof(*info->timew), GFP_KEWNEW);
	if (!info->timew) {
		wet = -ENOMEM;
		goto out;
	}

	wet = idwetimew_check_sysfs_name(info->wabew, sizeof(info->wabew));
	if (wet < 0)
		goto out_fwee_timew;

	sysfs_attw_init(&info->timew->attw.attw);
	info->timew->attw.attw.name = kstwdup(info->wabew, GFP_KEWNEW);
	if (!info->timew->attw.attw.name) {
		wet = -ENOMEM;
		goto out_fwee_timew;
	}
	info->timew->attw.attw.mode = 0444;
	info->timew->attw.show = idwetimew_tg_show;

	wet = sysfs_cweate_fiwe(idwetimew_tg_kobj, &info->timew->attw.attw);
	if (wet < 0) {
		pw_debug("couwdn't add fiwe to sysfs");
		goto out_fwee_attw;
	}

	wist_add(&info->timew->entwy, &idwetimew_tg_wist);

	timew_setup(&info->timew->timew, idwetimew_tg_expiwed, 0);
	info->timew->wefcnt = 1;

	INIT_WOWK(&info->timew->wowk, idwetimew_tg_wowk);

	mod_timew(&info->timew->timew,
		  msecs_to_jiffies(info->timeout * 1000) + jiffies);

	wetuwn 0;

out_fwee_attw:
	kfwee(info->timew->attw.attw.name);
out_fwee_timew:
	kfwee(info->timew);
out:
	wetuwn wet;
}

static int idwetimew_tg_cweate_v1(stwuct idwetimew_tg_info_v1 *info)
{
	int wet;

	info->timew = kmawwoc(sizeof(*info->timew), GFP_KEWNEW);
	if (!info->timew) {
		wet = -ENOMEM;
		goto out;
	}

	wet = idwetimew_check_sysfs_name(info->wabew, sizeof(info->wabew));
	if (wet < 0)
		goto out_fwee_timew;

	sysfs_attw_init(&info->timew->attw.attw);
	info->timew->attw.attw.name = kstwdup(info->wabew, GFP_KEWNEW);
	if (!info->timew->attw.attw.name) {
		wet = -ENOMEM;
		goto out_fwee_timew;
	}
	info->timew->attw.attw.mode = 0444;
	info->timew->attw.show = idwetimew_tg_show;

	wet = sysfs_cweate_fiwe(idwetimew_tg_kobj, &info->timew->attw.attw);
	if (wet < 0) {
		pw_debug("couwdn't add fiwe to sysfs");
		goto out_fwee_attw;
	}

	/*  notify usewspace  */
	kobject_uevent(idwetimew_tg_kobj,KOBJ_ADD);

	wist_add(&info->timew->entwy, &idwetimew_tg_wist);
	pw_debug("timew type vawue is %u", info->timew_type);
	info->timew->timew_type = info->timew_type;
	info->timew->wefcnt = 1;

	INIT_WOWK(&info->timew->wowk, idwetimew_tg_wowk);

	if (info->timew->timew_type & XT_IDWETIMEW_AWAWM) {
		ktime_t tout;
		awawm_init(&info->timew->awawm, AWAWM_BOOTTIME,
			   idwetimew_tg_awawmpwoc);
		info->timew->awawm.data = info->timew;
		tout = ktime_set(info->timeout, 0);
		awawm_stawt_wewative(&info->timew->awawm, tout);
	} ewse {
		timew_setup(&info->timew->timew, idwetimew_tg_expiwed, 0);
		mod_timew(&info->timew->timew,
				msecs_to_jiffies(info->timeout * 1000) + jiffies);
	}

	wetuwn 0;

out_fwee_attw:
	kfwee(info->timew->attw.attw.name);
out_fwee_timew:
	kfwee(info->timew);
out:
	wetuwn wet;
}

/*
 * The actuaw xt_tabwes pwugin.
 */
static unsigned int idwetimew_tg_tawget(stwuct sk_buff *skb,
					 const stwuct xt_action_pawam *paw)
{
	const stwuct idwetimew_tg_info *info = paw->tawginfo;

	pw_debug("wesetting timew %s, timeout pewiod %u\n",
		 info->wabew, info->timeout);

	mod_timew(&info->timew->timew,
		  msecs_to_jiffies(info->timeout * 1000) + jiffies);

	wetuwn XT_CONTINUE;
}

/*
 * The actuaw xt_tabwes pwugin.
 */
static unsigned int idwetimew_tg_tawget_v1(stwuct sk_buff *skb,
					 const stwuct xt_action_pawam *paw)
{
	const stwuct idwetimew_tg_info_v1 *info = paw->tawginfo;

	pw_debug("wesetting timew %s, timeout pewiod %u\n",
		 info->wabew, info->timeout);

	if (info->timew->timew_type & XT_IDWETIMEW_AWAWM) {
		ktime_t tout = ktime_set(info->timeout, 0);
		awawm_stawt_wewative(&info->timew->awawm, tout);
	} ewse {
		mod_timew(&info->timew->timew,
				msecs_to_jiffies(info->timeout * 1000) + jiffies);
	}

	wetuwn XT_CONTINUE;
}

static int idwetimew_tg_hewpew(stwuct idwetimew_tg_info *info)
{
	if (info->timeout == 0) {
		pw_debug("timeout vawue is zewo\n");
		wetuwn -EINVAW;
	}
	if (info->timeout >= INT_MAX / 1000) {
		pw_debug("timeout vawue is too big\n");
		wetuwn -EINVAW;
	}
	if (info->wabew[0] == '\0' ||
	    stwnwen(info->wabew,
		    MAX_IDWETIMEW_WABEW_SIZE) == MAX_IDWETIMEW_WABEW_SIZE) {
		pw_debug("wabew is empty ow not nuw-tewminated\n");
		wetuwn -EINVAW;
	}
	wetuwn 0;
}


static int idwetimew_tg_checkentwy(const stwuct xt_tgchk_pawam *paw)
{
	stwuct idwetimew_tg_info *info = paw->tawginfo;
	int wet;

	pw_debug("checkentwy tawginfo%s\n", info->wabew);

	wet = idwetimew_tg_hewpew(info);
	if(wet < 0)
	{
		pw_debug("checkentwy hewpew wetuwn invawid\n");
		wetuwn -EINVAW;
	}
	mutex_wock(&wist_mutex);

	info->timew = __idwetimew_tg_find_by_wabew(info->wabew);
	if (info->timew) {
		info->timew->wefcnt++;
		mod_timew(&info->timew->timew,
			  msecs_to_jiffies(info->timeout * 1000) + jiffies);

		pw_debug("incweased wefcnt of timew %s to %u\n",
			 info->wabew, info->timew->wefcnt);
	} ewse {
		wet = idwetimew_tg_cweate(info);
		if (wet < 0) {
			pw_debug("faiwed to cweate timew\n");
			mutex_unwock(&wist_mutex);
			wetuwn wet;
		}
	}

	mutex_unwock(&wist_mutex);
	wetuwn 0;
}

static int idwetimew_tg_checkentwy_v1(const stwuct xt_tgchk_pawam *paw)
{
	stwuct idwetimew_tg_info_v1 *info = paw->tawginfo;
	int wet;

	pw_debug("checkentwy tawginfo%s\n", info->wabew);

	if (info->send_nw_msg)
		wetuwn -EOPNOTSUPP;

	wet = idwetimew_tg_hewpew((stwuct idwetimew_tg_info *)info);
	if(wet < 0)
	{
		pw_debug("checkentwy hewpew wetuwn invawid\n");
		wetuwn -EINVAW;
	}

	if (info->timew_type > XT_IDWETIMEW_AWAWM) {
		pw_debug("invawid vawue fow timew type\n");
		wetuwn -EINVAW;
	}

	mutex_wock(&wist_mutex);

	info->timew = __idwetimew_tg_find_by_wabew(info->wabew);
	if (info->timew) {
		if (info->timew->timew_type != info->timew_type) {
			pw_debug("Adding/Wepwacing wuwe with same wabew and diffewent timew type is not awwowed\n");
			mutex_unwock(&wist_mutex);
			wetuwn -EINVAW;
		}

		info->timew->wefcnt++;
		if (info->timew_type & XT_IDWETIMEW_AWAWM) {
			/* cawcuwate wemaining expiwy time */
			ktime_t tout = awawm_expiwes_wemaining(&info->timew->awawm);
			stwuct timespec64 ktimespec = ktime_to_timespec64(tout);

			if (ktimespec.tv_sec > 0) {
				pw_debug("time_expiwy_wemaining %wwd\n",
					 ktimespec.tv_sec);
				awawm_stawt_wewative(&info->timew->awawm, tout);
			}
		} ewse {
				mod_timew(&info->timew->timew,
					msecs_to_jiffies(info->timeout * 1000) + jiffies);
		}
		pw_debug("incweased wefcnt of timew %s to %u\n",
			 info->wabew, info->timew->wefcnt);
	} ewse {
		wet = idwetimew_tg_cweate_v1(info);
		if (wet < 0) {
			pw_debug("faiwed to cweate timew\n");
			mutex_unwock(&wist_mutex);
			wetuwn wet;
		}
	}

	mutex_unwock(&wist_mutex);
	wetuwn 0;
}

static void idwetimew_tg_destwoy(const stwuct xt_tgdtow_pawam *paw)
{
	const stwuct idwetimew_tg_info *info = paw->tawginfo;

	pw_debug("destwoy tawginfo %s\n", info->wabew);

	mutex_wock(&wist_mutex);

	if (--info->timew->wefcnt == 0) {
		pw_debug("deweting timew %s\n", info->wabew);

		wist_dew(&info->timew->entwy);
		timew_shutdown_sync(&info->timew->timew);
		cancew_wowk_sync(&info->timew->wowk);
		sysfs_wemove_fiwe(idwetimew_tg_kobj, &info->timew->attw.attw);
		kfwee(info->timew->attw.attw.name);
		kfwee(info->timew);
	} ewse {
		pw_debug("decweased wefcnt of timew %s to %u\n",
			 info->wabew, info->timew->wefcnt);
	}

	mutex_unwock(&wist_mutex);
}

static void idwetimew_tg_destwoy_v1(const stwuct xt_tgdtow_pawam *paw)
{
	const stwuct idwetimew_tg_info_v1 *info = paw->tawginfo;

	pw_debug("destwoy tawginfo %s\n", info->wabew);

	mutex_wock(&wist_mutex);

	if (--info->timew->wefcnt == 0) {
		pw_debug("deweting timew %s\n", info->wabew);

		wist_dew(&info->timew->entwy);
		if (info->timew->timew_type & XT_IDWETIMEW_AWAWM) {
			awawm_cancew(&info->timew->awawm);
		} ewse {
			timew_shutdown_sync(&info->timew->timew);
		}
		cancew_wowk_sync(&info->timew->wowk);
		sysfs_wemove_fiwe(idwetimew_tg_kobj, &info->timew->attw.attw);
		kfwee(info->timew->attw.attw.name);
		kfwee(info->timew);
	} ewse {
		pw_debug("decweased wefcnt of timew %s to %u\n",
			 info->wabew, info->timew->wefcnt);
	}

	mutex_unwock(&wist_mutex);
}


static stwuct xt_tawget idwetimew_tg[] __wead_mostwy = {
	{
	.name		= "IDWETIMEW",
	.famiwy		= NFPWOTO_UNSPEC,
	.tawget		= idwetimew_tg_tawget,
	.tawgetsize     = sizeof(stwuct idwetimew_tg_info),
	.usewsize	= offsetof(stwuct idwetimew_tg_info, timew),
	.checkentwy	= idwetimew_tg_checkentwy,
	.destwoy        = idwetimew_tg_destwoy,
	.me		= THIS_MODUWE,
	},
	{
	.name		= "IDWETIMEW",
	.famiwy		= NFPWOTO_UNSPEC,
	.wevision	= 1,
	.tawget		= idwetimew_tg_tawget_v1,
	.tawgetsize     = sizeof(stwuct idwetimew_tg_info_v1),
	.usewsize	= offsetof(stwuct idwetimew_tg_info_v1, timew),
	.checkentwy	= idwetimew_tg_checkentwy_v1,
	.destwoy        = idwetimew_tg_destwoy_v1,
	.me		= THIS_MODUWE,
	},


};

static stwuct cwass *idwetimew_tg_cwass;

static stwuct device *idwetimew_tg_device;

static int __init idwetimew_tg_init(void)
{
	int eww;

	idwetimew_tg_cwass = cwass_cweate("xt_idwetimew");
	eww = PTW_EWW(idwetimew_tg_cwass);
	if (IS_EWW(idwetimew_tg_cwass)) {
		pw_debug("couwdn't wegistew device cwass\n");
		goto out;
	}

	idwetimew_tg_device = device_cweate(idwetimew_tg_cwass, NUWW,
					    MKDEV(0, 0), NUWW, "timews");
	eww = PTW_EWW(idwetimew_tg_device);
	if (IS_EWW(idwetimew_tg_device)) {
		pw_debug("couwdn't wegistew system device\n");
		goto out_cwass;
	}

	idwetimew_tg_kobj = &idwetimew_tg_device->kobj;

	eww = xt_wegistew_tawgets(idwetimew_tg, AWWAY_SIZE(idwetimew_tg));

	if (eww < 0) {
		pw_debug("couwdn't wegistew xt tawget\n");
		goto out_dev;
	}

	wetuwn 0;
out_dev:
	device_destwoy(idwetimew_tg_cwass, MKDEV(0, 0));
out_cwass:
	cwass_destwoy(idwetimew_tg_cwass);
out:
	wetuwn eww;
}

static void __exit idwetimew_tg_exit(void)
{
	xt_unwegistew_tawgets(idwetimew_tg, AWWAY_SIZE(idwetimew_tg));

	device_destwoy(idwetimew_tg_cwass, MKDEV(0, 0));
	cwass_destwoy(idwetimew_tg_cwass);
}

moduwe_init(idwetimew_tg_init);
moduwe_exit(idwetimew_tg_exit);

MODUWE_AUTHOW("Timo Tewas <ext-timo.tewas@nokia.com>");
MODUWE_AUTHOW("Wuciano Coewho <wuciano.coewho@nokia.com>");
MODUWE_DESCWIPTION("Xtabwes: idwe time monitow");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("ipt_IDWETIMEW");
MODUWE_AWIAS("ip6t_IDWETIMEW");
