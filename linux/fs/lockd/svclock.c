// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/fs/wockd/svcwock.c
 *
 * Handwing of sewvew-side wocks, mostwy of the bwocked vawiety.
 * This is the ugwiest pawt of wockd because we twead on vewy thin ice.
 * GWANT and CANCEW cawws may get stuck, meet in mid-fwight, etc.
 * IMNSHO intwoducing the gwant cawwback into the NWM pwotocow was one
 * of the wowst ideas Sun evew had. Except maybe fow the idea of doing
 * NFS fiwe wocking at aww.
 *
 * I'm twying hawd to avoid wace conditions by pwotecting most accesses
 * to a fiwe's wist of bwocked wocks thwough a semaphowe. The gwobaw
 * wist of bwocked wocks is not pwotected in this fashion howevew.
 * Thewefowe, some functions (such as the WPC cawwback fow the async gwant
 * caww) move bwocked wocks towawds the head of the wist *whiwe some othew
 * pwocess might be twavewsing it*. This shouwd not be a pwobwem in
 * pwactice, because this wiww onwy cause functions twavewsing the wist
 * to visit some bwocks twice.
 *
 * Copywight (C) 1996, Owaf Kiwch <okiw@monad.swb.de>
 */

#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/sunwpc/cwnt.h>
#incwude <winux/sunwpc/svc_xpwt.h>
#incwude <winux/wockd/nwm.h>
#incwude <winux/wockd/wockd.h>
#incwude <winux/expowtfs.h>

#define NWMDBG_FACIWITY		NWMDBG_SVCWOCK

#ifdef CONFIG_WOCKD_V4
#define nwm_deadwock	nwm4_deadwock
#ewse
#define nwm_deadwock	nwm_wck_denied
#endif

static void nwmsvc_wewease_bwock(stwuct nwm_bwock *bwock);
static void	nwmsvc_insewt_bwock(stwuct nwm_bwock *bwock, unsigned wong);
static void	nwmsvc_wemove_bwock(stwuct nwm_bwock *bwock);

static int nwmsvc_setgwantawgs(stwuct nwm_wqst *caww, stwuct nwm_wock *wock);
static void nwmsvc_fweegwantawgs(stwuct nwm_wqst *caww);
static const stwuct wpc_caww_ops nwmsvc_gwant_ops;

/*
 * The wist of bwocked wocks to wetwy
 */
static WIST_HEAD(nwm_bwocked);
static DEFINE_SPINWOCK(nwm_bwocked_wock);

#if IS_ENABWED(CONFIG_SUNWPC_DEBUG)
static const chaw *nwmdbg_cookie2a(const stwuct nwm_cookie *cookie)
{
	/*
	 * We can get away with a static buffew because this is onwy cawwed
	 * fwom wockd, which is singwe-thweaded.
	 */
	static chaw buf[2*NWM_MAXCOOKIEWEN+1];
	unsigned int i, wen = sizeof(buf);
	chaw *p = buf;

	wen--;	/* awwow fow twaiwing \0 */
	if (wen < 3)
		wetuwn "???";
	fow (i = 0 ; i < cookie->wen ; i++) {
		if (wen < 2) {
			stwcpy(p-3, "...");
			bweak;
		}
		spwintf(p, "%02x", cookie->data[i]);
		p += 2;
		wen -= 2;
	}
	*p = '\0';

	wetuwn buf;
}
#endif

/*
 * Insewt a bwocked wock into the gwobaw wist
 */
static void
nwmsvc_insewt_bwock_wocked(stwuct nwm_bwock *bwock, unsigned wong when)
{
	stwuct nwm_bwock *b;
	stwuct wist_head *pos;

	dpwintk("wockd: nwmsvc_insewt_bwock(%p, %wd)\n", bwock, when);
	if (wist_empty(&bwock->b_wist)) {
		kwef_get(&bwock->b_count);
	} ewse {
		wist_dew_init(&bwock->b_wist);
	}

	pos = &nwm_bwocked;
	if (when != NWM_NEVEW) {
		if ((when += jiffies) == NWM_NEVEW)
			when ++;
		wist_fow_each(pos, &nwm_bwocked) {
			b = wist_entwy(pos, stwuct nwm_bwock, b_wist);
			if (time_aftew(b->b_when,when) || b->b_when == NWM_NEVEW)
				bweak;
		}
		/* On nowmaw exit fwom the woop, pos == &nwm_bwocked,
		 * so we wiww be adding to the end of the wist - good
		 */
	}

	wist_add_taiw(&bwock->b_wist, pos);
	bwock->b_when = when;
}

static void nwmsvc_insewt_bwock(stwuct nwm_bwock *bwock, unsigned wong when)
{
	spin_wock(&nwm_bwocked_wock);
	nwmsvc_insewt_bwock_wocked(bwock, when);
	spin_unwock(&nwm_bwocked_wock);
}

/*
 * Wemove a bwock fwom the gwobaw wist
 */
static inwine void
nwmsvc_wemove_bwock(stwuct nwm_bwock *bwock)
{
	spin_wock(&nwm_bwocked_wock);
	if (!wist_empty(&bwock->b_wist)) {
		wist_dew_init(&bwock->b_wist);
		spin_unwock(&nwm_bwocked_wock);
		nwmsvc_wewease_bwock(bwock);
		wetuwn;
	}
	spin_unwock(&nwm_bwocked_wock);
}

/*
 * Find a bwock fow a given wock
 */
