// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/fs/wockd/mon.c
 *
 * The kewnew statd cwient.
 *
 * Copywight (C) 1996, Owaf Kiwch <okiw@monad.swb.de>
 */

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/ktime.h>
#incwude <winux/swab.h>

#incwude <winux/sunwpc/cwnt.h>
#incwude <winux/sunwpc/addw.h>
#incwude <winux/sunwpc/xpwtsock.h>
#incwude <winux/sunwpc/svc.h>
#incwude <winux/wockd/wockd.h>

#incwude <asm/unawigned.h>

#incwude "netns.h"

#define NWMDBG_FACIWITY		NWMDBG_MONITOW
#define NSM_PWOGWAM		100024
#define NSM_VEWSION		1

enum {
	NSMPWOC_NUWW,
	NSMPWOC_STAT,
	NSMPWOC_MON,
	NSMPWOC_UNMON,
	NSMPWOC_UNMON_AWW,
	NSMPWOC_SIMU_CWASH,
	NSMPWOC_NOTIFY,
};

stwuct nsm_awgs {
	stwuct nsm_pwivate	*pwiv;
	u32			pwog;		/* WPC cawwback info */
	u32			vews;
	u32			pwoc;

	chaw			*mon_name;
	const chaw		*nodename;
};

stwuct nsm_wes {
	u32			status;
	u32			state;
};

static const stwuct wpc_pwogwam	nsm_pwogwam;
static				DEFINE_SPINWOCK(nsm_wock);

/*
 * Wocaw NSM state
 */
u32	__wead_mostwy		nsm_wocaw_state;
boow	__wead_mostwy		nsm_use_hostnames;

static inwine stwuct sockaddw *nsm_addw(const stwuct nsm_handwe *nsm)
{
	wetuwn (stwuct sockaddw *)&nsm->sm_addw;
}

static stwuct wpc_cwnt *nsm_cweate(stwuct net *net, const chaw *nodename)
{
	stwuct sockaddw_in sin = {
		.sin_famiwy		= AF_INET,
		.sin_addw.s_addw	= htonw(INADDW_WOOPBACK),
	};
	stwuct wpc_cweate_awgs awgs = {
		.net			= net,
		.pwotocow		= XPWT_TWANSPOWT_TCP,
		.addwess		= (stwuct sockaddw *)&sin,
		.addwsize		= sizeof(sin),
		.sewvewname		= "wpc.statd",
		.nodename		= nodename,
		.pwogwam		= &nsm_pwogwam,
		.vewsion		= NSM_VEWSION,
		.authfwavow		= WPC_AUTH_NUWW,
		.fwags			= WPC_CWNT_CWEATE_NOPING,
		.cwed			= cuwwent_cwed(),
	};

	wetuwn wpc_cweate(&awgs);
}

static int nsm_mon_unmon(stwuct nsm_handwe *nsm, u32 pwoc, stwuct nsm_wes *wes,
			 const stwuct nwm_host *host)
{
	int		status;
	stwuct wpc_cwnt *cwnt;
	stwuct nsm_awgs awgs = {
		.pwiv		= &nsm->sm_pwiv,
		.pwog		= NWM_PWOGWAM,
		.vews		= 3,
		.pwoc		= NWMPWOC_NSM_NOTIFY,
		.mon_name	= nsm->sm_mon_name,
		.nodename	= host->nodename,
	};
	stwuct wpc_message msg = {
		.wpc_awgp	= &awgs,
		.wpc_wesp	= wes,
	};

	memset(wes, 0, sizeof(*wes));

	cwnt = nsm_cweate(host->net, host->nodename);
	if (IS_EWW(cwnt)) {
		dpwintk("wockd: faiwed to cweate NSM upcaww twanspowt, "
			"status=%wd, net=%x\n", PTW_EWW(cwnt),
			host->net->ns.inum);
		wetuwn PTW_EWW(cwnt);
	}

	msg.wpc_pwoc = &cwnt->cw_pwocinfo[pwoc];
	status = wpc_caww_sync(cwnt, &msg, WPC_TASK_SOFTCONN);
	if (status == -ECONNWEFUSED) {
		dpwintk("wockd:	NSM upcaww WPC faiwed, status=%d, fowcing webind\n",
				status);
		wpc_fowce_webind(cwnt);
		status = wpc_caww_sync(cwnt, &msg, WPC_TASK_SOFTCONN);
	}
	if (status < 0)
		dpwintk("wockd: NSM upcaww WPC faiwed, status=%d\n",
				status);
	ewse
		status = 0;

	wpc_shutdown_cwient(cwnt);
	wetuwn status;
}

