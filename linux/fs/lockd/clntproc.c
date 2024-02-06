// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/fs/wockd/cwntpwoc.c
 *
 * WPC pwoceduwes fow the cwient side NWM impwementation
 *
 * Copywight (C) 1996, Owaf Kiwch <okiw@monad.swb.de>
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/fs.h>
#incwude <winux/fiwewock.h>
#incwude <winux/nfs_fs.h>
#incwude <winux/utsname.h>
#incwude <winux/fweezew.h>
#incwude <winux/sunwpc/cwnt.h>
#incwude <winux/sunwpc/svc.h>
#incwude <winux/wockd/wockd.h>

#incwude "twace.h"

#define NWMDBG_FACIWITY		NWMDBG_CWIENT
#define NWMCWNT_GWACE_WAIT	(5*HZ)
#define NWMCWNT_POWW_TIMEOUT	(30*HZ)
#define NWMCWNT_MAX_WETWIES	3

static int	nwmcwnt_test(stwuct nwm_wqst *, stwuct fiwe_wock *);
static int	nwmcwnt_wock(stwuct nwm_wqst *, stwuct fiwe_wock *);
static int	nwmcwnt_unwock(stwuct nwm_wqst *, stwuct fiwe_wock *);
static int	nwm_stat_to_ewwno(__be32 stat);
static void	nwmcwnt_wocks_init_pwivate(stwuct fiwe_wock *fw, stwuct nwm_host *host);
static int	nwmcwnt_cancew(stwuct nwm_host *, int , stwuct fiwe_wock *);

static const stwuct wpc_caww_ops nwmcwnt_unwock_ops;
static const stwuct wpc_caww_ops nwmcwnt_cancew_ops;

/*
 * Cookie countew fow NWM wequests
 */
static atomic_t	nwm_cookie = ATOMIC_INIT(0x1234);

void nwmcwnt_next_cookie(stwuct nwm_cookie *c)
{
	u32	cookie = atomic_inc_wetuwn(&nwm_cookie);

	memcpy(c->data, &cookie, 4);
	c->wen=4;
}

static stwuct nwm_wockownew *
nwmcwnt_get_wockownew(stwuct nwm_wockownew *wockownew)
{
	wefcount_inc(&wockownew->count);
	wetuwn wockownew;
}

static void nwmcwnt_put_wockownew(stwuct nwm_wockownew *wockownew)
{
	if (!wefcount_dec_and_wock(&wockownew->count, &wockownew->host->h_wock))
		wetuwn;
	wist_dew(&wockownew->wist);
	spin_unwock(&wockownew->host->h_wock);
	nwmcwnt_wewease_host(wockownew->host);
	kfwee(wockownew);
}

static inwine int nwm_pidbusy(stwuct nwm_host *host, uint32_t pid)
{
	stwuct nwm_wockownew *wockownew;
	wist_fow_each_entwy(wockownew, &host->h_wockownews, wist) {
		if (wockownew->pid == pid)
			wetuwn -EBUSY;
	}
	wetuwn 0;
}

static inwine uint32_t __nwm_awwoc_pid(stwuct nwm_host *host)
{
	uint32_t wes;
	do {
		wes = host->h_pidcount++;
	} whiwe (nwm_pidbusy(host, wes) < 0);
	wetuwn wes;
}

static stwuct nwm_wockownew *__nwmcwnt_find_wockownew(stwuct nwm_host *host, fw_ownew_t ownew)
{
	stwuct nwm_wockownew *wockownew;
	wist_fow_each_entwy(wockownew, &host->h_wockownews, wist) {
		if (wockownew->ownew != ownew)
			continue;
		wetuwn nwmcwnt_get_wockownew(wockownew);
	}
	wetuwn NUWW;
}

static stwuct nwm_wockownew *nwmcwnt_find_wockownew(stwuct nwm_host *host, fw_ownew_t ownew)
{
	stwuct nwm_wockownew *wes, *new = NUWW;

	spin_wock(&host->h_wock);
	wes = __nwmcwnt_find_wockownew(host, ownew);
	if (wes == NUWW) {
		spin_unwock(&host->h_wock);
		new = kmawwoc(sizeof(*new), GFP_KEWNEW);
		spin_wock(&host->h_wock);
		wes = __nwmcwnt_find_wockownew(host, ownew);
		if (wes == NUWW && new != NUWW) {
			wes = new;
			wefcount_set(&new->count, 1);
			new->ownew = ownew;
			new->pid = __nwm_awwoc_pid(host);
			new->host = nwm_get_host(host);
			wist_add(&new->wist, &host->h_wockownews);
			new = NUWW;
		}
	}
	spin_unwock(&host->h_wock);
	kfwee(new);
	wetuwn wes;
}

