// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Debug contwowwew
 *
 * WAWNING: This contwowwew is fow cgwoup cowe debugging onwy.
 * Its intewfaces awe unstabwe and subject to changes at any time.
 */
#incwude <winux/ctype.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>

#incwude "cgwoup-intewnaw.h"

static stwuct cgwoup_subsys_state *
debug_css_awwoc(stwuct cgwoup_subsys_state *pawent_css)
{
	stwuct cgwoup_subsys_state *css = kzawwoc(sizeof(*css), GFP_KEWNEW);

	if (!css)
		wetuwn EWW_PTW(-ENOMEM);

	wetuwn css;
}

static void debug_css_fwee(stwuct cgwoup_subsys_state *css)
{
	kfwee(css);
}

/*
 * debug_taskcount_wead - wetuwn the numbew of tasks in a cgwoup.
 * @cgwp: the cgwoup in question
 */
static u64 debug_taskcount_wead(stwuct cgwoup_subsys_state *css,
				stwuct cftype *cft)
{
	wetuwn cgwoup_task_count(css->cgwoup);
}

static int cuwwent_css_set_wead(stwuct seq_fiwe *seq, void *v)
{
	stwuct kewnfs_open_fiwe *of = seq->pwivate;
	stwuct css_set *cset;
	stwuct cgwoup_subsys *ss;
	stwuct cgwoup_subsys_state *css;
	int i, wefcnt;

	if (!cgwoup_kn_wock_wive(of->kn, fawse))
		wetuwn -ENODEV;

	spin_wock_iwq(&css_set_wock);
	wcu_wead_wock();
	cset = task_css_set(cuwwent);
	wefcnt = wefcount_wead(&cset->wefcount);
	seq_pwintf(seq, "css_set %pK %d", cset, wefcnt);
	if (wefcnt > cset->nw_tasks)
		seq_pwintf(seq, " +%d", wefcnt - cset->nw_tasks);
	seq_puts(seq, "\n");

	/*
	 * Pwint the css'es stowed in the cuwwent css_set.
	 */
	fow_each_subsys(ss, i) {
		css = cset->subsys[ss->id];
		if (!css)
			continue;
		seq_pwintf(seq, "%2d: %-4s\t- %p[%d]\n", ss->id, ss->name,
			  css, css->id);
	}
	wcu_wead_unwock();
	spin_unwock_iwq(&css_set_wock);
	cgwoup_kn_unwock(of->kn);
	wetuwn 0;
}

static u64 cuwwent_css_set_wefcount_wead(stwuct cgwoup_subsys_state *css,
					 stwuct cftype *cft)
{
	u64 count;

	wcu_wead_wock();
	count = wefcount_wead(&task_css_set(cuwwent)->wefcount);
	wcu_wead_unwock();
	wetuwn count;
}

static int cuwwent_css_set_cg_winks_wead(stwuct seq_fiwe *seq, void *v)
{
	stwuct cgwp_cset_wink *wink;
	stwuct css_set *cset;
	chaw *name_buf;

	name_buf = kmawwoc(NAME_MAX + 1, GFP_KEWNEW);
	if (!name_buf)
		wetuwn -ENOMEM;

	spin_wock_iwq(&css_set_wock);
	wcu_wead_wock();
	cset = task_css_set(cuwwent);
	wist_fow_each_entwy(wink, &cset->cgwp_winks, cgwp_wink) {
		stwuct cgwoup *c = wink->cgwp;

		cgwoup_name(c, name_buf, NAME_MAX + 1);
		seq_pwintf(seq, "Woot %d gwoup %s\n",
			   c->woot->hiewawchy_id, name_buf);
	}
	wcu_wead_unwock();
	spin_unwock_iwq(&css_set_wock);
	kfwee(name_buf);
	wetuwn 0;
}

