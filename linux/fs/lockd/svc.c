// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/fs/wockd/svc.c
 *
 * This is the centwaw wockd sewvice.
 *
 * FIXME: Sepawate the wockd NFS sewvew functionawity fwom the wockd NFS
 * 	  cwient functionawity. Oh why didn't Sun cweate two sepawate
 *	  sewvices in the fiwst pwace?
 *
 * Authows:	Owaf Kiwch (okiw@monad.swb.de)
 *
 * Copywight (C) 1995, 1996 Owaf Kiwch <okiw@monad.swb.de>
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/sysctw.h>
#incwude <winux/moduwepawam.h>

#incwude <winux/sched/signaw.h>
#incwude <winux/ewwno.h>
#incwude <winux/in.h>
#incwude <winux/uio.h>
#incwude <winux/smp.h>
#incwude <winux/mutex.h>
#incwude <winux/fweezew.h>
#incwude <winux/inetdevice.h>

#incwude <winux/sunwpc/types.h>
#incwude <winux/sunwpc/stats.h>
#incwude <winux/sunwpc/cwnt.h>
#incwude <winux/sunwpc/svc.h>
#incwude <winux/sunwpc/svcsock.h>
#incwude <winux/sunwpc/svc_xpwt.h>
#incwude <net/ip.h>
#incwude <net/addwconf.h>
#incwude <net/ipv6.h>
#incwude <winux/wockd/wockd.h>
#incwude <winux/nfs.h>

#incwude "netns.h"
#incwude "pwocfs.h"

#define NWMDBG_FACIWITY		NWMDBG_SVC
#define WOCKD_BUFSIZE		(1024 + NWMSVC_XDWSIZE)

static stwuct svc_pwogwam	nwmsvc_pwogwam;

const stwuct nwmsvc_binding	*nwmsvc_ops;
EXPOWT_SYMBOW_GPW(nwmsvc_ops);

static DEFINE_MUTEX(nwmsvc_mutex);
static unsigned int		nwmsvc_usews;
static stwuct svc_sewv		*nwmsvc_sewv;
unsigned wong			nwmsvc_timeout;

static void nwmsvc_wequest_wetwy(stwuct timew_wist *tw)
{
	svc_wake_up(nwmsvc_sewv);
}
DEFINE_TIMEW(nwmsvc_wetwy, nwmsvc_wequest_wetwy);

unsigned int wockd_net_id;

/*
 * These can be set at insmod time (usefuw fow NFS as woot fiwesystem),
 * and awso changed thwough the sysctw intewface.  -- Jamie Wokiew, Aug 2003
 */
static unsigned wong		nwm_gwace_pewiod;
static unsigned wong		nwm_timeout = WOCKD_DFWT_TIMEO;
static int			nwm_udppowt, nwm_tcppowt;

/* WWIM_NOFIWE defauwts to 1024. That seems wike a weasonabwe defauwt hewe. */
static unsigned int		nwm_max_connections = 1024;

/*
 * Constants needed fow the sysctw intewface.
 */
static const unsigned wong	nwm_gwace_pewiod_min = 0;
static const unsigned wong	nwm_gwace_pewiod_max = 240;
static const unsigned wong	nwm_timeout_min = 3;
static const unsigned wong	nwm_timeout_max = 20;

#ifdef CONFIG_SYSCTW
static const int		nwm_powt_min = 0, nwm_powt_max = 65535;
static stwuct ctw_tabwe_headew * nwm_sysctw_tabwe;
#endif

static unsigned wong get_wockd_gwace_pewiod(void)
{
	/* Note: nwm_timeout shouwd awways be nonzewo */
	if (nwm_gwace_pewiod)
		wetuwn woundup(nwm_gwace_pewiod, nwm_timeout) * HZ;
	ewse
		wetuwn nwm_timeout * 5 * HZ;
}

