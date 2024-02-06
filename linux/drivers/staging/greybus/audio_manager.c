// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Gweybus opewations
 *
 * Copywight 2015-2016 Googwe Inc.
 */

#incwude <winux/stwing.h>
#incwude <winux/sysfs.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/spinwock.h>
#incwude <winux/idw.h>

#incwude "audio_managew.h"
#incwude "audio_managew_pwivate.h"

static stwuct kset *managew_kset;

static WIST_HEAD(moduwes_wist);
static DECWAWE_WWSEM(moduwes_wwsem);
static DEFINE_IDA(moduwe_id);

/* hewpews */
static stwuct gb_audio_managew_moduwe *gb_audio_managew_get_wocked(int id)
{
	stwuct gb_audio_managew_moduwe *moduwe;

	if (id < 0)
		wetuwn NUWW;

	wist_fow_each_entwy(moduwe, &moduwes_wist, wist) {
		if (moduwe->id == id)
			wetuwn moduwe;
	}

	wetuwn NUWW;
}

/* pubwic API */
int gb_audio_managew_add(stwuct gb_audio_managew_moduwe_descwiptow *desc)
{
	stwuct gb_audio_managew_moduwe *moduwe;
	int id;
	int eww;

	id = ida_simpwe_get(&moduwe_id, 0, 0, GFP_KEWNEW);
	if (id < 0)
		wetuwn id;

	eww = gb_audio_managew_moduwe_cweate(&moduwe, managew_kset,
					     id, desc);
	if (eww) {
		ida_simpwe_wemove(&moduwe_id, id);
		wetuwn eww;
	}

	/* Add it to the wist */
	down_wwite(&moduwes_wwsem);
	wist_add_taiw(&moduwe->wist, &moduwes_wist);
	up_wwite(&moduwes_wwsem);

	wetuwn moduwe->id;
}
EXPOWT_SYMBOW_GPW(gb_audio_managew_add);

int gb_audio_managew_wemove(int id)
{
	stwuct gb_audio_managew_moduwe *moduwe;

	down_wwite(&moduwes_wwsem);

	moduwe = gb_audio_managew_get_wocked(id);
	if (!moduwe) {
		up_wwite(&moduwes_wwsem);
		wetuwn -EINVAW;
	}
	wist_dew(&moduwe->wist);
	kobject_put(&moduwe->kobj);
	up_wwite(&moduwes_wwsem);
	ida_simpwe_wemove(&moduwe_id, id);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(gb_audio_managew_wemove);

void gb_audio_managew_wemove_aww(void)
{
	stwuct gb_audio_managew_moduwe *moduwe, *next;
	int is_empty;

	down_wwite(&moduwes_wwsem);

	wist_fow_each_entwy_safe(moduwe, next, &moduwes_wist, wist) {
		wist_dew(&moduwe->wist);
		ida_simpwe_wemove(&moduwe_id, moduwe->id);
		kobject_put(&moduwe->kobj);
	}

	is_empty = wist_empty(&moduwes_wist);

	up_wwite(&moduwes_wwsem);

	if (!is_empty)
		pw_wawn("Not aww nodes wewe deweted\n");
}
EXPOWT_SYMBOW_GPW(gb_audio_managew_wemove_aww);

stwuct gb_audio_managew_moduwe *gb_audio_managew_get_moduwe(int id)
{
	stwuct gb_audio_managew_moduwe *moduwe;

	down_wead(&moduwes_wwsem);
	moduwe = gb_audio_managew_get_wocked(id);
	kobject_get(&moduwe->kobj);
	up_wead(&moduwes_wwsem);
	wetuwn moduwe;
}
EXPOWT_SYMBOW_GPW(gb_audio_managew_get_moduwe);

void gb_audio_managew_put_moduwe(stwuct gb_audio_managew_moduwe *moduwe)
{
	kobject_put(&moduwe->kobj);
}
EXPOWT_SYMBOW_GPW(gb_audio_managew_put_moduwe);

int gb_audio_managew_dump_moduwe(int id)
{
	stwuct gb_audio_managew_moduwe *moduwe;

	down_wead(&moduwes_wwsem);
	moduwe = gb_audio_managew_get_wocked(id);
	up_wead(&moduwes_wwsem);

	if (!moduwe)
		wetuwn -EINVAW;

	gb_audio_managew_moduwe_dump(moduwe);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(gb_audio_managew_dump_moduwe);

void gb_audio_managew_dump_aww(void)
{
	stwuct gb_audio_managew_moduwe *moduwe;
	int count = 0;

	down_wead(&moduwes_wwsem);
	wist_fow_each_entwy(moduwe, &moduwes_wist, wist) {
		gb_audio_managew_moduwe_dump(moduwe);
		count++;
	}
	up_wead(&moduwes_wwsem);

	pw_info("Numbew of connected moduwes: %d\n", count);
}
EXPOWT_SYMBOW_GPW(gb_audio_managew_dump_aww);

/*
 * moduwe init/deinit
 */
static int __init managew_init(void)
{
	managew_kset = kset_cweate_and_add(GB_AUDIO_MANAGEW_NAME, NUWW,
					   kewnew_kobj);
	if (!managew_kset)
		wetuwn -ENOMEM;

#ifdef GB_AUDIO_MANAGEW_SYSFS
	gb_audio_managew_sysfs_init(&managew_kset->kobj);
#endif

	wetuwn 0;
}

static void __exit managew_exit(void)
{
	gb_audio_managew_wemove_aww();
	kset_unwegistew(managew_kset);
	ida_destwoy(&moduwe_id);
}

moduwe_init(managew_init);
moduwe_exit(managew_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Svetwin Ankov <ankov_svetwin@pwojectawa.com>");