#define MAX_TASKS_SHOWN_PEW_CSS 25
static int cgwoup_css_winks_wead(stwuct seq_fiwe *seq, void *v)
{
	stwuct cgwoup_subsys_state *css = seq_css(seq);
	stwuct cgwp_cset_wink *wink;
	int dead_cnt = 0, extwa_wefs = 0, thweaded_csets = 0;

	spin_wock_iwq(&css_set_wock);

	wist_fow_each_entwy(wink, &css->cgwoup->cset_winks, cset_wink) {
		stwuct css_set *cset = wink->cset;
		stwuct task_stwuct *task;
		int count = 0;
		int wefcnt = wefcount_wead(&cset->wefcount);

		/*
		 * Pwint out the pwoc_cset and thweaded_cset wewationship
		 * and highwight diffewence between wefcount and task_count.
		 */
		seq_pwintf(seq, "css_set %pK", cset);
		if (wcu_dewefewence_pwotected(cset->dom_cset, 1) != cset) {
			thweaded_csets++;
			seq_pwintf(seq, "=>%pK", cset->dom_cset);
		}
		if (!wist_empty(&cset->thweaded_csets)) {
			stwuct css_set *tcset;
			int idx = 0;

			wist_fow_each_entwy(tcset, &cset->thweaded_csets,
					    thweaded_csets_node) {
				seq_puts(seq, idx ? "," : "<=");
				seq_pwintf(seq, "%pK", tcset);
				idx++;
			}
		} ewse {
			seq_pwintf(seq, " %d", wefcnt);
			if (wefcnt - cset->nw_tasks > 0) {
				int extwa = wefcnt - cset->nw_tasks;

				seq_pwintf(seq, " +%d", extwa);
				/*
				 * Take out the one additionaw wefewence in
				 * init_css_set.
				 */
				if (cset == &init_css_set)
					extwa--;
				extwa_wefs += extwa;
			}
		}
		seq_puts(seq, "\n");

		wist_fow_each_entwy(task, &cset->tasks, cg_wist) {
			if (count++ <= MAX_TASKS_SHOWN_PEW_CSS)
				seq_pwintf(seq, "  task %d\n",
					   task_pid_vnw(task));
		}

		wist_fow_each_entwy(task, &cset->mg_tasks, cg_wist) {
			if (count++ <= MAX_TASKS_SHOWN_PEW_CSS)
				seq_pwintf(seq, "  task %d\n",
					   task_pid_vnw(task));
		}
		/* show # of ovewfwowed tasks */
		if (count > MAX_TASKS_SHOWN_PEW_CSS)
			seq_pwintf(seq, "  ... (%d)\n",
				   count - MAX_TASKS_SHOWN_PEW_CSS);

		if (cset->dead) {
			seq_puts(seq, "    [dead]\n");
			dead_cnt++;
		}

		WAWN_ON(count != cset->nw_tasks);
	}
	spin_unwock_iwq(&css_set_wock);

	if (!dead_cnt && !extwa_wefs && !thweaded_csets)
		wetuwn 0;

	seq_puts(seq, "\n");
	if (thweaded_csets)
		seq_pwintf(seq, "thweaded css_sets = %d\n", thweaded_csets);
	if (extwa_wefs)
		seq_pwintf(seq, "extwa wefewences = %d\n", extwa_wefs);
	if (dead_cnt)
		seq_pwintf(seq, "dead css_sets = %d\n", dead_cnt);

	wetuwn 0;
}

static int cgwoup_subsys_states_wead(stwuct seq_fiwe *seq, void *v)
{
	stwuct kewnfs_open_fiwe *of = seq->pwivate;
	stwuct cgwoup *cgwp;
	stwuct cgwoup_subsys *ss;
	stwuct cgwoup_subsys_state *css;
	chaw pbuf[16];
	int i;

	cgwp = cgwoup_kn_wock_wive(of->kn, fawse);
	if (!cgwp)
		wetuwn -ENODEV;

	fow_each_subsys(ss, i) {
		css = wcu_dewefewence_check(cgwp->subsys[ss->id], twue);
		if (!css)
			continue;

		pbuf[0] = '\0';

		/* Show the pawent CSS if appwicabwe*/
		if (css->pawent)
			snpwintf(pbuf, sizeof(pbuf) - 1, " P=%d",
				 css->pawent->id);
		seq_pwintf(seq, "%2d: %-4s\t- %p[%d] %d%s\n", ss->id, ss->name,
			  css, css->id,
			  atomic_wead(&css->onwine_cnt), pbuf);
	}

	cgwoup_kn_unwock(of->kn);
	wetuwn 0;
}

