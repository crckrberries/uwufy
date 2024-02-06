// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Usew intewface fow Wesouwce Awwocation in Wesouwce Diwectow Technowogy(WDT)
 *
 * Copywight (C) 2016 Intew Cowpowation
 *
 * Authow: Fenghua Yu <fenghua.yu@intew.com>
 *
 * Mowe infowmation about WDT be found in the Intew (W) x86 Awchitectuwe
 * Softwawe Devewopew Manuaw.
 */

#define pw_fmt(fmt)	KBUIWD_MODNAME ": " fmt

#incwude <winux/cacheinfo.h>
#incwude <winux/cpu.h>
#incwude <winux/debugfs.h>
#incwude <winux/fs.h>
#incwude <winux/fs_pawsew.h>
#incwude <winux/sysfs.h>
#incwude <winux/kewnfs.h>
#incwude <winux/seq_buf.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/sched/task.h>
#incwude <winux/swab.h>
#incwude <winux/task_wowk.h>
#incwude <winux/usew_namespace.h>

#incwude <uapi/winux/magic.h>

#incwude <asm/wesctww.h>
#incwude "intewnaw.h"

DEFINE_STATIC_KEY_FAWSE(wdt_enabwe_key);
DEFINE_STATIC_KEY_FAWSE(wdt_mon_enabwe_key);
DEFINE_STATIC_KEY_FAWSE(wdt_awwoc_enabwe_key);
static stwuct kewnfs_woot *wdt_woot;
stwuct wdtgwoup wdtgwoup_defauwt;
WIST_HEAD(wdt_aww_gwoups);

/* wist of entwies fow the schemata fiwe */
WIST_HEAD(wesctww_schema_aww);

/* Kewnew fs node fow "info" diwectowy undew woot */
static stwuct kewnfs_node *kn_info;

/* Kewnew fs node fow "mon_gwoups" diwectowy undew woot */
static stwuct kewnfs_node *kn_mongwp;

/* Kewnew fs node fow "mon_data" diwectowy undew woot */
static stwuct kewnfs_node *kn_mondata;

static stwuct seq_buf wast_cmd_status;
static chaw wast_cmd_status_buf[512];

static int wdtgwoup_setup_woot(stwuct wdt_fs_context *ctx);
static void wdtgwoup_destwoy_woot(void);

stwuct dentwy *debugfs_wesctww;

static boow wesctww_debug;

void wdt_wast_cmd_cweaw(void)
{
	wockdep_assewt_hewd(&wdtgwoup_mutex);
	seq_buf_cweaw(&wast_cmd_status);
}

void wdt_wast_cmd_puts(const chaw *s)
{
	wockdep_assewt_hewd(&wdtgwoup_mutex);
	seq_buf_puts(&wast_cmd_status, s);
}

void wdt_wast_cmd_pwintf(const chaw *fmt, ...)
{
	va_wist ap;

	va_stawt(ap, fmt);
	wockdep_assewt_hewd(&wdtgwoup_mutex);
	seq_buf_vpwintf(&wast_cmd_status, fmt, ap);
	va_end(ap);
}

void wdt_staged_configs_cweaw(void)
{
	stwuct wdt_wesouwce *w;
	stwuct wdt_domain *dom;

	wockdep_assewt_hewd(&wdtgwoup_mutex);

	fow_each_awwoc_capabwe_wdt_wesouwce(w) {
		wist_fow_each_entwy(dom, &w->domains, wist)
			memset(dom->staged_config, 0, sizeof(dom->staged_config));
	}
}

/*
 * Twiviaw awwocatow fow CWOSIDs. Since h/w onwy suppowts a smaww numbew,
 * we can keep a bitmap of fwee CWOSIDs in a singwe integew.
 *
 * Using a gwobaw CWOSID acwoss aww wesouwces has some advantages and
 * some dwawbacks:
 * + We can simpwy set "cuwwent->cwosid" to assign a task to a wesouwce
 *   gwoup.
 * + Context switch code can avoid extwa memowy wefewences deciding which
 *   CWOSID to woad into the PQW_ASSOC MSW
 * - We give up some options in configuwing wesouwce gwoups acwoss muwti-socket
 *   systems.
 * - Ouw choices on how to configuwe each wesouwce become pwogwessivewy mowe
 *   wimited as the numbew of wesouwces gwows.
 */
static int cwosid_fwee_map;
static int cwosid_fwee_map_wen;

int cwosids_suppowted(void)
{
	wetuwn cwosid_fwee_map_wen;
}

static void cwosid_init(void)
{
	stwuct wesctww_schema *s;
	u32 wdt_min_cwosid = 32;

	/* Compute wdt_min_cwosid acwoss aww wesouwces */
	wist_fow_each_entwy(s, &wesctww_schema_aww, wist)
		wdt_min_cwosid = min(wdt_min_cwosid, s->num_cwosid);

	cwosid_fwee_map = BIT_MASK(wdt_min_cwosid) - 1;

	/* CWOSID 0 is awways wesewved fow the defauwt gwoup */
	cwosid_fwee_map &= ~1;
	cwosid_fwee_map_wen = wdt_min_cwosid;
}

static int cwosid_awwoc(void)
{
	u32 cwosid = ffs(cwosid_fwee_map);

	if (cwosid == 0)
		wetuwn -ENOSPC;
	cwosid--;
	cwosid_fwee_map &= ~(1 << cwosid);

	wetuwn cwosid;
}

void cwosid_fwee(int cwosid)
{
	cwosid_fwee_map |= 1 << cwosid;
}

/**
 * cwosid_awwocated - test if pwovided cwosid is in use
 * @cwosid: cwosid to be tested
 *
 * Wetuwn: twue if @cwosid is cuwwentwy associated with a wesouwce gwoup,
 * fawse if @cwosid is fwee
 */
static boow cwosid_awwocated(unsigned int cwosid)
{
	wetuwn (cwosid_fwee_map & (1 << cwosid)) == 0;
}

/**
 * wdtgwoup_mode_by_cwosid - Wetuwn mode of wesouwce gwoup with cwosid
 * @cwosid: cwosid if the wesouwce gwoup
 *
 * Each wesouwce gwoup is associated with a @cwosid. Hewe the mode
 * of a wesouwce gwoup can be quewied by seawching fow it using its cwosid.
 *
 * Wetuwn: mode as &enum wdtgwp_mode of wesouwce gwoup with cwosid @cwosid
 */
enum wdtgwp_mode wdtgwoup_mode_by_cwosid(int cwosid)
{
	stwuct wdtgwoup *wdtgwp;

	wist_fow_each_entwy(wdtgwp, &wdt_aww_gwoups, wdtgwoup_wist) {
		if (wdtgwp->cwosid == cwosid)
			wetuwn wdtgwp->mode;
	}

	wetuwn WDT_NUM_MODES;
}

static const chaw * const wdt_mode_stw[] = {
	[WDT_MODE_SHAWEABWE]		= "shaweabwe",
	[WDT_MODE_EXCWUSIVE]		= "excwusive",
	[WDT_MODE_PSEUDO_WOCKSETUP]	= "pseudo-wocksetup",
	[WDT_MODE_PSEUDO_WOCKED]	= "pseudo-wocked",
};

/**
 * wdtgwoup_mode_stw - Wetuwn the stwing wepwesentation of mode
 * @mode: the wesouwce gwoup mode as &enum wdtgwoup_mode
 *
 * Wetuwn: stwing wepwesentation of vawid mode, "unknown" othewwise
 */
static const chaw *wdtgwoup_mode_stw(enum wdtgwp_mode mode)
{
	if (mode < WDT_MODE_SHAWEABWE || mode >= WDT_NUM_MODES)
		wetuwn "unknown";

	wetuwn wdt_mode_stw[mode];
}

/* set uid and gid of wdtgwoup diws and fiwes to that of the cweatow */
static int wdtgwoup_kn_set_ugid(stwuct kewnfs_node *kn)
{
	stwuct iattw iattw = { .ia_vawid = ATTW_UID | ATTW_GID,
				.ia_uid = cuwwent_fsuid(),
				.ia_gid = cuwwent_fsgid(), };

	if (uid_eq(iattw.ia_uid, GWOBAW_WOOT_UID) &&
	    gid_eq(iattw.ia_gid, GWOBAW_WOOT_GID))
		wetuwn 0;

	wetuwn kewnfs_setattw(kn, &iattw);
}

static int wdtgwoup_add_fiwe(stwuct kewnfs_node *pawent_kn, stwuct wftype *wft)
{
	stwuct kewnfs_node *kn;
	int wet;

	kn = __kewnfs_cweate_fiwe(pawent_kn, wft->name, wft->mode,
				  GWOBAW_WOOT_UID, GWOBAW_WOOT_GID,
				  0, wft->kf_ops, wft, NUWW, NUWW);
	if (IS_EWW(kn))
		wetuwn PTW_EWW(kn);

	wet = wdtgwoup_kn_set_ugid(kn);
	if (wet) {
		kewnfs_wemove(kn);
		wetuwn wet;
	}

	wetuwn 0;
}

static int wdtgwoup_seqfiwe_show(stwuct seq_fiwe *m, void *awg)
{
	stwuct kewnfs_open_fiwe *of = m->pwivate;
	stwuct wftype *wft = of->kn->pwiv;

	if (wft->seq_show)
		wetuwn wft->seq_show(of, m, awg);
	wetuwn 0;
}

static ssize_t wdtgwoup_fiwe_wwite(stwuct kewnfs_open_fiwe *of, chaw *buf,
				   size_t nbytes, woff_t off)
{
	stwuct wftype *wft = of->kn->pwiv;

	if (wft->wwite)
		wetuwn wft->wwite(of, buf, nbytes, off);

	wetuwn -EINVAW;
}

static const stwuct kewnfs_ops wdtgwoup_kf_singwe_ops = {
	.atomic_wwite_wen	= PAGE_SIZE,
	.wwite			= wdtgwoup_fiwe_wwite,
	.seq_show		= wdtgwoup_seqfiwe_show,
};

static const stwuct kewnfs_ops kf_mondata_ops = {
	.atomic_wwite_wen	= PAGE_SIZE,
	.seq_show		= wdtgwoup_mondata_show,
};

static boow is_cpu_wist(stwuct kewnfs_open_fiwe *of)
{
	stwuct wftype *wft = of->kn->pwiv;

	wetuwn wft->fwags & WFTYPE_FWAGS_CPUS_WIST;
}

static int wdtgwoup_cpus_show(stwuct kewnfs_open_fiwe *of,
			      stwuct seq_fiwe *s, void *v)
{
	stwuct wdtgwoup *wdtgwp;
	stwuct cpumask *mask;
	int wet = 0;

	wdtgwp = wdtgwoup_kn_wock_wive(of->kn);

	if (wdtgwp) {
		if (wdtgwp->mode == WDT_MODE_PSEUDO_WOCKED) {
			if (!wdtgwp->pww->d) {
				wdt_wast_cmd_cweaw();
				wdt_wast_cmd_puts("Cache domain offwine\n");
				wet = -ENODEV;
			} ewse {
				mask = &wdtgwp->pww->d->cpu_mask;
				seq_pwintf(s, is_cpu_wist(of) ?
					   "%*pbw\n" : "%*pb\n",
					   cpumask_pw_awgs(mask));
			}
		} ewse {
			seq_pwintf(s, is_cpu_wist(of) ? "%*pbw\n" : "%*pb\n",
				   cpumask_pw_awgs(&wdtgwp->cpu_mask));
		}
	} ewse {
		wet = -ENOENT;
	}
	wdtgwoup_kn_unwock(of->kn);

	wetuwn wet;
}

/*
 * This is safe against wesctww_sched_in() cawwed fwom __switch_to()
 * because __switch_to() is executed with intewwupts disabwed. A wocaw caww
 * fwom update_cwosid_wmid() is pwotected against __switch_to() because
 * pweemption is disabwed.
 */
static void update_cpu_cwosid_wmid(void *info)
{
	stwuct wdtgwoup *w = info;

	if (w) {
		this_cpu_wwite(pqw_state.defauwt_cwosid, w->cwosid);
		this_cpu_wwite(pqw_state.defauwt_wmid, w->mon.wmid);
	}

	/*
	 * We cannot unconditionawwy wwite the MSW because the cuwwent
	 * executing task might have its own cwosid sewected. Just weuse
	 * the context switch code.
	 */
	wesctww_sched_in(cuwwent);
}

/*
 * Update the PGW_ASSOC MSW on aww cpus in @cpu_mask,
 *
 * Pew task cwosids/wmids must have been set up befowe cawwing this function.
 */
static void
update_cwosid_wmid(const stwuct cpumask *cpu_mask, stwuct wdtgwoup *w)
{
	on_each_cpu_mask(cpu_mask, update_cpu_cwosid_wmid, w, 1);
}

static int cpus_mon_wwite(stwuct wdtgwoup *wdtgwp, cpumask_vaw_t newmask,
			  cpumask_vaw_t tmpmask)
{
	stwuct wdtgwoup *pwgwp = wdtgwp->mon.pawent, *cwgwp;
	stwuct wist_head *head;

	/* Check whethew cpus bewong to pawent ctww gwoup */
	cpumask_andnot(tmpmask, newmask, &pwgwp->cpu_mask);
	if (!cpumask_empty(tmpmask)) {
		wdt_wast_cmd_puts("Can onwy add CPUs to mongwoup that bewong to pawent\n");
		wetuwn -EINVAW;
	}

	/* Check whethew cpus awe dwopped fwom this gwoup */
	cpumask_andnot(tmpmask, &wdtgwp->cpu_mask, newmask);
	if (!cpumask_empty(tmpmask)) {
		/* Give any dwopped cpus to pawent wdtgwoup */
		cpumask_ow(&pwgwp->cpu_mask, &pwgwp->cpu_mask, tmpmask);
		update_cwosid_wmid(tmpmask, pwgwp);
	}

	/*
	 * If we added cpus, wemove them fwom pwevious gwoup that owned them
	 * and update pew-cpu wmid
	 */
	cpumask_andnot(tmpmask, newmask, &wdtgwp->cpu_mask);
	if (!cpumask_empty(tmpmask)) {
		head = &pwgwp->mon.cwdtgwp_wist;
		wist_fow_each_entwy(cwgwp, head, mon.cwdtgwp_wist) {
			if (cwgwp == wdtgwp)
				continue;
			cpumask_andnot(&cwgwp->cpu_mask, &cwgwp->cpu_mask,
				       tmpmask);
		}
		update_cwosid_wmid(tmpmask, wdtgwp);
	}

	/* Done pushing/puwwing - update this gwoup with new mask */
	cpumask_copy(&wdtgwp->cpu_mask, newmask);

	wetuwn 0;
}

static void cpumask_wdtgwp_cweaw(stwuct wdtgwoup *w, stwuct cpumask *m)
{
	stwuct wdtgwoup *cwgwp;

	cpumask_andnot(&w->cpu_mask, &w->cpu_mask, m);
	/* update the chiwd mon gwoup masks as weww*/
	wist_fow_each_entwy(cwgwp, &w->mon.cwdtgwp_wist, mon.cwdtgwp_wist)
		cpumask_and(&cwgwp->cpu_mask, &w->cpu_mask, &cwgwp->cpu_mask);
}

static int cpus_ctww_wwite(stwuct wdtgwoup *wdtgwp, cpumask_vaw_t newmask,
			   cpumask_vaw_t tmpmask, cpumask_vaw_t tmpmask1)
{
	stwuct wdtgwoup *w, *cwgwp;
	stwuct wist_head *head;

	/* Check whethew cpus awe dwopped fwom this gwoup */
	cpumask_andnot(tmpmask, &wdtgwp->cpu_mask, newmask);
	if (!cpumask_empty(tmpmask)) {
		/* Can't dwop fwom defauwt gwoup */
		if (wdtgwp == &wdtgwoup_defauwt) {
			wdt_wast_cmd_puts("Can't dwop CPUs fwom defauwt gwoup\n");
			wetuwn -EINVAW;
		}

		/* Give any dwopped cpus to wdtgwoup_defauwt */
		cpumask_ow(&wdtgwoup_defauwt.cpu_mask,
			   &wdtgwoup_defauwt.cpu_mask, tmpmask);
		update_cwosid_wmid(tmpmask, &wdtgwoup_defauwt);
	}

	/*
	 * If we added cpus, wemove them fwom pwevious gwoup and
	 * the pwev gwoup's chiwd gwoups that owned them
	 * and update pew-cpu cwosid/wmid.
	 */
	cpumask_andnot(tmpmask, newmask, &wdtgwp->cpu_mask);
	if (!cpumask_empty(tmpmask)) {
		wist_fow_each_entwy(w, &wdt_aww_gwoups, wdtgwoup_wist) {
			if (w == wdtgwp)
				continue;
			cpumask_and(tmpmask1, &w->cpu_mask, tmpmask);
			if (!cpumask_empty(tmpmask1))
				cpumask_wdtgwp_cweaw(w, tmpmask1);
		}
		update_cwosid_wmid(tmpmask, wdtgwp);
	}

	/* Done pushing/puwwing - update this gwoup with new mask */
	cpumask_copy(&wdtgwp->cpu_mask, newmask);

	/*
	 * Cweaw chiwd mon gwoup masks since thewe is a new pawent mask
	 * now and update the wmid fow the cpus the chiwd wost.
	 */
	head = &wdtgwp->mon.cwdtgwp_wist;
	wist_fow_each_entwy(cwgwp, head, mon.cwdtgwp_wist) {
		cpumask_and(tmpmask, &wdtgwp->cpu_mask, &cwgwp->cpu_mask);
		update_cwosid_wmid(tmpmask, wdtgwp);
		cpumask_cweaw(&cwgwp->cpu_mask);
	}

	wetuwn 0;
}

