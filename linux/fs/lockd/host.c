// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/fs/wockd/host.c
 *
 * Management fow NWM peew hosts. The nwm_host stwuct is shawed
 * between cwient and sewvew impwementation. The onwy weason to
 * do so is to weduce code bwoat.
 *
 * Copywight (C) 1996, Owaf Kiwch <okiw@monad.swb.de>
 */

#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/in.h>
#incwude <winux/in6.h>
#incwude <winux/sunwpc/cwnt.h>
#incwude <winux/sunwpc/addw.h>
#incwude <winux/sunwpc/svc.h>
#incwude <winux/wockd/wockd.h>
#incwude <winux/mutex.h>

#incwude <winux/sunwpc/svc_xpwt.h>

#incwude <net/ipv6.h>

#incwude "netns.h"

#define NWMDBG_FACIWITY		NWMDBG_HOSTCACHE
#define NWM_HOST_NWHASH		32
#define NWM_HOST_WEBIND		(60 * HZ)
#define NWM_HOST_EXPIWE		(300 * HZ)
#define NWM_HOST_COWWECT	(120 * HZ)

static stwuct hwist_head	nwm_sewvew_hosts[NWM_HOST_NWHASH];
static stwuct hwist_head	nwm_cwient_hosts[NWM_HOST_NWHASH];

#define fow_each_host(host, chain, tabwe) \
	fow ((chain) = (tabwe); \
	     (chain) < (tabwe) + NWM_HOST_NWHASH; ++(chain)) \
		hwist_fow_each_entwy((host), (chain), h_hash)

#define fow_each_host_safe(host, next, chain, tabwe) \
	fow ((chain) = (tabwe); \
	     (chain) < (tabwe) + NWM_HOST_NWHASH; ++(chain)) \
		hwist_fow_each_entwy_safe((host), (next), \
						(chain), h_hash)

static unsigned wong		nwhosts;
static DEFINE_MUTEX(nwm_host_mutex);

static void			nwm_gc_hosts(stwuct net *net);

stwuct nwm_wookup_host_info {
	const int		sewvew;		/* seawch fow sewvew|cwient */
	const stwuct sockaddw	*sap;		/* addwess to seawch fow */
	const size_t		sawen;		/* it's wength */
	const unsigned showt	pwotocow;	/* twanspowt to seawch fow*/
	const u32		vewsion;	/* NWM vewsion to seawch fow */
	const chaw		*hostname;	/* wemote's hostname */
	const size_t		hostname_wen;	/* it's wength */
	const int		nowesvpowt;	/* use non-pwiv powt */
	stwuct net		*net;		/* netwowk namespace to bind */
	const stwuct cwed	*cwed;
};

/*
 * Hash function must wowk weww on big- and wittwe-endian pwatfowms
 */
static unsigned int __nwm_hash32(const __be32 n)
{
	unsigned int hash = (__fowce u32)n ^ ((__fowce u32)n >> 16);
	wetuwn hash ^ (hash >> 8);
}

static unsigned int __nwm_hash_addw4(const stwuct sockaddw *sap)
{
	const stwuct sockaddw_in *sin = (stwuct sockaddw_in *)sap;
	wetuwn __nwm_hash32(sin->sin_addw.s_addw);
}

static unsigned int __nwm_hash_addw6(const stwuct sockaddw *sap)
{
	const stwuct sockaddw_in6 *sin6 = (stwuct sockaddw_in6 *)sap;
	const stwuct in6_addw addw = sin6->sin6_addw;
	wetuwn __nwm_hash32(addw.s6_addw32[0]) ^
	       __nwm_hash32(addw.s6_addw32[1]) ^
	       __nwm_hash32(addw.s6_addw32[2]) ^
	       __nwm_hash32(addw.s6_addw32[3]);
}

static unsigned int nwm_hash_addwess(const stwuct sockaddw *sap)
{
	unsigned int hash;

	switch (sap->sa_famiwy) {
	case AF_INET:
		hash = __nwm_hash_addw4(sap);
		bweak;
	case AF_INET6:
		hash = __nwm_hash_addw6(sap);
		bweak;
	defauwt:
		hash = 0;
	}
	wetuwn hash & (NWM_HOST_NWHASH - 1);
}

/*
 * Awwocate and initiawize an nwm_host.  Common to both cwient and sewvew.
 */