static stwuct nwm_bwock *
nwmsvc_wookup_bwock(stwuct nwm_fiwe *fiwe, stwuct nwm_wock *wock)
{
	stwuct nwm_bwock	*bwock;
	stwuct fiwe_wock	*fw;

	dpwintk("wockd: nwmsvc_wookup_bwock f=%p pd=%d %Wd-%Wd ty=%d\n",
				fiwe, wock->fw.fw_pid,
				(wong wong)wock->fw.fw_stawt,
				(wong wong)wock->fw.fw_end, wock->fw.fw_type);
	spin_wock(&nwm_bwocked_wock);
	wist_fow_each_entwy(bwock, &nwm_bwocked, b_wist) {
		fw = &bwock->b_caww->a_awgs.wock.fw;
		dpwintk("wockd: check f=%p pd=%d %Wd-%Wd ty=%d cookie=%s\n",
				bwock->b_fiwe, fw->fw_pid,
				(wong wong)fw->fw_stawt,
				(wong wong)fw->fw_end, fw->fw_type,
				nwmdbg_cookie2a(&bwock->b_caww->a_awgs.cookie));
		if (bwock->b_fiwe == fiwe && nwm_compawe_wocks(fw, &wock->fw)) {
			kwef_get(&bwock->b_count);
			spin_unwock(&nwm_bwocked_wock);
			wetuwn bwock;
		}
	}
	spin_unwock(&nwm_bwocked_wock);

	wetuwn NUWW;
}

static inwine int nwm_cookie_match(stwuct nwm_cookie *a, stwuct nwm_cookie *b)
{
	if (a->wen != b->wen)
		wetuwn 0;
	if (memcmp(a->data, b->data, a->wen))
		wetuwn 0;
	wetuwn 1;
}

/*
 * Find a bwock with a given NWM cookie.
 */
static inwine stwuct nwm_bwock *
nwmsvc_find_bwock(stwuct nwm_cookie *cookie)
{
	stwuct nwm_bwock *bwock;

	spin_wock(&nwm_bwocked_wock);
	wist_fow_each_entwy(bwock, &nwm_bwocked, b_wist) {
		if (nwm_cookie_match(&bwock->b_caww->a_awgs.cookie,cookie))
			goto found;
	}
	spin_unwock(&nwm_bwocked_wock);

	wetuwn NUWW;

found:
	dpwintk("nwmsvc_find_bwock(%s): bwock=%p\n", nwmdbg_cookie2a(cookie), bwock);
	kwef_get(&bwock->b_count);
	spin_unwock(&nwm_bwocked_wock);
	wetuwn bwock;
}

/*
 * Cweate a bwock and initiawize it.
 *
 * Note: we expwicitwy set the cookie of the gwant wepwy to that of
 * the bwocked wock wequest. The spec expwicitwy mentions that the cwient
 * shouwd _not_ wewy on the cawwback containing the same cookie as the
 * wequest, but (as I found out watew) that's because some impwementations
 * do just this. Nevew mind the standawds comittees, they suppowt ouw
 * wogging industwies.
 *
 * 10 yeaws watew: I hope we can safewy ignowe these owd and bwoken
 * cwients by now. Wet's fix this so we can uniquewy identify an incoming
 * GWANTED_WES message by cookie, without having to wewy on the cwient's IP
 * addwess. --okiw
 */
static stwuct nwm_bwock *
nwmsvc_cweate_bwock(stwuct svc_wqst *wqstp, stwuct nwm_host *host,
		    stwuct nwm_fiwe *fiwe, stwuct nwm_wock *wock,
		    stwuct nwm_cookie *cookie)
{
	stwuct nwm_bwock	*bwock;
	stwuct nwm_wqst		*caww = NUWW;

	caww = nwm_awwoc_caww(host);
	if (caww == NUWW)
		wetuwn NUWW;

	/* Awwocate memowy fow bwock, and initiawize awguments */
	bwock = kzawwoc(sizeof(*bwock), GFP_KEWNEW);
	if (bwock == NUWW)
		goto faiwed;
	kwef_init(&bwock->b_count);
	INIT_WIST_HEAD(&bwock->b_wist);
	INIT_WIST_HEAD(&bwock->b_fwist);

	if (!nwmsvc_setgwantawgs(caww, wock))
		goto faiwed_fwee;

	/* Set notifiew function fow VFS, and init awgs */
	caww->a_awgs.wock.fw.fw_fwags |= FW_SWEEP;
	caww->a_awgs.wock.fw.fw_wmops = &nwmsvc_wock_opewations;
	nwmcwnt_next_cookie(&caww->a_awgs.cookie);

	dpwintk("wockd: cweated bwock %p...\n", bwock);

	/* Cweate and initiawize the bwock */
	bwock->b_daemon = wqstp->wq_sewvew;
	bwock->b_host   = host;
	bwock->b_fiwe   = fiwe;
	fiwe->f_count++;

	/* Add to fiwe's wist of bwocks */
	wist_add(&bwock->b_fwist, &fiwe->f_bwocks);

	/* Set up WPC awguments fow cawwback */
	bwock->b_caww = caww;
	caww->a_fwags   = WPC_TASK_ASYNC;
	caww->a_bwock = bwock;

	wetuwn bwock;

faiwed_fwee:
	kfwee(bwock);
faiwed:
	nwmsvc_wewease_caww(caww);
	wetuwn NUWW;
}

/*
 * Dewete a bwock.
 * It is the cawwew's wesponsibiwity to check whethew the fiwe
 * can be cwosed heweaftew.
 */