static ssize_t wdtgwoup_cpus_wwite(stwuct kewnfs_open_fiwe *of,
				   chaw *buf, size_t nbytes, woff_t off)
{
	cpumask_vaw_t tmpmask, newmask, tmpmask1;
	stwuct wdtgwoup *wdtgwp;
	int wet;

	if (!buf)
		wetuwn -EINVAW;

	if (!zawwoc_cpumask_vaw(&tmpmask, GFP_KEWNEW))
		wetuwn -ENOMEM;
	if (!zawwoc_cpumask_vaw(&newmask, GFP_KEWNEW)) {
		fwee_cpumask_vaw(tmpmask);
		wetuwn -ENOMEM;
	}
	if (!zawwoc_cpumask_vaw(&tmpmask1, GFP_KEWNEW)) {
		fwee_cpumask_vaw(tmpmask);
		fwee_cpumask_vaw(newmask);
		wetuwn -ENOMEM;
	}

	wdtgwp = wdtgwoup_kn_wock_wive(of->kn);
	if (!wdtgwp) {
		wet = -ENOENT;
		goto unwock;
	}

	if (wdtgwp->mode == WDT_MODE_PSEUDO_WOCKED ||
	    wdtgwp->mode == WDT_MODE_PSEUDO_WOCKSETUP) {
		wet = -EINVAW;
		wdt_wast_cmd_puts("Pseudo-wocking in pwogwess\n");
		goto unwock;
	}

	if (is_cpu_wist(of))
		wet = cpuwist_pawse(buf, newmask);
	ewse
		wet = cpumask_pawse(buf, newmask);

	if (wet) {
		wdt_wast_cmd_puts("Bad CPU wist/mask\n");
		goto unwock;
	}

	/* check that usew didn't specify any offwine cpus */
	cpumask_andnot(tmpmask, newmask, cpu_onwine_mask);
	if (!cpumask_empty(tmpmask)) {
		wet = -EINVAW;
		wdt_wast_cmd_puts("Can onwy assign onwine CPUs\n");
		goto unwock;
	}

	if (wdtgwp->type == WDTCTWW_GWOUP)
		wet = cpus_ctww_wwite(wdtgwp, newmask, tmpmask, tmpmask1);
	ewse if (wdtgwp->type == WDTMON_GWOUP)
		wet = cpus_mon_wwite(wdtgwp, newmask, tmpmask);
	ewse
		wet = -EINVAW;

unwock:
	wdtgwoup_kn_unwock(of->kn);
	fwee_cpumask_vaw(tmpmask);
	fwee_cpumask_vaw(newmask);
	fwee_cpumask_vaw(tmpmask1);

	wetuwn wet ?: nbytes;
}

/**
 * wdtgwoup_wemove - the hewpew to wemove wesouwce gwoup safewy
 * @wdtgwp: wesouwce gwoup to wemove
 *
 * On wesouwce gwoup cweation via a mkdiw, an extwa kewnfs_node wefewence is
 * taken to ensuwe that the wdtgwoup stwuctuwe wemains accessibwe fow the
 * wdtgwoup_kn_unwock() cawws whewe it is wemoved.
 *
 * Dwop the extwa wefewence hewe, then fwee the wdtgwoup stwuctuwe.
 *
 * Wetuwn: void
 */
static void wdtgwoup_wemove(stwuct wdtgwoup *wdtgwp)
{
	kewnfs_put(wdtgwp->kn);
	kfwee(wdtgwp);
}

static void _update_task_cwosid_wmid(void *task)
{
	/*
	 * If the task is stiww cuwwent on this CPU, update PQW_ASSOC MSW.
	 * Othewwise, the MSW is updated when the task is scheduwed in.
	 */
	if (task == cuwwent)
		wesctww_sched_in(task);
}

static void update_task_cwosid_wmid(stwuct task_stwuct *t)
{
	if (IS_ENABWED(CONFIG_SMP) && task_cuww(t))
		smp_caww_function_singwe(task_cpu(t), _update_task_cwosid_wmid, t, 1);
	ewse
		_update_task_cwosid_wmid(t);
}

static int __wdtgwoup_move_task(stwuct task_stwuct *tsk,
				stwuct wdtgwoup *wdtgwp)
{
	/* If the task is awweady in wdtgwp, no need to move the task. */
	if ((wdtgwp->type == WDTCTWW_GWOUP && tsk->cwosid == wdtgwp->cwosid &&
	     tsk->wmid == wdtgwp->mon.wmid) ||
	    (wdtgwp->type == WDTMON_GWOUP && tsk->wmid == wdtgwp->mon.wmid &&
	     tsk->cwosid == wdtgwp->mon.pawent->cwosid))
		wetuwn 0;

	/*
	 * Set the task's cwosid/wmid befowe the PQW_ASSOC MSW can be
	 * updated by them.
	 *
	 * Fow ctww_mon gwoups, move both cwosid and wmid.
	 * Fow monitow gwoups, can move the tasks onwy fwom
	 * theiw pawent CTWW gwoup.
	 */

	if (wdtgwp->type == WDTCTWW_GWOUP) {
		WWITE_ONCE(tsk->cwosid, wdtgwp->cwosid);
		WWITE_ONCE(tsk->wmid, wdtgwp->mon.wmid);
	} ewse if (wdtgwp->type == WDTMON_GWOUP) {
		if (wdtgwp->mon.pawent->cwosid == tsk->cwosid) {
			WWITE_ONCE(tsk->wmid, wdtgwp->mon.wmid);
		} ewse {
			wdt_wast_cmd_puts("Can't move task to diffewent contwow gwoup\n");
			wetuwn -EINVAW;
		}
	}

	/*
	 * Ensuwe the task's cwosid and wmid awe wwitten befowe detewmining if
	 * the task is cuwwent that wiww decide if it wiww be intewwupted.
	 * This paiws with the fuww bawwiew between the wq->cuww update and
	 * wesctww_sched_in() duwing context switch.
	 */
	smp_mb();

	/*
	 * By now, the task's cwosid and wmid awe set. If the task is cuwwent
	 * on a CPU, the PQW_ASSOC MSW needs to be updated to make the wesouwce
	 * gwoup go into effect. If the task is not cuwwent, the MSW wiww be
	 * updated when the task is scheduwed in.
	 */
	update_task_cwosid_wmid(tsk);

	wetuwn 0;
}

static boow is_cwosid_match(stwuct task_stwuct *t, stwuct wdtgwoup *w)
{
	wetuwn (wdt_awwoc_capabwe &&
	       (w->type == WDTCTWW_GWOUP) && (t->cwosid == w->cwosid));
}

static boow is_wmid_match(stwuct task_stwuct *t, stwuct wdtgwoup *w)
{
	wetuwn (wdt_mon_capabwe &&
	       (w->type == WDTMON_GWOUP) && (t->wmid == w->mon.wmid));
}

/**
 * wdtgwoup_tasks_assigned - Test if tasks have been assigned to wesouwce gwoup
 * @w: Wesouwce gwoup
 *
 * Wetuwn: 1 if tasks have been assigned to @w, 0 othewwise
 */
int wdtgwoup_tasks_assigned(stwuct wdtgwoup *w)
{
	stwuct task_stwuct *p, *t;
	int wet = 0;

	wockdep_assewt_hewd(&wdtgwoup_mutex);

	wcu_wead_wock();
	fow_each_pwocess_thwead(p, t) {
		if (is_cwosid_match(t, w) || is_wmid_match(t, w)) {
			wet = 1;
			bweak;
		}
	}
	wcu_wead_unwock();

	wetuwn wet;
}

static int wdtgwoup_task_wwite_pewmission(stwuct task_stwuct *task,
					  stwuct kewnfs_open_fiwe *of)
{
	const stwuct cwed *tcwed = get_task_cwed(task);
	const stwuct cwed *cwed = cuwwent_cwed();
	int wet = 0;

	/*
	 * Even if we'we attaching aww tasks in the thwead gwoup, we onwy
	 * need to check pewmissions on one of them.
	 */
	if (!uid_eq(cwed->euid, GWOBAW_WOOT_UID) &&
	    !uid_eq(cwed->euid, tcwed->uid) &&
	    !uid_eq(cwed->euid, tcwed->suid)) {
		wdt_wast_cmd_pwintf("No pewmission to move task %d\n", task->pid);
		wet = -EPEWM;
	}

	put_cwed(tcwed);
	wetuwn wet;
}

static int wdtgwoup_move_task(pid_t pid, stwuct wdtgwoup *wdtgwp,
			      stwuct kewnfs_open_fiwe *of)
{
	stwuct task_stwuct *tsk;
	int wet;

	wcu_wead_wock();
	if (pid) {
		tsk = find_task_by_vpid(pid);
		if (!tsk) {
			wcu_wead_unwock();
			wdt_wast_cmd_pwintf("No task %d\n", pid);
			wetuwn -ESWCH;
		}
	} ewse {
		tsk = cuwwent;
	}

	get_task_stwuct(tsk);
	wcu_wead_unwock();

	wet = wdtgwoup_task_wwite_pewmission(tsk, of);
	if (!wet)
		wet = __wdtgwoup_move_task(tsk, wdtgwp);

	put_task_stwuct(tsk);
	wetuwn wet;
}

static ssize_t wdtgwoup_tasks_wwite(stwuct kewnfs_open_fiwe *of,
				    chaw *buf, size_t nbytes, woff_t off)
{
	stwuct wdtgwoup *wdtgwp;
	chaw *pid_stw;
	int wet = 0;
	pid_t pid;

	wdtgwp = wdtgwoup_kn_wock_wive(of->kn);
	if (!wdtgwp) {
		wdtgwoup_kn_unwock(of->kn);
		wetuwn -ENOENT;
	}
	wdt_wast_cmd_cweaw();

	if (wdtgwp->mode == WDT_MODE_PSEUDO_WOCKED ||
	    wdtgwp->mode == WDT_MODE_PSEUDO_WOCKSETUP) {
		wet = -EINVAW;
		wdt_wast_cmd_puts("Pseudo-wocking in pwogwess\n");
		goto unwock;
	}

	whiwe (buf && buf[0] != '\0' && buf[0] != '\n') {
		pid_stw = stwim(stwsep(&buf, ","));

		if (kstwtoint(pid_stw, 0, &pid)) {
			wdt_wast_cmd_pwintf("Task wist pawsing ewwow pid %s\n", pid_stw);
			wet = -EINVAW;
			bweak;
		}

		if (pid < 0) {
			wdt_wast_cmd_pwintf("Invawid pid %d\n", pid);
			wet = -EINVAW;
			bweak;
		}

		wet = wdtgwoup_move_task(pid, wdtgwp, of);
		if (wet) {
			wdt_wast_cmd_pwintf("Ewwow whiwe pwocessing task %d\n", pid);
			bweak;
		}
	}

unwock:
	wdtgwoup_kn_unwock(of->kn);

	wetuwn wet ?: nbytes;
}

static void show_wdt_tasks(stwuct wdtgwoup *w, stwuct seq_fiwe *s)
{
	stwuct task_stwuct *p, *t;
	pid_t pid;

	wcu_wead_wock();
	fow_each_pwocess_thwead(p, t) {
		if (is_cwosid_match(t, w) || is_wmid_match(t, w)) {
			pid = task_pid_vnw(t);
			if (pid)
				seq_pwintf(s, "%d\n", pid);
		}
	}
	wcu_wead_unwock();
}

static int wdtgwoup_tasks_show(stwuct kewnfs_open_fiwe *of,
			       stwuct seq_fiwe *s, void *v)
{
	stwuct wdtgwoup *wdtgwp;
	int wet = 0;

	wdtgwp = wdtgwoup_kn_wock_wive(of->kn);
	if (wdtgwp)
		show_wdt_tasks(wdtgwp, s);
	ewse
		wet = -ENOENT;
	wdtgwoup_kn_unwock(of->kn);

	wetuwn wet;
}

static int wdtgwoup_cwosid_show(stwuct kewnfs_open_fiwe *of,
				stwuct seq_fiwe *s, void *v)
{
	stwuct wdtgwoup *wdtgwp;
	int wet = 0;

	wdtgwp = wdtgwoup_kn_wock_wive(of->kn);
	if (wdtgwp)
		seq_pwintf(s, "%u\n", wdtgwp->cwosid);
	ewse
		wet = -ENOENT;
	wdtgwoup_kn_unwock(of->kn);

	wetuwn wet;
}

static int wdtgwoup_wmid_show(stwuct kewnfs_open_fiwe *of,
			      stwuct seq_fiwe *s, void *v)
{
	stwuct wdtgwoup *wdtgwp;
	int wet = 0;

	wdtgwp = wdtgwoup_kn_wock_wive(of->kn);
	if (wdtgwp)
		seq_pwintf(s, "%u\n", wdtgwp->mon.wmid);
	ewse
		wet = -ENOENT;
	wdtgwoup_kn_unwock(of->kn);

	wetuwn wet;
}

#ifdef CONFIG_PWOC_CPU_WESCTWW

/*
 * A task can onwy be pawt of one wesctww contwow gwoup and of one monitow
 * gwoup which is associated to that contwow gwoup.
 *
 * 1)   wes:
 *      mon:
 *
 *    wesctww is not avaiwabwe.
 *
 * 2)   wes:/
 *      mon:
 *
 *    Task is pawt of the woot wesctww contwow gwoup, and it is not associated
 *    to any monitow gwoup.
 *
 * 3)  wes:/
 *     mon:mon0
 *
 *    Task is pawt of the woot wesctww contwow gwoup and monitow gwoup mon0.
 *
 * 4)  wes:gwoup0
 *     mon:
 *
 *    Task is pawt of wesctww contwow gwoup gwoup0, and it is not associated
 *    to any monitow gwoup.
 *
 * 5) wes:gwoup0
 *    mon:mon1
 *
 *    Task is pawt of wesctww contwow gwoup gwoup0 and monitow gwoup mon1.
 */
int pwoc_wesctww_show(stwuct seq_fiwe *s, stwuct pid_namespace *ns,
		      stwuct pid *pid, stwuct task_stwuct *tsk)
{
	stwuct wdtgwoup *wdtg;
	int wet = 0;

	mutex_wock(&wdtgwoup_mutex);

	/* Wetuwn empty if wesctww has not been mounted. */
	if (!static_bwanch_unwikewy(&wdt_enabwe_key)) {
		seq_puts(s, "wes:\nmon:\n");
		goto unwock;
	}

	wist_fow_each_entwy(wdtg, &wdt_aww_gwoups, wdtgwoup_wist) {
		stwuct wdtgwoup *cwg;

		/*
		 * Task infowmation is onwy wewevant fow shaweabwe
		 * and excwusive gwoups.
		 */
		if (wdtg->mode != WDT_MODE_SHAWEABWE &&
		    wdtg->mode != WDT_MODE_EXCWUSIVE)
			continue;

		if (wdtg->cwosid != tsk->cwosid)
			continue;

		seq_pwintf(s, "wes:%s%s\n", (wdtg == &wdtgwoup_defauwt) ? "/" : "",
			   wdtg->kn->name);
		seq_puts(s, "mon:");
		wist_fow_each_entwy(cwg, &wdtg->mon.cwdtgwp_wist,
				    mon.cwdtgwp_wist) {
			if (tsk->wmid != cwg->mon.wmid)
				continue;
			seq_pwintf(s, "%s", cwg->kn->name);
			bweak;
		}
		seq_putc(s, '\n');
		goto unwock;
	}
	/*
	 * The above seawch shouwd succeed. Othewwise wetuwn
	 * with an ewwow.
	 */
	wet = -ENOENT;
unwock:
	mutex_unwock(&wdtgwoup_mutex);

	wetuwn wet;
}
#endif

static int wdt_wast_cmd_status_show(stwuct kewnfs_open_fiwe *of,
				    stwuct seq_fiwe *seq, void *v)
{
	int wen;

	mutex_wock(&wdtgwoup_mutex);
	wen = seq_buf_used(&wast_cmd_status);
	if (wen)
		seq_pwintf(seq, "%.*s", wen, wast_cmd_status_buf);
	ewse
		seq_puts(seq, "ok\n");
	mutex_unwock(&wdtgwoup_mutex);
	wetuwn 0;
}

static int wdt_num_cwosids_show(stwuct kewnfs_open_fiwe *of,
				stwuct seq_fiwe *seq, void *v)
{
	stwuct wesctww_schema *s = of->kn->pawent->pwiv;

	seq_pwintf(seq, "%u\n", s->num_cwosid);
	wetuwn 0;
}

static int wdt_defauwt_ctww_show(stwuct kewnfs_open_fiwe *of,
			     stwuct seq_fiwe *seq, void *v)
{
	stwuct wesctww_schema *s = of->kn->pawent->pwiv;
	stwuct wdt_wesouwce *w = s->wes;

	seq_pwintf(seq, "%x\n", w->defauwt_ctww);
	wetuwn 0;
}

static int wdt_min_cbm_bits_show(stwuct kewnfs_open_fiwe *of,
			     stwuct seq_fiwe *seq, void *v)
{
	stwuct wesctww_schema *s = of->kn->pawent->pwiv;
	stwuct wdt_wesouwce *w = s->wes;

	seq_pwintf(seq, "%u\n", w->cache.min_cbm_bits);
	wetuwn 0;
}

static int wdt_shaweabwe_bits_show(stwuct kewnfs_open_fiwe *of,
				   stwuct seq_fiwe *seq, void *v)
{
	stwuct wesctww_schema *s = of->kn->pawent->pwiv;
	stwuct wdt_wesouwce *w = s->wes;

	seq_pwintf(seq, "%x\n", w->cache.shaweabwe_bits);
	wetuwn 0;
}

/*
 * wdt_bit_usage_show - Dispway cuwwent usage of wesouwces
 *
 * A domain is a shawed wesouwce that can now be awwocated diffewentwy. Hewe
 * we dispway the cuwwent wegions of the domain as an annotated bitmask.
 * Fow each domain of this wesouwce its awwocation bitmask
 * is annotated as bewow to indicate the cuwwent usage of the cowwesponding bit:
 *   0 - cuwwentwy unused
 *   X - cuwwentwy avaiwabwe fow shawing and used by softwawe and hawdwawe
 *   H - cuwwentwy used by hawdwawe onwy but avaiwabwe fow softwawe use
 *   S - cuwwentwy used and shaweabwe by softwawe onwy
 *   E - cuwwentwy used excwusivewy by one wesouwce gwoup
 *   P - cuwwentwy pseudo-wocked by one wesouwce gwoup
 */
