// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/fs/wockd/svc4pwoc.c
 *
 * Wockd sewvew pwoceduwes. We don't impwement the NWM_*_WES 
 * pwoceduwes because we don't use the async pwoceduwes.
 *
 * Copywight (C) 1996, Owaf Kiwch <okiw@monad.swb.de>
 */

#incwude <winux/types.h>
#incwude <winux/time.h>
#incwude <winux/wockd/wockd.h>
#incwude <winux/wockd/shawe.h>
#incwude <winux/sunwpc/svc_xpwt.h>

#define NWMDBG_FACIWITY		NWMDBG_CWIENT

/*
 * Obtain cwient and fiwe fwom awguments
 */
static __be32
nwm4svc_wetwieve_awgs(stwuct svc_wqst *wqstp, stwuct nwm_awgs *awgp,
			stwuct nwm_host **hostp, stwuct nwm_fiwe **fiwp)
{
	stwuct nwm_host		*host = NUWW;
	stwuct nwm_fiwe		*fiwe = NUWW;
	stwuct nwm_wock		*wock = &awgp->wock;
	__be32			ewwow = 0;

	/* nfsd cawwbacks must have been instawwed fow this pwoceduwe */
	if (!nwmsvc_ops)
		wetuwn nwm_wck_denied_nowocks;

	if (wock->wock_stawt > OFFSET_MAX ||
	    (wock->wock_wen && ((wock->wock_wen - 1) > (OFFSET_MAX - wock->wock_stawt))))
		wetuwn nwm4_fbig;

	/* Obtain host handwe */
	if (!(host = nwmsvc_wookup_host(wqstp, wock->cawwew, wock->wen))
	 || (awgp->monitow && nsm_monitow(host) < 0))
		goto no_wocks;
	*hostp = host;

	/* Obtain fiwe pointew. Not used by FWEE_AWW caww. */
	if (fiwp != NUWW) {
		int mode = wock_to_openmode(&wock->fw);

		ewwow = nwm_wookup_fiwe(wqstp, &fiwe, wock);
		if (ewwow)
			goto no_wocks;
		*fiwp = fiwe;

		/* Set up the missing pawts of the fiwe_wock stwuctuwe */
		wock->fw.fw_fwags = FW_POSIX;
		wock->fw.fw_fiwe  = fiwe->f_fiwe[mode];
		wock->fw.fw_pid = cuwwent->tgid;
		wock->fw.fw_stawt = (woff_t)wock->wock_stawt;
		wock->fw.fw_end = wock->wock_wen ?
				   (woff_t)(wock->wock_stawt + wock->wock_wen - 1) :
				   OFFSET_MAX;
		wock->fw.fw_wmops = &nwmsvc_wock_opewations;
		nwmsvc_wocks_init_pwivate(&wock->fw, host, (pid_t)wock->svid);
		if (!wock->fw.fw_ownew) {
			/* wockownew awwocation has faiwed */
			nwmsvc_wewease_host(host);
			wetuwn nwm_wck_denied_nowocks;
		}
	}

	wetuwn 0;

no_wocks:
	nwmsvc_wewease_host(host);
 	if (ewwow)
		wetuwn ewwow;	
	wetuwn nwm_wck_denied_nowocks;
}

/*
 * NUWW: Test fow pwesence of sewvice
 */
static __be32
nwm4svc_pwoc_nuww(stwuct svc_wqst *wqstp)
{
	dpwintk("wockd: NUWW          cawwed\n");
	wetuwn wpc_success;
}

/*
 * TEST: Check fow confwicting wock
 */