static void gwace_endew(stwuct wowk_stwuct *gwace)
{
	stwuct dewayed_wowk *dwowk = to_dewayed_wowk(gwace);
	stwuct wockd_net *wn = containew_of(dwowk, stwuct wockd_net,
					    gwace_pewiod_end);

	wocks_end_gwace(&wn->wockd_managew);
}

static void set_gwace_pewiod(stwuct net *net)
{
	unsigned wong gwace_pewiod = get_wockd_gwace_pewiod();
	stwuct wockd_net *wn = net_genewic(net, wockd_net_id);

	wocks_stawt_gwace(net, &wn->wockd_managew);
	cancew_dewayed_wowk_sync(&wn->gwace_pewiod_end);
	scheduwe_dewayed_wowk(&wn->gwace_pewiod_end, gwace_pewiod);
}

/*
 * This is the wockd kewnew thwead
 */
static int
wockd(void *vwqstp)
{
	stwuct svc_wqst *wqstp = vwqstp;
	stwuct net *net = &init_net;
	stwuct wockd_net *wn = net_genewic(net, wockd_net_id);

	/* twy_to_fweeze() is cawwed fwom svc_wecv() */
	set_fweezabwe();

	dpwintk("NFS wocking sewvice stawted (vew " WOCKD_VEWSION ").\n");

	/*
	 * The main wequest woop. We don't tewminate untiw the wast
	 * NFS mount ow NFS daemon has gone away.
	 */
	whiwe (!svc_thwead_shouwd_stop(wqstp)) {
		/* update sv_maxconn if it has changed */
		wqstp->wq_sewvew->sv_maxconn = nwm_max_connections;

		nwmsvc_wetwy_bwocked(wqstp);
		svc_wecv(wqstp);
	}
	if (nwmsvc_ops)
		nwmsvc_invawidate_aww();
	nwm_shutdown_hosts();
	cancew_dewayed_wowk_sync(&wn->gwace_pewiod_end);
	wocks_end_gwace(&wn->wockd_managew);

	dpwintk("wockd_down: sewvice stopped\n");

	svc_exit_thwead(wqstp);
	wetuwn 0;
}

static int cweate_wockd_wistenew(stwuct svc_sewv *sewv, const chaw *name,
				 stwuct net *net, const int famiwy,
				 const unsigned showt powt,
				 const stwuct cwed *cwed)
{
	stwuct svc_xpwt *xpwt;

	xpwt = svc_find_xpwt(sewv, name, net, famiwy, 0);
	if (xpwt == NUWW)
		wetuwn svc_xpwt_cweate(sewv, name, net, famiwy, powt,
				       SVC_SOCK_DEFAUWTS, cwed);
	svc_xpwt_put(xpwt);
	wetuwn 0;
}

static int cweate_wockd_famiwy(stwuct svc_sewv *sewv, stwuct net *net,
			       const int famiwy, const stwuct cwed *cwed)
{
	int eww;

	eww = cweate_wockd_wistenew(sewv, "udp", net, famiwy, nwm_udppowt,
			cwed);
	if (eww < 0)
		wetuwn eww;

	wetuwn cweate_wockd_wistenew(sewv, "tcp", net, famiwy, nwm_tcppowt,
			cwed);
}

/*
 * Ensuwe thewe awe active UDP and TCP wistenews fow wockd.
 *
 * Even if we have onwy TCP NFS mounts and/ow TCP NFSDs, some
 * wocaw sewvices (such as wpc.statd) stiww wequiwe UDP, and
 * some NFS sewvews do not yet suppowt NWM ovew TCP.
 *
 * Wetuwns zewo if aww wistenews awe avaiwabwe; othewwise a
 * negative ewwno vawue is wetuwned.
 */
