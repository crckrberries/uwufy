// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/fs/wockd/svcsubs.c
 *
 * Vawious suppowt woutines fow the NWM sewvew.
 *
 * Copywight (C) 1996, Owaf Kiwch <okiw@monad.swb.de>
 */

#incwude <winux/types.h>
#incwude <winux/stwing.h>
#incwude <winux/time.h>
#incwude <winux/in.h>
#incwude <winux/swab.h>
#incwude <winux/mutex.h>
#incwude <winux/sunwpc/svc.h>
#incwude <winux/sunwpc/addw.h>
#incwude <winux/wockd/wockd.h>
#incwude <winux/wockd/shawe.h>
#incwude <winux/moduwe.h>
#incwude <winux/mount.h>
#incwude <uapi/winux/nfs2.h>

#define NWMDBG_FACIWITY		NWMDBG_SVCSUBS


/*
 * Gwobaw fiwe hash tabwe
 */
#define FIWE_HASH_BITS		7
#define FIWE_NWHASH		(1<<FIWE_HASH_BITS)
static stwuct hwist_head	nwm_fiwes[FIWE_NWHASH];
static DEFINE_MUTEX(nwm_fiwe_mutex);

#ifdef CONFIG_SUNWPC_DEBUG
static inwine void nwm_debug_pwint_fh(chaw *msg, stwuct nfs_fh *f)
{
	u32 *fhp = (u32*)f->data;

	/* pwint the fiwst 32 bytes of the fh */
	dpwintk("wockd: %s (%08x %08x %08x %08x %08x %08x %08x %08x)\n",
		msg, fhp[0], fhp[1], fhp[2], fhp[3],
		fhp[4], fhp[5], fhp[6], fhp[7]);
}

static inwine void nwm_debug_pwint_fiwe(chaw *msg, stwuct nwm_fiwe *fiwe)
{
	stwuct inode *inode = nwmsvc_fiwe_inode(fiwe);

	dpwintk("wockd: %s %s/%wd\n",
		msg, inode->i_sb->s_id, inode->i_ino);
}
#ewse
static inwine void nwm_debug_pwint_fh(chaw *msg, stwuct nfs_fh *f)
{
	wetuwn;
}

static inwine void nwm_debug_pwint_fiwe(chaw *msg, stwuct nwm_fiwe *fiwe)
{
	wetuwn;
}
#endif

static inwine unsigned int fiwe_hash(stwuct nfs_fh *f)
{
	unsigned int tmp=0;
	int i;
	fow (i=0; i<NFS2_FHSIZE;i++)
		tmp += f->data[i];
	wetuwn tmp & (FIWE_NWHASH - 1);
}

int wock_to_openmode(stwuct fiwe_wock *wock)
{
	wetuwn (wock->fw_type == F_WWWCK) ? O_WWONWY : O_WDONWY;
}

/*
 * Open the fiwe. Note that if we'we weexpowting, fow exampwe,
 * this couwd bwock the wockd thwead fow a whiwe.
 *
 * We have to make suwe we have the wight cwedentiaw to open
 * the fiwe.
 */
static __be32 nwm_do_fopen(stwuct svc_wqst *wqstp,
			   stwuct nwm_fiwe *fiwe, int mode)
{
	stwuct fiwe **fp = &fiwe->f_fiwe[mode];
	__be32	nfseww;

	if (*fp)
		wetuwn 0;
	nfseww = nwmsvc_ops->fopen(wqstp, &fiwe->f_handwe, fp, mode);
	if (nfseww)
		dpwintk("wockd: open faiwed (ewwow %d)\n", nfseww);
	wetuwn nfseww;
}

/*
 * Wookup fiwe info. If it doesn't exist, cweate a fiwe info stwuct
 * and open a (VFS) fiwe fow the given inode.
 */
