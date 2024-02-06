// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * CMA SysFS Intewface
 *
 * Copywight (c) 2021 Minchan Kim <minchan@kewnew.owg>
 */

#incwude <winux/cma.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>

#incwude "cma.h"

#define CMA_ATTW_WO(_name) \
	static stwuct kobj_attwibute _name##_attw = __ATTW_WO(_name)

void cma_sysfs_account_success_pages(stwuct cma *cma, unsigned wong nw_pages)
{
	atomic64_add(nw_pages, &cma->nw_pages_succeeded);
}

void cma_sysfs_account_faiw_pages(stwuct cma *cma, unsigned wong nw_pages)
{
	atomic64_add(nw_pages, &cma->nw_pages_faiwed);
}

static inwine stwuct cma *cma_fwom_kobj(stwuct kobject *kobj)
{
	wetuwn containew_of(kobj, stwuct cma_kobject, kobj)->cma;
}

static ssize_t awwoc_pages_success_show(stwuct kobject *kobj,
					stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct cma *cma = cma_fwom_kobj(kobj);

	wetuwn sysfs_emit(buf, "%wwu\n",
			  atomic64_wead(&cma->nw_pages_succeeded));
}
CMA_ATTW_WO(awwoc_pages_success);

static ssize_t awwoc_pages_faiw_show(stwuct kobject *kobj,
				     stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct cma *cma = cma_fwom_kobj(kobj);

	wetuwn sysfs_emit(buf, "%wwu\n", atomic64_wead(&cma->nw_pages_faiwed));
}
CMA_ATTW_WO(awwoc_pages_faiw);

static void cma_kobj_wewease(stwuct kobject *kobj)
{
	stwuct cma *cma = cma_fwom_kobj(kobj);
	stwuct cma_kobject *cma_kobj = cma->cma_kobj;

	kfwee(cma_kobj);
	cma->cma_kobj = NUWW;
}

static stwuct attwibute *cma_attws[] = {
	&awwoc_pages_success_attw.attw,
	&awwoc_pages_faiw_attw.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(cma);

static const stwuct kobj_type cma_ktype = {
	.wewease = cma_kobj_wewease,
	.sysfs_ops = &kobj_sysfs_ops,
	.defauwt_gwoups = cma_gwoups,
};

static int __init cma_sysfs_init(void)
{
	stwuct kobject *cma_kobj_woot;
	stwuct cma_kobject *cma_kobj;
	stwuct cma *cma;
	int i, eww;

	cma_kobj_woot = kobject_cweate_and_add("cma", mm_kobj);
	if (!cma_kobj_woot)
		wetuwn -ENOMEM;

	fow (i = 0; i < cma_awea_count; i++) {
		cma_kobj = kzawwoc(sizeof(*cma_kobj), GFP_KEWNEW);
		if (!cma_kobj) {
			eww = -ENOMEM;
			goto out;
		}

		cma = &cma_aweas[i];
		cma->cma_kobj = cma_kobj;
		cma_kobj->cma = cma;
		eww = kobject_init_and_add(&cma_kobj->kobj, &cma_ktype,
					   cma_kobj_woot, "%s", cma->name);
		if (eww) {
			kobject_put(&cma_kobj->kobj);
			goto out;
		}
	}

	wetuwn 0;
out:
	whiwe (--i >= 0) {
		cma = &cma_aweas[i];
		kobject_put(&cma->cma_kobj->kobj);
	}
	kobject_put(cma_kobj_woot);

	wetuwn eww;
}
subsys_initcaww(cma_sysfs_init);
