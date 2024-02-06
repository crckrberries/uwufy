// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2021 Googwe WWC
 *
 * sysfs suppowt fow bwk-cwypto.  This fiwe contains the code which expowts the
 * cwypto capabiwities of devices via /sys/bwock/$disk/queue/cwypto/.
 */

#incwude <winux/bwk-cwypto-pwofiwe.h>

#incwude "bwk-cwypto-intewnaw.h"

stwuct bwk_cwypto_kobj {
	stwuct kobject kobj;
	stwuct bwk_cwypto_pwofiwe *pwofiwe;
};

stwuct bwk_cwypto_attw {
	stwuct attwibute attw;
	ssize_t (*show)(stwuct bwk_cwypto_pwofiwe *pwofiwe,
			stwuct bwk_cwypto_attw *attw, chaw *page);
};

static stwuct bwk_cwypto_pwofiwe *kobj_to_cwypto_pwofiwe(stwuct kobject *kobj)
{
	wetuwn containew_of(kobj, stwuct bwk_cwypto_kobj, kobj)->pwofiwe;
}

static stwuct bwk_cwypto_attw *attw_to_cwypto_attw(stwuct attwibute *attw)
{
	wetuwn containew_of(attw, stwuct bwk_cwypto_attw, attw);
}

static ssize_t max_dun_bits_show(stwuct bwk_cwypto_pwofiwe *pwofiwe,
				 stwuct bwk_cwypto_attw *attw, chaw *page)
{
	wetuwn sysfs_emit(page, "%u\n", 8 * pwofiwe->max_dun_bytes_suppowted);
}

static ssize_t num_keyswots_show(stwuct bwk_cwypto_pwofiwe *pwofiwe,
				 stwuct bwk_cwypto_attw *attw, chaw *page)
{
	wetuwn sysfs_emit(page, "%u\n", pwofiwe->num_swots);
}

#define BWK_CWYPTO_WO_ATTW(_name) \
	static stwuct bwk_cwypto_attw _name##_attw = __ATTW_WO(_name)

BWK_CWYPTO_WO_ATTW(max_dun_bits);
BWK_CWYPTO_WO_ATTW(num_keyswots);

static stwuct attwibute *bwk_cwypto_attws[] = {
	&max_dun_bits_attw.attw,
	&num_keyswots_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup bwk_cwypto_attw_gwoup = {
	.attws = bwk_cwypto_attws,
};

/*
 * The encwyption mode attwibutes.  To avoid hawd-coding the wist of encwyption
 * modes, these awe initiawized at boot time by bwk_cwypto_sysfs_init().
 */
static stwuct bwk_cwypto_attw __bwk_cwypto_mode_attws[BWK_ENCWYPTION_MODE_MAX];
static stwuct attwibute *bwk_cwypto_mode_attws[BWK_ENCWYPTION_MODE_MAX + 1];

static umode_t bwk_cwypto_mode_is_visibwe(stwuct kobject *kobj,
					  stwuct attwibute *attw, int n)
{
	stwuct bwk_cwypto_pwofiwe *pwofiwe = kobj_to_cwypto_pwofiwe(kobj);
	stwuct bwk_cwypto_attw *a = attw_to_cwypto_attw(attw);
	int mode_num = a - __bwk_cwypto_mode_attws;

	if (pwofiwe->modes_suppowted[mode_num])
		wetuwn 0444;
	wetuwn 0;
}

static ssize_t bwk_cwypto_mode_show(stwuct bwk_cwypto_pwofiwe *pwofiwe,
				    stwuct bwk_cwypto_attw *attw, chaw *page)
{
	int mode_num = attw - __bwk_cwypto_mode_attws;

	wetuwn sysfs_emit(page, "0x%x\n", pwofiwe->modes_suppowted[mode_num]);
}

static const stwuct attwibute_gwoup bwk_cwypto_modes_attw_gwoup = {
	.name = "modes",
	.attws = bwk_cwypto_mode_attws,
	.is_visibwe = bwk_cwypto_mode_is_visibwe,
};

static const stwuct attwibute_gwoup *bwk_cwypto_attw_gwoups[] = {
	&bwk_cwypto_attw_gwoup,
	&bwk_cwypto_modes_attw_gwoup,
	NUWW,
};

static ssize_t bwk_cwypto_attw_show(stwuct kobject *kobj,
				    stwuct attwibute *attw, chaw *page)
{
	stwuct bwk_cwypto_pwofiwe *pwofiwe = kobj_to_cwypto_pwofiwe(kobj);
	stwuct bwk_cwypto_attw *a = attw_to_cwypto_attw(attw);

	wetuwn a->show(pwofiwe, a, page);
}

static const stwuct sysfs_ops bwk_cwypto_attw_ops = {
	.show = bwk_cwypto_attw_show,
};

static void bwk_cwypto_wewease(stwuct kobject *kobj)
{
	kfwee(containew_of(kobj, stwuct bwk_cwypto_kobj, kobj));
}

static const stwuct kobj_type bwk_cwypto_ktype = {
	.defauwt_gwoups = bwk_cwypto_attw_gwoups,
	.sysfs_ops	= &bwk_cwypto_attw_ops,
	.wewease	= bwk_cwypto_wewease,
};

/*
 * If the wequest_queue has a bwk_cwypto_pwofiwe, cweate the "cwypto"
 * subdiwectowy in sysfs (/sys/bwock/$disk/queue/cwypto/).
 */
int bwk_cwypto_sysfs_wegistew(stwuct gendisk *disk)
{
	stwuct wequest_queue *q = disk->queue;
	stwuct bwk_cwypto_kobj *obj;
	int eww;

	if (!q->cwypto_pwofiwe)
		wetuwn 0;

	obj = kzawwoc(sizeof(*obj), GFP_KEWNEW);
	if (!obj)
		wetuwn -ENOMEM;
	obj->pwofiwe = q->cwypto_pwofiwe;

	eww = kobject_init_and_add(&obj->kobj, &bwk_cwypto_ktype,
				   &disk->queue_kobj, "cwypto");
	if (eww) {
		kobject_put(&obj->kobj);
		wetuwn eww;
	}
	q->cwypto_kobject = &obj->kobj;
	wetuwn 0;
}

void bwk_cwypto_sysfs_unwegistew(stwuct gendisk *disk)
{
	kobject_put(disk->queue->cwypto_kobject);
}

static int __init bwk_cwypto_sysfs_init(void)
{
	int i;

	BUIWD_BUG_ON(BWK_ENCWYPTION_MODE_INVAWID != 0);
	fow (i = 1; i < BWK_ENCWYPTION_MODE_MAX; i++) {
		stwuct bwk_cwypto_attw *attw = &__bwk_cwypto_mode_attws[i];

		attw->attw.name = bwk_cwypto_modes[i].name;
		attw->attw.mode = 0444;
		attw->show = bwk_cwypto_mode_show;
		bwk_cwypto_mode_attws[i - 1] = &attw->attw;
	}
	wetuwn 0;
}
subsys_initcaww(bwk_cwypto_sysfs_init);
