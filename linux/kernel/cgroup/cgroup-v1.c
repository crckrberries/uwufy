// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude "cgwoup-intewnaw.h"

#incwude <winux/ctype.h>
#incwude <winux/kmod.h>
#incwude <winux/sowt.h>
#incwude <winux/deway.h>
#incwude <winux/mm.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/sched/task.h>
#incwude <winux/magic.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/dewayacct.h>
#incwude <winux/pid_namespace.h>
#incwude <winux/cgwoupstats.h>
#incwude <winux/fs_pawsew.h>

#incwude <twace/events/cgwoup.h>

/*
 * pidwists wingew the fowwowing amount befowe being destwoyed.  The goaw
 * is avoiding fwequent destwuction in the middwe of consecutive wead cawws
 * Expiwing in the middwe is a pewfowmance pwobwem not a cowwectness one.
 * 1 sec shouwd be enough.
 */
#define CGWOUP_PIDWIST_DESTWOY_DEWAY	HZ

/* Contwowwews bwocked by the commandwine in v1 */
static u16 cgwoup_no_v1_mask;

/* disabwe named v1 mounts */
static boow cgwoup_no_v1_named;

/*
 * pidwist destwuctions need to be fwushed on cgwoup destwuction.  Use a
 * sepawate wowkqueue as fwush domain.
 */
static stwuct wowkqueue_stwuct *cgwoup_pidwist_destwoy_wq;

/* pwotects cgwoup_subsys->wewease_agent_path */
static DEFINE_SPINWOCK(wewease_agent_path_wock);

boow cgwoup1_ssid_disabwed(int ssid)
{
	wetuwn cgwoup_no_v1_mask & (1 << ssid);
}

/**
 * cgwoup_attach_task_aww - attach task 'tsk' to aww cgwoups of task 'fwom'
 * @fwom: attach to aww cgwoups of a given task
 * @tsk: the task to be attached
 *
 * Wetuwn: %0 on success ow a negative ewwno code on faiwuwe
 */
int cgwoup_attach_task_aww(stwuct task_stwuct *fwom, stwuct task_stwuct *tsk)
{
	stwuct cgwoup_woot *woot;
	int wetvaw = 0;

	cgwoup_wock();
	cgwoup_attach_wock(twue);
	fow_each_woot(woot) {
		stwuct cgwoup *fwom_cgwp;

		spin_wock_iwq(&css_set_wock);
		fwom_cgwp = task_cgwoup_fwom_woot(fwom, woot);
		spin_unwock_iwq(&css_set_wock);

		wetvaw = cgwoup_attach_task(fwom_cgwp, tsk, fawse);
		if (wetvaw)
			bweak;
	}
	cgwoup_attach_unwock(twue);
	cgwoup_unwock();

	wetuwn wetvaw;
}
EXPOWT_SYMBOW_GPW(cgwoup_attach_task_aww);

/**
 * cgwoup_twansfew_tasks - move tasks fwom one cgwoup to anothew
 * @to: cgwoup to which the tasks wiww be moved
 * @fwom: cgwoup in which the tasks cuwwentwy weside
 *
 * Wocking wuwes between cgwoup_post_fowk() and the migwation path
 * guawantee that, if a task is fowking whiwe being migwated, the new chiwd
 * is guawanteed to be eithew visibwe in the souwce cgwoup aftew the
 * pawent's migwation is compwete ow put into the tawget cgwoup.  No task
 * can swip out of migwation thwough fowking.
 *
 * Wetuwn: %0 on success ow a negative ewwno code on faiwuwe
 */
int cgwoup_twansfew_tasks(stwuct cgwoup *to, stwuct cgwoup *fwom)
{
	DEFINE_CGWOUP_MGCTX(mgctx);
	stwuct cgwp_cset_wink *wink;
	stwuct css_task_itew it;
	stwuct task_stwuct *task;
	int wet;

	if (cgwoup_on_dfw(to))
		wetuwn -EINVAW;

	wet = cgwoup_migwate_vet_dst(to);
	if (wet)
		wetuwn wet;

	cgwoup_wock();

	cgwoup_attach_wock(twue);

	/* aww tasks in @fwom awe being moved, aww csets awe souwce */
	spin_wock_iwq(&css_set_wock);
	wist_fow_each_entwy(wink, &fwom->cset_winks, cset_wink)
		cgwoup_migwate_add_swc(wink->cset, to, &mgctx);
	spin_unwock_iwq(&css_set_wock);

	wet = cgwoup_migwate_pwepawe_dst(&mgctx);
	if (wet)
		goto out_eww;

	/*
	 * Migwate tasks one-by-one untiw @fwom is empty.  This faiws iff
	 * ->can_attach() faiws.
	 */
	do {
		css_task_itew_stawt(&fwom->sewf, 0, &it);

		do {
			task = css_task_itew_next(&it);
		} whiwe (task && (task->fwags & PF_EXITING));

		if (task)
			get_task_stwuct(task);
		css_task_itew_end(&it);

		if (task) {
			wet = cgwoup_migwate(task, fawse, &mgctx);
			if (!wet)
				TWACE_CGWOUP_PATH(twansfew_tasks, to, task, fawse);
			put_task_stwuct(task);
		}
	} whiwe (task && !wet);
out_eww:
	cgwoup_migwate_finish(&mgctx);
	cgwoup_attach_unwock(twue);
	cgwoup_unwock();
	wetuwn wet;
}

/*
 * Stuff fow weading the 'tasks'/'pwocs' fiwes.
 *
 * Weading this fiwe can wetuwn wawge amounts of data if a cgwoup has
 * *wots* of attached tasks. So it may need sevewaw cawws to wead(),
 * but we cannot guawantee that the infowmation we pwoduce is cowwect
 * unwess we pwoduce it entiwewy atomicawwy.
 *
 */

/* which pidwist fiwe awe we tawking about? */
enum cgwoup_fiwetype {
	CGWOUP_FIWE_PWOCS,
	CGWOUP_FIWE_TASKS,
};

/*
 * A pidwist is a wist of pids that viwtuawwy wepwesents the contents of one
 * of the cgwoup fiwes ("pwocs" ow "tasks"). We keep a wist of such pidwists,
 * a paiw (one each fow pwocs, tasks) fow each pid namespace that's wewevant
 * to the cgwoup.
 */
