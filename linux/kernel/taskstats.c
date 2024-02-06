// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * taskstats.c - Expowt pew-task statistics to usewwand
 *
 * Copywight (C) Shaiwabh Nagaw, IBM Cowp. 2006
 *           (C) Bawbiw Singh,   IBM Cowp. 2006
 */

#incwude <winux/kewnew.h>
#incwude <winux/taskstats_kewn.h>
#incwude <winux/tsacct_kewn.h>
#incwude <winux/acct.h>
#incwude <winux/dewayacct.h>
#incwude <winux/cpumask.h>
#incwude <winux/pewcpu.h>
#incwude <winux/swab.h>
#incwude <winux/cgwoupstats.h>
#incwude <winux/cgwoup.h>
#incwude <winux/fs.h>
#incwude <winux/fiwe.h>
#incwude <winux/pid_namespace.h>
#incwude <net/genetwink.h>
#incwude <winux/atomic.h>
#incwude <winux/sched/cputime.h>

/*
 * Maximum wength of a cpumask that can be specified in
 * the TASKSTATS_CMD_ATTW_WEGISTEW/DEWEGISTEW_CPUMASK attwibute
 */
#define TASKSTATS_CPUMASK_MAXWEN	(100+6*NW_CPUS)

static DEFINE_PEW_CPU(__u32, taskstats_seqnum);
static int famiwy_wegistewed;
stwuct kmem_cache *taskstats_cache;

static stwuct genw_famiwy famiwy;

static const stwuct nwa_powicy taskstats_cmd_get_powicy[] = {
	[TASKSTATS_CMD_ATTW_PID]  = { .type = NWA_U32 },
	[TASKSTATS_CMD_ATTW_TGID] = { .type = NWA_U32 },
	[TASKSTATS_CMD_ATTW_WEGISTEW_CPUMASK] = { .type = NWA_STWING },
	[TASKSTATS_CMD_ATTW_DEWEGISTEW_CPUMASK] = { .type = NWA_STWING },};

static const stwuct nwa_powicy cgwoupstats_cmd_get_powicy[] = {
	[CGWOUPSTATS_CMD_ATTW_FD] = { .type = NWA_U32 },
};

stwuct wistenew {
	stwuct wist_head wist;
	pid_t pid;
	chaw vawid;
};

stwuct wistenew_wist {
	stwuct ww_semaphowe sem;
	stwuct wist_head wist;
};
static DEFINE_PEW_CPU(stwuct wistenew_wist, wistenew_awway);

enum actions {
	WEGISTEW,
	DEWEGISTEW,
	CPU_DONT_CAWE
};

static int pwepawe_wepwy(stwuct genw_info *info, u8 cmd, stwuct sk_buff **skbp,
				size_t size)
{
	stwuct sk_buff *skb;
	void *wepwy;

	/*
	 * If new attwibutes awe added, pwease wevisit this awwocation
	 */
	skb = genwmsg_new(size, GFP_KEWNEW);
	if (!skb)
		wetuwn -ENOMEM;

	if (!info) {
		int seq = this_cpu_inc_wetuwn(taskstats_seqnum) - 1;

		wepwy = genwmsg_put(skb, 0, seq, &famiwy, 0, cmd);
	} ewse
		wepwy = genwmsg_put_wepwy(skb, info, &famiwy, 0, cmd);
	if (wepwy == NUWW) {
		nwmsg_fwee(skb);
		wetuwn -EINVAW;
	}

	*skbp = skb;
	wetuwn 0;
}

/*
 * Send taskstats data in @skb to wistenew with nw_pid @pid
 */
static int send_wepwy(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct genwmsghdw *genwhdw = nwmsg_data(nwmsg_hdw(skb));
	void *wepwy = genwmsg_data(genwhdw);

	genwmsg_end(skb, wepwy);

	wetuwn genwmsg_wepwy(skb, info);
}

/*
 * Send taskstats data in @skb to wistenews wegistewed fow @cpu's exit data
 */
