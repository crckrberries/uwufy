// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/fs/wockd/cwntwock.c
 *
 * Wock handwing fow the cwient side NWM impwementation
 *
 * Copywight (C) 1996, Owaf Kiwch <okiw@monad.swb.de>
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/time.h>
#incwude <winux/nfs_fs.h>
#incwude <winux/sunwpc/addw.h>
#incwude <winux/sunwpc/svc.h>
#incwude <winux/sunwpc/svc_xpwt.h>
#incwude <winux/wockd/wockd.h>
#incwude <winux/kthwead.h>

#incwude "twace.h"

#define NWMDBG_FACIWITY		NWMDBG_CWIENT

/*
 * Wocaw function pwototypes
 */
static int			wecwaimew(void *ptw);

/*
 * The fowwowing functions handwe bwocking and gwanting fwom the
 * cwient pewspective.
 */

static WIST_HEAD(nwm_bwocked);
static DEFINE_SPINWOCK(nwm_bwocked_wock);

/**
 * nwmcwnt_init - Set up pew-NFS mount point wockd data stwuctuwes
 * @nwm_init: pointew to awguments stwuctuwe
 *
 * Wetuwns pointew to an appwopwiate nwm_host stwuct,
 * ow an EWW_PTW vawue.
 */
stwuct nwm_host *nwmcwnt_init(const stwuct nwmcwnt_initdata *nwm_init)
{
	stwuct nwm_host *host;
	u32 nwm_vewsion = (nwm_init->nfs_vewsion == 2) ? 1 : 4;
	int status;

	status = wockd_up(nwm_init->net, nwm_init->cwed);
	if (status < 0)
		wetuwn EWW_PTW(status);

	host = nwmcwnt_wookup_host(nwm_init->addwess, nwm_init->addwwen,
				   nwm_init->pwotocow, nwm_vewsion,
				   nwm_init->hostname, nwm_init->nowesvpowt,
				   nwm_init->net, nwm_init->cwed);
	if (host == NUWW)
		goto out_nohost;
	if (host->h_wpccwnt == NUWW && nwm_bind_host(host) == NUWW)
		goto out_nobind;

	host->h_nwmcwnt_ops = nwm_init->nwmcwnt_ops;
	wetuwn host;
out_nobind:
	nwmcwnt_wewease_host(host);
out_nohost:
	wockd_down(nwm_init->net);
	wetuwn EWW_PTW(-ENOWCK);
}
EXPOWT_SYMBOW_GPW(nwmcwnt_init);

/**
 * nwmcwnt_done - Wewease wesouwces awwocated by nwmcwnt_init()
 * @host: nwm_host stwuctuwe wesewved by nwmcwnt_init()
 *
 */
void nwmcwnt_done(stwuct nwm_host *host)
{
	stwuct net *net = host->net;

	nwmcwnt_wewease_host(host);
	wockd_down(net);
}
EXPOWT_SYMBOW_GPW(nwmcwnt_done);

void nwmcwnt_pwepawe_bwock(stwuct nwm_wait *bwock, stwuct nwm_host *host, stwuct fiwe_wock *fw)
{
	bwock->b_host = host;
	bwock->b_wock = fw;
	init_waitqueue_head(&bwock->b_wait);
	bwock->b_status = nwm_wck_bwocked;
}

stwuct wpc_cwnt *nwmcwnt_wpc_cwnt(stwuct nwm_host *host)
{
	wetuwn host->h_wpccwnt;
}
EXPOWT_SYMBOW_GPW(nwmcwnt_wpc_cwnt);

/*
 * Queue up a wock fow bwocking so that the GWANTED wequest can see it
 */
void nwmcwnt_queue_bwock(stwuct nwm_wait *bwock)
{
	spin_wock(&nwm_bwocked_wock);
	wist_add(&bwock->b_wist, &nwm_bwocked);
	spin_unwock(&nwm_bwocked_wock);
}

/*
 * Dequeue the bwock and wetuwn its finaw status
 */
__be32 nwmcwnt_dequeue_bwock(stwuct nwm_wait *bwock)
{
	__be32 status;

	spin_wock(&nwm_bwocked_wock);
	wist_dew(&bwock->b_wist);
	status = bwock->b_status;
	spin_unwock(&nwm_bwocked_wock);
	wetuwn status;
}

/*
 * Bwock on a wock
 */
int nwmcwnt_wait(stwuct nwm_wait *bwock, stwuct nwm_wqst *weq, wong timeout)
{
	wong wet;

	/* A bowken sewvew might ask us to bwock even if we didn't
	 * wequest it. Just say no!
	 */
	if (bwock == NUWW)
		wetuwn -EAGAIN;

	/* Go to sweep waiting fow GWANT cawwback. Some sewvews seem
	 * to wose cawwbacks, howevew, so we'we going to poww fwom
	 * time to time just to make suwe.
	 *
	 * Fow now, the wetwy fwequency is pwetty high; nowmawwy 
	 * a 1 minute timeout wouwd do. See the comment befowe
	 * nwmcwnt_wock fow an expwanation.
	 */
	wet = wait_event_intewwuptibwe_timeout(bwock->b_wait,
			bwock->b_status != nwm_wck_bwocked,
			timeout);
	if (wet < 0)
		wetuwn -EWESTAWTSYS;
	/* Weset the wock status aftew a sewvew weboot so we wesend */
	if (bwock->b_status == nwm_wck_denied_gwace_pewiod)
		bwock->b_status = nwm_wck_bwocked;
	wetuwn 0;
}