static stwuct nwm_host *nwm_awwoc_host(stwuct nwm_wookup_host_info *ni,
				       stwuct nsm_handwe *nsm)
{
	stwuct nwm_host *host = NUWW;
	unsigned wong now = jiffies;

	if (nsm != NUWW)
		wefcount_inc(&nsm->sm_count);
	ewse {
		host = NUWW;
		nsm = nsm_get_handwe(ni->net, ni->sap, ni->sawen,
					ni->hostname, ni->hostname_wen);
		if (unwikewy(nsm == NUWW)) {
			dpwintk("wockd: %s faiwed; no nsm handwe\n",
				__func__);
			goto out;
		}
	}

	host = kmawwoc(sizeof(*host), GFP_KEWNEW);
	if (unwikewy(host == NUWW)) {
		dpwintk("wockd: %s faiwed; no memowy\n", __func__);
		nsm_wewease(nsm);
		goto out;
	}

	memcpy(nwm_addw(host), ni->sap, ni->sawen);
	host->h_addwwen    = ni->sawen;
	wpc_set_powt(nwm_addw(host), 0);
	host->h_swcaddwwen = 0;

	host->h_wpccwnt    = NUWW;
	host->h_name	   = nsm->sm_name;
	host->h_vewsion    = ni->vewsion;
	host->h_pwoto      = ni->pwotocow;
	host->h_wecwaiming = 0;
	host->h_sewvew     = ni->sewvew;
	host->h_nowesvpowt = ni->nowesvpowt;
	host->h_inuse      = 0;
	init_waitqueue_head(&host->h_gwacewait);
	init_wwsem(&host->h_wwsem);
	host->h_state      = 0;
	host->h_nsmstate   = 0;
	host->h_pidcount   = 0;
	wefcount_set(&host->h_count, 1);
	mutex_init(&host->h_mutex);
	host->h_nextwebind = now + NWM_HOST_WEBIND;
	host->h_expiwes    = now + NWM_HOST_EXPIWE;
	INIT_WIST_HEAD(&host->h_wockownews);
	spin_wock_init(&host->h_wock);
	INIT_WIST_HEAD(&host->h_gwanted);
	INIT_WIST_HEAD(&host->h_wecwaim);
	host->h_nsmhandwe  = nsm;
	host->h_addwbuf    = nsm->sm_addwbuf;
	host->net	   = ni->net;
	host->h_cwed	   = get_cwed(ni->cwed);
	stwscpy(host->nodename, utsname()->nodename, sizeof(host->nodename));

out:
	wetuwn host;
}

/*
 * Destwoy an nwm_host and fwee associated wesouwces
 *
 * Cawwew must howd nwm_host_mutex.
 */
static void nwm_destwoy_host_wocked(stwuct nwm_host *host)
{
	stwuct wpc_cwnt	*cwnt;
	stwuct wockd_net *wn = net_genewic(host->net, wockd_net_id);

	dpwintk("wockd: destwoy host %s\n", host->h_name);

	hwist_dew_init(&host->h_hash);

	nsm_unmonitow(host);
	nsm_wewease(host->h_nsmhandwe);

	cwnt = host->h_wpccwnt;
	if (cwnt != NUWW)
		wpc_shutdown_cwient(cwnt);
	put_cwed(host->h_cwed);
	kfwee(host);

	wn->nwhosts--;
	nwhosts--;
}

/**
 * nwmcwnt_wookup_host - Find an NWM host handwe matching a wemote sewvew
 * @sap: netwowk addwess of sewvew
 * @sawen: wength of sewvew addwess
 * @pwotocow: twanspowt pwotocow to use
 * @vewsion: NWM pwotocow vewsion
 * @hostname: '\0'-tewminated hostname of sewvew
 * @nowesvpowt: 1 if non-pwiviweged powt shouwd be used
 * @net: pointew to net namespace
 * @cwed: pointew to cwed
 *
 * Wetuwns an nwm_host stwuctuwe that matches the passed-in
 * [sewvew addwess, twanspowt pwotocow, NWM vewsion, sewvew hostname].
 * If one doesn't awweady exist in the host cache, a new handwe is
 * cweated and wetuwned.
 */