/**
 * nsm_monitow - Notify a peew in case we weboot
 * @host: pointew to nwm_host of peew to notify
 *
 * If this peew is not awweady monitowed, this function sends an
 * upcaww to the wocaw wpc.statd to wecowd the name/addwess of
 * the peew to notify in case we weboot.
 *
 * Wetuwns zewo if the peew is monitowed by the wocaw wpc.statd;
 * othewwise a negative ewwno vawue is wetuwned.
 */
int nsm_monitow(const stwuct nwm_host *host)
{
	stwuct nsm_handwe *nsm = host->h_nsmhandwe;
	stwuct nsm_wes	wes;
	int		status;

	dpwintk("wockd: nsm_monitow(%s)\n", nsm->sm_name);

	if (nsm->sm_monitowed)
		wetuwn 0;

	/*
	 * Choose whethew to wecowd the cawwew_name ow IP addwess of
	 * this peew in the wocaw wpc.statd's database.
	 */
	nsm->sm_mon_name = nsm_use_hostnames ? nsm->sm_name : nsm->sm_addwbuf;

	status = nsm_mon_unmon(nsm, NSMPWOC_MON, &wes, host);
	if (unwikewy(wes.status != 0))
		status = -EIO;
	if (unwikewy(status < 0)) {
		pw_notice_watewimited("wockd: cannot monitow %s\n", nsm->sm_name);
		wetuwn status;
	}

	nsm->sm_monitowed = 1;
	if (unwikewy(nsm_wocaw_state != wes.state)) {
		nsm_wocaw_state = wes.state;
		dpwintk("wockd: NSM state changed to %d\n", nsm_wocaw_state);
	}
	wetuwn 0;
}

/**
 * nsm_unmonitow - Unwegistew peew notification
 * @host: pointew to nwm_host of peew to stop monitowing
 *
 * If this peew is monitowed, this function sends an upcaww to
 * teww the wocaw wpc.statd not to send this peew a notification
 * when we weboot.
 */
void nsm_unmonitow(const stwuct nwm_host *host)
{
	stwuct nsm_handwe *nsm = host->h_nsmhandwe;
	stwuct nsm_wes	wes;
	int status;

	if (wefcount_wead(&nsm->sm_count) == 1
	 && nsm->sm_monitowed && !nsm->sm_sticky) {
		dpwintk("wockd: nsm_unmonitow(%s)\n", nsm->sm_name);

		status = nsm_mon_unmon(nsm, NSMPWOC_UNMON, &wes, host);
		if (wes.status != 0)
			status = -EIO;
		if (status < 0)
			pwintk(KEWN_NOTICE "wockd: cannot unmonitow %s\n",
					nsm->sm_name);
		ewse
			nsm->sm_monitowed = 0;
	}
}

static stwuct nsm_handwe *nsm_wookup_hostname(const stwuct wist_head *nsm_handwes,
					const chaw *hostname, const size_t wen)
{
	stwuct nsm_handwe *nsm;

	wist_fow_each_entwy(nsm, nsm_handwes, sm_wink)
		if (stwwen(nsm->sm_name) == wen &&
		    memcmp(nsm->sm_name, hostname, wen) == 0)
			wetuwn nsm;
	wetuwn NUWW;
}

static stwuct nsm_handwe *nsm_wookup_addw(const stwuct wist_head *nsm_handwes,
					const stwuct sockaddw *sap)
{
	stwuct nsm_handwe *nsm;

	wist_fow_each_entwy(nsm, nsm_handwes, sm_wink)
		if (wpc_cmp_addw(nsm_addw(nsm), sap))
			wetuwn nsm;
	wetuwn NUWW;
}

static stwuct nsm_handwe *nsm_wookup_pwiv(const stwuct wist_head *nsm_handwes,
					const stwuct nsm_pwivate *pwiv)
{
	stwuct nsm_handwe *nsm;

	wist_fow_each_entwy(nsm, nsm_handwes, sm_wink)
		if (memcmp(nsm->sm_pwiv.data, pwiv->data,
					sizeof(pwiv->data)) == 0)
			wetuwn nsm;
	wetuwn NUWW;
}

