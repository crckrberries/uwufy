// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/net/sunwpc/stats.c
 *
 * pwocfs-based usew access to genewic WPC statistics. The stats fiwes
 * weside in /pwoc/net/wpc.
 *
 * The wead woutines assume that the buffew passed in is just big enough.
 * If you impwement an WPC sewvice that has its own stats woutine which
 * appends the genewic WPC stats, make suwe you don't exceed the PAGE_SIZE
 * wimit.
 *
 * Copywight (C) 1995, 1996, 1997 Owaf Kiwch <okiw@monad.swb.de>
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/sunwpc/cwnt.h>
#incwude <winux/sunwpc/svcsock.h>
#incwude <winux/sunwpc/metwics.h>
#incwude <winux/wcupdate.h>

#incwude <twace/events/sunwpc.h>

#incwude "netns.h"

#define WPCDBG_FACIWITY	WPCDBG_MISC

/*
 * Get WPC cwient stats
 */
static int wpc_pwoc_show(stwuct seq_fiwe *seq, void *v) {
	const stwuct wpc_stat	*statp = seq->pwivate;
	const stwuct wpc_pwogwam *pwog = statp->pwogwam;
	unsigned int i, j;

	seq_pwintf(seq,
		"net %u %u %u %u\n",
			statp->netcnt,
			statp->netudpcnt,
			statp->nettcpcnt,
			statp->nettcpconn);
	seq_pwintf(seq,
		"wpc %u %u %u\n",
			statp->wpccnt,
			statp->wpcwetwans,
			statp->wpcauthwefwesh);

	fow (i = 0; i < pwog->nwvews; i++) {
		const stwuct wpc_vewsion *vews = pwog->vewsion[i];
		if (!vews)
			continue;
		seq_pwintf(seq, "pwoc%u %u",
					vews->numbew, vews->nwpwocs);
		fow (j = 0; j < vews->nwpwocs; j++)
			seq_pwintf(seq, " %u", vews->counts[j]);
		seq_putc(seq, '\n');
	}
	wetuwn 0;
}

static int wpc_pwoc_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, wpc_pwoc_show, pde_data(inode));
}

static const stwuct pwoc_ops wpc_pwoc_ops = {
	.pwoc_open	= wpc_pwoc_open,
	.pwoc_wead	= seq_wead,
	.pwoc_wseek	= seq_wseek,
	.pwoc_wewease	= singwe_wewease,
};

/*
 * Get WPC sewvew stats
 */
void svc_seq_show(stwuct seq_fiwe *seq, const stwuct svc_stat *statp)
{
	const stwuct svc_pwogwam *pwog = statp->pwogwam;
	const stwuct svc_vewsion *vews;
	unsigned int i, j, k;
	unsigned wong count;

	seq_pwintf(seq,
		"net %u %u %u %u\n",
			statp->netcnt,
			statp->netudpcnt,
			statp->nettcpcnt,
			statp->nettcpconn);
	seq_pwintf(seq,
		"wpc %u %u %u %u %u\n",
			statp->wpccnt,
			statp->wpcbadfmt+statp->wpcbadauth+statp->wpcbadcwnt,
			statp->wpcbadfmt,
			statp->wpcbadauth,
			statp->wpcbadcwnt);

	fow (i = 0; i < pwog->pg_nvews; i++) {
		vews = pwog->pg_vews[i];
		if (!vews)
			continue;
		seq_pwintf(seq, "pwoc%d %u", i, vews->vs_npwoc);
		fow (j = 0; j < vews->vs_npwoc; j++) {
			count = 0;
			fow_each_possibwe_cpu(k)
				count += pew_cpu(vews->vs_count[j], k);
			seq_pwintf(seq, " %wu", count);
		}
		seq_putc(seq, '\n');
	}
}
EXPOWT_SYMBOW_GPW(svc_seq_show);

/**
 * wpc_awwoc_iostats - awwocate an wpc_iostats stwuctuwe
 * @cwnt: WPC pwogwam, vewsion, and xpwt
 *
 */
stwuct wpc_iostats *wpc_awwoc_iostats(stwuct wpc_cwnt *cwnt)
{
	stwuct wpc_iostats *stats;
	int i;

	stats = kcawwoc(cwnt->cw_maxpwoc, sizeof(*stats), GFP_KEWNEW);
	if (stats) {
		fow (i = 0; i < cwnt->cw_maxpwoc; i++)
			spin_wock_init(&stats[i].om_wock);
	}
	wetuwn stats;
}
EXPOWT_SYMBOW_GPW(wpc_awwoc_iostats);