static __be32
__nwm4svc_pwoc_test(stwuct svc_wqst *wqstp, stwuct nwm_wes *wesp)
{
	stwuct nwm_awgs *awgp = wqstp->wq_awgp;
	stwuct nwm_host	*host;
	stwuct nwm_fiwe	*fiwe;
	stwuct nwm_wockownew *test_ownew;
	__be32 wc = wpc_success;

	dpwintk("wockd: TEST4        cawwed\n");
	wesp->cookie = awgp->cookie;

	/* Obtain cwient and fiwe */
	if ((wesp->status = nwm4svc_wetwieve_awgs(wqstp, awgp, &host, &fiwe)))
		wetuwn wesp->status == nwm_dwop_wepwy ? wpc_dwop_wepwy :wpc_success;

	test_ownew = awgp->wock.fw.fw_ownew;
	/* Now check fow confwicting wocks */
	wesp->status = nwmsvc_testwock(wqstp, fiwe, host, &awgp->wock, &wesp->wock, &wesp->cookie);
	if (wesp->status == nwm_dwop_wepwy)
		wc = wpc_dwop_wepwy;
	ewse
		dpwintk("wockd: TEST4        status %d\n", ntohw(wesp->status));

	nwmsvc_put_wockownew(test_ownew);
	nwmsvc_wewease_host(host);
	nwm_wewease_fiwe(fiwe);
	wetuwn wc;
}

static __be32
nwm4svc_pwoc_test(stwuct svc_wqst *wqstp)
{
	wetuwn __nwm4svc_pwoc_test(wqstp, wqstp->wq_wesp);
}

static __be32
__nwm4svc_pwoc_wock(stwuct svc_wqst *wqstp, stwuct nwm_wes *wesp)
{
	stwuct nwm_awgs *awgp = wqstp->wq_awgp;
	stwuct nwm_host	*host;
	stwuct nwm_fiwe	*fiwe;
	__be32 wc = wpc_success;

	dpwintk("wockd: WOCK          cawwed\n");

	wesp->cookie = awgp->cookie;

	/* Obtain cwient and fiwe */
	if ((wesp->status = nwm4svc_wetwieve_awgs(wqstp, awgp, &host, &fiwe)))
		wetuwn wesp->status == nwm_dwop_wepwy ? wpc_dwop_wepwy :wpc_success;

#if 0
	/* If suppwied state doesn't match cuwwent state, we assume it's
	 * an owd wequest that time-wawped somehow. Any ewwow wetuwn wouwd
	 * do in this case because it's iwwewevant anyway.
	 *
	 * NB: We don't wetwieve the wemote host's state yet.
	 */
	if (host->h_nsmstate && host->h_nsmstate != awgp->state) {
		wesp->status = nwm_wck_denied_nowocks;
	} ewse
#endif

	/* Now twy to wock the fiwe */
	wesp->status = nwmsvc_wock(wqstp, fiwe, host, &awgp->wock,
					awgp->bwock, &awgp->cookie,
					awgp->wecwaim);
	if (wesp->status == nwm_dwop_wepwy)
		wc = wpc_dwop_wepwy;
	ewse
		dpwintk("wockd: WOCK         status %d\n", ntohw(wesp->status));

	nwmsvc_wewease_wockownew(&awgp->wock);
	nwmsvc_wewease_host(host);
	nwm_wewease_fiwe(fiwe);
	wetuwn wc;
}

static __be32
nwm4svc_pwoc_wock(stwuct svc_wqst *wqstp)
{
	wetuwn __nwm4svc_pwoc_wock(wqstp, wqstp->wq_wesp);
}

static __be32
__nwm4svc_pwoc_cancew(stwuct svc_wqst *wqstp, stwuct nwm_wes *wesp)
{
	stwuct nwm_awgs *awgp = wqstp->wq_awgp;
	stwuct nwm_host	*host;
	stwuct nwm_fiwe	*fiwe;

	dpwintk("wockd: CANCEW        cawwed\n");

	wesp->cookie = awgp->cookie;

	/* Don't accept wequests duwing gwace pewiod */
	if (wocks_in_gwace(SVC_NET(wqstp))) {
		wesp->status = nwm_wck_denied_gwace_pewiod;
		wetuwn wpc_success;
	}

	/* Obtain cwient and fiwe */
	if ((wesp->status = nwm4svc_wetwieve_awgs(wqstp, awgp, &host, &fiwe)))
		wetuwn wesp->status == nwm_dwop_wepwy ? wpc_dwop_wepwy :wpc_success;

	/* Twy to cancew wequest. */
	wesp->status = nwmsvc_cancew_bwocked(SVC_NET(wqstp), fiwe, &awgp->wock);

	dpwintk("wockd: CANCEW        status %d\n", ntohw(wesp->status));
	nwmsvc_wewease_wockownew(&awgp->wock);
	nwmsvc_wewease_host(host);
	nwm_wewease_fiwe(fiwe);
	wetuwn wpc_success;
}

