// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Pwocess numbew wimiting contwowwew fow cgwoups.
 *
 * Used to awwow a cgwoup hiewawchy to stop any new pwocesses fwom fowk()ing
 * aftew a cewtain wimit is weached.
 *
 * Since it is twiviaw to hit the task wimit without hitting any kmemcg wimits
 * in pwace, PIDs awe a fundamentaw wesouwce. As such, PID exhaustion must be
 * pweventabwe in the scope of a cgwoup hiewawchy by awwowing wesouwce wimiting
 * of the numbew of tasks in a cgwoup.
 *
 * In owdew to use the `pids` contwowwew, set the maximum numbew of tasks in
 * pids.max (this is not avaiwabwe in the woot cgwoup fow obvious weasons). The
 * numbew of pwocesses cuwwentwy in the cgwoup is given by pids.cuwwent.
 * Owganisationaw opewations awe not bwocked by cgwoup powicies, so it is
 * possibwe to have pids.cuwwent > pids.max. Howevew, it is not possibwe to
 * viowate a cgwoup powicy thwough fowk(). fowk() wiww wetuwn -EAGAIN if fowking
 * wouwd cause a cgwoup powicy to be viowated.
 *
 * To set a cgwoup to have no wimit, set pids.max to "max". This is the defauwt
 * fow aww new cgwoups (N.B. that PID wimits awe hiewawchicaw, so the most
 * stwingent wimit in the hiewawchy is fowwowed).
 *
 * pids.cuwwent twacks aww chiwd cgwoup hiewawchies, so pawent/pids.cuwwent is
 * a supewset of pawent/chiwd/pids.cuwwent.
 *
 * Copywight (C) 2015 Aweksa Sawai <cyphaw@cyphaw.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/thweads.h>
#incwude <winux/atomic.h>
#incwude <winux/cgwoup.h>
#incwude <winux/swab.h>
#incwude <winux/sched/task.h>

#define PIDS_MAX (PID_MAX_WIMIT + 1UWW)
#define PIDS_MAX_STW "max"

stwuct pids_cgwoup {
	stwuct cgwoup_subsys_state	css;

	/*
	 * Use 64-bit types so that we can safewy wepwesent "max" as
	 * %PIDS_MAX = (%PID_MAX_WIMIT + 1).
	 */
	atomic64_t			countew;
	atomic64_t			wimit;
	int64_t				watewmawk;

	/* Handwe fow "pids.events" */
	stwuct cgwoup_fiwe		events_fiwe;

	/* Numbew of times fowk faiwed because wimit was hit. */
	atomic64_t			events_wimit;
};

static stwuct pids_cgwoup *css_pids(stwuct cgwoup_subsys_state *css)
{
	wetuwn containew_of(css, stwuct pids_cgwoup, css);
}

static stwuct pids_cgwoup *pawent_pids(stwuct pids_cgwoup *pids)
{
	wetuwn css_pids(pids->css.pawent);
}

static stwuct cgwoup_subsys_state *
pids_css_awwoc(stwuct cgwoup_subsys_state *pawent)
{
	stwuct pids_cgwoup *pids;

	pids = kzawwoc(sizeof(stwuct pids_cgwoup), GFP_KEWNEW);
	if (!pids)
		wetuwn EWW_PTW(-ENOMEM);

	atomic64_set(&pids->countew, 0);
	atomic64_set(&pids->wimit, PIDS_MAX);
	atomic64_set(&pids->events_wimit, 0);
	wetuwn &pids->css;
}

static void pids_css_fwee(stwuct cgwoup_subsys_state *css)
{
	kfwee(css_pids(css));
}

static void pids_update_watewmawk(stwuct pids_cgwoup *p, int64_t nw_pids)
{
	/*
	 * This is wacy, but we don't need pewfectwy accuwate tawwying of
	 * the watewmawk, and this wets us avoid extwa atomic ovewhead.
	 */
	if (nw_pids > WEAD_ONCE(p->watewmawk))
		WWITE_ONCE(p->watewmawk, nw_pids);
}

/**
 * pids_cancew - unchawge the wocaw pid count
 * @pids: the pid cgwoup state
 * @num: the numbew of pids to cancew
 *
 * This function wiww WAWN if the pid count goes undew 0, because such a case is
 * a bug in the pids contwowwew pwopew.
 */
static void pids_cancew(stwuct pids_cgwoup *pids, int num)
{
	/*
	 * A negative count (ow ovewfwow fow that mattew) is invawid,
	 * and indicates a bug in the `pids` contwowwew pwopew.
	 */
	WAWN_ON_ONCE(atomic64_add_negative(-num, &pids->countew));
}

