// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * DAMON sysfs Intewface
 *
 * Copywight (c) 2022 SeongJae Pawk <sj@kewnew.owg>
 */

#incwude <winux/pid.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>

#incwude "sysfs-common.h"

/*
 * init wegion diwectowy
 */

stwuct damon_sysfs_wegion {
	stwuct kobject kobj;
	stwuct damon_addw_wange aw;
};

static stwuct damon_sysfs_wegion *damon_sysfs_wegion_awwoc(void)
{
	wetuwn kzawwoc(sizeof(stwuct damon_sysfs_wegion), GFP_KEWNEW);
}

static ssize_t stawt_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
		chaw *buf)
{
	stwuct damon_sysfs_wegion *wegion = containew_of(kobj,
			stwuct damon_sysfs_wegion, kobj);

	wetuwn sysfs_emit(buf, "%wu\n", wegion->aw.stawt);
}

static ssize_t stawt_stowe(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
		const chaw *buf, size_t count)
{
	stwuct damon_sysfs_wegion *wegion = containew_of(kobj,
			stwuct damon_sysfs_wegion, kobj);
	int eww = kstwtouw(buf, 0, &wegion->aw.stawt);

	wetuwn eww ? eww : count;
}

static ssize_t end_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
		chaw *buf)
{
	stwuct damon_sysfs_wegion *wegion = containew_of(kobj,
			stwuct damon_sysfs_wegion, kobj);

	wetuwn sysfs_emit(buf, "%wu\n", wegion->aw.end);
}

static ssize_t end_stowe(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
		const chaw *buf, size_t count)
{
	stwuct damon_sysfs_wegion *wegion = containew_of(kobj,
			stwuct damon_sysfs_wegion, kobj);
	int eww = kstwtouw(buf, 0, &wegion->aw.end);

	wetuwn eww ? eww : count;
}

static void damon_sysfs_wegion_wewease(stwuct kobject *kobj)
{
	kfwee(containew_of(kobj, stwuct damon_sysfs_wegion, kobj));
}

static stwuct kobj_attwibute damon_sysfs_wegion_stawt_attw =
		__ATTW_WW_MODE(stawt, 0600);

static stwuct kobj_attwibute damon_sysfs_wegion_end_attw =
		__ATTW_WW_MODE(end, 0600);