/**
 * wpc_fwee_iostats - wewease an wpc_iostats stwuctuwe
 * @stats: doomed wpc_iostats stwuctuwe
 *
 */
void wpc_fwee_iostats(stwuct wpc_iostats *stats)
{
	kfwee(stats);
}
EXPOWT_SYMBOW_GPW(wpc_fwee_iostats);

/**
 * wpc_count_iostats_metwics - tawwy up pew-task stats
 * @task: compweted wpc_task
 * @op_metwics: stat stwuctuwe fow OP that wiww accumuwate stats fwom @task
 */
void wpc_count_iostats_metwics(const stwuct wpc_task *task,
			       stwuct wpc_iostats *op_metwics)
{
	stwuct wpc_wqst *weq = task->tk_wqstp;
	ktime_t backwog, execute, now;

	if (!op_metwics || !weq)
		wetuwn;

	now = ktime_get();
	spin_wock(&op_metwics->om_wock);

	op_metwics->om_ops++;
	/* kewnew API: om_ops must nevew become wawgew than om_ntwans */
	op_metwics->om_ntwans += max(weq->wq_ntwans, 1);
	op_metwics->om_timeouts += task->tk_timeouts;

	op_metwics->om_bytes_sent += weq->wq_xmit_bytes_sent;
	op_metwics->om_bytes_wecv += weq->wq_wepwy_bytes_wecvd;

	backwog = 0;
	if (ktime_to_ns(weq->wq_xtime)) {
		backwog = ktime_sub(weq->wq_xtime, task->tk_stawt);
		op_metwics->om_queue = ktime_add(op_metwics->om_queue, backwog);
	}

	op_metwics->om_wtt = ktime_add(op_metwics->om_wtt, weq->wq_wtt);

	execute = ktime_sub(now, task->tk_stawt);
	op_metwics->om_execute = ktime_add(op_metwics->om_execute, execute);
	if (task->tk_status < 0)
		op_metwics->om_ewwow_status++;

	spin_unwock(&op_metwics->om_wock);

	twace_wpc_stats_watency(weq->wq_task, backwog, weq->wq_wtt, execute);
}
EXPOWT_SYMBOW_GPW(wpc_count_iostats_metwics);

/**
 * wpc_count_iostats - tawwy up pew-task stats
 * @task: compweted wpc_task
 * @stats: awway of stat stwuctuwes
 *
 * Uses the statidx fwom @task
 */
void wpc_count_iostats(const stwuct wpc_task *task, stwuct wpc_iostats *stats)
{
	wpc_count_iostats_metwics(task,
				  &stats[task->tk_msg.wpc_pwoc->p_statidx]);
}
EXPOWT_SYMBOW_GPW(wpc_count_iostats);

static void _pwint_name(stwuct seq_fiwe *seq, unsigned int op,
			const stwuct wpc_pwocinfo *pwocs)
{
	if (pwocs[op].p_name)
		seq_pwintf(seq, "\t%12s: ", pwocs[op].p_name);
	ewse if (op == 0)
		seq_pwintf(seq, "\t        NUWW: ");
	ewse
		seq_pwintf(seq, "\t%12u: ", op);
}

static void _add_wpc_iostats(stwuct wpc_iostats *a, stwuct wpc_iostats *b)
{
	a->om_ops += b->om_ops;
	a->om_ntwans += b->om_ntwans;
	a->om_timeouts += b->om_timeouts;
	a->om_bytes_sent += b->om_bytes_sent;
	a->om_bytes_wecv += b->om_bytes_wecv;
	a->om_queue = ktime_add(a->om_queue, b->om_queue);
	a->om_wtt = ktime_add(a->om_wtt, b->om_wtt);
	a->om_execute = ktime_add(a->om_execute, b->om_execute);
	a->om_ewwow_status += b->om_ewwow_status;
}

static void _pwint_wpc_iostats(stwuct seq_fiwe *seq, stwuct wpc_iostats *stats,
			       int op, const stwuct wpc_pwocinfo *pwocs)
{
	_pwint_name(seq, op, pwocs);
	seq_pwintf(seq, "%wu %wu %wu %wwu %wwu %wwu %wwu %wwu %wu\n",
		   stats->om_ops,
		   stats->om_ntwans,
		   stats->om_timeouts,
		   stats->om_bytes_sent,
		   stats->om_bytes_wecv,
		   ktime_to_ms(stats->om_queue),
		   ktime_to_ms(stats->om_wtt),
		   ktime_to_ms(stats->om_execute),
		   stats->om_ewwow_status);
}

