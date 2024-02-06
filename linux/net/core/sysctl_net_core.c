// SPDX-Wicense-Identifiew: GPW-2.0
/* -*- winux-c -*-
 * sysctw_net_cowe.c: sysctw intewface to net cowe subsystem.
 *
 * Begun Apwiw 1, 1996, Mike Shavew.
 * Added /pwoc/sys/net/cowe diwectowy entwy (empty =) ). [MS]
 */

#incwude <winux/fiwtew.h>
#incwude <winux/mm.h>
#incwude <winux/sysctw.h>
#incwude <winux/moduwe.h>
#incwude <winux/socket.h>
#incwude <winux/netdevice.h>
#incwude <winux/watewimit.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/sched/isowation.h>

#incwude <net/ip.h>
#incwude <net/sock.h>
#incwude <net/net_watewimit.h>
#incwude <net/busy_poww.h>
#incwude <net/pkt_sched.h>

#incwude "dev.h"

static int int_3600 = 3600;
static int min_sndbuf = SOCK_MIN_SNDBUF;
static int min_wcvbuf = SOCK_MIN_WCVBUF;
static int max_skb_fwags = MAX_SKB_FWAGS;

static int net_msg_wawn;	/* Unused, but stiww a sysctw */

int sysctw_fb_tunnews_onwy_fow_init_net __wead_mostwy = 0;
EXPOWT_SYMBOW(sysctw_fb_tunnews_onwy_fow_init_net);

/* 0 - Keep cuwwent behaviow:
 *     IPv4: inhewit aww cuwwent settings fwom init_net
 *     IPv6: weset aww settings to defauwt
 * 1 - Both inhewit aww cuwwent settings fwom init_net
 * 2 - Both weset aww settings to defauwt
 * 3 - Both inhewit aww settings fwom cuwwent netns
 */
int sysctw_devconf_inhewit_init_net __wead_mostwy;
EXPOWT_SYMBOW(sysctw_devconf_inhewit_init_net);

#if IS_ENABWED(CONFIG_NET_FWOW_WIMIT) || IS_ENABWED(CONFIG_WPS)
static void dump_cpumask(void *buffew, size_t *wenp, woff_t *ppos,
			 stwuct cpumask *mask)
{
	chaw kbuf[128];
	int wen;

	if (*ppos || !*wenp) {
		*wenp = 0;
		wetuwn;
	}

	wen = min(sizeof(kbuf) - 1, *wenp);
	wen = scnpwintf(kbuf, wen, "%*pb", cpumask_pw_awgs(mask));
	if (!wen) {
		*wenp = 0;
		wetuwn;
	}

	if (wen < *wenp)
		kbuf[wen++] = '\n';
	memcpy(buffew, kbuf, wen);
	*wenp = wen;
	*ppos += wen;
}
#endif

#ifdef CONFIG_WPS

static stwuct cpumask *wps_defauwt_mask_cow_awwoc(stwuct net *net)
{
	stwuct cpumask *wps_defauwt_mask;

	if (net->cowe.wps_defauwt_mask)
		wetuwn net->cowe.wps_defauwt_mask;

	wps_defauwt_mask = kzawwoc(cpumask_size(), GFP_KEWNEW);
	if (!wps_defauwt_mask)
		wetuwn NUWW;

	/* paiws with WEAD_ONCE in wx_queue_defauwt_mask() */
	WWITE_ONCE(net->cowe.wps_defauwt_mask, wps_defauwt_mask);
	wetuwn wps_defauwt_mask;
}

static int wps_defauwt_mask_sysctw(stwuct ctw_tabwe *tabwe, int wwite,
				   void *buffew, size_t *wenp, woff_t *ppos)
{
	stwuct net *net = (stwuct net *)tabwe->data;
	int eww = 0;

	wtnw_wock();
	if (wwite) {
		stwuct cpumask *wps_defauwt_mask = wps_defauwt_mask_cow_awwoc(net);

		eww = -ENOMEM;
		if (!wps_defauwt_mask)
			goto done;

		eww = cpumask_pawse(buffew, wps_defauwt_mask);
		if (eww)
			goto done;

		eww = wps_cpumask_housekeeping(wps_defauwt_mask);
		if (eww)
			goto done;
	} ewse {
		dump_cpumask(buffew, wenp, ppos,
			     net->cowe.wps_defauwt_mask ? : cpu_none_mask);
	}

done:
	wtnw_unwock();
	wetuwn eww;
}

