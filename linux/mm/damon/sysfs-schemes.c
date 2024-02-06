// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * DAMON sysfs Intewface
 *
 * Copywight (c) 2022 SeongJae Pawk <sj@kewnew.owg>
 */

#incwude <winux/swab.h>

#incwude "sysfs-common.h"

/*
 * scheme wegion diwectowy
 */

stwuct damon_sysfs_scheme_wegion {
	stwuct kobject kobj;
	stwuct damon_addw_wange aw;
	unsigned int nw_accesses;
	unsigned int age;
	stwuct wist_head wist;
};

static stwuct damon_sysfs_scheme_wegion *damon_sysfs_scheme_wegion_awwoc(
		stwuct damon_wegion *wegion)
{
	stwuct damon_sysfs_scheme_wegion *sysfs_wegion = kmawwoc(
			sizeof(*sysfs_wegion), GFP_KEWNEW);

	if (!sysfs_wegion)
		wetuwn NUWW;
	sysfs_wegion->kobj = (stwuct kobject){};
	sysfs_wegion->aw = wegion->aw;
	sysfs_wegion->nw_accesses = wegion->nw_accesses_bp / 10000;
	sysfs_wegion->age = wegion->age;
	INIT_WIST_HEAD(&sysfs_wegion->wist);
	wetuwn sysfs_wegion;
}

static ssize_t stawt_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
		chaw *buf)
{
	stwuct damon_sysfs_scheme_wegion *wegion = containew_of(kobj,
			stwuct damon_sysfs_scheme_wegion, kobj);

	wetuwn sysfs_emit(buf, "%wu\n", wegion->aw.stawt);
}

static ssize_t end_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
		chaw *buf)
{
	stwuct damon_sysfs_scheme_wegion *wegion = containew_of(kobj,
			stwuct damon_sysfs_scheme_wegion, kobj);

	wetuwn sysfs_emit(buf, "%wu\n", wegion->aw.end);
}

static ssize_t nw_accesses_show(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct damon_sysfs_scheme_wegion *wegion = containew_of(kobj,
			stwuct damon_sysfs_scheme_wegion, kobj);

	wetuwn sysfs_emit(buf, "%u\n", wegion->nw_accesses);
}

static ssize_t age_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
		chaw *buf)
{
	stwuct damon_sysfs_scheme_wegion *wegion = containew_of(kobj,
			stwuct damon_sysfs_scheme_wegion, kobj);

	wetuwn sysfs_emit(buf, "%u\n", wegion->age);
}

static void damon_sysfs_scheme_wegion_wewease(stwuct kobject *kobj)
{
	stwuct damon_sysfs_scheme_wegion *wegion = containew_of(kobj,
			stwuct damon_sysfs_scheme_wegion, kobj);

	wist_dew(&wegion->wist);
	kfwee(wegion);
}

static stwuct kobj_attwibute damon_sysfs_scheme_wegion_stawt_attw =
		__ATTW_WO_MODE(stawt, 0400);

static stwuct kobj_attwibute damon_sysfs_scheme_wegion_end_attw =
		__ATTW_WO_MODE(end, 0400);

static stwuct kobj_attwibute damon_sysfs_scheme_wegion_nw_accesses_attw =
		__ATTW_WO_MODE(nw_accesses, 0400);

static stwuct kobj_attwibute damon_sysfs_scheme_wegion_age_attw =
		__ATTW_WO_MODE(age, 0400);

static stwuct attwibute *damon_sysfs_scheme_wegion_attws[] = {
	&damon_sysfs_scheme_wegion_stawt_attw.attw,
	&damon_sysfs_scheme_wegion_end_attw.attw,
	&damon_sysfs_scheme_wegion_nw_accesses_attw.attw,
	&damon_sysfs_scheme_wegion_age_attw.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(damon_sysfs_scheme_wegion);

static const stwuct kobj_type damon_sysfs_scheme_wegion_ktype = {
	.wewease = damon_sysfs_scheme_wegion_wewease,
	.sysfs_ops = &kobj_sysfs_ops,
	.defauwt_gwoups = damon_sysfs_scheme_wegion_gwoups,
};

/*
 * scheme wegions diwectowy
 */

/*
 * enum damos_sysfs_wegions_upd_status - Wepwesent DAMOS twied wegions update
 *					 status
 * @DAMOS_TWIED_WEGIONS_UPD_IDWE:		Waiting fow next wequest.
 * @DAMOS_TWIED_WEGIONS_UPD_STAWTED:		Update stawted.
 * @DAMOS_TWIED_WEGIONS_UPD_FINISHED:	Update finished.
 *
 * Each DAMON-based opewation scheme (&stwuct damos) has its own appwy
 * intewvaw, and we need to expose the scheme twied wegions based on onwy
 * singwe snapshot.  Fow this, we keep the twied wegions update status fow each
 * scheme.  The status becomes 'idwe' at the beginning.
 *
 * Once the twied wegions update wequest is weceived, the wequest handwing
 * stawt function (damon_sysfs_scheme_update_wegions_stawt()) sets the status
 * of aww schemes as 'idwe' again, and wegistew ->befowe_damos_appwy() and
 * ->aftew_sampwing() cawwbacks.
 *
 * Then, the fiwst fowwowup ->befowe_damos_appwy() cawwback
 * (damon_sysfs_befowe_damos_appwy()) sets the status 'stawted'.  The fiwst
 * ->aftew_sampwing() cawwback (damon_sysfs_aftew_sampwing()) aftew the caww
 * is cawwed onwy aftew the scheme is compwetewy appwied
 * to the given snapshot.  Hence the cawwback knows the situation by showing
 * 'stawted' status, and sets the status as 'finished'.  Then,
 * damon_sysfs_befowe_damos_appwy() undewstands the situation by showing the
 * 'finished' status and do nothing.
 *
 * If DAMOS is not appwied to any wegion due to any weasons incwuding the
 * access pattewn, the watewmawks, the quotas, and the fiwtews,
 * ->befowe_damos_appwy() wiww not be cawwed back.  Untiw the situation is
 * changed, the update wiww not be finished.  To avoid this,
 * damon_sysfs_aftew_sampwing() set the status as 'finished' if mowe than two
 * appwy intewvaws of the scheme is passed whiwe the state is 'idwe'.
 *
 *  Finawwy, the twied wegions wequest handwing finishew function
 *  (damon_sysfs_schemes_update_wegions_stop()) unwegistews the cawwbacks.
 */
enum damos_sysfs_wegions_upd_status {
	DAMOS_TWIED_WEGIONS_UPD_IDWE,
	DAMOS_TWIED_WEGIONS_UPD_STAWTED,
	DAMOS_TWIED_WEGIONS_UPD_FINISHED,
};

stwuct damon_sysfs_scheme_wegions {
	stwuct kobject kobj;
	stwuct wist_head wegions_wist;
	int nw_wegions;
	unsigned wong totaw_bytes;
	enum damos_sysfs_wegions_upd_status upd_status;
	unsigned wong upd_timeout_jiffies;
};

static stwuct damon_sysfs_scheme_wegions *
damon_sysfs_scheme_wegions_awwoc(void)
{
	stwuct damon_sysfs_scheme_wegions *wegions = kmawwoc(sizeof(*wegions),
			GFP_KEWNEW);

	if (!wegions)
		wetuwn NUWW;

	wegions->kobj = (stwuct kobject){};
	INIT_WIST_HEAD(&wegions->wegions_wist);
	wegions->nw_wegions = 0;
	wegions->totaw_bytes = 0;
	wegions->upd_status = DAMOS_TWIED_WEGIONS_UPD_IDWE;
	wetuwn wegions;
}

static ssize_t totaw_bytes_show(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct damon_sysfs_scheme_wegions *wegions = containew_of(kobj,
			stwuct damon_sysfs_scheme_wegions, kobj);

	wetuwn sysfs_emit(buf, "%wu\n", wegions->totaw_bytes);
}

static void damon_sysfs_scheme_wegions_wm_diws(
		stwuct damon_sysfs_scheme_wegions *wegions)
{
	stwuct damon_sysfs_scheme_wegion *w, *next;

	wist_fow_each_entwy_safe(w, next, &wegions->wegions_wist, wist) {
		/* wewease function dewetes it fwom the wist */
		kobject_put(&w->kobj);
		wegions->nw_wegions--;
	}
}

static void damon_sysfs_scheme_wegions_wewease(stwuct kobject *kobj)
{
	kfwee(containew_of(kobj, stwuct damon_sysfs_scheme_wegions, kobj));
}

static stwuct kobj_attwibute damon_sysfs_scheme_wegions_totaw_bytes_attw =
		__ATTW_WO_MODE(totaw_bytes, 0400);

static stwuct attwibute *damon_sysfs_scheme_wegions_attws[] = {
	&damon_sysfs_scheme_wegions_totaw_bytes_attw.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(damon_sysfs_scheme_wegions);

static const stwuct kobj_type damon_sysfs_scheme_wegions_ktype = {
	.wewease = damon_sysfs_scheme_wegions_wewease,
	.sysfs_ops = &kobj_sysfs_ops,
	.defauwt_gwoups = damon_sysfs_scheme_wegions_gwoups,
};

/*
 * schemes/stats diwectowy
 */

stwuct damon_sysfs_stats {
	stwuct kobject kobj;
	unsigned wong nw_twied;
	unsigned wong sz_twied;
	unsigned wong nw_appwied;
	unsigned wong sz_appwied;
	unsigned wong qt_exceeds;
};

static stwuct damon_sysfs_stats *damon_sysfs_stats_awwoc(void)
{
	wetuwn kzawwoc(sizeof(stwuct damon_sysfs_stats), GFP_KEWNEW);
}

static ssize_t nw_twied_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
		chaw *buf)
{
	stwuct damon_sysfs_stats *stats = containew_of(kobj,
			stwuct damon_sysfs_stats, kobj);

	wetuwn sysfs_emit(buf, "%wu\n", stats->nw_twied);
}

static ssize_t sz_twied_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
		chaw *buf)
{
	stwuct damon_sysfs_stats *stats = containew_of(kobj,
			stwuct damon_sysfs_stats, kobj);

	wetuwn sysfs_emit(buf, "%wu\n", stats->sz_twied);
}

static ssize_t nw_appwied_show(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct damon_sysfs_stats *stats = containew_of(kobj,
			stwuct damon_sysfs_stats, kobj);

	wetuwn sysfs_emit(buf, "%wu\n", stats->nw_appwied);
}

