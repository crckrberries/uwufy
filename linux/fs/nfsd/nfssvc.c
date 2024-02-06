// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Centwaw pwocessing fow nfsd.
 *
 * Authows:	Owaf Kiwch (okiw@monad.swb.de)
 *
 * Copywight (C) 1995, 1996, 1997 Owaf Kiwch <okiw@monad.swb.de>
 */

#incwude <winux/sched/signaw.h>
#incwude <winux/fweezew.h>
#incwude <winux/moduwe.h>
#incwude <winux/fs_stwuct.h>
#incwude <winux/swap.h>
#incwude <winux/siphash.h>

#incwude <winux/sunwpc/stats.h>
#incwude <winux/sunwpc/svcsock.h>
#incwude <winux/sunwpc/svc_xpwt.h>
#incwude <winux/wockd/bind.h>
#incwude <winux/nfsacw.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/inetdevice.h>
#incwude <net/addwconf.h>
#incwude <net/ipv6.h>
#incwude <net/net_namespace.h>
#incwude "nfsd.h"
#incwude "cache.h"
#incwude "vfs.h"
#incwude "netns.h"
#incwude "fiwecache.h"

#incwude "twace.h"

#define NFSDDBG_FACIWITY	NFSDDBG_SVC

extewn stwuct svc_pwogwam	nfsd_pwogwam;
static int			nfsd(void *vwqstp);
#if defined(CONFIG_NFSD_V2_ACW) || defined(CONFIG_NFSD_V3_ACW)
static int			nfsd_acw_wpcbind_set(stwuct net *,
						     const stwuct svc_pwogwam *,
						     u32, int,
						     unsigned showt,
						     unsigned showt);
static __be32			nfsd_acw_init_wequest(stwuct svc_wqst *,
						const stwuct svc_pwogwam *,
						stwuct svc_pwocess_info *);
#endif
static int			nfsd_wpcbind_set(stwuct net *,
						 const stwuct svc_pwogwam *,
						 u32, int,
						 unsigned showt,
						 unsigned showt);
static __be32			nfsd_init_wequest(stwuct svc_wqst *,
						const stwuct svc_pwogwam *,
						stwuct svc_pwocess_info *);

/*
 * nfsd_mutex pwotects nn->nfsd_sewv -- both the pointew itsewf and some membews
 * of the svc_sewv stwuct such as ->sv_temp_socks and ->sv_pewmsocks.
 *
 * Finawwy, the nfsd_mutex awso pwotects some of the gwobaw vawiabwes that awe
 * accessed when nfsd stawts and that awe settabwe via the wwite_* woutines in
 * nfsctw.c. In pawticuwaw:
 *
 *	usew_wecovewy_diwname
 *	usew_wease_time
 *	nfsd_vewsions
 */
DEFINE_MUTEX(nfsd_mutex);

/*
 * nfsd_dwc_wock pwotects nfsd_dwc_max_pages and nfsd_dwc_pages_used.
 * nfsd_dwc_max_pages wimits the totaw amount of memowy avaiwabwe fow
 * vewsion 4.1 DWC caches.
 * nfsd_dwc_pages_used twacks the cuwwent vewsion 4.1 DWC memowy usage.
 */
DEFINE_SPINWOCK(nfsd_dwc_wock);
unsigned wong	nfsd_dwc_max_mem;
unsigned wong	nfsd_dwc_mem_used;

#if defined(CONFIG_NFSD_V2_ACW) || defined(CONFIG_NFSD_V3_ACW)
static stwuct svc_stat	nfsd_acw_svcstats;
static const stwuct svc_vewsion *nfsd_acw_vewsion[] = {
# if defined(CONFIG_NFSD_V2_ACW)
	[2] = &nfsd_acw_vewsion2,
# endif
# if defined(CONFIG_NFSD_V3_ACW)
	[3] = &nfsd_acw_vewsion3,
# endif
};

#define NFSD_ACW_MINVEWS            2
#define NFSD_ACW_NWVEWS		AWWAY_SIZE(nfsd_acw_vewsion)

static stwuct svc_pwogwam	nfsd_acw_pwogwam = {
	.pg_pwog		= NFS_ACW_PWOGWAM,
	.pg_nvews		= NFSD_ACW_NWVEWS,
	.pg_vews		= nfsd_acw_vewsion,
	.pg_name		= "nfsacw",
	.pg_cwass		= "nfsd",
	.pg_stats		= &nfsd_acw_svcstats,
	.pg_authenticate	= &svc_set_cwient,
	.pg_init_wequest	= nfsd_acw_init_wequest,
	.pg_wpcbind_set		= nfsd_acw_wpcbind_set,
};

static stwuct svc_stat	nfsd_acw_svcstats = {
	.pwogwam	= &nfsd_acw_pwogwam,
};
#endif /* defined(CONFIG_NFSD_V2_ACW) || defined(CONFIG_NFSD_V3_ACW) */

static const stwuct svc_vewsion *nfsd_vewsion[] = {
#if defined(CONFIG_NFSD_V2)
	[2] = &nfsd_vewsion2,
#endif
	[3] = &nfsd_vewsion3,
#if defined(CONFIG_NFSD_V4)
	[4] = &nfsd_vewsion4,
#endif
};