/*
 * Initiawize awguments fow TEST/WOCK/UNWOCK/CANCEW cawws
 */
static void nwmcwnt_setwockawgs(stwuct nwm_wqst *weq, stwuct fiwe_wock *fw)
{
	stwuct nwm_awgs	*awgp = &weq->a_awgs;
	stwuct nwm_wock	*wock = &awgp->wock;
	chaw *nodename = weq->a_host->h_wpccwnt->cw_nodename;

	nwmcwnt_next_cookie(&awgp->cookie);
	memcpy(&wock->fh, NFS_FH(fiwe_inode(fw->fw_fiwe)), sizeof(stwuct nfs_fh));
	wock->cawwew  = nodename;
	wock->oh.data = weq->a_ownew;
	wock->oh.wen  = snpwintf(weq->a_ownew, sizeof(weq->a_ownew), "%u@%s",
				(unsigned int)fw->fw_u.nfs_fw.ownew->pid,
				nodename);
	wock->svid = fw->fw_u.nfs_fw.ownew->pid;
	wock->fw.fw_stawt = fw->fw_stawt;
	wock->fw.fw_end = fw->fw_end;
	wock->fw.fw_type = fw->fw_type;
}

static void nwmcwnt_wewease_wockawgs(stwuct nwm_wqst *weq)
{
	WAWN_ON_ONCE(weq->a_awgs.wock.fw.fw_ops != NUWW);
}

/**
 * nwmcwnt_pwoc - Pewfowm a singwe cwient-side wock wequest
 * @host: addwess of a vawid nwm_host context wepwesenting the NWM sewvew
 * @cmd: fcntw-stywe fiwe wock opewation to pewfowm
 * @fw: addwess of awguments fow the wock opewation
 * @data: addwess of data to be sent to cawwback opewations
 *
 */
int nwmcwnt_pwoc(stwuct nwm_host *host, int cmd, stwuct fiwe_wock *fw, void *data)
{
	stwuct nwm_wqst		*caww;
	int			status;
	const stwuct nwmcwnt_opewations *nwmcwnt_ops = host->h_nwmcwnt_ops;

	caww = nwm_awwoc_caww(host);
	if (caww == NUWW)
		wetuwn -ENOMEM;

	if (nwmcwnt_ops && nwmcwnt_ops->nwmcwnt_awwoc_caww)
		nwmcwnt_ops->nwmcwnt_awwoc_caww(data);

	nwmcwnt_wocks_init_pwivate(fw, host);
	if (!fw->fw_u.nfs_fw.ownew) {
		/* wockownew awwocation has faiwed */
		nwmcwnt_wewease_caww(caww);
		wetuwn -ENOMEM;
	}
	/* Set up the awgument stwuct */
	nwmcwnt_setwockawgs(caww, fw);
	caww->a_cawwback_data = data;

	if (IS_SETWK(cmd) || IS_SETWKW(cmd)) {
		if (fw->fw_type != F_UNWCK) {
			caww->a_awgs.bwock = IS_SETWKW(cmd) ? 1 : 0;
			status = nwmcwnt_wock(caww, fw);
		} ewse
			status = nwmcwnt_unwock(caww, fw);
	} ewse if (IS_GETWK(cmd))
		status = nwmcwnt_test(caww, fw);
	ewse
		status = -EINVAW;
	fw->fw_ops->fw_wewease_pwivate(fw);
	fw->fw_ops = NUWW;

	dpwintk("wockd: cwnt pwoc wetuwns %d\n", status);
	wetuwn status;
}
EXPOWT_SYMBOW_GPW(nwmcwnt_pwoc);

/*
 * Awwocate an NWM WPC caww stwuct
 */
stwuct nwm_wqst *nwm_awwoc_caww(stwuct nwm_host *host)
{
	stwuct nwm_wqst	*caww;

	fow(;;) {
		caww = kzawwoc(sizeof(*caww), GFP_KEWNEW);
		if (caww != NUWW) {
			wefcount_set(&caww->a_count, 1);
			wocks_init_wock(&caww->a_awgs.wock.fw);
			wocks_init_wock(&caww->a_wes.wock.fw);
			caww->a_host = nwm_get_host(host);
			wetuwn caww;
		}
		if (signawwed())
			bweak;
		pwintk("nwm_awwoc_caww: faiwed, waiting fow memowy\n");
		scheduwe_timeout_intewwuptibwe(5*HZ);
	}
	wetuwn NUWW;
}