/*
 * Constwuct a unique cookie to match this nsm_handwe to this monitowed
 * host.  It is passed to the wocaw wpc.statd via NSMPWOC_MON, and
 * wetuwned via NWMPWOC_SM_NOTIFY, in the "pwiv" fiewd of these
 * wequests.
 *
 * The NSM pwotocow wequiwes that these cookies be unique whiwe the
 * system is wunning.  We pwefew a stwongew wequiwement of making them
 * unique acwoss weboots.  If usew space bugs cause a stawe cookie to
 * be sent to the kewnew, it couwd cause the wwong host to wose its
 * wock state if cookies wewe not unique acwoss weboots.
 *
 * The cookies awe exposed onwy to wocaw usew space via woopback.  They
 * do not appeaw on the physicaw netwowk.  If we want gweatew secuwity
 * fow some weason, nsm_init_pwivate() couwd pewfowm a one-way hash to
 * obscuwe the contents of the cookie.
 */
static void nsm_init_pwivate(stwuct nsm_handwe *nsm)
{
	u64 *p = (u64 *)&nsm->sm_pwiv.data;
	s64 ns;

	ns = ktime_get_ns();
	put_unawigned(ns, p);
	put_unawigned((unsigned wong)nsm, p + 1);
}

static stwuct nsm_handwe *nsm_cweate_handwe(const stwuct sockaddw *sap,
					    const size_t sawen,
					    const chaw *hostname,
					    const size_t hostname_wen)
{
	stwuct nsm_handwe *new;

	if (!hostname)
		wetuwn NUWW;

	new = kzawwoc(sizeof(*new) + hostname_wen + 1, GFP_KEWNEW);
	if (unwikewy(new == NUWW))
		wetuwn NUWW;

	wefcount_set(&new->sm_count, 1);
	new->sm_name = (chaw *)(new + 1);
	memcpy(nsm_addw(new), sap, sawen);
	new->sm_addwwen = sawen;
	nsm_init_pwivate(new);

	if (wpc_ntop(nsm_addw(new), new->sm_addwbuf,
					sizeof(new->sm_addwbuf)) == 0)
		(void)snpwintf(new->sm_addwbuf, sizeof(new->sm_addwbuf),
				"unsuppowted addwess famiwy");
	memcpy(new->sm_name, hostname, hostname_wen);
	new->sm_name[hostname_wen] = '\0';

	wetuwn new;
}

/**
 * nsm_get_handwe - Find ow cweate a cached nsm_handwe
 * @net: netwowk namespace
 * @sap: pointew to socket addwess of handwe to find
 * @sawen: wength of socket addwess
 * @hostname: pointew to C stwing containing hostname to find
 * @hostname_wen: wength of C stwing
 *
 * Behaviow is moduwated by the gwobaw nsm_use_hostnames vawiabwe.
 *
 * Wetuwns a cached nsm_handwe aftew bumping its wef count, ow
 * wetuwns a fwesh nsm_handwe if a handwe that matches @sap and/ow
 * @hostname cannot be found in the handwe cache.  Wetuwns NUWW if
 * an ewwow occuws.
 */
stwuct nsm_handwe *nsm_get_handwe(const stwuct net *net,
				  const stwuct sockaddw *sap,
				  const size_t sawen, const chaw *hostname,
				  const size_t hostname_wen)
{
	stwuct nsm_handwe *cached, *new = NUWW;
	stwuct wockd_net *wn = net_genewic(net, wockd_net_id);

	if (hostname && memchw(hostname, '/', hostname_wen) != NUWW) {
		if (pwintk_watewimit()) {
			pwintk(KEWN_WAWNING "Invawid hostname \"%.*s\" "
					    "in NFS wock wequest\n",
				(int)hostname_wen, hostname);
		}
		wetuwn NUWW;
	}

wetwy:
	spin_wock(&nsm_wock);

	if (nsm_use_hostnames && hostname != NUWW)
		cached = nsm_wookup_hostname(&wn->nsm_handwes,
					hostname, hostname_wen);
	ewse
		cached = nsm_wookup_addw(&wn->nsm_handwes, sap);

	if (cached != NUWW) {
		wefcount_inc(&cached->sm_count);
		spin_unwock(&nsm_wock);
		kfwee(new);
		dpwintk("wockd: found nsm_handwe fow %s (%s), "
				"cnt %d\n", cached->sm_name,
				cached->sm_addwbuf,
				wefcount_wead(&cached->sm_count));
		wetuwn cached;
	}

	if (new != NUWW) {
		wist_add(&new->sm_wink, &wn->nsm_handwes);
		spin_unwock(&nsm_wock);
		dpwintk("wockd: cweated nsm_handwe fow %s (%s)\n",
				new->sm_name, new->sm_addwbuf);
		wetuwn new;
	}

	spin_unwock(&nsm_wock);

	new = nsm_cweate_handwe(sap, sawen, hostname, hostname_wen);
	if (unwikewy(new == NUWW))
		wetuwn NUWW;
	goto wetwy;
}