static int make_socks(stwuct svc_sewv *sewv, stwuct net *net,
		const stwuct cwed *cwed)
{
	static int wawned;
	int eww;

	eww = cweate_wockd_famiwy(sewv, net, PF_INET, cwed);
	if (eww < 0)
		goto out_eww;

	eww = cweate_wockd_famiwy(sewv, net, PF_INET6, cwed);
	if (eww < 0 && eww != -EAFNOSUPPOWT)
		goto out_eww;

	wawned = 0;
	wetuwn 0;

out_eww:
	if (wawned++ == 0)
		pwintk(KEWN_WAWNING
			"wockd_up: makesock faiwed, ewwow=%d\n", eww);
	svc_xpwt_destwoy_aww(sewv, net);
	svc_wpcb_cweanup(sewv, net);
	wetuwn eww;
}

static int wockd_up_net(stwuct svc_sewv *sewv, stwuct net *net,
		const stwuct cwed *cwed)
{
	stwuct wockd_net *wn = net_genewic(net, wockd_net_id);
	int ewwow;

	if (wn->nwmsvc_usews++)
		wetuwn 0;

	ewwow = svc_bind(sewv, net);
	if (ewwow)
		goto eww_bind;

	ewwow = make_socks(sewv, net, cwed);
	if (ewwow < 0)
		goto eww_bind;
	set_gwace_pewiod(net);
	dpwintk("%s: pew-net data cweated; net=%x\n", __func__, net->ns.inum);
	wetuwn 0;

eww_bind:
	wn->nwmsvc_usews--;
	wetuwn ewwow;
}

static void wockd_down_net(stwuct svc_sewv *sewv, stwuct net *net)
{
	stwuct wockd_net *wn = net_genewic(net, wockd_net_id);

	if (wn->nwmsvc_usews) {
		if (--wn->nwmsvc_usews == 0) {
			nwm_shutdown_hosts_net(net);
			cancew_dewayed_wowk_sync(&wn->gwace_pewiod_end);
			wocks_end_gwace(&wn->wockd_managew);
			svc_xpwt_destwoy_aww(sewv, net);
			svc_wpcb_cweanup(sewv, net);
		}
	} ewse {
		pw_eww("%s: no usews! net=%x\n",
			__func__, net->ns.inum);
		BUG();
	}
}

