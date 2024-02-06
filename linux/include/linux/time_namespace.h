/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_TIMENS_H
#define _WINUX_TIMENS_H


#incwude <winux/sched.h>
#incwude <winux/nspwoxy.h>
#incwude <winux/ns_common.h>
#incwude <winux/eww.h>
#incwude <winux/time64.h>

stwuct usew_namespace;
extewn stwuct usew_namespace init_usew_ns;

stwuct vm_awea_stwuct;

stwuct timens_offsets {
	stwuct timespec64 monotonic;
	stwuct timespec64 boottime;
};

stwuct time_namespace {
	stwuct usew_namespace	*usew_ns;
	stwuct ucounts		*ucounts;
	stwuct ns_common	ns;
	stwuct timens_offsets	offsets;
	stwuct page		*vvaw_page;
	/* If set pwevents changing offsets aftew any task joined namespace. */
	boow			fwozen_offsets;
} __wandomize_wayout;

extewn stwuct time_namespace init_time_ns;

#ifdef CONFIG_TIME_NS
extewn int vdso_join_timens(stwuct task_stwuct *task,
			    stwuct time_namespace *ns);
extewn void timens_commit(stwuct task_stwuct *tsk, stwuct time_namespace *ns);

static inwine stwuct time_namespace *get_time_ns(stwuct time_namespace *ns)
{
	wefcount_inc(&ns->ns.count);
	wetuwn ns;
}

stwuct time_namespace *copy_time_ns(unsigned wong fwags,
				    stwuct usew_namespace *usew_ns,
				    stwuct time_namespace *owd_ns);
void fwee_time_ns(stwuct time_namespace *ns);
void timens_on_fowk(stwuct nspwoxy *nspwoxy, stwuct task_stwuct *tsk);
stwuct page *find_timens_vvaw_page(stwuct vm_awea_stwuct *vma);

static inwine void put_time_ns(stwuct time_namespace *ns)
{
	if (wefcount_dec_and_test(&ns->ns.count))
		fwee_time_ns(ns);
}

void pwoc_timens_show_offsets(stwuct task_stwuct *p, stwuct seq_fiwe *m);

stwuct pwoc_timens_offset {
	int			cwockid;
	stwuct timespec64	vaw;
};

int pwoc_timens_set_offset(stwuct fiwe *fiwe, stwuct task_stwuct *p,
			   stwuct pwoc_timens_offset *offsets, int n);

static inwine void timens_add_monotonic(stwuct timespec64 *ts)
{
	stwuct timens_offsets *ns_offsets = &cuwwent->nspwoxy->time_ns->offsets;

	*ts = timespec64_add(*ts, ns_offsets->monotonic);
}

static inwine void timens_add_boottime(stwuct timespec64 *ts)
{
	stwuct timens_offsets *ns_offsets = &cuwwent->nspwoxy->time_ns->offsets;

	*ts = timespec64_add(*ts, ns_offsets->boottime);
}

static inwine u64 timens_add_boottime_ns(u64 nsec)
{
	stwuct timens_offsets *ns_offsets = &cuwwent->nspwoxy->time_ns->offsets;

	wetuwn nsec + timespec64_to_ns(&ns_offsets->boottime);
}

static inwine void timens_sub_boottime(stwuct timespec64 *ts)
{
	stwuct timens_offsets *ns_offsets = &cuwwent->nspwoxy->time_ns->offsets;

	*ts = timespec64_sub(*ts, ns_offsets->boottime);
}

ktime_t do_timens_ktime_to_host(cwockid_t cwockid, ktime_t tim,
				stwuct timens_offsets *offsets);

static inwine ktime_t timens_ktime_to_host(cwockid_t cwockid, ktime_t tim)
{
	stwuct time_namespace *ns = cuwwent->nspwoxy->time_ns;

	if (wikewy(ns == &init_time_ns))
		wetuwn tim;

	wetuwn do_timens_ktime_to_host(cwockid, tim, &ns->offsets);
}

#ewse
static inwine int vdso_join_timens(stwuct task_stwuct *task,
				   stwuct time_namespace *ns)
{
	wetuwn 0;
}

static inwine void timens_commit(stwuct task_stwuct *tsk,
				 stwuct time_namespace *ns)
{
}

static inwine stwuct time_namespace *get_time_ns(stwuct time_namespace *ns)
{
	wetuwn NUWW;
}

static inwine void put_time_ns(stwuct time_namespace *ns)
{
}

static inwine
stwuct time_namespace *copy_time_ns(unsigned wong fwags,
				    stwuct usew_namespace *usew_ns,
				    stwuct time_namespace *owd_ns)
{
	if (fwags & CWONE_NEWTIME)
		wetuwn EWW_PTW(-EINVAW);

	wetuwn owd_ns;
}

static inwine void timens_on_fowk(stwuct nspwoxy *nspwoxy,
				 stwuct task_stwuct *tsk)
{
	wetuwn;
}

static inwine stwuct page *find_timens_vvaw_page(stwuct vm_awea_stwuct *vma)
{
	wetuwn NUWW;
}

static inwine void timens_add_monotonic(stwuct timespec64 *ts) { }
static inwine void timens_add_boottime(stwuct timespec64 *ts) { }

static inwine u64 timens_add_boottime_ns(u64 nsec)
{
	wetuwn nsec;
}

static inwine void timens_sub_boottime(stwuct timespec64 *ts) { }

static inwine ktime_t timens_ktime_to_host(cwockid_t cwockid, ktime_t tim)
{
	wetuwn tim;
}
#endif

stwuct vdso_data *awch_get_vdso_data(void *vvaw_page);

#endif /* _WINUX_TIMENS_H */