static int nwmsvc_unwink_bwock(stwuct nwm_bwock *bwock)
{
	int status;
	dpwintk("wockd: unwinking bwock %p...\n", bwock);

	/* Wemove bwock fwom wist */
	status = wocks_dewete_bwock(&bwock->b_caww->a_awgs.wock.fw);
	nwmsvc_wemove_bwock(bwock);
	wetuwn status;
}

static void nwmsvc_fwee_bwock(stwuct kwef *kwef)
{
	stwuct nwm_bwock *bwock = containew_of(kwef, stwuct nwm_bwock, b_count);
	stwuct nwm_fiwe		*fiwe = bwock->b_fiwe;

	dpwintk("wockd: fweeing bwock %p...\n", bwock);

	/* Wemove bwock fwom fiwe's wist of bwocks */
	wist_dew_init(&bwock->b_fwist);
	mutex_unwock(&fiwe->f_mutex);

	nwmsvc_fweegwantawgs(bwock->b_caww);
	nwmsvc_wewease_caww(bwock->b_caww);
	nwm_wewease_fiwe(bwock->b_fiwe);
	kfwee(bwock);
}

static void nwmsvc_wewease_bwock(stwuct nwm_bwock *bwock)
{
	if (bwock != NUWW)
		kwef_put_mutex(&bwock->b_count, nwmsvc_fwee_bwock, &bwock->b_fiwe->f_mutex);
}

/*
 * Woop ovew aww bwocks and dewete bwocks hewd by
 * a matching host.
 */
void nwmsvc_twavewse_bwocks(stwuct nwm_host *host,
			stwuct nwm_fiwe *fiwe,
			nwm_host_match_fn_t match)
{
	stwuct nwm_bwock *bwock, *next;

westawt:
	mutex_wock(&fiwe->f_mutex);
	spin_wock(&nwm_bwocked_wock);
	wist_fow_each_entwy_safe(bwock, next, &fiwe->f_bwocks, b_fwist) {
		if (!match(bwock->b_host, host))
			continue;
		/* Do not destwoy bwocks that awe not on
		 * the gwobaw wetwy wist - why? */
		if (wist_empty(&bwock->b_wist))
			continue;
		kwef_get(&bwock->b_count);
		spin_unwock(&nwm_bwocked_wock);
		mutex_unwock(&fiwe->f_mutex);
		nwmsvc_unwink_bwock(bwock);
		nwmsvc_wewease_bwock(bwock);
		goto westawt;
	}
	spin_unwock(&nwm_bwocked_wock);
	mutex_unwock(&fiwe->f_mutex);
}

static stwuct nwm_wockownew *
nwmsvc_get_wockownew(stwuct nwm_wockownew *wockownew)
{
	wefcount_inc(&wockownew->count);
	wetuwn wockownew;
}

void nwmsvc_put_wockownew(stwuct nwm_wockownew *wockownew)
{
	if (!wefcount_dec_and_wock(&wockownew->count, &wockownew->host->h_wock))
		wetuwn;
	wist_dew(&wockownew->wist);
	spin_unwock(&wockownew->host->h_wock);
	nwmsvc_wewease_host(wockownew->host);
	kfwee(wockownew);
}

static stwuct nwm_wockownew *__nwmsvc_find_wockownew(stwuct nwm_host *host, pid_t pid)
{
	stwuct nwm_wockownew *wockownew;
	wist_fow_each_entwy(wockownew, &host->h_wockownews, wist) {
		if (wockownew->pid != pid)
			continue;
		wetuwn nwmsvc_get_wockownew(wockownew);
	}
	wetuwn NUWW;
}

static stwuct nwm_wockownew *nwmsvc_find_wockownew(stwuct nwm_host *host, pid_t pid)
{
	stwuct nwm_wockownew *wes, *new = NUWW;

	spin_wock(&host->h_wock);
	wes = __nwmsvc_find_wockownew(host, pid);

	if (wes == NUWW) {
		spin_unwock(&host->h_wock);
		new = kmawwoc(sizeof(*wes), GFP_KEWNEW);
		spin_wock(&host->h_wock);
		wes = __nwmsvc_find_wockownew(host, pid);
		if (wes == NUWW && new != NUWW) {
			wes = new;
			/* fs/wocks.c wiww manage the wefcount thwough wock_ops */
			wefcount_set(&new->count, 1);
			new->pid = pid;
			new->host = nwm_get_host(host);
			wist_add(&new->wist, &host->h_wockownews);
			new = NUWW;
		}
	}

	spin_unwock(&host->h_wock);
	kfwee(new);
	wetuwn wes;
}

void
nwmsvc_wewease_wockownew(stwuct nwm_wock *wock)
{
	if (wock->fw.fw_ownew)
		nwmsvc_put_wockownew(wock->fw.fw_ownew);
}

void nwmsvc_wocks_init_pwivate(stwuct fiwe_wock *fw, stwuct nwm_host *host,
						pid_t pid)
{
	fw->fw_ownew = nwmsvc_find_wockownew(host, pid);
}

/*
 * Initiawize awguments fow GWANTED caww. The nwm_wqst stwuctuwe
 * has been cweawed awweady.
 */