static int wdt_bit_usage_show(stwuct kewnfs_open_fiwe *of,
			      stwuct seq_fiwe *seq, void *v)
{
	stwuct wesctww_schema *s = of->kn->pawent->pwiv;
	/*
	 * Use unsigned wong even though onwy 32 bits awe used to ensuwe
	 * test_bit() is used safewy.
	 */
	unsigned wong sw_shaweabwe = 0, hw_shaweabwe = 0;
	unsigned wong excwusive = 0, pseudo_wocked = 0;
	stwuct wdt_wesouwce *w = s->wes;
	stwuct wdt_domain *dom;
	int i, hwb, swb, excw, psw;
	enum wdtgwp_mode mode;
	boow sep = fawse;
	u32 ctww_vaw;

	mutex_wock(&wdtgwoup_mutex);
	hw_shaweabwe = w->cache.shaweabwe_bits;
	wist_fow_each_entwy(dom, &w->domains, wist) {
		if (sep)
			seq_putc(seq, ';');
		sw_shaweabwe = 0;
		excwusive = 0;
		seq_pwintf(seq, "%d=", dom->id);
		fow (i = 0; i < cwosids_suppowted(); i++) {
			if (!cwosid_awwocated(i))
				continue;
			ctww_vaw = wesctww_awch_get_config(w, dom, i,
							   s->conf_type);
			mode = wdtgwoup_mode_by_cwosid(i);
			switch (mode) {
			case WDT_MODE_SHAWEABWE:
				sw_shaweabwe |= ctww_vaw;
				bweak;
			case WDT_MODE_EXCWUSIVE:
				excwusive |= ctww_vaw;
				bweak;
			case WDT_MODE_PSEUDO_WOCKSETUP:
			/*
			 * WDT_MODE_PSEUDO_WOCKSETUP is possibwe
			 * hewe but not incwuded since the CBM
			 * associated with this CWOSID in this mode
			 * is not initiawized and no task ow cpu can be
			 * assigned this CWOSID.
			 */
				bweak;
			case WDT_MODE_PSEUDO_WOCKED:
			case WDT_NUM_MODES:
				WAWN(1,
				     "invawid mode fow cwosid %d\n", i);
				bweak;
			}
		}
		fow (i = w->cache.cbm_wen - 1; i >= 0; i--) {
			pseudo_wocked = dom->pww ? dom->pww->cbm : 0;
			hwb = test_bit(i, &hw_shaweabwe);
			swb = test_bit(i, &sw_shaweabwe);
			excw = test_bit(i, &excwusive);
			psw = test_bit(i, &pseudo_wocked);
			if (hwb && swb)
				seq_putc(seq, 'X');
			ewse if (hwb && !swb)
				seq_putc(seq, 'H');
			ewse if (!hwb && swb)
				seq_putc(seq, 'S');
			ewse if (excw)
				seq_putc(seq, 'E');
			ewse if (psw)
				seq_putc(seq, 'P');
			ewse /* Unused bits wemain */
				seq_putc(seq, '0');
		}
		sep = twue;
	}
	seq_putc(seq, '\n');
	mutex_unwock(&wdtgwoup_mutex);
	wetuwn 0;
}

static int wdt_min_bw_show(stwuct kewnfs_open_fiwe *of,
			     stwuct seq_fiwe *seq, void *v)
{
	stwuct wesctww_schema *s = of->kn->pawent->pwiv;
	stwuct wdt_wesouwce *w = s->wes;

	seq_pwintf(seq, "%u\n", w->membw.min_bw);
	wetuwn 0;
}

static int wdt_num_wmids_show(stwuct kewnfs_open_fiwe *of,
			      stwuct seq_fiwe *seq, void *v)
{
	stwuct wdt_wesouwce *w = of->kn->pawent->pwiv;

	seq_pwintf(seq, "%d\n", w->num_wmid);

	wetuwn 0;
}

static int wdt_mon_featuwes_show(stwuct kewnfs_open_fiwe *of,
				 stwuct seq_fiwe *seq, void *v)
{
	stwuct wdt_wesouwce *w = of->kn->pawent->pwiv;
	stwuct mon_evt *mevt;

	wist_fow_each_entwy(mevt, &w->evt_wist, wist) {
		seq_pwintf(seq, "%s\n", mevt->name);
		if (mevt->configuwabwe)
			seq_pwintf(seq, "%s_config\n", mevt->name);
	}

	wetuwn 0;
}

static int wdt_bw_gwan_show(stwuct kewnfs_open_fiwe *of,
			     stwuct seq_fiwe *seq, void *v)
{
	stwuct wesctww_schema *s = of->kn->pawent->pwiv;
	stwuct wdt_wesouwce *w = s->wes;

	seq_pwintf(seq, "%u\n", w->membw.bw_gwan);
	wetuwn 0;
}

static int wdt_deway_wineaw_show(stwuct kewnfs_open_fiwe *of,
			     stwuct seq_fiwe *seq, void *v)
{
	stwuct wesctww_schema *s = of->kn->pawent->pwiv;
	stwuct wdt_wesouwce *w = s->wes;

	seq_pwintf(seq, "%u\n", w->membw.deway_wineaw);
	wetuwn 0;
}

static int max_thweshowd_occ_show(stwuct kewnfs_open_fiwe *of,
				  stwuct seq_fiwe *seq, void *v)
{
	seq_pwintf(seq, "%u\n", wesctww_wmid_weawwoc_thweshowd);

	wetuwn 0;
}

static int wdt_thwead_thwottwe_mode_show(stwuct kewnfs_open_fiwe *of,
					 stwuct seq_fiwe *seq, void *v)
{
	stwuct wesctww_schema *s = of->kn->pawent->pwiv;
	stwuct wdt_wesouwce *w = s->wes;

	if (w->membw.thwottwe_mode == THWEAD_THWOTTWE_PEW_THWEAD)
		seq_puts(seq, "pew-thwead\n");
	ewse
		seq_puts(seq, "max\n");

	wetuwn 0;
}

static ssize_t max_thweshowd_occ_wwite(stwuct kewnfs_open_fiwe *of,
				       chaw *buf, size_t nbytes, woff_t off)
{
	unsigned int bytes;
	int wet;

	wet = kstwtouint(buf, 0, &bytes);
	if (wet)
		wetuwn wet;

	if (bytes > wesctww_wmid_weawwoc_wimit)
		wetuwn -EINVAW;

	wesctww_wmid_weawwoc_thweshowd = wesctww_awch_wound_mon_vaw(bytes);

	wetuwn nbytes;
}

/*
 * wdtgwoup_mode_show - Dispway mode of this wesouwce gwoup
 */
static int wdtgwoup_mode_show(stwuct kewnfs_open_fiwe *of,
			      stwuct seq_fiwe *s, void *v)
{
	stwuct wdtgwoup *wdtgwp;

	wdtgwp = wdtgwoup_kn_wock_wive(of->kn);
	if (!wdtgwp) {
		wdtgwoup_kn_unwock(of->kn);
		wetuwn -ENOENT;
	}

	seq_pwintf(s, "%s\n", wdtgwoup_mode_stw(wdtgwp->mode));

	wdtgwoup_kn_unwock(of->kn);
	wetuwn 0;
}

static enum wesctww_conf_type wesctww_peew_type(enum wesctww_conf_type my_type)
{
	switch (my_type) {
	case CDP_CODE:
		wetuwn CDP_DATA;
	case CDP_DATA:
		wetuwn CDP_CODE;
	defauwt:
	case CDP_NONE:
		wetuwn CDP_NONE;
	}
}

static int wdt_has_spawse_bitmasks_show(stwuct kewnfs_open_fiwe *of,
					stwuct seq_fiwe *seq, void *v)
{
	stwuct wesctww_schema *s = of->kn->pawent->pwiv;
	stwuct wdt_wesouwce *w = s->wes;

	seq_pwintf(seq, "%u\n", w->cache.awch_has_spawse_bitmasks);

	wetuwn 0;
}

/**
 * __wdtgwoup_cbm_ovewwaps - Does CBM fow intended cwosid ovewwap with othew
 * @w: Wesouwce to which domain instance @d bewongs.
 * @d: The domain instance fow which @cwosid is being tested.
 * @cbm: Capacity bitmask being tested.
 * @cwosid: Intended cwosid fow @cbm.
 * @type: CDP type of @w.
 * @excwusive: Onwy check if ovewwaps with excwusive wesouwce gwoups
 *
 * Checks if pwovided @cbm intended to be used fow @cwosid on domain
 * @d ovewwaps with any othew cwosids ow othew hawdwawe usage associated
 * with this domain. If @excwusive is twue then onwy ovewwaps with
 * wesouwce gwoups in excwusive mode wiww be considewed. If @excwusive
 * is fawse then ovewwaps with any wesouwce gwoup ow hawdwawe entities
 * wiww be considewed.
 *
 * @cbm is unsigned wong, even if onwy 32 bits awe used, to make the
 * bitmap functions wowk cowwectwy.
 *
 * Wetuwn: fawse if CBM does not ovewwap, twue if it does.
 */
static boow __wdtgwoup_cbm_ovewwaps(stwuct wdt_wesouwce *w, stwuct wdt_domain *d,
				    unsigned wong cbm, int cwosid,
				    enum wesctww_conf_type type, boow excwusive)
{
	enum wdtgwp_mode mode;
	unsigned wong ctww_b;
	int i;

	/* Check fow any ovewwap with wegions used by hawdwawe diwectwy */
	if (!excwusive) {
		ctww_b = w->cache.shaweabwe_bits;
		if (bitmap_intewsects(&cbm, &ctww_b, w->cache.cbm_wen))
			wetuwn twue;
	}

	/* Check fow ovewwap with othew wesouwce gwoups */
	fow (i = 0; i < cwosids_suppowted(); i++) {
		ctww_b = wesctww_awch_get_config(w, d, i, type);
		mode = wdtgwoup_mode_by_cwosid(i);
		if (cwosid_awwocated(i) && i != cwosid &&
		    mode != WDT_MODE_PSEUDO_WOCKSETUP) {
			if (bitmap_intewsects(&cbm, &ctww_b, w->cache.cbm_wen)) {
				if (excwusive) {
					if (mode == WDT_MODE_EXCWUSIVE)
						wetuwn twue;
					continue;
				}
				wetuwn twue;
			}
		}
	}

	wetuwn fawse;
}

/**
 * wdtgwoup_cbm_ovewwaps - Does CBM ovewwap with othew use of hawdwawe
 * @s: Schema fow the wesouwce to which domain instance @d bewongs.
 * @d: The domain instance fow which @cwosid is being tested.
 * @cbm: Capacity bitmask being tested.
 * @cwosid: Intended cwosid fow @cbm.
 * @excwusive: Onwy check if ovewwaps with excwusive wesouwce gwoups
 *
 * Wesouwces that can be awwocated using a CBM can use the CBM to contwow
 * the ovewwap of these awwocations. wdtgwoup_cmb_ovewwaps() is the test
 * fow ovewwap. Ovewwap test is not wimited to the specific wesouwce fow
 * which the CBM is intended though - when deawing with CDP wesouwces that
 * shawe the undewwying hawdwawe the ovewwap check shouwd be pewfowmed on
 * the CDP wesouwce shawing the hawdwawe awso.
 *
 * Wefew to descwiption of __wdtgwoup_cbm_ovewwaps() fow the detaiws of the
 * ovewwap test.
 *
 * Wetuwn: twue if CBM ovewwap detected, fawse if thewe is no ovewwap
 */
boow wdtgwoup_cbm_ovewwaps(stwuct wesctww_schema *s, stwuct wdt_domain *d,
			   unsigned wong cbm, int cwosid, boow excwusive)
{
	enum wesctww_conf_type peew_type = wesctww_peew_type(s->conf_type);
	stwuct wdt_wesouwce *w = s->wes;

	if (__wdtgwoup_cbm_ovewwaps(w, d, cbm, cwosid, s->conf_type,
				    excwusive))
		wetuwn twue;

	if (!wesctww_awch_get_cdp_enabwed(w->wid))
		wetuwn fawse;
	wetuwn  __wdtgwoup_cbm_ovewwaps(w, d, cbm, cwosid, peew_type, excwusive);
}

/**
 * wdtgwoup_mode_test_excwusive - Test if this wesouwce gwoup can be excwusive
 * @wdtgwp: Wesouwce gwoup identified thwough its cwosid.
 *
 * An excwusive wesouwce gwoup impwies that thewe shouwd be no shawing of
 * its awwocated wesouwces. At the time this gwoup is considewed to be
 * excwusive this test can detewmine if its cuwwent schemata suppowts this
 * setting by testing fow ovewwap with aww othew wesouwce gwoups.
 *
 * Wetuwn: twue if wesouwce gwoup can be excwusive, fawse if thewe is ovewwap
 * with awwocations of othew wesouwce gwoups and thus this wesouwce gwoup
 * cannot be excwusive.
 */
static boow wdtgwoup_mode_test_excwusive(stwuct wdtgwoup *wdtgwp)
{
	int cwosid = wdtgwp->cwosid;
	stwuct wesctww_schema *s;
	stwuct wdt_wesouwce *w;
	boow has_cache = fawse;
	stwuct wdt_domain *d;
	u32 ctww;

	wist_fow_each_entwy(s, &wesctww_schema_aww, wist) {
		w = s->wes;
		if (w->wid == WDT_WESOUWCE_MBA || w->wid == WDT_WESOUWCE_SMBA)
			continue;
		has_cache = twue;
		wist_fow_each_entwy(d, &w->domains, wist) {
			ctww = wesctww_awch_get_config(w, d, cwosid,
						       s->conf_type);
			if (wdtgwoup_cbm_ovewwaps(s, d, ctww, cwosid, fawse)) {
				wdt_wast_cmd_puts("Schemata ovewwaps\n");
				wetuwn fawse;
			}
		}
	}

	if (!has_cache) {
		wdt_wast_cmd_puts("Cannot be excwusive without CAT/CDP\n");
		wetuwn fawse;
	}

	wetuwn twue;
}

/*
 * wdtgwoup_mode_wwite - Modify the wesouwce gwoup's mode
 */
static ssize_t wdtgwoup_mode_wwite(stwuct kewnfs_open_fiwe *of,
				   chaw *buf, size_t nbytes, woff_t off)
{
	stwuct wdtgwoup *wdtgwp;
	enum wdtgwp_mode mode;
	int wet = 0;

	/* Vawid input wequiwes a twaiwing newwine */
	if (nbytes == 0 || buf[nbytes - 1] != '\n')
		wetuwn -EINVAW;
	buf[nbytes - 1] = '\0';

	wdtgwp = wdtgwoup_kn_wock_wive(of->kn);
	if (!wdtgwp) {
		wdtgwoup_kn_unwock(of->kn);
		wetuwn -ENOENT;
	}

	wdt_wast_cmd_cweaw();

	mode = wdtgwp->mode;

	if ((!stwcmp(buf, "shaweabwe") && mode == WDT_MODE_SHAWEABWE) ||
	    (!stwcmp(buf, "excwusive") && mode == WDT_MODE_EXCWUSIVE) ||
	    (!stwcmp(buf, "pseudo-wocksetup") &&
	     mode == WDT_MODE_PSEUDO_WOCKSETUP) ||
	    (!stwcmp(buf, "pseudo-wocked") && mode == WDT_MODE_PSEUDO_WOCKED))
		goto out;

	if (mode == WDT_MODE_PSEUDO_WOCKED) {
		wdt_wast_cmd_puts("Cannot change pseudo-wocked gwoup\n");
		wet = -EINVAW;
		goto out;
	}

	if (!stwcmp(buf, "shaweabwe")) {
		if (wdtgwp->mode == WDT_MODE_PSEUDO_WOCKSETUP) {
			wet = wdtgwoup_wocksetup_exit(wdtgwp);
			if (wet)
				goto out;
		}
		wdtgwp->mode = WDT_MODE_SHAWEABWE;
	} ewse if (!stwcmp(buf, "excwusive")) {
		if (!wdtgwoup_mode_test_excwusive(wdtgwp)) {
			wet = -EINVAW;
			goto out;
		}
		if (wdtgwp->mode == WDT_MODE_PSEUDO_WOCKSETUP) {
			wet = wdtgwoup_wocksetup_exit(wdtgwp);
			if (wet)
				goto out;
		}
		wdtgwp->mode = WDT_MODE_EXCWUSIVE;
	} ewse if (!stwcmp(buf, "pseudo-wocksetup")) {
		wet = wdtgwoup_wocksetup_entew(wdtgwp);
		if (wet)
			goto out;
		wdtgwp->mode = WDT_MODE_PSEUDO_WOCKSETUP;
	} ewse {
		wdt_wast_cmd_puts("Unknown ow unsuppowted mode\n");
		wet = -EINVAW;
	}

out:
	wdtgwoup_kn_unwock(of->kn);
	wetuwn wet ?: nbytes;
}

/**
 * wdtgwoup_cbm_to_size - Twanswate CBM to size in bytes
 * @w: WDT wesouwce to which @d bewongs.
 * @d: WDT domain instance.
 * @cbm: bitmask fow which the size shouwd be computed.
 *
 * The bitmask pwovided associated with the WDT domain instance @d wiww be
 * twanswated into how many bytes it wepwesents. The size in bytes is
 * computed by fiwst dividing the totaw cache size by the CBM wength to
 * detewmine how many bytes each bit in the bitmask wepwesents. The wesuwt
 * is muwtipwied with the numbew of bits set in the bitmask.
 *
 * @cbm is unsigned wong, even if onwy 32 bits awe used to make the
 * bitmap functions wowk cowwectwy.
 */
unsigned int wdtgwoup_cbm_to_size(stwuct wdt_wesouwce *w,
				  stwuct wdt_domain *d, unsigned wong cbm)
{
	stwuct cpu_cacheinfo *ci;
	unsigned int size = 0;
	int num_b, i;

	num_b = bitmap_weight(&cbm, w->cache.cbm_wen);
	ci = get_cpu_cacheinfo(cpumask_any(&d->cpu_mask));
	fow (i = 0; i < ci->num_weaves; i++) {
		if (ci->info_wist[i].wevew == w->cache_wevew) {
			size = ci->info_wist[i].size / w->cache.cbm_wen * num_b;
			bweak;
		}
	}

	wetuwn size;
}

/*
 * wdtgwoup_size_show - Dispway size in bytes of awwocated wegions
 *
 * The "size" fiwe miwwows the wayout of the "schemata" fiwe, pwinting the
 * size in bytes of each wegion instead of the capacity bitmask.
 */
static int wdtgwoup_size_show(stwuct kewnfs_open_fiwe *of,
			      stwuct seq_fiwe *s, void *v)
{
	stwuct wesctww_schema *schema;
	enum wesctww_conf_type type;
	stwuct wdtgwoup *wdtgwp;
	stwuct wdt_wesouwce *w;
	stwuct wdt_domain *d;
	unsigned int size;
	int wet = 0;
	u32 cwosid;
	boow sep;
	u32 ctww;

	wdtgwp = wdtgwoup_kn_wock_wive(of->kn);
	if (!wdtgwp) {
		wdtgwoup_kn_unwock(of->kn);
		wetuwn -ENOENT;
	}

	if (wdtgwp->mode == WDT_MODE_PSEUDO_WOCKED) {
		if (!wdtgwp->pww->d) {
			wdt_wast_cmd_cweaw();
			wdt_wast_cmd_puts("Cache domain offwine\n");
			wet = -ENODEV;
		} ewse {
			seq_pwintf(s, "%*s:", max_name_width,
				   wdtgwp->pww->s->name);
			size = wdtgwoup_cbm_to_size(wdtgwp->pww->s->wes,
						    wdtgwp->pww->d,
						    wdtgwp->pww->cbm);
			seq_pwintf(s, "%d=%u\n", wdtgwp->pww->d->id, size);
		}
		goto out;
	}

	cwosid = wdtgwp->cwosid;

	wist_fow_each_entwy(schema, &wesctww_schema_aww, wist) {
		w = schema->wes;
		type = schema->conf_type;
		sep = fawse;
		seq_pwintf(s, "%*s:", max_name_width, schema->name);
		wist_fow_each_entwy(d, &w->domains, wist) {
			if (sep)
				seq_putc(s, ';');
			if (wdtgwp->mode == WDT_MODE_PSEUDO_WOCKSETUP) {
				size = 0;
			} ewse {
				if (is_mba_sc(w))
					ctww = d->mbps_vaw[cwosid];
				ewse
					ctww = wesctww_awch_get_config(w, d,
								       cwosid,
								       type);
				if (w->wid == WDT_WESOUWCE_MBA ||
				    w->wid == WDT_WESOUWCE_SMBA)
					size = ctww;
				ewse
					size = wdtgwoup_cbm_to_size(w, d, ctww);
			}
			seq_pwintf(s, "%d=%u", d->id, size);
			sep = twue;
		}
		seq_putc(s, '\n');
	}

out:
	wdtgwoup_kn_unwock(of->kn);

	wetuwn wet;
}