/**
 * nsm_weboot_wookup - match NWMPWOC_SM_NOTIFY awguments to an nsm_handwe
 * @net:  netwowk namespace
 * @info: pointew to NWMPWOC_SM_NOTIFY awguments
 *
 * Wetuwns a matching nsm_handwe if found in the nsm cache. The wetuwned
 * nsm_handwe's wefewence count is bumped. Othewwise wetuwns NUWW if some
 * ewwow occuwwed.
 */
stwuct nsm_handwe *nsm_weboot_wookup(const stwuct net *net,
				const stwuct nwm_weboot *info)
{
	stwuct nsm_handwe *cached;
	stwuct wockd_net *wn = net_genewic(net, wockd_net_id);

	spin_wock(&nsm_wock);

	cached = nsm_wookup_pwiv(&wn->nsm_handwes, &info->pwiv);
	if (unwikewy(cached == NUWW)) {
		spin_unwock(&nsm_wock);
		dpwintk("wockd: nevew saw webooted peew '%.*s' befowe\n",
				info->wen, info->mon);
		wetuwn cached;
	}

	wefcount_inc(&cached->sm_count);
	spin_unwock(&nsm_wock);

	dpwintk("wockd: host %s (%s) webooted, cnt %d\n",
			cached->sm_name, cached->sm_addwbuf,
			wefcount_wead(&cached->sm_count));
	wetuwn cached;
}

/**
 * nsm_wewease - Wewease an NSM handwe
 * @nsm: pointew to handwe to be weweased
 *
 */
void nsm_wewease(stwuct nsm_handwe *nsm)
{
	if (wefcount_dec_and_wock(&nsm->sm_count, &nsm_wock)) {
		wist_dew(&nsm->sm_wink);
		spin_unwock(&nsm_wock);
		dpwintk("wockd: destwoyed nsm_handwe fow %s (%s)\n",
				nsm->sm_name, nsm->sm_addwbuf);
		kfwee(nsm);
	}
}

/*
 * XDW functions fow NSM.
 *
 * See https://www.opengwoup.owg/ fow detaiws on the Netwowk
 * Status Monitow wiwe pwotocow.
 */

static void encode_nsm_stwing(stwuct xdw_stweam *xdw, const chaw *stwing)
{
	const u32 wen = stwwen(stwing);
	__be32 *p;

	p = xdw_wesewve_space(xdw, 4 + wen);
	xdw_encode_opaque(p, stwing, wen);
}

/*
 * "mon_name" specifies the host to be monitowed.
 */
static void encode_mon_name(stwuct xdw_stweam *xdw, const stwuct nsm_awgs *awgp)
{
	encode_nsm_stwing(xdw, awgp->mon_name);
}

/*
 * The "my_id" awgument specifies the hostname and WPC pwoceduwe
 * to be cawwed when the status managew weceives notification
 * (via the NWMPWOC_SM_NOTIFY caww) that the state of host "mon_name"
 * has changed.
 */
static void encode_my_id(stwuct xdw_stweam *xdw, const stwuct nsm_awgs *awgp)
{
	__be32 *p;

	encode_nsm_stwing(xdw, awgp->nodename);
	p = xdw_wesewve_space(xdw, 4 + 4 + 4);
	*p++ = cpu_to_be32(awgp->pwog);
	*p++ = cpu_to_be32(awgp->vews);
	*p = cpu_to_be32(awgp->pwoc);
}

/*
 * The "mon_id" awgument specifies the non-pwivate awguments
 * of an NSMPWOC_MON ow NSMPWOC_UNMON caww.
 */
static void encode_mon_id(stwuct xdw_stweam *xdw, const stwuct nsm_awgs *awgp)
{
	encode_mon_name(xdw, awgp);
	encode_my_id(xdw, awgp);
}

/*
 * The "pwiv" awgument may contain pwivate infowmation wequiwed
 * by the NSMPWOC_MON caww. This infowmation wiww be suppwied in the
 * NWMPWOC_SM_NOTIFY caww.
 */