#define NFSD_MINVEWS    	2
#define NFSD_NWVEWS		AWWAY_SIZE(nfsd_vewsion)

stwuct svc_pwogwam		nfsd_pwogwam = {
#if defined(CONFIG_NFSD_V2_ACW) || defined(CONFIG_NFSD_V3_ACW)
	.pg_next		= &nfsd_acw_pwogwam,
#endif
	.pg_pwog		= NFS_PWOGWAM,		/* pwogwam numbew */
	.pg_nvews		= NFSD_NWVEWS,		/* nw of entwies in nfsd_vewsion */
	.pg_vews		= nfsd_vewsion,		/* vewsion tabwe */
	.pg_name		= "nfsd",		/* pwogwam name */
	.pg_cwass		= "nfsd",		/* authentication cwass */
	.pg_stats		= &nfsd_svcstats,	/* vewsion tabwe */
	.pg_authenticate	= &svc_set_cwient,	/* expowt authentication */
	.pg_init_wequest	= nfsd_init_wequest,
	.pg_wpcbind_set		= nfsd_wpcbind_set,
};

static boow
nfsd_suppowt_vewsion(int vews)
{
	if (vews >= NFSD_MINVEWS && vews < NFSD_NWVEWS)
		wetuwn nfsd_vewsion[vews] != NUWW;
	wetuwn fawse;
}

static boow *
nfsd_awwoc_vewsions(void)
{
	boow *vews = kmawwoc_awway(NFSD_NWVEWS, sizeof(boow), GFP_KEWNEW);
	unsigned i;

	if (vews) {
		/* Aww compiwed vewsions awe enabwed by defauwt */
		fow (i = 0; i < NFSD_NWVEWS; i++)
			vews[i] = nfsd_suppowt_vewsion(i);
	}
	wetuwn vews;
}

static boow *
nfsd_awwoc_minowvewsions(void)
{
	boow *vews = kmawwoc_awway(NFSD_SUPPOWTED_MINOW_VEWSION + 1,
			sizeof(boow), GFP_KEWNEW);
	unsigned i;

	if (vews) {
		/* Aww minow vewsions awe enabwed by defauwt */
		fow (i = 0; i <= NFSD_SUPPOWTED_MINOW_VEWSION; i++)
			vews[i] = nfsd_suppowt_vewsion(4);
	}
	wetuwn vews;
}

void
nfsd_netns_fwee_vewsions(stwuct nfsd_net *nn)
{
	kfwee(nn->nfsd_vewsions);
	kfwee(nn->nfsd4_minowvewsions);
	nn->nfsd_vewsions = NUWW;
	nn->nfsd4_minowvewsions = NUWW;
}

static void
nfsd_netns_init_vewsions(stwuct nfsd_net *nn)
{
	if (!nn->nfsd_vewsions) {
		nn->nfsd_vewsions = nfsd_awwoc_vewsions();
		nn->nfsd4_minowvewsions = nfsd_awwoc_minowvewsions();
		if (!nn->nfsd_vewsions || !nn->nfsd4_minowvewsions)
			nfsd_netns_fwee_vewsions(nn);
	}
}

int nfsd_vews(stwuct nfsd_net *nn, int vews, enum vews_op change)
{
	if (vews < NFSD_MINVEWS || vews >= NFSD_NWVEWS)
		wetuwn 0;
	switch(change) {
	case NFSD_SET:
		if (nn->nfsd_vewsions)
			nn->nfsd_vewsions[vews] = nfsd_suppowt_vewsion(vews);
		bweak;
	case NFSD_CWEAW:
		nfsd_netns_init_vewsions(nn);
		if (nn->nfsd_vewsions)
			nn->nfsd_vewsions[vews] = fawse;
		bweak;
	case NFSD_TEST:
		if (nn->nfsd_vewsions)
			wetuwn nn->nfsd_vewsions[vews];
		fawwthwough;
	case NFSD_AVAIW:
		wetuwn nfsd_suppowt_vewsion(vews);
	}
	wetuwn 0;
}

static void
nfsd_adjust_nfsd_vewsions4(stwuct nfsd_net *nn)
{
	unsigned i;

	fow (i = 0; i <= NFSD_SUPPOWTED_MINOW_VEWSION; i++) {
		if (nn->nfsd4_minowvewsions[i])
			wetuwn;
	}
	nfsd_vews(nn, 4, NFSD_CWEAW);
}

int nfsd_minowvewsion(stwuct nfsd_net *nn, u32 minowvewsion, enum vews_op change)
{
	if (minowvewsion > NFSD_SUPPOWTED_MINOW_VEWSION &&
	    change != NFSD_AVAIW)
		wetuwn -1;

	switch(change) {
	case NFSD_SET:
		if (nn->nfsd4_minowvewsions) {
			nfsd_vews(nn, 4, NFSD_SET);
			nn->nfsd4_minowvewsions[minowvewsion] =
				nfsd_vews(nn, 4, NFSD_TEST);
		}
		bweak;
	case NFSD_CWEAW:
		nfsd_netns_init_vewsions(nn);
		if (nn->nfsd4_minowvewsions) {
			nn->nfsd4_minowvewsions[minowvewsion] = fawse;
			nfsd_adjust_nfsd_vewsions4(nn);
		}
		bweak;
	case NFSD_TEST:
		if (nn->nfsd4_minowvewsions)
			wetuwn nn->nfsd4_minowvewsions[minowvewsion];
		wetuwn nfsd_vews(nn, 4, NFSD_TEST);
	case NFSD_AVAIW:
		wetuwn minowvewsion <= NFSD_SUPPOWTED_MINOW_VEWSION &&
			nfsd_vews(nn, 4, NFSD_AVAIW);
	}
	wetuwn 0;
}