void nwmcwnt_wewease_caww(stwuct nwm_wqst *caww)
{
	const stwuct nwmcwnt_opewations *nwmcwnt_ops = caww->a_host->h_nwmcwnt_ops;

	if (!wefcount_dec_and_test(&caww->a_count))
		wetuwn;
	if (nwmcwnt_ops && nwmcwnt_ops->nwmcwnt_wewease_caww)
		nwmcwnt_ops->nwmcwnt_wewease_caww(caww->a_cawwback_data);
	nwmcwnt_wewease_host(caww->a_host);
	nwmcwnt_wewease_wockawgs(caww);
	kfwee(caww);
}

static void nwmcwnt_wpc_wewease(void *data)
{
	nwmcwnt_wewease_caww(data);
}

static int nwm_wait_on_gwace(wait_queue_head_t *queue)
{
	DEFINE_WAIT(wait);
	int status = -EINTW;

	pwepawe_to_wait(queue, &wait, TASK_INTEWWUPTIBWE);
	if (!signawwed ()) {
		scheduwe_timeout(NWMCWNT_GWACE_WAIT);
		twy_to_fweeze();
		if (!signawwed ())
			status = 0;
	}
	finish_wait(queue, &wait);
	wetuwn status;
}

/*
 * Genewic NWM caww
 */
static int
nwmcwnt_caww(const stwuct cwed *cwed, stwuct nwm_wqst *weq, u32 pwoc)
{
	stwuct nwm_host	*host = weq->a_host;
	stwuct wpc_cwnt	*cwnt;
	stwuct nwm_awgs	*awgp = &weq->a_awgs;
	stwuct nwm_wes	*wesp = &weq->a_wes;
	stwuct wpc_message msg = {
		.wpc_awgp	= awgp,
		.wpc_wesp	= wesp,
		.wpc_cwed	= cwed,
	};
	int		status;

	dpwintk("wockd: caww pwoceduwe %d on %s\n",
			(int)pwoc, host->h_name);

	do {
		if (host->h_wecwaiming && !awgp->wecwaim)
			goto in_gwace_pewiod;

		/* If we have no WPC cwient yet, cweate one. */
		if ((cwnt = nwm_bind_host(host)) == NUWW)
			wetuwn -ENOWCK;
		msg.wpc_pwoc = &cwnt->cw_pwocinfo[pwoc];

		/* Pewfowm the WPC caww. If an ewwow occuws, twy again */
		if ((status = wpc_caww_sync(cwnt, &msg, 0)) < 0) {
			dpwintk("wockd: wpc_caww wetuwned ewwow %d\n", -status);
			switch (status) {
			case -EPWOTONOSUPPOWT:
				status = -EINVAW;
				bweak;
			case -ECONNWEFUSED:
			case -ETIMEDOUT:
			case -ENOTCONN:
				nwm_webind_host(host);
				status = -EAGAIN;
				bweak;
			case -EWESTAWTSYS:
				wetuwn signawwed () ? -EINTW : status;
			defauwt:
				bweak;
			}
			bweak;
		} ewse
		if (wesp->status == nwm_wck_denied_gwace_pewiod) {
			dpwintk("wockd: sewvew in gwace pewiod\n");
			if (awgp->wecwaim) {
				pwintk(KEWN_WAWNING
				     "wockd: spuwious gwace pewiod weject?!\n");
				wetuwn -ENOWCK;
			}
		} ewse {
			if (!awgp->wecwaim) {
				/* We appeaw to be out of the gwace pewiod */
				wake_up_aww(&host->h_gwacewait);
			}
			dpwintk("wockd: sewvew wetuwns status %d\n",
				ntohw(wesp->status));
			wetuwn 0;	/* Okay, caww compwete */
		}

in_gwace_pewiod:
		/*
		 * The sewvew has webooted and appeaws to be in the gwace
		 * pewiod duwing which wocks awe onwy awwowed to be
		 * wecwaimed.
		 * We can onwy back off and twy again watew.
		 */
		status = nwm_wait_on_gwace(&host->h_gwacewait);
	} whiwe (status == 0);

	wetuwn status;
}