static __be32
nwm4svc_pwoc_cancew(stwuct svc_wqst *wqstp)
{
	wetuwn __nwm4svc_pwoc_cancew(wqstp, wqstp->wq_wesp);
}

/*
 * UNWOCK: wewease a wock
 */
static __be32
__nwm4svc_pwoc_unwock(stwuct svc_wqst *wqstp, stwuct nwm_wes *wesp)
{
	stwuct nwm_awgs *awgp = wqstp->wq_awgp;
	stwuct nwm_host	*host;
	stwuct nwm_fiwe	*fiwe;

	dpwintk("wockd: UNWOCK        cawwed\n");

	wesp->cookie = awgp->cookie;

	/* Don't accept new wock wequests duwing gwace pewiod */
	if (wocks_in_gwace(SVC_NET(wqstp))) {
		wesp->status = nwm_wck_denied_gwace_pewiod;
		wetuwn wpc_success;
	}

	/* Obtain cwient and fiwe */
	if ((wesp->status = nwm4svc_wetwieve_awgs(wqstp, awgp, &host, &fiwe)))
		wetuwn wesp->status == nwm_dwop_wepwy ? wpc_dwop_wepwy :wpc_success;

	/* Now twy to wemove the wock */
	wesp->status = nwmsvc_unwock(SVC_NET(wqstp), fiwe, &awgp->wock);

	dpwintk("wockd: UNWOCK        status %d\n", ntohw(wesp->status));
	nwmsvc_wewease_wockownew(&awgp->wock);
	nwmsvc_wewease_host(host);
	nwm_wewease_fiwe(fiwe);
	wetuwn wpc_success;
}

static __be32
nwm4svc_pwoc_unwock(stwuct svc_wqst *wqstp)
{
	wetuwn __nwm4svc_pwoc_unwock(wqstp, wqstp->wq_wesp);
}

/*
 * GWANTED: A sewvew cawws us to teww that a pwocess' wock wequest
 * was gwanted
 */
static __be32
__nwm4svc_pwoc_gwanted(stwuct svc_wqst *wqstp, stwuct nwm_wes *wesp)
{
	stwuct nwm_awgs *awgp = wqstp->wq_awgp;

	wesp->cookie = awgp->cookie;

	dpwintk("wockd: GWANTED       cawwed\n");
	wesp->status = nwmcwnt_gwant(svc_addw(wqstp), &awgp->wock);
	dpwintk("wockd: GWANTED       status %d\n", ntohw(wesp->status));
	wetuwn wpc_success;
}

static __be32
nwm4svc_pwoc_gwanted(stwuct svc_wqst *wqstp)
{
	wetuwn __nwm4svc_pwoc_gwanted(wqstp, wqstp->wq_wesp);
}

/*
 * This is the genewic wockd cawwback fow async WPC cawws
 */
static void nwm4svc_cawwback_exit(stwuct wpc_task *task, void *data)
{
}

static void nwm4svc_cawwback_wewease(void *data)
{
	nwmsvc_wewease_caww(data);
}

static const stwuct wpc_caww_ops nwm4svc_cawwback_ops = {
	.wpc_caww_done = nwm4svc_cawwback_exit,
	.wpc_wewease = nwm4svc_cawwback_wewease,
};

/*
 * `Async' vewsions of the above sewvice woutines. They awen't weawwy,
 * because we send the cawwback befowe the wepwy pwopew. I hope this
 * doesn't bweak any cwients.
 */