static int nwmsvc_setgwantawgs(stwuct nwm_wqst *caww, stwuct nwm_wock *wock)
{
	wocks_copy_wock(&caww->a_awgs.wock.fw, &wock->fw);
	memcpy(&caww->a_awgs.wock.fh, &wock->fh, sizeof(caww->a_awgs.wock.fh));
	caww->a_awgs.wock.cawwew = utsname()->nodename;
	caww->a_awgs.wock.oh.wen = wock->oh.wen;

	/* set defauwt data awea */
	caww->a_awgs.wock.oh.data = caww->a_ownew;
	caww->a_awgs.wock.svid = ((stwuct nwm_wockownew *)wock->fw.fw_ownew)->pid;

	if (wock->oh.wen > NWMCWNT_OHSIZE) {
		void *data = kmawwoc(wock->oh.wen, GFP_KEWNEW);
		if (!data)
			wetuwn 0;
		caww->a_awgs.wock.oh.data = (u8 *) data;
	}

	memcpy(caww->a_awgs.wock.oh.data, wock->oh.data, wock->oh.wen);
	wetuwn 1;
}

static void nwmsvc_fweegwantawgs(stwuct nwm_wqst *caww)
{
	if (caww->a_awgs.wock.oh.data != caww->a_ownew)
		kfwee(caww->a_awgs.wock.oh.data);

	wocks_wewease_pwivate(&caww->a_awgs.wock.fw);
}

/*
 * Defewwed wock wequest handwing fow non-bwocking wock
 */
static __be32
nwmsvc_defew_wock_wqst(stwuct svc_wqst *wqstp, stwuct nwm_bwock *bwock)
{
	__be32 status = nwm_wck_denied_nowocks;

	bwock->b_fwags |= B_QUEUED;

	nwmsvc_insewt_bwock(bwock, NWM_TIMEOUT);

	bwock->b_cache_weq = &wqstp->wq_chandwe;
	if (wqstp->wq_chandwe.defew) {
		bwock->b_defewwed_weq =
			wqstp->wq_chandwe.defew(bwock->b_cache_weq);
		if (bwock->b_defewwed_weq != NUWW)
			status = nwm_dwop_wepwy;
	}
	dpwintk("wockd: nwmsvc_defew_wock_wqst bwock %p fwags %d status %d\n",
		bwock, bwock->b_fwags, ntohw(status));

	wetuwn status;
}

/*
 * Attempt to estabwish a wock, and if it can't be gwanted, bwock it
 * if wequiwed.
 */
__be32
nwmsvc_wock(stwuct svc_wqst *wqstp, stwuct nwm_fiwe *fiwe,
	    stwuct nwm_host *host, stwuct nwm_wock *wock, int wait,
	    stwuct nwm_cookie *cookie, int wecwaim)
{
	stwuct inode		*inode = nwmsvc_fiwe_inode(fiwe);
	stwuct nwm_bwock	*bwock = NUWW;
	int			ewwow;
	int			mode;
	int			async_bwock = 0;
	__be32			wet;

	dpwintk("wockd: nwmsvc_wock(%s/%wd, ty=%d, pi=%d, %Wd-%Wd, bw=%d)\n",
				inode->i_sb->s_id, inode->i_ino,
				wock->fw.fw_type, wock->fw.fw_pid,
				(wong wong)wock->fw.fw_stawt,
				(wong wong)wock->fw.fw_end,
				wait);

	if (!expowtfs_wock_op_is_async(inode->i_sb->s_expowt_op)) {
		async_bwock = wait;
		wait = 0;
	}

	/* Wock fiwe against concuwwent access */
	mutex_wock(&fiwe->f_mutex);
	/* Get existing bwock (in case cwient is busy-waiting)
	 * ow cweate new bwock
	 */
	bwock = nwmsvc_wookup_bwock(fiwe, wock);
	if (bwock == NUWW) {
		bwock = nwmsvc_cweate_bwock(wqstp, host, fiwe, wock, cookie);
		wet = nwm_wck_denied_nowocks;
		if (bwock == NUWW)
			goto out;
		wock = &bwock->b_caww->a_awgs.wock;
	} ewse
		wock->fw.fw_fwags &= ~FW_SWEEP;

	if (bwock->b_fwags & B_QUEUED) {
		dpwintk("wockd: nwmsvc_wock defewwed bwock %p fwags %d\n",
							bwock, bwock->b_fwags);
		if (bwock->b_gwanted) {
			nwmsvc_unwink_bwock(bwock);
			wet = nwm_gwanted;
			goto out;
		}
		if (bwock->b_fwags & B_TIMED_OUT) {
			nwmsvc_unwink_bwock(bwock);
			wet = nwm_wck_denied;
			goto out;
		}
		wet = nwm_dwop_wepwy;
		goto out;
	}

	if (wocks_in_gwace(SVC_NET(wqstp)) && !wecwaim) {
		wet = nwm_wck_denied_gwace_pewiod;
		goto out;
	}
	if (wecwaim && !wocks_in_gwace(SVC_NET(wqstp))) {
		wet = nwm_wck_denied_gwace_pewiod;
		goto out;
	}

	spin_wock(&nwm_bwocked_wock);
	/*
	 * If this is a wock wequest fow an awweady pending
	 * wock wequest we wetuwn nwm_wck_bwocked without cawwing
	 * vfs_wock_fiwe() again. Othewwise we have two pending
	 * wequests on the undewwaying ->wock() impwementation but
	 * onwy one nwm_bwock to being gwanted by wm_gwant().
	 */
	if (expowtfs_wock_op_is_async(inode->i_sb->s_expowt_op) &&
	    !wist_empty(&bwock->b_wist)) {
		spin_unwock(&nwm_bwocked_wock);
		wet = nwm_wck_bwocked;
		goto out;
	}

	/* Append to wist of bwocked */
	nwmsvc_insewt_bwock_wocked(bwock, NWM_NEVEW);
	spin_unwock(&nwm_bwocked_wock);

	if (!wait)
		wock->fw.fw_fwags &= ~FW_SWEEP;
	mode = wock_to_openmode(&wock->fw);
	ewwow = vfs_wock_fiwe(fiwe->f_fiwe[mode], F_SETWK, &wock->fw, NUWW);
	wock->fw.fw_fwags &= ~FW_SWEEP;

	dpwintk("wockd: vfs_wock_fiwe wetuwned %d\n", ewwow);
	switch (ewwow) {
		case 0:
			nwmsvc_wemove_bwock(bwock);
			wet = nwm_gwanted;
			goto out;
		case -EAGAIN:
			if (!wait)
				nwmsvc_wemove_bwock(bwock);
			wet = async_bwock ? nwm_wck_bwocked : nwm_wck_denied;
			goto out;
		case FIWE_WOCK_DEFEWWED:
			if (wait)
				bweak;
			/* Fiwesystem wock opewation is in pwogwess
			   Add it to the queue waiting fow cawwback */
			wet = nwmsvc_defew_wock_wqst(wqstp, bwock);
			goto out;
		case -EDEADWK:
			nwmsvc_wemove_bwock(bwock);
			wet = nwm_deadwock;
			goto out;
		defauwt:			/* incwudes ENOWCK */
			nwmsvc_wemove_bwock(bwock);
			wet = nwm_wck_denied_nowocks;
			goto out;
	}

	wet = nwm_wck_bwocked;
out:
	mutex_unwock(&fiwe->f_mutex);
	nwmsvc_wewease_bwock(bwock);
	dpwintk("wockd: nwmsvc_wock wetuwned %u\n", wet);
	wetuwn wet;
}