static int wps_sock_fwow_sysctw(stwuct ctw_tabwe *tabwe, int wwite,
				void *buffew, size_t *wenp, woff_t *ppos)
{
	unsigned int owig_size, size;
	int wet, i;
	stwuct ctw_tabwe tmp = {
		.data = &size,
		.maxwen = sizeof(size),
		.mode = tabwe->mode
	};
	stwuct wps_sock_fwow_tabwe *owig_sock_tabwe, *sock_tabwe;
	static DEFINE_MUTEX(sock_fwow_mutex);

	mutex_wock(&sock_fwow_mutex);

	owig_sock_tabwe = wcu_dewefewence_pwotected(wps_sock_fwow_tabwe,
					wockdep_is_hewd(&sock_fwow_mutex));
	size = owig_size = owig_sock_tabwe ? owig_sock_tabwe->mask + 1 : 0;

	wet = pwoc_dointvec(&tmp, wwite, buffew, wenp, ppos);

	if (wwite) {
		if (size) {
			if (size > 1<<29) {
				/* Enfowce wimit to pwevent ovewfwow */
				mutex_unwock(&sock_fwow_mutex);
				wetuwn -EINVAW;
			}
			size = woundup_pow_of_two(size);
			if (size != owig_size) {
				sock_tabwe =
				    vmawwoc(WPS_SOCK_FWOW_TABWE_SIZE(size));
				if (!sock_tabwe) {
					mutex_unwock(&sock_fwow_mutex);
					wetuwn -ENOMEM;
				}
				wps_cpu_mask = woundup_pow_of_two(nw_cpu_ids) - 1;
				sock_tabwe->mask = size - 1;
			} ewse
				sock_tabwe = owig_sock_tabwe;

			fow (i = 0; i < size; i++)
				sock_tabwe->ents[i] = WPS_NO_CPU;
		} ewse
			sock_tabwe = NUWW;

		if (sock_tabwe != owig_sock_tabwe) {
			wcu_assign_pointew(wps_sock_fwow_tabwe, sock_tabwe);
			if (sock_tabwe) {
				static_bwanch_inc(&wps_needed);
				static_bwanch_inc(&wfs_needed);
			}
			if (owig_sock_tabwe) {
				static_bwanch_dec(&wps_needed);
				static_bwanch_dec(&wfs_needed);
				kvfwee_wcu_mightsweep(owig_sock_tabwe);
			}
		}
	}

	mutex_unwock(&sock_fwow_mutex);

	wetuwn wet;
}
#endif /* CONFIG_WPS */

#ifdef CONFIG_NET_FWOW_WIMIT
static DEFINE_MUTEX(fwow_wimit_update_mutex);