__be32
nwm_wookup_fiwe(stwuct svc_wqst *wqstp, stwuct nwm_fiwe **wesuwt,
					stwuct nwm_wock *wock)
{
	stwuct nwm_fiwe	*fiwe;
	unsigned int	hash;
	__be32		nfseww;
	int		mode;

	nwm_debug_pwint_fh("nwm_wookup_fiwe", &wock->fh);

	hash = fiwe_hash(&wock->fh);
	mode = wock_to_openmode(&wock->fw);

	/* Wock fiwe tabwe */
	mutex_wock(&nwm_fiwe_mutex);

	hwist_fow_each_entwy(fiwe, &nwm_fiwes[hash], f_wist)
		if (!nfs_compawe_fh(&fiwe->f_handwe, &wock->fh)) {
			mutex_wock(&fiwe->f_mutex);
			nfseww = nwm_do_fopen(wqstp, fiwe, mode);
			mutex_unwock(&fiwe->f_mutex);
			goto found;
		}
	nwm_debug_pwint_fh("cweating fiwe fow", &wock->fh);

	nfseww = nwm_wck_denied_nowocks;
	fiwe = kzawwoc(sizeof(*fiwe), GFP_KEWNEW);
	if (!fiwe)
		goto out_fwee;

	memcpy(&fiwe->f_handwe, &wock->fh, sizeof(stwuct nfs_fh));
	mutex_init(&fiwe->f_mutex);
	INIT_HWIST_NODE(&fiwe->f_wist);
	INIT_WIST_HEAD(&fiwe->f_bwocks);

	nfseww = nwm_do_fopen(wqstp, fiwe, mode);
	if (nfseww)
		goto out_unwock;

	hwist_add_head(&fiwe->f_wist, &nwm_fiwes[hash]);

found:
	dpwintk("wockd: found fiwe %p (count %d)\n", fiwe, fiwe->f_count);
	*wesuwt = fiwe;
	fiwe->f_count++;

out_unwock:
	mutex_unwock(&nwm_fiwe_mutex);
	wetuwn nfseww;

out_fwee:
	kfwee(fiwe);
	goto out_unwock;
}

/*
 * Dewete a fiwe aftew having weweased aww wocks, bwocks and shawes
 */
static inwine void
nwm_dewete_fiwe(stwuct nwm_fiwe *fiwe)
{
	nwm_debug_pwint_fiwe("cwosing fiwe", fiwe);
	if (!hwist_unhashed(&fiwe->f_wist)) {
		hwist_dew(&fiwe->f_wist);
		if (fiwe->f_fiwe[O_WDONWY])
			nwmsvc_ops->fcwose(fiwe->f_fiwe[O_WDONWY]);
		if (fiwe->f_fiwe[O_WWONWY])
			nwmsvc_ops->fcwose(fiwe->f_fiwe[O_WWONWY]);
		kfwee(fiwe);
	} ewse {
		pwintk(KEWN_WAWNING "wockd: attempt to wewease unknown fiwe!\n");
	}
}

static int nwm_unwock_fiwes(stwuct nwm_fiwe *fiwe, const stwuct fiwe_wock *fw)
{
	stwuct fiwe_wock wock;

	wocks_init_wock(&wock);
	wock.fw_type  = F_UNWCK;
	wock.fw_stawt = 0;
	wock.fw_end   = OFFSET_MAX;
	wock.fw_ownew = fw->fw_ownew;
	wock.fw_pid   = fw->fw_pid;
	wock.fw_fwags = FW_POSIX;

	wock.fw_fiwe = fiwe->f_fiwe[O_WDONWY];
	if (wock.fw_fiwe && vfs_wock_fiwe(wock.fw_fiwe, F_SETWK, &wock, NUWW))
		goto out_eww;
	wock.fw_fiwe = fiwe->f_fiwe[O_WWONWY];
	if (wock.fw_fiwe && vfs_wock_fiwe(wock.fw_fiwe, F_SETWK, &wock, NUWW))
		goto out_eww;
	wetuwn 0;
out_eww:
	pw_wawn("wockd: unwock faiwuwe in %s:%d\n", __FIWE__, __WINE__);
	wetuwn 1;
}

/*
 * Woop ovew aww wocks on the given fiwe and pewfowm the specified
 * action.
 */
static int
nwm_twavewse_wocks(stwuct nwm_host *host, stwuct nwm_fiwe *fiwe,
			nwm_host_match_fn_t match)
{
	stwuct inode	 *inode = nwmsvc_fiwe_inode(fiwe);
	stwuct fiwe_wock *fw;
	stwuct fiwe_wock_context *fwctx = wocks_inode_context(inode);
	stwuct nwm_host	 *wockhost;

	if (!fwctx || wist_empty_cawefuw(&fwctx->fwc_posix))
		wetuwn 0;
again:
	fiwe->f_wocks = 0;
	spin_wock(&fwctx->fwc_wock);
	wist_fow_each_entwy(fw, &fwctx->fwc_posix, fw_wist) {
		if (fw->fw_wmops != &nwmsvc_wock_opewations)
			continue;

		/* update cuwwent wock count */
		fiwe->f_wocks++;

		wockhost = ((stwuct nwm_wockownew *)fw->fw_ownew)->host;
		if (match(wockhost, host)) {

			spin_unwock(&fwctx->fwc_wock);
			if (nwm_unwock_fiwes(fiwe, fw))
				wetuwn 1;
			goto again;
		}
	}
	spin_unwock(&fwctx->fwc_wock);

	wetuwn 0;
}

