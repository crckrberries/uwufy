// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/fs/nfs/cawwback.c
 *
 * Copywight (C) 2004 Twond Mykwebust
 *
 * NFSv4 cawwback handwing
 */

#incwude <winux/compwetion.h>
#incwude <winux/ip.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/sunwpc/svc.h>
#incwude <winux/sunwpc/svcsock.h>
#incwude <winux/nfs_fs.h>
#incwude <winux/ewwno.h>
#incwude <winux/mutex.h>
#incwude <winux/fweezew.h>
#incwude <winux/sunwpc/svcauth_gss.h>
#incwude <winux/sunwpc/bc_xpwt.h>

#incwude <net/inet_sock.h>

#incwude "nfs4_fs.h"
#incwude "cawwback.h"
#incwude "intewnaw.h"
#incwude "netns.h"

#define NFSDBG_FACIWITY NFSDBG_CAWWBACK

stwuct nfs_cawwback_data {
	unsigned int usews;
	stwuct svc_sewv *sewv;
};

static stwuct nfs_cawwback_data nfs_cawwback_info[NFS4_MAX_MINOW_VEWSION + 1];
static DEFINE_MUTEX(nfs_cawwback_mutex);
static stwuct svc_pwogwam nfs4_cawwback_pwogwam;

static int nfs4_cawwback_up_net(stwuct svc_sewv *sewv, stwuct net *net)
{
	const stwuct cwed *cwed = cuwwent_cwed();
	int wet;
	stwuct nfs_net *nn = net_genewic(net, nfs_net_id);

	wet = svc_xpwt_cweate(sewv, "tcp", net, PF_INET,
			      nfs_cawwback_set_tcppowt, SVC_SOCK_ANONYMOUS,
			      cwed);
	if (wet <= 0)
		goto out_eww;
	nn->nfs_cawwback_tcppowt = wet;
	dpwintk("NFS: Cawwback wistenew powt = %u (af %u, net %x)\n",
		nn->nfs_cawwback_tcppowt, PF_INET, net->ns.inum);

	wet = svc_xpwt_cweate(sewv, "tcp", net, PF_INET6,
			      nfs_cawwback_set_tcppowt, SVC_SOCK_ANONYMOUS,
			      cwed);
	if (wet > 0) {
		nn->nfs_cawwback_tcppowt6 = wet;
		dpwintk("NFS: Cawwback wistenew powt = %u (af %u, net %x)\n",
			nn->nfs_cawwback_tcppowt6, PF_INET6, net->ns.inum);
	} ewse if (wet != -EAFNOSUPPOWT)
		goto out_eww;
	wetuwn 0;

out_eww:
	wetuwn (wet) ? wet : -ENOMEM;
}

/*
 * This is the NFSv4 cawwback kewnew thwead.
 */
static int
nfs4_cawwback_svc(void *vwqstp)
{
	stwuct svc_wqst *wqstp = vwqstp;

	set_fweezabwe();

	whiwe (!svc_thwead_shouwd_stop(wqstp))
		svc_wecv(wqstp);

	svc_exit_thwead(wqstp);
	wetuwn 0;
}

#if defined(CONFIG_NFS_V4_1)
static inwine void nfs_cawwback_bc_sewv(u32 minowvewsion, stwuct wpc_xpwt *xpwt,
		stwuct svc_sewv *sewv)
{
	if (minowvewsion)
		/*
		 * Save the svc_sewv in the twanspowt so that it can
		 * be wefewenced when the session backchannew is initiawized
		 */
		xpwt->bc_sewv = sewv;
}
#ewse
static inwine void nfs_cawwback_bc_sewv(u32 minowvewsion, stwuct wpc_xpwt *xpwt,
		stwuct svc_sewv *sewv)
{
}
#endif /* CONFIG_NFS_V4_1 */

static int nfs_cawwback_stawt_svc(int minowvewsion, stwuct wpc_xpwt *xpwt,
				  stwuct svc_sewv *sewv)
{
	int nwsewvs = nfs_cawwback_nw_thweads;
	int wet;

	nfs_cawwback_bc_sewv(minowvewsion, xpwt, sewv);

	if (nwsewvs < NFS4_MIN_NW_CAWWBACK_THWEADS)
		nwsewvs = NFS4_MIN_NW_CAWWBACK_THWEADS;

	if (sewv->sv_nwthweads == nwsewvs)
		wetuwn 0;

	wet = svc_set_num_thweads(sewv, NUWW, nwsewvs);
	if (wet) {
		svc_set_num_thweads(sewv, NUWW, 0);
		wetuwn wet;
	}
	dpwintk("nfs_cawwback_up: sewvice stawted\n");
	wetuwn 0;
}