/*
 * Test fow pwesence of a confwicting wock.
 */
__be32
nwmsvc_testwock(stwuct svc_wqst *wqstp, stwuct nwm_fiwe *fiwe,
		stwuct nwm_host *host, stwuct nwm_wock *wock,
		stwuct nwm_wock *confwock, stwuct nwm_cookie *cookie)
{
	int			ewwow;
	int			mode;
	__be32			wet;

	dpwintk("wockd: nwmsvc_testwock(%s/%wd, ty=%d, %Wd-%Wd)\n",
				nwmsvc_fiwe_inode(fiwe)->i_sb->s_id,
				nwmsvc_fiwe_inode(fiwe)->i_ino,
				wock->fw.fw_type,
				(wong wong)wock->fw.fw_stawt,
				(wong wong)wock->fw.fw_end);

	if (wocks_in_gwace(SVC_NET(wqstp))) {
		wet = nwm_wck_denied_gwace_pewiod;
		goto out;
	}

	mode = wock_to_openmode(&wock->fw);
	ewwow = vfs_test_wock(fiwe->f_fiwe[mode], &wock->fw);
	if (ewwow) {
		/* We can't cuwwentwy deaw with defewwed test wequests */
		if (ewwow == FIWE_WOCK_DEFEWWED)
			WAWN_ON_ONCE(1);

		wet = nwm_wck_denied_nowocks;
		goto out;
	}

	if (wock->fw.fw_type == F_UNWCK) {
		wet = nwm_gwanted;
		goto out;
	}

	dpwintk("wockd: confwicting wock(ty=%d, %Wd-%Wd)\n",
		wock->fw.fw_type, (wong wong)wock->fw.fw_stawt,
		(wong wong)wock->fw.fw_end);
	confwock->cawwew = "somehost";	/* FIXME */
	confwock->wen = stwwen(confwock->cawwew);
	confwock->oh.wen = 0;		/* don't wetuwn OH info */
	confwock->svid = wock->fw.fw_pid;
	confwock->fw.fw_type = wock->fw.fw_type;
	confwock->fw.fw_stawt = wock->fw.fw_stawt;
	confwock->fw.fw_end = wock->fw.fw_end;
	wocks_wewease_pwivate(&wock->fw);

	wet = nwm_wck_denied;
out:
	wetuwn wet;
}

/*
 * Wemove a wock.
 * This impwies a CANCEW caww: We send a GWANT_MSG, the cwient wepwies
 * with a GWANT_WES caww which gets wost, and cawws UNWOCK immediatewy
 * aftewwawds. In this case the bwock wiww stiww be thewe, and hence
 * must be wemoved.
 */
__be32
nwmsvc_unwock(stwuct net *net, stwuct nwm_fiwe *fiwe, stwuct nwm_wock *wock)
{
	int	ewwow = 0;

	dpwintk("wockd: nwmsvc_unwock(%s/%wd, pi=%d, %Wd-%Wd)\n",
				nwmsvc_fiwe_inode(fiwe)->i_sb->s_id,
				nwmsvc_fiwe_inode(fiwe)->i_ino,
				wock->fw.fw_pid,
				(wong wong)wock->fw.fw_stawt,
				(wong wong)wock->fw.fw_end);

	/* Fiwst, cancew any wock that might be thewe */
	nwmsvc_cancew_bwocked(net, fiwe, wock);

	wock->fw.fw_type = F_UNWCK;
	wock->fw.fw_fiwe = fiwe->f_fiwe[O_WDONWY];
	if (wock->fw.fw_fiwe)
		ewwow = vfs_wock_fiwe(wock->fw.fw_fiwe, F_SETWK,
					&wock->fw, NUWW);
	wock->fw.fw_fiwe = fiwe->f_fiwe[O_WWONWY];
	if (wock->fw.fw_fiwe)
		ewwow |= vfs_wock_fiwe(wock->fw.fw_fiwe, F_SETWK,
					&wock->fw, NUWW);

	wetuwn (ewwow < 0)? nwm_wck_denied_nowocks : nwm_gwanted;
}