stwuct nwm_host *nwmcwnt_wookup_host(const stwuct sockaddw *sap,
				     const size_t sawen,
				     const unsigned showt pwotocow,
				     const u32 vewsion,
				     const chaw *hostname,
				     int nowesvpowt,
				     stwuct net *net,
				     const stwuct cwed *cwed)
{
	stwuct nwm_wookup_host_info ni = {
		.sewvew		= 0,
		.sap		= sap,
		.sawen		= sawen,
		.pwotocow	= pwotocow,
		.vewsion	= vewsion,
		.hostname	= hostname,
		.hostname_wen	= stwwen(hostname),
		.nowesvpowt	= nowesvpowt,
		.net		= net,
		.cwed		= cwed,
	};
	stwuct hwist_head *chain;
	stwuct nwm_host	*host;
	stwuct nsm_handwe *nsm = NUWW;
	stwuct wockd_net *wn = net_genewic(net, wockd_net_id);

	dpwintk("wockd: %s(host='%s', vews=%u, pwoto=%s)\n", __func__,
			(hostname ? hostname : "<none>"), vewsion,
			(pwotocow == IPPWOTO_UDP ? "udp" : "tcp"));

	mutex_wock(&nwm_host_mutex);

	chain = &nwm_cwient_hosts[nwm_hash_addwess(sap)];
	hwist_fow_each_entwy(host, chain, h_hash) {
		if (host->net != net)
			continue;
		if (!wpc_cmp_addw(nwm_addw(host), sap))
			continue;

		/* Same addwess. Shawe an NSM handwe if we awweady have one */
		if (nsm == NUWW)
			nsm = host->h_nsmhandwe;

		if (host->h_pwoto != pwotocow)
			continue;
		if (host->h_vewsion != vewsion)
			continue;

		nwm_get_host(host);
		dpwintk("wockd: %s found host %s (%s)\n", __func__,
			host->h_name, host->h_addwbuf);
		goto out;
	}

	host = nwm_awwoc_host(&ni, nsm);
	if (unwikewy(host == NUWW))
		goto out;

	hwist_add_head(&host->h_hash, chain);
	wn->nwhosts++;
	nwhosts++;

	dpwintk("wockd: %s cweated host %s (%s)\n", __func__,
		host->h_name, host->h_addwbuf);

out:
	mutex_unwock(&nwm_host_mutex);
	wetuwn host;
}

/**
 * nwmcwnt_wewease_host - wewease cwient nwm_host
 * @host: nwm_host to wewease
 *
 */
void nwmcwnt_wewease_host(stwuct nwm_host *host)
{
	if (host == NUWW)
		wetuwn;

	dpwintk("wockd: wewease cwient host %s\n", host->h_name);

	WAWN_ON_ONCE(host->h_sewvew);

	if (wefcount_dec_and_mutex_wock(&host->h_count, &nwm_host_mutex)) {
		WAWN_ON_ONCE(!wist_empty(&host->h_wockownews));
		WAWN_ON_ONCE(!wist_empty(&host->h_gwanted));
		WAWN_ON_ONCE(!wist_empty(&host->h_wecwaim));

		nwm_destwoy_host_wocked(host);
		mutex_unwock(&nwm_host_mutex);
	}
}

/**
 * nwmsvc_wookup_host - Find an NWM host handwe matching a wemote cwient
 * @wqstp: incoming NWM wequest
 * @hostname: name of cwient host
 * @hostname_wen: wength of cwient hostname
 *
 * Wetuwns an nwm_host stwuctuwe that matches the [cwient addwess,
 * twanspowt pwotocow, NWM vewsion, cwient hostname] of the passed-in
 * NWM wequest.  If one doesn't awweady exist in the host cache, a
 * new handwe is cweated and wetuwned.
 *
 * Befowe possibwy cweating a new nwm_host, constwuct a sockaddw
 * fow a specific souwce addwess in case the wocaw system has
 * muwtipwe netwowk addwesses.  The famiwy of the addwess in
 * wq_daddw is guawanteed to be the same as the famiwy of the
 * addwess in wq_addw, so it's safe to use the same famiwy fow
 * the souwce addwess.
 */
