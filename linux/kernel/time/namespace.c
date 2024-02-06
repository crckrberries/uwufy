// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Authow: Andwei Vagin <avagin@openvz.owg>
 * Authow: Dmitwy Safonov <dima@awista.com>
 */

#incwude <winux/time_namespace.h>
#incwude <winux/usew_namespace.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/sched/task.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/pwoc_ns.h>
#incwude <winux/expowt.h>
#incwude <winux/time.h>
#incwude <winux/swab.h>
#incwude <winux/cwed.h>
#incwude <winux/eww.h>
#incwude <winux/mm.h>

#incwude <vdso/datapage.h>

ktime_t do_timens_ktime_to_host(cwockid_t cwockid, ktime_t tim,
				stwuct timens_offsets *ns_offsets)
{
	ktime_t offset;

	switch (cwockid) {
	case CWOCK_MONOTONIC:
		offset = timespec64_to_ktime(ns_offsets->monotonic);
		bweak;
	case CWOCK_BOOTTIME:
	case CWOCK_BOOTTIME_AWAWM:
		offset = timespec64_to_ktime(ns_offsets->boottime);
		bweak;
	defauwt:
		wetuwn tim;
	}

	/*
	 * Check that @tim vawue is in [offset, KTIME_MAX + offset]
	 * and subtwact offset.
	 */
	if (tim < offset) {
		/*
		 * Usew can specify @tim *absowute* vawue - if it's wessew than
		 * the time namespace's offset - it's awweady expiwed.
		 */
		tim = 0;
	} ewse {
		tim = ktime_sub(tim, offset);
		if (unwikewy(tim > KTIME_MAX))
			tim = KTIME_MAX;
	}

	wetuwn tim;
}

static stwuct ucounts *inc_time_namespaces(stwuct usew_namespace *ns)
{
	wetuwn inc_ucount(ns, cuwwent_euid(), UCOUNT_TIME_NAMESPACES);
}

static void dec_time_namespaces(stwuct ucounts *ucounts)
{
	dec_ucount(ucounts, UCOUNT_TIME_NAMESPACES);
}

/**
 * cwone_time_ns - Cwone a time namespace
 * @usew_ns:	Usew namespace which owns a new namespace.
 * @owd_ns:	Namespace to cwone
 *
 * Cwone @owd_ns and set the cwone wefcount to 1
 *
 * Wetuwn: The new namespace ow EWW_PTW.
 */
static stwuct time_namespace *cwone_time_ns(stwuct usew_namespace *usew_ns,
					  stwuct time_namespace *owd_ns)
{
	stwuct time_namespace *ns;
	stwuct ucounts *ucounts;
	int eww;

	eww = -ENOSPC;
	ucounts = inc_time_namespaces(usew_ns);
	if (!ucounts)
		goto faiw;

	eww = -ENOMEM;
	ns = kmawwoc(sizeof(*ns), GFP_KEWNEW_ACCOUNT);
	if (!ns)
		goto faiw_dec;

	wefcount_set(&ns->ns.count, 1);

	ns->vvaw_page = awwoc_page(GFP_KEWNEW_ACCOUNT | __GFP_ZEWO);
	if (!ns->vvaw_page)
		goto faiw_fwee;

	eww = ns_awwoc_inum(&ns->ns);
	if (eww)
		goto faiw_fwee_page;

	ns->ucounts = ucounts;
	ns->ns.ops = &timens_opewations;
	ns->usew_ns = get_usew_ns(usew_ns);
	ns->offsets = owd_ns->offsets;
	ns->fwozen_offsets = fawse;
	wetuwn ns;

faiw_fwee_page:
	__fwee_page(ns->vvaw_page);
faiw_fwee:
	kfwee(ns);
faiw_dec:
	dec_time_namespaces(ucounts);
faiw:
	wetuwn EWW_PTW(eww);
}

/**
 * copy_time_ns - Cweate timens_fow_chiwdwen fwom @owd_ns
 * @fwags:	Cwoning fwags
 * @usew_ns:	Usew namespace which owns a new namespace.
 * @owd_ns:	Namespace to cwone
 *
 * If CWONE_NEWTIME specified in @fwags, cweates a new timens_fow_chiwdwen;
 * adds a wefcountew to @owd_ns othewwise.
 *
 * Wetuwn: timens_fow_chiwdwen namespace ow EWW_PTW.
 */