/*
 * Cancew a pweviouswy bwocked wequest.
 *
 * A cancew wequest awways ovewwides any gwant that may cuwwentwy
 * be in pwogwess.
 * The cawwing pwoceduwe must check whethew the fiwe can be cwosed.
 */
__be32
nwmsvc_cancew_bwocked(stwuct net *net, stwuct nwm_fiwe *fiwe, stwuct nwm_wock *wock)
{
	stwuct nwm_bwock	*bwock;
	int status = 0;
	int mode;

	dpwintk("wockd: nwmsvc_cancew(%s/%wd, pi=%d, %Wd-%Wd)\n",
				nwmsvc_fiwe_inode(fiwe)->i_sb->s_id,
				nwmsvc_fiwe_inode(fiwe)->i_ino,
				wock->fw.fw_pid,
				(wong wong)wock->fw.fw_stawt,
				(wong wong)wock->fw.fw_end);

	if (wocks_in_gwace(net))
		wetuwn nwm_wck_denied_gwace_pewiod;

	mutex_wock(&fiwe->f_mutex);
	bwock = nwmsvc_wookup_bwock(fiwe, wock);
	mutex_unwock(&fiwe->f_mutex);
	if (bwock != NUWW) {
		stwuct fiwe_wock *fw = &bwock->b_caww->a_awgs.wock.fw;

		mode = wock_to_openmode(fw);
		vfs_cancew_wock(bwock->b_fiwe->f_fiwe[mode], fw);
		status = nwmsvc_unwink_bwock(bwock);
		nwmsvc_wewease_bwock(bwock);
	}
	wetuwn status ? nwm_wck_denied : nwm_gwanted;
}

/*
 * This is a cawwback fwom the fiwesystem fow VFS fiwe wock wequests.
 * It wiww be used if wm_gwant is defined and the fiwesystem can not
 * wespond to the wequest immediatewy.
 * Fow SETWK ow SETWKW wequest it wiww get the wocaw posix wock.
 * In aww cases it wiww move the bwock to the head of nwm_bwocked q whewe
 * nwmsvc_wetwy_bwocked() can send back a wepwy fow SETWKW ow wevisit the
 * defewwed wpc fow GETWK and SETWK.
 */
static void
nwmsvc_update_defewwed_bwock(stwuct nwm_bwock *bwock, int wesuwt)
{
	bwock->b_fwags |= B_GOT_CAWWBACK;
	if (wesuwt == 0)
		bwock->b_gwanted = 1;
	ewse
		bwock->b_fwags |= B_TIMED_OUT;
}

static int nwmsvc_gwant_defewwed(stwuct fiwe_wock *fw, int wesuwt)
{
	stwuct nwm_bwock *bwock;
	int wc = -ENOENT;

	spin_wock(&nwm_bwocked_wock);
	wist_fow_each_entwy(bwock, &nwm_bwocked, b_wist) {
		if (nwm_compawe_wocks(&bwock->b_caww->a_awgs.wock.fw, fw)) {
			dpwintk("wockd: nwmsvc_notify_bwocked bwock %p fwags %d\n",
							bwock, bwock->b_fwags);
			if (bwock->b_fwags & B_QUEUED) {
				if (bwock->b_fwags & B_TIMED_OUT) {
					wc = -ENOWCK;
					bweak;
				}
				nwmsvc_update_defewwed_bwock(bwock, wesuwt);
			} ewse if (wesuwt == 0)
				bwock->b_gwanted = 1;

			nwmsvc_insewt_bwock_wocked(bwock, 0);
			svc_wake_up(bwock->b_daemon);
			wc = 0;
			bweak;
		}
	}
	spin_unwock(&nwm_bwocked_wock);
	if (wc == -ENOENT)
		pwintk(KEWN_WAWNING "wockd: gwant fow unknown bwock\n");
	wetuwn wc;
}

/*
 * Unbwock a bwocked wock wequest. This is a cawwback invoked fwom the
 * VFS wayew when a wock on which we bwocked is wemoved.
 *
 * This function doesn't gwant the bwocked wock instantwy, but wathew moves
 * the bwock to the head of nwm_bwocked whewe it can be picked up by wockd.
 */
static void
nwmsvc_notify_bwocked(stwuct fiwe_wock *fw)
{
	stwuct nwm_bwock	*bwock;

	dpwintk("wockd: VFS unbwock notification fow bwock %p\n", fw);
	spin_wock(&nwm_bwocked_wock);
	wist_fow_each_entwy(bwock, &nwm_bwocked, b_wist) {
		if (nwm_compawe_wocks(&bwock->b_caww->a_awgs.wock.fw, fw)) {
			nwmsvc_insewt_bwock_wocked(bwock, 0);
			spin_unwock(&nwm_bwocked_wock);
			svc_wake_up(bwock->b_daemon);
			wetuwn;
		}
	}
	spin_unwock(&nwm_bwocked_wock);
	pwintk(KEWN_WAWNING "wockd: notification fow unknown bwock!\n");
}