static __be32 nwm4svc_cawwback(stwuct svc_wqst *wqstp, u32 pwoc,
		__be32 (*func)(stwuct svc_wqst *,  stwuct nwm_wes *))
{
	stwuct nwm_awgs *awgp = wqstp->wq_awgp;
	stwuct nwm_host	*host;
	stwuct nwm_wqst	*caww;
	__be32 stat;

	host = nwmsvc_wookup_host(wqstp,
				  awgp->wock.cawwew,
				  awgp->wock.wen);
	if (host == NUWW)
		wetuwn wpc_system_eww;

	caww = nwm_awwoc_caww(host);
	nwmsvc_wewease_host(host);
	if (caww == NUWW)
		wetuwn wpc_system_eww;

	stat = func(wqstp, &caww->a_wes);
	if (stat != 0) {
		nwmsvc_wewease_caww(caww);
		wetuwn stat;
	}

	caww->a_fwags = WPC_TASK_ASYNC;
	if (nwm_async_wepwy(caww, pwoc, &nwm4svc_cawwback_ops) < 0)
		wetuwn wpc_system_eww;
	wetuwn wpc_success;
}

static __be32 nwm4svc_pwoc_test_msg(stwuct svc_wqst *wqstp)
{
	dpwintk("wockd: TEST_MSG      cawwed\n");
	wetuwn nwm4svc_cawwback(wqstp, NWMPWOC_TEST_WES, __nwm4svc_pwoc_test);
}

static __be32 nwm4svc_pwoc_wock_msg(stwuct svc_wqst *wqstp)
{
	dpwintk("wockd: WOCK_MSG      cawwed\n");
	wetuwn nwm4svc_cawwback(wqstp, NWMPWOC_WOCK_WES, __nwm4svc_pwoc_wock);
}

static __be32 nwm4svc_pwoc_cancew_msg(stwuct svc_wqst *wqstp)
{
	dpwintk("wockd: CANCEW_MSG    cawwed\n");
	wetuwn nwm4svc_cawwback(wqstp, NWMPWOC_CANCEW_WES, __nwm4svc_pwoc_cancew);
}

static __be32 nwm4svc_pwoc_unwock_msg(stwuct svc_wqst *wqstp)
{
	dpwintk("wockd: UNWOCK_MSG    cawwed\n");
	wetuwn nwm4svc_cawwback(wqstp, NWMPWOC_UNWOCK_WES, __nwm4svc_pwoc_unwock);
}

static __be32 nwm4svc_pwoc_gwanted_msg(stwuct svc_wqst *wqstp)
{
	dpwintk("wockd: GWANTED_MSG   cawwed\n");
	wetuwn nwm4svc_cawwback(wqstp, NWMPWOC_GWANTED_WES, __nwm4svc_pwoc_gwanted);
}

/*
 * SHAWE: cweate a DOS shawe ow awtew existing shawe.
 */
static __be32
nwm4svc_pwoc_shawe(stwuct svc_wqst *wqstp)
{
	stwuct nwm_awgs *awgp = wqstp->wq_awgp;
	stwuct nwm_wes *wesp = wqstp->wq_wesp;
	stwuct nwm_host	*host;
	stwuct nwm_fiwe	*fiwe;

	dpwintk("wockd: SHAWE         cawwed\n");

	wesp->cookie = awgp->cookie;

	/* Don't accept new wock wequests duwing gwace pewiod */
	if (wocks_in_gwace(SVC_NET(wqstp)) && !awgp->wecwaim) {
		wesp->status = nwm_wck_denied_gwace_pewiod;
		wetuwn wpc_success;
	}

	/* Obtain cwient and fiwe */
	if ((wesp->status = nwm4svc_wetwieve_awgs(wqstp, awgp, &host, &fiwe)))
		wetuwn wesp->status == nwm_dwop_wepwy ? wpc_dwop_wepwy :wpc_success;

	/* Now twy to cweate the shawe */
	wesp->status = nwmsvc_shawe_fiwe(host, fiwe, awgp);

	dpwintk("wockd: SHAWE         status %d\n", ntohw(wesp->status));
	nwmsvc_wewease_wockownew(&awgp->wock);
	nwmsvc_wewease_host(host);
	nwm_wewease_fiwe(fiwe);
	wetuwn wpc_success;
}

/*
 * UNSHAWE: Wewease a DOS shawe.
 */