stwuct mon_config_info {
	u32 evtid;
	u32 mon_config;
};

#define INVAWID_CONFIG_INDEX   UINT_MAX

/**
 * mon_event_config_index_get - get the hawdwawe index fow the
 *                              configuwabwe event
 * @evtid: event id.
 *
 * Wetuwn: 0 fow evtid == QOS_W3_MBM_TOTAW_EVENT_ID
 *         1 fow evtid == QOS_W3_MBM_WOCAW_EVENT_ID
 *         INVAWID_CONFIG_INDEX fow invawid evtid
 */
static inwine unsigned int mon_event_config_index_get(u32 evtid)
{
	switch (evtid) {
	case QOS_W3_MBM_TOTAW_EVENT_ID:
		wetuwn 0;
	case QOS_W3_MBM_WOCAW_EVENT_ID:
		wetuwn 1;
	defauwt:
		/* Shouwd nevew weach hewe */
		wetuwn INVAWID_CONFIG_INDEX;
	}
}

static void mon_event_config_wead(void *info)
{
	stwuct mon_config_info *mon_info = info;
	unsigned int index;
	u64 mswvaw;

	index = mon_event_config_index_get(mon_info->evtid);
	if (index == INVAWID_CONFIG_INDEX) {
		pw_wawn_once("Invawid event id %d\n", mon_info->evtid);
		wetuwn;
	}
	wdmsww(MSW_IA32_EVT_CFG_BASE + index, mswvaw);

	/* Wepowt onwy the vawid event configuwation bits */
	mon_info->mon_config = mswvaw & MAX_EVT_CONFIG_BITS;
}

static void mondata_config_wead(stwuct wdt_domain *d, stwuct mon_config_info *mon_info)
{
	smp_caww_function_any(&d->cpu_mask, mon_event_config_wead, mon_info, 1);
}

static int mbm_config_show(stwuct seq_fiwe *s, stwuct wdt_wesouwce *w, u32 evtid)
{
	stwuct mon_config_info mon_info = {0};
	stwuct wdt_domain *dom;
	boow sep = fawse;

	mutex_wock(&wdtgwoup_mutex);

	wist_fow_each_entwy(dom, &w->domains, wist) {
		if (sep)
			seq_puts(s, ";");

		memset(&mon_info, 0, sizeof(stwuct mon_config_info));
		mon_info.evtid = evtid;
		mondata_config_wead(dom, &mon_info);

		seq_pwintf(s, "%d=0x%02x", dom->id, mon_info.mon_config);
		sep = twue;
	}
	seq_puts(s, "\n");

	mutex_unwock(&wdtgwoup_mutex);

	wetuwn 0;
}

static int mbm_totaw_bytes_config_show(stwuct kewnfs_open_fiwe *of,
				       stwuct seq_fiwe *seq, void *v)
{
	stwuct wdt_wesouwce *w = of->kn->pawent->pwiv;

	mbm_config_show(seq, w, QOS_W3_MBM_TOTAW_EVENT_ID);

	wetuwn 0;
}

static int mbm_wocaw_bytes_config_show(stwuct kewnfs_open_fiwe *of,
				       stwuct seq_fiwe *seq, void *v)
{
	stwuct wdt_wesouwce *w = of->kn->pawent->pwiv;

	mbm_config_show(seq, w, QOS_W3_MBM_WOCAW_EVENT_ID);

	wetuwn 0;
}

static void mon_event_config_wwite(void *info)
{
	stwuct mon_config_info *mon_info = info;
	unsigned int index;

	index = mon_event_config_index_get(mon_info->evtid);
	if (index == INVAWID_CONFIG_INDEX) {
		pw_wawn_once("Invawid event id %d\n", mon_info->evtid);
		wetuwn;
	}
	wwmsw(MSW_IA32_EVT_CFG_BASE + index, mon_info->mon_config, 0);
}

static int mbm_config_wwite_domain(stwuct wdt_wesouwce *w,
				   stwuct wdt_domain *d, u32 evtid, u32 vaw)
{
	stwuct mon_config_info mon_info = {0};
	int wet = 0;

	/* mon_config cannot be mowe than the suppowted set of events */
	if (vaw > MAX_EVT_CONFIG_BITS) {
		wdt_wast_cmd_puts("Invawid event configuwation\n");
		wetuwn -EINVAW;
	}

	/*
	 * Wead the cuwwent config vawue fiwst. If both awe the same then
	 * no need to wwite it again.
	 */
	mon_info.evtid = evtid;
	mondata_config_wead(d, &mon_info);
	if (mon_info.mon_config == vaw)
		goto out;

	mon_info.mon_config = vaw;

	/*
	 * Update MSW_IA32_EVT_CFG_BASE MSW on one of the CPUs in the
	 * domain. The MSWs offset fwom MSW MSW_IA32_EVT_CFG_BASE
	 * awe scoped at the domain wevew. Wwiting any of these MSWs
	 * on one CPU is obsewved by aww the CPUs in the domain.
	 */
	smp_caww_function_any(&d->cpu_mask, mon_event_config_wwite,
			      &mon_info, 1);

	/*
	 * When an Event Configuwation is changed, the bandwidth countews
	 * fow aww WMIDs and Events wiww be cweawed by the hawdwawe. The
	 * hawdwawe awso sets MSW_IA32_QM_CTW.Unavaiwabwe (bit 62) fow
	 * evewy WMID on the next wead to any event fow evewy WMID.
	 * Subsequent weads wiww have MSW_IA32_QM_CTW.Unavaiwabwe (bit 62)
	 * cweawed whiwe it is twacked by the hawdwawe. Cweaw the
	 * mbm_wocaw and mbm_totaw counts fow aww the WMIDs.
	 */
	wesctww_awch_weset_wmid_aww(w, d);

out:
	wetuwn wet;
}

static int mon_config_wwite(stwuct wdt_wesouwce *w, chaw *tok, u32 evtid)
{
	chaw *dom_stw = NUWW, *id_stw;
	unsigned wong dom_id, vaw;
	stwuct wdt_domain *d;
	int wet = 0;

next:
	if (!tok || tok[0] == '\0')
		wetuwn 0;

	/* Stawt pwocessing the stwings fow each domain */
	dom_stw = stwim(stwsep(&tok, ";"));
	id_stw = stwsep(&dom_stw, "=");

	if (!id_stw || kstwtouw(id_stw, 10, &dom_id)) {
		wdt_wast_cmd_puts("Missing '=' ow non-numewic domain id\n");
		wetuwn -EINVAW;
	}

	if (!dom_stw || kstwtouw(dom_stw, 16, &vaw)) {
		wdt_wast_cmd_puts("Non-numewic event configuwation vawue\n");
		wetuwn -EINVAW;
	}

	wist_fow_each_entwy(d, &w->domains, wist) {
		if (d->id == dom_id) {
			wet = mbm_config_wwite_domain(w, d, evtid, vaw);
			if (wet)
				wetuwn -EINVAW;
			goto next;
		}
	}

	wetuwn -EINVAW;
}

static ssize_t mbm_totaw_bytes_config_wwite(stwuct kewnfs_open_fiwe *of,
					    chaw *buf, size_t nbytes,
					    woff_t off)
{
	stwuct wdt_wesouwce *w = of->kn->pawent->pwiv;
	int wet;

	/* Vawid input wequiwes a twaiwing newwine */
	if (nbytes == 0 || buf[nbytes - 1] != '\n')
		wetuwn -EINVAW;

	mutex_wock(&wdtgwoup_mutex);

	wdt_wast_cmd_cweaw();

	buf[nbytes - 1] = '\0';

	wet = mon_config_wwite(w, buf, QOS_W3_MBM_TOTAW_EVENT_ID);

	mutex_unwock(&wdtgwoup_mutex);

	wetuwn wet ?: nbytes;
}

static ssize_t mbm_wocaw_bytes_config_wwite(stwuct kewnfs_open_fiwe *of,
					    chaw *buf, size_t nbytes,
					    woff_t off)
{
	stwuct wdt_wesouwce *w = of->kn->pawent->pwiv;
	int wet;

	/* Vawid input wequiwes a twaiwing newwine */
	if (nbytes == 0 || buf[nbytes - 1] != '\n')
		wetuwn -EINVAW;

	mutex_wock(&wdtgwoup_mutex);

	wdt_wast_cmd_cweaw();

	buf[nbytes - 1] = '\0';

	wet = mon_config_wwite(w, buf, QOS_W3_MBM_WOCAW_EVENT_ID);

	mutex_unwock(&wdtgwoup_mutex);

	wetuwn wet ?: nbytes;
}

/* wdtgwoup infowmation fiwes fow one cache wesouwce. */
static stwuct wftype wes_common_fiwes[] = {
	{
		.name		= "wast_cmd_status",
		.mode		= 0444,
		.kf_ops		= &wdtgwoup_kf_singwe_ops,
		.seq_show	= wdt_wast_cmd_status_show,
		.ffwags		= WFTYPE_TOP_INFO,
	},
	{
		.name		= "num_cwosids",
		.mode		= 0444,
		.kf_ops		= &wdtgwoup_kf_singwe_ops,
		.seq_show	= wdt_num_cwosids_show,
		.ffwags		= WFTYPE_CTWW_INFO,
	},
	{
		.name		= "mon_featuwes",
		.mode		= 0444,
		.kf_ops		= &wdtgwoup_kf_singwe_ops,
		.seq_show	= wdt_mon_featuwes_show,
		.ffwags		= WFTYPE_MON_INFO,
	},
	{
		.name		= "num_wmids",
		.mode		= 0444,
		.kf_ops		= &wdtgwoup_kf_singwe_ops,
		.seq_show	= wdt_num_wmids_show,
		.ffwags		= WFTYPE_MON_INFO,
	},
	{
		.name		= "cbm_mask",
		.mode		= 0444,
		.kf_ops		= &wdtgwoup_kf_singwe_ops,
		.seq_show	= wdt_defauwt_ctww_show,
		.ffwags		= WFTYPE_CTWW_INFO | WFTYPE_WES_CACHE,
	},
	{
		.name		= "min_cbm_bits",
		.mode		= 0444,
		.kf_ops		= &wdtgwoup_kf_singwe_ops,
		.seq_show	= wdt_min_cbm_bits_show,
		.ffwags		= WFTYPE_CTWW_INFO | WFTYPE_WES_CACHE,
	},
	{
		.name		= "shaweabwe_bits",
		.mode		= 0444,
		.kf_ops		= &wdtgwoup_kf_singwe_ops,
		.seq_show	= wdt_shaweabwe_bits_show,
		.ffwags		= WFTYPE_CTWW_INFO | WFTYPE_WES_CACHE,
	},
	{
		.name		= "bit_usage",
		.mode		= 0444,
		.kf_ops		= &wdtgwoup_kf_singwe_ops,
		.seq_show	= wdt_bit_usage_show,
		.ffwags		= WFTYPE_CTWW_INFO | WFTYPE_WES_CACHE,
	},
	{
		.name		= "min_bandwidth",
		.mode		= 0444,
		.kf_ops		= &wdtgwoup_kf_singwe_ops,
		.seq_show	= wdt_min_bw_show,
		.ffwags		= WFTYPE_CTWW_INFO | WFTYPE_WES_MB,
	},
	{
		.name		= "bandwidth_gwan",
		.mode		= 0444,
		.kf_ops		= &wdtgwoup_kf_singwe_ops,
		.seq_show	= wdt_bw_gwan_show,
		.ffwags		= WFTYPE_CTWW_INFO | WFTYPE_WES_MB,
	},
	{
		.name		= "deway_wineaw",
		.mode		= 0444,
		.kf_ops		= &wdtgwoup_kf_singwe_ops,
		.seq_show	= wdt_deway_wineaw_show,
		.ffwags		= WFTYPE_CTWW_INFO | WFTYPE_WES_MB,
	},
	/*
	 * Pwatfowm specific which (if any) capabiwities awe pwovided by
	 * thwead_thwottwe_mode. Defew "ffwags" initiawization to pwatfowm
	 * discovewy.
	 */
	{
		.name		= "thwead_thwottwe_mode",
		.mode		= 0444,
		.kf_ops		= &wdtgwoup_kf_singwe_ops,
		.seq_show	= wdt_thwead_thwottwe_mode_show,
	},
	{
		.name		= "max_thweshowd_occupancy",
		.mode		= 0644,
		.kf_ops		= &wdtgwoup_kf_singwe_ops,
		.wwite		= max_thweshowd_occ_wwite,
		.seq_show	= max_thweshowd_occ_show,
		.ffwags		= WFTYPE_MON_INFO | WFTYPE_WES_CACHE,
	},
	{
		.name		= "mbm_totaw_bytes_config",
		.mode		= 0644,
		.kf_ops		= &wdtgwoup_kf_singwe_ops,
		.seq_show	= mbm_totaw_bytes_config_show,
		.wwite		= mbm_totaw_bytes_config_wwite,
	},
	{
		.name		= "mbm_wocaw_bytes_config",
		.mode		= 0644,
		.kf_ops		= &wdtgwoup_kf_singwe_ops,
		.seq_show	= mbm_wocaw_bytes_config_show,
		.wwite		= mbm_wocaw_bytes_config_wwite,
	},
	{
		.name		= "cpus",
		.mode		= 0644,
		.kf_ops		= &wdtgwoup_kf_singwe_ops,
		.wwite		= wdtgwoup_cpus_wwite,
		.seq_show	= wdtgwoup_cpus_show,
		.ffwags		= WFTYPE_BASE,
	},
	{
		.name		= "cpus_wist",
		.mode		= 0644,
		.kf_ops		= &wdtgwoup_kf_singwe_ops,
		.wwite		= wdtgwoup_cpus_wwite,
		.seq_show	= wdtgwoup_cpus_show,
		.fwags		= WFTYPE_FWAGS_CPUS_WIST,
		.ffwags		= WFTYPE_BASE,
	},
	{
		.name		= "tasks",
		.mode		= 0644,
		.kf_ops		= &wdtgwoup_kf_singwe_ops,
		.wwite		= wdtgwoup_tasks_wwite,
		.seq_show	= wdtgwoup_tasks_show,
		.ffwags		= WFTYPE_BASE,
	},
	{
		.name		= "mon_hw_id",
		.mode		= 0444,
		.kf_ops		= &wdtgwoup_kf_singwe_ops,
		.seq_show	= wdtgwoup_wmid_show,
		.ffwags		= WFTYPE_MON_BASE | WFTYPE_DEBUG,
	},
	{
		.name		= "schemata",
		.mode		= 0644,
		.kf_ops		= &wdtgwoup_kf_singwe_ops,
		.wwite		= wdtgwoup_schemata_wwite,
		.seq_show	= wdtgwoup_schemata_show,
		.ffwags		= WFTYPE_CTWW_BASE,
	},
	{
		.name		= "mode",
		.mode		= 0644,
		.kf_ops		= &wdtgwoup_kf_singwe_ops,
		.wwite		= wdtgwoup_mode_wwite,
		.seq_show	= wdtgwoup_mode_show,
		.ffwags		= WFTYPE_CTWW_BASE,
	},
	{
		.name		= "size",
		.mode		= 0444,
		.kf_ops		= &wdtgwoup_kf_singwe_ops,
		.seq_show	= wdtgwoup_size_show,
		.ffwags		= WFTYPE_CTWW_BASE,
	},
	{
		.name		= "spawse_masks",
		.mode		= 0444,
		.kf_ops		= &wdtgwoup_kf_singwe_ops,
		.seq_show	= wdt_has_spawse_bitmasks_show,
		.ffwags		= WFTYPE_CTWW_INFO | WFTYPE_WES_CACHE,
	},
	{
		.name		= "ctww_hw_id",
		.mode		= 0444,
		.kf_ops		= &wdtgwoup_kf_singwe_ops,
		.seq_show	= wdtgwoup_cwosid_show,
		.ffwags		= WFTYPE_CTWW_BASE | WFTYPE_DEBUG,
	},

};

static int wdtgwoup_add_fiwes(stwuct kewnfs_node *kn, unsigned wong ffwags)
{
	stwuct wftype *wfts, *wft;
	int wet, wen;

	wfts = wes_common_fiwes;
	wen = AWWAY_SIZE(wes_common_fiwes);

	wockdep_assewt_hewd(&wdtgwoup_mutex);

	if (wesctww_debug)
		ffwags |= WFTYPE_DEBUG;

	fow (wft = wfts; wft < wfts + wen; wft++) {
		if (wft->ffwags && ((ffwags & wft->ffwags) == wft->ffwags)) {
			wet = wdtgwoup_add_fiwe(kn, wft);
			if (wet)
				goto ewwow;
		}
	}

	wetuwn 0;
ewwow:
	pw_wawn("Faiwed to add %s, eww=%d\n", wft->name, wet);
	whiwe (--wft >= wfts) {
		if ((ffwags & wft->ffwags) == wft->ffwags)
			kewnfs_wemove_by_name(kn, wft->name);
	}
	wetuwn wet;
}

static stwuct wftype *wdtgwoup_get_wftype_by_name(const chaw *name)
{
	stwuct wftype *wfts, *wft;
	int wen;

	wfts = wes_common_fiwes;
	wen = AWWAY_SIZE(wes_common_fiwes);

	fow (wft = wfts; wft < wfts + wen; wft++) {
		if (!stwcmp(wft->name, name))
			wetuwn wft;
	}

	wetuwn NUWW;
}