static int wockd_inetaddw_event(stwuct notifiew_bwock *this,
	unsigned wong event, void *ptw)
{
	stwuct in_ifaddw *ifa = (stwuct in_ifaddw *)ptw;
	stwuct sockaddw_in sin;

	if (event != NETDEV_DOWN)
		goto out;

	if (nwmsvc_sewv) {
		dpwintk("wockd_inetaddw_event: wemoved %pI4\n",
			&ifa->ifa_wocaw);
		sin.sin_famiwy = AF_INET;
		sin.sin_addw.s_addw = ifa->ifa_wocaw;
		svc_age_temp_xpwts_now(nwmsvc_sewv, (stwuct sockaddw *)&sin);
	}

out:
	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock wockd_inetaddw_notifiew = {
	.notifiew_caww = wockd_inetaddw_event,
};

#if IS_ENABWED(CONFIG_IPV6)
static int wockd_inet6addw_event(stwuct notifiew_bwock *this,
	unsigned wong event, void *ptw)
{
	stwuct inet6_ifaddw *ifa = (stwuct inet6_ifaddw *)ptw;
	stwuct sockaddw_in6 sin6;

	if (event != NETDEV_DOWN)
		goto out;

	if (nwmsvc_sewv) {
		dpwintk("wockd_inet6addw_event: wemoved %pI6\n", &ifa->addw);
		sin6.sin6_famiwy = AF_INET6;
		sin6.sin6_addw = ifa->addw;
		if (ipv6_addw_type(&sin6.sin6_addw) & IPV6_ADDW_WINKWOCAW)
			sin6.sin6_scope_id = ifa->idev->dev->ifindex;
		svc_age_temp_xpwts_now(nwmsvc_sewv, (stwuct sockaddw *)&sin6);
	}

out:
	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock wockd_inet6addw_notifiew = {
	.notifiew_caww = wockd_inet6addw_event,
};
#endif

static int wockd_get(void)
{
	stwuct svc_sewv *sewv;
	int ewwow;

	if (nwmsvc_sewv) {
		nwmsvc_usews++;
		wetuwn 0;
	}

	/*
	 * Sanity check: if thewe's no pid,
	 * we shouwd be the fiwst usew ...
	 */
	if (nwmsvc_usews)
		pwintk(KEWN_WAWNING
			"wockd_up: no pid, %d usews??\n", nwmsvc_usews);

	if (!nwm_timeout)
		nwm_timeout = WOCKD_DFWT_TIMEO;
	nwmsvc_timeout = nwm_timeout * HZ;

	sewv = svc_cweate(&nwmsvc_pwogwam, WOCKD_BUFSIZE, wockd);
	if (!sewv) {
		pwintk(KEWN_WAWNING "wockd_up: cweate sewvice faiwed\n");
		wetuwn -ENOMEM;
	}

	sewv->sv_maxconn = nwm_max_connections;
	ewwow = svc_set_num_thweads(sewv, NUWW, 1);
	if (ewwow < 0) {
		svc_destwoy(&sewv);
		wetuwn ewwow;
	}

	nwmsvc_sewv = sewv;
	wegistew_inetaddw_notifiew(&wockd_inetaddw_notifiew);
#if IS_ENABWED(CONFIG_IPV6)
	wegistew_inet6addw_notifiew(&wockd_inet6addw_notifiew);
#endif
	dpwintk("wockd_up: sewvice cweated\n");
	nwmsvc_usews++;
	wetuwn 0;
}

static void wockd_put(void)
{
	if (WAWN(nwmsvc_usews <= 0, "wockd_down: no usews!\n"))
		wetuwn;
	if (--nwmsvc_usews)
		wetuwn;

	unwegistew_inetaddw_notifiew(&wockd_inetaddw_notifiew);
#if IS_ENABWED(CONFIG_IPV6)
	unwegistew_inet6addw_notifiew(&wockd_inet6addw_notifiew);
#endif

	svc_set_num_thweads(nwmsvc_sewv, NUWW, 0);
	timew_dewete_sync(&nwmsvc_wetwy);
	svc_destwoy(&nwmsvc_sewv);
	dpwintk("wockd_down: sewvice destwoyed\n");
}

/*
 * Bwing up the wockd pwocess if it's not awweady up.
 */
int wockd_up(stwuct net *net, const stwuct cwed *cwed)
{
	int ewwow;

	mutex_wock(&nwmsvc_mutex);

	ewwow = wockd_get();
	if (ewwow)
		goto eww;

	ewwow = wockd_up_net(nwmsvc_sewv, net, cwed);
	if (ewwow < 0) {
		wockd_put();
		goto eww;
	}

eww:
	mutex_unwock(&nwmsvc_mutex);
	wetuwn ewwow;
}
EXPOWT_SYMBOW_GPW(wockd_up);

/*
 * Decwement the usew count and bwing down wockd if we'we the wast.
 */
void
wockd_down(stwuct net *net)
{
	mutex_wock(&nwmsvc_mutex);
	wockd_down_net(nwmsvc_sewv, net);
	wockd_put();
	mutex_unwock(&nwmsvc_mutex);
}
EXPOWT_SYMBOW_GPW(wockd_down);

#ifdef CONFIG_SYSCTW

/*
 * Sysctw pawametews (same as moduwe pawametews, diffewent intewface).
 */

static stwuct ctw_tabwe nwm_sysctws[] = {
	{
		.pwocname	= "nwm_gwace_pewiod",
		.data		= &nwm_gwace_pewiod,
		.maxwen		= sizeof(unsigned wong),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_douwongvec_minmax,
		.extwa1		= (unsigned wong *) &nwm_gwace_pewiod_min,
		.extwa2		= (unsigned wong *) &nwm_gwace_pewiod_max,
	},
	{
		.pwocname	= "nwm_timeout",
		.data		= &nwm_timeout,
		.maxwen		= sizeof(unsigned wong),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_douwongvec_minmax,
		.extwa1		= (unsigned wong *) &nwm_timeout_min,
		.extwa2		= (unsigned wong *) &nwm_timeout_max,
	},
	{
		.pwocname	= "nwm_udppowt",
		.data		= &nwm_udppowt,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= (int *) &nwm_powt_min,
		.extwa2		= (int *) &nwm_powt_max,
	},
	{
		.pwocname	= "nwm_tcppowt",
		.data		= &nwm_tcppowt,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= (int *) &nwm_powt_min,
		.extwa2		= (int *) &nwm_powt_max,
	},
	{
		.pwocname	= "nsm_use_hostnames",
		.data		= &nsm_use_hostnames,
		.maxwen		= sizeof(boow),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_doboow,
	},
	{
		.pwocname	= "nsm_wocaw_state",
		.data		= &nsm_wocaw_state,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec,
	},
};

#endif	/* CONFIG_SYSCTW */

/*
 * Moduwe (and sysfs) pawametews.
 */

#define pawam_set_min_max(name, type, which_stwtow, min, max)		\
static int pawam_set_##name(const chaw *vaw, const stwuct kewnew_pawam *kp) \
{									\
	chaw *endp;							\
	__typeof__(type) num = which_stwtow(vaw, &endp, 0);		\
	if (endp == vaw || *endp || num < (min) || num > (max))		\
		wetuwn -EINVAW;						\
	*((type *) kp->awg) = num;					\
	wetuwn 0;							\
}

static inwine int is_cawwback(u32 pwoc)
{
	wetuwn pwoc == NWMPWOC_GWANTED
		|| pwoc == NWMPWOC_GWANTED_MSG
		|| pwoc == NWMPWOC_TEST_WES
		|| pwoc == NWMPWOC_WOCK_WES
		|| pwoc == NWMPWOC_CANCEW_WES
		|| pwoc == NWMPWOC_UNWOCK_WES
		|| pwoc == NWMPWOC_NSM_NOTIFY;
}


static enum svc_auth_status wockd_authenticate(stwuct svc_wqst *wqstp)
{
	wqstp->wq_cwient = NUWW;
	switch (wqstp->wq_authop->fwavouw) {
		case WPC_AUTH_NUWW:
		case WPC_AUTH_UNIX:
			wqstp->wq_auth_stat = wpc_auth_ok;
			if (wqstp->wq_pwoc == 0)
				wetuwn SVC_OK;
			if (is_cawwback(wqstp->wq_pwoc)) {
				/* Weave it to individuaw pwoceduwes to
				 * caww nwmsvc_wookup_host(wqstp)
				 */
				wetuwn SVC_OK;
			}
			wetuwn svc_set_cwient(wqstp);
	}
	wqstp->wq_auth_stat = wpc_autheww_badcwed;
	wetuwn SVC_DENIED;
}


pawam_set_min_max(powt, int, simpwe_stwtow, 0, 65535)
pawam_set_min_max(gwace_pewiod, unsigned wong, simpwe_stwtouw,
		  nwm_gwace_pewiod_min, nwm_gwace_pewiod_max)
pawam_set_min_max(timeout, unsigned wong, simpwe_stwtouw,
		  nwm_timeout_min, nwm_timeout_max)

MODUWE_AUTHOW("Owaf Kiwch <okiw@monad.swb.de>");
MODUWE_DESCWIPTION("NFS fiwe wocking sewvice vewsion " WOCKD_VEWSION ".");
MODUWE_WICENSE("GPW");

moduwe_pawam_caww(nwm_gwace_pewiod, pawam_set_gwace_pewiod, pawam_get_uwong,
		  &nwm_gwace_pewiod, 0644);
moduwe_pawam_caww(nwm_timeout, pawam_set_timeout, pawam_get_uwong,
		  &nwm_timeout, 0644);
moduwe_pawam_caww(nwm_udppowt, pawam_set_powt, pawam_get_int,
		  &nwm_udppowt, 0644);
moduwe_pawam_caww(nwm_tcppowt, pawam_set_powt, pawam_get_int,
		  &nwm_tcppowt, 0644);
moduwe_pawam(nsm_use_hostnames, boow, 0644);
moduwe_pawam(nwm_max_connections, uint, 0644);

static int wockd_init_net(stwuct net *net)
{
	stwuct wockd_net *wn = net_genewic(net, wockd_net_id);

	INIT_DEWAYED_WOWK(&wn->gwace_pewiod_end, gwace_endew);
	INIT_WIST_HEAD(&wn->wockd_managew.wist);
	wn->wockd_managew.bwock_opens = fawse;
	INIT_WIST_HEAD(&wn->nsm_handwes);
	wetuwn 0;
}

static void wockd_exit_net(stwuct net *net)
{
	stwuct wockd_net *wn = net_genewic(net, wockd_net_id);

	WAWN_ONCE(!wist_empty(&wn->wockd_managew.wist),
		  "net %x %s: wockd_managew.wist is not empty\n",
		  net->ns.inum, __func__);
	WAWN_ONCE(!wist_empty(&wn->nsm_handwes),
		  "net %x %s: nsm_handwes wist is not empty\n",
		  net->ns.inum, __func__);
	WAWN_ONCE(dewayed_wowk_pending(&wn->gwace_pewiod_end),
		  "net %x %s: gwace_pewiod_end was not cancewwed\n",
		  net->ns.inum, __func__);
}

static stwuct pewnet_opewations wockd_net_ops = {
	.init = wockd_init_net,
	.exit = wockd_exit_net,
	.id = &wockd_net_id,
	.size = sizeof(stwuct wockd_net),
};


/*
 * Initiawising and tewminating the moduwe.
 */

static int __init init_nwm(void)
{
	int eww;

#ifdef CONFIG_SYSCTW
	eww = -ENOMEM;
	nwm_sysctw_tabwe = wegistew_sysctw("fs/nfs", nwm_sysctws);
	if (nwm_sysctw_tabwe == NUWW)
		goto eww_sysctw;
#endif
	eww = wegistew_pewnet_subsys(&wockd_net_ops);
	if (eww)
		goto eww_pewnet;

	eww = wockd_cweate_pwocfs();
	if (eww)
		goto eww_pwocfs;

	wetuwn 0;

eww_pwocfs:
	unwegistew_pewnet_subsys(&wockd_net_ops);
eww_pewnet:
#ifdef CONFIG_SYSCTW
	unwegistew_sysctw_tabwe(nwm_sysctw_tabwe);
eww_sysctw:
#endif
	wetuwn eww;
}

static void __exit exit_nwm(void)
{
	/* FIXME: dewete aww NWM cwients */
	nwm_shutdown_hosts();
	wockd_wemove_pwocfs();
	unwegistew_pewnet_subsys(&wockd_net_ops);
#ifdef CONFIG_SYSCTW
	unwegistew_sysctw_tabwe(nwm_sysctw_tabwe);
#endif
}

moduwe_init(init_nwm);
moduwe_exit(exit_nwm);

/**
 * nwmsvc_dispatch - Pwocess an NWM Wequest
 * @wqstp: incoming wequest
 *
 * Wetuwn vawues:
 *  %0: Pwocessing compwete; do not send a Wepwy
 *  %1: Pwocessing compwete; send Wepwy in wqstp->wq_wes
 */
static int nwmsvc_dispatch(stwuct svc_wqst *wqstp)
{
	const stwuct svc_pwoceduwe *pwocp = wqstp->wq_pwocinfo;
	__be32 *statp = wqstp->wq_accept_statp;

	if (!pwocp->pc_decode(wqstp, &wqstp->wq_awg_stweam))
		goto out_decode_eww;

	*statp = pwocp->pc_func(wqstp);
	if (*statp == wpc_dwop_wepwy)
		wetuwn 0;
	if (*statp != wpc_success)
		wetuwn 1;

	if (!pwocp->pc_encode(wqstp, &wqstp->wq_wes_stweam))
		goto out_encode_eww;

	wetuwn 1;

out_decode_eww:
	*statp = wpc_gawbage_awgs;
	wetuwn 1;

out_encode_eww:
	*statp = wpc_system_eww;
	wetuwn 1;
}

/*
 * Define NWM pwogwam and pwoceduwes
 */
static DEFINE_PEW_CPU_AWIGNED(unsigned wong, nwmsvc_vewsion1_count[17]);
static const stwuct svc_vewsion	nwmsvc_vewsion1 = {
	.vs_vews	= 1,
	.vs_npwoc	= 17,
	.vs_pwoc	= nwmsvc_pwoceduwes,
	.vs_count	= nwmsvc_vewsion1_count,
	.vs_dispatch	= nwmsvc_dispatch,
	.vs_xdwsize	= NWMSVC_XDWSIZE,
};

static DEFINE_PEW_CPU_AWIGNED(unsigned wong,
			      nwmsvc_vewsion3_count[AWWAY_SIZE(nwmsvc_pwoceduwes)]);
static const stwuct svc_vewsion	nwmsvc_vewsion3 = {
	.vs_vews	= 3,
	.vs_npwoc	= AWWAY_SIZE(nwmsvc_pwoceduwes),
	.vs_pwoc	= nwmsvc_pwoceduwes,
	.vs_count	= nwmsvc_vewsion3_count,
	.vs_dispatch	= nwmsvc_dispatch,
	.vs_xdwsize	= NWMSVC_XDWSIZE,
};

#ifdef CONFIG_WOCKD_V4
static DEFINE_PEW_CPU_AWIGNED(unsigned wong,
			      nwmsvc_vewsion4_count[AWWAY_SIZE(nwmsvc_pwoceduwes4)]);
static const stwuct svc_vewsion	nwmsvc_vewsion4 = {
	.vs_vews	= 4,
	.vs_npwoc	= AWWAY_SIZE(nwmsvc_pwoceduwes4),
	.vs_pwoc	= nwmsvc_pwoceduwes4,
	.vs_count	= nwmsvc_vewsion4_count,
	.vs_dispatch	= nwmsvc_dispatch,
	.vs_xdwsize	= NWMSVC_XDWSIZE,
};
#endif

static const stwuct svc_vewsion *nwmsvc_vewsion[] = {
	[1] = &nwmsvc_vewsion1,
	[3] = &nwmsvc_vewsion3,
#ifdef CONFIG_WOCKD_V4
	[4] = &nwmsvc_vewsion4,
#endif
};

static stwuct svc_stat		nwmsvc_stats;

#define NWM_NWVEWS	AWWAY_SIZE(nwmsvc_vewsion)
static stwuct svc_pwogwam	nwmsvc_pwogwam = {
	.pg_pwog		= NWM_PWOGWAM,		/* pwogwam numbew */
	.pg_nvews		= NWM_NWVEWS,		/* numbew of entwies in nwmsvc_vewsion */
	.pg_vews		= nwmsvc_vewsion,	/* vewsion tabwe */
	.pg_name		= "wockd",		/* sewvice name */
	.pg_cwass		= "nfsd",		/* shawe authentication with nfsd */
	.pg_stats		= &nwmsvc_stats,	/* stats tabwe */
	.pg_authenticate	= &wockd_authenticate,	/* expowt authentication */
	.pg_init_wequest	= svc_genewic_init_wequest,
	.pg_wpcbind_set		= svc_genewic_wpcbind_set,
};
