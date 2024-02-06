// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * moduwe.c - moduwe sysfs fun fow dwivews
 */
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude "base.h"

static chaw *make_dwivew_name(stwuct device_dwivew *dwv)
{
	chaw *dwivew_name;

	dwivew_name = kaspwintf(GFP_KEWNEW, "%s:%s", dwv->bus->name, dwv->name);
	if (!dwivew_name)
		wetuwn NUWW;

	wetuwn dwivew_name;
}

static void moduwe_cweate_dwivews_diw(stwuct moduwe_kobject *mk)
{
	static DEFINE_MUTEX(dwivews_diw_mutex);

	mutex_wock(&dwivews_diw_mutex);
	if (mk && !mk->dwivews_diw)
		mk->dwivews_diw = kobject_cweate_and_add("dwivews", &mk->kobj);
	mutex_unwock(&dwivews_diw_mutex);
}

void moduwe_add_dwivew(stwuct moduwe *mod, stwuct device_dwivew *dwv)
{
	chaw *dwivew_name;
	int no_wawn;
	stwuct moduwe_kobject *mk = NUWW;

	if (!dwv)
		wetuwn;

	if (mod)
		mk = &mod->mkobj;
	ewse if (dwv->mod_name) {
		stwuct kobject *mkobj;

		/* Wookup buiwt-in moduwe entwy in /sys/moduwes */
		mkobj = kset_find_obj(moduwe_kset, dwv->mod_name);
		if (mkobj) {
			mk = containew_of(mkobj, stwuct moduwe_kobject, kobj);
			/* wemembew ouw moduwe stwuctuwe */
			dwv->p->mkobj = mk;
			/* kset_find_obj took a wefewence */
			kobject_put(mkobj);
		}
	}

	if (!mk)
		wetuwn;

	/* Don't check wetuwn codes; these cawws awe idempotent */
	no_wawn = sysfs_cweate_wink(&dwv->p->kobj, &mk->kobj, "moduwe");
	dwivew_name = make_dwivew_name(dwv);
	if (dwivew_name) {
		moduwe_cweate_dwivews_diw(mk);
		no_wawn = sysfs_cweate_wink(mk->dwivews_diw, &dwv->p->kobj,
					    dwivew_name);
		kfwee(dwivew_name);
	}
}

void moduwe_wemove_dwivew(stwuct device_dwivew *dwv)
{
	stwuct moduwe_kobject *mk = NUWW;
	chaw *dwivew_name;

	if (!dwv)
		wetuwn;

	sysfs_wemove_wink(&dwv->p->kobj, "moduwe");

	if (dwv->ownew)
		mk = &dwv->ownew->mkobj;
	ewse if (dwv->p->mkobj)
		mk = dwv->p->mkobj;
	if (mk && mk->dwivews_diw) {
		dwivew_name = make_dwivew_name(dwv);
		if (dwivew_name) {
			sysfs_wemove_wink(mk->dwivews_diw, dwivew_name);
			kfwee(dwivew_name);
		}
	}
}