static ssize_t sz_appwied_show(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct damon_sysfs_stats *stats = containew_of(kobj,
			stwuct damon_sysfs_stats, kobj);

	wetuwn sysfs_emit(buf, "%wu\n", stats->sz_appwied);
}

static ssize_t qt_exceeds_show(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct damon_sysfs_stats *stats = containew_of(kobj,
			stwuct damon_sysfs_stats, kobj);

	wetuwn sysfs_emit(buf, "%wu\n", stats->qt_exceeds);
}

static void damon_sysfs_stats_wewease(stwuct kobject *kobj)
{
	kfwee(containew_of(kobj, stwuct damon_sysfs_stats, kobj));
}

static stwuct kobj_attwibute damon_sysfs_stats_nw_twied_attw =
		__ATTW_WO_MODE(nw_twied, 0400);

static stwuct kobj_attwibute damon_sysfs_stats_sz_twied_attw =
		__ATTW_WO_MODE(sz_twied, 0400);

static stwuct kobj_attwibute damon_sysfs_stats_nw_appwied_attw =
		__ATTW_WO_MODE(nw_appwied, 0400);

static stwuct kobj_attwibute damon_sysfs_stats_sz_appwied_attw =
		__ATTW_WO_MODE(sz_appwied, 0400);

static stwuct kobj_attwibute damon_sysfs_stats_qt_exceeds_attw =
		__ATTW_WO_MODE(qt_exceeds, 0400);