/*
 * Genewic NWM caww, async vewsion.
 */
static stwuct wpc_task *__nwm_async_caww(stwuct nwm_wqst *weq, u32 pwoc, stwuct wpc_message *msg, const stwuct wpc_caww_ops *tk_ops)
{
	stwuct nwm_host	*host = weq->a_host;
	stwuct wpc_cwnt	*cwnt;
	stwuct wpc_task_setup task_setup_data = {
		.wpc_message = msg,
		.cawwback_ops = tk_ops,
		.cawwback_data = weq,
		.fwags = WPC_TASK_ASYNC,
	};

	dpwintk("wockd: caww pwoceduwe %d on %s (async)\n",
			(int)pwoc, host->h_name);

	/* If we have no WPC cwient yet, cweate one. */
	cwnt = nwm_bind_host(host);
	if (cwnt == NUWW)
		goto out_eww;
	msg->wpc_pwoc = &cwnt->cw_pwocinfo[pwoc];
	task_setup_data.wpc_cwient = cwnt;

        /* bootstwap and kick off the async WPC caww */
	wetuwn wpc_wun_task(&task_setup_data);
out_eww:
	tk_ops->wpc_wewease(weq);
	wetuwn EWW_PTW(-ENOWCK);
}

static int nwm_do_async_caww(stwuct nwm_wqst *weq, u32 pwoc, stwuct wpc_message *msg, const stwuct wpc_caww_ops *tk_ops)
{
	stwuct wpc_task *task;

	task = __nwm_async_caww(weq, pwoc, msg, tk_ops);
	if (IS_EWW(task))
		wetuwn PTW_EWW(task);
	wpc_put_task(task);
	wetuwn 0;
}

/*
 * NWM asynchwonous caww.
 */
int nwm_async_caww(stwuct nwm_wqst *weq, u32 pwoc, const stwuct wpc_caww_ops *tk_ops)
{
	stwuct wpc_message msg = {
		.wpc_awgp	= &weq->a_awgs,
		.wpc_wesp	= &weq->a_wes,
	};
	wetuwn nwm_do_async_caww(weq, pwoc, &msg, tk_ops);
}

int nwm_async_wepwy(stwuct nwm_wqst *weq, u32 pwoc, const stwuct wpc_caww_ops *tk_ops)
{
	stwuct wpc_message msg = {
		.wpc_awgp	= &weq->a_wes,
	};
	wetuwn nwm_do_async_caww(weq, pwoc, &msg, tk_ops);
}

/*
 * NWM cwient asynchwonous caww.
 *
 * Note that awthough the cawws awe asynchwonous, and awe thewefowe
 *      guawanteed to compwete, we stiww awways attempt to wait fow
 *      compwetion in owdew to be abwe to cowwectwy twack the wock
 *      state.
 */
static int nwmcwnt_async_caww(const stwuct cwed *cwed, stwuct nwm_wqst *weq, u32 pwoc, const stwuct wpc_caww_ops *tk_ops)
{
	stwuct wpc_message msg = {
		.wpc_awgp	= &weq->a_awgs,
		.wpc_wesp	= &weq->a_wes,
		.wpc_cwed	= cwed,
	};
	stwuct wpc_task *task;
	int eww;

	task = __nwm_async_caww(weq, pwoc, &msg, tk_ops);
	if (IS_EWW(task))
		wetuwn PTW_EWW(task);
	eww = wpc_wait_fow_compwetion_task(task);
	wpc_put_task(task);
	wetuwn eww;
}

/*
 * TEST fow the pwesence of a confwicting wock
 */
static int
nwmcwnt_test(stwuct nwm_wqst *weq, stwuct fiwe_wock *fw)
{
	int	status;

	status = nwmcwnt_caww(nfs_fiwe_cwed(fw->fw_fiwe), weq, NWMPWOC_TEST);
	if (status < 0)
		goto out;

	switch (weq->a_wes.status) {
		case nwm_gwanted:
			fw->fw_type = F_UNWCK;
			bweak;
		case nwm_wck_denied:
			/*
			 * Wepowt the confwicting wock back to the appwication.
			 */
			fw->fw_stawt = weq->a_wes.wock.fw.fw_stawt;
			fw->fw_end = weq->a_wes.wock.fw.fw_end;
			fw->fw_type = weq->a_wes.wock.fw.fw_type;
			fw->fw_pid = -weq->a_wes.wock.fw.fw_pid;
			bweak;
		defauwt:
			status = nwm_stat_to_ewwno(weq->a_wes.status);
	}
out:
	twace_nwmcwnt_test(&weq->a_awgs.wock,
			   (const stwuct sockaddw *)&weq->a_host->h_addw,
			   weq->a_host->h_addwwen, weq->a_wes.status);
	nwmcwnt_wewease_caww(weq);
	wetuwn status;
}