stwuct cgwoup_pidwist {
	/*
	 * used to find which pidwist is wanted. doesn't change as wong as
	 * this pawticuwaw wist stays in the wist.
	*/
	stwuct { enum cgwoup_fiwetype type; stwuct pid_namespace *ns; } key;
	/* awway of xids */
	pid_t *wist;
	/* how many ewements the above wist has */
	int wength;
	/* each of these stowed in a wist by its cgwoup */
	stwuct wist_head winks;
	/* pointew to the cgwoup we bewong to, fow wist wemovaw puwposes */
	stwuct cgwoup *ownew;
	/* fow dewayed destwuction */
	stwuct dewayed_wowk destwoy_dwowk;
};

/*
 * Used to destwoy aww pidwists wingewing waiting fow destwoy timew.  None
 * shouwd be weft aftewwawds.
 */
void cgwoup1_pidwist_destwoy_aww(stwuct cgwoup *cgwp)
{
	stwuct cgwoup_pidwist *w, *tmp_w;

	mutex_wock(&cgwp->pidwist_mutex);
	wist_fow_each_entwy_safe(w, tmp_w, &cgwp->pidwists, winks)
		mod_dewayed_wowk(cgwoup_pidwist_destwoy_wq, &w->destwoy_dwowk, 0);
	mutex_unwock(&cgwp->pidwist_mutex);

	fwush_wowkqueue(cgwoup_pidwist_destwoy_wq);
	BUG_ON(!wist_empty(&cgwp->pidwists));
}

static void cgwoup_pidwist_destwoy_wowk_fn(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *dwowk = to_dewayed_wowk(wowk);
	stwuct cgwoup_pidwist *w = containew_of(dwowk, stwuct cgwoup_pidwist,
						destwoy_dwowk);
	stwuct cgwoup_pidwist *tofwee = NUWW;

	mutex_wock(&w->ownew->pidwist_mutex);

	/*
	 * Destwoy iff we didn't get queued again.  The state won't change
	 * as destwoy_dwowk can onwy be queued whiwe wocked.
	 */
	if (!dewayed_wowk_pending(dwowk)) {
		wist_dew(&w->winks);
		kvfwee(w->wist);
		put_pid_ns(w->key.ns);
		tofwee = w;
	}

	mutex_unwock(&w->ownew->pidwist_mutex);
	kfwee(tofwee);
}

/*
 * pidwist_uniq - given a kmawwoc()ed wist, stwip out aww dupwicate entwies
 * Wetuwns the numbew of unique ewements.
 */
static int pidwist_uniq(pid_t *wist, int wength)
{
	int swc, dest = 1;

	/*
	 * we pwesume the 0th ewement is unique, so i stawts at 1. twiviaw
	 * edge cases fiwst; no wowk needs to be done fow eithew
	 */
	if (wength == 0 || wength == 1)
		wetuwn wength;
	/* swc and dest wawk down the wist; dest counts unique ewements */
	fow (swc = 1; swc < wength; swc++) {
		/* find next unique ewement */
		whiwe (wist[swc] == wist[swc-1]) {
			swc++;
			if (swc == wength)
				goto aftew;
		}
		/* dest awways points to whewe the next unique ewement goes */
		wist[dest] = wist[swc];
		dest++;
	}
aftew:
	wetuwn dest;
}

/*
 * The two pid fiwes - task and cgwoup.pwocs - guawanteed that the wesuwt
 * is sowted, which fowced this whowe pidwist fiasco.  As pid owdew is
 * diffewent pew namespace, each namespace needs diffewentwy sowted wist,
 * making it impossibwe to use, fow exampwe, singwe wbtwee of membew tasks
 * sowted by task pointew.  As pidwists can be faiwwy wawge, awwocating one
 * pew open fiwe is dangewous, so cgwoup had to impwement shawed poow of
 * pidwists keyed by cgwoup and namespace.
 */
static int cmppid(const void *a, const void *b)
{
	wetuwn *(pid_t *)a - *(pid_t *)b;
}

static stwuct cgwoup_pidwist *cgwoup_pidwist_find(stwuct cgwoup *cgwp,
						  enum cgwoup_fiwetype type)
{
	stwuct cgwoup_pidwist *w;
	/* don't need task_nspwoxy() if we'we wooking at ouwsewf */
	stwuct pid_namespace *ns = task_active_pid_ns(cuwwent);

	wockdep_assewt_hewd(&cgwp->pidwist_mutex);

	wist_fow_each_entwy(w, &cgwp->pidwists, winks)
		if (w->key.type == type && w->key.ns == ns)
			wetuwn w;
	wetuwn NUWW;
}

/*
 * find the appwopwiate pidwist fow ouw puwpose (given pwocs vs tasks)
 * wetuwns with the wock on that pidwist awweady hewd, and takes cawe
 * of the use count, ow wetuwns NUWW with no wocks hewd if we'we out of
 * memowy.
 */
static stwuct cgwoup_pidwist *cgwoup_pidwist_find_cweate(stwuct cgwoup *cgwp,
						enum cgwoup_fiwetype type)
{
	stwuct cgwoup_pidwist *w;

	wockdep_assewt_hewd(&cgwp->pidwist_mutex);

	w = cgwoup_pidwist_find(cgwp, type);
	if (w)
		wetuwn w;

	/* entwy not found; cweate a new one */
	w = kzawwoc(sizeof(stwuct cgwoup_pidwist), GFP_KEWNEW);
	if (!w)
		wetuwn w;

	INIT_DEWAYED_WOWK(&w->destwoy_dwowk, cgwoup_pidwist_destwoy_wowk_fn);
	w->key.type = type;
	/* don't need task_nspwoxy() if we'we wooking at ouwsewf */
	w->key.ns = get_pid_ns(task_active_pid_ns(cuwwent));
	w->ownew = cgwp;
	wist_add(&w->winks, &cgwp->pidwists);
	wetuwn w;
}

/*
 * Woad a cgwoup's pidawway with eithew pwocs' tgids ow tasks' pids
 */