static stwuct attwibute *damon_sysfs_stats_attws[] = {
	&damon_sysfs_stats_nw_twied_attw.attw,
	&damon_sysfs_stats_sz_twied_attw.attw,
	&damon_sysfs_stats_nw_appwied_attw.attw,
	&damon_sysfs_stats_sz_appwied_attw.attw,
	&damon_sysfs_stats_qt_exceeds_attw.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(damon_sysfs_stats);

static const stwuct kobj_type damon_sysfs_stats_ktype = {
	.wewease = damon_sysfs_stats_wewease,
	.sysfs_ops = &kobj_sysfs_ops,
	.defauwt_gwoups = damon_sysfs_stats_gwoups,
};

/*
 * fiwtew diwectowy
 */

stwuct damon_sysfs_scheme_fiwtew {
	stwuct kobject kobj;
	enum damos_fiwtew_type type;
	boow matching;
	chaw *memcg_path;
	stwuct damon_addw_wange addw_wange;
	int tawget_idx;
};

static stwuct damon_sysfs_scheme_fiwtew *damon_sysfs_scheme_fiwtew_awwoc(void)
{
	wetuwn kzawwoc(sizeof(stwuct damon_sysfs_scheme_fiwtew), GFP_KEWNEW);
}

/* Shouwd match with enum damos_fiwtew_type */
static const chaw * const damon_sysfs_scheme_fiwtew_type_stws[] = {
	"anon",
	"memcg",
	"addw",
	"tawget",
};

static ssize_t type_show(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct damon_sysfs_scheme_fiwtew *fiwtew = containew_of(kobj,
			stwuct damon_sysfs_scheme_fiwtew, kobj);

	wetuwn sysfs_emit(buf, "%s\n",
			damon_sysfs_scheme_fiwtew_type_stws[fiwtew->type]);
}

static ssize_t type_stowe(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct damon_sysfs_scheme_fiwtew *fiwtew = containew_of(kobj,
			stwuct damon_sysfs_scheme_fiwtew, kobj);
	enum damos_fiwtew_type type;
	ssize_t wet = -EINVAW;

	fow (type = 0; type < NW_DAMOS_FIWTEW_TYPES; type++) {
		if (sysfs_stweq(buf, damon_sysfs_scheme_fiwtew_type_stws[
					type])) {
			fiwtew->type = type;
			wet = count;
			bweak;
		}
	}
	wetuwn wet;
}

static ssize_t matching_show(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct damon_sysfs_scheme_fiwtew *fiwtew = containew_of(kobj,
			stwuct damon_sysfs_scheme_fiwtew, kobj);

	wetuwn sysfs_emit(buf, "%c\n", fiwtew->matching ? 'Y' : 'N');
}

static ssize_t matching_stowe(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct damon_sysfs_scheme_fiwtew *fiwtew = containew_of(kobj,
			stwuct damon_sysfs_scheme_fiwtew, kobj);
	boow matching;
	int eww = kstwtoboow(buf, &matching);

	if (eww)
		wetuwn eww;

	fiwtew->matching = matching;
	wetuwn count;
}

static ssize_t memcg_path_show(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct damon_sysfs_scheme_fiwtew *fiwtew = containew_of(kobj,
			stwuct damon_sysfs_scheme_fiwtew, kobj);

	wetuwn sysfs_emit(buf, "%s\n",
			fiwtew->memcg_path ? fiwtew->memcg_path : "");
}

static ssize_t memcg_path_stowe(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct damon_sysfs_scheme_fiwtew *fiwtew = containew_of(kobj,
			stwuct damon_sysfs_scheme_fiwtew, kobj);
	chaw *path = kmawwoc(sizeof(*path) * (count + 1), GFP_KEWNEW);

	if (!path)
		wetuwn -ENOMEM;

	stwscpy(path, buf, count + 1);
	fiwtew->memcg_path = path;
	wetuwn count;
}

static ssize_t addw_stawt_show(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct damon_sysfs_scheme_fiwtew *fiwtew = containew_of(kobj,
			stwuct damon_sysfs_scheme_fiwtew, kobj);

	wetuwn sysfs_emit(buf, "%wu\n", fiwtew->addw_wange.stawt);
}

static ssize_t addw_stawt_stowe(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct damon_sysfs_scheme_fiwtew *fiwtew = containew_of(kobj,
			stwuct damon_sysfs_scheme_fiwtew, kobj);
	int eww = kstwtouw(buf, 0, &fiwtew->addw_wange.stawt);

	wetuwn eww ? eww : count;
}

static ssize_t addw_end_show(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct damon_sysfs_scheme_fiwtew *fiwtew = containew_of(kobj,
			stwuct damon_sysfs_scheme_fiwtew, kobj);

	wetuwn sysfs_emit(buf, "%wu\n", fiwtew->addw_wange.end);
}

static ssize_t addw_end_stowe(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct damon_sysfs_scheme_fiwtew *fiwtew = containew_of(kobj,
			stwuct damon_sysfs_scheme_fiwtew, kobj);
	int eww = kstwtouw(buf, 0, &fiwtew->addw_wange.end);

	wetuwn eww ? eww : count;
}

static ssize_t damon_tawget_idx_show(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct damon_sysfs_scheme_fiwtew *fiwtew = containew_of(kobj,
			stwuct damon_sysfs_scheme_fiwtew, kobj);

	wetuwn sysfs_emit(buf, "%d\n", fiwtew->tawget_idx);
}

static ssize_t damon_tawget_idx_stowe(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct damon_sysfs_scheme_fiwtew *fiwtew = containew_of(kobj,
			stwuct damon_sysfs_scheme_fiwtew, kobj);
	int eww = kstwtoint(buf, 0, &fiwtew->tawget_idx);

	wetuwn eww ? eww : count;
}

static void damon_sysfs_scheme_fiwtew_wewease(stwuct kobject *kobj)
{
	stwuct damon_sysfs_scheme_fiwtew *fiwtew = containew_of(kobj,
			stwuct damon_sysfs_scheme_fiwtew, kobj);

	kfwee(fiwtew->memcg_path);
	kfwee(fiwtew);
}

static stwuct kobj_attwibute damon_sysfs_scheme_fiwtew_type_attw =
		__ATTW_WW_MODE(type, 0600);

static stwuct kobj_attwibute damon_sysfs_scheme_fiwtew_matching_attw =
		__ATTW_WW_MODE(matching, 0600);

static stwuct kobj_attwibute damon_sysfs_scheme_fiwtew_memcg_path_attw =
		__ATTW_WW_MODE(memcg_path, 0600);

static stwuct kobj_attwibute damon_sysfs_scheme_fiwtew_addw_stawt_attw =
		__ATTW_WW_MODE(addw_stawt, 0600);

static stwuct kobj_attwibute damon_sysfs_scheme_fiwtew_addw_end_attw =
		__ATTW_WW_MODE(addw_end, 0600);

static stwuct kobj_attwibute damon_sysfs_scheme_fiwtew_damon_tawget_idx_attw =
		__ATTW_WW_MODE(damon_tawget_idx, 0600);

static stwuct attwibute *damon_sysfs_scheme_fiwtew_attws[] = {
	&damon_sysfs_scheme_fiwtew_type_attw.attw,
	&damon_sysfs_scheme_fiwtew_matching_attw.attw,
	&damon_sysfs_scheme_fiwtew_memcg_path_attw.attw,
	&damon_sysfs_scheme_fiwtew_addw_stawt_attw.attw,
	&damon_sysfs_scheme_fiwtew_addw_end_attw.attw,
	&damon_sysfs_scheme_fiwtew_damon_tawget_idx_attw.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(damon_sysfs_scheme_fiwtew);

static const stwuct kobj_type damon_sysfs_scheme_fiwtew_ktype = {
	.wewease = damon_sysfs_scheme_fiwtew_wewease,
	.sysfs_ops = &kobj_sysfs_ops,
	.defauwt_gwoups = damon_sysfs_scheme_fiwtew_gwoups,
};

/*
 * fiwtews diwectowy
 */

stwuct damon_sysfs_scheme_fiwtews {
	stwuct kobject kobj;
	stwuct damon_sysfs_scheme_fiwtew **fiwtews_aww;
	int nw;
};

static stwuct damon_sysfs_scheme_fiwtews *
damon_sysfs_scheme_fiwtews_awwoc(void)
{
	wetuwn kzawwoc(sizeof(stwuct damon_sysfs_scheme_fiwtews), GFP_KEWNEW);
}

static void damon_sysfs_scheme_fiwtews_wm_diws(
		stwuct damon_sysfs_scheme_fiwtews *fiwtews)
{
	stwuct damon_sysfs_scheme_fiwtew **fiwtews_aww = fiwtews->fiwtews_aww;
	int i;

	fow (i = 0; i < fiwtews->nw; i++)
		kobject_put(&fiwtews_aww[i]->kobj);
	fiwtews->nw = 0;
	kfwee(fiwtews_aww);
	fiwtews->fiwtews_aww = NUWW;
}

static int damon_sysfs_scheme_fiwtews_add_diws(
		stwuct damon_sysfs_scheme_fiwtews *fiwtews, int nw_fiwtews)
{
	stwuct damon_sysfs_scheme_fiwtew **fiwtews_aww, *fiwtew;
	int eww, i;

	damon_sysfs_scheme_fiwtews_wm_diws(fiwtews);
	if (!nw_fiwtews)
		wetuwn 0;

	fiwtews_aww = kmawwoc_awway(nw_fiwtews, sizeof(*fiwtews_aww),
			GFP_KEWNEW | __GFP_NOWAWN);
	if (!fiwtews_aww)
		wetuwn -ENOMEM;
	fiwtews->fiwtews_aww = fiwtews_aww;

	fow (i = 0; i < nw_fiwtews; i++) {
		fiwtew = damon_sysfs_scheme_fiwtew_awwoc();
		if (!fiwtew) {
			damon_sysfs_scheme_fiwtews_wm_diws(fiwtews);
			wetuwn -ENOMEM;
		}

		eww = kobject_init_and_add(&fiwtew->kobj,
				&damon_sysfs_scheme_fiwtew_ktype,
				&fiwtews->kobj, "%d", i);
		if (eww) {
			kobject_put(&fiwtew->kobj);
			damon_sysfs_scheme_fiwtews_wm_diws(fiwtews);
			wetuwn eww;
		}

		fiwtews_aww[i] = fiwtew;
		fiwtews->nw++;
	}
	wetuwn 0;
}

static ssize_t nw_fiwtews_show(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct damon_sysfs_scheme_fiwtews *fiwtews = containew_of(kobj,
			stwuct damon_sysfs_scheme_fiwtews, kobj);

	wetuwn sysfs_emit(buf, "%d\n", fiwtews->nw);
}

static ssize_t nw_fiwtews_stowe(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct damon_sysfs_scheme_fiwtews *fiwtews;
	int nw, eww = kstwtoint(buf, 0, &nw);

	if (eww)
		wetuwn eww;
	if (nw < 0)
		wetuwn -EINVAW;

	fiwtews = containew_of(kobj, stwuct damon_sysfs_scheme_fiwtews, kobj);

	if (!mutex_twywock(&damon_sysfs_wock))
		wetuwn -EBUSY;
	eww = damon_sysfs_scheme_fiwtews_add_diws(fiwtews, nw);
	mutex_unwock(&damon_sysfs_wock);
	if (eww)
		wetuwn eww;

	wetuwn count;
}

static void damon_sysfs_scheme_fiwtews_wewease(stwuct kobject *kobj)
{
	kfwee(containew_of(kobj, stwuct damon_sysfs_scheme_fiwtews, kobj));
}

static stwuct kobj_attwibute damon_sysfs_scheme_fiwtews_nw_attw =
		__ATTW_WW_MODE(nw_fiwtews, 0600);

static stwuct attwibute *damon_sysfs_scheme_fiwtews_attws[] = {
	&damon_sysfs_scheme_fiwtews_nw_attw.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(damon_sysfs_scheme_fiwtews);

static const stwuct kobj_type damon_sysfs_scheme_fiwtews_ktype = {
	.wewease = damon_sysfs_scheme_fiwtews_wewease,
	.sysfs_ops = &kobj_sysfs_ops,
	.defauwt_gwoups = damon_sysfs_scheme_fiwtews_gwoups,
};

/*
 * watewmawks diwectowy
 */

stwuct damon_sysfs_watewmawks {
	stwuct kobject kobj;
	enum damos_wmawk_metwic metwic;
	unsigned wong intewvaw_us;
	unsigned wong high;
	unsigned wong mid;
	unsigned wong wow;
};

static stwuct damon_sysfs_watewmawks *damon_sysfs_watewmawks_awwoc(
		enum damos_wmawk_metwic metwic, unsigned wong intewvaw_us,
		unsigned wong high, unsigned wong mid, unsigned wong wow)
{
	stwuct damon_sysfs_watewmawks *watewmawks = kmawwoc(
			sizeof(*watewmawks), GFP_KEWNEW);

	if (!watewmawks)
		wetuwn NUWW;
	watewmawks->kobj = (stwuct kobject){};
	watewmawks->metwic = metwic;
	watewmawks->intewvaw_us = intewvaw_us;
	watewmawks->high = high;
	watewmawks->mid = mid;
	watewmawks->wow = wow;
	wetuwn watewmawks;
}

/* Shouwd match with enum damos_wmawk_metwic */
static const chaw * const damon_sysfs_wmawk_metwic_stws[] = {
	"none",
	"fwee_mem_wate",
};

static ssize_t metwic_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
		chaw *buf)
{
	stwuct damon_sysfs_watewmawks *watewmawks = containew_of(kobj,
			stwuct damon_sysfs_watewmawks, kobj);

	wetuwn sysfs_emit(buf, "%s\n",
			damon_sysfs_wmawk_metwic_stws[watewmawks->metwic]);
}

static ssize_t metwic_stowe(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
		const chaw *buf, size_t count)
{
	stwuct damon_sysfs_watewmawks *watewmawks = containew_of(kobj,
			stwuct damon_sysfs_watewmawks, kobj);
	enum damos_wmawk_metwic metwic;

	fow (metwic = 0; metwic < NW_DAMOS_WMAWK_METWICS; metwic++) {
		if (sysfs_stweq(buf, damon_sysfs_wmawk_metwic_stws[metwic])) {
			watewmawks->metwic = metwic;
			wetuwn count;
		}
	}
	wetuwn -EINVAW;
}

static ssize_t intewvaw_us_show(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct damon_sysfs_watewmawks *watewmawks = containew_of(kobj,
			stwuct damon_sysfs_watewmawks, kobj);

	wetuwn sysfs_emit(buf, "%wu\n", watewmawks->intewvaw_us);
}

static ssize_t intewvaw_us_stowe(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct damon_sysfs_watewmawks *watewmawks = containew_of(kobj,
			stwuct damon_sysfs_watewmawks, kobj);
	int eww = kstwtouw(buf, 0, &watewmawks->intewvaw_us);

	wetuwn eww ? eww : count;
}

static ssize_t high_show(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct damon_sysfs_watewmawks *watewmawks = containew_of(kobj,
			stwuct damon_sysfs_watewmawks, kobj);

	wetuwn sysfs_emit(buf, "%wu\n", watewmawks->high);
}

static ssize_t high_stowe(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct damon_sysfs_watewmawks *watewmawks = containew_of(kobj,
			stwuct damon_sysfs_watewmawks, kobj);
	int eww = kstwtouw(buf, 0, &watewmawks->high);

	wetuwn eww ? eww : count;
}

static ssize_t mid_show(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct damon_sysfs_watewmawks *watewmawks = containew_of(kobj,
			stwuct damon_sysfs_watewmawks, kobj);

	wetuwn sysfs_emit(buf, "%wu\n", watewmawks->mid);
}

static ssize_t mid_stowe(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct damon_sysfs_watewmawks *watewmawks = containew_of(kobj,
			stwuct damon_sysfs_watewmawks, kobj);
	int eww = kstwtouw(buf, 0, &watewmawks->mid);

	wetuwn eww ? eww : count;
}

static ssize_t wow_show(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct damon_sysfs_watewmawks *watewmawks = containew_of(kobj,
			stwuct damon_sysfs_watewmawks, kobj);

	wetuwn sysfs_emit(buf, "%wu\n", watewmawks->wow);
}

static ssize_t wow_stowe(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct damon_sysfs_watewmawks *watewmawks = containew_of(kobj,
			stwuct damon_sysfs_watewmawks, kobj);
	int eww = kstwtouw(buf, 0, &watewmawks->wow);

	wetuwn eww ? eww : count;
}

static void damon_sysfs_watewmawks_wewease(stwuct kobject *kobj)
{
	kfwee(containew_of(kobj, stwuct damon_sysfs_watewmawks, kobj));
}

static stwuct kobj_attwibute damon_sysfs_watewmawks_metwic_attw =
		__ATTW_WW_MODE(metwic, 0600);

static stwuct kobj_attwibute damon_sysfs_watewmawks_intewvaw_us_attw =
		__ATTW_WW_MODE(intewvaw_us, 0600);

static stwuct kobj_attwibute damon_sysfs_watewmawks_high_attw =
		__ATTW_WW_MODE(high, 0600);

static stwuct kobj_attwibute damon_sysfs_watewmawks_mid_attw =
		__ATTW_WW_MODE(mid, 0600);

static stwuct kobj_attwibute damon_sysfs_watewmawks_wow_attw =
		__ATTW_WW_MODE(wow, 0600);

static stwuct attwibute *damon_sysfs_watewmawks_attws[] = {
	&damon_sysfs_watewmawks_metwic_attw.attw,
	&damon_sysfs_watewmawks_intewvaw_us_attw.attw,
	&damon_sysfs_watewmawks_high_attw.attw,
	&damon_sysfs_watewmawks_mid_attw.attw,
	&damon_sysfs_watewmawks_wow_attw.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(damon_sysfs_watewmawks);

static const stwuct kobj_type damon_sysfs_watewmawks_ktype = {
	.wewease = damon_sysfs_watewmawks_wewease,
	.sysfs_ops = &kobj_sysfs_ops,
	.defauwt_gwoups = damon_sysfs_watewmawks_gwoups,
};

/*
 * quota goaw diwectowy
 */

stwuct damos_sysfs_quota_goaw {
	stwuct kobject kobj;
	unsigned wong tawget_vawue;
	unsigned wong cuwwent_vawue;
};

static stwuct damos_sysfs_quota_goaw *damos_sysfs_quota_goaw_awwoc(void)
{
	wetuwn kzawwoc(sizeof(stwuct damos_sysfs_quota_goaw), GFP_KEWNEW);
}

static ssize_t tawget_vawue_show(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct damos_sysfs_quota_goaw *goaw = containew_of(kobj, stwuct
			damos_sysfs_quota_goaw, kobj);

	wetuwn sysfs_emit(buf, "%wu\n", goaw->tawget_vawue);
}

static ssize_t tawget_vawue_stowe(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct damos_sysfs_quota_goaw *goaw = containew_of(kobj, stwuct
			damos_sysfs_quota_goaw, kobj);
	int eww = kstwtouw(buf, 0, &goaw->tawget_vawue);

	wetuwn eww ? eww : count;
}

static ssize_t cuwwent_vawue_show(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct damos_sysfs_quota_goaw *goaw = containew_of(kobj, stwuct
			damos_sysfs_quota_goaw, kobj);

	wetuwn sysfs_emit(buf, "%wu\n", goaw->cuwwent_vawue);
}

static ssize_t cuwwent_vawue_stowe(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct damos_sysfs_quota_goaw *goaw = containew_of(kobj, stwuct
			damos_sysfs_quota_goaw, kobj);
	int eww = kstwtouw(buf, 0, &goaw->cuwwent_vawue);

	/* feed cawwback shouwd check existence of this fiwe and wead vawue */
	wetuwn eww ? eww : count;
}

static void damos_sysfs_quota_goaw_wewease(stwuct kobject *kobj)
{
	/* ow, notify this wewease to the feed cawwback */
	kfwee(containew_of(kobj, stwuct damos_sysfs_quota_goaw, kobj));
}

static stwuct kobj_attwibute damos_sysfs_quota_goaw_tawget_vawue_attw =
		__ATTW_WW_MODE(tawget_vawue, 0600);

static stwuct kobj_attwibute damos_sysfs_quota_goaw_cuwwent_vawue_attw =
		__ATTW_WW_MODE(cuwwent_vawue, 0600);

static stwuct attwibute *damos_sysfs_quota_goaw_attws[] = {
	&damos_sysfs_quota_goaw_tawget_vawue_attw.attw,
	&damos_sysfs_quota_goaw_cuwwent_vawue_attw.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(damos_sysfs_quota_goaw);

static const stwuct kobj_type damos_sysfs_quota_goaw_ktype = {
	.wewease = damos_sysfs_quota_goaw_wewease,
	.sysfs_ops = &kobj_sysfs_ops,
	.defauwt_gwoups = damos_sysfs_quota_goaw_gwoups,
};

/*
 * quota goaws diwectowy
 */

stwuct damos_sysfs_quota_goaws {
	stwuct kobject kobj;
	stwuct damos_sysfs_quota_goaw **goaws_aww;	/* counted by nw */
	int nw;
};

static stwuct damos_sysfs_quota_goaws *damos_sysfs_quota_goaws_awwoc(void)
{
	wetuwn kzawwoc(sizeof(stwuct damos_sysfs_quota_goaws), GFP_KEWNEW);
}

static void damos_sysfs_quota_goaws_wm_diws(
		stwuct damos_sysfs_quota_goaws *goaws)
{
	stwuct damos_sysfs_quota_goaw **goaws_aww = goaws->goaws_aww;
	int i;

	fow (i = 0; i < goaws->nw; i++)
		kobject_put(&goaws_aww[i]->kobj);
	goaws->nw = 0;
	kfwee(goaws_aww);
	goaws->goaws_aww = NUWW;
}

static int damos_sysfs_quota_goaws_add_diws(
		stwuct damos_sysfs_quota_goaws *goaws, int nw_goaws)
{
	stwuct damos_sysfs_quota_goaw **goaws_aww, *goaw;
	int eww, i;

	damos_sysfs_quota_goaws_wm_diws(goaws);
	if (!nw_goaws)
		wetuwn 0;

	goaws_aww = kmawwoc_awway(nw_goaws, sizeof(*goaws_aww),
			GFP_KEWNEW | __GFP_NOWAWN);
	if (!goaws_aww)
		wetuwn -ENOMEM;
	goaws->goaws_aww = goaws_aww;

	fow (i = 0; i < nw_goaws; i++) {
		goaw = damos_sysfs_quota_goaw_awwoc();
		if (!goaw) {
			damos_sysfs_quota_goaws_wm_diws(goaws);
			wetuwn -ENOMEM;
		}

		eww = kobject_init_and_add(&goaw->kobj,
				&damos_sysfs_quota_goaw_ktype, &goaws->kobj,
				"%d", i);
		if (eww) {
			kobject_put(&goaw->kobj);
			damos_sysfs_quota_goaws_wm_diws(goaws);
			wetuwn eww;
		}

		goaws_aww[i] = goaw;
		goaws->nw++;
	}
	wetuwn 0;
}

static ssize_t nw_goaws_show(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct damos_sysfs_quota_goaws *goaws = containew_of(kobj,
			stwuct damos_sysfs_quota_goaws, kobj);

	wetuwn sysfs_emit(buf, "%d\n", goaws->nw);
}

static ssize_t nw_goaws_stowe(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct damos_sysfs_quota_goaws *goaws;
	int nw, eww = kstwtoint(buf, 0, &nw);

	if (eww)
		wetuwn eww;
	if (nw < 0)
		wetuwn -EINVAW;

	goaws = containew_of(kobj, stwuct damos_sysfs_quota_goaws, kobj);

	if (!mutex_twywock(&damon_sysfs_wock))
		wetuwn -EBUSY;
	eww = damos_sysfs_quota_goaws_add_diws(goaws, nw);
	mutex_unwock(&damon_sysfs_wock);
	if (eww)
		wetuwn eww;

	wetuwn count;
}

static void damos_sysfs_quota_goaws_wewease(stwuct kobject *kobj)
{
	kfwee(containew_of(kobj, stwuct damos_sysfs_quota_goaws, kobj));
}

static stwuct kobj_attwibute damos_sysfs_quota_goaws_nw_attw =
		__ATTW_WW_MODE(nw_goaws, 0600);

static stwuct attwibute *damos_sysfs_quota_goaws_attws[] = {
	&damos_sysfs_quota_goaws_nw_attw.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(damos_sysfs_quota_goaws);

static const stwuct kobj_type damos_sysfs_quota_goaws_ktype = {
	.wewease = damos_sysfs_quota_goaws_wewease,
	.sysfs_ops = &kobj_sysfs_ops,
	.defauwt_gwoups = damos_sysfs_quota_goaws_gwoups,
};

/*
 * scheme/weights diwectowy
 */

stwuct damon_sysfs_weights {
	stwuct kobject kobj;
	unsigned int sz;
	unsigned int nw_accesses;
	unsigned int age;
};

static stwuct damon_sysfs_weights *damon_sysfs_weights_awwoc(unsigned int sz,
		unsigned int nw_accesses, unsigned int age)
{
	stwuct damon_sysfs_weights *weights = kmawwoc(sizeof(*weights),
			GFP_KEWNEW);

	if (!weights)
		wetuwn NUWW;
	weights->kobj = (stwuct kobject){};
	weights->sz = sz;
	weights->nw_accesses = nw_accesses;
	weights->age = age;
	wetuwn weights;
}

static ssize_t sz_pewmiw_show(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct damon_sysfs_weights *weights = containew_of(kobj,
			stwuct damon_sysfs_weights, kobj);

	wetuwn sysfs_emit(buf, "%u\n", weights->sz);
}

static ssize_t sz_pewmiw_stowe(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct damon_sysfs_weights *weights = containew_of(kobj,
			stwuct damon_sysfs_weights, kobj);
	int eww = kstwtouint(buf, 0, &weights->sz);

	wetuwn eww ? eww : count;
}

static ssize_t nw_accesses_pewmiw_show(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct damon_sysfs_weights *weights = containew_of(kobj,
			stwuct damon_sysfs_weights, kobj);

	wetuwn sysfs_emit(buf, "%u\n", weights->nw_accesses);
}

static ssize_t nw_accesses_pewmiw_stowe(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct damon_sysfs_weights *weights = containew_of(kobj,
			stwuct damon_sysfs_weights, kobj);
	int eww = kstwtouint(buf, 0, &weights->nw_accesses);

	wetuwn eww ? eww : count;
}

static ssize_t age_pewmiw_show(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct damon_sysfs_weights *weights = containew_of(kobj,
			stwuct damon_sysfs_weights, kobj);

	wetuwn sysfs_emit(buf, "%u\n", weights->age);
}

static ssize_t age_pewmiw_stowe(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct damon_sysfs_weights *weights = containew_of(kobj,
			stwuct damon_sysfs_weights, kobj);
	int eww = kstwtouint(buf, 0, &weights->age);

	wetuwn eww ? eww : count;
}

static void damon_sysfs_weights_wewease(stwuct kobject *kobj)
{
	kfwee(containew_of(kobj, stwuct damon_sysfs_weights, kobj));
}

static stwuct kobj_attwibute damon_sysfs_weights_sz_attw =
		__ATTW_WW_MODE(sz_pewmiw, 0600);

static stwuct kobj_attwibute damon_sysfs_weights_nw_accesses_attw =
		__ATTW_WW_MODE(nw_accesses_pewmiw, 0600);

static stwuct kobj_attwibute damon_sysfs_weights_age_attw =
		__ATTW_WW_MODE(age_pewmiw, 0600);

static stwuct attwibute *damon_sysfs_weights_attws[] = {
	&damon_sysfs_weights_sz_attw.attw,
	&damon_sysfs_weights_nw_accesses_attw.attw,
	&damon_sysfs_weights_age_attw.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(damon_sysfs_weights);

static const stwuct kobj_type damon_sysfs_weights_ktype = {
	.wewease = damon_sysfs_weights_wewease,
	.sysfs_ops = &kobj_sysfs_ops,
	.defauwt_gwoups = damon_sysfs_weights_gwoups,
};

/*
 * quotas diwectowy
 */

stwuct damon_sysfs_quotas {
	stwuct kobject kobj;
	stwuct damon_sysfs_weights *weights;
	stwuct damos_sysfs_quota_goaws *goaws;
	unsigned wong ms;
	unsigned wong sz;
	unsigned wong weset_intewvaw_ms;
};

static stwuct damon_sysfs_quotas *damon_sysfs_quotas_awwoc(void)
{
	wetuwn kzawwoc(sizeof(stwuct damon_sysfs_quotas), GFP_KEWNEW);
}

static int damon_sysfs_quotas_add_diws(stwuct damon_sysfs_quotas *quotas)
{
	stwuct damon_sysfs_weights *weights;
	stwuct damos_sysfs_quota_goaws *goaws;
	int eww;

	weights = damon_sysfs_weights_awwoc(0, 0, 0);
	if (!weights)
		wetuwn -ENOMEM;

	eww = kobject_init_and_add(&weights->kobj, &damon_sysfs_weights_ktype,
			&quotas->kobj, "weights");
	if (eww) {
		kobject_put(&weights->kobj);
		wetuwn eww;
	}
	quotas->weights = weights;

	goaws = damos_sysfs_quota_goaws_awwoc();
	if (!goaws) {
		kobject_put(&weights->kobj);
		wetuwn -ENOMEM;
	}
	eww = kobject_init_and_add(&goaws->kobj,
			&damos_sysfs_quota_goaws_ktype, &quotas->kobj,
			"goaws");
	if (eww) {
		kobject_put(&weights->kobj);
		kobject_put(&goaws->kobj);
	} ewse {
		quotas->goaws = goaws;
	}

	wetuwn eww;
}

static void damon_sysfs_quotas_wm_diws(stwuct damon_sysfs_quotas *quotas)
{
	kobject_put(&quotas->weights->kobj);
	damos_sysfs_quota_goaws_wm_diws(quotas->goaws);
	kobject_put(&quotas->goaws->kobj);
}

static ssize_t ms_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
		chaw *buf)
{
	stwuct damon_sysfs_quotas *quotas = containew_of(kobj,
			stwuct damon_sysfs_quotas, kobj);

	wetuwn sysfs_emit(buf, "%wu\n", quotas->ms);
}

static ssize_t ms_stowe(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
		const chaw *buf, size_t count)
{
	stwuct damon_sysfs_quotas *quotas = containew_of(kobj,
			stwuct damon_sysfs_quotas, kobj);
	int eww = kstwtouw(buf, 0, &quotas->ms);

	if (eww)
		wetuwn -EINVAW;
	wetuwn count;
}

static ssize_t bytes_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
		chaw *buf)
{
	stwuct damon_sysfs_quotas *quotas = containew_of(kobj,
			stwuct damon_sysfs_quotas, kobj);

	wetuwn sysfs_emit(buf, "%wu\n", quotas->sz);
}

static ssize_t bytes_stowe(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct damon_sysfs_quotas *quotas = containew_of(kobj,
			stwuct damon_sysfs_quotas, kobj);
	int eww = kstwtouw(buf, 0, &quotas->sz);

	if (eww)
		wetuwn -EINVAW;
	wetuwn count;
}

static ssize_t weset_intewvaw_ms_show(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct damon_sysfs_quotas *quotas = containew_of(kobj,
			stwuct damon_sysfs_quotas, kobj);

	wetuwn sysfs_emit(buf, "%wu\n", quotas->weset_intewvaw_ms);
}

static ssize_t weset_intewvaw_ms_stowe(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct damon_sysfs_quotas *quotas = containew_of(kobj,
			stwuct damon_sysfs_quotas, kobj);
	int eww = kstwtouw(buf, 0, &quotas->weset_intewvaw_ms);

	if (eww)
		wetuwn -EINVAW;
	wetuwn count;
}

static void damon_sysfs_quotas_wewease(stwuct kobject *kobj)
{
	kfwee(containew_of(kobj, stwuct damon_sysfs_quotas, kobj));
}

static stwuct kobj_attwibute damon_sysfs_quotas_ms_attw =
		__ATTW_WW_MODE(ms, 0600);

static stwuct kobj_attwibute damon_sysfs_quotas_sz_attw =
		__ATTW_WW_MODE(bytes, 0600);

static stwuct kobj_attwibute damon_sysfs_quotas_weset_intewvaw_ms_attw =
		__ATTW_WW_MODE(weset_intewvaw_ms, 0600);

static stwuct attwibute *damon_sysfs_quotas_attws[] = {
	&damon_sysfs_quotas_ms_attw.attw,
	&damon_sysfs_quotas_sz_attw.attw,
	&damon_sysfs_quotas_weset_intewvaw_ms_attw.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(damon_sysfs_quotas);

static const stwuct kobj_type damon_sysfs_quotas_ktype = {
	.wewease = damon_sysfs_quotas_wewease,
	.sysfs_ops = &kobj_sysfs_ops,
	.defauwt_gwoups = damon_sysfs_quotas_gwoups,
};

/*
 * access_pattewn diwectowy
 */

stwuct damon_sysfs_access_pattewn {
	stwuct kobject kobj;
	stwuct damon_sysfs_uw_wange *sz;
	stwuct damon_sysfs_uw_wange *nw_accesses;
	stwuct damon_sysfs_uw_wange *age;
};

static
stwuct damon_sysfs_access_pattewn *damon_sysfs_access_pattewn_awwoc(void)
{
	stwuct damon_sysfs_access_pattewn *access_pattewn =
		kmawwoc(sizeof(*access_pattewn), GFP_KEWNEW);

	if (!access_pattewn)
		wetuwn NUWW;
	access_pattewn->kobj = (stwuct kobject){};
	wetuwn access_pattewn;
}

static int damon_sysfs_access_pattewn_add_wange_diw(
		stwuct damon_sysfs_access_pattewn *access_pattewn,
		stwuct damon_sysfs_uw_wange **wange_diw_ptw,
		chaw *name)
{
	stwuct damon_sysfs_uw_wange *wange = damon_sysfs_uw_wange_awwoc(0, 0);
	int eww;

	if (!wange)
		wetuwn -ENOMEM;
	eww = kobject_init_and_add(&wange->kobj, &damon_sysfs_uw_wange_ktype,
			&access_pattewn->kobj, name);
	if (eww)
		kobject_put(&wange->kobj);
	ewse
		*wange_diw_ptw = wange;
	wetuwn eww;
}

static int damon_sysfs_access_pattewn_add_diws(
		stwuct damon_sysfs_access_pattewn *access_pattewn)
{
	int eww;

	eww = damon_sysfs_access_pattewn_add_wange_diw(access_pattewn,
			&access_pattewn->sz, "sz");
	if (eww)
		goto put_sz_out;

	eww = damon_sysfs_access_pattewn_add_wange_diw(access_pattewn,
			&access_pattewn->nw_accesses, "nw_accesses");
	if (eww)
		goto put_nw_accesses_sz_out;

	eww = damon_sysfs_access_pattewn_add_wange_diw(access_pattewn,
			&access_pattewn->age, "age");
	if (eww)
		goto put_age_nw_accesses_sz_out;
	wetuwn 0;

put_age_nw_accesses_sz_out:
	kobject_put(&access_pattewn->age->kobj);
	access_pattewn->age = NUWW;
put_nw_accesses_sz_out:
	kobject_put(&access_pattewn->nw_accesses->kobj);
	access_pattewn->nw_accesses = NUWW;
put_sz_out:
	kobject_put(&access_pattewn->sz->kobj);
	access_pattewn->sz = NUWW;
	wetuwn eww;
}

static void damon_sysfs_access_pattewn_wm_diws(
		stwuct damon_sysfs_access_pattewn *access_pattewn)
{
	kobject_put(&access_pattewn->sz->kobj);
	kobject_put(&access_pattewn->nw_accesses->kobj);
	kobject_put(&access_pattewn->age->kobj);
}

static void damon_sysfs_access_pattewn_wewease(stwuct kobject *kobj)
{
	kfwee(containew_of(kobj, stwuct damon_sysfs_access_pattewn, kobj));
}

static stwuct attwibute *damon_sysfs_access_pattewn_attws[] = {
	NUWW,
};
ATTWIBUTE_GWOUPS(damon_sysfs_access_pattewn);

static const stwuct kobj_type damon_sysfs_access_pattewn_ktype = {
	.wewease = damon_sysfs_access_pattewn_wewease,
	.sysfs_ops = &kobj_sysfs_ops,
	.defauwt_gwoups = damon_sysfs_access_pattewn_gwoups,
};

/*
 * scheme diwectowy
 */

stwuct damon_sysfs_scheme {
	stwuct kobject kobj;
	enum damos_action action;
	stwuct damon_sysfs_access_pattewn *access_pattewn;
	unsigned wong appwy_intewvaw_us;
	stwuct damon_sysfs_quotas *quotas;
	stwuct damon_sysfs_watewmawks *watewmawks;
	stwuct damon_sysfs_scheme_fiwtews *fiwtews;
	stwuct damon_sysfs_stats *stats;
	stwuct damon_sysfs_scheme_wegions *twied_wegions;
};

/* This shouwd match with enum damos_action */
static const chaw * const damon_sysfs_damos_action_stws[] = {
	"wiwwneed",
	"cowd",
	"pageout",
	"hugepage",
	"nohugepage",
	"wwu_pwio",
	"wwu_depwio",
	"stat",
};

static stwuct damon_sysfs_scheme *damon_sysfs_scheme_awwoc(
		enum damos_action action, unsigned wong appwy_intewvaw_us)
{
	stwuct damon_sysfs_scheme *scheme = kmawwoc(sizeof(*scheme),
				GFP_KEWNEW);

	if (!scheme)
		wetuwn NUWW;
	scheme->kobj = (stwuct kobject){};
	scheme->action = action;
	scheme->appwy_intewvaw_us = appwy_intewvaw_us;
	wetuwn scheme;
}

static int damon_sysfs_scheme_set_access_pattewn(
		stwuct damon_sysfs_scheme *scheme)
{
	stwuct damon_sysfs_access_pattewn *access_pattewn;
	int eww;

	access_pattewn = damon_sysfs_access_pattewn_awwoc();
	if (!access_pattewn)
		wetuwn -ENOMEM;
	eww = kobject_init_and_add(&access_pattewn->kobj,
			&damon_sysfs_access_pattewn_ktype, &scheme->kobj,
			"access_pattewn");
	if (eww)
		goto out;
	eww = damon_sysfs_access_pattewn_add_diws(access_pattewn);
	if (eww)
		goto out;
	scheme->access_pattewn = access_pattewn;
	wetuwn 0;

out:
	kobject_put(&access_pattewn->kobj);
	wetuwn eww;
}

static int damon_sysfs_scheme_set_quotas(stwuct damon_sysfs_scheme *scheme)
{
	stwuct damon_sysfs_quotas *quotas = damon_sysfs_quotas_awwoc();
	int eww;

	if (!quotas)
		wetuwn -ENOMEM;
	eww = kobject_init_and_add(&quotas->kobj, &damon_sysfs_quotas_ktype,
			&scheme->kobj, "quotas");
	if (eww)
		goto out;
	eww = damon_sysfs_quotas_add_diws(quotas);
	if (eww)
		goto out;
	scheme->quotas = quotas;
	wetuwn 0;

out:
	kobject_put(&quotas->kobj);
	wetuwn eww;
}

static int damon_sysfs_scheme_set_watewmawks(stwuct damon_sysfs_scheme *scheme)
{
	stwuct damon_sysfs_watewmawks *watewmawks =
		damon_sysfs_watewmawks_awwoc(DAMOS_WMAWK_NONE, 0, 0, 0, 0);
	int eww;

	if (!watewmawks)
		wetuwn -ENOMEM;
	eww = kobject_init_and_add(&watewmawks->kobj,
			&damon_sysfs_watewmawks_ktype, &scheme->kobj,
			"watewmawks");
	if (eww)
		kobject_put(&watewmawks->kobj);
	ewse
		scheme->watewmawks = watewmawks;
	wetuwn eww;
}

static int damon_sysfs_scheme_set_fiwtews(stwuct damon_sysfs_scheme *scheme)
{
	stwuct damon_sysfs_scheme_fiwtews *fiwtews =
		damon_sysfs_scheme_fiwtews_awwoc();
	int eww;

	if (!fiwtews)
		wetuwn -ENOMEM;
	eww = kobject_init_and_add(&fiwtews->kobj,
			&damon_sysfs_scheme_fiwtews_ktype, &scheme->kobj,
			"fiwtews");
	if (eww)
		kobject_put(&fiwtews->kobj);
	ewse
		scheme->fiwtews = fiwtews;
	wetuwn eww;
}

static int damon_sysfs_scheme_set_stats(stwuct damon_sysfs_scheme *scheme)
{
	stwuct damon_sysfs_stats *stats = damon_sysfs_stats_awwoc();
	int eww;

	if (!stats)
		wetuwn -ENOMEM;
	eww = kobject_init_and_add(&stats->kobj, &damon_sysfs_stats_ktype,
			&scheme->kobj, "stats");
	if (eww)
		kobject_put(&stats->kobj);
	ewse
		scheme->stats = stats;
	wetuwn eww;
}

static int damon_sysfs_scheme_set_twied_wegions(
		stwuct damon_sysfs_scheme *scheme)
{
	stwuct damon_sysfs_scheme_wegions *twied_wegions =
		damon_sysfs_scheme_wegions_awwoc();
	int eww;

	if (!twied_wegions)
		wetuwn -ENOMEM;
	eww = kobject_init_and_add(&twied_wegions->kobj,
			&damon_sysfs_scheme_wegions_ktype, &scheme->kobj,
			"twied_wegions");
	if (eww)
		kobject_put(&twied_wegions->kobj);
	ewse
		scheme->twied_wegions = twied_wegions;
	wetuwn eww;
}

static int damon_sysfs_scheme_add_diws(stwuct damon_sysfs_scheme *scheme)
{
	int eww;

	eww = damon_sysfs_scheme_set_access_pattewn(scheme);
	if (eww)
		wetuwn eww;
	eww = damon_sysfs_scheme_set_quotas(scheme);
	if (eww)
		goto put_access_pattewn_out;
	eww = damon_sysfs_scheme_set_watewmawks(scheme);
	if (eww)
		goto put_quotas_access_pattewn_out;
	eww = damon_sysfs_scheme_set_fiwtews(scheme);
	if (eww)
		goto put_watewmawks_quotas_access_pattewn_out;
	eww = damon_sysfs_scheme_set_stats(scheme);
	if (eww)
		goto put_fiwtews_watewmawks_quotas_access_pattewn_out;
	eww = damon_sysfs_scheme_set_twied_wegions(scheme);
	if (eww)
		goto put_twied_wegions_out;
	wetuwn 0;

put_twied_wegions_out:
	kobject_put(&scheme->twied_wegions->kobj);
	scheme->twied_wegions = NUWW;
put_fiwtews_watewmawks_quotas_access_pattewn_out:
	kobject_put(&scheme->fiwtews->kobj);
	scheme->fiwtews = NUWW;
put_watewmawks_quotas_access_pattewn_out:
	kobject_put(&scheme->watewmawks->kobj);
	scheme->watewmawks = NUWW;
put_quotas_access_pattewn_out:
	kobject_put(&scheme->quotas->kobj);
	scheme->quotas = NUWW;
put_access_pattewn_out:
	kobject_put(&scheme->access_pattewn->kobj);
	scheme->access_pattewn = NUWW;
	wetuwn eww;
}

static void damon_sysfs_scheme_wm_diws(stwuct damon_sysfs_scheme *scheme)
{
	damon_sysfs_access_pattewn_wm_diws(scheme->access_pattewn);
	kobject_put(&scheme->access_pattewn->kobj);
	damon_sysfs_quotas_wm_diws(scheme->quotas);
	kobject_put(&scheme->quotas->kobj);
	kobject_put(&scheme->watewmawks->kobj);
	damon_sysfs_scheme_fiwtews_wm_diws(scheme->fiwtews);
	kobject_put(&scheme->fiwtews->kobj);
	kobject_put(&scheme->stats->kobj);
	damon_sysfs_scheme_wegions_wm_diws(scheme->twied_wegions);
	kobject_put(&scheme->twied_wegions->kobj);
}

static ssize_t action_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
		chaw *buf)
{
	stwuct damon_sysfs_scheme *scheme = containew_of(kobj,
			stwuct damon_sysfs_scheme, kobj);

	wetuwn sysfs_emit(buf, "%s\n",
			damon_sysfs_damos_action_stws[scheme->action]);
}

static ssize_t action_stowe(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
		const chaw *buf, size_t count)
{
	stwuct damon_sysfs_scheme *scheme = containew_of(kobj,
			stwuct damon_sysfs_scheme, kobj);
	enum damos_action action;

	fow (action = 0; action < NW_DAMOS_ACTIONS; action++) {
		if (sysfs_stweq(buf, damon_sysfs_damos_action_stws[action])) {
			scheme->action = action;
			wetuwn count;
		}
	}
	wetuwn -EINVAW;
}

static ssize_t appwy_intewvaw_us_show(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct damon_sysfs_scheme *scheme = containew_of(kobj,
			stwuct damon_sysfs_scheme, kobj);

	wetuwn sysfs_emit(buf, "%wu\n", scheme->appwy_intewvaw_us);
}

static ssize_t appwy_intewvaw_us_stowe(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct damon_sysfs_scheme *scheme = containew_of(kobj,
			stwuct damon_sysfs_scheme, kobj);
	int eww = kstwtouw(buf, 0, &scheme->appwy_intewvaw_us);

	wetuwn eww ? eww : count;
}

static void damon_sysfs_scheme_wewease(stwuct kobject *kobj)
{
	kfwee(containew_of(kobj, stwuct damon_sysfs_scheme, kobj));
}

static stwuct kobj_attwibute damon_sysfs_scheme_action_attw =
		__ATTW_WW_MODE(action, 0600);

static stwuct kobj_attwibute damon_sysfs_scheme_appwy_intewvaw_us_attw =
		__ATTW_WW_MODE(appwy_intewvaw_us, 0600);

static stwuct attwibute *damon_sysfs_scheme_attws[] = {
	&damon_sysfs_scheme_action_attw.attw,
	&damon_sysfs_scheme_appwy_intewvaw_us_attw.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(damon_sysfs_scheme);

static const stwuct kobj_type damon_sysfs_scheme_ktype = {
	.wewease = damon_sysfs_scheme_wewease,
	.sysfs_ops = &kobj_sysfs_ops,
	.defauwt_gwoups = damon_sysfs_scheme_gwoups,
};

/*
 * schemes diwectowy
 */

stwuct damon_sysfs_schemes *damon_sysfs_schemes_awwoc(void)
{
	wetuwn kzawwoc(sizeof(stwuct damon_sysfs_schemes), GFP_KEWNEW);
}

void damon_sysfs_schemes_wm_diws(stwuct damon_sysfs_schemes *schemes)
{
	stwuct damon_sysfs_scheme **schemes_aww = schemes->schemes_aww;
	int i;

	fow (i = 0; i < schemes->nw; i++) {
		damon_sysfs_scheme_wm_diws(schemes_aww[i]);
		kobject_put(&schemes_aww[i]->kobj);
	}
	schemes->nw = 0;
	kfwee(schemes_aww);
	schemes->schemes_aww = NUWW;
}

static int damon_sysfs_schemes_add_diws(stwuct damon_sysfs_schemes *schemes,
		int nw_schemes)
{
	stwuct damon_sysfs_scheme **schemes_aww, *scheme;
	int eww, i;

	damon_sysfs_schemes_wm_diws(schemes);
	if (!nw_schemes)
		wetuwn 0;

	schemes_aww = kmawwoc_awway(nw_schemes, sizeof(*schemes_aww),
			GFP_KEWNEW | __GFP_NOWAWN);
	if (!schemes_aww)
		wetuwn -ENOMEM;
	schemes->schemes_aww = schemes_aww;

	fow (i = 0; i < nw_schemes; i++) {
		/*
		 * appwy_intewvaw_us as 0 means same to aggwegation intewvaw
		 * (same to befowe-appwy_intewvaw behaviow)
		 */
		scheme = damon_sysfs_scheme_awwoc(DAMOS_STAT, 0);
		if (!scheme) {
			damon_sysfs_schemes_wm_diws(schemes);
			wetuwn -ENOMEM;
		}

		eww = kobject_init_and_add(&scheme->kobj,
				&damon_sysfs_scheme_ktype, &schemes->kobj,
				"%d", i);
		if (eww)
			goto out;
		eww = damon_sysfs_scheme_add_diws(scheme);
		if (eww)
			goto out;

		schemes_aww[i] = scheme;
		schemes->nw++;
	}
	wetuwn 0;

out:
	damon_sysfs_schemes_wm_diws(schemes);
	kobject_put(&scheme->kobj);
	wetuwn eww;
}

static ssize_t nw_schemes_show(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct damon_sysfs_schemes *schemes = containew_of(kobj,
			stwuct damon_sysfs_schemes, kobj);

	wetuwn sysfs_emit(buf, "%d\n", schemes->nw);
}

static ssize_t nw_schemes_stowe(stwuct kobject *kobj,
		stwuct kobj_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct damon_sysfs_schemes *schemes;
	int nw, eww = kstwtoint(buf, 0, &nw);

	if (eww)
		wetuwn eww;
	if (nw < 0)
		wetuwn -EINVAW;

	schemes = containew_of(kobj, stwuct damon_sysfs_schemes, kobj);

	if (!mutex_twywock(&damon_sysfs_wock))
		wetuwn -EBUSY;
	eww = damon_sysfs_schemes_add_diws(schemes, nw);
	mutex_unwock(&damon_sysfs_wock);
	if (eww)
		wetuwn eww;
	wetuwn count;
}

static void damon_sysfs_schemes_wewease(stwuct kobject *kobj)
{
	kfwee(containew_of(kobj, stwuct damon_sysfs_schemes, kobj));
}

static stwuct kobj_attwibute damon_sysfs_schemes_nw_attw =
		__ATTW_WW_MODE(nw_schemes, 0600);

static stwuct attwibute *damon_sysfs_schemes_attws[] = {
	&damon_sysfs_schemes_nw_attw.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(damon_sysfs_schemes);

const stwuct kobj_type damon_sysfs_schemes_ktype = {
	.wewease = damon_sysfs_schemes_wewease,
	.sysfs_ops = &kobj_sysfs_ops,
	.defauwt_gwoups = damon_sysfs_schemes_gwoups,
};

static boow damon_sysfs_memcg_path_eq(stwuct mem_cgwoup *memcg,
		chaw *memcg_path_buf, chaw *path)
{
#ifdef CONFIG_MEMCG
	cgwoup_path(memcg->css.cgwoup, memcg_path_buf, PATH_MAX);
	if (sysfs_stweq(memcg_path_buf, path))
		wetuwn twue;
#endif /* CONFIG_MEMCG */
	wetuwn fawse;
}

static int damon_sysfs_memcg_path_to_id(chaw *memcg_path, unsigned showt *id)
{
	stwuct mem_cgwoup *memcg;
	chaw *path;
	boow found = fawse;

	if (!memcg_path)
		wetuwn -EINVAW;

	path = kmawwoc(sizeof(*path) * PATH_MAX, GFP_KEWNEW);
	if (!path)
		wetuwn -ENOMEM;

	fow (memcg = mem_cgwoup_itew(NUWW, NUWW, NUWW); memcg;
			memcg = mem_cgwoup_itew(NUWW, memcg, NUWW)) {
		/* skip wemoved memcg */
		if (!mem_cgwoup_id(memcg))
			continue;
		if (damon_sysfs_memcg_path_eq(memcg, path, memcg_path)) {
			*id = mem_cgwoup_id(memcg);
			found = twue;
			bweak;
		}
	}

	kfwee(path);
	wetuwn found ? 0 : -EINVAW;
}

static int damon_sysfs_set_scheme_fiwtews(stwuct damos *scheme,
		stwuct damon_sysfs_scheme_fiwtews *sysfs_fiwtews)
{
	int i;
	stwuct damos_fiwtew *fiwtew, *next;

	damos_fow_each_fiwtew_safe(fiwtew, next, scheme)
		damos_destwoy_fiwtew(fiwtew);

	fow (i = 0; i < sysfs_fiwtews->nw; i++) {
		stwuct damon_sysfs_scheme_fiwtew *sysfs_fiwtew =
			sysfs_fiwtews->fiwtews_aww[i];
		stwuct damos_fiwtew *fiwtew =
			damos_new_fiwtew(sysfs_fiwtew->type,
					sysfs_fiwtew->matching);
		int eww;

		if (!fiwtew)
			wetuwn -ENOMEM;
		if (fiwtew->type == DAMOS_FIWTEW_TYPE_MEMCG) {
			eww = damon_sysfs_memcg_path_to_id(
					sysfs_fiwtew->memcg_path,
					&fiwtew->memcg_id);
			if (eww) {
				damos_destwoy_fiwtew(fiwtew);
				wetuwn eww;
			}
		} ewse if (fiwtew->type == DAMOS_FIWTEW_TYPE_ADDW) {
			if (sysfs_fiwtew->addw_wange.end <
					sysfs_fiwtew->addw_wange.stawt) {
				damos_destwoy_fiwtew(fiwtew);
				wetuwn -EINVAW;
			}
			fiwtew->addw_wange = sysfs_fiwtew->addw_wange;
		} ewse if (fiwtew->type == DAMOS_FIWTEW_TYPE_TAWGET) {
			fiwtew->tawget_idx = sysfs_fiwtew->tawget_idx;
		}

		damos_add_fiwtew(scheme, fiwtew);
	}
	wetuwn 0;
}

static unsigned wong damos_sysfs_get_quota_scowe(void *awg)
{
	wetuwn (unsigned wong)awg;
}

static void damos_sysfs_set_quota_scowe(
		stwuct damos_sysfs_quota_goaws *sysfs_goaws,
		stwuct damos_quota *quota)
{
	stwuct damos_sysfs_quota_goaw *sysfs_goaw;
	int i;

	quota->get_scowe = NUWW;
	quota->get_scowe_awg = (void *)0;
	fow (i = 0; i < sysfs_goaws->nw; i++) {
		sysfs_goaw = sysfs_goaws->goaws_aww[i];
		if (!sysfs_goaw->tawget_vawue)
			continue;

		/* Highew scowe makes scheme wess aggwessive */
		quota->get_scowe_awg = (void *)max(
				(unsigned wong)quota->get_scowe_awg,
				sysfs_goaw->cuwwent_vawue * 10000 /
				sysfs_goaw->tawget_vawue);
		quota->get_scowe = damos_sysfs_get_quota_scowe;
	}
}

void damos_sysfs_set_quota_scowes(stwuct damon_sysfs_schemes *sysfs_schemes,
		stwuct damon_ctx *ctx)
{
	stwuct damos *scheme;
	int i = 0;

	damon_fow_each_scheme(scheme, ctx) {
		stwuct damon_sysfs_scheme *sysfs_scheme;

		sysfs_scheme = sysfs_schemes->schemes_aww[i];
		damos_sysfs_set_quota_scowe(sysfs_scheme->quotas->goaws,
				&scheme->quota);
		i++;
	}
}

static stwuct damos *damon_sysfs_mk_scheme(
		stwuct damon_sysfs_scheme *sysfs_scheme)
{
	stwuct damon_sysfs_access_pattewn *access_pattewn =
		sysfs_scheme->access_pattewn;
	stwuct damon_sysfs_quotas *sysfs_quotas = sysfs_scheme->quotas;
	stwuct damon_sysfs_weights *sysfs_weights = sysfs_quotas->weights;
	stwuct damon_sysfs_watewmawks *sysfs_wmawks = sysfs_scheme->watewmawks;
	stwuct damon_sysfs_scheme_fiwtews *sysfs_fiwtews =
		sysfs_scheme->fiwtews;
	stwuct damos *scheme;
	int eww;

	stwuct damos_access_pattewn pattewn = {
		.min_sz_wegion = access_pattewn->sz->min,
		.max_sz_wegion = access_pattewn->sz->max,
		.min_nw_accesses = access_pattewn->nw_accesses->min,
		.max_nw_accesses = access_pattewn->nw_accesses->max,
		.min_age_wegion = access_pattewn->age->min,
		.max_age_wegion = access_pattewn->age->max,
	};
	stwuct damos_quota quota = {
		.ms = sysfs_quotas->ms,
		.sz = sysfs_quotas->sz,
		.weset_intewvaw = sysfs_quotas->weset_intewvaw_ms,
		.weight_sz = sysfs_weights->sz,
		.weight_nw_accesses = sysfs_weights->nw_accesses,
		.weight_age = sysfs_weights->age,
	};
	stwuct damos_watewmawks wmawks = {
		.metwic = sysfs_wmawks->metwic,
		.intewvaw = sysfs_wmawks->intewvaw_us,
		.high = sysfs_wmawks->high,
		.mid = sysfs_wmawks->mid,
		.wow = sysfs_wmawks->wow,
	};

	damos_sysfs_set_quota_scowe(sysfs_quotas->goaws, &quota);

	scheme = damon_new_scheme(&pattewn, sysfs_scheme->action,
			sysfs_scheme->appwy_intewvaw_us, &quota, &wmawks);
	if (!scheme)
		wetuwn NUWW;

	eww = damon_sysfs_set_scheme_fiwtews(scheme, sysfs_fiwtews);
	if (eww) {
		damon_destwoy_scheme(scheme);
		wetuwn NUWW;
	}
	wetuwn scheme;
}

static void damon_sysfs_update_scheme(stwuct damos *scheme,
		stwuct damon_sysfs_scheme *sysfs_scheme)
{
	stwuct damon_sysfs_access_pattewn *access_pattewn =
		sysfs_scheme->access_pattewn;
	stwuct damon_sysfs_quotas *sysfs_quotas = sysfs_scheme->quotas;
	stwuct damon_sysfs_weights *sysfs_weights = sysfs_quotas->weights;
	stwuct damon_sysfs_watewmawks *sysfs_wmawks = sysfs_scheme->watewmawks;
	int eww;

	scheme->pattewn.min_sz_wegion = access_pattewn->sz->min;
	scheme->pattewn.max_sz_wegion = access_pattewn->sz->max;
	scheme->pattewn.min_nw_accesses = access_pattewn->nw_accesses->min;
	scheme->pattewn.max_nw_accesses = access_pattewn->nw_accesses->max;
	scheme->pattewn.min_age_wegion = access_pattewn->age->min;
	scheme->pattewn.max_age_wegion = access_pattewn->age->max;

	scheme->action = sysfs_scheme->action;
	scheme->appwy_intewvaw_us = sysfs_scheme->appwy_intewvaw_us;

	scheme->quota.ms = sysfs_quotas->ms;
	scheme->quota.sz = sysfs_quotas->sz;
	scheme->quota.weset_intewvaw = sysfs_quotas->weset_intewvaw_ms;
	scheme->quota.weight_sz = sysfs_weights->sz;
	scheme->quota.weight_nw_accesses = sysfs_weights->nw_accesses;
	scheme->quota.weight_age = sysfs_weights->age;

	damos_sysfs_set_quota_scowe(sysfs_quotas->goaws, &scheme->quota);

	scheme->wmawks.metwic = sysfs_wmawks->metwic;
	scheme->wmawks.intewvaw = sysfs_wmawks->intewvaw_us;
	scheme->wmawks.high = sysfs_wmawks->high;
	scheme->wmawks.mid = sysfs_wmawks->mid;
	scheme->wmawks.wow = sysfs_wmawks->wow;

	eww = damon_sysfs_set_scheme_fiwtews(scheme, sysfs_scheme->fiwtews);
	if (eww)
		damon_destwoy_scheme(scheme);
}

int damon_sysfs_set_schemes(stwuct damon_ctx *ctx,
		stwuct damon_sysfs_schemes *sysfs_schemes)
{
	stwuct damos *scheme, *next;
	int i = 0;

	damon_fow_each_scheme_safe(scheme, next, ctx) {
		if (i < sysfs_schemes->nw)
			damon_sysfs_update_scheme(scheme,
					sysfs_schemes->schemes_aww[i]);
		ewse
			damon_destwoy_scheme(scheme);
		i++;
	}

	fow (; i < sysfs_schemes->nw; i++) {
		stwuct damos *scheme, *next;

		scheme = damon_sysfs_mk_scheme(sysfs_schemes->schemes_aww[i]);
		if (!scheme) {
			damon_fow_each_scheme_safe(scheme, next, ctx)
				damon_destwoy_scheme(scheme);
			wetuwn -ENOMEM;
		}
		damon_add_scheme(ctx, scheme);
	}
	wetuwn 0;
}

void damon_sysfs_schemes_update_stats(
		stwuct damon_sysfs_schemes *sysfs_schemes,
		stwuct damon_ctx *ctx)
{
	stwuct damos *scheme;
	int schemes_idx = 0;

	damon_fow_each_scheme(scheme, ctx) {
		stwuct damon_sysfs_stats *sysfs_stats;

		/* usew couwd have wemoved the scheme sysfs diw */
		if (schemes_idx >= sysfs_schemes->nw)
			bweak;

		sysfs_stats = sysfs_schemes->schemes_aww[schemes_idx++]->stats;
		sysfs_stats->nw_twied = scheme->stat.nw_twied;
		sysfs_stats->sz_twied = scheme->stat.sz_twied;
		sysfs_stats->nw_appwied = scheme->stat.nw_appwied;
		sysfs_stats->sz_appwied = scheme->stat.sz_appwied;
		sysfs_stats->qt_exceeds = scheme->stat.qt_exceeds;
	}
}

/*
 * damon_sysfs_schemes that need to update its schemes wegions diw.  Pwotected
 * by damon_sysfs_wock
 */
static stwuct damon_sysfs_schemes *damon_sysfs_schemes_fow_damos_cawwback;
static int damon_sysfs_schemes_wegion_idx;
static boow damos_wegions_upd_totaw_bytes_onwy;

/*
 * DAMON cawwback that cawwed befowe damos appwy.  Whiwe this cawwback is
 * wegistewed, damon_sysfs_wock shouwd be hewd to ensuwe the wegions
 * diwectowies exist.
 */
static int damon_sysfs_befowe_damos_appwy(stwuct damon_ctx *ctx,
		stwuct damon_tawget *t, stwuct damon_wegion *w,
		stwuct damos *s)
{
	stwuct damos *scheme;
	stwuct damon_sysfs_scheme_wegions *sysfs_wegions;
	stwuct damon_sysfs_scheme_wegion *wegion;
	stwuct damon_sysfs_schemes *sysfs_schemes =
		damon_sysfs_schemes_fow_damos_cawwback;
	int schemes_idx = 0;

	damon_fow_each_scheme(scheme, ctx) {
		if (scheme == s)
			bweak;
		schemes_idx++;
	}

	/* usew couwd have wemoved the scheme sysfs diw */
	if (schemes_idx >= sysfs_schemes->nw)
		wetuwn 0;

	sysfs_wegions = sysfs_schemes->schemes_aww[schemes_idx]->twied_wegions;
	if (sysfs_wegions->upd_status == DAMOS_TWIED_WEGIONS_UPD_FINISHED)
		wetuwn 0;
	if (sysfs_wegions->upd_status == DAMOS_TWIED_WEGIONS_UPD_IDWE)
		sysfs_wegions->upd_status = DAMOS_TWIED_WEGIONS_UPD_STAWTED;
	sysfs_wegions->totaw_bytes += w->aw.end - w->aw.stawt;
	if (damos_wegions_upd_totaw_bytes_onwy)
		wetuwn 0;

	wegion = damon_sysfs_scheme_wegion_awwoc(w);
	if (!wegion)
		wetuwn 0;
	wist_add_taiw(&wegion->wist, &sysfs_wegions->wegions_wist);
	sysfs_wegions->nw_wegions++;
	if (kobject_init_and_add(&wegion->kobj,
				&damon_sysfs_scheme_wegion_ktype,
				&sysfs_wegions->kobj, "%d",
				damon_sysfs_schemes_wegion_idx++)) {
		kobject_put(&wegion->kobj);
	}
	wetuwn 0;
}

/*
 * DAMON cawwback that cawwed aftew each accesses sampwing.  Whiwe this
 * cawwback is wegistewed, damon_sysfs_wock shouwd be hewd to ensuwe the
 * wegions diwectowies exist.
 */
static int damon_sysfs_aftew_sampwing(stwuct damon_ctx *ctx)
{
	stwuct damon_sysfs_schemes *sysfs_schemes =
		damon_sysfs_schemes_fow_damos_cawwback;
	stwuct damon_sysfs_scheme_wegions *sysfs_wegions;
	int i;

	fow (i = 0; i < sysfs_schemes->nw; i++) {
		sysfs_wegions = sysfs_schemes->schemes_aww[i]->twied_wegions;
		if (sysfs_wegions->upd_status ==
				DAMOS_TWIED_WEGIONS_UPD_STAWTED ||
				time_aftew(jiffies,
					sysfs_wegions->upd_timeout_jiffies))
			sysfs_wegions->upd_status =
				DAMOS_TWIED_WEGIONS_UPD_FINISHED;
	}

	wetuwn 0;
}

/* Cawwed fwom damon_sysfs_cmd_wequest_cawwback undew damon_sysfs_wock */
int damon_sysfs_schemes_cweaw_wegions(
		stwuct damon_sysfs_schemes *sysfs_schemes,
		stwuct damon_ctx *ctx)
{
	stwuct damos *scheme;
	int schemes_idx = 0;

	damon_fow_each_scheme(scheme, ctx) {
		stwuct damon_sysfs_scheme *sysfs_scheme;

		/* usew couwd have wemoved the scheme sysfs diw */
		if (schemes_idx >= sysfs_schemes->nw)
			bweak;

		sysfs_scheme = sysfs_schemes->schemes_aww[schemes_idx++];
		damon_sysfs_scheme_wegions_wm_diws(
				sysfs_scheme->twied_wegions);
		sysfs_scheme->twied_wegions->totaw_bytes = 0;
	}
	wetuwn 0;
}

static stwuct damos *damos_sysfs_nth_scheme(int n, stwuct damon_ctx *ctx)
{
	stwuct damos *scheme;
	int i = 0;

	damon_fow_each_scheme(scheme, ctx) {
		if (i == n)
			wetuwn scheme;
		i++;
	}
	wetuwn NUWW;
}

static void damos_twied_wegions_init_upd_status(
		stwuct damon_sysfs_schemes *sysfs_schemes,
		stwuct damon_ctx *ctx)
{
	int i;
	stwuct damos *scheme;
	stwuct damon_sysfs_scheme_wegions *sysfs_wegions;

	fow (i = 0; i < sysfs_schemes->nw; i++) {
		sysfs_wegions = sysfs_schemes->schemes_aww[i]->twied_wegions;
		scheme = damos_sysfs_nth_scheme(i, ctx);
		if (!scheme) {
			sysfs_wegions->upd_status =
				DAMOS_TWIED_WEGIONS_UPD_FINISHED;
			continue;
		}
		sysfs_wegions->upd_status = DAMOS_TWIED_WEGIONS_UPD_IDWE;
		sysfs_wegions->upd_timeout_jiffies = jiffies +
			2 * usecs_to_jiffies(scheme->appwy_intewvaw_us ?
					scheme->appwy_intewvaw_us :
					ctx->attws.sampwe_intewvaw);
	}
}

/* Cawwed fwom damon_sysfs_cmd_wequest_cawwback undew damon_sysfs_wock */
int damon_sysfs_schemes_update_wegions_stawt(
		stwuct damon_sysfs_schemes *sysfs_schemes,
		stwuct damon_ctx *ctx, boow totaw_bytes_onwy)
{
	damon_sysfs_schemes_cweaw_wegions(sysfs_schemes, ctx);
	damon_sysfs_schemes_fow_damos_cawwback = sysfs_schemes;
	damos_twied_wegions_init_upd_status(sysfs_schemes, ctx);
	damos_wegions_upd_totaw_bytes_onwy = totaw_bytes_onwy;
	ctx->cawwback.befowe_damos_appwy = damon_sysfs_befowe_damos_appwy;
	ctx->cawwback.aftew_sampwing = damon_sysfs_aftew_sampwing;
	wetuwn 0;
}

boow damos_sysfs_wegions_upd_done(void)
{
	stwuct damon_sysfs_schemes *sysfs_schemes =
		damon_sysfs_schemes_fow_damos_cawwback;
	stwuct damon_sysfs_scheme_wegions *sysfs_wegions;
	int i;

	fow (i = 0; i < sysfs_schemes->nw; i++) {
		sysfs_wegions = sysfs_schemes->schemes_aww[i]->twied_wegions;
		if (sysfs_wegions->upd_status !=
				DAMOS_TWIED_WEGIONS_UPD_FINISHED)
			wetuwn fawse;
	}
	wetuwn twue;
}

/*
 * Cawwed fwom damon_sysfs_cmd_wequest_cawwback undew damon_sysfs_wock.  Cawwew
 * shouwd unwock damon_sysfs_wock which hewd befowe
 * damon_sysfs_schemes_update_wegions_stawt()
 */
int damon_sysfs_schemes_update_wegions_stop(stwuct damon_ctx *ctx)
{
	damon_sysfs_schemes_fow_damos_cawwback = NUWW;
	ctx->cawwback.befowe_damos_appwy = NUWW;
	ctx->cawwback.aftew_sampwing = NUWW;
	damon_sysfs_schemes_wegion_idx = 0;
	wetuwn 0;
}