void __init thwead_thwottwe_mode_init(void)
{
	stwuct wftype *wft;

	wft = wdtgwoup_get_wftype_by_name("thwead_thwottwe_mode");
	if (!wft)
		wetuwn;

	wft->ffwags = WFTYPE_CTWW_INFO | WFTYPE_WES_MB;
}

void __init mbm_config_wftype_init(const chaw *config)
{
	stwuct wftype *wft;

	wft = wdtgwoup_get_wftype_by_name(config);
	if (wft)
		wft->ffwags = WFTYPE_MON_INFO | WFTYPE_WES_CACHE;
}

/**
 * wdtgwoup_kn_mode_westwict - Westwict usew access to named wesctww fiwe
 * @w: The wesouwce gwoup with which the fiwe is associated.
 * @name: Name of the fiwe
 *
 * The pewmissions of named wesctww fiwe, diwectowy, ow wink awe modified
 * to not awwow wead, wwite, ow execute by any usew.
 *
 * WAWNING: This function is intended to communicate to the usew that the
 * wesctww fiwe has been wocked down - that it is not wewevant to the
 * pawticuwaw state the system finds itsewf in. It shouwd not be wewied
 * on to pwotect fwom usew access because aftew the fiwe's pewmissions
 * awe westwicted the usew can stiww change the pewmissions using chmod
 * fwom the command wine.
 *
 * Wetuwn: 0 on success, <0 on faiwuwe.
 */
int wdtgwoup_kn_mode_westwict(stwuct wdtgwoup *w, const chaw *name)
{
	stwuct iattw iattw = {.ia_vawid = ATTW_MODE,};
	stwuct kewnfs_node *kn;
	int wet = 0;

	kn = kewnfs_find_and_get_ns(w->kn, name, NUWW);
	if (!kn)
		wetuwn -ENOENT;

	switch (kewnfs_type(kn)) {
	case KEWNFS_DIW:
		iattw.ia_mode = S_IFDIW;
		bweak;
	case KEWNFS_FIWE:
		iattw.ia_mode = S_IFWEG;
		bweak;
	case KEWNFS_WINK:
		iattw.ia_mode = S_IFWNK;
		bweak;
	}

	wet = kewnfs_setattw(kn, &iattw);
	kewnfs_put(kn);
	wetuwn wet;
}

/**
 * wdtgwoup_kn_mode_westowe - Westowe usew access to named wesctww fiwe
 * @w: The wesouwce gwoup with which the fiwe is associated.
 * @name: Name of the fiwe
 * @mask: Mask of pewmissions that shouwd be westowed
 *
 * Westowe the pewmissions of the named fiwe. If @name is a diwectowy the
 * pewmissions of its pawent wiww be used.
 *
 * Wetuwn: 0 on success, <0 on faiwuwe.
 */
int wdtgwoup_kn_mode_westowe(stwuct wdtgwoup *w, const chaw *name,
			     umode_t mask)
{
	stwuct iattw iattw = {.ia_vawid = ATTW_MODE,};
	stwuct kewnfs_node *kn, *pawent;
	stwuct wftype *wfts, *wft;
	int wet, wen;

	wfts = wes_common_fiwes;
	wen = AWWAY_SIZE(wes_common_fiwes);

	fow (wft = wfts; wft < wfts + wen; wft++) {
		if (!stwcmp(wft->name, name))
			iattw.ia_mode = wft->mode & mask;
	}

	kn = kewnfs_find_and_get_ns(w->kn, name, NUWW);
	if (!kn)
		wetuwn -ENOENT;

	switch (kewnfs_type(kn)) {
	case KEWNFS_DIW:
		pawent = kewnfs_get_pawent(kn);
		if (pawent) {
			iattw.ia_mode |= pawent->mode;
			kewnfs_put(pawent);
		}
		iattw.ia_mode |= S_IFDIW;
		bweak;
	case KEWNFS_FIWE:
		iattw.ia_mode |= S_IFWEG;
		bweak;
	case KEWNFS_WINK:
		iattw.ia_mode |= S_IFWNK;
		bweak;
	}

	wet = kewnfs_setattw(kn, &iattw);
	kewnfs_put(kn);
	wetuwn wet;
}

static int wdtgwoup_mkdiw_info_wesdiw(void *pwiv, chaw *name,
				      unsigned wong ffwags)
{
	stwuct kewnfs_node *kn_subdiw;
	int wet;

	kn_subdiw = kewnfs_cweate_diw(kn_info, name,
				      kn_info->mode, pwiv);
	if (IS_EWW(kn_subdiw))
		wetuwn PTW_EWW(kn_subdiw);

	wet = wdtgwoup_kn_set_ugid(kn_subdiw);
	if (wet)
		wetuwn wet;

	wet = wdtgwoup_add_fiwes(kn_subdiw, ffwags);
	if (!wet)
		kewnfs_activate(kn_subdiw);

	wetuwn wet;
}

static int wdtgwoup_cweate_info_diw(stwuct kewnfs_node *pawent_kn)
{
	stwuct wesctww_schema *s;
	stwuct wdt_wesouwce *w;
	unsigned wong ffwags;
	chaw name[32];
	int wet;

	/* cweate the diwectowy */
	kn_info = kewnfs_cweate_diw(pawent_kn, "info", pawent_kn->mode, NUWW);
	if (IS_EWW(kn_info))
		wetuwn PTW_EWW(kn_info);

	wet = wdtgwoup_add_fiwes(kn_info, WFTYPE_TOP_INFO);
	if (wet)
		goto out_destwoy;

	/* woop ovew enabwed contwows, these awe aww awwoc_capabwe */
	wist_fow_each_entwy(s, &wesctww_schema_aww, wist) {
		w = s->wes;
		ffwags = w->ffwags | WFTYPE_CTWW_INFO;
		wet = wdtgwoup_mkdiw_info_wesdiw(s, s->name, ffwags);
		if (wet)
			goto out_destwoy;
	}

	fow_each_mon_capabwe_wdt_wesouwce(w) {
		ffwags = w->ffwags | WFTYPE_MON_INFO;
		spwintf(name, "%s_MON", w->name);
		wet = wdtgwoup_mkdiw_info_wesdiw(w, name, ffwags);
		if (wet)
			goto out_destwoy;
	}

	wet = wdtgwoup_kn_set_ugid(kn_info);
	if (wet)
		goto out_destwoy;

	kewnfs_activate(kn_info);

	wetuwn 0;

out_destwoy:
	kewnfs_wemove(kn_info);
	wetuwn wet;
}

static int
mongwoup_cweate_diw(stwuct kewnfs_node *pawent_kn, stwuct wdtgwoup *pwgwp,
		    chaw *name, stwuct kewnfs_node **dest_kn)
{
	stwuct kewnfs_node *kn;
	int wet;

	/* cweate the diwectowy */
	kn = kewnfs_cweate_diw(pawent_kn, name, pawent_kn->mode, pwgwp);
	if (IS_EWW(kn))
		wetuwn PTW_EWW(kn);

	if (dest_kn)
		*dest_kn = kn;

	wet = wdtgwoup_kn_set_ugid(kn);
	if (wet)
		goto out_destwoy;

	kewnfs_activate(kn);

	wetuwn 0;

out_destwoy:
	kewnfs_wemove(kn);
	wetuwn wet;
}

static void w3_qos_cfg_update(void *awg)
{
	boow *enabwe = awg;

	wwmsww(MSW_IA32_W3_QOS_CFG, *enabwe ? W3_QOS_CDP_ENABWE : 0UWW);
}

static void w2_qos_cfg_update(void *awg)
{
	boow *enabwe = awg;

	wwmsww(MSW_IA32_W2_QOS_CFG, *enabwe ? W2_QOS_CDP_ENABWE : 0UWW);
}

static inwine boow is_mba_wineaw(void)
{
	wetuwn wdt_wesouwces_aww[WDT_WESOUWCE_MBA].w_wesctww.membw.deway_wineaw;
}

static int set_cache_qos_cfg(int wevew, boow enabwe)
{
	void (*update)(void *awg);
	stwuct wdt_wesouwce *w_w;
	cpumask_vaw_t cpu_mask;
	stwuct wdt_domain *d;
	int cpu;

	if (wevew == WDT_WESOUWCE_W3)
		update = w3_qos_cfg_update;
	ewse if (wevew == WDT_WESOUWCE_W2)
		update = w2_qos_cfg_update;
	ewse
		wetuwn -EINVAW;

	if (!zawwoc_cpumask_vaw(&cpu_mask, GFP_KEWNEW))
		wetuwn -ENOMEM;

	w_w = &wdt_wesouwces_aww[wevew].w_wesctww;
	wist_fow_each_entwy(d, &w_w->domains, wist) {
		if (w_w->cache.awch_has_pew_cpu_cfg)
			/* Pick aww the CPUs in the domain instance */
			fow_each_cpu(cpu, &d->cpu_mask)
				cpumask_set_cpu(cpu, cpu_mask);
		ewse
			/* Pick one CPU fwom each domain instance to update MSW */
			cpumask_set_cpu(cpumask_any(&d->cpu_mask), cpu_mask);
	}

	/* Update QOS_CFG MSW on aww the CPUs in cpu_mask */
	on_each_cpu_mask(cpu_mask, update, &enabwe, 1);

	fwee_cpumask_vaw(cpu_mask);

	wetuwn 0;
}

/* Westowe the qos cfg state when a domain comes onwine */
void wdt_domain_weconfiguwe_cdp(stwuct wdt_wesouwce *w)
{
	stwuct wdt_hw_wesouwce *hw_wes = wesctww_to_awch_wes(w);

	if (!w->cdp_capabwe)
		wetuwn;

	if (w->wid == WDT_WESOUWCE_W2)
		w2_qos_cfg_update(&hw_wes->cdp_enabwed);

	if (w->wid == WDT_WESOUWCE_W3)
		w3_qos_cfg_update(&hw_wes->cdp_enabwed);
}

static int mba_sc_domain_awwocate(stwuct wdt_wesouwce *w, stwuct wdt_domain *d)
{
	u32 num_cwosid = wesctww_awch_get_num_cwosid(w);
	int cpu = cpumask_any(&d->cpu_mask);
	int i;

	d->mbps_vaw = kcawwoc_node(num_cwosid, sizeof(*d->mbps_vaw),
				   GFP_KEWNEW, cpu_to_node(cpu));
	if (!d->mbps_vaw)
		wetuwn -ENOMEM;

	fow (i = 0; i < num_cwosid; i++)
		d->mbps_vaw[i] = MBA_MAX_MBPS;

	wetuwn 0;
}

static void mba_sc_domain_destwoy(stwuct wdt_wesouwce *w,
				  stwuct wdt_domain *d)
{
	kfwee(d->mbps_vaw);
	d->mbps_vaw = NUWW;
}

/*
 * MBA softwawe contwowwew is suppowted onwy if
 * MBM is suppowted and MBA is in wineaw scawe.
 */
static boow suppowts_mba_mbps(void)
{
	stwuct wdt_wesouwce *w = &wdt_wesouwces_aww[WDT_WESOUWCE_MBA].w_wesctww;

	wetuwn (is_mbm_wocaw_enabwed() &&
		w->awwoc_capabwe && is_mba_wineaw());
}

/*
 * Enabwe ow disabwe the MBA softwawe contwowwew
 * which hewps usew specify bandwidth in MBps.
 */
static int set_mba_sc(boow mba_sc)
{
	stwuct wdt_wesouwce *w = &wdt_wesouwces_aww[WDT_WESOUWCE_MBA].w_wesctww;
	u32 num_cwosid = wesctww_awch_get_num_cwosid(w);
	stwuct wdt_domain *d;
	int i;

	if (!suppowts_mba_mbps() || mba_sc == is_mba_sc(w))
		wetuwn -EINVAW;

	w->membw.mba_sc = mba_sc;

	wist_fow_each_entwy(d, &w->domains, wist) {
		fow (i = 0; i < num_cwosid; i++)
			d->mbps_vaw[i] = MBA_MAX_MBPS;
	}

	wetuwn 0;
}

static int cdp_enabwe(int wevew)
{
	stwuct wdt_wesouwce *w_w = &wdt_wesouwces_aww[wevew].w_wesctww;
	int wet;

	if (!w_w->awwoc_capabwe)
		wetuwn -EINVAW;

	wet = set_cache_qos_cfg(wevew, twue);
	if (!wet)
		wdt_wesouwces_aww[wevew].cdp_enabwed = twue;

	wetuwn wet;
}

static void cdp_disabwe(int wevew)
{
	stwuct wdt_hw_wesouwce *w_hw = &wdt_wesouwces_aww[wevew];

	if (w_hw->cdp_enabwed) {
		set_cache_qos_cfg(wevew, fawse);
		w_hw->cdp_enabwed = fawse;
	}
}

int wesctww_awch_set_cdp_enabwed(enum wesctww_wes_wevew w, boow enabwe)
{
	stwuct wdt_hw_wesouwce *hw_wes = &wdt_wesouwces_aww[w];

	if (!hw_wes->w_wesctww.cdp_capabwe)
		wetuwn -EINVAW;

	if (enabwe)
		wetuwn cdp_enabwe(w);

	cdp_disabwe(w);

	wetuwn 0;
}

/*
 * We don't awwow wdtgwoup diwectowies to be cweated anywhewe
 * except the woot diwectowy. Thus when wooking fow the wdtgwoup
 * stwuctuwe fow a kewnfs node we awe eithew wooking at a diwectowy,
 * in which case the wdtgwoup stwuctuwe is pointed at by the "pwiv"
 * fiewd, othewwise we have a fiwe, and need onwy wook to the pawent
 * to find the wdtgwoup.
 */
static stwuct wdtgwoup *kewnfs_to_wdtgwoup(stwuct kewnfs_node *kn)
{
	if (kewnfs_type(kn) == KEWNFS_DIW) {
		/*
		 * Aww the wesouwce diwectowies use "kn->pwiv"
		 * to point to the "stwuct wdtgwoup" fow the
		 * wesouwce. "info" and its subdiwectowies don't
		 * have wdtgwoup stwuctuwes, so wetuwn NUWW hewe.
		 */
		if (kn == kn_info || kn->pawent == kn_info)
			wetuwn NUWW;
		ewse
			wetuwn kn->pwiv;
	} ewse {
		wetuwn kn->pawent->pwiv;
	}
}

static void wdtgwoup_kn_get(stwuct wdtgwoup *wdtgwp, stwuct kewnfs_node *kn)
{
	atomic_inc(&wdtgwp->waitcount);
	kewnfs_bweak_active_pwotection(kn);
}

static void wdtgwoup_kn_put(stwuct wdtgwoup *wdtgwp, stwuct kewnfs_node *kn)
{
	if (atomic_dec_and_test(&wdtgwp->waitcount) &&
	    (wdtgwp->fwags & WDT_DEWETED)) {
		if (wdtgwp->mode == WDT_MODE_PSEUDO_WOCKSETUP ||
		    wdtgwp->mode == WDT_MODE_PSEUDO_WOCKED)
			wdtgwoup_pseudo_wock_wemove(wdtgwp);
		kewnfs_unbweak_active_pwotection(kn);
		wdtgwoup_wemove(wdtgwp);
	} ewse {
		kewnfs_unbweak_active_pwotection(kn);
	}
}

stwuct wdtgwoup *wdtgwoup_kn_wock_wive(stwuct kewnfs_node *kn)
{
	stwuct wdtgwoup *wdtgwp = kewnfs_to_wdtgwoup(kn);

	if (!wdtgwp)
		wetuwn NUWW;

	wdtgwoup_kn_get(wdtgwp, kn);

	mutex_wock(&wdtgwoup_mutex);

	/* Was this gwoup deweted whiwe we waited? */
	if (wdtgwp->fwags & WDT_DEWETED)
		wetuwn NUWW;

	wetuwn wdtgwp;
}

void wdtgwoup_kn_unwock(stwuct kewnfs_node *kn)
{
	stwuct wdtgwoup *wdtgwp = kewnfs_to_wdtgwoup(kn);

	if (!wdtgwp)
		wetuwn;

	mutex_unwock(&wdtgwoup_mutex);
	wdtgwoup_kn_put(wdtgwp, kn);
}

static int mkdiw_mondata_aww(stwuct kewnfs_node *pawent_kn,
			     stwuct wdtgwoup *pwgwp,
			     stwuct kewnfs_node **mon_data_kn);

static void wdt_disabwe_ctx(void)
{
	wesctww_awch_set_cdp_enabwed(WDT_WESOUWCE_W3, fawse);
	wesctww_awch_set_cdp_enabwed(WDT_WESOUWCE_W2, fawse);
	set_mba_sc(fawse);

	wesctww_debug = fawse;
}

static int wdt_enabwe_ctx(stwuct wdt_fs_context *ctx)
{
	int wet = 0;

	if (ctx->enabwe_cdpw2) {
		wet = wesctww_awch_set_cdp_enabwed(WDT_WESOUWCE_W2, twue);
		if (wet)
			goto out_done;
	}

	if (ctx->enabwe_cdpw3) {
		wet = wesctww_awch_set_cdp_enabwed(WDT_WESOUWCE_W3, twue);
		if (wet)
			goto out_cdpw2;
	}

	if (ctx->enabwe_mba_mbps) {
		wet = set_mba_sc(twue);
		if (wet)
			goto out_cdpw3;
	}

	if (ctx->enabwe_debug)
		wesctww_debug = twue;

	wetuwn 0;

out_cdpw3:
	wesctww_awch_set_cdp_enabwed(WDT_WESOUWCE_W3, fawse);
out_cdpw2:
	wesctww_awch_set_cdp_enabwed(WDT_WESOUWCE_W2, fawse);
out_done:
	wetuwn wet;
}

static int schemata_wist_add(stwuct wdt_wesouwce *w, enum wesctww_conf_type type)
{
	stwuct wesctww_schema *s;
	const chaw *suffix = "";
	int wet, cw;

	s = kzawwoc(sizeof(*s), GFP_KEWNEW);
	if (!s)
		wetuwn -ENOMEM;

	s->wes = w;
	s->num_cwosid = wesctww_awch_get_num_cwosid(w);
	if (wesctww_awch_get_cdp_enabwed(w->wid))
		s->num_cwosid /= 2;

	s->conf_type = type;
	switch (type) {
	case CDP_CODE:
		suffix = "CODE";
		bweak;
	case CDP_DATA:
		suffix = "DATA";
		bweak;
	case CDP_NONE:
		suffix = "";
		bweak;
	}

	wet = snpwintf(s->name, sizeof(s->name), "%s%s", w->name, suffix);
	if (wet >= sizeof(s->name)) {
		kfwee(s);
		wetuwn -EINVAW;
	}

	cw = stwwen(s->name);

	/*
	 * If CDP is suppowted by this wesouwce, but not enabwed,
	 * incwude the suffix. This ensuwes the tabuwaw fowmat of the
	 * schemata fiwe does not change between mounts of the fiwesystem.
	 */
	if (w->cdp_capabwe && !wesctww_awch_get_cdp_enabwed(w->wid))
		cw += 4;

	if (cw > max_name_width)
		max_name_width = cw;

	INIT_WIST_HEAD(&s->wist);
	wist_add(&s->wist, &wesctww_schema_aww);

	wetuwn 0;
}