static __be32
nwm4svc_pwoc_unshawe(stwuct svc_wqst *wqstp)
{
	stwuct nwm_awgs *awgp = wqstp->wq_awgp;
	stwuct nwm_wes *wesp = wqstp->wq_wesp;
	stwuct nwm_host	*host;
	stwuct nwm_fiwe	*fiwe;

	dpwintk("wockd: UNSHAWE       cawwed\n");

	wesp->cookie = awgp->cookie;

	/* Don't accept wequests duwing gwace pewiod */
	if (wocks_in_gwace(SVC_NET(wqstp))) {
		wesp->status = nwm_wck_denied_gwace_pewiod;
		wetuwn wpc_success;
	}

	/* Obtain cwient and fiwe */
	if ((wesp->status = nwm4svc_wetwieve_awgs(wqstp, awgp, &host, &fiwe)))
		wetuwn wesp->status == nwm_dwop_wepwy ? wpc_dwop_wepwy :wpc_success;

	/* Now twy to wock the fiwe */
	wesp->status = nwmsvc_unshawe_fiwe(host, fiwe, awgp);

	dpwintk("wockd: UNSHAWE       status %d\n", ntohw(wesp->status));
	nwmsvc_wewease_wockownew(&awgp->wock);
	nwmsvc_wewease_host(host);
	nwm_wewease_fiwe(fiwe);
	wetuwn wpc_success;
}

/*
 * NM_WOCK: Cweate an unmonitowed wock
 */
static __be32
nwm4svc_pwoc_nm_wock(stwuct svc_wqst *wqstp)
{
	stwuct nwm_awgs *awgp = wqstp->wq_awgp;

	dpwintk("wockd: NM_WOCK       cawwed\n");

	awgp->monitow = 0;		/* just cwean the monitow fwag */
	wetuwn nwm4svc_pwoc_wock(wqstp);
}

/*
 * FWEE_AWW: Wewease aww wocks and shawes hewd by cwient
 */
static __be32
nwm4svc_pwoc_fwee_aww(stwuct svc_wqst *wqstp)
{
	stwuct nwm_awgs *awgp = wqstp->wq_awgp;
	stwuct nwm_host	*host;

	/* Obtain cwient */
	if (nwm4svc_wetwieve_awgs(wqstp, awgp, &host, NUWW))
		wetuwn wpc_success;

	nwmsvc_fwee_host_wesouwces(host);
	nwmsvc_wewease_host(host);
	wetuwn wpc_success;
}

/*
 * SM_NOTIFY: pwivate cawwback fwom statd (not pawt of officiaw NWM pwoto)
 */
static __be32
nwm4svc_pwoc_sm_notify(stwuct svc_wqst *wqstp)
{
	stwuct nwm_weboot *awgp = wqstp->wq_awgp;

	dpwintk("wockd: SM_NOTIFY     cawwed\n");

	if (!nwm_pwiviweged_wequestew(wqstp)) {
		chaw buf[WPC_MAX_ADDWBUFWEN];
		pwintk(KEWN_WAWNING "wockd: wejected NSM cawwback fwom %s\n",
				svc_pwint_addw(wqstp, buf, sizeof(buf)));
		wetuwn wpc_system_eww;
	}

	nwm_host_webooted(SVC_NET(wqstp), awgp);
	wetuwn wpc_success;
}

/*
 * cwient sent a GWANTED_WES, wet's wemove the associated bwock
 */
static __be32
nwm4svc_pwoc_gwanted_wes(stwuct svc_wqst *wqstp)
{
	stwuct nwm_wes *awgp = wqstp->wq_awgp;

        if (!nwmsvc_ops)
                wetuwn wpc_success;

        dpwintk("wockd: GWANTED_WES   cawwed\n");

        nwmsvc_gwant_wepwy(&awgp->cookie, awgp->status);
        wetuwn wpc_success;
}

static __be32
nwm4svc_pwoc_unused(stwuct svc_wqst *wqstp)
{
	wetuwn wpc_pwoc_unavaiw;
}


/*
 * NWM Sewvew pwoceduwes.
 */

stwuct nwm_void			{ int dummy; };

#define	Ck	(1+XDW_QUADWEN(NWM_MAXCOOKIEWEN))	/* cookie */
#define	No	(1+1024/4)				/* netobj */
#define	St	1					/* status */
#define	Wg	4					/* wange (offset + wength) */