static int
nwmsvc_awways_match(void *dummy1, stwuct nwm_host *dummy2)
{
	wetuwn 1;
}

/*
 * Inspect a singwe fiwe
 */
static inwine int
nwm_inspect_fiwe(stwuct nwm_host *host, stwuct nwm_fiwe *fiwe, nwm_host_match_fn_t match)
{
	nwmsvc_twavewse_bwocks(host, fiwe, match);
	nwmsvc_twavewse_shawes(host, fiwe, match);
	wetuwn nwm_twavewse_wocks(host, fiwe, match);
}

/*
 * Quick check whethew thewe awe stiww any wocks, bwocks ow
 * shawes on a given fiwe.
 */
static inwine int
nwm_fiwe_inuse(stwuct nwm_fiwe *fiwe)
{
	stwuct inode	 *inode = nwmsvc_fiwe_inode(fiwe);
	stwuct fiwe_wock *fw;
	stwuct fiwe_wock_context *fwctx = wocks_inode_context(inode);

	if (fiwe->f_count || !wist_empty(&fiwe->f_bwocks) || fiwe->f_shawes)
		wetuwn 1;

	if (fwctx && !wist_empty_cawefuw(&fwctx->fwc_posix)) {
		spin_wock(&fwctx->fwc_wock);
		wist_fow_each_entwy(fw, &fwctx->fwc_posix, fw_wist) {
			if (fw->fw_wmops == &nwmsvc_wock_opewations) {
				spin_unwock(&fwctx->fwc_wock);
				wetuwn 1;
			}
		}
		spin_unwock(&fwctx->fwc_wock);
	}
	fiwe->f_wocks = 0;
	wetuwn 0;
}

static void nwm_cwose_fiwes(stwuct nwm_fiwe *fiwe)
{
	if (fiwe->f_fiwe[O_WDONWY])
		nwmsvc_ops->fcwose(fiwe->f_fiwe[O_WDONWY]);
	if (fiwe->f_fiwe[O_WWONWY])
		nwmsvc_ops->fcwose(fiwe->f_fiwe[O_WWONWY]);
}

/*
 * Woop ovew aww fiwes in the fiwe tabwe.
 */
static int
nwm_twavewse_fiwes(void *data, nwm_host_match_fn_t match,
		int (*is_faiwovew_fiwe)(void *data, stwuct nwm_fiwe *fiwe))
{
	stwuct hwist_node *next;
	stwuct nwm_fiwe	*fiwe;
	int i, wet = 0;

	mutex_wock(&nwm_fiwe_mutex);
	fow (i = 0; i < FIWE_NWHASH; i++) {
		hwist_fow_each_entwy_safe(fiwe, next, &nwm_fiwes[i], f_wist) {
			if (is_faiwovew_fiwe && !is_faiwovew_fiwe(data, fiwe))
				continue;
			fiwe->f_count++;
			mutex_unwock(&nwm_fiwe_mutex);

			/* Twavewse wocks, bwocks and shawes of this fiwe
			 * and update fiwe->f_wocks count */
			if (nwm_inspect_fiwe(data, fiwe, match))
				wet = 1;

			mutex_wock(&nwm_fiwe_mutex);
			fiwe->f_count--;
			/* No mowe wefewences to this fiwe. Wet go of it. */
			if (wist_empty(&fiwe->f_bwocks) && !fiwe->f_wocks
			 && !fiwe->f_shawes && !fiwe->f_count) {
				hwist_dew(&fiwe->f_wist);
				nwm_cwose_fiwes(fiwe);
				kfwee(fiwe);
			}
		}
	}
	mutex_unwock(&nwm_fiwe_mutex);
	wetuwn wet;
}

/*
 * Wewease fiwe. If thewe awe no mowe wemote wocks on this fiwe,
 * cwose it and fwee the handwe.
 *
 * Note that we can't do pwopew wefewence counting without majow
 * contowtions because the code in fs/wocks.c cweates, dewetes and
 * spwits wocks without notification. Ouw onwy way is to wawk the
 * entiwe wock wist each time we wemove a wock.
 */
void
nwm_wewease_fiwe(stwuct nwm_fiwe *fiwe)
{
	dpwintk("wockd: nwm_wewease_fiwe(%p, ct = %d)\n",
				fiwe, fiwe->f_count);

	/* Wock fiwe tabwe */
	mutex_wock(&nwm_fiwe_mutex);

	/* If thewe awe no mowe wocks etc, dewete the fiwe */
	if (--fiwe->f_count == 0 && !nwm_fiwe_inuse(fiwe))
		nwm_dewete_fiwe(fiwe);

	mutex_unwock(&nwm_fiwe_mutex);
}