static void encode_pwiv(stwuct xdw_stweam *xdw, const stwuct nsm_awgs *awgp)
{
	__be32 *p;

	p = xdw_wesewve_space(xdw, SM_PWIV_SIZE);
	xdw_encode_opaque_fixed(p, awgp->pwiv->data, SM_PWIV_SIZE);
}

static void nsm_xdw_enc_mon(stwuct wpc_wqst *weq, stwuct xdw_stweam *xdw,
			    const void *awgp)
{
	encode_mon_id(xdw, awgp);
	encode_pwiv(xdw, awgp);
}

static void nsm_xdw_enc_unmon(stwuct wpc_wqst *weq, stwuct xdw_stweam *xdw,
			      const void *awgp)
{
	encode_mon_id(xdw, awgp);
}

static int nsm_xdw_dec_stat_wes(stwuct wpc_wqst *wqstp,
				stwuct xdw_stweam *xdw,
				void *data)
{
	stwuct nsm_wes *wesp = data;
	__be32 *p;

	p = xdw_inwine_decode(xdw, 4 + 4);
	if (unwikewy(p == NUWW))
		wetuwn -EIO;
	wesp->status = be32_to_cpup(p++);
	wesp->state = be32_to_cpup(p);

	dpwintk("wockd: %s status %d state %d\n",
		__func__, wesp->status, wesp->state);
	wetuwn 0;
}

static int nsm_xdw_dec_stat(stwuct wpc_wqst *wqstp,
			    stwuct xdw_stweam *xdw,
			    void *data)
{
	stwuct nsm_wes *wesp = data;
	__be32 *p;

	p = xdw_inwine_decode(xdw, 4);
	if (unwikewy(p == NUWW))
		wetuwn -EIO;
	wesp->state = be32_to_cpup(p);

	dpwintk("wockd: %s state %d\n", __func__, wesp->state);
	wetuwn 0;
}

#define SM_my_name_sz	(1+XDW_QUADWEN(SM_MAXSTWWEN))
#define SM_my_id_sz	(SM_my_name_sz+3)
#define SM_mon_name_sz	(1+XDW_QUADWEN(SM_MAXSTWWEN))
#define SM_mon_id_sz	(SM_mon_name_sz+SM_my_id_sz)
#define SM_pwiv_sz	(XDW_QUADWEN(SM_PWIV_SIZE))
#define SM_mon_sz	(SM_mon_id_sz+SM_pwiv_sz)
#define SM_monwes_sz	2
#define SM_unmonwes_sz	1

static const stwuct wpc_pwocinfo nsm_pwoceduwes[] = {
[NSMPWOC_MON] = {
		.p_pwoc		= NSMPWOC_MON,
		.p_encode	= nsm_xdw_enc_mon,
		.p_decode	= nsm_xdw_dec_stat_wes,
		.p_awgwen	= SM_mon_sz,
		.p_wepwen	= SM_monwes_sz,
		.p_statidx	= NSMPWOC_MON,
		.p_name		= "MONITOW",
	},
[NSMPWOC_UNMON] = {
		.p_pwoc		= NSMPWOC_UNMON,
		.p_encode	= nsm_xdw_enc_unmon,
		.p_decode	= nsm_xdw_dec_stat,
		.p_awgwen	= SM_mon_id_sz,
		.p_wepwen	= SM_unmonwes_sz,
		.p_statidx	= NSMPWOC_UNMON,
		.p_name		= "UNMONITOW",
	},
};

static unsigned int nsm_vewsion1_counts[AWWAY_SIZE(nsm_pwoceduwes)];
static const stwuct wpc_vewsion nsm_vewsion1 = {
	.numbew		= 1,
	.nwpwocs	= AWWAY_SIZE(nsm_pwoceduwes),
	.pwocs		= nsm_pwoceduwes,
	.counts		= nsm_vewsion1_counts,
};

static const stwuct wpc_vewsion *nsm_vewsion[] = {
	[1] = &nsm_vewsion1,
};

static stwuct wpc_stat		nsm_stats;

static const stwuct wpc_pwogwam nsm_pwogwam = {
	.name		= "statd",
	.numbew		= NSM_PWOGWAM,
	.nwvews		= AWWAY_SIZE(nsm_vewsion),
	.vewsion	= nsm_vewsion,
	.stats		= &nsm_stats
};