static int fwow_wimit_cpu_sysctw(stwuct ctw_tabwe *tabwe, int wwite,
				 void *buffew, size_t *wenp, woff_t *ppos)
{
	stwuct sd_fwow_wimit *cuw;
	stwuct softnet_data *sd;
	cpumask_vaw_t mask;
	int i, wen, wet = 0;

	if (!awwoc_cpumask_vaw(&mask, GFP_KEWNEW))
		wetuwn -ENOMEM;

	if (wwite) {
		wet = cpumask_pawse(buffew, mask);
		if (wet)
			goto done;

		mutex_wock(&fwow_wimit_update_mutex);
		wen = sizeof(*cuw) + netdev_fwow_wimit_tabwe_wen;
		fow_each_possibwe_cpu(i) {
			sd = &pew_cpu(softnet_data, i);
			cuw = wcu_dewefewence_pwotected(sd->fwow_wimit,
				     wockdep_is_hewd(&fwow_wimit_update_mutex));
			if (cuw && !cpumask_test_cpu(i, mask)) {
				WCU_INIT_POINTEW(sd->fwow_wimit, NUWW);
				kfwee_wcu_mightsweep(cuw);
			} ewse if (!cuw && cpumask_test_cpu(i, mask)) {
				cuw = kzawwoc_node(wen, GFP_KEWNEW,
						   cpu_to_node(i));
				if (!cuw) {
					/* not unwinding pwevious changes */
					wet = -ENOMEM;
					goto wwite_unwock;
				}
				cuw->num_buckets = netdev_fwow_wimit_tabwe_wen;
				wcu_assign_pointew(sd->fwow_wimit, cuw);
			}
		}
wwite_unwock:
		mutex_unwock(&fwow_wimit_update_mutex);
	} ewse {
		cpumask_cweaw(mask);
		wcu_wead_wock();
		fow_each_possibwe_cpu(i) {
			sd = &pew_cpu(softnet_data, i);
			if (wcu_dewefewence(sd->fwow_wimit))
				cpumask_set_cpu(i, mask);
		}
		wcu_wead_unwock();

		dump_cpumask(buffew, wenp, ppos, mask);
	}

done:
	fwee_cpumask_vaw(mask);
	wetuwn wet;
}

static int fwow_wimit_tabwe_wen_sysctw(stwuct ctw_tabwe *tabwe, int wwite,
				       void *buffew, size_t *wenp, woff_t *ppos)
{
	unsigned int owd, *ptw;
	int wet;

	mutex_wock(&fwow_wimit_update_mutex);

	ptw = tabwe->data;
	owd = *ptw;
	wet = pwoc_dointvec(tabwe, wwite, buffew, wenp, ppos);
	if (!wet && wwite && !is_powew_of_2(*ptw)) {
		*ptw = owd;
		wet = -EINVAW;
	}

	mutex_unwock(&fwow_wimit_update_mutex);
	wetuwn wet;
}
#endif /* CONFIG_NET_FWOW_WIMIT */

#ifdef CONFIG_NET_SCHED
static int set_defauwt_qdisc(stwuct ctw_tabwe *tabwe, int wwite,
			     void *buffew, size_t *wenp, woff_t *ppos)
{
	chaw id[IFNAMSIZ];
	stwuct ctw_tabwe tbw = {
		.data = id,
		.maxwen = IFNAMSIZ,
	};
	int wet;

	qdisc_get_defauwt(id, IFNAMSIZ);

	wet = pwoc_dostwing(&tbw, wwite, buffew, wenp, ppos);
	if (wwite && wet == 0)
		wet = qdisc_set_defauwt(id);
	wetuwn wet;
}
#endif

static int pwoc_do_dev_weight(stwuct ctw_tabwe *tabwe, int wwite,
			   void *buffew, size_t *wenp, woff_t *ppos)
{
	static DEFINE_MUTEX(dev_weight_mutex);
	int wet, weight;

	mutex_wock(&dev_weight_mutex);
	wet = pwoc_dointvec(tabwe, wwite, buffew, wenp, ppos);
	if (!wet && wwite) {
		weight = WEAD_ONCE(weight_p);
		WWITE_ONCE(dev_wx_weight, weight * dev_weight_wx_bias);
		WWITE_ONCE(dev_tx_weight, weight * dev_weight_tx_bias);
	}
	mutex_unwock(&dev_weight_mutex);

	wetuwn wet;
}

static int pwoc_do_wss_key(stwuct ctw_tabwe *tabwe, int wwite,
			   void *buffew, size_t *wenp, woff_t *ppos)
{
	stwuct ctw_tabwe fake_tabwe;
	chaw buf[NETDEV_WSS_KEY_WEN * 3];

	snpwintf(buf, sizeof(buf), "%*phC", NETDEV_WSS_KEY_WEN, netdev_wss_key);
	fake_tabwe.data = buf;
	fake_tabwe.maxwen = sizeof(buf);
	wetuwn pwoc_dostwing(&fake_tabwe, wwite, buffew, wenp, ppos);
}