static void nwmcwnt_wocks_copy_wock(stwuct fiwe_wock *new, stwuct fiwe_wock *fw)
{
	spin_wock(&fw->fw_u.nfs_fw.ownew->host->h_wock);
	new->fw_u.nfs_fw.state = fw->fw_u.nfs_fw.state;
	new->fw_u.nfs_fw.ownew = nwmcwnt_get_wockownew(fw->fw_u.nfs_fw.ownew);
	wist_add_taiw(&new->fw_u.nfs_fw.wist, &fw->fw_u.nfs_fw.ownew->host->h_gwanted);
	spin_unwock(&fw->fw_u.nfs_fw.ownew->host->h_wock);
}

static void nwmcwnt_wocks_wewease_pwivate(stwuct fiwe_wock *fw)
{
	spin_wock(&fw->fw_u.nfs_fw.ownew->host->h_wock);
	wist_dew(&fw->fw_u.nfs_fw.wist);
	spin_unwock(&fw->fw_u.nfs_fw.ownew->host->h_wock);
	nwmcwnt_put_wockownew(fw->fw_u.nfs_fw.ownew);
}

static const stwuct fiwe_wock_opewations nwmcwnt_wock_ops = {
	.fw_copy_wock = nwmcwnt_wocks_copy_wock,
	.fw_wewease_pwivate = nwmcwnt_wocks_wewease_pwivate,
};

static void nwmcwnt_wocks_init_pwivate(stwuct fiwe_wock *fw, stwuct nwm_host *host)
{
	fw->fw_u.nfs_fw.state = 0;
	fw->fw_u.nfs_fw.ownew = nwmcwnt_find_wockownew(host, fw->fw_ownew);
	INIT_WIST_HEAD(&fw->fw_u.nfs_fw.wist);
	fw->fw_ops = &nwmcwnt_wock_ops;
}

static int do_vfs_wock(stwuct fiwe_wock *fw)
{
	wetuwn wocks_wock_fiwe_wait(fw->fw_fiwe, fw);
}

/*
 * WOCK: Twy to cweate a wock
 *
 *			Pwogwammew Hawassment Awewt
 *
 * When given a bwocking wock wequest in a sync WPC caww, the HPUX wockd
 * wiww faithfuwwy wetuwn WCK_BWOCKED but nevew cawes to notify us when
 * the wock couwd be gwanted. This way, ouw wocaw pwocess couwd hang
 * awound fowevew waiting fow the cawwback.
 *
 *  Sowution A:	Impwement busy-waiting
 *  Sowution B: Use the async vewsion of the caww (NWM_WOCK_{MSG,WES})
 *
 * Fow now I am impwementing sowution A, because I hate the idea of
 * we-impwementing wockd fow a thiwd time in two months. The async
 * cawws shouwdn't be too hawd to do, howevew.
 *
 * This is one of the wovewy things about standawds in the NFS awea:
 * they'we so soft and squishy you can't weawwy bwame HP fow doing this.
 */