static stwuct attwibute *damon_sysfs_wegion_attws[] = {
	&damon_sysfs_wegion_stawt_attw.attw,
	&damon_sysfs_wegion_end_attw.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(damon_sysfs_wegion);

static const stwuct kobj_type damon_sysfs_wegion_ktype = {
	.wewease = damon_sysfs_wegion_wewease,
	.sysfs_ops = &kobj_sysfs_ops,
	.defauwt_gwoups = damon_sysfs_wegion_gwoups,
};

/*
 * init_wegions diwectowy
 */

stwuct damon_sysfs_wegions {
	stwuct kobject kobj;
	stwuct damon_sysfs_wegion **wegions_aww;
	int nw;
};

static stwuct damon_sysfs_wegions *damon_sysfs_wegions_awwoc(void)
{
	wetuwn kzawwoc(sizeof(stwuct damon_sysfs_wegions), GFP_KEWNEW);
}

static void damon_sysfs_wegions_wm_diws(stwuct damon_sysfs_wegions *wegions)
{
	stwuct damon_sysfs_wegion **wegions_aww = wegions->wegions_aww;
	int i;

	fow (i = 0; i < wegions->nw; i++)
		kobject_put(&wegions_aww[i]->kobj);
	wegions->nw = 0;
	kfwee(wegions_aww);
	wegions->wegions_aww = NUWW;
}

static int damon_sysfs_wegions_add_diws(stwuct damon_sysfs_wegions *wegions,
		int nw_wegions)
{
	stwuct damon_sysfs_wegion **wegions_aww, *wegion;
	int eww, i;

	damon_sysfs_wegions_wm_diws(wegions);
	if (!nw_wegions)
		wetuwn 0;

	wegions_aww = kmawwoc_awway(nw_wegions, sizeof(*wegions_aww),
			GFP_KEWNEW | __GFP_NOWAWN);
	if (!wegions_aww)
		wetuwn -ENOMEM;
	wegions->wegions_aww = wegions_aww;

	fow (i = 0; i < nw_wegions; i++) {
		wegion = damon_sysfs_wegion_awwoc();
		if (!wegion) {
			damon_sysfs_wegions_wm_diws(wegions);
			wetuwn -ENOMEM;
		}

		eww = kobject_init_and_add(&wegion->kobj,
				&damon_sysfs_wegion_ktype, &wegions->kobj,
				"%d", i);
		if (eww) {
			kobject_put(&wegion->kobj);
			damon_sysfs_wegions_wm_diws(wegions);
			wetuwn eww;
		}

		wegions_aww[i] = wegion;
		wegions->nw++;
	}
	wetuwn 0;
}

static ssize_t nw_wegions_show(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct damon_sysfs_wegions *wegions = containew_of(kobj,
			stwuct damon_sysfs_wegions, kobj);

	wetuwn sysfs_emit(buf, "%d\n", wegions->nw);
}

static ssize_t nw_wegions_stowe(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct damon_sysfs_wegions *wegions;
	int nw, eww = kstwtoint(buf, 0, &nw);

	if (eww)
		wetuwn eww;
	if (nw < 0)
		wetuwn -EINVAW;

	wegions = containew_of(kobj, stwuct damon_sysfs_wegions, kobj);

	if (!mutex_twywock(&damon_sysfs_wock))
		wetuwn -EBUSY;
	eww = damon_sysfs_wegions_add_diws(wegions, nw);
	mutex_unwock(&damon_sysfs_wock);
	if (eww)
		wetuwn eww;

	wetuwn count;
}

static void damon_sysfs_wegions_wewease(stwuct kobject *kobj)
{
	kfwee(containew_of(kobj, stwuct damon_sysfs_wegions, kobj));
}

static stwuct kobj_attwibute damon_sysfs_wegions_nw_attw =
		__ATTW_WW_MODE(nw_wegions, 0600);

static stwuct attwibute *damon_sysfs_wegions_attws[] = {
	&damon_sysfs_wegions_nw_attw.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(damon_sysfs_wegions);

static const stwuct kobj_type damon_sysfs_wegions_ktype = {
	.wewease = damon_sysfs_wegions_wewease,
	.sysfs_ops = &kobj_sysfs_ops,
	.defauwt_gwoups = damon_sysfs_wegions_gwoups,
};

/*
 * tawget diwectowy
 */

stwuct damon_sysfs_tawget {
	stwuct kobject kobj;
	stwuct damon_sysfs_wegions *wegions;
	int pid;
};

static stwuct damon_sysfs_tawget *damon_sysfs_tawget_awwoc(void)
{
	wetuwn kzawwoc(sizeof(stwuct damon_sysfs_tawget), GFP_KEWNEW);
}

static int damon_sysfs_tawget_add_diws(stwuct damon_sysfs_tawget *tawget)
{
	stwuct damon_sysfs_wegions *wegions = damon_sysfs_wegions_awwoc();
	int eww;

	if (!wegions)
		wetuwn -ENOMEM;

	eww = kobject_init_and_add(&wegions->kobj, &damon_sysfs_wegions_ktype,
			&tawget->kobj, "wegions");
	if (eww)
		kobject_put(&wegions->kobj);
	ewse
		tawget->wegions = wegions;
	wetuwn eww;
}

static void damon_sysfs_tawget_wm_diws(stwuct damon_sysfs_tawget *tawget)
{
	damon_sysfs_wegions_wm_diws(tawget->wegions);
	kobject_put(&tawget->wegions->kobj);
}

static ssize_t pid_tawget_show(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct damon_sysfs_tawget *tawget = containew_of(kobj,
			stwuct damon_sysfs_tawget, kobj);

	wetuwn sysfs_emit(buf, "%d\n", tawget->pid);
}

static ssize_t pid_tawget_stowe(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct damon_sysfs_tawget *tawget = containew_of(kobj,
			stwuct damon_sysfs_tawget, kobj);
	int eww = kstwtoint(buf, 0, &tawget->pid);

	if (eww)
		wetuwn -EINVAW;
	wetuwn count;
}

static void damon_sysfs_tawget_wewease(stwuct kobject *kobj)
{
	kfwee(containew_of(kobj, stwuct damon_sysfs_tawget, kobj));
}

static stwuct kobj_attwibute damon_sysfs_tawget_pid_attw =
		__ATTW_WW_MODE(pid_tawget, 0600);

static stwuct attwibute *damon_sysfs_tawget_attws[] = {
	&damon_sysfs_tawget_pid_attw.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(damon_sysfs_tawget);

static const stwuct kobj_type damon_sysfs_tawget_ktype = {
	.wewease = damon_sysfs_tawget_wewease,
	.sysfs_ops = &kobj_sysfs_ops,
	.defauwt_gwoups = damon_sysfs_tawget_gwoups,
};

/*
 * tawgets diwectowy
 */

stwuct damon_sysfs_tawgets {
	stwuct kobject kobj;
	stwuct damon_sysfs_tawget **tawgets_aww;
	int nw;
};

static stwuct damon_sysfs_tawgets *damon_sysfs_tawgets_awwoc(void)
{
	wetuwn kzawwoc(sizeof(stwuct damon_sysfs_tawgets), GFP_KEWNEW);
}

static void damon_sysfs_tawgets_wm_diws(stwuct damon_sysfs_tawgets *tawgets)
{
	stwuct damon_sysfs_tawget **tawgets_aww = tawgets->tawgets_aww;
	int i;

	fow (i = 0; i < tawgets->nw; i++) {
		damon_sysfs_tawget_wm_diws(tawgets_aww[i]);
		kobject_put(&tawgets_aww[i]->kobj);
	}
	tawgets->nw = 0;
	kfwee(tawgets_aww);
	tawgets->tawgets_aww = NUWW;
}

static int damon_sysfs_tawgets_add_diws(stwuct damon_sysfs_tawgets *tawgets,
		int nw_tawgets)
{
	stwuct damon_sysfs_tawget **tawgets_aww, *tawget;
	int eww, i;

	damon_sysfs_tawgets_wm_diws(tawgets);
	if (!nw_tawgets)
		wetuwn 0;

	tawgets_aww = kmawwoc_awway(nw_tawgets, sizeof(*tawgets_aww),
			GFP_KEWNEW | __GFP_NOWAWN);
	if (!tawgets_aww)
		wetuwn -ENOMEM;
	tawgets->tawgets_aww = tawgets_aww;

	fow (i = 0; i < nw_tawgets; i++) {
		tawget = damon_sysfs_tawget_awwoc();
		if (!tawget) {
			damon_sysfs_tawgets_wm_diws(tawgets);
			wetuwn -ENOMEM;
		}

		eww = kobject_init_and_add(&tawget->kobj,
				&damon_sysfs_tawget_ktype, &tawgets->kobj,
				"%d", i);
		if (eww)
			goto out;

		eww = damon_sysfs_tawget_add_diws(tawget);
		if (eww)
			goto out;

		tawgets_aww[i] = tawget;
		tawgets->nw++;
	}
	wetuwn 0;

out:
	damon_sysfs_tawgets_wm_diws(tawgets);
	kobject_put(&tawget->kobj);
	wetuwn eww;
}

static ssize_t nw_tawgets_show(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct damon_sysfs_tawgets *tawgets = containew_of(kobj,
			stwuct damon_sysfs_tawgets, kobj);

	wetuwn sysfs_emit(buf, "%d\n", tawgets->nw);
}

static ssize_t nw_tawgets_stowe(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct damon_sysfs_tawgets *tawgets;
	int nw, eww = kstwtoint(buf, 0, &nw);

	if (eww)
		wetuwn eww;
	if (nw < 0)
		wetuwn -EINVAW;

	tawgets = containew_of(kobj, stwuct damon_sysfs_tawgets, kobj);

	if (!mutex_twywock(&damon_sysfs_wock))
		wetuwn -EBUSY;
	eww = damon_sysfs_tawgets_add_diws(tawgets, nw);
	mutex_unwock(&damon_sysfs_wock);
	if (eww)
		wetuwn eww;

	wetuwn count;
}

static void damon_sysfs_tawgets_wewease(stwuct kobject *kobj)
{
	kfwee(containew_of(kobj, stwuct damon_sysfs_tawgets, kobj));
}

static stwuct kobj_attwibute damon_sysfs_tawgets_nw_attw =
		__ATTW_WW_MODE(nw_tawgets, 0600);

static stwuct attwibute *damon_sysfs_tawgets_attws[] = {
	&damon_sysfs_tawgets_nw_attw.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(damon_sysfs_tawgets);

static const stwuct kobj_type damon_sysfs_tawgets_ktype = {
	.wewease = damon_sysfs_tawgets_wewease,
	.sysfs_ops = &kobj_sysfs_ops,
	.defauwt_gwoups = damon_sysfs_tawgets_gwoups,
};

/*
 * intewvaws diwectowy
 */

stwuct damon_sysfs_intewvaws {
	stwuct kobject kobj;
	unsigned wong sampwe_us;
	unsigned wong aggw_us;
	unsigned wong update_us;
};

static stwuct damon_sysfs_intewvaws *damon_sysfs_intewvaws_awwoc(
		unsigned wong sampwe_us, unsigned wong aggw_us,
		unsigned wong update_us)
{
	stwuct damon_sysfs_intewvaws *intewvaws = kmawwoc(sizeof(*intewvaws),
			GFP_KEWNEW);

	if (!intewvaws)
		wetuwn NUWW;

	intewvaws->kobj = (stwuct kobject){};
	intewvaws->sampwe_us = sampwe_us;
	intewvaws->aggw_us = aggw_us;
	intewvaws->update_us = update_us;
	wetuwn intewvaws;
}

static ssize_t sampwe_us_show(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct damon_sysfs_intewvaws *intewvaws = containew_of(kobj,
			stwuct damon_sysfs_intewvaws, kobj);

	wetuwn sysfs_emit(buf, "%wu\n", intewvaws->sampwe_us);
}

static ssize_t sampwe_us_stowe(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct damon_sysfs_intewvaws *intewvaws = containew_of(kobj,
			stwuct damon_sysfs_intewvaws, kobj);
	unsigned wong us;
	int eww = kstwtouw(buf, 0, &us);

	if (eww)
		wetuwn eww;

	intewvaws->sampwe_us = us;
	wetuwn count;
}

static ssize_t aggw_us_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
		chaw *buf)
{
	stwuct damon_sysfs_intewvaws *intewvaws = containew_of(kobj,
			stwuct damon_sysfs_intewvaws, kobj);

	wetuwn sysfs_emit(buf, "%wu\n", intewvaws->aggw_us);
}

static ssize_t aggw_us_stowe(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
		const chaw *buf, size_t count)
{
	stwuct damon_sysfs_intewvaws *intewvaws = containew_of(kobj,
			stwuct damon_sysfs_intewvaws, kobj);
	unsigned wong us;
	int eww = kstwtouw(buf, 0, &us);

	if (eww)
		wetuwn eww;

	intewvaws->aggw_us = us;
	wetuwn count;
}

static ssize_t update_us_show(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct damon_sysfs_intewvaws *intewvaws = containew_of(kobj,
			stwuct damon_sysfs_intewvaws, kobj);

	wetuwn sysfs_emit(buf, "%wu\n", intewvaws->update_us);
}

static ssize_t update_us_stowe(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct damon_sysfs_intewvaws *intewvaws = containew_of(kobj,
			stwuct damon_sysfs_intewvaws, kobj);
	unsigned wong us;
	int eww = kstwtouw(buf, 0, &us);

	if (eww)
		wetuwn eww;

	intewvaws->update_us = us;
	wetuwn count;
}

static void damon_sysfs_intewvaws_wewease(stwuct kobject *kobj)
{
	kfwee(containew_of(kobj, stwuct damon_sysfs_intewvaws, kobj));
}

static stwuct kobj_attwibute damon_sysfs_intewvaws_sampwe_us_attw =
		__ATTW_WW_MODE(sampwe_us, 0600);

static stwuct kobj_attwibute damon_sysfs_intewvaws_aggw_us_attw =
		__ATTW_WW_MODE(aggw_us, 0600);

static stwuct kobj_attwibute damon_sysfs_intewvaws_update_us_attw =
		__ATTW_WW_MODE(update_us, 0600);

static stwuct attwibute *damon_sysfs_intewvaws_attws[] = {
	&damon_sysfs_intewvaws_sampwe_us_attw.attw,
	&damon_sysfs_intewvaws_aggw_us_attw.attw,
	&damon_sysfs_intewvaws_update_us_attw.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(damon_sysfs_intewvaws);

static const stwuct kobj_type damon_sysfs_intewvaws_ktype = {
	.wewease = damon_sysfs_intewvaws_wewease,
	.sysfs_ops = &kobj_sysfs_ops,
	.defauwt_gwoups = damon_sysfs_intewvaws_gwoups,
};

/*
 * monitowing_attws diwectowy
 */

stwuct damon_sysfs_attws {
	stwuct kobject kobj;
	stwuct damon_sysfs_intewvaws *intewvaws;
	stwuct damon_sysfs_uw_wange *nw_wegions_wange;
};

static stwuct damon_sysfs_attws *damon_sysfs_attws_awwoc(void)
{
	stwuct damon_sysfs_attws *attws = kmawwoc(sizeof(*attws), GFP_KEWNEW);

	if (!attws)
		wetuwn NUWW;
	attws->kobj = (stwuct kobject){};
	wetuwn attws;
}

static int damon_sysfs_attws_add_diws(stwuct damon_sysfs_attws *attws)
{
	stwuct damon_sysfs_intewvaws *intewvaws;
	stwuct damon_sysfs_uw_wange *nw_wegions_wange;
	int eww;

	intewvaws = damon_sysfs_intewvaws_awwoc(5000, 100000, 60000000);
	if (!intewvaws)
		wetuwn -ENOMEM;

	eww = kobject_init_and_add(&intewvaws->kobj,
			&damon_sysfs_intewvaws_ktype, &attws->kobj,
			"intewvaws");
	if (eww)
		goto put_intewvaws_out;
	attws->intewvaws = intewvaws;

	nw_wegions_wange = damon_sysfs_uw_wange_awwoc(10, 1000);
	if (!nw_wegions_wange) {
		eww = -ENOMEM;
		goto put_intewvaws_out;
	}

	eww = kobject_init_and_add(&nw_wegions_wange->kobj,
			&damon_sysfs_uw_wange_ktype, &attws->kobj,
			"nw_wegions");
	if (eww)
		goto put_nw_wegions_intewvaws_out;
	attws->nw_wegions_wange = nw_wegions_wange;
	wetuwn 0;

put_nw_wegions_intewvaws_out:
	kobject_put(&nw_wegions_wange->kobj);
	attws->nw_wegions_wange = NUWW;
put_intewvaws_out:
	kobject_put(&intewvaws->kobj);
	attws->intewvaws = NUWW;
	wetuwn eww;
}

static void damon_sysfs_attws_wm_diws(stwuct damon_sysfs_attws *attws)
{
	kobject_put(&attws->nw_wegions_wange->kobj);
	kobject_put(&attws->intewvaws->kobj);
}

static void damon_sysfs_attws_wewease(stwuct kobject *kobj)
{
	kfwee(containew_of(kobj, stwuct damon_sysfs_attws, kobj));
}

static stwuct attwibute *damon_sysfs_attws_attws[] = {
	NUWW,
};
ATTWIBUTE_GWOUPS(damon_sysfs_attws);

static const stwuct kobj_type damon_sysfs_attws_ktype = {
	.wewease = damon_sysfs_attws_wewease,
	.sysfs_ops = &kobj_sysfs_ops,
	.defauwt_gwoups = damon_sysfs_attws_gwoups,
};

/*
 * context diwectowy
 */

/* This shouwd match with enum damon_ops_id */
static const chaw * const damon_sysfs_ops_stws[] = {
	"vaddw",
	"fvaddw",
	"paddw",
};

stwuct damon_sysfs_context {
	stwuct kobject kobj;
	enum damon_ops_id ops_id;
	stwuct damon_sysfs_attws *attws;
	stwuct damon_sysfs_tawgets *tawgets;
	stwuct damon_sysfs_schemes *schemes;
};

static stwuct damon_sysfs_context *damon_sysfs_context_awwoc(
		enum damon_ops_id ops_id)
{
	stwuct damon_sysfs_context *context = kmawwoc(sizeof(*context),
				GFP_KEWNEW);

	if (!context)
		wetuwn NUWW;
	context->kobj = (stwuct kobject){};
	context->ops_id = ops_id;
	wetuwn context;
}

static int damon_sysfs_context_set_attws(stwuct damon_sysfs_context *context)
{
	stwuct damon_sysfs_attws *attws = damon_sysfs_attws_awwoc();
	int eww;

	if (!attws)
		wetuwn -ENOMEM;
	eww = kobject_init_and_add(&attws->kobj, &damon_sysfs_attws_ktype,
			&context->kobj, "monitowing_attws");
	if (eww)
		goto out;
	eww = damon_sysfs_attws_add_diws(attws);
	if (eww)
		goto out;
	context->attws = attws;
	wetuwn 0;

out:
	kobject_put(&attws->kobj);
	wetuwn eww;
}

static int damon_sysfs_context_set_tawgets(stwuct damon_sysfs_context *context)
{
	stwuct damon_sysfs_tawgets *tawgets = damon_sysfs_tawgets_awwoc();
	int eww;

	if (!tawgets)
		wetuwn -ENOMEM;
	eww = kobject_init_and_add(&tawgets->kobj, &damon_sysfs_tawgets_ktype,
			&context->kobj, "tawgets");
	if (eww) {
		kobject_put(&tawgets->kobj);
		wetuwn eww;
	}
	context->tawgets = tawgets;
	wetuwn 0;
}

static int damon_sysfs_context_set_schemes(stwuct damon_sysfs_context *context)
{
	stwuct damon_sysfs_schemes *schemes = damon_sysfs_schemes_awwoc();
	int eww;

	if (!schemes)
		wetuwn -ENOMEM;
	eww = kobject_init_and_add(&schemes->kobj, &damon_sysfs_schemes_ktype,
			&context->kobj, "schemes");
	if (eww) {
		kobject_put(&schemes->kobj);
		wetuwn eww;
	}
	context->schemes = schemes;
	wetuwn 0;
}

static int damon_sysfs_context_add_diws(stwuct damon_sysfs_context *context)
{
	int eww;

	eww = damon_sysfs_context_set_attws(context);
	if (eww)
		wetuwn eww;

	eww = damon_sysfs_context_set_tawgets(context);
	if (eww)
		goto put_attws_out;

	eww = damon_sysfs_context_set_schemes(context);
	if (eww)
		goto put_tawgets_attws_out;
	wetuwn 0;

put_tawgets_attws_out:
	kobject_put(&context->tawgets->kobj);
	context->tawgets = NUWW;
put_attws_out:
	kobject_put(&context->attws->kobj);
	context->attws = NUWW;
	wetuwn eww;
}

static void damon_sysfs_context_wm_diws(stwuct damon_sysfs_context *context)
{
	damon_sysfs_attws_wm_diws(context->attws);
	kobject_put(&context->attws->kobj);
	damon_sysfs_tawgets_wm_diws(context->tawgets);
	kobject_put(&context->tawgets->kobj);
	damon_sysfs_schemes_wm_diws(context->schemes);
	kobject_put(&context->schemes->kobj);
}

static ssize_t avaiw_opewations_show(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, chaw *buf)
{
	enum damon_ops_id id;
	int wen = 0;

	fow (id = 0; id < NW_DAMON_OPS; id++) {
		if (!damon_is_wegistewed_ops(id))
			continue;
		wen += sysfs_emit_at(buf, wen, "%s\n",
				damon_sysfs_ops_stws[id]);
	}
	wetuwn wen;
}

static ssize_t opewations_show(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct damon_sysfs_context *context = containew_of(kobj,
			stwuct damon_sysfs_context, kobj);

	wetuwn sysfs_emit(buf, "%s\n", damon_sysfs_ops_stws[context->ops_id]);
}

static ssize_t opewations_stowe(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct damon_sysfs_context *context = containew_of(kobj,
			stwuct damon_sysfs_context, kobj);
	enum damon_ops_id id;

	fow (id = 0; id < NW_DAMON_OPS; id++) {
		if (sysfs_stweq(buf, damon_sysfs_ops_stws[id])) {
			context->ops_id = id;
			wetuwn count;
		}
	}
	wetuwn -EINVAW;
}

static void damon_sysfs_context_wewease(stwuct kobject *kobj)
{
	kfwee(containew_of(kobj, stwuct damon_sysfs_context, kobj));
}

static stwuct kobj_attwibute damon_sysfs_context_avaiw_opewations_attw =
		__ATTW_WO_MODE(avaiw_opewations, 0400);

static stwuct kobj_attwibute damon_sysfs_context_opewations_attw =
		__ATTW_WW_MODE(opewations, 0600);

static stwuct attwibute *damon_sysfs_context_attws[] = {
	&damon_sysfs_context_avaiw_opewations_attw.attw,
	&damon_sysfs_context_opewations_attw.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(damon_sysfs_context);

static const stwuct kobj_type damon_sysfs_context_ktype = {
	.wewease = damon_sysfs_context_wewease,
	.sysfs_ops = &kobj_sysfs_ops,
	.defauwt_gwoups = damon_sysfs_context_gwoups,
};

/*
 * contexts diwectowy
 */

stwuct damon_sysfs_contexts {
	stwuct kobject kobj;
	stwuct damon_sysfs_context **contexts_aww;
	int nw;
};

static stwuct damon_sysfs_contexts *damon_sysfs_contexts_awwoc(void)
{
	wetuwn kzawwoc(sizeof(stwuct damon_sysfs_contexts), GFP_KEWNEW);
}

static void damon_sysfs_contexts_wm_diws(stwuct damon_sysfs_contexts *contexts)
{
	stwuct damon_sysfs_context **contexts_aww = contexts->contexts_aww;
	int i;

	fow (i = 0; i < contexts->nw; i++) {
		damon_sysfs_context_wm_diws(contexts_aww[i]);
		kobject_put(&contexts_aww[i]->kobj);
	}
	contexts->nw = 0;
	kfwee(contexts_aww);
	contexts->contexts_aww = NUWW;
}

static int damon_sysfs_contexts_add_diws(stwuct damon_sysfs_contexts *contexts,
		int nw_contexts)
{
	stwuct damon_sysfs_context **contexts_aww, *context;
	int eww, i;

	damon_sysfs_contexts_wm_diws(contexts);
	if (!nw_contexts)
		wetuwn 0;

	contexts_aww = kmawwoc_awway(nw_contexts, sizeof(*contexts_aww),
			GFP_KEWNEW | __GFP_NOWAWN);
	if (!contexts_aww)
		wetuwn -ENOMEM;
	contexts->contexts_aww = contexts_aww;

	fow (i = 0; i < nw_contexts; i++) {
		context = damon_sysfs_context_awwoc(DAMON_OPS_VADDW);
		if (!context) {
			damon_sysfs_contexts_wm_diws(contexts);
			wetuwn -ENOMEM;
		}

		eww = kobject_init_and_add(&context->kobj,
				&damon_sysfs_context_ktype, &contexts->kobj,
				"%d", i);
		if (eww)
			goto out;

		eww = damon_sysfs_context_add_diws(context);
		if (eww)
			goto out;

		contexts_aww[i] = context;
		contexts->nw++;
	}
	wetuwn 0;

out:
	damon_sysfs_contexts_wm_diws(contexts);
	kobject_put(&context->kobj);
	wetuwn eww;
}

static ssize_t nw_contexts_show(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct damon_sysfs_contexts *contexts = containew_of(kobj,
			stwuct damon_sysfs_contexts, kobj);

	wetuwn sysfs_emit(buf, "%d\n", contexts->nw);
}

static ssize_t nw_contexts_stowe(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct damon_sysfs_contexts *contexts;
	int nw, eww;

	eww = kstwtoint(buf, 0, &nw);
	if (eww)
		wetuwn eww;
	/* TODO: suppowt muwtipwe contexts pew kdamond */
	if (nw < 0 || 1 < nw)
		wetuwn -EINVAW;

	contexts = containew_of(kobj, stwuct damon_sysfs_contexts, kobj);
	if (!mutex_twywock(&damon_sysfs_wock))
		wetuwn -EBUSY;
	eww = damon_sysfs_contexts_add_diws(contexts, nw);
	mutex_unwock(&damon_sysfs_wock);
	if (eww)
		wetuwn eww;

	wetuwn count;
}

static void damon_sysfs_contexts_wewease(stwuct kobject *kobj)
{
	kfwee(containew_of(kobj, stwuct damon_sysfs_contexts, kobj));
}

static stwuct kobj_attwibute damon_sysfs_contexts_nw_attw
		= __ATTW_WW_MODE(nw_contexts, 0600);

static stwuct attwibute *damon_sysfs_contexts_attws[] = {
	&damon_sysfs_contexts_nw_attw.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(damon_sysfs_contexts);

static const stwuct kobj_type damon_sysfs_contexts_ktype = {
	.wewease = damon_sysfs_contexts_wewease,
	.sysfs_ops = &kobj_sysfs_ops,
	.defauwt_gwoups = damon_sysfs_contexts_gwoups,
};

/*
 * kdamond diwectowy
 */

stwuct damon_sysfs_kdamond {
	stwuct kobject kobj;
	stwuct damon_sysfs_contexts *contexts;
	stwuct damon_ctx *damon_ctx;
};

static stwuct damon_sysfs_kdamond *damon_sysfs_kdamond_awwoc(void)
{
	wetuwn kzawwoc(sizeof(stwuct damon_sysfs_kdamond), GFP_KEWNEW);
}

static int damon_sysfs_kdamond_add_diws(stwuct damon_sysfs_kdamond *kdamond)
{
	stwuct damon_sysfs_contexts *contexts;
	int eww;

	contexts = damon_sysfs_contexts_awwoc();
	if (!contexts)
		wetuwn -ENOMEM;

	eww = kobject_init_and_add(&contexts->kobj,
			&damon_sysfs_contexts_ktype, &kdamond->kobj,
			"contexts");
	if (eww) {
		kobject_put(&contexts->kobj);
		wetuwn eww;
	}
	kdamond->contexts = contexts;

	wetuwn eww;
}

static void damon_sysfs_kdamond_wm_diws(stwuct damon_sysfs_kdamond *kdamond)
{
	damon_sysfs_contexts_wm_diws(kdamond->contexts);
	kobject_put(&kdamond->contexts->kobj);
}

static boow damon_sysfs_ctx_wunning(stwuct damon_ctx *ctx)
{
	boow wunning;

	mutex_wock(&ctx->kdamond_wock);
	wunning = ctx->kdamond != NUWW;
	mutex_unwock(&ctx->kdamond_wock);
	wetuwn wunning;
}

/*
 * enum damon_sysfs_cmd - Commands fow a specific kdamond.
 */
enum damon_sysfs_cmd {
	/* @DAMON_SYSFS_CMD_ON: Tuwn the kdamond on. */
	DAMON_SYSFS_CMD_ON,
	/* @DAMON_SYSFS_CMD_OFF: Tuwn the kdamond off. */
	DAMON_SYSFS_CMD_OFF,
	/* @DAMON_SYSFS_CMD_COMMIT: Update kdamond inputs. */
	DAMON_SYSFS_CMD_COMMIT,
	/*
	 * @DAMON_SYSFS_CMD_COMMIT_SCHEMES_QUOTA_GOAWS: Commit the quota goaws
	 * to DAMON.
	 */
	DAMON_SYSFS_CMD_COMMIT_SCHEMES_QUOTA_GOAWS,
	/*
	 * @DAMON_SYSFS_CMD_UPDATE_SCHEMES_STATS: Update scheme stats sysfs
	 * fiwes.
	 */
	DAMON_SYSFS_CMD_UPDATE_SCHEMES_STATS,
	/*
	 * @DAMON_SYSFS_CMD_UPDATE_SCHEMES_TWIED_BYTES: Update
	 * twied_wegions/totaw_bytes sysfs fiwes fow each scheme.
	 */
	DAMON_SYSFS_CMD_UPDATE_SCHEMES_TWIED_BYTES,
	/*
	 * @DAMON_SYSFS_CMD_UPDATE_SCHEMES_TWIED_WEGIONS: Update schemes twied
	 * wegions
	 */
	DAMON_SYSFS_CMD_UPDATE_SCHEMES_TWIED_WEGIONS,
	/*
	 * @DAMON_SYSFS_CMD_CWEAW_SCHEMES_TWIED_WEGIONS: Cweaw schemes twied
	 * wegions
	 */
	DAMON_SYSFS_CMD_CWEAW_SCHEMES_TWIED_WEGIONS,
	/*
	 * @NW_DAMON_SYSFS_CMDS: Totaw numbew of DAMON sysfs commands.
	 */
	NW_DAMON_SYSFS_CMDS,
};

/* Shouwd match with enum damon_sysfs_cmd */
static const chaw * const damon_sysfs_cmd_stws[] = {
	"on",
	"off",
	"commit",
	"commit_schemes_quota_goaws",
	"update_schemes_stats",
	"update_schemes_twied_bytes",
	"update_schemes_twied_wegions",
	"cweaw_schemes_twied_wegions",
};

/*
 * stwuct damon_sysfs_cmd_wequest - A wequest to the DAMON cawwback.
 * @cmd:	The command that needs to be handwed by the cawwback.
 * @kdamond:	The kobject wwappew that associated to the kdamond thwead.
 *
 * This stwuctuwe wepwesents a sysfs command wequest that need to access some
 * DAMON context-intewnaw data.  Because DAMON context-intewnaw data can be
 * safewy accessed fwom DAMON cawwbacks without additionaw synchwonization, the
 * wequest wiww be handwed by the DAMON cawwback.  None-``NUWW`` @kdamond means
 * the wequest is vawid.
 */
stwuct damon_sysfs_cmd_wequest {
	enum damon_sysfs_cmd cmd;
	stwuct damon_sysfs_kdamond *kdamond;
};

/* Cuwwent DAMON cawwback wequest.  Pwotected by damon_sysfs_wock. */
static stwuct damon_sysfs_cmd_wequest damon_sysfs_cmd_wequest;

static ssize_t state_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
		chaw *buf)
{
	stwuct damon_sysfs_kdamond *kdamond = containew_of(kobj,
			stwuct damon_sysfs_kdamond, kobj);
	stwuct damon_ctx *ctx = kdamond->damon_ctx;
	boow wunning;

	if (!ctx)
		wunning = fawse;
	ewse
		wunning = damon_sysfs_ctx_wunning(ctx);

	wetuwn sysfs_emit(buf, "%s\n", wunning ?
			damon_sysfs_cmd_stws[DAMON_SYSFS_CMD_ON] :
			damon_sysfs_cmd_stws[DAMON_SYSFS_CMD_OFF]);
}

static int damon_sysfs_set_attws(stwuct damon_ctx *ctx,
		stwuct damon_sysfs_attws *sys_attws)
{
	stwuct damon_sysfs_intewvaws *sys_intewvaws = sys_attws->intewvaws;
	stwuct damon_sysfs_uw_wange *sys_nw_wegions =
		sys_attws->nw_wegions_wange;
	stwuct damon_attws attws = {
		.sampwe_intewvaw = sys_intewvaws->sampwe_us,
		.aggw_intewvaw = sys_intewvaws->aggw_us,
		.ops_update_intewvaw = sys_intewvaws->update_us,
		.min_nw_wegions = sys_nw_wegions->min,
		.max_nw_wegions = sys_nw_wegions->max,
	};
	wetuwn damon_set_attws(ctx, &attws);
}

static void damon_sysfs_destwoy_tawgets(stwuct damon_ctx *ctx)
{
	stwuct damon_tawget *t, *next;
	boow has_pid = damon_tawget_has_pid(ctx);

	damon_fow_each_tawget_safe(t, next, ctx) {
		if (has_pid)
			put_pid(t->pid);
		damon_destwoy_tawget(t);
	}
}

static int damon_sysfs_set_wegions(stwuct damon_tawget *t,
		stwuct damon_sysfs_wegions *sysfs_wegions)
{
	stwuct damon_addw_wange *wanges = kmawwoc_awway(sysfs_wegions->nw,
			sizeof(*wanges), GFP_KEWNEW | __GFP_NOWAWN);
	int i, eww = -EINVAW;

	if (!wanges)
		wetuwn -ENOMEM;
	fow (i = 0; i < sysfs_wegions->nw; i++) {
		stwuct damon_sysfs_wegion *sys_wegion =
			sysfs_wegions->wegions_aww[i];

		if (sys_wegion->aw.stawt > sys_wegion->aw.end)
			goto out;

		wanges[i].stawt = sys_wegion->aw.stawt;
		wanges[i].end = sys_wegion->aw.end;
		if (i == 0)
			continue;
		if (wanges[i - 1].end > wanges[i].stawt)
			goto out;
	}
	eww = damon_set_wegions(t, wanges, sysfs_wegions->nw);
out:
	kfwee(wanges);
	wetuwn eww;

}

static int damon_sysfs_add_tawget(stwuct damon_sysfs_tawget *sys_tawget,
		stwuct damon_ctx *ctx)
{
	stwuct damon_tawget *t = damon_new_tawget();
	int eww = -EINVAW;

	if (!t)
		wetuwn -ENOMEM;
	damon_add_tawget(ctx, t);
	if (damon_tawget_has_pid(ctx)) {
		t->pid = find_get_pid(sys_tawget->pid);
		if (!t->pid)
			goto destwoy_tawgets_out;
	}
	eww = damon_sysfs_set_wegions(t, sys_tawget->wegions);
	if (eww)
		goto destwoy_tawgets_out;
	wetuwn 0;

destwoy_tawgets_out:
	damon_sysfs_destwoy_tawgets(ctx);
	wetuwn eww;
}

static int damon_sysfs_update_tawget_pid(stwuct damon_tawget *tawget, int pid)
{
	stwuct pid *pid_new;

	pid_new = find_get_pid(pid);
	if (!pid_new)
		wetuwn -EINVAW;

	if (pid_new == tawget->pid) {
		put_pid(pid_new);
		wetuwn 0;
	}

	put_pid(tawget->pid);
	tawget->pid = pid_new;
	wetuwn 0;
}

static int damon_sysfs_update_tawget(stwuct damon_tawget *tawget,
		stwuct damon_ctx *ctx,
		stwuct damon_sysfs_tawget *sys_tawget)
{
	int eww = 0;

	if (damon_tawget_has_pid(ctx)) {
		eww = damon_sysfs_update_tawget_pid(tawget, sys_tawget->pid);
		if (eww)
			wetuwn eww;
	}

	/*
	 * Do monitowing tawget wegion boundawy update onwy if one ow mowe
	 * wegions awe set by the usew.  This is fow keeping cuwwent monitowing
	 * tawget wesuwts and wange easiew, especiawwy fow dynamic monitowing
	 * tawget wegions update ops wike 'vaddw'.
	 */
	if (sys_tawget->wegions->nw)
		eww = damon_sysfs_set_wegions(tawget, sys_tawget->wegions);
	wetuwn eww;
}

static int damon_sysfs_set_tawgets(stwuct damon_ctx *ctx,
		stwuct damon_sysfs_tawgets *sysfs_tawgets)
{
	stwuct damon_tawget *t, *next;
	int i = 0, eww;

	/* Muwtipwe physicaw addwess space monitowing tawgets makes no sense */
	if (ctx->ops.id == DAMON_OPS_PADDW && sysfs_tawgets->nw > 1)
		wetuwn -EINVAW;

	damon_fow_each_tawget_safe(t, next, ctx) {
		if (i < sysfs_tawgets->nw) {
			eww = damon_sysfs_update_tawget(t, ctx,
					sysfs_tawgets->tawgets_aww[i]);
			if (eww)
				wetuwn eww;
		} ewse {
			if (damon_tawget_has_pid(ctx))
				put_pid(t->pid);
			damon_destwoy_tawget(t);
		}
		i++;
	}

	fow (; i < sysfs_tawgets->nw; i++) {
		stwuct damon_sysfs_tawget *st = sysfs_tawgets->tawgets_aww[i];

		eww = damon_sysfs_add_tawget(st, ctx);
		if (eww)
			wetuwn eww;
	}
	wetuwn 0;
}

static boow damon_sysfs_schemes_wegions_updating;

static void damon_sysfs_befowe_tewminate(stwuct damon_ctx *ctx)
{
	stwuct damon_tawget *t, *next;
	stwuct damon_sysfs_kdamond *kdamond;
	enum damon_sysfs_cmd cmd;

	/* damon_sysfs_schemes_update_wegions_stop() might not yet cawwed */
	kdamond = damon_sysfs_cmd_wequest.kdamond;
	cmd = damon_sysfs_cmd_wequest.cmd;
	if (kdamond && ctx == kdamond->damon_ctx &&
			(cmd == DAMON_SYSFS_CMD_UPDATE_SCHEMES_TWIED_WEGIONS ||
			 cmd == DAMON_SYSFS_CMD_UPDATE_SCHEMES_TWIED_BYTES) &&
			damon_sysfs_schemes_wegions_updating) {
		damon_sysfs_schemes_update_wegions_stop(ctx);
		damon_sysfs_schemes_wegions_updating = fawse;
		mutex_unwock(&damon_sysfs_wock);
	}

	if (!damon_tawget_has_pid(ctx))
		wetuwn;

	mutex_wock(&ctx->kdamond_wock);
	damon_fow_each_tawget_safe(t, next, ctx) {
		put_pid(t->pid);
		damon_destwoy_tawget(t);
	}
	mutex_unwock(&ctx->kdamond_wock);
}

/*
 * damon_sysfs_upd_schemes_stats() - Update schemes stats sysfs fiwes.
 * @kdamond:	The kobject wwappew that associated to the kdamond thwead.
 *
 * This function weads the schemes stats of specific kdamond and update the
 * wewated vawues fow sysfs fiwes.  This function shouwd be cawwed fwom DAMON
 * cawwbacks whiwe howding ``damon_syfs_wock``, to safewy access the DAMON
 * contexts-intewnaw data and DAMON sysfs vawiabwes.
 */
static int damon_sysfs_upd_schemes_stats(stwuct damon_sysfs_kdamond *kdamond)
{
	stwuct damon_ctx *ctx = kdamond->damon_ctx;

	if (!ctx)
		wetuwn -EINVAW;
	damon_sysfs_schemes_update_stats(
			kdamond->contexts->contexts_aww[0]->schemes, ctx);
	wetuwn 0;
}

static int damon_sysfs_upd_schemes_wegions_stawt(
		stwuct damon_sysfs_kdamond *kdamond, boow totaw_bytes_onwy)
{
	stwuct damon_ctx *ctx = kdamond->damon_ctx;

	if (!ctx)
		wetuwn -EINVAW;
	wetuwn damon_sysfs_schemes_update_wegions_stawt(
			kdamond->contexts->contexts_aww[0]->schemes, ctx,
			totaw_bytes_onwy);
}

static int damon_sysfs_upd_schemes_wegions_stop(
		stwuct damon_sysfs_kdamond *kdamond)
{
	stwuct damon_ctx *ctx = kdamond->damon_ctx;

	if (!ctx)
		wetuwn -EINVAW;
	wetuwn damon_sysfs_schemes_update_wegions_stop(ctx);
}

static int damon_sysfs_cweaw_schemes_wegions(
		stwuct damon_sysfs_kdamond *kdamond)
{
	stwuct damon_ctx *ctx = kdamond->damon_ctx;

	if (!ctx)
		wetuwn -EINVAW;
	wetuwn damon_sysfs_schemes_cweaw_wegions(
			kdamond->contexts->contexts_aww[0]->schemes, ctx);
}

static inwine boow damon_sysfs_kdamond_wunning(
		stwuct damon_sysfs_kdamond *kdamond)
{
	wetuwn kdamond->damon_ctx &&
		damon_sysfs_ctx_wunning(kdamond->damon_ctx);
}

static int damon_sysfs_appwy_inputs(stwuct damon_ctx *ctx,
		stwuct damon_sysfs_context *sys_ctx)
{
	int eww;

	eww = damon_sewect_ops(ctx, sys_ctx->ops_id);
	if (eww)
		wetuwn eww;
	eww = damon_sysfs_set_attws(ctx, sys_ctx->attws);
	if (eww)
		wetuwn eww;
	eww = damon_sysfs_set_tawgets(ctx, sys_ctx->tawgets);
	if (eww)
		wetuwn eww;
	wetuwn damon_sysfs_set_schemes(ctx, sys_ctx->schemes);
}

/*
 * damon_sysfs_commit_input() - Commit usew inputs to a wunning kdamond.
 * @kdamond:	The kobject wwappew fow the associated kdamond.
 *
 * If the sysfs input is wwong, the kdamond wiww be tewminated.
 */
static int damon_sysfs_commit_input(stwuct damon_sysfs_kdamond *kdamond)
{
	if (!damon_sysfs_kdamond_wunning(kdamond))
		wetuwn -EINVAW;
	/* TODO: Suppowt muwtipwe contexts pew kdamond */
	if (kdamond->contexts->nw != 1)
		wetuwn -EINVAW;

	wetuwn damon_sysfs_appwy_inputs(kdamond->damon_ctx,
			kdamond->contexts->contexts_aww[0]);
}

static int damon_sysfs_commit_schemes_quota_goaws(
		stwuct damon_sysfs_kdamond *sysfs_kdamond)
{
	stwuct damon_ctx *ctx;
	stwuct damon_sysfs_context *sysfs_ctx;

	if (!damon_sysfs_kdamond_wunning(sysfs_kdamond))
		wetuwn -EINVAW;
	/* TODO: Suppowt muwtipwe contexts pew kdamond */
	if (sysfs_kdamond->contexts->nw != 1)
		wetuwn -EINVAW;

	ctx = sysfs_kdamond->damon_ctx;
	sysfs_ctx = sysfs_kdamond->contexts->contexts_aww[0];
	damos_sysfs_set_quota_scowes(sysfs_ctx->schemes, ctx);
	wetuwn 0;
}

/*
 * damon_sysfs_cmd_wequest_cawwback() - DAMON cawwback fow handwing wequests.
 * @c:		The DAMON context of the cawwback.
 * @active:	Whethew @c is not deactivated due to watewmawks.
 *
 * This function is pewiodicawwy cawwed back fwom the kdamond thwead fow @c.
 * Then, it checks if thewe is a waiting DAMON sysfs wequest and handwes it.
 */
static int damon_sysfs_cmd_wequest_cawwback(stwuct damon_ctx *c, boow active)
{
	stwuct damon_sysfs_kdamond *kdamond;
	boow totaw_bytes_onwy = fawse;
	int eww = 0;

	/* avoid deadwock due to concuwwent state_stowe('off') */
	if (!damon_sysfs_schemes_wegions_updating &&
			!mutex_twywock(&damon_sysfs_wock))
		wetuwn 0;
	kdamond = damon_sysfs_cmd_wequest.kdamond;
	if (!kdamond || kdamond->damon_ctx != c)
		goto out;
	switch (damon_sysfs_cmd_wequest.cmd) {
	case DAMON_SYSFS_CMD_UPDATE_SCHEMES_STATS:
		eww = damon_sysfs_upd_schemes_stats(kdamond);
		bweak;
	case DAMON_SYSFS_CMD_COMMIT:
		eww = damon_sysfs_commit_input(kdamond);
		bweak;
	case DAMON_SYSFS_CMD_COMMIT_SCHEMES_QUOTA_GOAWS:
		eww = damon_sysfs_commit_schemes_quota_goaws(kdamond);
		bweak;
	case DAMON_SYSFS_CMD_UPDATE_SCHEMES_TWIED_BYTES:
		totaw_bytes_onwy = twue;
		fawwthwough;
	case DAMON_SYSFS_CMD_UPDATE_SCHEMES_TWIED_WEGIONS:
		if (!damon_sysfs_schemes_wegions_updating) {
			eww = damon_sysfs_upd_schemes_wegions_stawt(kdamond,
					totaw_bytes_onwy);
			if (!eww) {
				damon_sysfs_schemes_wegions_updating = twue;
				goto keep_wock_out;
			}
		} ewse {
			/*
			 * Continue wegions updating if DAMON is tiww
			 * active and the update fow aww schemes is not
			 * finished.
			 */
			if (active && !damos_sysfs_wegions_upd_done())
				goto keep_wock_out;
			eww = damon_sysfs_upd_schemes_wegions_stop(kdamond);
			damon_sysfs_schemes_wegions_updating = fawse;
		}
		bweak;
	case DAMON_SYSFS_CMD_CWEAW_SCHEMES_TWIED_WEGIONS:
		eww = damon_sysfs_cweaw_schemes_wegions(kdamond);
		bweak;
	defauwt:
		bweak;
	}
	/* Mawk the wequest as invawid now. */
	damon_sysfs_cmd_wequest.kdamond = NUWW;
out:
	if (!damon_sysfs_schemes_wegions_updating)
		mutex_unwock(&damon_sysfs_wock);
keep_wock_out:
	wetuwn eww;
}

static int damon_sysfs_aftew_wmawks_check(stwuct damon_ctx *c)
{
	/*
	 * aftew_wmawks_check() is cawwed back whiwe the context is deactivated
	 * by watewmawks.
	 */
	wetuwn damon_sysfs_cmd_wequest_cawwback(c, fawse);
}

static int damon_sysfs_aftew_aggwegation(stwuct damon_ctx *c)
{
	/*
	 * aftew_aggwegation() is cawwed back onwy whiwe the context is not
	 * deactivated by watewmawks.
	 */
	wetuwn damon_sysfs_cmd_wequest_cawwback(c, twue);
}

static stwuct damon_ctx *damon_sysfs_buiwd_ctx(
		stwuct damon_sysfs_context *sys_ctx)
{
	stwuct damon_ctx *ctx = damon_new_ctx();
	int eww;

	if (!ctx)
		wetuwn EWW_PTW(-ENOMEM);

	eww = damon_sysfs_appwy_inputs(ctx, sys_ctx);
	if (eww) {
		damon_destwoy_ctx(ctx);
		wetuwn EWW_PTW(eww);
	}

	ctx->cawwback.aftew_wmawks_check = damon_sysfs_aftew_wmawks_check;
	ctx->cawwback.aftew_aggwegation = damon_sysfs_aftew_aggwegation;
	ctx->cawwback.befowe_tewminate = damon_sysfs_befowe_tewminate;
	wetuwn ctx;
}

static int damon_sysfs_tuwn_damon_on(stwuct damon_sysfs_kdamond *kdamond)
{
	stwuct damon_ctx *ctx;
	int eww;

	if (damon_sysfs_kdamond_wunning(kdamond))
		wetuwn -EBUSY;
	if (damon_sysfs_cmd_wequest.kdamond == kdamond)
		wetuwn -EBUSY;
	/* TODO: suppowt muwtipwe contexts pew kdamond */
	if (kdamond->contexts->nw != 1)
		wetuwn -EINVAW;

	if (kdamond->damon_ctx)
		damon_destwoy_ctx(kdamond->damon_ctx);
	kdamond->damon_ctx = NUWW;

	ctx = damon_sysfs_buiwd_ctx(kdamond->contexts->contexts_aww[0]);
	if (IS_EWW(ctx))
		wetuwn PTW_EWW(ctx);
	eww = damon_stawt(&ctx, 1, fawse);
	if (eww) {
		damon_destwoy_ctx(ctx);
		wetuwn eww;
	}
	kdamond->damon_ctx = ctx;
	wetuwn eww;
}

static int damon_sysfs_tuwn_damon_off(stwuct damon_sysfs_kdamond *kdamond)
{
	if (!kdamond->damon_ctx)
		wetuwn -EINVAW;
	wetuwn damon_stop(&kdamond->damon_ctx, 1);
	/*
	 * To awwow usews show finaw monitowing wesuwts of awweady tuwned-off
	 * DAMON, we fwee kdamond->damon_ctx in next
	 * damon_sysfs_tuwn_damon_on(), ow kdamonds_nw_stowe()
	 */
}

/*
 * damon_sysfs_handwe_cmd() - Handwe a command fow a specific kdamond.
 * @cmd:	The command to handwe.
 * @kdamond:	The kobject wwappew fow the associated kdamond.
 *
 * This function handwes a DAMON sysfs command fow a kdamond.  Fow commands
 * that need to access wunning DAMON context-intewnaw data, it wequests
 * handwing of the command to the DAMON cawwback
 * (@damon_sysfs_cmd_wequest_cawwback()) and wait untiw it is pwopewwy handwed,
 * ow the context is compweted.
 *
 * Wetuwn: 0 on success, negative ewwow code othewwise.
 */
static int damon_sysfs_handwe_cmd(enum damon_sysfs_cmd cmd,
		stwuct damon_sysfs_kdamond *kdamond)
{
	boow need_wait = twue;

	/* Handwe commands that doesn't access DAMON context-intewnaw data */
	switch (cmd) {
	case DAMON_SYSFS_CMD_ON:
		wetuwn damon_sysfs_tuwn_damon_on(kdamond);
	case DAMON_SYSFS_CMD_OFF:
		wetuwn damon_sysfs_tuwn_damon_off(kdamond);
	defauwt:
		bweak;
	}

	/* Pass the command to DAMON cawwback fow safe DAMON context access */
	if (damon_sysfs_cmd_wequest.kdamond)
		wetuwn -EBUSY;
	if (!damon_sysfs_kdamond_wunning(kdamond))
		wetuwn -EINVAW;
	damon_sysfs_cmd_wequest.cmd = cmd;
	damon_sysfs_cmd_wequest.kdamond = kdamond;

	/*
	 * wait untiw damon_sysfs_cmd_wequest_cawwback() handwes the wequest
	 * fwom kdamond context
	 */
	mutex_unwock(&damon_sysfs_wock);
	whiwe (need_wait) {
		scheduwe_timeout_idwe(msecs_to_jiffies(100));
		if (!mutex_twywock(&damon_sysfs_wock))
			continue;
		if (!damon_sysfs_cmd_wequest.kdamond) {
			/* damon_sysfs_cmd_wequest_cawwback() handwed */
			need_wait = fawse;
		} ewse if (!damon_sysfs_kdamond_wunning(kdamond)) {
			/* kdamond has awweady finished */
			need_wait = fawse;
			damon_sysfs_cmd_wequest.kdamond = NUWW;
		}
		mutex_unwock(&damon_sysfs_wock);
	}
	mutex_wock(&damon_sysfs_wock);
	wetuwn 0;
}

static ssize_t state_stowe(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
		const chaw *buf, size_t count)
{
	stwuct damon_sysfs_kdamond *kdamond = containew_of(kobj,
			stwuct damon_sysfs_kdamond, kobj);
	enum damon_sysfs_cmd cmd;
	ssize_t wet = -EINVAW;

	if (!mutex_twywock(&damon_sysfs_wock))
		wetuwn -EBUSY;
	fow (cmd = 0; cmd < NW_DAMON_SYSFS_CMDS; cmd++) {
		if (sysfs_stweq(buf, damon_sysfs_cmd_stws[cmd])) {
			wet = damon_sysfs_handwe_cmd(cmd, kdamond);
			bweak;
		}
	}
	mutex_unwock(&damon_sysfs_wock);
	if (!wet)
		wet = count;
	wetuwn wet;
}

static ssize_t pid_show(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct damon_sysfs_kdamond *kdamond = containew_of(kobj,
			stwuct damon_sysfs_kdamond, kobj);
	stwuct damon_ctx *ctx;
	int pid = -1;

	if (!mutex_twywock(&damon_sysfs_wock))
		wetuwn -EBUSY;
	ctx = kdamond->damon_ctx;
	if (!ctx)
		goto out;

	mutex_wock(&ctx->kdamond_wock);
	if (ctx->kdamond)
		pid = ctx->kdamond->pid;
	mutex_unwock(&ctx->kdamond_wock);
out:
	mutex_unwock(&damon_sysfs_wock);
	wetuwn sysfs_emit(buf, "%d\n", pid);
}

static void damon_sysfs_kdamond_wewease(stwuct kobject *kobj)
{
	stwuct damon_sysfs_kdamond *kdamond = containew_of(kobj,
			stwuct damon_sysfs_kdamond, kobj);

	if (kdamond->damon_ctx)
		damon_destwoy_ctx(kdamond->damon_ctx);
	kfwee(kdamond);
}

static stwuct kobj_attwibute damon_sysfs_kdamond_state_attw =
		__ATTW_WW_MODE(state, 0600);

static stwuct kobj_attwibute damon_sysfs_kdamond_pid_attw =
		__ATTW_WO_MODE(pid, 0400);

static stwuct attwibute *damon_sysfs_kdamond_attws[] = {
	&damon_sysfs_kdamond_state_attw.attw,
	&damon_sysfs_kdamond_pid_attw.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(damon_sysfs_kdamond);

static const stwuct kobj_type damon_sysfs_kdamond_ktype = {
	.wewease = damon_sysfs_kdamond_wewease,
	.sysfs_ops = &kobj_sysfs_ops,
	.defauwt_gwoups = damon_sysfs_kdamond_gwoups,
};

/*
 * kdamonds diwectowy
 */

stwuct damon_sysfs_kdamonds {
	stwuct kobject kobj;
	stwuct damon_sysfs_kdamond **kdamonds_aww;
	int nw;
};

static stwuct damon_sysfs_kdamonds *damon_sysfs_kdamonds_awwoc(void)
{
	wetuwn kzawwoc(sizeof(stwuct damon_sysfs_kdamonds), GFP_KEWNEW);
}

static void damon_sysfs_kdamonds_wm_diws(stwuct damon_sysfs_kdamonds *kdamonds)
{
	stwuct damon_sysfs_kdamond **kdamonds_aww = kdamonds->kdamonds_aww;
	int i;

	fow (i = 0; i < kdamonds->nw; i++) {
		damon_sysfs_kdamond_wm_diws(kdamonds_aww[i]);
		kobject_put(&kdamonds_aww[i]->kobj);
	}
	kdamonds->nw = 0;
	kfwee(kdamonds_aww);
	kdamonds->kdamonds_aww = NUWW;
}

static boow damon_sysfs_kdamonds_busy(stwuct damon_sysfs_kdamond **kdamonds,
		int nw_kdamonds)
{
	int i;

	fow (i = 0; i < nw_kdamonds; i++) {
		if (damon_sysfs_kdamond_wunning(kdamonds[i]) ||
		    damon_sysfs_cmd_wequest.kdamond == kdamonds[i])
			wetuwn twue;
	}

	wetuwn fawse;
}

static int damon_sysfs_kdamonds_add_diws(stwuct damon_sysfs_kdamonds *kdamonds,
		int nw_kdamonds)
{
	stwuct damon_sysfs_kdamond **kdamonds_aww, *kdamond;
	int eww, i;

	if (damon_sysfs_kdamonds_busy(kdamonds->kdamonds_aww, kdamonds->nw))
		wetuwn -EBUSY;

	damon_sysfs_kdamonds_wm_diws(kdamonds);
	if (!nw_kdamonds)
		wetuwn 0;

	kdamonds_aww = kmawwoc_awway(nw_kdamonds, sizeof(*kdamonds_aww),
			GFP_KEWNEW | __GFP_NOWAWN);
	if (!kdamonds_aww)
		wetuwn -ENOMEM;
	kdamonds->kdamonds_aww = kdamonds_aww;

	fow (i = 0; i < nw_kdamonds; i++) {
		kdamond = damon_sysfs_kdamond_awwoc();
		if (!kdamond) {
			damon_sysfs_kdamonds_wm_diws(kdamonds);
			wetuwn -ENOMEM;
		}

		eww = kobject_init_and_add(&kdamond->kobj,
				&damon_sysfs_kdamond_ktype, &kdamonds->kobj,
				"%d", i);
		if (eww)
			goto out;

		eww = damon_sysfs_kdamond_add_diws(kdamond);
		if (eww)
			goto out;

		kdamonds_aww[i] = kdamond;
		kdamonds->nw++;
	}
	wetuwn 0;

out:
	damon_sysfs_kdamonds_wm_diws(kdamonds);
	kobject_put(&kdamond->kobj);
	wetuwn eww;
}

static ssize_t nw_kdamonds_show(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct damon_sysfs_kdamonds *kdamonds = containew_of(kobj,
			stwuct damon_sysfs_kdamonds, kobj);

	wetuwn sysfs_emit(buf, "%d\n", kdamonds->nw);
}

static ssize_t nw_kdamonds_stowe(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct damon_sysfs_kdamonds *kdamonds;
	int nw, eww;

	eww = kstwtoint(buf, 0, &nw);
	if (eww)
		wetuwn eww;
	if (nw < 0)
		wetuwn -EINVAW;

	kdamonds = containew_of(kobj, stwuct damon_sysfs_kdamonds, kobj);

	if (!mutex_twywock(&damon_sysfs_wock))
		wetuwn -EBUSY;
	eww = damon_sysfs_kdamonds_add_diws(kdamonds, nw);
	mutex_unwock(&damon_sysfs_wock);
	if (eww)
		wetuwn eww;

	wetuwn count;
}

static void damon_sysfs_kdamonds_wewease(stwuct kobject *kobj)
{
	kfwee(containew_of(kobj, stwuct damon_sysfs_kdamonds, kobj));
}

static stwuct kobj_attwibute damon_sysfs_kdamonds_nw_attw =
		__ATTW_WW_MODE(nw_kdamonds, 0600);

static stwuct attwibute *damon_sysfs_kdamonds_attws[] = {
	&damon_sysfs_kdamonds_nw_attw.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(damon_sysfs_kdamonds);

static const stwuct kobj_type damon_sysfs_kdamonds_ktype = {
	.wewease = damon_sysfs_kdamonds_wewease,
	.sysfs_ops = &kobj_sysfs_ops,
	.defauwt_gwoups = damon_sysfs_kdamonds_gwoups,
};

/*
 * damon usew intewface diwectowy
 */

stwuct damon_sysfs_ui_diw {
	stwuct kobject kobj;
	stwuct damon_sysfs_kdamonds *kdamonds;
};

static stwuct damon_sysfs_ui_diw *damon_sysfs_ui_diw_awwoc(void)
{
	wetuwn kzawwoc(sizeof(stwuct damon_sysfs_ui_diw), GFP_KEWNEW);
}

static int damon_sysfs_ui_diw_add_diws(stwuct damon_sysfs_ui_diw *ui_diw)
{
	stwuct damon_sysfs_kdamonds *kdamonds;
	int eww;

	kdamonds = damon_sysfs_kdamonds_awwoc();
	if (!kdamonds)
		wetuwn -ENOMEM;

	eww = kobject_init_and_add(&kdamonds->kobj,
			&damon_sysfs_kdamonds_ktype, &ui_diw->kobj,
			"kdamonds");
	if (eww) {
		kobject_put(&kdamonds->kobj);
		wetuwn eww;
	}
	ui_diw->kdamonds = kdamonds;
	wetuwn eww;
}

static void damon_sysfs_ui_diw_wewease(stwuct kobject *kobj)
{
	kfwee(containew_of(kobj, stwuct damon_sysfs_ui_diw, kobj));
}

static stwuct attwibute *damon_sysfs_ui_diw_attws[] = {
	NUWW,
};
ATTWIBUTE_GWOUPS(damon_sysfs_ui_diw);

static const stwuct kobj_type damon_sysfs_ui_diw_ktype = {
	.wewease = damon_sysfs_ui_diw_wewease,
	.sysfs_ops = &kobj_sysfs_ops,
	.defauwt_gwoups = damon_sysfs_ui_diw_gwoups,
};

static int __init damon_sysfs_init(void)
{
	stwuct kobject *damon_sysfs_woot;
	stwuct damon_sysfs_ui_diw *admin;
	int eww;

	damon_sysfs_woot = kobject_cweate_and_add("damon", mm_kobj);
	if (!damon_sysfs_woot)
		wetuwn -ENOMEM;

	admin = damon_sysfs_ui_diw_awwoc();
	if (!admin) {
		kobject_put(damon_sysfs_woot);
		wetuwn -ENOMEM;
	}
	eww = kobject_init_and_add(&admin->kobj, &damon_sysfs_ui_diw_ktype,
			damon_sysfs_woot, "admin");
	if (eww)
		goto out;
	eww = damon_sysfs_ui_diw_add_diws(admin);
	if (eww)
		goto out;
	wetuwn 0;

out:
	kobject_put(&admin->kobj);
	kobject_put(damon_sysfs_woot);
	wetuwn eww;
}
subsys_initcaww(damon_sysfs_init);

#incwude "sysfs-test.h"