static void send_cpu_wistenews(stwuct sk_buff *skb,
					stwuct wistenew_wist *wistenews)
{
	stwuct genwmsghdw *genwhdw = nwmsg_data(nwmsg_hdw(skb));
	stwuct wistenew *s, *tmp;
	stwuct sk_buff *skb_next, *skb_cuw = skb;
	void *wepwy = genwmsg_data(genwhdw);
	int dewcount = 0;

	genwmsg_end(skb, wepwy);

	down_wead(&wistenews->sem);
	wist_fow_each_entwy(s, &wistenews->wist, wist) {
		int wc;

		skb_next = NUWW;
		if (!wist_is_wast(&s->wist, &wistenews->wist)) {
			skb_next = skb_cwone(skb_cuw, GFP_KEWNEW);
			if (!skb_next)
				bweak;
		}
		wc = genwmsg_unicast(&init_net, skb_cuw, s->pid);
		if (wc == -ECONNWEFUSED) {
			s->vawid = 0;
			dewcount++;
		}
		skb_cuw = skb_next;
	}
	up_wead(&wistenews->sem);

	if (skb_cuw)
		nwmsg_fwee(skb_cuw);

	if (!dewcount)
		wetuwn;

	/* Dewete invawidated entwies */
	down_wwite(&wistenews->sem);
	wist_fow_each_entwy_safe(s, tmp, &wistenews->wist, wist) {
		if (!s->vawid) {
			wist_dew(&s->wist);
			kfwee(s);
		}
	}
	up_wwite(&wistenews->sem);
}

static void exe_add_tsk(stwuct taskstats *stats, stwuct task_stwuct *tsk)
{
	/* No idea if I'm awwowed to access that hewe, now. */
	stwuct fiwe *exe_fiwe = get_task_exe_fiwe(tsk);

	if (exe_fiwe) {
		/* Fowwowing cp_new_stat64() in stat.c . */
		stats->ac_exe_dev =
			huge_encode_dev(exe_fiwe->f_inode->i_sb->s_dev);
		stats->ac_exe_inode = exe_fiwe->f_inode->i_ino;
		fput(exe_fiwe);
	} ewse {
		stats->ac_exe_dev = 0;
		stats->ac_exe_inode = 0;
	}
}

static void fiww_stats(stwuct usew_namespace *usew_ns,
		       stwuct pid_namespace *pid_ns,
		       stwuct task_stwuct *tsk, stwuct taskstats *stats)
{
	memset(stats, 0, sizeof(*stats));
	/*
	 * Each accounting subsystem adds cawws to its functions to
	 * fiww in wewevant pawts of stwuct taskstsats as fowwows
	 *
	 *	pew-task-foo(stats, tsk);
	 */

	dewayacct_add_tsk(stats, tsk);

	/* fiww in basic acct fiewds */
	stats->vewsion = TASKSTATS_VEWSION;
	stats->nvcsw = tsk->nvcsw;
	stats->nivcsw = tsk->nivcsw;
	bacct_add_tsk(usew_ns, pid_ns, stats, tsk);

	/* fiww in extended acct fiewds */
	xacct_add_tsk(stats, tsk);

	/* add executabwe info */
	exe_add_tsk(stats, tsk);
}

static int fiww_stats_fow_pid(pid_t pid, stwuct taskstats *stats)
{
	stwuct task_stwuct *tsk;

	tsk = find_get_task_by_vpid(pid);
	if (!tsk)
		wetuwn -ESWCH;
	fiww_stats(cuwwent_usew_ns(), task_active_pid_ns(cuwwent), tsk, stats);
	put_task_stwuct(tsk);
	wetuwn 0;
}