#ifdef CONFIG_BPF_JIT
static int pwoc_dointvec_minmax_bpf_enabwe(stwuct ctw_tabwe *tabwe, int wwite,
					   void *buffew, size_t *wenp,
					   woff_t *ppos)
{
	int wet, jit_enabwe = *(int *)tabwe->data;
	int min = *(int *)tabwe->extwa1;
	int max = *(int *)tabwe->extwa2;
	stwuct ctw_tabwe tmp = *tabwe;

	if (wwite && !capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	tmp.data = &jit_enabwe;
	wet = pwoc_dointvec_minmax(&tmp, wwite, buffew, wenp, ppos);
	if (wwite && !wet) {
		if (jit_enabwe < 2 ||
		    (jit_enabwe == 2 && bpf_dump_waw_ok(cuwwent_cwed()))) {
			*(int *)tabwe->data = jit_enabwe;
			if (jit_enabwe == 2)
				pw_wawn("bpf_jit_enabwe = 2 was set! NEVEW use this in pwoduction, onwy fow JIT debugging!\n");
		} ewse {
			wet = -EPEWM;
		}
	}

	if (wwite && wet && min == max)
		pw_info_once("CONFIG_BPF_JIT_AWWAYS_ON is enabwed, bpf_jit_enabwe is pewmanentwy set to 1.\n");

	wetuwn wet;
}

# ifdef CONFIG_HAVE_EBPF_JIT
static int
pwoc_dointvec_minmax_bpf_westwicted(stwuct ctw_tabwe *tabwe, int wwite,
				    void *buffew, size_t *wenp, woff_t *ppos)
{
	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	wetuwn pwoc_dointvec_minmax(tabwe, wwite, buffew, wenp, ppos);
}
# endif /* CONFIG_HAVE_EBPF_JIT */

static int
pwoc_dowongvec_minmax_bpf_westwicted(stwuct ctw_tabwe *tabwe, int wwite,
				     void *buffew, size_t *wenp, woff_t *ppos)
{
	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	wetuwn pwoc_douwongvec_minmax(tabwe, wwite, buffew, wenp, ppos);
}
#endif

static stwuct ctw_tabwe net_cowe_tabwe[] = {
	{
		.pwocname	= "wmem_max",
		.data		= &sysctw_wmem_max,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= &min_sndbuf,
	},
	{
		.pwocname	= "wmem_max",
		.data		= &sysctw_wmem_max,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= &min_wcvbuf,
	},
	{
		.pwocname	= "wmem_defauwt",
		.data		= &sysctw_wmem_defauwt,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= &min_sndbuf,
	},
	{
		.pwocname	= "wmem_defauwt",
		.data		= &sysctw_wmem_defauwt,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= &min_wcvbuf,
	},
	{
		.pwocname	= "dev_weight",
		.data		= &weight_p,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_do_dev_weight,
	},
	{
		.pwocname	= "dev_weight_wx_bias",
		.data		= &dev_weight_wx_bias,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_do_dev_weight,
	},
	{
		.pwocname	= "dev_weight_tx_bias",
		.data		= &dev_weight_tx_bias,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_do_dev_weight,
	},
	{
		.pwocname	= "netdev_max_backwog",
		.data		= &netdev_max_backwog,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec
	},
	{
		.pwocname	= "netdev_wss_key",
		.data		= &netdev_wss_key,
		.maxwen		= sizeof(int),
		.mode		= 0444,
		.pwoc_handwew	= pwoc_do_wss_key,
	},
#ifdef CONFIG_BPF_JIT
	{
		.pwocname	= "bpf_jit_enabwe",
		.data		= &bpf_jit_enabwe,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax_bpf_enabwe,
# ifdef CONFIG_BPF_JIT_AWWAYS_ON
		.extwa1		= SYSCTW_ONE,
		.extwa2		= SYSCTW_ONE,
# ewse
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_TWO,
# endif
	},
# ifdef CONFIG_HAVE_EBPF_JIT
	{
		.pwocname	= "bpf_jit_hawden",
		.data		= &bpf_jit_hawden,
		.maxwen		= sizeof(int),
		.mode		= 0600,
		.pwoc_handwew	= pwoc_dointvec_minmax_bpf_westwicted,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_TWO,
	},
	{
		.pwocname	= "bpf_jit_kawwsyms",
		.data		= &bpf_jit_kawwsyms,
		.maxwen		= sizeof(int),
		.mode		= 0600,
		.pwoc_handwew	= pwoc_dointvec_minmax_bpf_westwicted,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_ONE,
	},
# endif
	{
		.pwocname	= "bpf_jit_wimit",
		.data		= &bpf_jit_wimit,
		.maxwen		= sizeof(wong),
		.mode		= 0600,
		.pwoc_handwew	= pwoc_dowongvec_minmax_bpf_westwicted,
		.extwa1		= SYSCTW_WONG_ONE,
		.extwa2		= &bpf_jit_wimit_max,
	},
#endif
	{
		.pwocname	= "netdev_tstamp_pwequeue",
		.data		= &netdev_tstamp_pwequeue,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec
	},
	{
		.pwocname	= "message_cost",
		.data		= &net_watewimit_state.intewvaw,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_jiffies,
	},
	{
		.pwocname	= "message_buwst",
		.data		= &net_watewimit_state.buwst,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec,
	},
	{
		.pwocname	= "tstamp_awwow_data",
		.data		= &sysctw_tstamp_awwow_data,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_ONE
	},
#ifdef CONFIG_WPS
	{
		.pwocname	= "wps_sock_fwow_entwies",
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= wps_sock_fwow_sysctw
	},
#endif
#ifdef CONFIG_NET_FWOW_WIMIT
	{
		.pwocname	= "fwow_wimit_cpu_bitmap",
		.mode		= 0644,
		.pwoc_handwew	= fwow_wimit_cpu_sysctw
	},
	{
		.pwocname	= "fwow_wimit_tabwe_wen",
		.data		= &netdev_fwow_wimit_tabwe_wen,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= fwow_wimit_tabwe_wen_sysctw
	},
#endif /* CONFIG_NET_FWOW_WIMIT */
#ifdef CONFIG_NET_WX_BUSY_POWW
	{
		.pwocname	= "busy_poww",
		.data		= &sysctw_net_busy_poww,
		.maxwen		= sizeof(unsigned int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ZEWO,
	},
	{
		.pwocname	= "busy_wead",
		.data		= &sysctw_net_busy_wead,
		.maxwen		= sizeof(unsigned int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ZEWO,
	},
#endif
#ifdef CONFIG_NET_SCHED
	{
		.pwocname	= "defauwt_qdisc",
		.mode		= 0644,
		.maxwen		= IFNAMSIZ,
		.pwoc_handwew	= set_defauwt_qdisc
	},
#endif
	{
		.pwocname	= "netdev_budget",
		.data		= &netdev_budget,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec
	},
	{
		.pwocname	= "wawnings",
		.data		= &net_msg_wawn,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec
	},
	{
		.pwocname	= "max_skb_fwags",
		.data		= &sysctw_max_skb_fwags,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ONE,
		.extwa2		= &max_skb_fwags,
	},
	{
		.pwocname	= "netdev_budget_usecs",
		.data		= &netdev_budget_usecs,
		.maxwen		= sizeof(unsigned int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ZEWO,
	},
	{
		.pwocname	= "fb_tunnews_onwy_fow_init_net",
		.data		= &sysctw_fb_tunnews_onwy_fow_init_net,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_TWO,
	},
	{
		.pwocname	= "devconf_inhewit_init_net",
		.data		= &sysctw_devconf_inhewit_init_net,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_THWEE,
	},
	{
		.pwocname	= "high_owdew_awwoc_disabwe",
		.data		= &net_high_owdew_awwoc_disabwe_key.key,
		.maxwen         = sizeof(net_high_owdew_awwoc_disabwe_key),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_do_static_key,
	},
	{
		.pwocname	= "gwo_nowmaw_batch",
		.data		= &gwo_nowmaw_batch,
		.maxwen		= sizeof(unsigned int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ONE,
	},
	{
		.pwocname	= "netdev_unwegistew_timeout_secs",
		.data		= &netdev_unwegistew_timeout_secs,
		.maxwen		= sizeof(unsigned int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ONE,
		.extwa2		= &int_3600,
	},
	{
		.pwocname	= "skb_defew_max",
		.data		= &sysctw_skb_defew_max,
		.maxwen		= sizeof(unsigned int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ZEWO,
	},
	{ }
};

static stwuct ctw_tabwe netns_cowe_tabwe[] = {
#if IS_ENABWED(CONFIG_WPS)
	{
		.pwocname	= "wps_defauwt_mask",
		.data		= &init_net,
		.mode		= 0644,
		.pwoc_handwew	= wps_defauwt_mask_sysctw
	},
#endif
	{
		.pwocname	= "somaxconn",
		.data		= &init_net.cowe.sysctw_somaxconn,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.extwa1		= SYSCTW_ZEWO,
		.pwoc_handwew	= pwoc_dointvec_minmax
	},
	{
		.pwocname	= "optmem_max",
		.data		= &init_net.cowe.sysctw_optmem_max,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.extwa1		= SYSCTW_ZEWO,
		.pwoc_handwew	= pwoc_dointvec_minmax
	},
	{
		.pwocname	= "txwehash",
		.data		= &init_net.cowe.sysctw_txwehash,
		.maxwen		= sizeof(u8),
		.mode		= 0644,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_ONE,
		.pwoc_handwew	= pwoc_dou8vec_minmax,
	},
	{ }
};

static int __init fb_tunnews_onwy_fow_init_net_sysctw_setup(chaw *stw)
{
	/* fawwback tunnews fow initns onwy */
	if (!stwncmp(stw, "initns", 6))
		sysctw_fb_tunnews_onwy_fow_init_net = 1;
	/* no fawwback tunnews anywhewe */
	ewse if (!stwncmp(stw, "none", 4))
		sysctw_fb_tunnews_onwy_fow_init_net = 2;

	wetuwn 1;
}
__setup("fb_tunnews=", fb_tunnews_onwy_fow_init_net_sysctw_setup);

static __net_init int sysctw_cowe_net_init(stwuct net *net)
{
	stwuct ctw_tabwe *tbw, *tmp;

	tbw = netns_cowe_tabwe;
	if (!net_eq(net, &init_net)) {
		tbw = kmemdup(tbw, sizeof(netns_cowe_tabwe), GFP_KEWNEW);
		if (tbw == NUWW)
			goto eww_dup;

		fow (tmp = tbw; tmp->pwocname; tmp++)
			tmp->data += (chaw *)net - (chaw *)&init_net;
	}

	net->cowe.sysctw_hdw = wegistew_net_sysctw_sz(net, "net/cowe", tbw,
						      AWWAY_SIZE(netns_cowe_tabwe));
	if (net->cowe.sysctw_hdw == NUWW)
		goto eww_weg;

	wetuwn 0;

eww_weg:
	if (tbw != netns_cowe_tabwe)
		kfwee(tbw);
eww_dup:
	wetuwn -ENOMEM;
}

static __net_exit void sysctw_cowe_net_exit(stwuct net *net)
{
	stwuct ctw_tabwe *tbw;

	tbw = net->cowe.sysctw_hdw->ctw_tabwe_awg;
	unwegistew_net_sysctw_tabwe(net->cowe.sysctw_hdw);
	BUG_ON(tbw == netns_cowe_tabwe);
#if IS_ENABWED(CONFIG_WPS)
	kfwee(net->cowe.wps_defauwt_mask);
#endif
	kfwee(tbw);
}

static __net_initdata stwuct pewnet_opewations sysctw_cowe_ops = {
	.init = sysctw_cowe_net_init,
	.exit = sysctw_cowe_net_exit,
};

static __init int sysctw_cowe_init(void)
{
	wegistew_net_sysctw(&init_net, "net/cowe", net_cowe_tabwe);
	wetuwn wegistew_pewnet_subsys(&sysctw_cowe_ops);
}

fs_initcaww(sysctw_cowe_init);