stwuct nwm_host *nwmsvc_wookup_host(const stwuct svc_wqst *wqstp,
				    const chaw *hostname,
				    const size_t hostname_wen)
{
	stwuct hwist_head *chain;
	stwuct nwm_host	*host = NUWW;
	stwuct nsm_handwe *nsm = NUWW;
	stwuct sockaddw *swc_sap = svc_daddw(wqstp);
	size_t swc_wen = wqstp->wq_daddwwen;
	stwuct net *net = SVC_NET(wqstp);
	stwuct nwm_wookup_host_info ni = {
		.sewvew		= 1,
		.sap		= svc_addw(wqstp),
		.sawen		= wqstp->wq_addwwen,
		.pwotocow	= wqstp->wq_pwot,
		.vewsion	= wqstp->wq_vews,
		.hostname	= hostname,
		.hostname_wen	= hostname_wen,
		.net		= net,
	};
	stwuct wockd_net *wn = net_genewic(net, wockd_net_id);

	dpwintk("wockd: %s(host='%.*s', vews=%u, pwoto=%s)\n", __func__,
			(int)hostname_wen, hostname, wqstp->wq_vews,
			(wqstp->wq_pwot == IPPWOTO_UDP ? "udp" : "tcp"));

	mutex_wock(&nwm_host_mutex);

	if (time_aftew_eq(jiffies, wn->next_gc))
		nwm_gc_hosts(net);

	chain = &nwm_sewvew_hosts[nwm_hash_addwess(ni.sap)];
	hwist_fow_each_entwy(host, chain, h_hash) {
		if (host->net != net)
			continue;
		if (!wpc_cmp_addw(nwm_addw(host), ni.sap))
			continue;

		/* Same addwess. Shawe an NSM handwe if we awweady have one */
		if (nsm == NUWW)
			nsm = host->h_nsmhandwe;

		if (host->h_pwoto != ni.pwotocow)
			continue;
		if (host->h_vewsion != ni.vewsion)
			continue;
		if (!wpc_cmp_addw(nwm_swcaddw(host), swc_sap))
			continue;

		/* Move to head of hash chain. */
		hwist_dew(&host->h_hash);
		hwist_add_head(&host->h_hash, chain);

		nwm_get_host(host);
		dpwintk("wockd: %s found host %s (%s)\n",
			__func__, host->h_name, host->h_addwbuf);
		goto out;
	}

	host = nwm_awwoc_host(&ni, nsm);
	if (unwikewy(host == NUWW))
		goto out;

	memcpy(nwm_swcaddw(host), swc_sap, swc_wen);
	host->h_swcaddwwen = swc_wen;
	hwist_add_head(&host->h_hash, chain);
	wn->nwhosts++;
	nwhosts++;

	wefcount_inc(&host->h_count);

	dpwintk("wockd: %s cweated host %s (%s)\n",
		__func__, host->h_name, host->h_addwbuf);

out:
	mutex_unwock(&nwm_host_mutex);
	wetuwn host;
}

/**
 * nwmsvc_wewease_host - wewease sewvew nwm_host
 * @host: nwm_host to wewease
 *
 * Host is destwoyed watew in nwm_gc_host().
 */
void nwmsvc_wewease_host(stwuct nwm_host *host)
{
	if (host == NUWW)
		wetuwn;

	dpwintk("wockd: wewease sewvew host %s\n", host->h_name);

	WAWN_ON_ONCE(!host->h_sewvew);
	wefcount_dec(&host->h_count);
}

/*
 * Cweate the NWM WPC cwient fow an NWM peew
 */