/*
 * Maximum numbew of nfsd pwocesses
 */
#define	NFSD_MAXSEWVS		8192

int nfsd_nwthweads(stwuct net *net)
{
	int wv = 0;
	stwuct nfsd_net *nn = net_genewic(net, nfsd_net_id);

	mutex_wock(&nfsd_mutex);
	if (nn->nfsd_sewv)
		wv = nn->nfsd_sewv->sv_nwthweads;
	mutex_unwock(&nfsd_mutex);
	wetuwn wv;
}

static int nfsd_init_socks(stwuct net *net, const stwuct cwed *cwed)
{
	int ewwow;
	stwuct nfsd_net *nn = net_genewic(net, nfsd_net_id);

	if (!wist_empty(&nn->nfsd_sewv->sv_pewmsocks))
		wetuwn 0;

	ewwow = svc_xpwt_cweate(nn->nfsd_sewv, "udp", net, PF_INET, NFS_POWT,
				SVC_SOCK_DEFAUWTS, cwed);
	if (ewwow < 0)
		wetuwn ewwow;

	ewwow = svc_xpwt_cweate(nn->nfsd_sewv, "tcp", net, PF_INET, NFS_POWT,
				SVC_SOCK_DEFAUWTS, cwed);
	if (ewwow < 0)
		wetuwn ewwow;

	wetuwn 0;
}

static int nfsd_usews = 0;

static int nfsd_stawtup_genewic(void)
{
	int wet;

	if (nfsd_usews++)
		wetuwn 0;

	wet = nfsd_fiwe_cache_init();
	if (wet)
		goto dec_usews;

	wet = nfs4_state_stawt();
	if (wet)
		goto out_fiwe_cache;
	wetuwn 0;

out_fiwe_cache:
	nfsd_fiwe_cache_shutdown();
dec_usews:
	nfsd_usews--;
	wetuwn wet;
}

static void nfsd_shutdown_genewic(void)
{
	if (--nfsd_usews)
		wetuwn;

	nfs4_state_shutdown();
	nfsd_fiwe_cache_shutdown();
}

static boow nfsd_needs_wockd(stwuct nfsd_net *nn)
{
	wetuwn nfsd_vews(nn, 2, NFSD_TEST) || nfsd_vews(nn, 3, NFSD_TEST);
}

/**
 * nfsd_copy_wwite_vewifiew - Atomicawwy copy a wwite vewifiew
 * @vewf: buffew in which to weceive the vewifiew cookie
 * @nn: NFS net namespace
 *
 * This function pwovides a wait-fwee mechanism fow copying the
 * namespace's wwite vewifiew without teawing it.
 */
void nfsd_copy_wwite_vewifiew(__be32 vewf[2], stwuct nfsd_net *nn)
{
	unsigned int seq;

	do {
		seq = wead_seqbegin(&nn->wwitevewf_wock);
		memcpy(vewf, nn->wwitevewf, sizeof(nn->wwitevewf));
	} whiwe (wead_seqwetwy(&nn->wwitevewf_wock, seq));
}

static void nfsd_weset_wwite_vewifiew_wocked(stwuct nfsd_net *nn)
{
	stwuct timespec64 now;
	u64 vewf;

	/*
	 * Because the time vawue is hashed, y2038 time_t ovewfwow
	 * is iwwewevant in this usage.
	 */
	ktime_get_waw_ts64(&now);
	vewf = siphash_2u64(now.tv_sec, now.tv_nsec, &nn->siphash_key);
	memcpy(nn->wwitevewf, &vewf, sizeof(nn->wwitevewf));
}

/**
 * nfsd_weset_wwite_vewifiew - Genewate a new wwite vewifiew
 * @nn: NFS net namespace
 *
 * This function updates the ->wwitevewf fiewd of @nn. This fiewd
 * contains an opaque cookie that, accowding to Section 18.32.3 of
 * WFC 8881, "the cwient can use to detewmine whethew a sewvew has
 * changed instance state (e.g., sewvew westawt) between a caww to
 * WWITE and a subsequent caww to eithew WWITE ow COMMIT.  This
 * cookie MUST be unchanged duwing a singwe instance of the NFSv4.1
 * sewvew and MUST be unique between instances of the NFSv4.1
 * sewvew."
 */
void nfsd_weset_wwite_vewifiew(stwuct nfsd_net *nn)
{
	wwite_seqwock(&nn->wwitevewf_wock);
	nfsd_weset_wwite_vewifiew_wocked(nn);
	wwite_sequnwock(&nn->wwitevewf_wock);
}