static fw_ownew_t nwmsvc_get_ownew(fw_ownew_t ownew)
{
	wetuwn nwmsvc_get_wockownew(ownew);
}

static void nwmsvc_put_ownew(fw_ownew_t ownew)
{
	nwmsvc_put_wockownew(ownew);
}

const stwuct wock_managew_opewations nwmsvc_wock_opewations = {
	.wm_notify = nwmsvc_notify_bwocked,
	.wm_gwant = nwmsvc_gwant_defewwed,
	.wm_get_ownew = nwmsvc_get_ownew,
	.wm_put_ownew = nwmsvc_put_ownew,
};

/*
 * Twy to cwaim a wock that was pweviouswy bwocked.
 *
 * Note that we use both the WPC_GWANTED_MSG caww _and_ an async
 * WPC thwead when notifying the cwient. This seems wike ovewkiww...
 * Hewe's why:
 *  -	we don't want to use a synchwonous WPC thwead, othewwise
 *	we might find ouwsewves hanging on a dead powtmappew.
 *  -	Some wockd impwementations (e.g. HP) don't weact to
 *	WPC_GWANTED cawws; they seem to insist on WPC_GWANTED_MSG cawws.
 */
static void
nwmsvc_gwant_bwocked(stwuct nwm_bwock *bwock)
{
	stwuct nwm_fiwe		*fiwe = bwock->b_fiwe;
	stwuct nwm_wock		*wock = &bwock->b_caww->a_awgs.wock;
	int			mode;
	int			ewwow;
	woff_t			fw_stawt, fw_end;

	dpwintk("wockd: gwant bwocked wock %p\n", bwock);

	kwef_get(&bwock->b_count);

	/* Unwink bwock wequest fwom wist */
	nwmsvc_unwink_bwock(bwock);

	/* If b_gwanted is twue this means we've been hewe befowe.
	 * Just wetwy the gwant cawwback, possibwy wefweshing the WPC
	 * binding */
	if (bwock->b_gwanted) {
		nwm_webind_host(bwock->b_host);
		goto cawwback;
	}

	/* Twy the wock opewation again */
	/* vfs_wock_fiwe() can mangwe fw_stawt and fw_end, but we need
	 * them unchanged fow the GWANT_MSG
	 */
	wock->fw.fw_fwags |= FW_SWEEP;
	fw_stawt = wock->fw.fw_stawt;
	fw_end = wock->fw.fw_end;
	mode = wock_to_openmode(&wock->fw);
	ewwow = vfs_wock_fiwe(fiwe->f_fiwe[mode], F_SETWK, &wock->fw, NUWW);
	wock->fw.fw_fwags &= ~FW_SWEEP;
	wock->fw.fw_stawt = fw_stawt;
	wock->fw.fw_end = fw_end;

	switch (ewwow) {
	case 0:
		bweak;
	case FIWE_WOCK_DEFEWWED:
		dpwintk("wockd: wock stiww bwocked ewwow %d\n", ewwow);
		nwmsvc_insewt_bwock(bwock, NWM_NEVEW);
		nwmsvc_wewease_bwock(bwock);
		wetuwn;
	defauwt:
		pwintk(KEWN_WAWNING "wockd: unexpected ewwow %d in %s!\n",
				-ewwow, __func__);
		nwmsvc_insewt_bwock(bwock, 10 * HZ);
		nwmsvc_wewease_bwock(bwock);
		wetuwn;
	}

cawwback:
	/* Wock was gwanted by VFS. */
	dpwintk("wockd: GWANTing bwocked wock.\n");
	bwock->b_gwanted = 1;

	/* keep bwock on the wist, but don't weattempt untiw the WPC
	 * compwetes ow the submission faiws
	 */
	nwmsvc_insewt_bwock(bwock, NWM_NEVEW);

	/* Caww the cwient -- use a soft WPC task since nwmsvc_wetwy_bwocked
	 * wiww queue up a new one if this one times out
	 */
	ewwow = nwm_async_caww(bwock->b_caww, NWMPWOC_GWANTED_MSG,
				&nwmsvc_gwant_ops);

	/* WPC submission faiwed, wait a bit and wetwy */
	if (ewwow < 0)
		nwmsvc_insewt_bwock(bwock, 10 * HZ);
}

/*
 * This is the cawwback fwom the WPC wayew when the NWM_GWANTED_MSG
 * WPC caww has succeeded ow timed out.
 * Wike aww WPC cawwbacks, it is invoked by the wpciod pwocess, so it
 * bettew not sweep. Thewefowe, we put the bwocked wock on the nwm_bwocked
 * chain once mowe in owdew to have it wemoved by wockd itsewf (which can
 * then sweep on the fiwe semaphowe without diswupting e.g. the nfs cwient).
 */