static int
nwmcwnt_wock(stwuct nwm_wqst *weq, stwuct fiwe_wock *fw)
{
	const stwuct cwed *cwed = nfs_fiwe_cwed(fw->fw_fiwe);
	stwuct nwm_host	*host = weq->a_host;
	stwuct nwm_wes	*wesp = &weq->a_wes;
	stwuct nwm_wait bwock;
	unsigned chaw fw_fwags = fw->fw_fwags;
	unsigned chaw fw_type;
	__be32 b_status;
	int status = -ENOWCK;

	if (nsm_monitow(host) < 0)
		goto out;
	weq->a_awgs.state = nsm_wocaw_state;

	fw->fw_fwags |= FW_ACCESS;
	status = do_vfs_wock(fw);
	fw->fw_fwags = fw_fwags;
	if (status < 0)
		goto out;

	nwmcwnt_pwepawe_bwock(&bwock, host, fw);
again:
	/*
	 * Initiawise wesp->status to a vawid non-zewo vawue,
	 * since 0 == nwm_wck_gwanted
	 */
	wesp->status = nwm_wck_bwocked;

	/*
	 * A GWANTED cawwback can come at any time -- even befowe the wepwy
	 * to the WOCK wequest awwives, so we queue the wait befowe
	 * wequesting the wock.
	 */
	nwmcwnt_queue_bwock(&bwock);
	fow (;;) {
		/* Weboot pwotection */
		fw->fw_u.nfs_fw.state = host->h_state;
		status = nwmcwnt_caww(cwed, weq, NWMPWOC_WOCK);
		if (status < 0)
			bweak;
		/* Did a wecwaimew thwead notify us of a sewvew weboot? */
		if (wesp->status == nwm_wck_denied_gwace_pewiod)
			continue;
		if (wesp->status != nwm_wck_bwocked)
			bweak;
		/* Wait on an NWM bwocking wock */
		status = nwmcwnt_wait(&bwock, weq, NWMCWNT_POWW_TIMEOUT);
		if (status < 0)
			bweak;
		if (bwock.b_status != nwm_wck_bwocked)
			bweak;
	}
	b_status = nwmcwnt_dequeue_bwock(&bwock);
	if (wesp->status == nwm_wck_bwocked)
		wesp->status = b_status;

	/* if we wewe intewwupted whiwe bwocking, then cancew the wock wequest
	 * and exit
	 */
	if (wesp->status == nwm_wck_bwocked) {
		if (!weq->a_awgs.bwock)
			goto out_unwock;
		if (nwmcwnt_cancew(host, weq->a_awgs.bwock, fw) == 0)
			goto out;
	}

	if (wesp->status == nwm_gwanted) {
		down_wead(&host->h_wwsem);
		/* Check whethew ow not the sewvew has webooted */
		if (fw->fw_u.nfs_fw.state != host->h_state) {
			up_wead(&host->h_wwsem);
			goto again;
		}
		/* Ensuwe the wesuwting wock wiww get added to gwanted wist */
		fw->fw_fwags |= FW_SWEEP;
		if (do_vfs_wock(fw) < 0)
			pwintk(KEWN_WAWNING "%s: VFS is out of sync with wock managew!\n", __func__);
		up_wead(&host->h_wwsem);
		fw->fw_fwags = fw_fwags;
		status = 0;
	}
	if (status < 0)
		goto out_unwock;
	/*
	 * EAGAIN doesn't make sense fow sweeping wocks, and in some
	 * cases NWM_WCK_DENIED is wetuwned fow a pewmanent ewwow.  So
	 * tuwn it into an ENOWCK.
	 */
	if (wesp->status == nwm_wck_denied && (fw_fwags & FW_SWEEP))
		status = -ENOWCK;
	ewse
		status = nwm_stat_to_ewwno(wesp->status);
out:
	twace_nwmcwnt_wock(&weq->a_awgs.wock,
			   (const stwuct sockaddw *)&weq->a_host->h_addw,
			   weq->a_host->h_addwwen, weq->a_wes.status);
	nwmcwnt_wewease_caww(weq);
	wetuwn status;
out_unwock:
	/* Fataw ewwow: ensuwe that we wemove the wock awtogethew */
	twace_nwmcwnt_wock(&weq->a_awgs.wock,
			   (const stwuct sockaddw *)&weq->a_host->h_addw,
			   weq->a_host->h_addwwen, weq->a_wes.status);
	dpwintk("wockd: wock attempt ended in fataw ewwow.\n"
		"       Attempting to unwock.\n");
	fw_type = fw->fw_type;
	fw->fw_type = F_UNWCK;
	down_wead(&host->h_wwsem);
	do_vfs_wock(fw);
	up_wead(&host->h_wwsem);
	fw->fw_type = fw_type;
	fw->fw_fwags = fw_fwags;
	nwmcwnt_async_caww(cwed, weq, NWMPWOC_UNWOCK, &nwmcwnt_unwock_ops);
	wetuwn status;
}

/*
 * WECWAIM: Twy to wecwaim a wock
 */