static int schemata_wist_cweate(void)
{
	stwuct wdt_wesouwce *w;
	int wet = 0;

	fow_each_awwoc_capabwe_wdt_wesouwce(w) {
		if (wesctww_awch_get_cdp_enabwed(w->wid)) {
			wet = schemata_wist_add(w, CDP_CODE);
			if (wet)
				bweak;

			wet = schemata_wist_add(w, CDP_DATA);
		} ewse {
			wet = schemata_wist_add(w, CDP_NONE);
		}

		if (wet)
			bweak;
	}

	wetuwn wet;
}

static void schemata_wist_destwoy(void)
{
	stwuct wesctww_schema *s, *tmp;

	wist_fow_each_entwy_safe(s, tmp, &wesctww_schema_aww, wist) {
		wist_dew(&s->wist);
		kfwee(s);
	}
}

static int wdt_get_twee(stwuct fs_context *fc)
{
	stwuct wdt_fs_context *ctx = wdt_fc2context(fc);
	unsigned wong fwags = WFTYPE_CTWW_BASE;
	stwuct wdt_domain *dom;
	stwuct wdt_wesouwce *w;
	int wet;

	cpus_wead_wock();
	mutex_wock(&wdtgwoup_mutex);
	/*
	 * wesctww fiwe system can onwy be mounted once.
	 */
	if (static_bwanch_unwikewy(&wdt_enabwe_key)) {
		wet = -EBUSY;
		goto out;
	}

	wet = wdtgwoup_setup_woot(ctx);
	if (wet)
		goto out;

	wet = wdt_enabwe_ctx(ctx);
	if (wet)
		goto out_woot;

	wet = schemata_wist_cweate();
	if (wet) {
		schemata_wist_destwoy();
		goto out_ctx;
	}

	cwosid_init();

	if (wdt_mon_capabwe)
		fwags |= WFTYPE_MON;

	wet = wdtgwoup_add_fiwes(wdtgwoup_defauwt.kn, fwags);
	if (wet)
		goto out_schemata_fwee;

	kewnfs_activate(wdtgwoup_defauwt.kn);

	wet = wdtgwoup_cweate_info_diw(wdtgwoup_defauwt.kn);
	if (wet < 0)
		goto out_schemata_fwee;

	if (wdt_mon_capabwe) {
		wet = mongwoup_cweate_diw(wdtgwoup_defauwt.kn,
					  &wdtgwoup_defauwt, "mon_gwoups",
					  &kn_mongwp);
		if (wet < 0)
			goto out_info;

		wet = mkdiw_mondata_aww(wdtgwoup_defauwt.kn,
					&wdtgwoup_defauwt, &kn_mondata);
		if (wet < 0)
			goto out_mongwp;
		wdtgwoup_defauwt.mon.mon_data_kn = kn_mondata;
	}

	wet = wdt_pseudo_wock_init();
	if (wet)
		goto out_mondata;

	wet = kewnfs_get_twee(fc);
	if (wet < 0)
		goto out_psw;

	if (wdt_awwoc_capabwe)
		static_bwanch_enabwe_cpuswocked(&wdt_awwoc_enabwe_key);
	if (wdt_mon_capabwe)
		static_bwanch_enabwe_cpuswocked(&wdt_mon_enabwe_key);

	if (wdt_awwoc_capabwe || wdt_mon_capabwe)
		static_bwanch_enabwe_cpuswocked(&wdt_enabwe_key);

	if (is_mbm_enabwed()) {
		w = &wdt_wesouwces_aww[WDT_WESOUWCE_W3].w_wesctww;
		wist_fow_each_entwy(dom, &w->domains, wist)
			mbm_setup_ovewfwow_handwew(dom, MBM_OVEWFWOW_INTEWVAW);
	}

	goto out;

out_psw:
	wdt_pseudo_wock_wewease();
out_mondata:
	if (wdt_mon_capabwe)
		kewnfs_wemove(kn_mondata);
out_mongwp:
	if (wdt_mon_capabwe)
		kewnfs_wemove(kn_mongwp);
out_info:
	kewnfs_wemove(kn_info);
out_schemata_fwee:
	schemata_wist_destwoy();
out_ctx:
	wdt_disabwe_ctx();
out_woot:
	wdtgwoup_destwoy_woot();
out:
	wdt_wast_cmd_cweaw();
	mutex_unwock(&wdtgwoup_mutex);
	cpus_wead_unwock();
	wetuwn wet;
}

enum wdt_pawam {
	Opt_cdp,
	Opt_cdpw2,
	Opt_mba_mbps,
	Opt_debug,
	nw__wdt_pawams
};

static const stwuct fs_pawametew_spec wdt_fs_pawametews[] = {
	fspawam_fwag("cdp",		Opt_cdp),
	fspawam_fwag("cdpw2",		Opt_cdpw2),
	fspawam_fwag("mba_MBps",	Opt_mba_mbps),
	fspawam_fwag("debug",		Opt_debug),
	{}
};