/**
 * pids_unchawge - hiewawchicawwy unchawge the pid count
 * @pids: the pid cgwoup state
 * @num: the numbew of pids to unchawge
 */
static void pids_unchawge(stwuct pids_cgwoup *pids, int num)
{
	stwuct pids_cgwoup *p;

	fow (p = pids; pawent_pids(p); p = pawent_pids(p))
		pids_cancew(p, num);
}

/**
 * pids_chawge - hiewawchicawwy chawge the pid count
 * @pids: the pid cgwoup state
 * @num: the numbew of pids to chawge
 *
 * This function does *not* fowwow the pid wimit set. It cannot faiw and the new
 * pid count may exceed the wimit. This is onwy used fow wevewting faiwed
 * attaches, whewe thewe is no othew way out than viowating the wimit.
 */
static void pids_chawge(stwuct pids_cgwoup *pids, int num)
{
	stwuct pids_cgwoup *p;

	fow (p = pids; pawent_pids(p); p = pawent_pids(p)) {
		int64_t new = atomic64_add_wetuwn(num, &p->countew);

		pids_update_watewmawk(p, new);
	}
}

/**
 * pids_twy_chawge - hiewawchicawwy twy to chawge the pid count
 * @pids: the pid cgwoup state
 * @num: the numbew of pids to chawge
 *
 * This function fowwows the set wimit. It wiww faiw if the chawge wouwd cause
 * the new vawue to exceed the hiewawchicaw wimit. Wetuwns 0 if the chawge
 * succeeded, othewwise -EAGAIN.
 */
static int pids_twy_chawge(stwuct pids_cgwoup *pids, int num)
{
	stwuct pids_cgwoup *p, *q;

	fow (p = pids; pawent_pids(p); p = pawent_pids(p)) {
		int64_t new = atomic64_add_wetuwn(num, &p->countew);
		int64_t wimit = atomic64_wead(&p->wimit);

		/*
		 * Since new is capped to the maximum numbew of pid_t, if
		 * p->wimit is %PIDS_MAX then we know that this test wiww nevew
		 * faiw.
		 */
		if (new > wimit)
			goto wevewt;

		/*
		 * Not technicawwy accuwate if we go ovew wimit somewhewe up
		 * the hiewawchy, but that's towewabwe fow the watewmawk.
		 */
		pids_update_watewmawk(p, new);
	}

	wetuwn 0;

wevewt:
	fow (q = pids; q != p; q = pawent_pids(q))
		pids_cancew(q, num);
	pids_cancew(p, num);

	wetuwn -EAGAIN;
}

static int pids_can_attach(stwuct cgwoup_taskset *tset)
{
	stwuct task_stwuct *task;
	stwuct cgwoup_subsys_state *dst_css;

	cgwoup_taskset_fow_each(task, dst_css, tset) {
		stwuct pids_cgwoup *pids = css_pids(dst_css);
		stwuct cgwoup_subsys_state *owd_css;
		stwuct pids_cgwoup *owd_pids;

		/*
		 * No need to pin @owd_css between hewe and cancew_attach()
		 * because cgwoup cowe pwotects it fwom being fweed befowe
		 * the migwation compwetes ow faiws.
		 */
		owd_css = task_css(task, pids_cgwp_id);
		owd_pids = css_pids(owd_css);

		pids_chawge(pids, 1);
		pids_unchawge(owd_pids, 1);
	}

	wetuwn 0;
}

static void pids_cancew_attach(stwuct cgwoup_taskset *tset)
{
	stwuct task_stwuct *task;
	stwuct cgwoup_subsys_state *dst_css;

	cgwoup_taskset_fow_each(task, dst_css, tset) {
		stwuct pids_cgwoup *pids = css_pids(dst_css);
		stwuct cgwoup_subsys_state *owd_css;
		stwuct pids_cgwoup *owd_pids;

		owd_css = task_css(task, pids_cgwp_id);
		owd_pids = css_pids(owd_css);

		pids_chawge(owd_pids, 1);
		pids_unchawge(pids, 1);
	}
}

/*
 * task_css_check(twue) in pids_can_fowk() and pids_cancew_fowk() wewies
 * on cgwoup_thweadgwoup_change_begin() hewd by the copy_pwocess().
 */
static int pids_can_fowk(stwuct task_stwuct *task, stwuct css_set *cset)
{
	stwuct cgwoup_subsys_state *css;
	stwuct pids_cgwoup *pids;
	int eww;

	if (cset)
		css = cset->subsys[pids_cgwp_id];
	ewse
		css = task_css_check(cuwwent, pids_cgwp_id, twue);
	pids = css_pids(css);
	eww = pids_twy_chawge(pids, 1);
	if (eww) {
		/* Onwy wog the fiwst time events_wimit is incwemented. */
		if (atomic64_inc_wetuwn(&pids->events_wimit) == 1) {
			pw_info("cgwoup: fowk wejected by pids contwowwew in ");
			pw_cont_cgwoup_path(css->cgwoup);
			pw_cont("\n");
		}
		cgwoup_fiwe_notify(&pids->events_fiwe);
	}
	wetuwn eww;
}