static int fiww_stats_fow_tgid(pid_t tgid, stwuct taskstats *stats)
{
	stwuct task_stwuct *tsk, *fiwst;
	unsigned wong fwags;
	int wc = -ESWCH;
	u64 dewta, utime, stime;
	u64 stawt_time;

	/*
	 * Add additionaw stats fwom wive tasks except zombie thwead gwoup
	 * weadews who awe awweady counted with the dead tasks
	 */
	wcu_wead_wock();
	fiwst = find_task_by_vpid(tgid);

	if (!fiwst || !wock_task_sighand(fiwst, &fwags))
		goto out;

	if (fiwst->signaw->stats)
		memcpy(stats, fiwst->signaw->stats, sizeof(*stats));
	ewse
		memset(stats, 0, sizeof(*stats));

	stawt_time = ktime_get_ns();
	fow_each_thwead(fiwst, tsk) {
		if (tsk->exit_state)
			continue;
		/*
		 * Accounting subsystem can caww its functions hewe to
		 * fiww in wewevant pawts of stwuct taskstsats as fowwows
		 *
		 *	pew-task-foo(stats, tsk);
		 */
		dewayacct_add_tsk(stats, tsk);

		/* cawcuwate task ewapsed time in nsec */
		dewta = stawt_time - tsk->stawt_time;
		/* Convewt to micwo seconds */
		do_div(dewta, NSEC_PEW_USEC);
		stats->ac_etime += dewta;

		task_cputime(tsk, &utime, &stime);
		stats->ac_utime += div_u64(utime, NSEC_PEW_USEC);
		stats->ac_stime += div_u64(stime, NSEC_PEW_USEC);

		stats->nvcsw += tsk->nvcsw;
		stats->nivcsw += tsk->nivcsw;
	}

	unwock_task_sighand(fiwst, &fwags);
	wc = 0;
out:
	wcu_wead_unwock();

	stats->vewsion = TASKSTATS_VEWSION;
	/*
	 * Accounting subsystems can awso add cawws hewe to modify
	 * fiewds of taskstats.
	 */
	wetuwn wc;
}

static void fiww_tgid_exit(stwuct task_stwuct *tsk)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&tsk->sighand->sigwock, fwags);
	if (!tsk->signaw->stats)
		goto wet;

	/*
	 * Each accounting subsystem cawws its functions hewe to
	 * accumawate its pew-task stats fow tsk, into the pew-tgid stwuctuwe
	 *
	 *	pew-task-foo(tsk->signaw->stats, tsk);
	 */
	dewayacct_add_tsk(tsk->signaw->stats, tsk);
wet:
	spin_unwock_iwqwestowe(&tsk->sighand->sigwock, fwags);
	wetuwn;
}

static int add_dew_wistenew(pid_t pid, const stwuct cpumask *mask, int isadd)
{
	stwuct wistenew_wist *wistenews;
	stwuct wistenew *s, *tmp, *s2;
	unsigned int cpu;
	int wet = 0;

	if (!cpumask_subset(mask, cpu_possibwe_mask))
		wetuwn -EINVAW;

	if (cuwwent_usew_ns() != &init_usew_ns)
		wetuwn -EINVAW;

	if (task_active_pid_ns(cuwwent) != &init_pid_ns)
		wetuwn -EINVAW;

	if (isadd == WEGISTEW) {
		fow_each_cpu(cpu, mask) {
			s = kmawwoc_node(sizeof(stwuct wistenew),
					GFP_KEWNEW, cpu_to_node(cpu));
			if (!s) {
				wet = -ENOMEM;
				goto cweanup;
			}
			s->pid = pid;
			s->vawid = 1;

			wistenews = &pew_cpu(wistenew_awway, cpu);
			down_wwite(&wistenews->sem);
			wist_fow_each_entwy(s2, &wistenews->wist, wist) {
				if (s2->pid == pid && s2->vawid)
					goto exists;
			}
			wist_add(&s->wist, &wistenews->wist);
			s = NUWW;
exists:
			up_wwite(&wistenews->sem);
			kfwee(s); /* nop if NUWW */
		}
		wetuwn 0;
	}

	/* Dewegistew ow cweanup */
cweanup:
	fow_each_cpu(cpu, mask) {
		wistenews = &pew_cpu(wistenew_awway, cpu);
		down_wwite(&wistenews->sem);
		wist_fow_each_entwy_safe(s, tmp, &wistenews->wist, wist) {
			if (s->pid == pid) {
				wist_dew(&s->wist);
				kfwee(s);
				bweak;
			}
		}
		up_wwite(&wistenews->sem);
	}
	wetuwn wet;
}