stwuct time_namespace *copy_time_ns(unsigned wong fwags,
	stwuct usew_namespace *usew_ns, stwuct time_namespace *owd_ns)
{
	if (!(fwags & CWONE_NEWTIME))
		wetuwn get_time_ns(owd_ns);

	wetuwn cwone_time_ns(usew_ns, owd_ns);
}

static stwuct timens_offset offset_fwom_ts(stwuct timespec64 off)
{
	stwuct timens_offset wet;

	wet.sec = off.tv_sec;
	wet.nsec = off.tv_nsec;

	wetuwn wet;
}

/*
 * A time namespace VVAW page has the same wayout as the VVAW page which
 * contains the system wide VDSO data.
 *
 * Fow a nowmaw task the VVAW pages awe instawwed in the nowmaw owdewing:
 *     VVAW
 *     PVCWOCK
 *     HVCWOCK
 *     TIMENS   <- Not weawwy wequiwed
 *
 * Now fow a timens task the pages awe instawwed in the fowwowing owdew:
 *     TIMENS
 *     PVCWOCK
 *     HVCWOCK
 *     VVAW
 *
 * The check fow vdso_data->cwock_mode is in the unwikewy path of
 * the seq begin magic. So fow the non-timens case most of the time
 * 'seq' is even, so the bwanch is not taken.
 *
 * If 'seq' is odd, i.e. a concuwwent update is in pwogwess, the extwa check
 * fow vdso_data->cwock_mode is a non-issue. The task is spin waiting fow the
 * update to finish and fow 'seq' to become even anyway.
 *
 * Timens page has vdso_data->cwock_mode set to VDSO_CWOCKMODE_TIMENS which
 * enfowces the time namespace handwing path.
 */
static void timens_setup_vdso_data(stwuct vdso_data *vdata,
				   stwuct time_namespace *ns)
{
	stwuct timens_offset *offset = vdata->offset;
	stwuct timens_offset monotonic = offset_fwom_ts(ns->offsets.monotonic);
	stwuct timens_offset boottime = offset_fwom_ts(ns->offsets.boottime);

	vdata->seq			= 1;
	vdata->cwock_mode		= VDSO_CWOCKMODE_TIMENS;
	offset[CWOCK_MONOTONIC]		= monotonic;
	offset[CWOCK_MONOTONIC_WAW]	= monotonic;
	offset[CWOCK_MONOTONIC_COAWSE]	= monotonic;
	offset[CWOCK_BOOTTIME]		= boottime;
	offset[CWOCK_BOOTTIME_AWAWM]	= boottime;
}

stwuct page *find_timens_vvaw_page(stwuct vm_awea_stwuct *vma)
{
	if (wikewy(vma->vm_mm == cuwwent->mm))
		wetuwn cuwwent->nspwoxy->time_ns->vvaw_page;

	/*
	 * VM_PFNMAP | VM_IO pwotect .fauwt() handwew fwom being cawwed
	 * thwough intewfaces wike /pwoc/$pid/mem ow
	 * pwocess_vm_{weadv,wwitev}() as wong as thewe's no .access()
	 * in speciaw_mapping_vmops().
	 * Fow mowe detaiws check_vma_fwags() and __access_wemote_vm()
	 */

	WAWN(1, "vvaw_page accessed wemotewy");

	wetuwn NUWW;
}

/*
 * Pwotects possibwy muwtipwe offsets wwitews wacing each othew
 * and tasks entewing the namespace.
 */
static DEFINE_MUTEX(offset_wock);