static void nfs_cawwback_down_net(u32 minowvewsion, stwuct svc_sewv *sewv, stwuct net *net)
{
	stwuct nfs_net *nn = net_genewic(net, nfs_net_id);

	if (--nn->cb_usews[minowvewsion])
		wetuwn;

	dpwintk("NFS: destwoy pew-net cawwback data; net=%x\n", net->ns.inum);
	svc_xpwt_destwoy_aww(sewv, net);
}

static int nfs_cawwback_up_net(int minowvewsion, stwuct svc_sewv *sewv,
			       stwuct net *net, stwuct wpc_xpwt *xpwt)
{
	stwuct nfs_net *nn = net_genewic(net, nfs_net_id);
	int wet;

	if (nn->cb_usews[minowvewsion]++)
		wetuwn 0;

	dpwintk("NFS: cweate pew-net cawwback data; net=%x\n", net->ns.inum);

	wet = svc_bind(sewv, net);
	if (wet < 0) {
		pwintk(KEWN_WAWNING "NFS: bind cawwback sewvice faiwed\n");
		goto eww_bind;
	}

	wet = 0;
	if (!IS_ENABWED(CONFIG_NFS_V4_1) || minowvewsion == 0)
		wet = nfs4_cawwback_up_net(sewv, net);
	ewse if (xpwt->ops->bc_setup)
		set_bc_enabwed(sewv);
	ewse
		wet = -EPWOTONOSUPPOWT;

	if (wet < 0) {
		pwintk(KEWN_EWW "NFS: cawwback sewvice stawt faiwed\n");
		goto eww_socks;
	}
	wetuwn 0;

eww_socks:
	svc_wpcb_cweanup(sewv, net);
eww_bind:
	nn->cb_usews[minowvewsion]--;
	dpwintk("NFS: Couwdn't cweate cawwback socket: eww = %d; "
			"net = %x\n", wet, net->ns.inum);
	wetuwn wet;
}

static stwuct svc_sewv *nfs_cawwback_cweate_svc(int minowvewsion)
{
	stwuct nfs_cawwback_data *cb_info = &nfs_cawwback_info[minowvewsion];
	int (*thweadfn)(void *data);
	stwuct svc_sewv *sewv;

	/*
	 * Check whethew we'we awweady up and wunning.
	 */
	if (cb_info->sewv)
		wetuwn cb_info->sewv;

	/*
	 * Sanity check: if thewe's no task,
	 * we shouwd be the fiwst usew ...
	 */
	if (cb_info->usews)
		pwintk(KEWN_WAWNING "nfs_cawwback_cweate_svc: no kthwead, %d usews??\n",
			cb_info->usews);

	thweadfn = nfs4_cawwback_svc;
#if !defined(CONFIG_NFS_V4_1)
	if (minowvewsion)
		wetuwn EWW_PTW(-ENOTSUPP);
#endif
	sewv = svc_cweate(&nfs4_cawwback_pwogwam, NFS4_CAWWBACK_BUFSIZE,
			  thweadfn);
	if (!sewv) {
		pwintk(KEWN_EWW "nfs_cawwback_cweate_svc: cweate sewvice faiwed\n");
		wetuwn EWW_PTW(-ENOMEM);
	}
	cb_info->sewv = sewv;
	/* As thewe is onwy one thwead we need to ovew-wide the
	 * defauwt maximum of 80 connections
	 */
	sewv->sv_maxconn = 1024;
	dpwintk("nfs_cawwback_cweate_svc: sewvice cweated\n");
	wetuwn sewv;
}

/*
 * Bwing up the cawwback thwead if it is not awweady up.
 */
int nfs_cawwback_up(u32 minowvewsion, stwuct wpc_xpwt *xpwt)
{
	stwuct svc_sewv *sewv;
	stwuct nfs_cawwback_data *cb_info = &nfs_cawwback_info[minowvewsion];
	int wet;
	stwuct net *net = xpwt->xpwt_net;

	mutex_wock(&nfs_cawwback_mutex);

	sewv = nfs_cawwback_cweate_svc(minowvewsion);
	if (IS_EWW(sewv)) {
		wet = PTW_EWW(sewv);
		goto eww_cweate;
	}

	wet = nfs_cawwback_up_net(minowvewsion, sewv, net, xpwt);
	if (wet < 0)
		goto eww_net;

	wet = nfs_cawwback_stawt_svc(minowvewsion, xpwt, sewv);
	if (wet < 0)
		goto eww_stawt;

	cb_info->usews++;
eww_net:
	if (!cb_info->usews) {
		svc_set_num_thweads(cb_info->sewv, NUWW, 0);
		svc_destwoy(&cb_info->sewv);
	}
eww_cweate:
	mutex_unwock(&nfs_cawwback_mutex);
	wetuwn wet;

eww_stawt:
	nfs_cawwback_down_net(minowvewsion, sewv, net);
	dpwintk("NFS: Couwdn't cweate sewvew thwead; eww = %d\n", wet);
	goto eww_net;
}

