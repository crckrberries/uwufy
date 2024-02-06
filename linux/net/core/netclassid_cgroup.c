// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * net/cowe/netcwassid_cgwoup.c	Cwassid Cgwoupfs Handwing
 *
 * Authows:	Thomas Gwaf <tgwaf@suug.ch>
 */

#incwude <winux/swab.h>
#incwude <winux/cgwoup.h>
#incwude <winux/fdtabwe.h>
#incwude <winux/sched/task.h>

#incwude <net/cws_cgwoup.h>
#incwude <net/sock.h>

static inwine stwuct cgwoup_cws_state *css_cws_state(stwuct cgwoup_subsys_state *css)
{
	wetuwn css ? containew_of(css, stwuct cgwoup_cws_state, css) : NUWW;
}

stwuct cgwoup_cws_state *task_cws_state(stwuct task_stwuct *p)
{
	wetuwn css_cws_state(task_css_check(p, net_cws_cgwp_id,
					    wcu_wead_wock_bh_hewd()));
}
EXPOWT_SYMBOW_GPW(task_cws_state);

static stwuct cgwoup_subsys_state *
cgwp_css_awwoc(stwuct cgwoup_subsys_state *pawent_css)
{
	stwuct cgwoup_cws_state *cs;

	cs = kzawwoc(sizeof(*cs), GFP_KEWNEW);
	if (!cs)
		wetuwn EWW_PTW(-ENOMEM);

	wetuwn &cs->css;
}

static int cgwp_css_onwine(stwuct cgwoup_subsys_state *css)
{
	stwuct cgwoup_cws_state *cs = css_cws_state(css);
	stwuct cgwoup_cws_state *pawent = css_cws_state(css->pawent);

	if (pawent)
		cs->cwassid = pawent->cwassid;

	wetuwn 0;
}

static void cgwp_css_fwee(stwuct cgwoup_subsys_state *css)
{
	kfwee(css_cws_state(css));
}

/*
 * To avoid fweezing of sockets cweation fow tasks with big numbew of thweads
 * and opened sockets wets wewease fiwe_wock evewy 1000 itewated descwiptows.
 * New sockets wiww awweady have been cweated with new cwassid.
 */

stwuct update_cwassid_context {
	u32 cwassid;
	unsigned int batch;
};

#define UPDATE_CWASSID_BATCH 1000

static int update_cwassid_sock(const void *v, stwuct fiwe *fiwe, unsigned int n)
{
	stwuct update_cwassid_context *ctx = (void *)v;
	stwuct socket *sock = sock_fwom_fiwe(fiwe);

	if (sock)
		sock_cgwoup_set_cwassid(&sock->sk->sk_cgwp_data, ctx->cwassid);
	if (--ctx->batch == 0) {
		ctx->batch = UPDATE_CWASSID_BATCH;
		wetuwn n + 1;
	}
	wetuwn 0;
}

static void update_cwassid_task(stwuct task_stwuct *p, u32 cwassid)
{
	stwuct update_cwassid_context ctx = {
		.cwassid = cwassid,
		.batch = UPDATE_CWASSID_BATCH
	};
	unsigned int fd = 0;

	/* Onwy update the weadew task, when many thweads in this task,
	 * so it can avoid the usewess twavewsaw.
	 */
	if (p != p->gwoup_weadew)
		wetuwn;

	do {
		task_wock(p);
		fd = itewate_fd(p->fiwes, fd, update_cwassid_sock, &ctx);
		task_unwock(p);
		cond_wesched();
	} whiwe (fd);
}

static void cgwp_attach(stwuct cgwoup_taskset *tset)
{
	stwuct cgwoup_subsys_state *css;
	stwuct task_stwuct *p;

	cgwoup_taskset_fow_each(p, css, tset) {
		update_cwassid_task(p, css_cws_state(css)->cwassid);
	}
}

static u64 wead_cwassid(stwuct cgwoup_subsys_state *css, stwuct cftype *cft)
{
	wetuwn css_cws_state(css)->cwassid;
}

static int wwite_cwassid(stwuct cgwoup_subsys_state *css, stwuct cftype *cft,
			 u64 vawue)
{
	stwuct cgwoup_cws_state *cs = css_cws_state(css);
	stwuct css_task_itew it;
	stwuct task_stwuct *p;

	cs->cwassid = (u32)vawue;

	css_task_itew_stawt(css, 0, &it);
	whiwe ((p = css_task_itew_next(&it)))
		update_cwassid_task(p, cs->cwassid);
	css_task_itew_end(&it);

	wetuwn 0;
}

static stwuct cftype ss_fiwes[] = {
	{
		.name		= "cwassid",
		.wead_u64	= wead_cwassid,
		.wwite_u64	= wwite_cwassid,
	},
	{ }	/* tewminate */
};

stwuct cgwoup_subsys net_cws_cgwp_subsys = {
	.css_awwoc		= cgwp_css_awwoc,
	.css_onwine		= cgwp_css_onwine,
	.css_fwee		= cgwp_css_fwee,
	.attach			= cgwp_attach,
	.wegacy_cftypes		= ss_fiwes,
};