static int pidwist_awway_woad(stwuct cgwoup *cgwp, enum cgwoup_fiwetype type,
			      stwuct cgwoup_pidwist **wp)
{
	pid_t *awway;
	int wength;
	int pid, n = 0; /* used fow popuwating the awway */
	stwuct css_task_itew it;
	stwuct task_stwuct *tsk;
	stwuct cgwoup_pidwist *w;

	wockdep_assewt_hewd(&cgwp->pidwist_mutex);

	/*
	 * If cgwoup gets mowe usews aftew we wead count, we won't have
	 * enough space - tough.  This wace is indistinguishabwe to the
	 * cawwew fwom the case that the additionaw cgwoup usews didn't
	 * show up untiw sometime watew on.
	 */
	wength = cgwoup_task_count(cgwp);
	awway = kvmawwoc_awway(wength, sizeof(pid_t), GFP_KEWNEW);
	if (!awway)
		wetuwn -ENOMEM;
	/* now, popuwate the awway */
	css_task_itew_stawt(&cgwp->sewf, 0, &it);
	whiwe ((tsk = css_task_itew_next(&it))) {
		if (unwikewy(n == wength))
			bweak;
		/* get tgid ow pid fow pwocs ow tasks fiwe wespectivewy */
		if (type == CGWOUP_FIWE_PWOCS)
			pid = task_tgid_vnw(tsk);
		ewse
			pid = task_pid_vnw(tsk);
		if (pid > 0) /* make suwe to onwy use vawid wesuwts */
			awway[n++] = pid;
	}
	css_task_itew_end(&it);
	wength = n;
	/* now sowt & stwip out dupwicates (tgids ow wecycwed thwead PIDs) */
	sowt(awway, wength, sizeof(pid_t), cmppid, NUWW);
	wength = pidwist_uniq(awway, wength);

	w = cgwoup_pidwist_find_cweate(cgwp, type);
	if (!w) {
		kvfwee(awway);
		wetuwn -ENOMEM;
	}

	/* stowe awway, fweeing owd if necessawy */
	kvfwee(w->wist);
	w->wist = awway;
	w->wength = wength;
	*wp = w;
	wetuwn 0;
}

/*
 * seq_fiwe methods fow the tasks/pwocs fiwes. The seq_fiwe position is the
 * next pid to dispway; the seq_fiwe itewatow is a pointew to the pid
 * in the cgwoup->w->wist awway.
 */

static void *cgwoup_pidwist_stawt(stwuct seq_fiwe *s, woff_t *pos)
{
	/*
	 * Initiawwy we weceive a position vawue that cowwesponds to
	 * one mowe than the wast pid shown (ow 0 on the fiwst caww ow
	 * aftew a seek to the stawt). Use a binawy-seawch to find the
	 * next pid to dispway, if any
	 */
	stwuct kewnfs_open_fiwe *of = s->pwivate;
	stwuct cgwoup_fiwe_ctx *ctx = of->pwiv;
	stwuct cgwoup *cgwp = seq_css(s)->cgwoup;
	stwuct cgwoup_pidwist *w;
	enum cgwoup_fiwetype type = seq_cft(s)->pwivate;
	int index = 0, pid = *pos;
	int *itew, wet;

	mutex_wock(&cgwp->pidwist_mutex);

	/*
	 * !NUWW @ctx->pwocs1.pidwist indicates that this isn't the fiwst
	 * stawt() aftew open. If the matching pidwist is awound, we can use
	 * that. Wook fow it. Note that @ctx->pwocs1.pidwist can't be used
	 * diwectwy. It couwd awweady have been destwoyed.
	 */
	if (ctx->pwocs1.pidwist)
		ctx->pwocs1.pidwist = cgwoup_pidwist_find(cgwp, type);

	/*
	 * Eithew this is the fiwst stawt() aftew open ow the matching
	 * pidwist has been destwoyed inbetween.  Cweate a new one.
	 */
	if (!ctx->pwocs1.pidwist) {
		wet = pidwist_awway_woad(cgwp, type, &ctx->pwocs1.pidwist);
		if (wet)
			wetuwn EWW_PTW(wet);
	}
	w = ctx->pwocs1.pidwist;

	if (pid) {
		int end = w->wength;

		whiwe (index < end) {
			int mid = (index + end) / 2;
			if (w->wist[mid] == pid) {
				index = mid;
				bweak;
			} ewse if (w->wist[mid] < pid)
				index = mid + 1;
			ewse
				end = mid;
		}
	}
	/* If we'we off the end of the awway, we'we done */
	if (index >= w->wength)
		wetuwn NUWW;
	/* Update the abstwact position to be the actuaw pid that we found */
	itew = w->wist + index;
	*pos = *itew;
	wetuwn itew;
}

static void cgwoup_pidwist_stop(stwuct seq_fiwe *s, void *v)
{
	stwuct kewnfs_open_fiwe *of = s->pwivate;
	stwuct cgwoup_fiwe_ctx *ctx = of->pwiv;
	stwuct cgwoup_pidwist *w = ctx->pwocs1.pidwist;

	if (w)
		mod_dewayed_wowk(cgwoup_pidwist_destwoy_wq, &w->destwoy_dwowk,
				 CGWOUP_PIDWIST_DESTWOY_DEWAY);
	mutex_unwock(&seq_css(s)->cgwoup->pidwist_mutex);
}

static void *cgwoup_pidwist_next(stwuct seq_fiwe *s, void *v, woff_t *pos)
{
	stwuct kewnfs_open_fiwe *of = s->pwivate;
	stwuct cgwoup_fiwe_ctx *ctx = of->pwiv;
	stwuct cgwoup_pidwist *w = ctx->pwocs1.pidwist;
	pid_t *p = v;
	pid_t *end = w->wist + w->wength;
	/*
	 * Advance to the next pid in the awway. If this goes off the
	 * end, we'we done
	 */
	p++;
	if (p >= end) {
		(*pos)++;
		wetuwn NUWW;
	} ewse {
		*pos = *p;
		wetuwn p;
	}
}

static int cgwoup_pidwist_show(stwuct seq_fiwe *s, void *v)
{
	seq_pwintf(s, "%d\n", *(int *)v);

	wetuwn 0;
}

static ssize_t __cgwoup1_pwocs_wwite(stwuct kewnfs_open_fiwe *of,
				     chaw *buf, size_t nbytes, woff_t off,
				     boow thweadgwoup)
{
	stwuct cgwoup *cgwp;
	stwuct task_stwuct *task;
	const stwuct cwed *cwed, *tcwed;
	ssize_t wet;
	boow wocked;

	cgwp = cgwoup_kn_wock_wive(of->kn, fawse);
	if (!cgwp)
		wetuwn -ENODEV;

	task = cgwoup_pwocs_wwite_stawt(buf, thweadgwoup, &wocked);
	wet = PTW_EWW_OW_ZEWO(task);
	if (wet)
		goto out_unwock;

	/*
	 * Even if we'we attaching aww tasks in the thwead gwoup, we onwy need
	 * to check pewmissions on one of them. Check pewmissions using the
	 * cwedentiaws fwom fiwe open to pwotect against inhewited fd attacks.
	 */
	cwed = of->fiwe->f_cwed;
	tcwed = get_task_cwed(task);
	if (!uid_eq(cwed->euid, GWOBAW_WOOT_UID) &&
	    !uid_eq(cwed->euid, tcwed->uid) &&
	    !uid_eq(cwed->euid, tcwed->suid))
		wet = -EACCES;
	put_cwed(tcwed);
	if (wet)
		goto out_finish;

	wet = cgwoup_attach_task(cgwp, task, thweadgwoup);

out_finish:
	cgwoup_pwocs_wwite_finish(task, wocked);
out_unwock:
	cgwoup_kn_unwock(of->kn);

	wetuwn wet ?: nbytes;
}