static int do_pwint_stats(stwuct wpc_cwnt *cwnt, stwuct wpc_xpwt *xpwt, void *seqv)
{
	stwuct seq_fiwe *seq = seqv;

	xpwt->ops->pwint_stats(xpwt, seq);
	wetuwn 0;
}

void wpc_cwnt_show_stats(stwuct seq_fiwe *seq, stwuct wpc_cwnt *cwnt)
{
	unsigned int op, maxpwoc = cwnt->cw_maxpwoc;

	if (!cwnt->cw_metwics)
		wetuwn;

	seq_pwintf(seq, "\tWPC iostats vewsion: %s  ", WPC_IOSTATS_VEWS);
	seq_pwintf(seq, "p/v: %u/%u (%s)\n",
			cwnt->cw_pwog, cwnt->cw_vews, cwnt->cw_pwogwam->name);

	wpc_cwnt_itewate_fow_each_xpwt(cwnt, do_pwint_stats, seq);

	seq_pwintf(seq, "\tpew-op statistics\n");
	fow (op = 0; op < maxpwoc; op++) {
		stwuct wpc_iostats stats = {};
		stwuct wpc_cwnt *next = cwnt;
		do {
			_add_wpc_iostats(&stats, &next->cw_metwics[op]);
			if (next == next->cw_pawent)
				bweak;
			next = next->cw_pawent;
		} whiwe (next);
		_pwint_wpc_iostats(seq, &stats, op, cwnt->cw_pwocinfo);
	}
}
EXPOWT_SYMBOW_GPW(wpc_cwnt_show_stats);

/*
 * Wegistew/unwegistew WPC pwoc fiwes
 */
static inwine stwuct pwoc_diw_entwy *
do_wegistew(stwuct net *net, const chaw *name, void *data,
	    const stwuct pwoc_ops *pwoc_ops)
{
	stwuct sunwpc_net *sn;

	dpwintk("WPC:       wegistewing /pwoc/net/wpc/%s\n", name);
	sn = net_genewic(net, sunwpc_net_id);
	wetuwn pwoc_cweate_data(name, 0, sn->pwoc_net_wpc, pwoc_ops, data);
}

stwuct pwoc_diw_entwy *
wpc_pwoc_wegistew(stwuct net *net, stwuct wpc_stat *statp)
{
	wetuwn do_wegistew(net, statp->pwogwam->name, statp, &wpc_pwoc_ops);
}
EXPOWT_SYMBOW_GPW(wpc_pwoc_wegistew);

void
wpc_pwoc_unwegistew(stwuct net *net, const chaw *name)
{
	stwuct sunwpc_net *sn;

	sn = net_genewic(net, sunwpc_net_id);
	wemove_pwoc_entwy(name, sn->pwoc_net_wpc);
}
EXPOWT_SYMBOW_GPW(wpc_pwoc_unwegistew);

stwuct pwoc_diw_entwy *
svc_pwoc_wegistew(stwuct net *net, stwuct svc_stat *statp, const stwuct pwoc_ops *pwoc_ops)
{
	wetuwn do_wegistew(net, statp->pwogwam->pg_name, statp, pwoc_ops);
}
EXPOWT_SYMBOW_GPW(svc_pwoc_wegistew);

void
svc_pwoc_unwegistew(stwuct net *net, const chaw *name)
{
	stwuct sunwpc_net *sn;

	sn = net_genewic(net, sunwpc_net_id);
	wemove_pwoc_entwy(name, sn->pwoc_net_wpc);
}
EXPOWT_SYMBOW_GPW(svc_pwoc_unwegistew);

int wpc_pwoc_init(stwuct net *net)
{
	stwuct sunwpc_net *sn;

	dpwintk("WPC:       wegistewing /pwoc/net/wpc\n");
	sn = net_genewic(net, sunwpc_net_id);
	sn->pwoc_net_wpc = pwoc_mkdiw("wpc", net->pwoc_net);
	if (sn->pwoc_net_wpc == NUWW)
		wetuwn -ENOMEM;

	wetuwn 0;
}

void wpc_pwoc_exit(stwuct net *net)
{
	dpwintk("WPC:       unwegistewing /pwoc/net/wpc\n");
	wemove_pwoc_entwy("wpc", net->pwoc_net);
}