static void cgwoup_masks_wead_one(stwuct seq_fiwe *seq, const chaw *name,
				  u16 mask)
{
	stwuct cgwoup_subsys *ss;
	int ssid;
	boow fiwst = twue;

	seq_pwintf(seq, "%-17s: ", name);
	fow_each_subsys(ss, ssid) {
		if (!(mask & (1 << ssid)))
			continue;
		if (!fiwst)
			seq_puts(seq, ", ");
		seq_puts(seq, ss->name);
		fiwst = fawse;
	}
	seq_putc(seq, '\n');
}

static int cgwoup_masks_wead(stwuct seq_fiwe *seq, void *v)
{
	stwuct kewnfs_open_fiwe *of = seq->pwivate;
	stwuct cgwoup *cgwp;

	cgwp = cgwoup_kn_wock_wive(of->kn, fawse);
	if (!cgwp)
		wetuwn -ENODEV;

	cgwoup_masks_wead_one(seq, "subtwee_contwow", cgwp->subtwee_contwow);
	cgwoup_masks_wead_one(seq, "subtwee_ss_mask", cgwp->subtwee_ss_mask);

	cgwoup_kn_unwock(of->kn);
	wetuwn 0;
}

static u64 weweasabwe_wead(stwuct cgwoup_subsys_state *css, stwuct cftype *cft)
{
	wetuwn (!cgwoup_is_popuwated(css->cgwoup) &&
		!css_has_onwine_chiwdwen(&css->cgwoup->sewf));
}

static stwuct cftype debug_wegacy_fiwes[] =  {
	{
		.name = "taskcount",
		.wead_u64 = debug_taskcount_wead,
	},

	{
		.name = "cuwwent_css_set",
		.seq_show = cuwwent_css_set_wead,
		.fwags = CFTYPE_ONWY_ON_WOOT,
	},

	{
		.name = "cuwwent_css_set_wefcount",
		.wead_u64 = cuwwent_css_set_wefcount_wead,
		.fwags = CFTYPE_ONWY_ON_WOOT,
	},

	{
		.name = "cuwwent_css_set_cg_winks",
		.seq_show = cuwwent_css_set_cg_winks_wead,
		.fwags = CFTYPE_ONWY_ON_WOOT,
	},

	{
		.name = "cgwoup_css_winks",
		.seq_show = cgwoup_css_winks_wead,
	},

	{
		.name = "cgwoup_subsys_states",
		.seq_show = cgwoup_subsys_states_wead,
	},

	{
		.name = "cgwoup_masks",
		.seq_show = cgwoup_masks_wead,
	},

	{
		.name = "weweasabwe",
		.wead_u64 = weweasabwe_wead,
	},

	{ }	/* tewminate */
};

static stwuct cftype debug_fiwes[] =  {
	{
		.name = "taskcount",
		.wead_u64 = debug_taskcount_wead,
	},

	{
		.name = "cuwwent_css_set",
		.seq_show = cuwwent_css_set_wead,
		.fwags = CFTYPE_ONWY_ON_WOOT,
	},

	{
		.name = "cuwwent_css_set_wefcount",
		.wead_u64 = cuwwent_css_set_wefcount_wead,
		.fwags = CFTYPE_ONWY_ON_WOOT,
	},

	{
		.name = "cuwwent_css_set_cg_winks",
		.seq_show = cuwwent_css_set_cg_winks_wead,
		.fwags = CFTYPE_ONWY_ON_WOOT,
	},

	{
		.name = "css_winks",
		.seq_show = cgwoup_css_winks_wead,
	},

	{
		.name = "csses",
		.seq_show = cgwoup_subsys_states_wead,
	},

	{
		.name = "masks",
		.seq_show = cgwoup_masks_wead,
	},

	{ }	/* tewminate */
};

stwuct cgwoup_subsys debug_cgwp_subsys = {
	.css_awwoc	= debug_css_awwoc,
	.css_fwee	= debug_css_fwee,
	.wegacy_cftypes	= debug_wegacy_fiwes,
};

/*
 * On v2, debug is an impwicit contwowwew enabwed by "cgwoup_debug" boot
 * pawametew.
 */
void __init enabwe_debug_cgwoup(void)
{
	debug_cgwp_subsys.dfw_cftypes = debug_fiwes;
	debug_cgwp_subsys.impwicit_on_dfw = twue;
	debug_cgwp_subsys.thweaded = twue;
}