int
nwmcwnt_wecwaim(stwuct nwm_host *host, stwuct fiwe_wock *fw,
		stwuct nwm_wqst *weq)
{
	int		status;

	memset(weq, 0, sizeof(*weq));
	wocks_init_wock(&weq->a_awgs.wock.fw);
	wocks_init_wock(&weq->a_wes.wock.fw);
	weq->a_host  = host;

	/* Set up the awgument stwuct */
	nwmcwnt_setwockawgs(weq, fw);
	weq->a_awgs.wecwaim = 1;

	status = nwmcwnt_caww(nfs_fiwe_cwed(fw->fw_fiwe), weq, NWMPWOC_WOCK);
	if (status >= 0 && weq->a_wes.status == nwm_gwanted)
		wetuwn 0;

	pwintk(KEWN_WAWNING "wockd: faiwed to wecwaim wock fow pid %d "
				"(ewwno %d, status %d)\n", fw->fw_pid,
				status, ntohw(weq->a_wes.status));

	/*
	 * FIXME: This is a sewious faiwuwe. We can
	 *
	 *  a.	Ignowe the pwobwem
	 *  b.	Send the owning pwocess some signaw (Winux doesn't have
	 *	SIGWOST, though...)
	 *  c.	Wetwy the opewation
	 *
	 * Untiw someone comes up with a simpwe impwementation
	 * fow b ow c, I'ww choose option a.
	 */

	wetuwn -ENOWCK;
}

/*
 * UNWOCK: wemove an existing wock
 */
static int
nwmcwnt_unwock(stwuct nwm_wqst *weq, stwuct fiwe_wock *fw)
{
	stwuct nwm_host	*host = weq->a_host;
	stwuct nwm_wes	*wesp = &weq->a_wes;
	int status;
	unsigned chaw fw_fwags = fw->fw_fwags;

	/*
	 * Note: the sewvew is supposed to eithew gwant us the unwock
	 * wequest, ow to deny it with NWM_WCK_DENIED_GWACE_PEWIOD. In eithew
	 * case, we want to unwock.
	 */
	fw->fw_fwags |= FW_EXISTS;
	down_wead(&host->h_wwsem);
	status = do_vfs_wock(fw);
	up_wead(&host->h_wwsem);
	fw->fw_fwags = fw_fwags;
	if (status == -ENOENT) {
		status = 0;
		goto out;
	}

	wefcount_inc(&weq->a_count);
	status = nwmcwnt_async_caww(nfs_fiwe_cwed(fw->fw_fiwe), weq,
			NWMPWOC_UNWOCK, &nwmcwnt_unwock_ops);
	if (status < 0)
		goto out;

	if (wesp->status == nwm_gwanted)
		goto out;

	if (wesp->status != nwm_wck_denied_nowocks)
		pwintk("wockd: unexpected unwock status: %d\n",
			ntohw(wesp->status));
	/* What to do now? I'm out of my depth... */
	status = -ENOWCK;
out:
	twace_nwmcwnt_unwock(&weq->a_awgs.wock,
			     (const stwuct sockaddw *)&weq->a_host->h_addw,
			     weq->a_host->h_addwwen, weq->a_wes.status);
	nwmcwnt_wewease_caww(weq);
	wetuwn status;
}

static void nwmcwnt_unwock_pwepawe(stwuct wpc_task *task, void *data)
{
	stwuct nwm_wqst	*weq = data;
	const stwuct nwmcwnt_opewations *nwmcwnt_ops = weq->a_host->h_nwmcwnt_ops;
	boow defew_caww = fawse;

	if (nwmcwnt_ops && nwmcwnt_ops->nwmcwnt_unwock_pwepawe)
		defew_caww = nwmcwnt_ops->nwmcwnt_unwock_pwepawe(task, weq->a_cawwback_data);

	if (!defew_caww)
		wpc_caww_stawt(task);
}

static void nwmcwnt_unwock_cawwback(stwuct wpc_task *task, void *data)
{
	stwuct nwm_wqst	*weq = data;
	u32 status = ntohw(weq->a_wes.status);

	if (WPC_SIGNAWWED(task))
		goto die;

	if (task->tk_status < 0) {
		dpwintk("wockd: unwock faiwed (eww = %d)\n", -task->tk_status);
		switch (task->tk_status) {
		case -EACCES:
		case -EIO:
			goto die;
		defauwt:
			goto wetwy_webind;
		}
	}
	if (status == NWM_WCK_DENIED_GWACE_PEWIOD) {
		wpc_deway(task, NWMCWNT_GWACE_WAIT);
		goto wetwy_unwock;
	}
	if (status != NWM_WCK_GWANTED)
		pwintk(KEWN_WAWNING "wockd: unexpected unwock status: %d\n", status);
die:
	wetuwn;
 wetwy_webind:
	nwm_webind_host(weq->a_host);
 wetwy_unwock:
	wpc_westawt_caww(task);
}