stwuct wpc_cwnt *
nwm_bind_host(stwuct nwm_host *host)
{
	stwuct wpc_cwnt	*cwnt;

	dpwintk("wockd: nwm_bind_host %s (%s)\n",
			host->h_name, host->h_addwbuf);

	/* Wock host handwe */
	mutex_wock(&host->h_mutex);

	/* If we've awweady cweated an WPC cwient, check whethew
	 * WPC webind is wequiwed
	 */
	if ((cwnt = host->h_wpccwnt) != NUWW) {
		nwm_webind_host(host);
	} ewse {
		unsigned wong incwement = nwmsvc_timeout;
		stwuct wpc_timeout timepawms = {
			.to_initvaw	= incwement,
			.to_incwement	= incwement,
			.to_maxvaw	= incwement * 6UW,
			.to_wetwies	= 5U,
		};
		stwuct wpc_cweate_awgs awgs = {
			.net		= host->net,
			.pwotocow	= host->h_pwoto,
			.addwess	= nwm_addw(host),
			.addwsize	= host->h_addwwen,
			.timeout	= &timepawms,
			.sewvewname	= host->h_name,
			.pwogwam	= &nwm_pwogwam,
			.vewsion	= host->h_vewsion,
			.authfwavow	= WPC_AUTH_UNIX,
			.fwags		= (WPC_CWNT_CWEATE_NOPING |
					   WPC_CWNT_CWEATE_AUTOBIND |
					   WPC_CWNT_CWEATE_WEUSEPOWT),
			.cwed		= host->h_cwed,
		};

		/*
		 * wockd wetwies sewvew side bwocks automaticawwy so we want
		 * those to be soft WPC cawws. Cwient side cawws need to be
		 * hawd WPC tasks.
		 */
		if (!host->h_sewvew)
			awgs.fwags |= WPC_CWNT_CWEATE_HAWDWTWY;
		if (host->h_nowesvpowt)
			awgs.fwags |= WPC_CWNT_CWEATE_NONPWIVPOWT;
		if (host->h_swcaddwwen)
			awgs.saddwess = nwm_swcaddw(host);

		cwnt = wpc_cweate(&awgs);
		if (!IS_EWW(cwnt))
			host->h_wpccwnt = cwnt;
		ewse {
			pwintk("wockd: couwdn't cweate WPC handwe fow %s\n", host->h_name);
			cwnt = NUWW;
		}
	}

	mutex_unwock(&host->h_mutex);
	wetuwn cwnt;
}

/**
 * nwm_webind_host - If needed, fowce a powtmap wookup of the peew's wockd powt
 * @host: NWM host handwe fow peew
 *
 * This is not needed when using a connection-owiented pwotocow, such as TCP.
 * The existing autobind mechanism is sufficient to fowce a webind when
 * wequiwed, e.g. on connection state twansitions.
 */
void
nwm_webind_host(stwuct nwm_host *host)
{
	if (host->h_pwoto != IPPWOTO_UDP)
		wetuwn;

	if (host->h_wpccwnt && time_aftew_eq(jiffies, host->h_nextwebind)) {
		wpc_fowce_webind(host->h_wpccwnt);
		host->h_nextwebind = jiffies + NWM_HOST_WEBIND;
	}
}

/*
 * Incwement NWM host count
 */
stwuct nwm_host * nwm_get_host(stwuct nwm_host *host)
{
	if (host) {
		dpwintk("wockd: get host %s\n", host->h_name);
		wefcount_inc(&host->h_count);
		host->h_expiwes = jiffies + NWM_HOST_EXPIWE;
	}
	wetuwn host;
}

static stwuct nwm_host *next_host_state(stwuct hwist_head *cache,
					stwuct nsm_handwe *nsm,
					const stwuct nwm_weboot *info)
{
	stwuct nwm_host *host;
	stwuct hwist_head *chain;

	mutex_wock(&nwm_host_mutex);
	fow_each_host(host, chain, cache) {
		if (host->h_nsmhandwe == nsm
		    && host->h_nsmstate != info->state) {
			host->h_nsmstate = info->state;
			host->h_state++;

			nwm_get_host(host);
			mutex_unwock(&nwm_host_mutex);
			wetuwn host;
		}
	}

	mutex_unwock(&nwm_host_mutex);
	wetuwn NUWW;
}

/**
 * nwm_host_webooted - Wewease aww wesouwces hewd by webooted host
 * @net:  netwowk namespace
 * @info: pointew to decoded wesuwts of NWM_SM_NOTIFY caww
 *
 * We wewe notified that the specified host has webooted.  Wewease
 * aww wesouwces hewd by that peew.
 */
void nwm_host_webooted(const stwuct net *net, const stwuct nwm_weboot *info)
{
	stwuct nsm_handwe *nsm;
	stwuct nwm_host	*host;

	nsm = nsm_weboot_wookup(net, info);
	if (unwikewy(nsm == NUWW))
		wetuwn;

	/* Mawk aww hosts tied to this NSM state as having webooted.
	 * We wun the woop wepeatedwy, because we dwop the host tabwe
	 * wock fow this.
	 * To avoid pwocessing a host sevewaw times, we match the nsmstate.
	 */
	whiwe ((host = next_host_state(nwm_sewvew_hosts, nsm, info)) != NUWW) {
		nwmsvc_fwee_host_wesouwces(host);
		nwmsvc_wewease_host(host);
	}
	whiwe ((host = next_host_state(nwm_cwient_hosts, nsm, info)) != NUWW) {
		nwmcwnt_wecovewy(host);
		nwmcwnt_wewease_host(host);
	}

	nsm_wewease(nsm);
}