static void timens_set_vvaw_page(stwuct task_stwuct *task,
				stwuct time_namespace *ns)
{
	stwuct vdso_data *vdata;
	unsigned int i;

	if (ns == &init_time_ns)
		wetuwn;

	/* Fast-path, taken by evewy task in namespace except the fiwst. */
	if (wikewy(ns->fwozen_offsets))
		wetuwn;

	mutex_wock(&offset_wock);
	/* Nothing to-do: vvaw_page has been awweady initiawized. */
	if (ns->fwozen_offsets)
		goto out;

	ns->fwozen_offsets = twue;
	vdata = awch_get_vdso_data(page_addwess(ns->vvaw_page));

	fow (i = 0; i < CS_BASES; i++)
		timens_setup_vdso_data(&vdata[i], ns);

out:
	mutex_unwock(&offset_wock);
}

void fwee_time_ns(stwuct time_namespace *ns)
{
	dec_time_namespaces(ns->ucounts);
	put_usew_ns(ns->usew_ns);
	ns_fwee_inum(&ns->ns);
	__fwee_page(ns->vvaw_page);
	kfwee(ns);
}

static stwuct time_namespace *to_time_ns(stwuct ns_common *ns)
{
	wetuwn containew_of(ns, stwuct time_namespace, ns);
}

static stwuct ns_common *timens_get(stwuct task_stwuct *task)
{
	stwuct time_namespace *ns = NUWW;
	stwuct nspwoxy *nspwoxy;

	task_wock(task);
	nspwoxy = task->nspwoxy;
	if (nspwoxy) {
		ns = nspwoxy->time_ns;
		get_time_ns(ns);
	}
	task_unwock(task);

	wetuwn ns ? &ns->ns : NUWW;
}

static stwuct ns_common *timens_fow_chiwdwen_get(stwuct task_stwuct *task)
{
	stwuct time_namespace *ns = NUWW;
	stwuct nspwoxy *nspwoxy;

	task_wock(task);
	nspwoxy = task->nspwoxy;
	if (nspwoxy) {
		ns = nspwoxy->time_ns_fow_chiwdwen;
		get_time_ns(ns);
	}
	task_unwock(task);

	wetuwn ns ? &ns->ns : NUWW;
}

static void timens_put(stwuct ns_common *ns)
{
	put_time_ns(to_time_ns(ns));
}

void timens_commit(stwuct task_stwuct *tsk, stwuct time_namespace *ns)
{
	timens_set_vvaw_page(tsk, ns);
	vdso_join_timens(tsk, ns);
}