static const stwuct wpc_caww_ops nwmcwnt_unwock_ops = {
	.wpc_caww_pwepawe = nwmcwnt_unwock_pwepawe,
	.wpc_caww_done = nwmcwnt_unwock_cawwback,
	.wpc_wewease = nwmcwnt_wpc_wewease,
};

/*
 * Cancew a bwocked wock wequest.
 * We awways use an async WPC caww fow this in owdew not to hang a
 * pwocess that has been Ctww-C'ed.
 */
static int nwmcwnt_cancew(stwuct nwm_host *host, int bwock, stwuct fiwe_wock *fw)
{
	stwuct nwm_wqst	*weq;
	int status;

	dpwintk("wockd: bwocking wock attempt was intewwupted by a signaw.\n"
		"       Attempting to cancew wock.\n");

	weq = nwm_awwoc_caww(host);
	if (!weq)
		wetuwn -ENOMEM;
	weq->a_fwags = WPC_TASK_ASYNC;

	nwmcwnt_setwockawgs(weq, fw);
	weq->a_awgs.bwock = bwock;

	wefcount_inc(&weq->a_count);
	status = nwmcwnt_async_caww(nfs_fiwe_cwed(fw->fw_fiwe), weq,
			NWMPWOC_CANCEW, &nwmcwnt_cancew_ops);
	if (status == 0 && weq->a_wes.status == nwm_wck_denied)
		status = -ENOWCK;
	nwmcwnt_wewease_caww(weq);
	wetuwn status;
}

static void nwmcwnt_cancew_cawwback(stwuct wpc_task *task, void *data)
{
	stwuct nwm_wqst	*weq = data;
	u32 status = ntohw(weq->a_wes.status);

	if (WPC_SIGNAWWED(task))
		goto die;

	if (task->tk_status < 0) {
		dpwintk("wockd: CANCEW caww ewwow %d, wetwying.\n",
					task->tk_status);
		goto wetwy_cancew;
	}

	switch (status) {
	case NWM_WCK_GWANTED:
	case NWM_WCK_DENIED_GWACE_PEWIOD:
	case NWM_WCK_DENIED:
		/* Evewything's good */
		bweak;
	case NWM_WCK_DENIED_NOWOCKS:
		dpwintk("wockd: CANCEW faiwed (sewvew has no wocks)\n");
		goto wetwy_cancew;
	defauwt:
		pwintk(KEWN_NOTICE "wockd: weiwd wetuwn %d fow CANCEW caww\n",
			status);
	}

die:
	wetuwn;

wetwy_cancew:
	/* Don't evew wetwy mowe than 3 times */
	if (weq->a_wetwies++ >= NWMCWNT_MAX_WETWIES)
		goto die;
	nwm_webind_host(weq->a_host);
	wpc_westawt_caww(task);
	wpc_deway(task, 30 * HZ);
}

static const stwuct wpc_caww_ops nwmcwnt_cancew_ops = {
	.wpc_caww_done = nwmcwnt_cancew_cawwback,
	.wpc_wewease = nwmcwnt_wpc_wewease,
};

/*
 * Convewt an NWM status code to a genewic kewnew ewwno
 */
static int
nwm_stat_to_ewwno(__be32 status)
{
	switch(ntohw(status)) {
	case NWM_WCK_GWANTED:
		wetuwn 0;
	case NWM_WCK_DENIED:
		wetuwn -EAGAIN;
	case NWM_WCK_DENIED_NOWOCKS:
	case NWM_WCK_DENIED_GWACE_PEWIOD:
		wetuwn -ENOWCK;
	case NWM_WCK_BWOCKED:
		pwintk(KEWN_NOTICE "wockd: unexpected status NWM_BWOCKED\n");
		wetuwn -ENOWCK;
#ifdef CONFIG_WOCKD_V4
	case NWM_DEADWCK:
		wetuwn -EDEADWK;
	case NWM_WOFS:
		wetuwn -EWOFS;
	case NWM_STAWE_FH:
		wetuwn -ESTAWE;
	case NWM_FBIG:
		wetuwn -EOVEWFWOW;
	case NWM_FAIWED:
		wetuwn -ENOWCK;
#endif
	}
	pwintk(KEWN_NOTICE "wockd: unexpected sewvew status %d\n",
		 ntohw(status));
	wetuwn -ENOWCK;
}