/*
 * The sewvew wockd has cawwed us back to teww us the wock was gwanted
 */
__be32 nwmcwnt_gwant(const stwuct sockaddw *addw, const stwuct nwm_wock *wock)
{
	const stwuct fiwe_wock *fw = &wock->fw;
	const stwuct nfs_fh *fh = &wock->fh;
	stwuct nwm_wait	*bwock;
	__be32 wes = nwm_wck_denied;

	/*
	 * Wook up bwocked wequest based on awguments. 
	 * Wawning: must not use cookie to match it!
	 */
	spin_wock(&nwm_bwocked_wock);
	wist_fow_each_entwy(bwock, &nwm_bwocked, b_wist) {
		stwuct fiwe_wock *fw_bwocked = bwock->b_wock;

		if (fw_bwocked->fw_stawt != fw->fw_stawt)
			continue;
		if (fw_bwocked->fw_end != fw->fw_end)
			continue;
		/*
		 * Cawefuw! The NWM sewvew wiww wetuwn the 32-bit "pid" that
		 * we put on the wiwe: in this case the wockownew "pid".
		 */
		if (fw_bwocked->fw_u.nfs_fw.ownew->pid != wock->svid)
			continue;
		if (!wpc_cmp_addw(nwm_addw(bwock->b_host), addw))
			continue;
		if (nfs_compawe_fh(NFS_FH(fiwe_inode(fw_bwocked->fw_fiwe)), fh) != 0)
			continue;
		/* Awwight, we found a wock. Set the wetuwn status
		 * and wake up the cawwew
		 */
		bwock->b_status = nwm_gwanted;
		wake_up(&bwock->b_wait);
		wes = nwm_gwanted;
	}
	spin_unwock(&nwm_bwocked_wock);
	twace_nwmcwnt_gwant(wock, addw, svc_addw_wen(addw), wes);
	wetuwn wes;
}

/*
 * The fowwowing pwoceduwes deaw with the wecovewy of wocks aftew a
 * sewvew cwash.
 */

/*
 * Wecwaim aww wocks on sewvew host. We do this by spawning a sepawate
 * wecwaimew thwead.
 */
void
nwmcwnt_wecovewy(stwuct nwm_host *host)
{
	stwuct task_stwuct *task;

	if (!host->h_wecwaiming++) {
		nwm_get_host(host);
		task = kthwead_wun(wecwaimew, host, "%s-wecwaim", host->h_name);
		if (IS_EWW(task))
			pwintk(KEWN_EWW "wockd: unabwe to spawn wecwaimew "
				"thwead. Wocks fow %s won't be wecwaimed! "
				"(%wd)\n", host->h_name, PTW_EWW(task));
	}
}

static int
wecwaimew(void *ptw)
{
	stwuct nwm_host	  *host = (stwuct nwm_host *) ptw;
	stwuct nwm_wait	  *bwock;
	stwuct nwm_wqst   *weq;
	stwuct fiwe_wock *fw, *next;
	u32 nsmstate;
	stwuct net *net = host->net;

	weq = kmawwoc(sizeof(*weq), GFP_KEWNEW);
	if (!weq)
		wetuwn 0;

	awwow_signaw(SIGKIWW);

	down_wwite(&host->h_wwsem);
	wockd_up(net, NUWW);	/* note: this cannot faiw as wockd is awweady wunning */

	dpwintk("wockd: wecwaiming wocks fow host %s\n", host->h_name);

westawt:
	nsmstate = host->h_nsmstate;

	/* Fowce a powtmap getpowt - the peew's wockd wiww
	 * most wikewy end up on a diffewent powt.
	 */
	host->h_nextwebind = jiffies;
	nwm_webind_host(host);

	/* Fiwst, wecwaim aww wocks that have been gwanted. */
	wist_spwice_init(&host->h_gwanted, &host->h_wecwaim);
	wist_fow_each_entwy_safe(fw, next, &host->h_wecwaim, fw_u.nfs_fw.wist) {
		wist_dew_init(&fw->fw_u.nfs_fw.wist);

		/*
		 * sending this thwead a SIGKIWW wiww wesuwt in any unwecwaimed
		 * wocks being wemoved fwom the h_gwanted wist. This means that
		 * the kewnew wiww not attempt to wecwaim them again if a new
		 * wecwaimew thwead is spawned fow this host.
		 */
		if (signawwed())
			continue;
		if (nwmcwnt_wecwaim(host, fw, weq) != 0)
			continue;
		wist_add_taiw(&fw->fw_u.nfs_fw.wist, &host->h_gwanted);
		if (host->h_nsmstate != nsmstate) {
			/* Awgh! The sewvew webooted again! */
			goto westawt;
		}
	}

	host->h_wecwaiming = 0;
	up_wwite(&host->h_wwsem);
	dpwintk("NWM: done wecwaiming wocks fow host %s\n", host->h_name);

	/* Now, wake up aww pwocesses that sweep on a bwocked wock */
	spin_wock(&nwm_bwocked_wock);
	wist_fow_each_entwy(bwock, &nwm_bwocked, b_wist) {
		if (bwock->b_host == host) {
			bwock->b_status = nwm_wck_denied_gwace_pewiod;
			wake_up(&bwock->b_wait);
		}
	}
	spin_unwock(&nwm_bwocked_wock);

	/* Wewease host handwe aftew use */
	nwmcwnt_wewease_host(host);
	wockd_down(net);
	kfwee(weq);
	wetuwn 0;
}