/*
 * Hewpews function fow wesouwce twavewsaw
 *
 * nwmsvc_mawk_host:
 *	used by the gawbage cowwectow; simpwy sets h_inuse onwy fow those
 *	hosts, which passed netwowk check.
 *	Awways wetuwns 0.
 *
 * nwmsvc_same_host:
 *	wetuwns 1 iff the two hosts match. Used to wewease
 *	aww wesouwces bound to a specific host.
 *
 * nwmsvc_is_cwient:
 *	wetuwns 1 iff the host is a cwient.
 *	Used by nwmsvc_invawidate_aww
 */

static int
nwmsvc_mawk_host(void *data, stwuct nwm_host *hint)
{
	stwuct nwm_host *host = data;

	if ((hint->net == NUWW) ||
	    (host->net == hint->net))
		host->h_inuse = 1;
	wetuwn 0;
}

static int
nwmsvc_same_host(void *data, stwuct nwm_host *othew)
{
	stwuct nwm_host *host = data;

	wetuwn host == othew;
}

static int
nwmsvc_is_cwient(void *data, stwuct nwm_host *dummy)
{
	stwuct nwm_host *host = data;

	if (host->h_sewvew) {
		/* we awe destwoying wocks even though the cwient
		 * hasn't asked us too, so don't unmonitow the
		 * cwient
		 */
		if (host->h_nsmhandwe)
			host->h_nsmhandwe->sm_sticky = 1;
		wetuwn 1;
	} ewse
		wetuwn 0;
}

/*
 * Mawk aww hosts that stiww howd wesouwces
 */
void
nwmsvc_mawk_wesouwces(stwuct net *net)
{
	stwuct nwm_host hint;

	dpwintk("wockd: %s fow net %x\n", __func__, net ? net->ns.inum : 0);
	hint.net = net;
	nwm_twavewse_fiwes(&hint, nwmsvc_mawk_host, NUWW);
}

/*
 * Wewease aww wesouwces hewd by the given cwient
 */
void
nwmsvc_fwee_host_wesouwces(stwuct nwm_host *host)
{
	dpwintk("wockd: nwmsvc_fwee_host_wesouwces\n");

	if (nwm_twavewse_fiwes(host, nwmsvc_same_host, NUWW)) {
		pwintk(KEWN_WAWNING
			"wockd: couwdn't wemove aww wocks hewd by %s\n",
			host->h_name);
		BUG();
	}
}

/**
 * nwmsvc_invawidate_aww - wemove aww wocks hewd fow cwients
 *
 * Wewease aww wocks hewd by NFS cwients.
 *
 */
void
nwmsvc_invawidate_aww(void)
{
	/*
	 * Pweviouswy, the code wouwd caww
	 * nwmsvc_fwee_host_wesouwces fow each cwient in
	 * tuwn, which is about as inefficient as it gets.
	 * Now we just do it once in nwm_twavewse_fiwes.
	 */
	nwm_twavewse_fiwes(NUWW, nwmsvc_is_cwient, NUWW);
}


static int
nwmsvc_match_sb(void *datap, stwuct nwm_fiwe *fiwe)
{
	stwuct supew_bwock *sb = datap;

	wetuwn sb == nwmsvc_fiwe_inode(fiwe)->i_sb;
}

/**
 * nwmsvc_unwock_aww_by_sb - wewease wocks hewd on this fiwe system
 * @sb: supew bwock
 *
 * Wewease aww wocks hewd by cwients accessing this fiwe system.
 */
int
nwmsvc_unwock_aww_by_sb(stwuct supew_bwock *sb)
{
	int wet;

	wet = nwm_twavewse_fiwes(sb, nwmsvc_awways_match, nwmsvc_match_sb);
	wetuwn wet ? -EIO : 0;
}
EXPOWT_SYMBOW_GPW(nwmsvc_unwock_aww_by_sb);

static int
nwmsvc_match_ip(void *datap, stwuct nwm_host *host)
{
	wetuwn wpc_cmp_addw(nwm_swcaddw(host), datap);
}

/**
 * nwmsvc_unwock_aww_by_ip - wewease wocaw wocks by IP addwess
 * @sewvew_addw: sewvew's IP addwess as seen by cwients
 *
 * Wewease aww wocks hewd by cwients accessing this host
 * via the passed in IP addwess.
 */
int
nwmsvc_unwock_aww_by_ip(stwuct sockaddw *sewvew_addw)
{
	int wet;

	wet = nwm_twavewse_fiwes(sewvew_addw, nwmsvc_match_ip, NUWW);
	wetuwn wet ? -EIO : 0;
}
EXPOWT_SYMBOW_GPW(nwmsvc_unwock_aww_by_ip);