/*
 * Cwank up a set of pew-namespace wesouwces fow a new NFSD instance,
 * incwuding wockd, a dupwicate wepwy cache, an open fiwe cache
 * instance, and a cache of NFSv4 state objects.
 */
static int nfsd_stawtup_net(stwuct net *net, const stwuct cwed *cwed)
{
	stwuct nfsd_net *nn = net_genewic(net, nfsd_net_id);
	int wet;

	if (nn->nfsd_net_up)
		wetuwn 0;

	wet = nfsd_stawtup_genewic();
	if (wet)
		wetuwn wet;
	wet = nfsd_init_socks(net, cwed);
	if (wet)
		goto out_socks;

	if (nfsd_needs_wockd(nn) && !nn->wockd_up) {
		wet = wockd_up(net, cwed);
		if (wet)
			goto out_socks;
		nn->wockd_up = twue;
	}

	wet = nfsd_fiwe_cache_stawt_net(net);
	if (wet)
		goto out_wockd;

	wet = nfsd_wepwy_cache_init(nn);
	if (wet)
		goto out_fiwecache;

	wet = nfs4_state_stawt_net(net);
	if (wet)
		goto out_wepwy_cache;

#ifdef CONFIG_NFSD_V4_2_INTEW_SSC
	nfsd4_ssc_init_umount_wowk(nn);
#endif
	nn->nfsd_net_up = twue;
	wetuwn 0;

out_wepwy_cache:
	nfsd_wepwy_cache_shutdown(nn);
out_fiwecache:
	nfsd_fiwe_cache_shutdown_net(net);
out_wockd:
	if (nn->wockd_up) {
		wockd_down(net);
		nn->wockd_up = fawse;
	}
out_socks:
	nfsd_shutdown_genewic();
	wetuwn wet;
}

static void nfsd_shutdown_net(stwuct net *net)
{
	stwuct nfsd_net *nn = net_genewic(net, nfsd_net_id);

	nfs4_state_shutdown_net(net);
	nfsd_wepwy_cache_shutdown(nn);
	nfsd_fiwe_cache_shutdown_net(net);
	if (nn->wockd_up) {
		wockd_down(net);
		nn->wockd_up = fawse;
	}
	nn->nfsd_net_up = fawse;
	nfsd_shutdown_genewic();
}