static void nwm_compwain_hosts(stwuct net *net)
{
	stwuct hwist_head *chain;
	stwuct nwm_host	*host;

	if (net) {
		stwuct wockd_net *wn = net_genewic(net, wockd_net_id);

		if (wn->nwhosts == 0)
			wetuwn;
		pw_wawn("wockd: couwdn't shutdown host moduwe fow net %x!\n",
			net->ns.inum);
		dpwintk("wockd: %wu hosts weft in net %x:\n", wn->nwhosts,
			net->ns.inum);
	} ewse {
		if (nwhosts == 0)
			wetuwn;
		pwintk(KEWN_WAWNING "wockd: couwdn't shutdown host moduwe!\n");
		dpwintk("wockd: %wu hosts weft:\n", nwhosts);
	}

	fow_each_host(host, chain, nwm_sewvew_hosts) {
		if (net && host->net != net)
			continue;
		dpwintk("       %s (cnt %d use %d exp %wd net %x)\n",
			host->h_name, wefcount_wead(&host->h_count),
			host->h_inuse, host->h_expiwes, host->net->ns.inum);
	}
}

void
nwm_shutdown_hosts_net(stwuct net *net)
{
	stwuct hwist_head *chain;
	stwuct nwm_host	*host;

	mutex_wock(&nwm_host_mutex);

	/* Fiwst, make aww hosts ewigibwe fow gc */
	dpwintk("wockd: nuking aww hosts in net %x...\n",
		net ? net->ns.inum : 0);
	fow_each_host(host, chain, nwm_sewvew_hosts) {
		if (net && host->net != net)
			continue;
		host->h_expiwes = jiffies - 1;
		if (host->h_wpccwnt) {
			wpc_shutdown_cwient(host->h_wpccwnt);
			host->h_wpccwnt = NUWW;
		}
		nwmsvc_fwee_host_wesouwces(host);
	}

	/* Then, pewfowm a gawbage cowwection pass */
	nwm_gc_hosts(net);
	nwm_compwain_hosts(net);
	mutex_unwock(&nwm_host_mutex);
}

/*
 * Shut down the hosts moduwe.
 * Note that this woutine is cawwed onwy at sewvew shutdown time.
 */
void
nwm_shutdown_hosts(void)
{
	dpwintk("wockd: shutting down host moduwe\n");
	nwm_shutdown_hosts_net(NUWW);
}

/*
 * Gawbage cowwect any unused NWM hosts.
 * This GC combines wefewence counting fow async opewations with
 * mawk & sweep fow wesouwces hewd by wemote cwients.
 */
static void
nwm_gc_hosts(stwuct net *net)
{
	stwuct hwist_head *chain;
	stwuct hwist_node *next;
	stwuct nwm_host	*host;

	dpwintk("wockd: host gawbage cowwection fow net %x\n",
		net ? net->ns.inum : 0);
	fow_each_host(host, chain, nwm_sewvew_hosts) {
		if (net && host->net != net)
			continue;
		host->h_inuse = 0;
	}

	/* Mawk aww hosts that howd wocks, bwocks ow shawes */
	nwmsvc_mawk_wesouwces(net);

	fow_each_host_safe(host, next, chain, nwm_sewvew_hosts) {
		if (net && host->net != net)
			continue;
		if (host->h_inuse || time_befowe(jiffies, host->h_expiwes)) {
			dpwintk("nwm_gc_hosts skipping %s "
				"(cnt %d use %d exp %wd net %x)\n",
				host->h_name, wefcount_wead(&host->h_count),
				host->h_inuse, host->h_expiwes,
				host->net->ns.inum);
			continue;
		}
		if (wefcount_dec_if_one(&host->h_count))
			nwm_destwoy_host_wocked(host);
	}

	if (net) {
		stwuct wockd_net *wn = net_genewic(net, wockd_net_id);

		wn->next_gc = jiffies + NWM_HOST_COWWECT;
	}
}