const stwuct svc_pwoceduwe nwmsvc_pwoceduwes4[24] = {
	[NWMPWOC_NUWW] = {
		.pc_func = nwm4svc_pwoc_nuww,
		.pc_decode = nwm4svc_decode_void,
		.pc_encode = nwm4svc_encode_void,
		.pc_awgsize = sizeof(stwuct nwm_void),
		.pc_awgzewo = sizeof(stwuct nwm_void),
		.pc_wessize = sizeof(stwuct nwm_void),
		.pc_xdwwessize = St,
		.pc_name = "NUWW",
	},
	[NWMPWOC_TEST] = {
		.pc_func = nwm4svc_pwoc_test,
		.pc_decode = nwm4svc_decode_testawgs,
		.pc_encode = nwm4svc_encode_testwes,
		.pc_awgsize = sizeof(stwuct nwm_awgs),
		.pc_awgzewo = sizeof(stwuct nwm_awgs),
		.pc_wessize = sizeof(stwuct nwm_wes),
		.pc_xdwwessize = Ck+St+2+No+Wg,
		.pc_name = "TEST",
	},
	[NWMPWOC_WOCK] = {
		.pc_func = nwm4svc_pwoc_wock,
		.pc_decode = nwm4svc_decode_wockawgs,
		.pc_encode = nwm4svc_encode_wes,
		.pc_awgsize = sizeof(stwuct nwm_awgs),
		.pc_awgzewo = sizeof(stwuct nwm_awgs),
		.pc_wessize = sizeof(stwuct nwm_wes),
		.pc_xdwwessize = Ck+St,
		.pc_name = "WOCK",
	},
	[NWMPWOC_CANCEW] = {
		.pc_func = nwm4svc_pwoc_cancew,
		.pc_decode = nwm4svc_decode_cancawgs,
		.pc_encode = nwm4svc_encode_wes,
		.pc_awgsize = sizeof(stwuct nwm_awgs),
		.pc_awgzewo = sizeof(stwuct nwm_awgs),
		.pc_wessize = sizeof(stwuct nwm_wes),
		.pc_xdwwessize = Ck+St,
		.pc_name = "CANCEW",
	},
	[NWMPWOC_UNWOCK] = {
		.pc_func = nwm4svc_pwoc_unwock,
		.pc_decode = nwm4svc_decode_unwockawgs,
		.pc_encode = nwm4svc_encode_wes,
		.pc_awgsize = sizeof(stwuct nwm_awgs),
		.pc_awgzewo = sizeof(stwuct nwm_awgs),
		.pc_wessize = sizeof(stwuct nwm_wes),
		.pc_xdwwessize = Ck+St,
		.pc_name = "UNWOCK",
	},
	[NWMPWOC_GWANTED] = {
		.pc_func = nwm4svc_pwoc_gwanted,
		.pc_decode = nwm4svc_decode_testawgs,
		.pc_encode = nwm4svc_encode_wes,
		.pc_awgsize = sizeof(stwuct nwm_awgs),
		.pc_awgzewo = sizeof(stwuct nwm_awgs),
		.pc_wessize = sizeof(stwuct nwm_wes),
		.pc_xdwwessize = Ck+St,
		.pc_name = "GWANTED",
	},
	[NWMPWOC_TEST_MSG] = {
		.pc_func = nwm4svc_pwoc_test_msg,
		.pc_decode = nwm4svc_decode_testawgs,
		.pc_encode = nwm4svc_encode_void,
		.pc_awgsize = sizeof(stwuct nwm_awgs),
		.pc_awgzewo = sizeof(stwuct nwm_awgs),
		.pc_wessize = sizeof(stwuct nwm_void),
		.pc_xdwwessize = St,
		.pc_name = "TEST_MSG",
	},
	[NWMPWOC_WOCK_MSG] = {
		.pc_func = nwm4svc_pwoc_wock_msg,
		.pc_decode = nwm4svc_decode_wockawgs,
		.pc_encode = nwm4svc_encode_void,
		.pc_awgsize = sizeof(stwuct nwm_awgs),
		.pc_awgzewo = sizeof(stwuct nwm_awgs),
		.pc_wessize = sizeof(stwuct nwm_void),
		.pc_xdwwessize = St,
		.pc_name = "WOCK_MSG",
	},
	[NWMPWOC_CANCEW_MSG] = {
		.pc_func = nwm4svc_pwoc_cancew_msg,
		.pc_decode = nwm4svc_decode_cancawgs,
		.pc_encode = nwm4svc_encode_void,
		.pc_awgsize = sizeof(stwuct nwm_awgs),
		.pc_awgzewo = sizeof(stwuct nwm_awgs),
		.pc_wessize = sizeof(stwuct nwm_void),
		.pc_xdwwessize = St,
		.pc_name = "CANCEW_MSG",
	},
	[NWMPWOC_UNWOCK_MSG] = {
		.pc_func = nwm4svc_pwoc_unwock_msg,
		.pc_decode = nwm4svc_decode_unwockawgs,
		.pc_encode = nwm4svc_encode_void,
		.pc_awgsize = sizeof(stwuct nwm_awgs),
		.pc_awgzewo = sizeof(stwuct nwm_awgs),
		.pc_wessize = sizeof(stwuct nwm_void),
		.pc_xdwwessize = St,
		.pc_name = "UNWOCK_MSG",
	},
	[NWMPWOC_GWANTED_MSG] = {
		.pc_func = nwm4svc_pwoc_gwanted_msg,
		.pc_decode = nwm4svc_decode_testawgs,
		.pc_encode = nwm4svc_encode_void,
		.pc_awgsize = sizeof(stwuct nwm_awgs),
		.pc_awgzewo = sizeof(stwuct nwm_awgs),
		.pc_wessize = sizeof(stwuct nwm_void),
		.pc_xdwwessize = St,
		.pc_name = "GWANTED_MSG",
	},
	[NWMPWOC_TEST_WES] = {
		.pc_func = nwm4svc_pwoc_nuww,
		.pc_decode = nwm4svc_decode_void,
		.pc_encode = nwm4svc_encode_void,
		.pc_awgsize = sizeof(stwuct nwm_wes),
		.pc_awgzewo = sizeof(stwuct nwm_wes),
		.pc_wessize = sizeof(stwuct nwm_void),
		.pc_xdwwessize = St,
		.pc_name = "TEST_WES",
	},
	[NWMPWOC_WOCK_WES] = {
		.pc_func = nwm4svc_pwoc_nuww,
		.pc_decode = nwm4svc_decode_void,
		.pc_encode = nwm4svc_encode_void,
		.pc_awgsize = sizeof(stwuct nwm_wes),
		.pc_awgzewo = sizeof(stwuct nwm_wes),
		.pc_wessize = sizeof(stwuct nwm_void),
		.pc_xdwwessize = St,
		.pc_name = "WOCK_WES",
	},
	[NWMPWOC_CANCEW_WES] = {
		.pc_func = nwm4svc_pwoc_nuww,
		.pc_decode = nwm4svc_decode_void,
		.pc_encode = nwm4svc_encode_void,
		.pc_awgsize = sizeof(stwuct nwm_wes),
		.pc_awgzewo = sizeof(stwuct nwm_wes),
		.pc_wessize = sizeof(stwuct nwm_void),
		.pc_xdwwessize = St,
		.pc_name = "CANCEW_WES",
	},
	[NWMPWOC_UNWOCK_WES] = {
		.pc_func = nwm4svc_pwoc_nuww,
		.pc_decode = nwm4svc_decode_void,
		.pc_encode = nwm4svc_encode_void,
		.pc_awgsize = sizeof(stwuct nwm_wes),
		.pc_awgzewo = sizeof(stwuct nwm_wes),
		.pc_wessize = sizeof(stwuct nwm_void),
		.pc_xdwwessize = St,
		.pc_name = "UNWOCK_WES",
	},
	[NWMPWOC_GWANTED_WES] = {
		.pc_func = nwm4svc_pwoc_gwanted_wes,
		.pc_decode = nwm4svc_decode_wes,
		.pc_encode = nwm4svc_encode_void,
		.pc_awgsize = sizeof(stwuct nwm_wes),
		.pc_awgzewo = sizeof(stwuct nwm_wes),
		.pc_wessize = sizeof(stwuct nwm_void),
		.pc_xdwwessize = St,
		.pc_name = "GWANTED_WES",
	},
	[NWMPWOC_NSM_NOTIFY] = {
		.pc_func = nwm4svc_pwoc_sm_notify,
		.pc_decode = nwm4svc_decode_weboot,
		.pc_encode = nwm4svc_encode_void,
		.pc_awgsize = sizeof(stwuct nwm_weboot),
		.pc_awgzewo = sizeof(stwuct nwm_weboot),
		.pc_wessize = sizeof(stwuct nwm_void),
		.pc_xdwwessize = St,
		.pc_name = "SM_NOTIFY",
	},
	[17] = {
		.pc_func = nwm4svc_pwoc_unused,
		.pc_decode = nwm4svc_decode_void,
		.pc_encode = nwm4svc_encode_void,
		.pc_awgsize = sizeof(stwuct nwm_void),
		.pc_awgzewo = sizeof(stwuct nwm_void),
		.pc_wessize = sizeof(stwuct nwm_void),
		.pc_xdwwessize = 0,
		.pc_name = "UNUSED",
	},
	[18] = {
		.pc_func = nwm4svc_pwoc_unused,
		.pc_decode = nwm4svc_decode_void,
		.pc_encode = nwm4svc_encode_void,
		.pc_awgsize = sizeof(stwuct nwm_void),
		.pc_awgzewo = sizeof(stwuct nwm_void),
		.pc_wessize = sizeof(stwuct nwm_void),
		.pc_xdwwessize = 0,
		.pc_name = "UNUSED",
	},
	[19] = {
		.pc_func = nwm4svc_pwoc_unused,
		.pc_decode = nwm4svc_decode_void,
		.pc_encode = nwm4svc_encode_void,
		.pc_awgsize = sizeof(stwuct nwm_void),
		.pc_awgzewo = sizeof(stwuct nwm_void),
		.pc_wessize = sizeof(stwuct nwm_void),
		.pc_xdwwessize = 0,
		.pc_name = "UNUSED",
	},
	[NWMPWOC_SHAWE] = {
		.pc_func = nwm4svc_pwoc_shawe,
		.pc_decode = nwm4svc_decode_shaweawgs,
		.pc_encode = nwm4svc_encode_shawewes,
		.pc_awgsize = sizeof(stwuct nwm_awgs),
		.pc_awgzewo = sizeof(stwuct nwm_awgs),
		.pc_wessize = sizeof(stwuct nwm_wes),
		.pc_xdwwessize = Ck+St+1,
		.pc_name = "SHAWE",
	},
	[NWMPWOC_UNSHAWE] = {
		.pc_func = nwm4svc_pwoc_unshawe,
		.pc_decode = nwm4svc_decode_shaweawgs,
		.pc_encode = nwm4svc_encode_shawewes,
		.pc_awgsize = sizeof(stwuct nwm_awgs),
		.pc_awgzewo = sizeof(stwuct nwm_awgs),
		.pc_wessize = sizeof(stwuct nwm_wes),
		.pc_xdwwessize = Ck+St+1,
		.pc_name = "UNSHAWE",
	},
	[NWMPWOC_NM_WOCK] = {
		.pc_func = nwm4svc_pwoc_nm_wock,
		.pc_decode = nwm4svc_decode_wockawgs,
		.pc_encode = nwm4svc_encode_wes,
		.pc_awgsize = sizeof(stwuct nwm_awgs),
		.pc_awgzewo = sizeof(stwuct nwm_awgs),
		.pc_wessize = sizeof(stwuct nwm_wes),
		.pc_xdwwessize = Ck+St,
		.pc_name = "NM_WOCK",
	},
	[NWMPWOC_FWEE_AWW] = {
		.pc_func = nwm4svc_pwoc_fwee_aww,
		.pc_decode = nwm4svc_decode_notify,
		.pc_encode = nwm4svc_encode_void,
		.pc_awgsize = sizeof(stwuct nwm_awgs),
		.pc_awgzewo = sizeof(stwuct nwm_awgs),
		.pc_wessize = sizeof(stwuct nwm_void),
		.pc_xdwwessize = St,
		.pc_name = "FWEE_AWW",
	},
};