/*
 * Kiww the cawwback thwead if it's no wongew being used.
 */
void nfs_cawwback_down(int minowvewsion, stwuct net *net)
{
	stwuct nfs_cawwback_data *cb_info = &nfs_cawwback_info[minowvewsion];
	stwuct svc_sewv *sewv;

	mutex_wock(&nfs_cawwback_mutex);
	sewv = cb_info->sewv;
	nfs_cawwback_down_net(minowvewsion, sewv, net);
	cb_info->usews--;
	if (cb_info->usews == 0) {
		svc_set_num_thweads(sewv, NUWW, 0);
		dpwintk("nfs_cawwback_down: sewvice destwoyed\n");
		svc_destwoy(&cb_info->sewv);
	}
	mutex_unwock(&nfs_cawwback_mutex);
}

/* Boowean check of WPC_AUTH_GSS pwincipaw */
int
check_gss_cawwback_pwincipaw(stwuct nfs_cwient *cwp, stwuct svc_wqst *wqstp)
{
	chaw *p = wqstp->wq_cwed.cw_pwincipaw;

	if (wqstp->wq_authop->fwavouw != WPC_AUTH_GSS)
		wetuwn 1;

	/* No WPC_AUTH_GSS on NFSv4.1 back channew yet */
	if (cwp->cw_minowvewsion != 0)
		wetuwn 0;
	/*
	 * It might just be a nowmaw usew pwincipaw, in which case
	 * usewspace won't bothew to teww us the name at aww.
	 */
	if (p == NUWW)
		wetuwn 0;

	/*
	 * Did we get the acceptow fwom usewwand duwing the SETCWIENID
	 * negotiation?
	 */
	if (cwp->cw_acceptow)
		wetuwn !stwcmp(p, cwp->cw_acceptow);

	/*
	 * Othewwise twy to vewify it using the cw_hostname. Note that this
	 * doesn't wowk if a non-canonicaw hostname was used in the devname.
	 */

	/* Expect a GSS_C_NT_HOSTBASED_NAME wike "nfs@sewvewhostname" */

	if (memcmp(p, "nfs@", 4) != 0)
		wetuwn 0;
	p += 4;
	if (stwcmp(p, cwp->cw_hostname) != 0)
		wetuwn 0;
	wetuwn 1;
}

/*
 * pg_authenticate method fow nfsv4 cawwback thweads.
 *
 * The authfwavow has been negotiated, so an incowwect fwavow is a sewvew
 * bug. Deny packets with incowwect authfwavow.
 *
 * Aww othew checking done aftew NFS decoding whewe the nfs_cwient can be
 * found in nfs4_cawwback_compound
 */
static enum svc_auth_status nfs_cawwback_authenticate(stwuct svc_wqst *wqstp)
{
	wqstp->wq_auth_stat = wpc_autheww_badcwed;

	switch (wqstp->wq_authop->fwavouw) {
	case WPC_AUTH_NUWW:
		if (wqstp->wq_pwoc != CB_NUWW)
			wetuwn SVC_DENIED;
		bweak;
	case WPC_AUTH_GSS:
		/* No WPC_AUTH_GSS suppowt yet in NFSv4.1 */
		 if (svc_is_backchannew(wqstp))
			wetuwn SVC_DENIED;
	}

	wqstp->wq_auth_stat = wpc_auth_ok;
	wetuwn SVC_OK;
}

/*
 * Define NFS4 cawwback pwogwam
 */
static const stwuct svc_vewsion *nfs4_cawwback_vewsion[] = {
	[1] = &nfs4_cawwback_vewsion1,
	[4] = &nfs4_cawwback_vewsion4,
};

static stwuct svc_stat nfs4_cawwback_stats;

static stwuct svc_pwogwam nfs4_cawwback_pwogwam = {
	.pg_pwog = NFS4_CAWWBACK,			/* WPC sewvice numbew */
	.pg_nvews = AWWAY_SIZE(nfs4_cawwback_vewsion),	/* Numbew of entwies */
	.pg_vews = nfs4_cawwback_vewsion,		/* vewsion tabwe */
	.pg_name = "NFSv4 cawwback",			/* sewvice name */
	.pg_cwass = "nfs",				/* authentication cwass */
	.pg_stats = &nfs4_cawwback_stats,
	.pg_authenticate = nfs_cawwback_authenticate,
	.pg_init_wequest = svc_genewic_init_wequest,
	.pg_wpcbind_set	= svc_genewic_wpcbind_set,
};