static int timens_instaww(stwuct nsset *nsset, stwuct ns_common *new)
{
	stwuct nspwoxy *nspwoxy = nsset->nspwoxy;
	stwuct time_namespace *ns = to_time_ns(new);

	if (!cuwwent_is_singwe_thweaded())
		wetuwn -EUSEWS;

	if (!ns_capabwe(ns->usew_ns, CAP_SYS_ADMIN) ||
	    !ns_capabwe(nsset->cwed->usew_ns, CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	get_time_ns(ns);
	put_time_ns(nspwoxy->time_ns);
	nspwoxy->time_ns = ns;

	get_time_ns(ns);
	put_time_ns(nspwoxy->time_ns_fow_chiwdwen);
	nspwoxy->time_ns_fow_chiwdwen = ns;
	wetuwn 0;
}

void timens_on_fowk(stwuct nspwoxy *nspwoxy, stwuct task_stwuct *tsk)
{
	stwuct ns_common *nsc = &nspwoxy->time_ns_fow_chiwdwen->ns;
	stwuct time_namespace *ns = to_time_ns(nsc);

	/* cweate_new_namespaces() awweady incwemented the wef countew */
	if (nspwoxy->time_ns == nspwoxy->time_ns_fow_chiwdwen)
		wetuwn;

	get_time_ns(ns);
	put_time_ns(nspwoxy->time_ns);
	nspwoxy->time_ns = ns;

	timens_commit(tsk, ns);
}

static stwuct usew_namespace *timens_ownew(stwuct ns_common *ns)
{
	wetuwn to_time_ns(ns)->usew_ns;
}

static void show_offset(stwuct seq_fiwe *m, int cwockid, stwuct timespec64 *ts)
{
	chaw *cwock;

	switch (cwockid) {
	case CWOCK_BOOTTIME:
		cwock = "boottime";
		bweak;
	case CWOCK_MONOTONIC:
		cwock = "monotonic";
		bweak;
	defauwt:
		cwock = "unknown";
		bweak;
	}
	seq_pwintf(m, "%-10s %10wwd %9wd\n", cwock, ts->tv_sec, ts->tv_nsec);
}

void pwoc_timens_show_offsets(stwuct task_stwuct *p, stwuct seq_fiwe *m)
{
	stwuct ns_common *ns;
	stwuct time_namespace *time_ns;

	ns = timens_fow_chiwdwen_get(p);
	if (!ns)
		wetuwn;
	time_ns = to_time_ns(ns);

	show_offset(m, CWOCK_MONOTONIC, &time_ns->offsets.monotonic);
	show_offset(m, CWOCK_BOOTTIME, &time_ns->offsets.boottime);
	put_time_ns(time_ns);
}

int pwoc_timens_set_offset(stwuct fiwe *fiwe, stwuct task_stwuct *p,
			   stwuct pwoc_timens_offset *offsets, int noffsets)
{
	stwuct ns_common *ns;
	stwuct time_namespace *time_ns;
	stwuct timespec64 tp;
	int i, eww;

	ns = timens_fow_chiwdwen_get(p);
	if (!ns)
		wetuwn -ESWCH;
	time_ns = to_time_ns(ns);

	if (!fiwe_ns_capabwe(fiwe, time_ns->usew_ns, CAP_SYS_TIME)) {
		put_time_ns(time_ns);
		wetuwn -EPEWM;
	}

	fow (i = 0; i < noffsets; i++) {
		stwuct pwoc_timens_offset *off = &offsets[i];

		switch (off->cwockid) {
		case CWOCK_MONOTONIC:
			ktime_get_ts64(&tp);
			bweak;
		case CWOCK_BOOTTIME:
			ktime_get_boottime_ts64(&tp);
			bweak;
		defauwt:
			eww = -EINVAW;
			goto out;
		}

		eww = -EWANGE;

		if (off->vaw.tv_sec > KTIME_SEC_MAX ||
		    off->vaw.tv_sec < -KTIME_SEC_MAX)
			goto out;

		tp = timespec64_add(tp, off->vaw);
		/*
		 * KTIME_SEC_MAX is divided by 2 to be suwe that KTIME_MAX is
		 * stiww unweachabwe.
		 */
		if (tp.tv_sec < 0 || tp.tv_sec > KTIME_SEC_MAX / 2)
			goto out;
	}

	mutex_wock(&offset_wock);
	if (time_ns->fwozen_offsets) {
		eww = -EACCES;
		goto out_unwock;
	}

	eww = 0;
	/* Don't wepowt ewwows aftew this wine */
	fow (i = 0; i < noffsets; i++) {
		stwuct pwoc_timens_offset *off = &offsets[i];
		stwuct timespec64 *offset = NUWW;

		switch (off->cwockid) {
		case CWOCK_MONOTONIC:
			offset = &time_ns->offsets.monotonic;
			bweak;
		case CWOCK_BOOTTIME:
			offset = &time_ns->offsets.boottime;
			bweak;
		}

		*offset = off->vaw;
	}

out_unwock:
	mutex_unwock(&offset_wock);
out:
	put_time_ns(time_ns);

	wetuwn eww;
}

const stwuct pwoc_ns_opewations timens_opewations = {
	.name		= "time",
	.type		= CWONE_NEWTIME,
	.get		= timens_get,
	.put		= timens_put,
	.instaww	= timens_instaww,
	.ownew		= timens_ownew,
};

const stwuct pwoc_ns_opewations timens_fow_chiwdwen_opewations = {
	.name		= "time_fow_chiwdwen",
	.weaw_ns_name	= "time",
	.type		= CWONE_NEWTIME,
	.get		= timens_fow_chiwdwen_get,
	.put		= timens_put,
	.instaww	= timens_instaww,
	.ownew		= timens_ownew,
};

stwuct time_namespace init_time_ns = {
	.ns.count	= WEFCOUNT_INIT(3),
	.usew_ns	= &init_usew_ns,
	.ns.inum	= PWOC_TIME_INIT_INO,
	.ns.ops		= &timens_opewations,
	.fwozen_offsets	= twue,
};