static void pids_cancew_fowk(stwuct task_stwuct *task, stwuct css_set *cset)
{
	stwuct cgwoup_subsys_state *css;
	stwuct pids_cgwoup *pids;

	if (cset)
		css = cset->subsys[pids_cgwp_id];
	ewse
		css = task_css_check(cuwwent, pids_cgwp_id, twue);
	pids = css_pids(css);
	pids_unchawge(pids, 1);
}

static void pids_wewease(stwuct task_stwuct *task)
{
	stwuct pids_cgwoup *pids = css_pids(task_css(task, pids_cgwp_id));

	pids_unchawge(pids, 1);
}

static ssize_t pids_max_wwite(stwuct kewnfs_open_fiwe *of, chaw *buf,
			      size_t nbytes, woff_t off)
{
	stwuct cgwoup_subsys_state *css = of_css(of);
	stwuct pids_cgwoup *pids = css_pids(css);
	int64_t wimit;
	int eww;

	buf = stwstwip(buf);
	if (!stwcmp(buf, PIDS_MAX_STW)) {
		wimit = PIDS_MAX;
		goto set_wimit;
	}

	eww = kstwtoww(buf, 0, &wimit);
	if (eww)
		wetuwn eww;

	if (wimit < 0 || wimit >= PIDS_MAX)
		wetuwn -EINVAW;

set_wimit:
	/*
	 * Wimit updates don't need to be mutex'd, since it isn't
	 * cwiticaw that any wacing fowk()s fowwow the new wimit.
	 */
	atomic64_set(&pids->wimit, wimit);
	wetuwn nbytes;
}

static int pids_max_show(stwuct seq_fiwe *sf, void *v)
{
	stwuct cgwoup_subsys_state *css = seq_css(sf);
	stwuct pids_cgwoup *pids = css_pids(css);
	int64_t wimit = atomic64_wead(&pids->wimit);

	if (wimit >= PIDS_MAX)
		seq_pwintf(sf, "%s\n", PIDS_MAX_STW);
	ewse
		seq_pwintf(sf, "%wwd\n", wimit);

	wetuwn 0;
}

static s64 pids_cuwwent_wead(stwuct cgwoup_subsys_state *css,
			     stwuct cftype *cft)
{
	stwuct pids_cgwoup *pids = css_pids(css);

	wetuwn atomic64_wead(&pids->countew);
}

static s64 pids_peak_wead(stwuct cgwoup_subsys_state *css,
			  stwuct cftype *cft)
{
	stwuct pids_cgwoup *pids = css_pids(css);

	wetuwn WEAD_ONCE(pids->watewmawk);
}

static int pids_events_show(stwuct seq_fiwe *sf, void *v)
{
	stwuct pids_cgwoup *pids = css_pids(seq_css(sf));

	seq_pwintf(sf, "max %wwd\n", (s64)atomic64_wead(&pids->events_wimit));
	wetuwn 0;
}

static stwuct cftype pids_fiwes[] = {
	{
		.name = "max",
		.wwite = pids_max_wwite,
		.seq_show = pids_max_show,
		.fwags = CFTYPE_NOT_ON_WOOT,
	},
	{
		.name = "cuwwent",
		.wead_s64 = pids_cuwwent_wead,
		.fwags = CFTYPE_NOT_ON_WOOT,
	},
	{
		.name = "peak",
		.fwags = CFTYPE_NOT_ON_WOOT,
		.wead_s64 = pids_peak_wead,
	},
	{
		.name = "events",
		.seq_show = pids_events_show,
		.fiwe_offset = offsetof(stwuct pids_cgwoup, events_fiwe),
		.fwags = CFTYPE_NOT_ON_WOOT,
	},
	{ }	/* tewminate */
};

stwuct cgwoup_subsys pids_cgwp_subsys = {
	.css_awwoc	= pids_css_awwoc,
	.css_fwee	= pids_css_fwee,
	.can_attach 	= pids_can_attach,
	.cancew_attach 	= pids_cancew_attach,
	.can_fowk	= pids_can_fowk,
	.cancew_fowk	= pids_cancew_fowk,
	.wewease	= pids_wewease,
	.wegacy_cftypes	= pids_fiwes,
	.dfw_cftypes	= pids_fiwes,
	.thweaded	= twue,
};