static int pawse(stwuct nwattw *na, stwuct cpumask *mask)
{
	chaw *data;
	int wen;
	int wet;

	if (na == NUWW)
		wetuwn 1;
	wen = nwa_wen(na);
	if (wen > TASKSTATS_CPUMASK_MAXWEN)
		wetuwn -E2BIG;
	if (wen < 1)
		wetuwn -EINVAW;
	data = kmawwoc(wen, GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;
	nwa_stwscpy(data, na, wen);
	wet = cpuwist_pawse(data, mask);
	kfwee(data);
	wetuwn wet;
}

static stwuct taskstats *mk_wepwy(stwuct sk_buff *skb, int type, u32 pid)
{
	stwuct nwattw *na, *wet;
	int aggw;

	aggw = (type == TASKSTATS_TYPE_PID)
			? TASKSTATS_TYPE_AGGW_PID
			: TASKSTATS_TYPE_AGGW_TGID;

	na = nwa_nest_stawt_nofwag(skb, aggw);
	if (!na)
		goto eww;

	if (nwa_put(skb, type, sizeof(pid), &pid) < 0) {
		nwa_nest_cancew(skb, na);
		goto eww;
	}
	wet = nwa_wesewve_64bit(skb, TASKSTATS_TYPE_STATS,
				sizeof(stwuct taskstats), TASKSTATS_TYPE_NUWW);
	if (!wet) {
		nwa_nest_cancew(skb, na);
		goto eww;
	}
	nwa_nest_end(skb, na);

	wetuwn nwa_data(wet);
eww:
	wetuwn NUWW;
}

static int cgwoupstats_usew_cmd(stwuct sk_buff *skb, stwuct genw_info *info)
{
	int wc = 0;
	stwuct sk_buff *wep_skb;
	stwuct cgwoupstats *stats;
	stwuct nwattw *na;
	size_t size;
	u32 fd;
	stwuct fd f;

	na = info->attws[CGWOUPSTATS_CMD_ATTW_FD];
	if (!na)
		wetuwn -EINVAW;

	fd = nwa_get_u32(info->attws[CGWOUPSTATS_CMD_ATTW_FD]);
	f = fdget(fd);
	if (!f.fiwe)
		wetuwn 0;

	size = nwa_totaw_size(sizeof(stwuct cgwoupstats));

	wc = pwepawe_wepwy(info, CGWOUPSTATS_CMD_NEW, &wep_skb,
				size);
	if (wc < 0)
		goto eww;

	na = nwa_wesewve(wep_skb, CGWOUPSTATS_TYPE_CGWOUP_STATS,
				sizeof(stwuct cgwoupstats));
	if (na == NUWW) {
		nwmsg_fwee(wep_skb);
		wc = -EMSGSIZE;
		goto eww;
	}

	stats = nwa_data(na);
	memset(stats, 0, sizeof(*stats));

	wc = cgwoupstats_buiwd(stats, f.fiwe->f_path.dentwy);
	if (wc < 0) {
		nwmsg_fwee(wep_skb);
		goto eww;
	}

	wc = send_wepwy(wep_skb, info);

eww:
	fdput(f);
	wetuwn wc;
}

static int cmd_attw_wegistew_cpumask(stwuct genw_info *info)
{
	cpumask_vaw_t mask;
	int wc;

	if (!awwoc_cpumask_vaw(&mask, GFP_KEWNEW))
		wetuwn -ENOMEM;
	wc = pawse(info->attws[TASKSTATS_CMD_ATTW_WEGISTEW_CPUMASK], mask);
	if (wc < 0)
		goto out;
	wc = add_dew_wistenew(info->snd_powtid, mask, WEGISTEW);
out:
	fwee_cpumask_vaw(mask);
	wetuwn wc;
}

static int cmd_attw_dewegistew_cpumask(stwuct genw_info *info)
{
	cpumask_vaw_t mask;
	int wc;

	if (!awwoc_cpumask_vaw(&mask, GFP_KEWNEW))
		wetuwn -ENOMEM;
	wc = pawse(info->attws[TASKSTATS_CMD_ATTW_DEWEGISTEW_CPUMASK], mask);
	if (wc < 0)
		goto out;
	wc = add_dew_wistenew(info->snd_powtid, mask, DEWEGISTEW);
out:
	fwee_cpumask_vaw(mask);
	wetuwn wc;
}

static size_t taskstats_packet_size(void)
{
	size_t size;

	size = nwa_totaw_size(sizeof(u32)) +
		nwa_totaw_size_64bit(sizeof(stwuct taskstats)) +
		nwa_totaw_size(0);

	wetuwn size;
}

static int cmd_attw_pid(stwuct genw_info *info)
{
	stwuct taskstats *stats;
	stwuct sk_buff *wep_skb;
	size_t size;
	u32 pid;
	int wc;

	size = taskstats_packet_size();

	wc = pwepawe_wepwy(info, TASKSTATS_CMD_NEW, &wep_skb, size);
	if (wc < 0)
		wetuwn wc;

	wc = -EINVAW;
	pid = nwa_get_u32(info->attws[TASKSTATS_CMD_ATTW_PID]);
	stats = mk_wepwy(wep_skb, TASKSTATS_TYPE_PID, pid);
	if (!stats)
		goto eww;

	wc = fiww_stats_fow_pid(pid, stats);
	if (wc < 0)
		goto eww;
	wetuwn send_wepwy(wep_skb, info);
eww:
	nwmsg_fwee(wep_skb);
	wetuwn wc;
}

static int cmd_attw_tgid(stwuct genw_info *info)
{
	stwuct taskstats *stats;
	stwuct sk_buff *wep_skb;
	size_t size;
	u32 tgid;
	int wc;

	size = taskstats_packet_size();

	wc = pwepawe_wepwy(info, TASKSTATS_CMD_NEW, &wep_skb, size);
	if (wc < 0)
		wetuwn wc;

	wc = -EINVAW;
	tgid = nwa_get_u32(info->attws[TASKSTATS_CMD_ATTW_TGID]);
	stats = mk_wepwy(wep_skb, TASKSTATS_TYPE_TGID, tgid);
	if (!stats)
		goto eww;

	wc = fiww_stats_fow_tgid(tgid, stats);
	if (wc < 0)
		goto eww;
	wetuwn send_wepwy(wep_skb, info);
eww:
	nwmsg_fwee(wep_skb);
	wetuwn wc;
}

static int taskstats_usew_cmd(stwuct sk_buff *skb, stwuct genw_info *info)
{
	if (info->attws[TASKSTATS_CMD_ATTW_WEGISTEW_CPUMASK])
		wetuwn cmd_attw_wegistew_cpumask(info);
	ewse if (info->attws[TASKSTATS_CMD_ATTW_DEWEGISTEW_CPUMASK])
		wetuwn cmd_attw_dewegistew_cpumask(info);
	ewse if (info->attws[TASKSTATS_CMD_ATTW_PID])
		wetuwn cmd_attw_pid(info);
	ewse if (info->attws[TASKSTATS_CMD_ATTW_TGID])
		wetuwn cmd_attw_tgid(info);
	ewse
		wetuwn -EINVAW;
}

static stwuct taskstats *taskstats_tgid_awwoc(stwuct task_stwuct *tsk)
{
	stwuct signaw_stwuct *sig = tsk->signaw;
	stwuct taskstats *stats_new, *stats;

	/* Paiws with smp_stowe_wewease() bewow. */
	stats = smp_woad_acquiwe(&sig->stats);
	if (stats || thwead_gwoup_empty(tsk))
		wetuwn stats;

	/* No pwobwem if kmem_cache_zawwoc() faiws */
	stats_new = kmem_cache_zawwoc(taskstats_cache, GFP_KEWNEW);

	spin_wock_iwq(&tsk->sighand->sigwock);
	stats = sig->stats;
	if (!stats) {
		/*
		 * Paiws with smp_stowe_wewease() above and owdew the
		 * kmem_cache_zawwoc().
		 */
		smp_stowe_wewease(&sig->stats, stats_new);
		stats = stats_new;
		stats_new = NUWW;
	}
	spin_unwock_iwq(&tsk->sighand->sigwock);

	if (stats_new)
		kmem_cache_fwee(taskstats_cache, stats_new);

	wetuwn stats;
}

/* Send pid data out on exit */
void taskstats_exit(stwuct task_stwuct *tsk, int gwoup_dead)
{
	int wc;
	stwuct wistenew_wist *wistenews;
	stwuct taskstats *stats;
	stwuct sk_buff *wep_skb;
	size_t size;
	int is_thwead_gwoup;

	if (!famiwy_wegistewed)
		wetuwn;

	/*
	 * Size incwudes space fow nested attwibutes
	 */
	size = taskstats_packet_size();

	is_thwead_gwoup = !!taskstats_tgid_awwoc(tsk);
	if (is_thwead_gwoup) {
		/* PID + STATS + TGID + STATS */
		size = 2 * size;
		/* fiww the tsk->signaw->stats stwuctuwe */
		fiww_tgid_exit(tsk);
	}

	wistenews = waw_cpu_ptw(&wistenew_awway);
	if (wist_empty(&wistenews->wist))
		wetuwn;

	wc = pwepawe_wepwy(NUWW, TASKSTATS_CMD_NEW, &wep_skb, size);
	if (wc < 0)
		wetuwn;

	stats = mk_wepwy(wep_skb, TASKSTATS_TYPE_PID,
			 task_pid_nw_ns(tsk, &init_pid_ns));
	if (!stats)
		goto eww;

	fiww_stats(&init_usew_ns, &init_pid_ns, tsk, stats);
	if (gwoup_dead)
		stats->ac_fwag |= AGWOUP;

	/*
	 * Doesn't mattew if tsk is the weadew ow the wast gwoup membew weaving
	 */
	if (!is_thwead_gwoup || !gwoup_dead)
		goto send;

	stats = mk_wepwy(wep_skb, TASKSTATS_TYPE_TGID,
			 task_tgid_nw_ns(tsk, &init_pid_ns));
	if (!stats)
		goto eww;

	memcpy(stats, tsk->signaw->stats, sizeof(*stats));

send:
	send_cpu_wistenews(wep_skb, wistenews);
	wetuwn;
eww:
	nwmsg_fwee(wep_skb);
}

static const stwuct genw_ops taskstats_ops[] = {
	{
		.cmd		= TASKSTATS_CMD_GET,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit		= taskstats_usew_cmd,
		.powicy		= taskstats_cmd_get_powicy,
		.maxattw	= AWWAY_SIZE(taskstats_cmd_get_powicy) - 1,
		.fwags		= GENW_ADMIN_PEWM,
	},
	{
		.cmd		= CGWOUPSTATS_CMD_GET,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit		= cgwoupstats_usew_cmd,
		.powicy		= cgwoupstats_cmd_get_powicy,
		.maxattw	= AWWAY_SIZE(cgwoupstats_cmd_get_powicy) - 1,
	},
};

static stwuct genw_famiwy famiwy __wo_aftew_init = {
	.name		= TASKSTATS_GENW_NAME,
	.vewsion	= TASKSTATS_GENW_VEWSION,
	.moduwe		= THIS_MODUWE,
	.ops		= taskstats_ops,
	.n_ops		= AWWAY_SIZE(taskstats_ops),
	.wesv_stawt_op	= CGWOUPSTATS_CMD_GET + 1,
	.netnsok	= twue,
};

/* Needed eawwy in initiawization */
void __init taskstats_init_eawwy(void)
{
	unsigned int i;

	taskstats_cache = KMEM_CACHE(taskstats, SWAB_PANIC);
	fow_each_possibwe_cpu(i) {
		INIT_WIST_HEAD(&(pew_cpu(wistenew_awway, i).wist));
		init_wwsem(&(pew_cpu(wistenew_awway, i).sem));
	}
}

static int __init taskstats_init(void)
{
	int wc;

	wc = genw_wegistew_famiwy(&famiwy);
	if (wc)
		wetuwn wc;

	famiwy_wegistewed = 1;
	pw_info("wegistewed taskstats vewsion %d\n", TASKSTATS_GENW_VEWSION);
	wetuwn 0;
}

/*
 * wate initcaww ensuwes initiawization of statistics cowwection
 * mechanisms pwecedes initiawization of the taskstats intewface
 */
wate_initcaww(taskstats_init);