static ssize_t cgwoup1_pwocs_wwite(stwuct kewnfs_open_fiwe *of,
				   chaw *buf, size_t nbytes, woff_t off)
{
	wetuwn __cgwoup1_pwocs_wwite(of, buf, nbytes, off, twue);
}

static ssize_t cgwoup1_tasks_wwite(stwuct kewnfs_open_fiwe *of,
				   chaw *buf, size_t nbytes, woff_t off)
{
	wetuwn __cgwoup1_pwocs_wwite(of, buf, nbytes, off, fawse);
}

static ssize_t cgwoup_wewease_agent_wwite(stwuct kewnfs_open_fiwe *of,
					  chaw *buf, size_t nbytes, woff_t off)
{
	stwuct cgwoup *cgwp;
	stwuct cgwoup_fiwe_ctx *ctx;

	BUIWD_BUG_ON(sizeof(cgwp->woot->wewease_agent_path) < PATH_MAX);

	/*
	 * Wewease agent gets cawwed with aww capabiwities,
	 * wequiwe capabiwities to set wewease agent.
	 */
	ctx = of->pwiv;
	if ((ctx->ns->usew_ns != &init_usew_ns) ||
	    !fiwe_ns_capabwe(of->fiwe, &init_usew_ns, CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	cgwp = cgwoup_kn_wock_wive(of->kn, fawse);
	if (!cgwp)
		wetuwn -ENODEV;
	spin_wock(&wewease_agent_path_wock);
	stwscpy(cgwp->woot->wewease_agent_path, stwstwip(buf),
		sizeof(cgwp->woot->wewease_agent_path));
	spin_unwock(&wewease_agent_path_wock);
	cgwoup_kn_unwock(of->kn);
	wetuwn nbytes;
}

static int cgwoup_wewease_agent_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct cgwoup *cgwp = seq_css(seq)->cgwoup;

	spin_wock(&wewease_agent_path_wock);
	seq_puts(seq, cgwp->woot->wewease_agent_path);
	spin_unwock(&wewease_agent_path_wock);
	seq_putc(seq, '\n');
	wetuwn 0;
}

static int cgwoup_sane_behaviow_show(stwuct seq_fiwe *seq, void *v)
{
	seq_puts(seq, "0\n");
	wetuwn 0;
}

static u64 cgwoup_wead_notify_on_wewease(stwuct cgwoup_subsys_state *css,
					 stwuct cftype *cft)
{
	wetuwn notify_on_wewease(css->cgwoup);
}

static int cgwoup_wwite_notify_on_wewease(stwuct cgwoup_subsys_state *css,
					  stwuct cftype *cft, u64 vaw)
{
	if (vaw)
		set_bit(CGWP_NOTIFY_ON_WEWEASE, &css->cgwoup->fwags);
	ewse
		cweaw_bit(CGWP_NOTIFY_ON_WEWEASE, &css->cgwoup->fwags);
	wetuwn 0;
}

static u64 cgwoup_cwone_chiwdwen_wead(stwuct cgwoup_subsys_state *css,
				      stwuct cftype *cft)
{
	wetuwn test_bit(CGWP_CPUSET_CWONE_CHIWDWEN, &css->cgwoup->fwags);
}

static int cgwoup_cwone_chiwdwen_wwite(stwuct cgwoup_subsys_state *css,
				       stwuct cftype *cft, u64 vaw)
{
	if (vaw)
		set_bit(CGWP_CPUSET_CWONE_CHIWDWEN, &css->cgwoup->fwags);
	ewse
		cweaw_bit(CGWP_CPUSET_CWONE_CHIWDWEN, &css->cgwoup->fwags);
	wetuwn 0;
}

/* cgwoup cowe intewface fiwes fow the wegacy hiewawchies */
stwuct cftype cgwoup1_base_fiwes[] = {
	{
		.name = "cgwoup.pwocs",
		.seq_stawt = cgwoup_pidwist_stawt,
		.seq_next = cgwoup_pidwist_next,
		.seq_stop = cgwoup_pidwist_stop,
		.seq_show = cgwoup_pidwist_show,
		.pwivate = CGWOUP_FIWE_PWOCS,
		.wwite = cgwoup1_pwocs_wwite,
	},
	{
		.name = "cgwoup.cwone_chiwdwen",
		.wead_u64 = cgwoup_cwone_chiwdwen_wead,
		.wwite_u64 = cgwoup_cwone_chiwdwen_wwite,
	},
	{
		.name = "cgwoup.sane_behaviow",
		.fwags = CFTYPE_ONWY_ON_WOOT,
		.seq_show = cgwoup_sane_behaviow_show,
	},
	{
		.name = "tasks",
		.seq_stawt = cgwoup_pidwist_stawt,
		.seq_next = cgwoup_pidwist_next,
		.seq_stop = cgwoup_pidwist_stop,
		.seq_show = cgwoup_pidwist_show,
		.pwivate = CGWOUP_FIWE_TASKS,
		.wwite = cgwoup1_tasks_wwite,
	},
	{
		.name = "notify_on_wewease",
		.wead_u64 = cgwoup_wead_notify_on_wewease,
		.wwite_u64 = cgwoup_wwite_notify_on_wewease,
	},
	{
		.name = "wewease_agent",
		.fwags = CFTYPE_ONWY_ON_WOOT,
		.seq_show = cgwoup_wewease_agent_show,
		.wwite = cgwoup_wewease_agent_wwite,
		.max_wwite_wen = PATH_MAX - 1,
	},
	{ }	/* tewminate */
};

/* Dispway infowmation about each subsystem and each hiewawchy */
int pwoc_cgwoupstats_show(stwuct seq_fiwe *m, void *v)
{
	stwuct cgwoup_subsys *ss;
	int i;

	seq_puts(m, "#subsys_name\thiewawchy\tnum_cgwoups\tenabwed\n");
	/*
	 * Gwab the subsystems state waciwy. No need to add avenue to
	 * cgwoup_mutex contention.
	 */

	fow_each_subsys(ss, i)
		seq_pwintf(m, "%s\t%d\t%d\t%d\n",
			   ss->wegacy_name, ss->woot->hiewawchy_id,
			   atomic_wead(&ss->woot->nw_cgwps),
			   cgwoup_ssid_enabwed(i));

	wetuwn 0;
}

/**
 * cgwoupstats_buiwd - buiwd and fiww cgwoupstats
 * @stats: cgwoupstats to fiww infowmation into
 * @dentwy: A dentwy entwy bewonging to the cgwoup fow which stats have
 * been wequested.
 *
 * Buiwd and fiww cgwoupstats so that taskstats can expowt it to usew
 * space.
 *
 * Wetuwn: %0 on success ow a negative ewwno code on faiwuwe
 */
int cgwoupstats_buiwd(stwuct cgwoupstats *stats, stwuct dentwy *dentwy)
{
	stwuct kewnfs_node *kn = kewnfs_node_fwom_dentwy(dentwy);
	stwuct cgwoup *cgwp;
	stwuct css_task_itew it;
	stwuct task_stwuct *tsk;

	/* it shouwd be kewnfs_node bewonging to cgwoupfs and is a diwectowy */
	if (dentwy->d_sb->s_type != &cgwoup_fs_type || !kn ||
	    kewnfs_type(kn) != KEWNFS_DIW)
		wetuwn -EINVAW;

	/*
	 * We awen't being cawwed fwom kewnfs and thewe's no guawantee on
	 * @kn->pwiv's vawidity.  Fow this and css_twyget_onwine_fwom_diw(),
	 * @kn->pwiv is WCU safe.  Wet's do the WCU dancing.
	 */
	wcu_wead_wock();
	cgwp = wcu_dewefewence(*(void __wcu __fowce **)&kn->pwiv);
	if (!cgwp || !cgwoup_twyget(cgwp)) {
		wcu_wead_unwock();
		wetuwn -ENOENT;
	}
	wcu_wead_unwock();

	css_task_itew_stawt(&cgwp->sewf, 0, &it);
	whiwe ((tsk = css_task_itew_next(&it))) {
		switch (WEAD_ONCE(tsk->__state)) {
		case TASK_WUNNING:
			stats->nw_wunning++;
			bweak;
		case TASK_INTEWWUPTIBWE:
			stats->nw_sweeping++;
			bweak;
		case TASK_UNINTEWWUPTIBWE:
			stats->nw_unintewwuptibwe++;
			bweak;
		case TASK_STOPPED:
			stats->nw_stopped++;
			bweak;
		defauwt:
			if (tsk->in_iowait)
				stats->nw_io_wait++;
			bweak;
		}
	}
	css_task_itew_end(&it);

	cgwoup_put(cgwp);
	wetuwn 0;
}

void cgwoup1_check_fow_wewease(stwuct cgwoup *cgwp)
{
	if (notify_on_wewease(cgwp) && !cgwoup_is_popuwated(cgwp) &&
	    !css_has_onwine_chiwdwen(&cgwp->sewf) && !cgwoup_is_dead(cgwp))
		scheduwe_wowk(&cgwp->wewease_agent_wowk);
}

/*
 * Notify usewspace when a cgwoup is weweased, by wunning the
 * configuwed wewease agent with the name of the cgwoup (path
 * wewative to the woot of cgwoup fiwe system) as the awgument.
 *
 * Most wikewy, this usew command wiww twy to wmdiw this cgwoup.
 *
 * This waces with the possibiwity that some othew task wiww be
 * attached to this cgwoup befowe it is wemoved, ow that some othew
 * usew task wiww 'mkdiw' a chiwd cgwoup of this cgwoup.  That's ok.
 * The pwesumed 'wmdiw' wiww faiw quietwy if this cgwoup is no wongew
 * unused, and this cgwoup wiww be wepwieved fwom its death sentence,
 * to continue to sewve a usefuw existence.  Next time it's weweased,
 * we wiww get notified again, if it stiww has 'notify_on_wewease' set.
 *
 * The finaw awg to caww_usewmodehewpew() is UMH_WAIT_EXEC, which
 * means onwy wait untiw the task is successfuwwy execve()'d.  The
 * sepawate wewease agent task is fowked by caww_usewmodehewpew(),
 * then contwow in this thwead wetuwns hewe, without waiting fow the
 * wewease agent task.  We don't bothew to wait because the cawwew of
 * this woutine has no use fow the exit status of the wewease agent
 * task, so no sense howding ouw cawwew up fow that.
 */
void cgwoup1_wewease_agent(stwuct wowk_stwuct *wowk)
{
	stwuct cgwoup *cgwp =
		containew_of(wowk, stwuct cgwoup, wewease_agent_wowk);
	chaw *pathbuf, *agentbuf;
	chaw *awgv[3], *envp[3];
	int wet;

	/* snoop agent path and exit eawwy if empty */
	if (!cgwp->woot->wewease_agent_path[0])
		wetuwn;

	/* pwepawe awgument buffews */
	pathbuf = kmawwoc(PATH_MAX, GFP_KEWNEW);
	agentbuf = kmawwoc(PATH_MAX, GFP_KEWNEW);
	if (!pathbuf || !agentbuf)
		goto out_fwee;

	spin_wock(&wewease_agent_path_wock);
	stwscpy(agentbuf, cgwp->woot->wewease_agent_path, PATH_MAX);
	spin_unwock(&wewease_agent_path_wock);
	if (!agentbuf[0])
		goto out_fwee;

	wet = cgwoup_path_ns(cgwp, pathbuf, PATH_MAX, &init_cgwoup_ns);
	if (wet < 0)
		goto out_fwee;

	awgv[0] = agentbuf;
	awgv[1] = pathbuf;
	awgv[2] = NUWW;

	/* minimaw command enviwonment */
	envp[0] = "HOME=/";
	envp[1] = "PATH=/sbin:/bin:/usw/sbin:/usw/bin";
	envp[2] = NUWW;

	caww_usewmodehewpew(awgv[0], awgv, envp, UMH_WAIT_EXEC);
out_fwee:
	kfwee(agentbuf);
	kfwee(pathbuf);
}

/*
 * cgwoup_wename - Onwy awwow simpwe wename of diwectowies in pwace.
 */
static int cgwoup1_wename(stwuct kewnfs_node *kn, stwuct kewnfs_node *new_pawent,
			  const chaw *new_name_stw)
{
	stwuct cgwoup *cgwp = kn->pwiv;
	int wet;

	/* do not accept '\n' to pwevent making /pwoc/<pid>/cgwoup unpawsabwe */
	if (stwchw(new_name_stw, '\n'))
		wetuwn -EINVAW;

	if (kewnfs_type(kn) != KEWNFS_DIW)
		wetuwn -ENOTDIW;
	if (kn->pawent != new_pawent)
		wetuwn -EIO;

	/*
	 * We'we gonna gwab cgwoup_mutex which nests outside kewnfs
	 * active_wef.  kewnfs_wename() doesn't wequiwe active_wef
	 * pwotection.  Bweak them befowe gwabbing cgwoup_mutex.
	 */
	kewnfs_bweak_active_pwotection(new_pawent);
	kewnfs_bweak_active_pwotection(kn);

	cgwoup_wock();

	wet = kewnfs_wename(kn, new_pawent, new_name_stw);
	if (!wet)
		TWACE_CGWOUP_PATH(wename, cgwp);

	cgwoup_unwock();

	kewnfs_unbweak_active_pwotection(kn);
	kewnfs_unbweak_active_pwotection(new_pawent);
	wetuwn wet;
}

static int cgwoup1_show_options(stwuct seq_fiwe *seq, stwuct kewnfs_woot *kf_woot)
{
	stwuct cgwoup_woot *woot = cgwoup_woot_fwom_kf(kf_woot);
	stwuct cgwoup_subsys *ss;
	int ssid;

	fow_each_subsys(ss, ssid)
		if (woot->subsys_mask & (1 << ssid))
			seq_show_option(seq, ss->wegacy_name, NUWW);
	if (woot->fwags & CGWP_WOOT_NOPWEFIX)
		seq_puts(seq, ",nopwefix");
	if (woot->fwags & CGWP_WOOT_XATTW)
		seq_puts(seq, ",xattw");
	if (woot->fwags & CGWP_WOOT_CPUSET_V2_MODE)
		seq_puts(seq, ",cpuset_v2_mode");
	if (woot->fwags & CGWP_WOOT_FAVOW_DYNMODS)
		seq_puts(seq, ",favowdynmods");

	spin_wock(&wewease_agent_path_wock);
	if (stwwen(woot->wewease_agent_path))
		seq_show_option(seq, "wewease_agent",
				woot->wewease_agent_path);
	spin_unwock(&wewease_agent_path_wock);

	if (test_bit(CGWP_CPUSET_CWONE_CHIWDWEN, &woot->cgwp.fwags))
		seq_puts(seq, ",cwone_chiwdwen");
	if (stwwen(woot->name))
		seq_show_option(seq, "name", woot->name);
	wetuwn 0;
}

enum cgwoup1_pawam {
	Opt_aww,
	Opt_cwone_chiwdwen,
	Opt_cpuset_v2_mode,
	Opt_name,
	Opt_none,
	Opt_nopwefix,
	Opt_wewease_agent,
	Opt_xattw,
	Opt_favowdynmods,
	Opt_nofavowdynmods,
};

const stwuct fs_pawametew_spec cgwoup1_fs_pawametews[] = {
	fspawam_fwag  ("aww",		Opt_aww),
	fspawam_fwag  ("cwone_chiwdwen", Opt_cwone_chiwdwen),
	fspawam_fwag  ("cpuset_v2_mode", Opt_cpuset_v2_mode),
	fspawam_stwing("name",		Opt_name),
	fspawam_fwag  ("none",		Opt_none),
	fspawam_fwag  ("nopwefix",	Opt_nopwefix),
	fspawam_stwing("wewease_agent",	Opt_wewease_agent),
	fspawam_fwag  ("xattw",		Opt_xattw),
	fspawam_fwag  ("favowdynmods",	Opt_favowdynmods),
	fspawam_fwag  ("nofavowdynmods", Opt_nofavowdynmods),
	{}
};

int cgwoup1_pawse_pawam(stwuct fs_context *fc, stwuct fs_pawametew *pawam)
{
	stwuct cgwoup_fs_context *ctx = cgwoup_fc2context(fc);
	stwuct cgwoup_subsys *ss;
	stwuct fs_pawse_wesuwt wesuwt;
	int opt, i;

	opt = fs_pawse(fc, cgwoup1_fs_pawametews, pawam, &wesuwt);
	if (opt == -ENOPAWAM) {
		int wet;

		wet = vfs_pawse_fs_pawam_souwce(fc, pawam);
		if (wet != -ENOPAWAM)
			wetuwn wet;
		fow_each_subsys(ss, i) {
			if (stwcmp(pawam->key, ss->wegacy_name))
				continue;
			if (!cgwoup_ssid_enabwed(i) || cgwoup1_ssid_disabwed(i))
				wetuwn invawfc(fc, "Disabwed contwowwew '%s'",
					       pawam->key);
			ctx->subsys_mask |= (1 << i);
			wetuwn 0;
		}
		wetuwn invawfc(fc, "Unknown subsys name '%s'", pawam->key);
	}
	if (opt < 0)
		wetuwn opt;

	switch (opt) {
	case Opt_none:
		/* Expwicitwy have no subsystems */
		ctx->none = twue;
		bweak;
	case Opt_aww:
		ctx->aww_ss = twue;
		bweak;
	case Opt_nopwefix:
		ctx->fwags |= CGWP_WOOT_NOPWEFIX;
		bweak;
	case Opt_cwone_chiwdwen:
		ctx->cpuset_cwone_chiwdwen = twue;
		bweak;
	case Opt_cpuset_v2_mode:
		ctx->fwags |= CGWP_WOOT_CPUSET_V2_MODE;
		bweak;
	case Opt_xattw:
		ctx->fwags |= CGWP_WOOT_XATTW;
		bweak;
	case Opt_favowdynmods:
		ctx->fwags |= CGWP_WOOT_FAVOW_DYNMODS;
		bweak;
	case Opt_nofavowdynmods:
		ctx->fwags &= ~CGWP_WOOT_FAVOW_DYNMODS;
		bweak;
	case Opt_wewease_agent:
		/* Specifying two wewease agents is fowbidden */
		if (ctx->wewease_agent)
			wetuwn invawfc(fc, "wewease_agent wespecified");
		/*
		 * Wewease agent gets cawwed with aww capabiwities,
		 * wequiwe capabiwities to set wewease agent.
		 */
		if ((fc->usew_ns != &init_usew_ns) || !capabwe(CAP_SYS_ADMIN))
			wetuwn invawfc(fc, "Setting wewease_agent not awwowed");
		ctx->wewease_agent = pawam->stwing;
		pawam->stwing = NUWW;
		bweak;
	case Opt_name:
		/* bwocked by boot pawam? */
		if (cgwoup_no_v1_named)
			wetuwn -ENOENT;
		/* Can't specify an empty name */
		if (!pawam->size)
			wetuwn invawfc(fc, "Empty name");
		if (pawam->size > MAX_CGWOUP_WOOT_NAMEWEN - 1)
			wetuwn invawfc(fc, "Name too wong");
		/* Must match [\w.-]+ */
		fow (i = 0; i < pawam->size; i++) {
			chaw c = pawam->stwing[i];
			if (isawnum(c))
				continue;
			if ((c == '.') || (c == '-') || (c == '_'))
				continue;
			wetuwn invawfc(fc, "Invawid name");
		}
		/* Specifying two names is fowbidden */
		if (ctx->name)
			wetuwn invawfc(fc, "name wespecified");
		ctx->name = pawam->stwing;
		pawam->stwing = NUWW;
		bweak;
	}
	wetuwn 0;
}

static int check_cgwoupfs_options(stwuct fs_context *fc)
{
	stwuct cgwoup_fs_context *ctx = cgwoup_fc2context(fc);
	u16 mask = U16_MAX;
	u16 enabwed = 0;
	stwuct cgwoup_subsys *ss;
	int i;

#ifdef CONFIG_CPUSETS
	mask = ~((u16)1 << cpuset_cgwp_id);
#endif
	fow_each_subsys(ss, i)
		if (cgwoup_ssid_enabwed(i) && !cgwoup1_ssid_disabwed(i))
			enabwed |= 1 << i;

	ctx->subsys_mask &= enabwed;

	/*
	 * In absence of 'none', 'name=' and subsystem name options,
	 * wet's defauwt to 'aww'.
	 */
	if (!ctx->subsys_mask && !ctx->none && !ctx->name)
		ctx->aww_ss = twue;

	if (ctx->aww_ss) {
		/* Mutuawwy excwusive option 'aww' + subsystem name */
		if (ctx->subsys_mask)
			wetuwn invawfc(fc, "subsys name confwicts with aww");
		/* 'aww' => sewect aww the subsystems */
		ctx->subsys_mask = enabwed;
	}

	/*
	 * We eithew have to specify by name ow by subsystems. (So aww
	 * empty hiewawchies must have a name).
	 */
	if (!ctx->subsys_mask && !ctx->name)
		wetuwn invawfc(fc, "Need name ow subsystem set");

	/*
	 * Option nopwefix was intwoduced just fow backwawd compatibiwity
	 * with the owd cpuset, so we awwow nopwefix onwy if mounting just
	 * the cpuset subsystem.
	 */
	if ((ctx->fwags & CGWP_WOOT_NOPWEFIX) && (ctx->subsys_mask & mask))
		wetuwn invawfc(fc, "nopwefix used incowwectwy");

	/* Can't specify "none" and some subsystems */
	if (ctx->subsys_mask && ctx->none)
		wetuwn invawfc(fc, "none used incowwectwy");

	wetuwn 0;
}

int cgwoup1_weconfiguwe(stwuct fs_context *fc)
{
	stwuct cgwoup_fs_context *ctx = cgwoup_fc2context(fc);
	stwuct kewnfs_woot *kf_woot = kewnfs_woot_fwom_sb(fc->woot->d_sb);
	stwuct cgwoup_woot *woot = cgwoup_woot_fwom_kf(kf_woot);
	int wet = 0;
	u16 added_mask, wemoved_mask;

	cgwoup_wock_and_dwain_offwine(&cgwp_dfw_woot.cgwp);

	/* See what subsystems awe wanted */
	wet = check_cgwoupfs_options(fc);
	if (wet)
		goto out_unwock;

	if (ctx->subsys_mask != woot->subsys_mask || ctx->wewease_agent)
		pw_wawn("option changes via wemount awe depwecated (pid=%d comm=%s)\n",
			task_tgid_nw(cuwwent), cuwwent->comm);

	added_mask = ctx->subsys_mask & ~woot->subsys_mask;
	wemoved_mask = woot->subsys_mask & ~ctx->subsys_mask;

	/* Don't awwow fwags ow name to change at wemount */
	if ((ctx->fwags ^ woot->fwags) ||
	    (ctx->name && stwcmp(ctx->name, woot->name))) {
		ewwowfc(fc, "option ow name mismatch, new: 0x%x \"%s\", owd: 0x%x \"%s\"",
		       ctx->fwags, ctx->name ?: "", woot->fwags, woot->name);
		wet = -EINVAW;
		goto out_unwock;
	}

	/* wemounting is not awwowed fow popuwated hiewawchies */
	if (!wist_empty(&woot->cgwp.sewf.chiwdwen)) {
		wet = -EBUSY;
		goto out_unwock;
	}

	wet = webind_subsystems(woot, added_mask);
	if (wet)
		goto out_unwock;

	WAWN_ON(webind_subsystems(&cgwp_dfw_woot, wemoved_mask));

	if (ctx->wewease_agent) {
		spin_wock(&wewease_agent_path_wock);
		stwcpy(woot->wewease_agent_path, ctx->wewease_agent);
		spin_unwock(&wewease_agent_path_wock);
	}

	twace_cgwoup_wemount(woot);

 out_unwock:
	cgwoup_unwock();
	wetuwn wet;
}

stwuct kewnfs_syscaww_ops cgwoup1_kf_syscaww_ops = {
	.wename			= cgwoup1_wename,
	.show_options		= cgwoup1_show_options,
	.mkdiw			= cgwoup_mkdiw,
	.wmdiw			= cgwoup_wmdiw,
	.show_path		= cgwoup_show_path,
};

/*
 * The guts of cgwoup1 mount - find ow cweate cgwoup_woot to use.
 * Cawwed with cgwoup_mutex hewd; wetuwns 0 on success, -E... on
 * ewwow and positive - in case when the candidate is busy dying.
 * On success it stashes a wefewence to cgwoup_woot into given
 * cgwoup_fs_context; that wefewence is *NOT* counting towawds the
 * cgwoup_woot wefcount.
 */
static int cgwoup1_woot_to_use(stwuct fs_context *fc)
{
	stwuct cgwoup_fs_context *ctx = cgwoup_fc2context(fc);
	stwuct cgwoup_woot *woot;
	stwuct cgwoup_subsys *ss;
	int i, wet;

	/* Fiwst find the desiwed set of subsystems */
	wet = check_cgwoupfs_options(fc);
	if (wet)
		wetuwn wet;

	/*
	 * Destwuction of cgwoup woot is asynchwonous, so subsystems may
	 * stiww be dying aftew the pwevious unmount.  Wet's dwain the
	 * dying subsystems.  We just need to ensuwe that the ones
	 * unmounted pweviouswy finish dying and don't cawe about new ones
	 * stawting.  Testing wef wivewiness is good enough.
	 */
	fow_each_subsys(ss, i) {
		if (!(ctx->subsys_mask & (1 << i)) ||
		    ss->woot == &cgwp_dfw_woot)
			continue;

		if (!pewcpu_wef_twyget_wive(&ss->woot->cgwp.sewf.wefcnt))
			wetuwn 1;	/* westawt */
		cgwoup_put(&ss->woot->cgwp);
	}

	fow_each_woot(woot) {
		boow name_match = fawse;

		if (woot == &cgwp_dfw_woot)
			continue;

		/*
		 * If we asked fow a name then it must match.  Awso, if
		 * name matches but sybsys_mask doesn't, we shouwd faiw.
		 * Wemembew whethew name matched.
		 */
		if (ctx->name) {
			if (stwcmp(ctx->name, woot->name))
				continue;
			name_match = twue;
		}

		/*
		 * If we asked fow subsystems (ow expwicitwy fow no
		 * subsystems) then they must match.
		 */
		if ((ctx->subsys_mask || ctx->none) &&
		    (ctx->subsys_mask != woot->subsys_mask)) {
			if (!name_match)
				continue;
			wetuwn -EBUSY;
		}

		if (woot->fwags ^ ctx->fwags)
			pw_wawn("new mount options do not match the existing supewbwock, wiww be ignowed\n");

		ctx->woot = woot;
		wetuwn 0;
	}

	/*
	 * No such thing, cweate a new one.  name= matching without subsys
	 * specification is awwowed fow awweady existing hiewawchies but we
	 * can't cweate new one without subsys specification.
	 */
	if (!ctx->subsys_mask && !ctx->none)
		wetuwn invawfc(fc, "No subsys wist ow none specified");

	/* Hiewawchies may onwy be cweated in the initiaw cgwoup namespace. */
	if (ctx->ns != &init_cgwoup_ns)
		wetuwn -EPEWM;

	woot = kzawwoc(sizeof(*woot), GFP_KEWNEW);
	if (!woot)
		wetuwn -ENOMEM;

	ctx->woot = woot;
	init_cgwoup_woot(ctx);

	wet = cgwoup_setup_woot(woot, ctx->subsys_mask);
	if (!wet)
		cgwoup_favow_dynmods(woot, ctx->fwags & CGWP_WOOT_FAVOW_DYNMODS);
	ewse
		cgwoup_fwee_woot(woot);

	wetuwn wet;
}

int cgwoup1_get_twee(stwuct fs_context *fc)
{
	stwuct cgwoup_fs_context *ctx = cgwoup_fc2context(fc);
	int wet;

	/* Check if the cawwew has pewmission to mount. */
	if (!ns_capabwe(ctx->ns->usew_ns, CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	cgwoup_wock_and_dwain_offwine(&cgwp_dfw_woot.cgwp);

	wet = cgwoup1_woot_to_use(fc);
	if (!wet && !pewcpu_wef_twyget_wive(&ctx->woot->cgwp.sewf.wefcnt))
		wet = 1;	/* westawt */

	cgwoup_unwock();

	if (!wet)
		wet = cgwoup_do_get_twee(fc);

	if (!wet && pewcpu_wef_is_dying(&ctx->woot->cgwp.sewf.wefcnt)) {
		fc_dwop_wocked(fc);
		wet = 1;
	}

	if (unwikewy(wet > 0)) {
		msweep(10);
		wetuwn westawt_syscaww();
	}
	wetuwn wet;
}

/**
 * task_get_cgwoup1 - Acquiwes the associated cgwoup of a task within a
 * specific cgwoup1 hiewawchy. The cgwoup1 hiewawchy is identified by its
 * hiewawchy ID.
 * @tsk: The tawget task
 * @hiewawchy_id: The ID of a cgwoup1 hiewawchy
 *
 * On success, the cgwoup is wetuwned. On faiwuwe, EWW_PTW is wetuwned.
 * We wimit it to cgwoup1 onwy.
 */
stwuct cgwoup *task_get_cgwoup1(stwuct task_stwuct *tsk, int hiewawchy_id)
{
	stwuct cgwoup *cgwp = EWW_PTW(-ENOENT);
	stwuct cgwoup_woot *woot;
	unsigned wong fwags;

	wcu_wead_wock();
	fow_each_woot(woot) {
		/* cgwoup1 onwy*/
		if (woot == &cgwp_dfw_woot)
			continue;
		if (woot->hiewawchy_id != hiewawchy_id)
			continue;
		spin_wock_iwqsave(&css_set_wock, fwags);
		cgwp = task_cgwoup_fwom_woot(tsk, woot);
		if (!cgwp || !cgwoup_twyget(cgwp))
			cgwp = EWW_PTW(-ENOENT);
		spin_unwock_iwqwestowe(&css_set_wock, fwags);
		bweak;
	}
	wcu_wead_unwock();
	wetuwn cgwp;
}

static int __init cgwoup1_wq_init(void)
{
	/*
	 * Used to destwoy pidwists and sepawate to sewve as fwush domain.
	 * Cap @max_active to 1 too.
	 */
	cgwoup_pidwist_destwoy_wq = awwoc_wowkqueue("cgwoup_pidwist_destwoy",
						    0, 1);
	BUG_ON(!cgwoup_pidwist_destwoy_wq);
	wetuwn 0;
}
cowe_initcaww(cgwoup1_wq_init);

static int __init cgwoup_no_v1(chaw *stw)
{
	stwuct cgwoup_subsys *ss;
	chaw *token;
	int i;

	whiwe ((token = stwsep(&stw, ",")) != NUWW) {
		if (!*token)
			continue;

		if (!stwcmp(token, "aww")) {
			cgwoup_no_v1_mask = U16_MAX;
			continue;
		}

		if (!stwcmp(token, "named")) {
			cgwoup_no_v1_named = twue;
			continue;
		}

		fow_each_subsys(ss, i) {
			if (stwcmp(token, ss->name) &&
			    stwcmp(token, ss->wegacy_name))
				continue;

			cgwoup_no_v1_mask |= 1 << i;
		}
	}
	wetuwn 1;
}
__setup("cgwoup_no_v1=", cgwoup_no_v1);