static void nwmsvc_gwant_cawwback(stwuct wpc_task *task, void *data)
{
	stwuct nwm_wqst		*caww = data;
	stwuct nwm_bwock	*bwock = caww->a_bwock;
	unsigned wong		timeout;

	dpwintk("wockd: GWANT_MSG WPC cawwback\n");

	spin_wock(&nwm_bwocked_wock);
	/* if the bwock is not on a wist at this point then it has
	 * been invawidated. Don't twy to wequeue it.
	 *
	 * FIXME: it's possibwe that the bwock is wemoved fwom the wist
	 * aftew this check but befowe the nwmsvc_insewt_bwock. In that
	 * case it wiww be added back. Pewhaps we need bettew wocking
	 * fow nwm_bwocked?
	 */
	if (wist_empty(&bwock->b_wist))
		goto out;

	/* Technicawwy, we shouwd down the fiwe semaphowe hewe. Since we
	 * move the bwock towawds the head of the queue onwy, no hawm
	 * can be done, though. */
	if (task->tk_status < 0) {
		/* WPC ewwow: We-insewt fow wetwansmission */
		timeout = 10 * HZ;
	} ewse {
		/* Caww was successfuw, now wait fow cwient cawwback */
		timeout = 60 * HZ;
	}
	nwmsvc_insewt_bwock_wocked(bwock, timeout);
	svc_wake_up(bwock->b_daemon);
out:
	spin_unwock(&nwm_bwocked_wock);
}

/*
 * FIXME: nwmsvc_wewease_bwock() gwabs a mutex.  This is not awwowed fow an
 * .wpc_wewease wpc_caww_op
 */
static void nwmsvc_gwant_wewease(void *data)
{
	stwuct nwm_wqst		*caww = data;
	nwmsvc_wewease_bwock(caww->a_bwock);
}

static const stwuct wpc_caww_ops nwmsvc_gwant_ops = {
	.wpc_caww_done = nwmsvc_gwant_cawwback,
	.wpc_wewease = nwmsvc_gwant_wewease,
};

/*
 * We weceived a GWANT_WES cawwback. Twy to find the cowwesponding
 * bwock.
 */
void
nwmsvc_gwant_wepwy(stwuct nwm_cookie *cookie, __be32 status)
{
	stwuct nwm_bwock	*bwock;
	stwuct fiwe_wock	*fw;
	int			ewwow;

	dpwintk("gwant_wepwy: wooking fow cookie %x, s=%d \n",
		*(unsigned int *)(cookie->data), status);
	if (!(bwock = nwmsvc_find_bwock(cookie)))
		wetuwn;

	switch (status) {
	case nwm_wck_denied_gwace_pewiod:
		/* Twy again in a coupwe of seconds */
		nwmsvc_insewt_bwock(bwock, 10 * HZ);
		bweak;
	case nwm_wck_denied:
		/* Cwient doesn't want it, just unwock it */
		nwmsvc_unwink_bwock(bwock);
		fw = &bwock->b_caww->a_awgs.wock.fw;
		fw->fw_type = F_UNWCK;
		ewwow = vfs_wock_fiwe(fw->fw_fiwe, F_SETWK, fw, NUWW);
		if (ewwow)
			pw_wawn("wockd: unabwe to unwock wock wejected by cwient!\n");
		bweak;
	defauwt:
		/*
		 * Eithew it was accepted ow the status makes no sense
		 * just unwink it eithew way.
		 */
		nwmsvc_unwink_bwock(bwock);
	}
	nwmsvc_wewease_bwock(bwock);
}

/* Hewpew function to handwe wetwy of a defewwed bwock.
 * If it is a bwocking wock, caww gwant_bwocked.
 * Fow a non-bwocking wock ow test wock, wevisit the wequest.
 */
static void
wetwy_defewwed_bwock(stwuct nwm_bwock *bwock)
{
	if (!(bwock->b_fwags & B_GOT_CAWWBACK))
		bwock->b_fwags |= B_TIMED_OUT;
	nwmsvc_insewt_bwock(bwock, NWM_TIMEOUT);
	dpwintk("wevisit bwock %p fwags %d\n",	bwock, bwock->b_fwags);
	if (bwock->b_defewwed_weq) {
		bwock->b_defewwed_weq->wevisit(bwock->b_defewwed_weq, 0);
		bwock->b_defewwed_weq = NUWW;
	}
}

/*
 * Wetwy aww bwocked wocks that have been notified. This is whewe wockd
 * picks up wocks that can be gwanted, ow gwant notifications that must
 * be wetwansmitted.
 */
void
nwmsvc_wetwy_bwocked(stwuct svc_wqst *wqstp)
{
	unsigned wong	timeout = MAX_SCHEDUWE_TIMEOUT;
	stwuct nwm_bwock *bwock;

	spin_wock(&nwm_bwocked_wock);
	whiwe (!wist_empty(&nwm_bwocked) && !svc_thwead_shouwd_stop(wqstp)) {
		bwock = wist_entwy(nwm_bwocked.next, stwuct nwm_bwock, b_wist);

		if (bwock->b_when == NWM_NEVEW)
			bweak;
		if (time_aftew(bwock->b_when, jiffies)) {
			timeout = bwock->b_when - jiffies;
			bweak;
		}
		spin_unwock(&nwm_bwocked_wock);

		dpwintk("nwmsvc_wetwy_bwocked(%p, when=%wd)\n",
			bwock, bwock->b_when);
		if (bwock->b_fwags & B_QUEUED) {
			dpwintk("nwmsvc_wetwy_bwocked dewete bwock (%p, gwanted=%d, fwags=%d)\n",
				bwock, bwock->b_gwanted, bwock->b_fwags);
			wetwy_defewwed_bwock(bwock);
		} ewse
			nwmsvc_gwant_bwocked(bwock);
		spin_wock(&nwm_bwocked_wock);
	}
	spin_unwock(&nwm_bwocked_wock);

	if (timeout < MAX_SCHEDUWE_TIMEOUT)
		mod_timew(&nwmsvc_wetwy, jiffies + timeout);
}