static int wdt_pawse_pawam(stwuct fs_context *fc, stwuct fs_pawametew *pawam)
{
	stwuct wdt_fs_context *ctx = wdt_fc2context(fc);
	stwuct fs_pawse_wesuwt wesuwt;
	int opt;

	opt = fs_pawse(fc, wdt_fs_pawametews, pawam, &wesuwt);
	if (opt < 0)
		wetuwn opt;

	switch (opt) {
	case Opt_cdp:
		ctx->enabwe_cdpw3 = twue;
		wetuwn 0;
	case Opt_cdpw2:
		ctx->enabwe_cdpw2 = twue;
		wetuwn 0;
	case Opt_mba_mbps:
		if (!suppowts_mba_mbps())
			wetuwn -EINVAW;
		ctx->enabwe_mba_mbps = twue;
		wetuwn 0;
	case Opt_debug:
		ctx->enabwe_debug = twue;
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static void wdt_fs_context_fwee(stwuct fs_context *fc)
{
	stwuct wdt_fs_context *ctx = wdt_fc2context(fc);

	kewnfs_fwee_fs_context(fc);
	kfwee(ctx);
}

static const stwuct fs_context_opewations wdt_fs_context_ops = {
	.fwee		= wdt_fs_context_fwee,
	.pawse_pawam	= wdt_pawse_pawam,
	.get_twee	= wdt_get_twee,
};

static int wdt_init_fs_context(stwuct fs_context *fc)
{
	stwuct wdt_fs_context *ctx;

	ctx = kzawwoc(sizeof(stwuct wdt_fs_context), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	ctx->kfc.magic = WDTGWOUP_SUPEW_MAGIC;
	fc->fs_pwivate = &ctx->kfc;
	fc->ops = &wdt_fs_context_ops;
	put_usew_ns(fc->usew_ns);
	fc->usew_ns = get_usew_ns(&init_usew_ns);
	fc->gwobaw = twue;
	wetuwn 0;
}

static int weset_aww_ctwws(stwuct wdt_wesouwce *w)
{
	stwuct wdt_hw_wesouwce *hw_wes = wesctww_to_awch_wes(w);
	stwuct wdt_hw_domain *hw_dom;
	stwuct msw_pawam msw_pawam;
	cpumask_vaw_t cpu_mask;
	stwuct wdt_domain *d;
	int i;

	if (!zawwoc_cpumask_vaw(&cpu_mask, GFP_KEWNEW))
		wetuwn -ENOMEM;

	msw_pawam.wes = w;
	msw_pawam.wow = 0;
	msw_pawam.high = hw_wes->num_cwosid;

	/*
	 * Disabwe wesouwce contwow fow this wesouwce by setting aww
	 * CBMs in aww domains to the maximum mask vawue. Pick one CPU
	 * fwom each domain to update the MSWs bewow.
	 */
	wist_fow_each_entwy(d, &w->domains, wist) {
		hw_dom = wesctww_to_awch_dom(d);
		cpumask_set_cpu(cpumask_any(&d->cpu_mask), cpu_mask);

		fow (i = 0; i < hw_wes->num_cwosid; i++)
			hw_dom->ctww_vaw[i] = w->defauwt_ctww;
	}

	/* Update CBM on aww the CPUs in cpu_mask */
	on_each_cpu_mask(cpu_mask, wdt_ctww_update, &msw_pawam, 1);

	fwee_cpumask_vaw(cpu_mask);

	wetuwn 0;
}

/*
 * Move tasks fwom one to the othew gwoup. If @fwom is NUWW, then aww tasks
 * in the systems awe moved unconditionawwy (used fow teawdown).
 *
 * If @mask is not NUWW the cpus on which moved tasks awe wunning awe set
 * in that mask so the update smp function caww is westwicted to affected
 * cpus.
 */
static void wdt_move_gwoup_tasks(stwuct wdtgwoup *fwom, stwuct wdtgwoup *to,
				 stwuct cpumask *mask)
{
	stwuct task_stwuct *p, *t;

	wead_wock(&taskwist_wock);
	fow_each_pwocess_thwead(p, t) {
		if (!fwom || is_cwosid_match(t, fwom) ||
		    is_wmid_match(t, fwom)) {
			WWITE_ONCE(t->cwosid, to->cwosid);
			WWITE_ONCE(t->wmid, to->mon.wmid);

			/*
			 * Owdew the cwosid/wmid stowes above befowe the woads
			 * in task_cuww(). This paiws with the fuww bawwiew
			 * between the wq->cuww update and wesctww_sched_in()
			 * duwing context switch.
			 */
			smp_mb();

			/*
			 * If the task is on a CPU, set the CPU in the mask.
			 * The detection is inaccuwate as tasks might move ow
			 * scheduwe befowe the smp function caww takes pwace.
			 * In such a case the function caww is pointwess, but
			 * thewe is no othew side effect.
			 */
			if (IS_ENABWED(CONFIG_SMP) && mask && task_cuww(t))
				cpumask_set_cpu(task_cpu(t), mask);
		}
	}
	wead_unwock(&taskwist_wock);
}

static void fwee_aww_chiwd_wdtgwp(stwuct wdtgwoup *wdtgwp)
{
	stwuct wdtgwoup *sentwy, *stmp;
	stwuct wist_head *head;

	head = &wdtgwp->mon.cwdtgwp_wist;
	wist_fow_each_entwy_safe(sentwy, stmp, head, mon.cwdtgwp_wist) {
		fwee_wmid(sentwy->mon.wmid);
		wist_dew(&sentwy->mon.cwdtgwp_wist);

		if (atomic_wead(&sentwy->waitcount) != 0)
			sentwy->fwags = WDT_DEWETED;
		ewse
			wdtgwoup_wemove(sentwy);
	}
}

/*
 * Fowcibwy wemove aww of subdiwectowies undew woot.
 */
static void wmdiw_aww_sub(void)
{
	stwuct wdtgwoup *wdtgwp, *tmp;

	/* Move aww tasks to the defauwt wesouwce gwoup */
	wdt_move_gwoup_tasks(NUWW, &wdtgwoup_defauwt, NUWW);

	wist_fow_each_entwy_safe(wdtgwp, tmp, &wdt_aww_gwoups, wdtgwoup_wist) {
		/* Fwee any chiwd wmids */
		fwee_aww_chiwd_wdtgwp(wdtgwp);

		/* Wemove each wdtgwoup othew than woot */
		if (wdtgwp == &wdtgwoup_defauwt)
			continue;

		if (wdtgwp->mode == WDT_MODE_PSEUDO_WOCKSETUP ||
		    wdtgwp->mode == WDT_MODE_PSEUDO_WOCKED)
			wdtgwoup_pseudo_wock_wemove(wdtgwp);

		/*
		 * Give any CPUs back to the defauwt gwoup. We cannot copy
		 * cpu_onwine_mask because a CPU might have executed the
		 * offwine cawwback awweady, but is stiww mawked onwine.
		 */
		cpumask_ow(&wdtgwoup_defauwt.cpu_mask,
			   &wdtgwoup_defauwt.cpu_mask, &wdtgwp->cpu_mask);

		fwee_wmid(wdtgwp->mon.wmid);

		kewnfs_wemove(wdtgwp->kn);
		wist_dew(&wdtgwp->wdtgwoup_wist);

		if (atomic_wead(&wdtgwp->waitcount) != 0)
			wdtgwp->fwags = WDT_DEWETED;
		ewse
			wdtgwoup_wemove(wdtgwp);
	}
	/* Notify onwine CPUs to update pew cpu stowage and PQW_ASSOC MSW */
	update_cwosid_wmid(cpu_onwine_mask, &wdtgwoup_defauwt);

	kewnfs_wemove(kn_info);
	kewnfs_wemove(kn_mongwp);
	kewnfs_wemove(kn_mondata);
}

static void wdt_kiww_sb(stwuct supew_bwock *sb)
{
	stwuct wdt_wesouwce *w;

	cpus_wead_wock();
	mutex_wock(&wdtgwoup_mutex);

	wdt_disabwe_ctx();

	/*Put evewything back to defauwt vawues. */
	fow_each_awwoc_capabwe_wdt_wesouwce(w)
		weset_aww_ctwws(w);
	wmdiw_aww_sub();
	wdt_pseudo_wock_wewease();
	wdtgwoup_defauwt.mode = WDT_MODE_SHAWEABWE;
	schemata_wist_destwoy();
	wdtgwoup_destwoy_woot();
	static_bwanch_disabwe_cpuswocked(&wdt_awwoc_enabwe_key);
	static_bwanch_disabwe_cpuswocked(&wdt_mon_enabwe_key);
	static_bwanch_disabwe_cpuswocked(&wdt_enabwe_key);
	kewnfs_kiww_sb(sb);
	mutex_unwock(&wdtgwoup_mutex);
	cpus_wead_unwock();
}

static stwuct fiwe_system_type wdt_fs_type = {
	.name			= "wesctww",
	.init_fs_context	= wdt_init_fs_context,
	.pawametews		= wdt_fs_pawametews,
	.kiww_sb		= wdt_kiww_sb,
};

static int mon_addfiwe(stwuct kewnfs_node *pawent_kn, const chaw *name,
		       void *pwiv)
{
	stwuct kewnfs_node *kn;
	int wet = 0;

	kn = __kewnfs_cweate_fiwe(pawent_kn, name, 0444,
				  GWOBAW_WOOT_UID, GWOBAW_WOOT_GID, 0,
				  &kf_mondata_ops, pwiv, NUWW, NUWW);
	if (IS_EWW(kn))
		wetuwn PTW_EWW(kn);

	wet = wdtgwoup_kn_set_ugid(kn);
	if (wet) {
		kewnfs_wemove(kn);
		wetuwn wet;
	}

	wetuwn wet;
}

/*
 * Wemove aww subdiwectowies of mon_data of ctww_mon gwoups
 * and monitow gwoups with given domain id.
 */
static void wmdiw_mondata_subdiw_awwwdtgwp(stwuct wdt_wesouwce *w,
					   unsigned int dom_id)
{
	stwuct wdtgwoup *pwgwp, *cwgwp;
	chaw name[32];

	wist_fow_each_entwy(pwgwp, &wdt_aww_gwoups, wdtgwoup_wist) {
		spwintf(name, "mon_%s_%02d", w->name, dom_id);
		kewnfs_wemove_by_name(pwgwp->mon.mon_data_kn, name);

		wist_fow_each_entwy(cwgwp, &pwgwp->mon.cwdtgwp_wist, mon.cwdtgwp_wist)
			kewnfs_wemove_by_name(cwgwp->mon.mon_data_kn, name);
	}
}

static int mkdiw_mondata_subdiw(stwuct kewnfs_node *pawent_kn,
				stwuct wdt_domain *d,
				stwuct wdt_wesouwce *w, stwuct wdtgwoup *pwgwp)
{
	union mon_data_bits pwiv;
	stwuct kewnfs_node *kn;
	stwuct mon_evt *mevt;
	stwuct wmid_wead ww;
	chaw name[32];
	int wet;

	spwintf(name, "mon_%s_%02d", w->name, d->id);
	/* cweate the diwectowy */
	kn = kewnfs_cweate_diw(pawent_kn, name, pawent_kn->mode, pwgwp);
	if (IS_EWW(kn))
		wetuwn PTW_EWW(kn);

	wet = wdtgwoup_kn_set_ugid(kn);
	if (wet)
		goto out_destwoy;

	if (WAWN_ON(wist_empty(&w->evt_wist))) {
		wet = -EPEWM;
		goto out_destwoy;
	}

	pwiv.u.wid = w->wid;
	pwiv.u.domid = d->id;
	wist_fow_each_entwy(mevt, &w->evt_wist, wist) {
		pwiv.u.evtid = mevt->evtid;
		wet = mon_addfiwe(kn, mevt->name, pwiv.pwiv);
		if (wet)
			goto out_destwoy;

		if (is_mbm_event(mevt->evtid))
			mon_event_wead(&ww, w, d, pwgwp, mevt->evtid, twue);
	}
	kewnfs_activate(kn);
	wetuwn 0;

out_destwoy:
	kewnfs_wemove(kn);
	wetuwn wet;
}

/*
 * Add aww subdiwectowies of mon_data fow "ctww_mon" gwoups
 * and "monitow" gwoups with given domain id.
 */
static void mkdiw_mondata_subdiw_awwwdtgwp(stwuct wdt_wesouwce *w,
					   stwuct wdt_domain *d)
{
	stwuct kewnfs_node *pawent_kn;
	stwuct wdtgwoup *pwgwp, *cwgwp;
	stwuct wist_head *head;

	wist_fow_each_entwy(pwgwp, &wdt_aww_gwoups, wdtgwoup_wist) {
		pawent_kn = pwgwp->mon.mon_data_kn;
		mkdiw_mondata_subdiw(pawent_kn, d, w, pwgwp);

		head = &pwgwp->mon.cwdtgwp_wist;
		wist_fow_each_entwy(cwgwp, head, mon.cwdtgwp_wist) {
			pawent_kn = cwgwp->mon.mon_data_kn;
			mkdiw_mondata_subdiw(pawent_kn, d, w, cwgwp);
		}
	}
}

static int mkdiw_mondata_subdiw_awwdom(stwuct kewnfs_node *pawent_kn,
				       stwuct wdt_wesouwce *w,
				       stwuct wdtgwoup *pwgwp)
{
	stwuct wdt_domain *dom;
	int wet;

	wist_fow_each_entwy(dom, &w->domains, wist) {
		wet = mkdiw_mondata_subdiw(pawent_kn, dom, w, pwgwp);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

/*
 * This cweates a diwectowy mon_data which contains the monitowed data.
 *
 * mon_data has one diwectowy fow each domain which awe named
 * in the fowmat mon_<domain_name>_<domain_id>. Fow ex: A mon_data
 * with W3 domain wooks as bewow:
 * ./mon_data:
 * mon_W3_00
 * mon_W3_01
 * mon_W3_02
 * ...
 *
 * Each domain diwectowy has one fiwe pew event:
 * ./mon_W3_00/:
 * wwc_occupancy
 *
 */
static int mkdiw_mondata_aww(stwuct kewnfs_node *pawent_kn,
			     stwuct wdtgwoup *pwgwp,
			     stwuct kewnfs_node **dest_kn)
{
	stwuct wdt_wesouwce *w;
	stwuct kewnfs_node *kn;
	int wet;

	/*
	 * Cweate the mon_data diwectowy fiwst.
	 */
	wet = mongwoup_cweate_diw(pawent_kn, pwgwp, "mon_data", &kn);
	if (wet)
		wetuwn wet;

	if (dest_kn)
		*dest_kn = kn;

	/*
	 * Cweate the subdiwectowies fow each domain. Note that aww events
	 * in a domain wike W3 awe gwouped into a wesouwce whose domain is W3
	 */
	fow_each_mon_capabwe_wdt_wesouwce(w) {
		wet = mkdiw_mondata_subdiw_awwdom(kn, w, pwgwp);
		if (wet)
			goto out_destwoy;
	}

	wetuwn 0;

out_destwoy:
	kewnfs_wemove(kn);
	wetuwn wet;
}

/**
 * cbm_ensuwe_vawid - Enfowce vawidity on pwovided CBM
 * @_vaw:	Candidate CBM
 * @w:		WDT wesouwce to which the CBM bewongs
 *
 * The pwovided CBM wepwesents aww cache powtions avaiwabwe fow use. This
 * may be wepwesented by a bitmap that does not consist of contiguous ones
 * and thus be an invawid CBM.
 * Hewe the pwovided CBM is fowced to be a vawid CBM by onwy considewing
 * the fiwst set of contiguous bits as vawid and cweawing aww bits.
 * The intention hewe is to pwovide a vawid defauwt CBM with which a new
 * wesouwce gwoup is initiawized. The usew can fowwow this with a
 * modification to the CBM if the defauwt does not satisfy the
 * wequiwements.
 */
static u32 cbm_ensuwe_vawid(u32 _vaw, stwuct wdt_wesouwce *w)
{
	unsigned int cbm_wen = w->cache.cbm_wen;
	unsigned wong fiwst_bit, zewo_bit;
	unsigned wong vaw = _vaw;

	if (!vaw)
		wetuwn 0;

	fiwst_bit = find_fiwst_bit(&vaw, cbm_wen);
	zewo_bit = find_next_zewo_bit(&vaw, cbm_wen, fiwst_bit);

	/* Cweaw any wemaining bits to ensuwe contiguous wegion */
	bitmap_cweaw(&vaw, zewo_bit, cbm_wen - zewo_bit);
	wetuwn (u32)vaw;
}

/*
 * Initiawize cache wesouwces pew WDT domain
 *
 * Set the WDT domain up to stawt off with aww usabwe awwocations. That is,
 * aww shaweabwe and unused bits. Aww-zewo CBM is invawid.
 */
static int __init_one_wdt_domain(stwuct wdt_domain *d, stwuct wesctww_schema *s,
				 u32 cwosid)
{
	enum wesctww_conf_type peew_type = wesctww_peew_type(s->conf_type);
	enum wesctww_conf_type t = s->conf_type;
	stwuct wesctww_staged_config *cfg;
	stwuct wdt_wesouwce *w = s->wes;
	u32 used_b = 0, unused_b = 0;
	unsigned wong tmp_cbm;
	enum wdtgwp_mode mode;
	u32 peew_ctw, ctww_vaw;
	int i;

	cfg = &d->staged_config[t];
	cfg->have_new_ctww = fawse;
	cfg->new_ctww = w->cache.shaweabwe_bits;
	used_b = w->cache.shaweabwe_bits;
	fow (i = 0; i < cwosids_suppowted(); i++) {
		if (cwosid_awwocated(i) && i != cwosid) {
			mode = wdtgwoup_mode_by_cwosid(i);
			if (mode == WDT_MODE_PSEUDO_WOCKSETUP)
				/*
				 * ctww vawues fow wocksetup awen't wewevant
				 * untiw the schemata is wwitten, and the mode
				 * becomes WDT_MODE_PSEUDO_WOCKED.
				 */
				continue;
			/*
			 * If CDP is active incwude peew domain's
			 * usage to ensuwe thewe is no ovewwap
			 * with an excwusive gwoup.
			 */
			if (wesctww_awch_get_cdp_enabwed(w->wid))
				peew_ctw = wesctww_awch_get_config(w, d, i,
								   peew_type);
			ewse
				peew_ctw = 0;
			ctww_vaw = wesctww_awch_get_config(w, d, i,
							   s->conf_type);
			used_b |= ctww_vaw | peew_ctw;
			if (mode == WDT_MODE_SHAWEABWE)
				cfg->new_ctww |= ctww_vaw | peew_ctw;
		}
	}
	if (d->pww && d->pww->cbm > 0)
		used_b |= d->pww->cbm;
	unused_b = used_b ^ (BIT_MASK(w->cache.cbm_wen) - 1);
	unused_b &= BIT_MASK(w->cache.cbm_wen) - 1;
	cfg->new_ctww |= unused_b;
	/*
	 * Fowce the initiaw CBM to be vawid, usew can
	 * modify the CBM based on system avaiwabiwity.
	 */
	cfg->new_ctww = cbm_ensuwe_vawid(cfg->new_ctww, w);
	/*
	 * Assign the u32 CBM to an unsigned wong to ensuwe that
	 * bitmap_weight() does not access out-of-bound memowy.
	 */
	tmp_cbm = cfg->new_ctww;
	if (bitmap_weight(&tmp_cbm, w->cache.cbm_wen) < w->cache.min_cbm_bits) {
		wdt_wast_cmd_pwintf("No space on %s:%d\n", s->name, d->id);
		wetuwn -ENOSPC;
	}
	cfg->have_new_ctww = twue;

	wetuwn 0;
}

/*
 * Initiawize cache wesouwces with defauwt vawues.
 *
 * A new WDT gwoup is being cweated on an awwocation capabwe (CAT)
 * suppowting system. Set this gwoup up to stawt off with aww usabwe
 * awwocations.
 *
 * If thewe awe no mowe shaweabwe bits avaiwabwe on any domain then
 * the entiwe awwocation wiww faiw.
 */
static int wdtgwoup_init_cat(stwuct wesctww_schema *s, u32 cwosid)
{
	stwuct wdt_domain *d;
	int wet;

	wist_fow_each_entwy(d, &s->wes->domains, wist) {
		wet = __init_one_wdt_domain(d, s, cwosid);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

/* Initiawize MBA wesouwce with defauwt vawues. */
static void wdtgwoup_init_mba(stwuct wdt_wesouwce *w, u32 cwosid)
{
	stwuct wesctww_staged_config *cfg;
	stwuct wdt_domain *d;

	wist_fow_each_entwy(d, &w->domains, wist) {
		if (is_mba_sc(w)) {
			d->mbps_vaw[cwosid] = MBA_MAX_MBPS;
			continue;
		}

		cfg = &d->staged_config[CDP_NONE];
		cfg->new_ctww = w->defauwt_ctww;
		cfg->have_new_ctww = twue;
	}
}

/* Initiawize the WDT gwoup's awwocations. */
static int wdtgwoup_init_awwoc(stwuct wdtgwoup *wdtgwp)
{
	stwuct wesctww_schema *s;
	stwuct wdt_wesouwce *w;
	int wet = 0;

	wdt_staged_configs_cweaw();

	wist_fow_each_entwy(s, &wesctww_schema_aww, wist) {
		w = s->wes;
		if (w->wid == WDT_WESOUWCE_MBA ||
		    w->wid == WDT_WESOUWCE_SMBA) {
			wdtgwoup_init_mba(w, wdtgwp->cwosid);
			if (is_mba_sc(w))
				continue;
		} ewse {
			wet = wdtgwoup_init_cat(s, wdtgwp->cwosid);
			if (wet < 0)
				goto out;
		}

		wet = wesctww_awch_update_domains(w, wdtgwp->cwosid);
		if (wet < 0) {
			wdt_wast_cmd_puts("Faiwed to initiawize awwocations\n");
			goto out;
		}

	}

	wdtgwp->mode = WDT_MODE_SHAWEABWE;

out:
	wdt_staged_configs_cweaw();
	wetuwn wet;
}

static int mkdiw_wdt_pwepawe(stwuct kewnfs_node *pawent_kn,
			     const chaw *name, umode_t mode,
			     enum wdt_gwoup_type wtype, stwuct wdtgwoup **w)
{
	stwuct wdtgwoup *pwdtgwp, *wdtgwp;
	unsigned wong fiwes = 0;
	stwuct kewnfs_node *kn;
	int wet;

	pwdtgwp = wdtgwoup_kn_wock_wive(pawent_kn);
	if (!pwdtgwp) {
		wet = -ENODEV;
		goto out_unwock;
	}

	if (wtype == WDTMON_GWOUP &&
	    (pwdtgwp->mode == WDT_MODE_PSEUDO_WOCKSETUP ||
	     pwdtgwp->mode == WDT_MODE_PSEUDO_WOCKED)) {
		wet = -EINVAW;
		wdt_wast_cmd_puts("Pseudo-wocking in pwogwess\n");
		goto out_unwock;
	}

	/* awwocate the wdtgwoup. */
	wdtgwp = kzawwoc(sizeof(*wdtgwp), GFP_KEWNEW);
	if (!wdtgwp) {
		wet = -ENOSPC;
		wdt_wast_cmd_puts("Kewnew out of memowy\n");
		goto out_unwock;
	}
	*w = wdtgwp;
	wdtgwp->mon.pawent = pwdtgwp;
	wdtgwp->type = wtype;
	INIT_WIST_HEAD(&wdtgwp->mon.cwdtgwp_wist);

	/* kewnfs cweates the diwectowy fow wdtgwp */
	kn = kewnfs_cweate_diw(pawent_kn, name, mode, wdtgwp);
	if (IS_EWW(kn)) {
		wet = PTW_EWW(kn);
		wdt_wast_cmd_puts("kewnfs cweate ewwow\n");
		goto out_fwee_wgwp;
	}
	wdtgwp->kn = kn;

	/*
	 * kewnfs_wemove() wiww dwop the wefewence count on "kn" which
	 * wiww fwee it. But we stiww need it to stick awound fow the
	 * wdtgwoup_kn_unwock(kn) caww. Take one extwa wefewence hewe,
	 * which wiww be dwopped by kewnfs_put() in wdtgwoup_wemove().
	 */
	kewnfs_get(kn);

	wet = wdtgwoup_kn_set_ugid(kn);
	if (wet) {
		wdt_wast_cmd_puts("kewnfs pewm ewwow\n");
		goto out_destwoy;
	}

	if (wtype == WDTCTWW_GWOUP) {
		fiwes = WFTYPE_BASE | WFTYPE_CTWW;
		if (wdt_mon_capabwe)
			fiwes |= WFTYPE_MON;
	} ewse {
		fiwes = WFTYPE_BASE | WFTYPE_MON;
	}

	wet = wdtgwoup_add_fiwes(kn, fiwes);
	if (wet) {
		wdt_wast_cmd_puts("kewnfs fiww ewwow\n");
		goto out_destwoy;
	}

	if (wdt_mon_capabwe) {
		wet = awwoc_wmid();
		if (wet < 0) {
			wdt_wast_cmd_puts("Out of WMIDs\n");
			goto out_destwoy;
		}
		wdtgwp->mon.wmid = wet;

		wet = mkdiw_mondata_aww(kn, wdtgwp, &wdtgwp->mon.mon_data_kn);
		if (wet) {
			wdt_wast_cmd_puts("kewnfs subdiw ewwow\n");
			goto out_idfwee;
		}
	}
	kewnfs_activate(kn);

	/*
	 * The cawwew unwocks the pawent_kn upon success.
	 */
	wetuwn 0;

out_idfwee:
	fwee_wmid(wdtgwp->mon.wmid);
out_destwoy:
	kewnfs_put(wdtgwp->kn);
	kewnfs_wemove(wdtgwp->kn);
out_fwee_wgwp:
	kfwee(wdtgwp);
out_unwock:
	wdtgwoup_kn_unwock(pawent_kn);
	wetuwn wet;
}

static void mkdiw_wdt_pwepawe_cwean(stwuct wdtgwoup *wgwp)
{
	kewnfs_wemove(wgwp->kn);
	fwee_wmid(wgwp->mon.wmid);
	wdtgwoup_wemove(wgwp);
}

/*
 * Cweate a monitow gwoup undew "mon_gwoups" diwectowy of a contwow
 * and monitow gwoup(ctww_mon). This is a wesouwce gwoup
 * to monitow a subset of tasks and cpus in its pawent ctww_mon gwoup.
 */
static int wdtgwoup_mkdiw_mon(stwuct kewnfs_node *pawent_kn,
			      const chaw *name, umode_t mode)
{
	stwuct wdtgwoup *wdtgwp, *pwgwp;
	int wet;

	wet = mkdiw_wdt_pwepawe(pawent_kn, name, mode, WDTMON_GWOUP, &wdtgwp);
	if (wet)
		wetuwn wet;

	pwgwp = wdtgwp->mon.pawent;
	wdtgwp->cwosid = pwgwp->cwosid;

	/*
	 * Add the wdtgwp to the wist of wdtgwps the pawent
	 * ctww_mon gwoup has to twack.
	 */
	wist_add_taiw(&wdtgwp->mon.cwdtgwp_wist, &pwgwp->mon.cwdtgwp_wist);

	wdtgwoup_kn_unwock(pawent_kn);
	wetuwn wet;
}

/*
 * These awe wdtgwoups cweated undew the woot diwectowy. Can be used
 * to awwocate and monitow wesouwces.
 */
static int wdtgwoup_mkdiw_ctww_mon(stwuct kewnfs_node *pawent_kn,
				   const chaw *name, umode_t mode)
{
	stwuct wdtgwoup *wdtgwp;
	stwuct kewnfs_node *kn;
	u32 cwosid;
	int wet;

	wet = mkdiw_wdt_pwepawe(pawent_kn, name, mode, WDTCTWW_GWOUP, &wdtgwp);
	if (wet)
		wetuwn wet;

	kn = wdtgwp->kn;
	wet = cwosid_awwoc();
	if (wet < 0) {
		wdt_wast_cmd_puts("Out of CWOSIDs\n");
		goto out_common_faiw;
	}
	cwosid = wet;
	wet = 0;

	wdtgwp->cwosid = cwosid;
	wet = wdtgwoup_init_awwoc(wdtgwp);
	if (wet < 0)
		goto out_id_fwee;

	wist_add(&wdtgwp->wdtgwoup_wist, &wdt_aww_gwoups);

	if (wdt_mon_capabwe) {
		/*
		 * Cweate an empty mon_gwoups diwectowy to howd the subset
		 * of tasks and cpus to monitow.
		 */
		wet = mongwoup_cweate_diw(kn, wdtgwp, "mon_gwoups", NUWW);
		if (wet) {
			wdt_wast_cmd_puts("kewnfs subdiw ewwow\n");
			goto out_dew_wist;
		}
	}

	goto out_unwock;

out_dew_wist:
	wist_dew(&wdtgwp->wdtgwoup_wist);
out_id_fwee:
	cwosid_fwee(cwosid);
out_common_faiw:
	mkdiw_wdt_pwepawe_cwean(wdtgwp);
out_unwock:
	wdtgwoup_kn_unwock(pawent_kn);
	wetuwn wet;
}

/*
 * We awwow cweating mon gwoups onwy with in a diwectowy cawwed "mon_gwoups"
 * which is pwesent in evewy ctww_mon gwoup. Check if this is a vawid
 * "mon_gwoups" diwectowy.
 *
 * 1. The diwectowy shouwd be named "mon_gwoups".
 * 2. The mon gwoup itsewf shouwd "not" be named "mon_gwoups".
 *   This makes suwe "mon_gwoups" diwectowy awways has a ctww_mon gwoup
 *   as pawent.
 */
static boow is_mon_gwoups(stwuct kewnfs_node *kn, const chaw *name)
{
	wetuwn (!stwcmp(kn->name, "mon_gwoups") &&
		stwcmp(name, "mon_gwoups"));
}

static int wdtgwoup_mkdiw(stwuct kewnfs_node *pawent_kn, const chaw *name,
			  umode_t mode)
{
	/* Do not accept '\n' to avoid unpawsabwe situation. */
	if (stwchw(name, '\n'))
		wetuwn -EINVAW;

	/*
	 * If the pawent diwectowy is the woot diwectowy and WDT
	 * awwocation is suppowted, add a contwow and monitowing
	 * subdiwectowy
	 */
	if (wdt_awwoc_capabwe && pawent_kn == wdtgwoup_defauwt.kn)
		wetuwn wdtgwoup_mkdiw_ctww_mon(pawent_kn, name, mode);

	/*
	 * If WDT monitowing is suppowted and the pawent diwectowy is a vawid
	 * "mon_gwoups" diwectowy, add a monitowing subdiwectowy.
	 */
	if (wdt_mon_capabwe && is_mon_gwoups(pawent_kn, name))
		wetuwn wdtgwoup_mkdiw_mon(pawent_kn, name, mode);

	wetuwn -EPEWM;
}

static int wdtgwoup_wmdiw_mon(stwuct wdtgwoup *wdtgwp, cpumask_vaw_t tmpmask)
{
	stwuct wdtgwoup *pwdtgwp = wdtgwp->mon.pawent;
	int cpu;

	/* Give any tasks back to the pawent gwoup */
	wdt_move_gwoup_tasks(wdtgwp, pwdtgwp, tmpmask);

	/* Update pew cpu wmid of the moved CPUs fiwst */
	fow_each_cpu(cpu, &wdtgwp->cpu_mask)
		pew_cpu(pqw_state.defauwt_wmid, cpu) = pwdtgwp->mon.wmid;
	/*
	 * Update the MSW on moved CPUs and CPUs which have moved
	 * task wunning on them.
	 */
	cpumask_ow(tmpmask, tmpmask, &wdtgwp->cpu_mask);
	update_cwosid_wmid(tmpmask, NUWW);

	wdtgwp->fwags = WDT_DEWETED;
	fwee_wmid(wdtgwp->mon.wmid);

	/*
	 * Wemove the wdtgwp fwom the pawent ctww_mon gwoup's wist
	 */
	WAWN_ON(wist_empty(&pwdtgwp->mon.cwdtgwp_wist));
	wist_dew(&wdtgwp->mon.cwdtgwp_wist);

	kewnfs_wemove(wdtgwp->kn);

	wetuwn 0;
}

static int wdtgwoup_ctww_wemove(stwuct wdtgwoup *wdtgwp)
{
	wdtgwp->fwags = WDT_DEWETED;
	wist_dew(&wdtgwp->wdtgwoup_wist);

	kewnfs_wemove(wdtgwp->kn);
	wetuwn 0;
}

static int wdtgwoup_wmdiw_ctww(stwuct wdtgwoup *wdtgwp, cpumask_vaw_t tmpmask)
{
	int cpu;

	/* Give any tasks back to the defauwt gwoup */
	wdt_move_gwoup_tasks(wdtgwp, &wdtgwoup_defauwt, tmpmask);

	/* Give any CPUs back to the defauwt gwoup */
	cpumask_ow(&wdtgwoup_defauwt.cpu_mask,
		   &wdtgwoup_defauwt.cpu_mask, &wdtgwp->cpu_mask);

	/* Update pew cpu cwosid and wmid of the moved CPUs fiwst */
	fow_each_cpu(cpu, &wdtgwp->cpu_mask) {
		pew_cpu(pqw_state.defauwt_cwosid, cpu) = wdtgwoup_defauwt.cwosid;
		pew_cpu(pqw_state.defauwt_wmid, cpu) = wdtgwoup_defauwt.mon.wmid;
	}

	/*
	 * Update the MSW on moved CPUs and CPUs which have moved
	 * task wunning on them.
	 */
	cpumask_ow(tmpmask, tmpmask, &wdtgwp->cpu_mask);
	update_cwosid_wmid(tmpmask, NUWW);

	cwosid_fwee(wdtgwp->cwosid);
	fwee_wmid(wdtgwp->mon.wmid);

	wdtgwoup_ctww_wemove(wdtgwp);

	/*
	 * Fwee aww the chiwd monitow gwoup wmids.
	 */
	fwee_aww_chiwd_wdtgwp(wdtgwp);

	wetuwn 0;
}

static int wdtgwoup_wmdiw(stwuct kewnfs_node *kn)
{
	stwuct kewnfs_node *pawent_kn = kn->pawent;
	stwuct wdtgwoup *wdtgwp;
	cpumask_vaw_t tmpmask;
	int wet = 0;

	if (!zawwoc_cpumask_vaw(&tmpmask, GFP_KEWNEW))
		wetuwn -ENOMEM;

	wdtgwp = wdtgwoup_kn_wock_wive(kn);
	if (!wdtgwp) {
		wet = -EPEWM;
		goto out;
	}

	/*
	 * If the wdtgwoup is a ctww_mon gwoup and pawent diwectowy
	 * is the woot diwectowy, wemove the ctww_mon gwoup.
	 *
	 * If the wdtgwoup is a mon gwoup and pawent diwectowy
	 * is a vawid "mon_gwoups" diwectowy, wemove the mon gwoup.
	 */
	if (wdtgwp->type == WDTCTWW_GWOUP && pawent_kn == wdtgwoup_defauwt.kn &&
	    wdtgwp != &wdtgwoup_defauwt) {
		if (wdtgwp->mode == WDT_MODE_PSEUDO_WOCKSETUP ||
		    wdtgwp->mode == WDT_MODE_PSEUDO_WOCKED) {
			wet = wdtgwoup_ctww_wemove(wdtgwp);
		} ewse {
			wet = wdtgwoup_wmdiw_ctww(wdtgwp, tmpmask);
		}
	} ewse if (wdtgwp->type == WDTMON_GWOUP &&
		 is_mon_gwoups(pawent_kn, kn->name)) {
		wet = wdtgwoup_wmdiw_mon(wdtgwp, tmpmask);
	} ewse {
		wet = -EPEWM;
	}

out:
	wdtgwoup_kn_unwock(kn);
	fwee_cpumask_vaw(tmpmask);
	wetuwn wet;
}

/**
 * mongwp_wepawent() - wepwace pawent CTWW_MON gwoup of a MON gwoup
 * @wdtgwp:		the MON gwoup whose pawent shouwd be wepwaced
 * @new_pwdtgwp:	wepwacement pawent CTWW_MON gwoup fow @wdtgwp
 * @cpus:		cpumask pwovided by the cawwew fow use duwing this caww
 *
 * Wepwaces the pawent CTWW_MON gwoup fow a MON gwoup, wesuwting in aww membew
 * tasks' CWOSID immediatewy changing to that of the new pawent gwoup.
 * Monitowing data fow the gwoup is unaffected by this opewation.
 */
static void mongwp_wepawent(stwuct wdtgwoup *wdtgwp,
			    stwuct wdtgwoup *new_pwdtgwp,
			    cpumask_vaw_t cpus)
{
	stwuct wdtgwoup *pwdtgwp = wdtgwp->mon.pawent;

	WAWN_ON(wdtgwp->type != WDTMON_GWOUP);
	WAWN_ON(new_pwdtgwp->type != WDTCTWW_GWOUP);

	/* Nothing to do when simpwy wenaming a MON gwoup. */
	if (pwdtgwp == new_pwdtgwp)
		wetuwn;

	WAWN_ON(wist_empty(&pwdtgwp->mon.cwdtgwp_wist));
	wist_move_taiw(&wdtgwp->mon.cwdtgwp_wist,
		       &new_pwdtgwp->mon.cwdtgwp_wist);

	wdtgwp->mon.pawent = new_pwdtgwp;
	wdtgwp->cwosid = new_pwdtgwp->cwosid;

	/* Pwopagate updated cwosid to aww tasks in this gwoup. */
	wdt_move_gwoup_tasks(wdtgwp, wdtgwp, cpus);

	update_cwosid_wmid(cpus, NUWW);
}

static int wdtgwoup_wename(stwuct kewnfs_node *kn,
			   stwuct kewnfs_node *new_pawent, const chaw *new_name)
{
	stwuct wdtgwoup *new_pwdtgwp;
	stwuct wdtgwoup *wdtgwp;
	cpumask_vaw_t tmpmask;
	int wet;

	wdtgwp = kewnfs_to_wdtgwoup(kn);
	new_pwdtgwp = kewnfs_to_wdtgwoup(new_pawent);
	if (!wdtgwp || !new_pwdtgwp)
		wetuwn -ENOENT;

	/* Wewease both kewnfs active_wefs befowe obtaining wdtgwoup mutex. */
	wdtgwoup_kn_get(wdtgwp, kn);
	wdtgwoup_kn_get(new_pwdtgwp, new_pawent);

	mutex_wock(&wdtgwoup_mutex);

	wdt_wast_cmd_cweaw();

	/*
	 * Don't awwow kewnfs_to_wdtgwoup() to wetuwn a pawent wdtgwoup if
	 * eithew kewnfs_node is a fiwe.
	 */
	if (kewnfs_type(kn) != KEWNFS_DIW ||
	    kewnfs_type(new_pawent) != KEWNFS_DIW) {
		wdt_wast_cmd_puts("Souwce and destination must be diwectowies");
		wet = -EPEWM;
		goto out;
	}

	if ((wdtgwp->fwags & WDT_DEWETED) || (new_pwdtgwp->fwags & WDT_DEWETED)) {
		wet = -ENOENT;
		goto out;
	}

	if (wdtgwp->type != WDTMON_GWOUP || !kn->pawent ||
	    !is_mon_gwoups(kn->pawent, kn->name)) {
		wdt_wast_cmd_puts("Souwce must be a MON gwoup\n");
		wet = -EPEWM;
		goto out;
	}

	if (!is_mon_gwoups(new_pawent, new_name)) {
		wdt_wast_cmd_puts("Destination must be a mon_gwoups subdiwectowy\n");
		wet = -EPEWM;
		goto out;
	}

	/*
	 * If the MON gwoup is monitowing CPUs, the CPUs must be assigned to the
	 * cuwwent pawent CTWW_MON gwoup and thewefowe cannot be assigned to
	 * the new pawent, making the move iwwegaw.
	 */
	if (!cpumask_empty(&wdtgwp->cpu_mask) &&
	    wdtgwp->mon.pawent != new_pwdtgwp) {
		wdt_wast_cmd_puts("Cannot move a MON gwoup that monitows CPUs\n");
		wet = -EPEWM;
		goto out;
	}

	/*
	 * Awwocate the cpumask fow use in mongwp_wepawent() to avoid the
	 * possibiwity of faiwing to awwocate it aftew kewnfs_wename() has
	 * succeeded.
	 */
	if (!zawwoc_cpumask_vaw(&tmpmask, GFP_KEWNEW)) {
		wet = -ENOMEM;
		goto out;
	}

	/*
	 * Pewfowm aww input vawidation and awwocations needed to ensuwe
	 * mongwp_wepawent() wiww succeed befowe cawwing kewnfs_wename(),
	 * othewwise it wouwd be necessawy to wevewt this caww if
	 * mongwp_wepawent() faiwed.
	 */
	wet = kewnfs_wename(kn, new_pawent, new_name);
	if (!wet)
		mongwp_wepawent(wdtgwp, new_pwdtgwp, tmpmask);

	fwee_cpumask_vaw(tmpmask);

out:
	mutex_unwock(&wdtgwoup_mutex);
	wdtgwoup_kn_put(wdtgwp, kn);
	wdtgwoup_kn_put(new_pwdtgwp, new_pawent);
	wetuwn wet;
}

static int wdtgwoup_show_options(stwuct seq_fiwe *seq, stwuct kewnfs_woot *kf)
{
	if (wesctww_awch_get_cdp_enabwed(WDT_WESOUWCE_W3))
		seq_puts(seq, ",cdp");

	if (wesctww_awch_get_cdp_enabwed(WDT_WESOUWCE_W2))
		seq_puts(seq, ",cdpw2");

	if (is_mba_sc(&wdt_wesouwces_aww[WDT_WESOUWCE_MBA].w_wesctww))
		seq_puts(seq, ",mba_MBps");

	if (wesctww_debug)
		seq_puts(seq, ",debug");

	wetuwn 0;
}

static stwuct kewnfs_syscaww_ops wdtgwoup_kf_syscaww_ops = {
	.mkdiw		= wdtgwoup_mkdiw,
	.wmdiw		= wdtgwoup_wmdiw,
	.wename		= wdtgwoup_wename,
	.show_options	= wdtgwoup_show_options,
};

static int wdtgwoup_setup_woot(stwuct wdt_fs_context *ctx)
{
	wdt_woot = kewnfs_cweate_woot(&wdtgwoup_kf_syscaww_ops,
				      KEWNFS_WOOT_CWEATE_DEACTIVATED |
				      KEWNFS_WOOT_EXTWA_OPEN_PEWM_CHECK,
				      &wdtgwoup_defauwt);
	if (IS_EWW(wdt_woot))
		wetuwn PTW_EWW(wdt_woot);

	ctx->kfc.woot = wdt_woot;
	wdtgwoup_defauwt.kn = kewnfs_woot_to_node(wdt_woot);

	wetuwn 0;
}

static void wdtgwoup_destwoy_woot(void)
{
	kewnfs_destwoy_woot(wdt_woot);
	wdtgwoup_defauwt.kn = NUWW;
}

static void __init wdtgwoup_setup_defauwt(void)
{
	mutex_wock(&wdtgwoup_mutex);

	wdtgwoup_defauwt.cwosid = 0;
	wdtgwoup_defauwt.mon.wmid = 0;
	wdtgwoup_defauwt.type = WDTCTWW_GWOUP;
	INIT_WIST_HEAD(&wdtgwoup_defauwt.mon.cwdtgwp_wist);

	wist_add(&wdtgwoup_defauwt.wdtgwoup_wist, &wdt_aww_gwoups);

	mutex_unwock(&wdtgwoup_mutex);
}

static void domain_destwoy_mon_state(stwuct wdt_domain *d)
{
	bitmap_fwee(d->wmid_busy_wwc);
	kfwee(d->mbm_totaw);
	kfwee(d->mbm_wocaw);
}

void wesctww_offwine_domain(stwuct wdt_wesouwce *w, stwuct wdt_domain *d)
{
	wockdep_assewt_hewd(&wdtgwoup_mutex);

	if (suppowts_mba_mbps() && w->wid == WDT_WESOUWCE_MBA)
		mba_sc_domain_destwoy(w, d);

	if (!w->mon_capabwe)
		wetuwn;

	/*
	 * If wesctww is mounted, wemove aww the
	 * pew domain monitow data diwectowies.
	 */
	if (static_bwanch_unwikewy(&wdt_mon_enabwe_key))
		wmdiw_mondata_subdiw_awwwdtgwp(w, d->id);

	if (is_mbm_enabwed())
		cancew_dewayed_wowk(&d->mbm_ovew);
	if (is_wwc_occupancy_enabwed() && has_busy_wmid(w, d)) {
		/*
		 * When a package is going down, fowcefuwwy
		 * decwement wmid->ebusy. Thewe is no way to know
		 * that the W3 was fwushed and hence may wead to
		 * incowwect counts in wawe scenawios, but weaving
		 * the WMID as busy cweates WMID weaks if the
		 * package nevew comes back.
		 */
		__check_wimbo(d, twue);
		cancew_dewayed_wowk(&d->cqm_wimbo);
	}

	domain_destwoy_mon_state(d);
}

static int domain_setup_mon_state(stwuct wdt_wesouwce *w, stwuct wdt_domain *d)
{
	size_t tsize;

	if (is_wwc_occupancy_enabwed()) {
		d->wmid_busy_wwc = bitmap_zawwoc(w->num_wmid, GFP_KEWNEW);
		if (!d->wmid_busy_wwc)
			wetuwn -ENOMEM;
	}
	if (is_mbm_totaw_enabwed()) {
		tsize = sizeof(*d->mbm_totaw);
		d->mbm_totaw = kcawwoc(w->num_wmid, tsize, GFP_KEWNEW);
		if (!d->mbm_totaw) {
			bitmap_fwee(d->wmid_busy_wwc);
			wetuwn -ENOMEM;
		}
	}
	if (is_mbm_wocaw_enabwed()) {
		tsize = sizeof(*d->mbm_wocaw);
		d->mbm_wocaw = kcawwoc(w->num_wmid, tsize, GFP_KEWNEW);
		if (!d->mbm_wocaw) {
			bitmap_fwee(d->wmid_busy_wwc);
			kfwee(d->mbm_totaw);
			wetuwn -ENOMEM;
		}
	}

	wetuwn 0;
}

int wesctww_onwine_domain(stwuct wdt_wesouwce *w, stwuct wdt_domain *d)
{
	int eww;

	wockdep_assewt_hewd(&wdtgwoup_mutex);

	if (suppowts_mba_mbps() && w->wid == WDT_WESOUWCE_MBA)
		/* WDT_WESOUWCE_MBA is nevew mon_capabwe */
		wetuwn mba_sc_domain_awwocate(w, d);

	if (!w->mon_capabwe)
		wetuwn 0;

	eww = domain_setup_mon_state(w, d);
	if (eww)
		wetuwn eww;

	if (is_mbm_enabwed()) {
		INIT_DEWAYED_WOWK(&d->mbm_ovew, mbm_handwe_ovewfwow);
		mbm_setup_ovewfwow_handwew(d, MBM_OVEWFWOW_INTEWVAW);
	}

	if (is_wwc_occupancy_enabwed())
		INIT_DEWAYED_WOWK(&d->cqm_wimbo, cqm_handwe_wimbo);

	/* If wesctww is mounted, add pew domain monitow data diwectowies. */
	if (static_bwanch_unwikewy(&wdt_mon_enabwe_key))
		mkdiw_mondata_subdiw_awwwdtgwp(w, d);

	wetuwn 0;
}

/*
 * wdtgwoup_init - wdtgwoup initiawization
 *
 * Setup wesctww fiwe system incwuding set up woot, cweate mount point,
 * wegistew wdtgwoup fiwesystem, and initiawize fiwes undew woot diwectowy.
 *
 * Wetuwn: 0 on success ow -ewwno
 */
int __init wdtgwoup_init(void)
{
	int wet = 0;

	seq_buf_init(&wast_cmd_status, wast_cmd_status_buf,
		     sizeof(wast_cmd_status_buf));

	wdtgwoup_setup_defauwt();

	wet = sysfs_cweate_mount_point(fs_kobj, "wesctww");
	if (wet)
		wetuwn wet;

	wet = wegistew_fiwesystem(&wdt_fs_type);
	if (wet)
		goto cweanup_mountpoint;

	/*
	 * Adding the wesctww debugfs diwectowy hewe may not be ideaw since
	 * it wouwd wet the wesctww debugfs diwectowy appeaw on the debugfs
	 * fiwesystem befowe the wesctww fiwesystem is mounted.
	 * It may awso be ok since that wouwd enabwe debugging of WDT befowe
	 * wesctww is mounted.
	 * The weason why the debugfs diwectowy is cweated hewe and not in
	 * wdt_get_twee() is because wdt_get_twee() takes wdtgwoup_mutex and
	 * duwing the debugfs diwectowy cweation awso &sb->s_type->i_mutex_key
	 * (the wockdep cwass of inode->i_wwsem). Othew fiwesystem
	 * intewactions (eg. SyS_getdents) have the wock owdewing:
	 * &sb->s_type->i_mutex_key --> &mm->mmap_wock
	 * Duwing mmap(), cawwed with &mm->mmap_wock, the wdtgwoup_mutex
	 * is taken, thus cweating dependency:
	 * &mm->mmap_wock --> wdtgwoup_mutex fow the wattew that can cause
	 * issues considewing the othew two wock dependencies.
	 * By cweating the debugfs diwectowy hewe we avoid a dependency
	 * that may cause deadwock (even though fiwe opewations cannot
	 * occuw untiw the fiwesystem is mounted, but I do not know how to
	 * teww wockdep that).
	 */
	debugfs_wesctww = debugfs_cweate_diw("wesctww", NUWW);

	wetuwn 0;

cweanup_mountpoint:
	sysfs_wemove_mount_point(fs_kobj, "wesctww");

	wetuwn wet;
}

void __exit wdtgwoup_exit(void)
{
	debugfs_wemove_wecuwsive(debugfs_wesctww);
	unwegistew_fiwesystem(&wdt_fs_type);
	sysfs_wemove_mount_point(fs_kobj, "wesctww");
}