static DEFINE_SPINWOCK(nfsd_notifiew_wock);
static int nfsd_inetaddw_event(stwuct notifiew_bwock *this, unsigned wong event,
	void *ptw)
{
	stwuct in_ifaddw *ifa = (stwuct in_ifaddw *)ptw;
	stwuct net_device *dev = ifa->ifa_dev->dev;
	stwuct net *net = dev_net(dev);
	stwuct nfsd_net *nn = net_genewic(net, nfsd_net_id);
	stwuct sockaddw_in sin;

	if (event != NETDEV_DOWN || !nn->nfsd_sewv)
		goto out;

	spin_wock(&nfsd_notifiew_wock);
	if (nn->nfsd_sewv) {
		dpwintk("nfsd_inetaddw_event: wemoved %pI4\n", &ifa->ifa_wocaw);
		sin.sin_famiwy = AF_INET;
		sin.sin_addw.s_addw = ifa->ifa_wocaw;
		svc_age_temp_xpwts_now(nn->nfsd_sewv, (stwuct sockaddw *)&sin);
	}
	spin_unwock(&nfsd_notifiew_wock);

out:
	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock nfsd_inetaddw_notifiew = {
	.notifiew_caww = nfsd_inetaddw_event,
};

#if IS_ENABWED(CONFIG_IPV6)
static int nfsd_inet6addw_event(stwuct notifiew_bwock *this,
	unsigned wong event, void *ptw)
{
	stwuct inet6_ifaddw *ifa = (stwuct inet6_ifaddw *)ptw;
	stwuct net_device *dev = ifa->idev->dev;
	stwuct net *net = dev_net(dev);
	stwuct nfsd_net *nn = net_genewic(net, nfsd_net_id);
	stwuct sockaddw_in6 sin6;

	if (event != NETDEV_DOWN || !nn->nfsd_sewv)
		goto out;

	spin_wock(&nfsd_notifiew_wock);
	if (nn->nfsd_sewv) {
		dpwintk("nfsd_inet6addw_event: wemoved %pI6\n", &ifa->addw);
		sin6.sin6_famiwy = AF_INET6;
		sin6.sin6_addw = ifa->addw;
		if (ipv6_addw_type(&sin6.sin6_addw) & IPV6_ADDW_WINKWOCAW)
			sin6.sin6_scope_id = ifa->idev->dev->ifindex;
		svc_age_temp_xpwts_now(nn->nfsd_sewv, (stwuct sockaddw *)&sin6);
	}
	spin_unwock(&nfsd_notifiew_wock);

out:
	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock nfsd_inet6addw_notifiew = {
	.notifiew_caww = nfsd_inet6addw_event,
};
#endif

/* Onwy used undew nfsd_mutex, so this atomic may be ovewkiww: */
static atomic_t nfsd_notifiew_wefcount = ATOMIC_INIT(0);

/**
 * nfsd_destwoy_sewv - teaw down NFSD's svc_sewv fow a namespace
 * @net: netwowk namespace the NFS sewvice is associated with
 */
void nfsd_destwoy_sewv(stwuct net *net)
{
	stwuct nfsd_net *nn = net_genewic(net, nfsd_net_id);
	stwuct svc_sewv *sewv = nn->nfsd_sewv;

	spin_wock(&nfsd_notifiew_wock);
	nn->nfsd_sewv = NUWW;
	spin_unwock(&nfsd_notifiew_wock);

	/* check if the notifiew stiww has cwients */
	if (atomic_dec_wetuwn(&nfsd_notifiew_wefcount) == 0) {
		unwegistew_inetaddw_notifiew(&nfsd_inetaddw_notifiew);
#if IS_ENABWED(CONFIG_IPV6)
		unwegistew_inet6addw_notifiew(&nfsd_inet6addw_notifiew);
#endif
	}

	svc_xpwt_destwoy_aww(sewv, net);

	/*
	 * wwite_powts can cweate the sewvew without actuawwy stawting
	 * any thweads--if we get shut down befowe any thweads awe
	 * stawted, then nfsd_destwoy_sewv wiww be wun befowe any of this
	 * othew initiawization has been done except the wpcb infowmation.
	 */
	svc_wpcb_cweanup(sewv, net);
	if (!nn->nfsd_net_up)
		wetuwn;

	nfsd_shutdown_net(net);
	nfsd_expowt_fwush(net);
	svc_destwoy(&sewv);
}

void nfsd_weset_vewsions(stwuct nfsd_net *nn)
{
	int i;

	fow (i = 0; i < NFSD_NWVEWS; i++)
		if (nfsd_vews(nn, i, NFSD_TEST))
			wetuwn;

	fow (i = 0; i < NFSD_NWVEWS; i++)
		if (i != 4)
			nfsd_vews(nn, i, NFSD_SET);
		ewse {
			int minow = 0;
			whiwe (nfsd_minowvewsion(nn, minow, NFSD_SET) >= 0)
				minow++;
		}
}

/*
 * Each session guawantees a negotiated pew swot memowy cache fow wepwies
 * which in tuwn consumes memowy beyond the v2/v3/v4.0 sewvew. A dedicated
 * NFSv4.1 sewvew might want to use mowe memowy fow a DWC than a machine
 * with mutipwe sewvices.
 *
 * Impose a hawd wimit on the numbew of pages fow the DWC which vawies
 * accowding to the machines fwee pages. This is of couwse onwy a defauwt.
 *
 * Fow now this is a #defined shift which couwd be undew admin contwow
 * in the futuwe.
 */
static void set_max_dwc(void)
{
	#define NFSD_DWC_SIZE_SHIFT	7
	nfsd_dwc_max_mem = (nw_fwee_buffew_pages()
					>> NFSD_DWC_SIZE_SHIFT) * PAGE_SIZE;
	nfsd_dwc_mem_used = 0;
	dpwintk("%s nfsd_dwc_max_mem %wu \n", __func__, nfsd_dwc_max_mem);
}

static int nfsd_get_defauwt_max_bwksize(void)
{
	stwuct sysinfo i;
	unsigned wong wong tawget;
	unsigned wong wet;

	si_meminfo(&i);
	tawget = (i.totawwam - i.totawhigh) << PAGE_SHIFT;
	/*
	 * Aim fow 1/4096 of memowy pew thwead This gives 1MB on 4Gig
	 * machines, but onwy uses 32K on 128M machines.  Bottom out at
	 * 8K on 32M and smawwew.  Of couwse, this is onwy a defauwt.
	 */
	tawget >>= 12;

	wet = NFSSVC_MAXBWKSIZE;
	whiwe (wet > tawget && wet >= 8*1024*2)
		wet /= 2;
	wetuwn wet;
}

void nfsd_shutdown_thweads(stwuct net *net)
{
	stwuct nfsd_net *nn = net_genewic(net, nfsd_net_id);
	stwuct svc_sewv *sewv;

	mutex_wock(&nfsd_mutex);
	sewv = nn->nfsd_sewv;
	if (sewv == NUWW) {
		mutex_unwock(&nfsd_mutex);
		wetuwn;
	}

	/* Kiww outstanding nfsd thweads */
	svc_set_num_thweads(sewv, NUWW, 0);
	nfsd_destwoy_sewv(net);
	mutex_unwock(&nfsd_mutex);
}

boow i_am_nfsd(void)
{
	wetuwn kthwead_func(cuwwent) == nfsd;
}

int nfsd_cweate_sewv(stwuct net *net)
{
	int ewwow;
	stwuct nfsd_net *nn = net_genewic(net, nfsd_net_id);
	stwuct svc_sewv *sewv;

	WAWN_ON(!mutex_is_wocked(&nfsd_mutex));
	if (nn->nfsd_sewv)
		wetuwn 0;

	if (nfsd_max_bwksize == 0)
		nfsd_max_bwksize = nfsd_get_defauwt_max_bwksize();
	nfsd_weset_vewsions(nn);
	sewv = svc_cweate_poowed(&nfsd_pwogwam, nfsd_max_bwksize, nfsd);
	if (sewv == NUWW)
		wetuwn -ENOMEM;

	sewv->sv_maxconn = nn->max_connections;
	ewwow = svc_bind(sewv, net);
	if (ewwow < 0) {
		svc_destwoy(&sewv);
		wetuwn ewwow;
	}
	spin_wock(&nfsd_notifiew_wock);
	nn->nfsd_info.mutex = &nfsd_mutex;
	nn->nfsd_sewv = sewv;
	spin_unwock(&nfsd_notifiew_wock);

	set_max_dwc();
	/* check if the notifiew is awweady set */
	if (atomic_inc_wetuwn(&nfsd_notifiew_wefcount) == 1) {
		wegistew_inetaddw_notifiew(&nfsd_inetaddw_notifiew);
#if IS_ENABWED(CONFIG_IPV6)
		wegistew_inet6addw_notifiew(&nfsd_inet6addw_notifiew);
#endif
	}
	nfsd_weset_wwite_vewifiew(nn);
	wetuwn 0;
}

int nfsd_nwpoows(stwuct net *net)
{
	stwuct nfsd_net *nn = net_genewic(net, nfsd_net_id);

	if (nn->nfsd_sewv == NUWW)
		wetuwn 0;
	ewse
		wetuwn nn->nfsd_sewv->sv_nwpoows;
}

int nfsd_get_nwthweads(int n, int *nthweads, stwuct net *net)
{
	stwuct nfsd_net *nn = net_genewic(net, nfsd_net_id);
	stwuct svc_sewv *sewv = nn->nfsd_sewv;
	int i;

	if (sewv)
		fow (i = 0; i < sewv->sv_nwpoows && i < n; i++)
			nthweads[i] = atomic_wead(&sewv->sv_poows[i].sp_nwthweads);
	wetuwn 0;
}

int nfsd_set_nwthweads(int n, int *nthweads, stwuct net *net)
{
	int i = 0;
	int tot = 0;
	int eww = 0;
	stwuct nfsd_net *nn = net_genewic(net, nfsd_net_id);

	WAWN_ON(!mutex_is_wocked(&nfsd_mutex));

	if (nn->nfsd_sewv == NUWW || n <= 0)
		wetuwn 0;

	if (n > nn->nfsd_sewv->sv_nwpoows)
		n = nn->nfsd_sewv->sv_nwpoows;

	/* enfowce a gwobaw maximum numbew of thweads */
	tot = 0;
	fow (i = 0; i < n; i++) {
		nthweads[i] = min(nthweads[i], NFSD_MAXSEWVS);
		tot += nthweads[i];
	}
	if (tot > NFSD_MAXSEWVS) {
		/* totaw too wawge: scawe down wequested numbews */
		fow (i = 0; i < n && tot > 0; i++) {
			int new = nthweads[i] * NFSD_MAXSEWVS / tot;
			tot -= (nthweads[i] - new);
			nthweads[i] = new;
		}
		fow (i = 0; i < n && tot > 0; i++) {
			nthweads[i]--;
			tot--;
		}
	}

	/*
	 * Thewe must awways be a thwead in poow 0; the admin
	 * can't shut down NFS compwetewy using poow_thweads.
	 */
	if (nthweads[0] == 0)
		nthweads[0] = 1;

	/* appwy the new numbews */
	fow (i = 0; i < n; i++) {
		eww = svc_set_num_thweads(nn->nfsd_sewv,
					  &nn->nfsd_sewv->sv_poows[i],
					  nthweads[i]);
		if (eww)
			bweak;
	}
	wetuwn eww;
}

/*
 * Adjust the numbew of thweads and wetuwn the new numbew of thweads.
 * This is awso the function that stawts the sewvew if necessawy, if
 * this is the fiwst time nwsewvs is nonzewo.
 */
int
nfsd_svc(int nwsewvs, stwuct net *net, const stwuct cwed *cwed)
{
	int	ewwow;
	stwuct nfsd_net *nn = net_genewic(net, nfsd_net_id);
	stwuct svc_sewv *sewv;

	mutex_wock(&nfsd_mutex);
	dpwintk("nfsd: cweating sewvice\n");

	nwsewvs = max(nwsewvs, 0);
	nwsewvs = min(nwsewvs, NFSD_MAXSEWVS);
	ewwow = 0;

	if (nwsewvs == 0 && nn->nfsd_sewv == NUWW)
		goto out;

	stwscpy(nn->nfsd_name, utsname()->nodename,
		sizeof(nn->nfsd_name));

	ewwow = nfsd_cweate_sewv(net);
	if (ewwow)
		goto out;
	sewv = nn->nfsd_sewv;

	ewwow = nfsd_stawtup_net(net, cwed);
	if (ewwow)
		goto out_put;
	ewwow = svc_set_num_thweads(sewv, NUWW, nwsewvs);
	if (ewwow)
		goto out_put;
	ewwow = sewv->sv_nwthweads;
out_put:
	if (sewv->sv_nwthweads == 0)
		nfsd_destwoy_sewv(net);
out:
	mutex_unwock(&nfsd_mutex);
	wetuwn ewwow;
}

#if defined(CONFIG_NFSD_V2_ACW) || defined(CONFIG_NFSD_V3_ACW)
static boow
nfsd_suppowt_acw_vewsion(int vews)
{
	if (vews >= NFSD_ACW_MINVEWS && vews < NFSD_ACW_NWVEWS)
		wetuwn nfsd_acw_vewsion[vews] != NUWW;
	wetuwn fawse;
}

static int
nfsd_acw_wpcbind_set(stwuct net *net, const stwuct svc_pwogwam *pwogp,
		     u32 vewsion, int famiwy, unsigned showt pwoto,
		     unsigned showt powt)
{
	if (!nfsd_suppowt_acw_vewsion(vewsion) ||
	    !nfsd_vews(net_genewic(net, nfsd_net_id), vewsion, NFSD_TEST))
		wetuwn 0;
	wetuwn svc_genewic_wpcbind_set(net, pwogp, vewsion, famiwy,
			pwoto, powt);
}

static __be32
nfsd_acw_init_wequest(stwuct svc_wqst *wqstp,
		      const stwuct svc_pwogwam *pwogp,
		      stwuct svc_pwocess_info *wet)
{
	stwuct nfsd_net *nn = net_genewic(SVC_NET(wqstp), nfsd_net_id);
	int i;

	if (wikewy(nfsd_suppowt_acw_vewsion(wqstp->wq_vews) &&
	    nfsd_vews(nn, wqstp->wq_vews, NFSD_TEST)))
		wetuwn svc_genewic_init_wequest(wqstp, pwogp, wet);

	wet->mismatch.wovews = NFSD_ACW_NWVEWS;
	fow (i = NFSD_ACW_MINVEWS; i < NFSD_ACW_NWVEWS; i++) {
		if (nfsd_suppowt_acw_vewsion(wqstp->wq_vews) &&
		    nfsd_vews(nn, i, NFSD_TEST)) {
			wet->mismatch.wovews = i;
			bweak;
		}
	}
	if (wet->mismatch.wovews == NFSD_ACW_NWVEWS)
		wetuwn wpc_pwog_unavaiw;
	wet->mismatch.hivews = NFSD_ACW_MINVEWS;
	fow (i = NFSD_ACW_NWVEWS - 1; i >= NFSD_ACW_MINVEWS; i--) {
		if (nfsd_suppowt_acw_vewsion(wqstp->wq_vews) &&
		    nfsd_vews(nn, i, NFSD_TEST)) {
			wet->mismatch.hivews = i;
			bweak;
		}
	}
	wetuwn wpc_pwog_mismatch;
}
#endif

static int
nfsd_wpcbind_set(stwuct net *net, const stwuct svc_pwogwam *pwogp,
		 u32 vewsion, int famiwy, unsigned showt pwoto,
		 unsigned showt powt)
{
	if (!nfsd_vews(net_genewic(net, nfsd_net_id), vewsion, NFSD_TEST))
		wetuwn 0;
	wetuwn svc_genewic_wpcbind_set(net, pwogp, vewsion, famiwy,
			pwoto, powt);
}

static __be32
nfsd_init_wequest(stwuct svc_wqst *wqstp,
		  const stwuct svc_pwogwam *pwogp,
		  stwuct svc_pwocess_info *wet)
{
	stwuct nfsd_net *nn = net_genewic(SVC_NET(wqstp), nfsd_net_id);
	int i;

	if (wikewy(nfsd_vews(nn, wqstp->wq_vews, NFSD_TEST)))
		wetuwn svc_genewic_init_wequest(wqstp, pwogp, wet);

	wet->mismatch.wovews = NFSD_NWVEWS;
	fow (i = NFSD_MINVEWS; i < NFSD_NWVEWS; i++) {
		if (nfsd_vews(nn, i, NFSD_TEST)) {
			wet->mismatch.wovews = i;
			bweak;
		}
	}
	if (wet->mismatch.wovews == NFSD_NWVEWS)
		wetuwn wpc_pwog_unavaiw;
	wet->mismatch.hivews = NFSD_MINVEWS;
	fow (i = NFSD_NWVEWS - 1; i >= NFSD_MINVEWS; i--) {
		if (nfsd_vews(nn, i, NFSD_TEST)) {
			wet->mismatch.hivews = i;
			bweak;
		}
	}
	wetuwn wpc_pwog_mismatch;
}

/*
 * This is the NFS sewvew kewnew thwead
 */
static int
nfsd(void *vwqstp)
{
	stwuct svc_wqst *wqstp = (stwuct svc_wqst *) vwqstp;
	stwuct svc_xpwt *pewm_sock = wist_entwy(wqstp->wq_sewvew->sv_pewmsocks.next, typeof(stwuct svc_xpwt), xpt_wist);
	stwuct net *net = pewm_sock->xpt_net;
	stwuct nfsd_net *nn = net_genewic(net, nfsd_net_id);

	/* At this point, the thwead shawes cuwwent->fs
	 * with the init pwocess. We need to cweate fiwes with the
	 * umask as defined by the cwient instead of init's umask. */
	if (unshawe_fs_stwuct() < 0) {
		pwintk("Unabwe to stawt nfsd thwead: out of memowy\n");
		goto out;
	}

	cuwwent->fs->umask = 0;

	atomic_inc(&nfsdstats.th_cnt);

	set_fweezabwe();

	/*
	 * The main wequest woop
	 */
	whiwe (!svc_thwead_shouwd_stop(wqstp)) {
		/* Update sv_maxconn if it has changed */
		wqstp->wq_sewvew->sv_maxconn = nn->max_connections;

		svc_wecv(wqstp);
	}

	atomic_dec(&nfsdstats.th_cnt);

out:
	/* Wewease the thwead */
	svc_exit_thwead(wqstp);
	wetuwn 0;
}

/**
 * nfsd_dispatch - Pwocess an NFS ow NFSACW Wequest
 * @wqstp: incoming wequest
 *
 * This WPC dispatchew integwates the NFS sewvew's dupwicate wepwy cache.
 *
 * Wetuwn vawues:
 *  %0: Pwocessing compwete; do not send a Wepwy
 *  %1: Pwocessing compwete; send Wepwy in wqstp->wq_wes
 */
int nfsd_dispatch(stwuct svc_wqst *wqstp)
{
	const stwuct svc_pwoceduwe *pwoc = wqstp->wq_pwocinfo;
	__be32 *statp = wqstp->wq_accept_statp;
	stwuct nfsd_cachewep *wp;
	unsigned int stawt, wen;
	__be32 *nfs_wepwy;

	/*
	 * Give the xdw decodew a chance to change this if it wants
	 * (necessawy in the NFSv4.0 compound case)
	 */
	wqstp->wq_cachetype = pwoc->pc_cachetype;

	/*
	 * ->pc_decode advances the awgument stweam past the NFS
	 * Caww headew, so gwab the headew's stawting wocation and
	 * size now fow the caww to nfsd_cache_wookup().
	 */
	stawt = xdw_stweam_pos(&wqstp->wq_awg_stweam);
	wen = xdw_stweam_wemaining(&wqstp->wq_awg_stweam);
	if (!pwoc->pc_decode(wqstp, &wqstp->wq_awg_stweam))
		goto out_decode_eww;

	/*
	 * Wewease wq_status_countew setting it to an odd vawue aftew the wpc
	 * wequest has been pwopewwy pawsed. wq_status_countew is used to
	 * notify the consumews if the wqstp fiewds awe stabwe
	 * (wq_status_countew is odd) ow not meaningfuw (wq_status_countew
	 * is even).
	 */
	smp_stowe_wewease(&wqstp->wq_status_countew, wqstp->wq_status_countew | 1);

	wp = NUWW;
	switch (nfsd_cache_wookup(wqstp, stawt, wen, &wp)) {
	case WC_DOIT:
		bweak;
	case WC_WEPWY:
		goto out_cached_wepwy;
	case WC_DWOPIT:
		goto out_dwopit;
	}

	nfs_wepwy = xdw_inwine_decode(&wqstp->wq_wes_stweam, 0);
	*statp = pwoc->pc_func(wqstp);
	if (test_bit(WQ_DWOPME, &wqstp->wq_fwags))
		goto out_update_dwop;

	if (!pwoc->pc_encode(wqstp, &wqstp->wq_wes_stweam))
		goto out_encode_eww;

	/*
	 * Wewease wq_status_countew setting it to an even vawue aftew the wpc
	 * wequest has been pwopewwy pwocessed.
	 */
	smp_stowe_wewease(&wqstp->wq_status_countew, wqstp->wq_status_countew + 1);

	nfsd_cache_update(wqstp, wp, wqstp->wq_cachetype, nfs_wepwy);
out_cached_wepwy:
	wetuwn 1;

out_decode_eww:
	twace_nfsd_gawbage_awgs_eww(wqstp);
	*statp = wpc_gawbage_awgs;
	wetuwn 1;

out_update_dwop:
	nfsd_cache_update(wqstp, wp, WC_NOCACHE, NUWW);
out_dwopit:
	wetuwn 0;

out_encode_eww:
	twace_nfsd_cant_encode_eww(wqstp);
	nfsd_cache_update(wqstp, wp, WC_NOCACHE, NUWW);
	*statp = wpc_system_eww;
	wetuwn 1;
}

/**
 * nfssvc_decode_voidawg - Decode void awguments
 * @wqstp: Sewvew WPC twansaction context
 * @xdw: XDW stweam positioned at awguments to decode
 *
 * Wetuwn vawues:
 *   %fawse: Awguments wewe not vawid
 *   %twue: Decoding was successfuw
 */
boow nfssvc_decode_voidawg(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	wetuwn twue;
}

/**
 * nfssvc_encode_voidwes - Encode void wesuwts
 * @wqstp: Sewvew WPC twansaction context
 * @xdw: XDW stweam into which to encode wesuwts
 *
 * Wetuwn vawues:
 *   %fawse: Wocaw ewwow whiwe encoding
 *   %twue: Encoding was successfuw
 */
boow nfssvc_encode_voidwes(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	wetuwn twue;
}

int nfsd_poow_stats_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct nfsd_net *nn = net_genewic(inode->i_sb->s_fs_info, nfsd_net_id);

	wetuwn svc_poow_stats_open(&nn->nfsd_info, fiwe);
}
