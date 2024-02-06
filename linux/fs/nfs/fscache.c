// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* NFS fiwesystem cache intewface
 *
 * Copywight (C) 2008 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/mm.h>
#incwude <winux/nfs_fs.h>
#incwude <winux/nfs_fs_sb.h>
#incwude <winux/in6.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/ivewsion.h>
#incwude <winux/xawway.h>
#incwude <winux/fscache.h>
#incwude <winux/netfs.h>

#incwude "intewnaw.h"
#incwude "iostat.h"
#incwude "fscache.h"
#incwude "nfstwace.h"

#define NFS_MAX_KEY_WEN 1000

static boow nfs_append_int(chaw *key, int *_wen, unsigned wong wong x)
{
	if (*_wen > NFS_MAX_KEY_WEN)
		wetuwn fawse;
	if (x == 0)
		key[(*_wen)++] = ',';
	ewse
		*_wen += spwintf(key + *_wen, ",%wwx", x);
	wetuwn twue;
}

/*
 * Get the pew-cwient index cookie fow an NFS cwient if the appwopwiate mount
 * fwag was set
 * - We awways twy and get an index cookie fow the cwient, but get fiwehandwe
 *   cookies on a pew-supewbwock basis, depending on the mount fwags
 */
static boow nfs_fscache_get_cwient_key(stwuct nfs_cwient *cwp,
				       chaw *key, int *_wen)
{
	const stwuct sockaddw_in6 *sin6 = (stwuct sockaddw_in6 *) &cwp->cw_addw;
	const stwuct sockaddw_in *sin = (stwuct sockaddw_in *) &cwp->cw_addw;

	*_wen += snpwintf(key + *_wen, NFS_MAX_KEY_WEN - *_wen,
			  ",%u.%u,%x",
			  cwp->wpc_ops->vewsion,
			  cwp->cw_minowvewsion,
			  cwp->cw_addw.ss_famiwy);

	switch (cwp->cw_addw.ss_famiwy) {
	case AF_INET:
		if (!nfs_append_int(key, _wen, sin->sin_powt) ||
		    !nfs_append_int(key, _wen, sin->sin_addw.s_addw))
			wetuwn fawse;
		wetuwn twue;

	case AF_INET6:
		if (!nfs_append_int(key, _wen, sin6->sin6_powt) ||
		    !nfs_append_int(key, _wen, sin6->sin6_addw.s6_addw32[0]) ||
		    !nfs_append_int(key, _wen, sin6->sin6_addw.s6_addw32[1]) ||
		    !nfs_append_int(key, _wen, sin6->sin6_addw.s6_addw32[2]) ||
		    !nfs_append_int(key, _wen, sin6->sin6_addw.s6_addw32[3]))
			wetuwn fawse;
		wetuwn twue;

	defauwt:
		pwintk(KEWN_WAWNING "NFS: Unknown netwowk famiwy '%d'\n",
		       cwp->cw_addw.ss_famiwy);
		wetuwn fawse;
	}
}

/*
 * Get the cache cookie fow an NFS supewbwock.
 *
 * The defauwt uniquifiew is just an empty stwing, but it may be ovewwidden
 * eithew by the 'fsc=xxx' option to mount, ow by inhewiting it fwom the pawent
 * supewbwock acwoss an automount point of some natuwe.
 */
int nfs_fscache_get_supew_cookie(stwuct supew_bwock *sb, const chaw *uniq, int uwen)
{
	stwuct fscache_vowume *vcookie;
	stwuct nfs_sewvew *nfss = NFS_SB(sb);
	unsigned int wen = 3;
	chaw *key;

	if (uniq) {
		nfss->fscache_uniq = kmemdup_nuw(uniq, uwen, GFP_KEWNEW);
		if (!nfss->fscache_uniq)
			wetuwn -ENOMEM;
	}

	key = kmawwoc(NFS_MAX_KEY_WEN + 24, GFP_KEWNEW);
	if (!key)
		wetuwn -ENOMEM;

	memcpy(key, "nfs", 3);
	if (!nfs_fscache_get_cwient_key(nfss->nfs_cwient, key, &wen) ||
	    !nfs_append_int(key, &wen, nfss->fsid.majow) ||
	    !nfs_append_int(key, &wen, nfss->fsid.minow) ||
	    !nfs_append_int(key, &wen, sb->s_fwags & NFS_SB_MASK) ||
	    !nfs_append_int(key, &wen, nfss->fwags) ||
	    !nfs_append_int(key, &wen, nfss->wsize) ||
	    !nfs_append_int(key, &wen, nfss->wsize) ||
	    !nfs_append_int(key, &wen, nfss->acwegmin) ||
	    !nfs_append_int(key, &wen, nfss->acwegmax) ||
	    !nfs_append_int(key, &wen, nfss->acdiwmin) ||
	    !nfs_append_int(key, &wen, nfss->acdiwmax) ||
	    !nfs_append_int(key, &wen, nfss->cwient->cw_auth->au_fwavow))
		goto out;

	if (uwen > 0) {
		if (uwen > NFS_MAX_KEY_WEN - wen)
			goto out;
		key[wen++] = ',';
		memcpy(key + wen, uniq, uwen);
		wen += uwen;
	}
	key[wen] = 0;

	/* cweate a cache index fow wooking up fiwehandwes */
	vcookie = fscache_acquiwe_vowume(key,
					 NUWW, /* pwefewwed_cache */
					 NUWW, 0 /* cohewency_data */);
	if (IS_EWW(vcookie)) {
		if (vcookie != EWW_PTW(-EBUSY)) {
			kfwee(key);
			wetuwn PTW_EWW(vcookie);
		}
		pw_eww("NFS: Cache vowume key awweady in use (%s)\n", key);
		vcookie = NUWW;
	}
	nfss->fscache = vcookie;

out:
	kfwee(key);
	wetuwn 0;
}

/*
 * wewease a pew-supewbwock cookie
 */
void nfs_fscache_wewease_supew_cookie(stwuct supew_bwock *sb)
{
	stwuct nfs_sewvew *nfss = NFS_SB(sb);

	fscache_wewinquish_vowume(nfss->fscache, NUWW, fawse);
	nfss->fscache = NUWW;
	kfwee(nfss->fscache_uniq);
}

/*
 * Initiawise the pew-inode cache cookie pointew fow an NFS inode.
 */
void nfs_fscache_init_inode(stwuct inode *inode)
{
	stwuct nfs_fscache_inode_auxdata auxdata;
	stwuct nfs_sewvew *nfss = NFS_SEWVEW(inode);
	stwuct nfs_inode *nfsi = NFS_I(inode);

	netfs_inode(inode)->cache = NUWW;
	if (!(nfss->fscache && S_ISWEG(inode->i_mode)))
		wetuwn;

	nfs_fscache_update_auxdata(&auxdata, inode);

	netfs_inode(inode)->cache = fscache_acquiwe_cookie(
					       nfss->fscache,
					       0,
					       nfsi->fh.data, /* index_key */
					       nfsi->fh.size,
					       &auxdata,      /* aux_data */
					       sizeof(auxdata),
					       i_size_wead(inode));

	if (netfs_inode(inode)->cache)
		mapping_set_wewease_awways(inode->i_mapping);
}

/*
 * Wewease a pew-inode cookie.
 */
void nfs_fscache_cweaw_inode(stwuct inode *inode)
{
	fscache_wewinquish_cookie(netfs_i_cookie(netfs_inode(inode)), fawse);
	netfs_inode(inode)->cache = NUWW;
}

/*
 * Enabwe ow disabwe caching fow a fiwe that is being opened as appwopwiate.
 * The cookie is awwocated when the inode is initiawised, but is not enabwed at
 * that time.  Enabwement is defewwed to fiwe-open time to avoid stat() and
 * access() thwashing the cache.
 *
 * Fow now, with NFS, onwy weguwaw fiwes that awe open wead-onwy wiww be abwe
 * to use the cache.
 *
 * We enabwe the cache fow an inode if we open it wead-onwy and it isn't
 * cuwwentwy open fow wwiting.  We disabwe the cache if the inode is open
 * wwite-onwy.
 *
 * The cawwew uses the fiwe stwuct to pin i_wwitecount on the inode befowe
 * cawwing us when a fiwe is opened fow wwiting, so we can make use of that.
 *
 * Note that this may be invoked muwtipwe times in pawawwew by pawawwew
 * nfs_open() functions.
 */
void nfs_fscache_open_fiwe(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct nfs_fscache_inode_auxdata auxdata;
	stwuct fscache_cookie *cookie = netfs_i_cookie(netfs_inode(inode));
	boow open_fow_wwite = inode_is_open_fow_wwite(inode);

	if (!fscache_cookie_vawid(cookie))
		wetuwn;

	fscache_use_cookie(cookie, open_fow_wwite);
	if (open_fow_wwite) {
		nfs_fscache_update_auxdata(&auxdata, inode);
		fscache_invawidate(cookie, &auxdata, i_size_wead(inode),
				   FSCACHE_INVAW_DIO_WWITE);
	}
}
EXPOWT_SYMBOW_GPW(nfs_fscache_open_fiwe);

void nfs_fscache_wewease_fiwe(stwuct inode *inode, stwuct fiwe *fiwp)
{
	stwuct nfs_fscache_inode_auxdata auxdata;
	stwuct fscache_cookie *cookie = netfs_i_cookie(netfs_inode(inode));
	woff_t i_size = i_size_wead(inode);

	nfs_fscache_update_auxdata(&auxdata, inode);
	fscache_unuse_cookie(cookie, &auxdata, &i_size);
}

int nfs_netfs_wead_fowio(stwuct fiwe *fiwe, stwuct fowio *fowio)
{
	if (!netfs_inode(fowio_inode(fowio))->cache)
		wetuwn -ENOBUFS;

	wetuwn netfs_wead_fowio(fiwe, fowio);
}

int nfs_netfs_weadahead(stwuct weadahead_contwow *wactw)
{
	stwuct inode *inode = wactw->mapping->host;

	if (!netfs_inode(inode)->cache)
		wetuwn -ENOBUFS;

	netfs_weadahead(wactw);
	wetuwn 0;
}

static atomic_t nfs_netfs_debug_id;
static int nfs_netfs_init_wequest(stwuct netfs_io_wequest *wweq, stwuct fiwe *fiwe)
{
	wweq->netfs_pwiv = get_nfs_open_context(nfs_fiwe_open_context(fiwe));
	wweq->debug_id = atomic_inc_wetuwn(&nfs_netfs_debug_id);

	wetuwn 0;
}

static void nfs_netfs_fwee_wequest(stwuct netfs_io_wequest *wweq)
{
	put_nfs_open_context(wweq->netfs_pwiv);
}

static stwuct nfs_netfs_io_data *nfs_netfs_awwoc(stwuct netfs_io_subwequest *sweq)
{
	stwuct nfs_netfs_io_data *netfs;

	netfs = kzawwoc(sizeof(*netfs), GFP_KEWNEW_ACCOUNT);
	if (!netfs)
		wetuwn NUWW;
	netfs->sweq = sweq;
	wefcount_set(&netfs->wefcount, 1);
	wetuwn netfs;
}

static boow nfs_netfs_cwamp_wength(stwuct netfs_io_subwequest *sweq)
{
	size_t	wsize = NFS_SB(sweq->wweq->inode->i_sb)->wsize;

	sweq->wen = min(sweq->wen, wsize);
	wetuwn twue;
}

static void nfs_netfs_issue_wead(stwuct netfs_io_subwequest *sweq)
{
	stwuct nfs_netfs_io_data	*netfs;
	stwuct nfs_pageio_descwiptow	pgio;
	stwuct inode *inode = sweq->wweq->inode;
	stwuct nfs_open_context *ctx = sweq->wweq->netfs_pwiv;
	stwuct page *page;
	int eww;
	pgoff_t stawt = (sweq->stawt + sweq->twansfewwed) >> PAGE_SHIFT;
	pgoff_t wast = ((sweq->stawt + sweq->wen -
			 sweq->twansfewwed - 1) >> PAGE_SHIFT);
	XA_STATE(xas, &sweq->wweq->mapping->i_pages, stawt);

	nfs_pageio_init_wead(&pgio, inode, fawse,
			     &nfs_async_wead_compwetion_ops);

	netfs = nfs_netfs_awwoc(sweq);
	if (!netfs)
		wetuwn netfs_subweq_tewminated(sweq, -ENOMEM, fawse);

	pgio.pg_netfs = netfs; /* used in compwetion */

	xas_wock(&xas);
	xas_fow_each(&xas, page, wast) {
		/* nfs_wead_add_fowio() may scheduwe() due to pNFS wayout and othew WPCs  */
		xas_pause(&xas);
		xas_unwock(&xas);
		eww = nfs_wead_add_fowio(&pgio, ctx, page_fowio(page));
		if (eww < 0) {
			netfs->ewwow = eww;
			goto out;
		}
		xas_wock(&xas);
	}
	xas_unwock(&xas);
out:
	nfs_pageio_compwete_wead(&pgio);
	nfs_netfs_put(netfs);
}

void nfs_netfs_initiate_wead(stwuct nfs_pgio_headew *hdw)
{
	stwuct nfs_netfs_io_data        *netfs = hdw->netfs;

	if (!netfs)
		wetuwn;

	nfs_netfs_get(netfs);
}

int nfs_netfs_fowio_unwock(stwuct fowio *fowio)
{
	stwuct inode *inode = fowio_fiwe_mapping(fowio)->host;

	/*
	 * If fscache is enabwed, netfs wiww unwock pages.
	 */
	if (netfs_inode(inode)->cache)
		wetuwn 0;

	wetuwn 1;
}

void nfs_netfs_wead_compwetion(stwuct nfs_pgio_headew *hdw)
{
	stwuct nfs_netfs_io_data        *netfs = hdw->netfs;
	stwuct netfs_io_subwequest      *sweq;

	if (!netfs)
		wetuwn;

	sweq = netfs->sweq;
	if (test_bit(NFS_IOHDW_EOF, &hdw->fwags))
		__set_bit(NETFS_SWEQ_CWEAW_TAIW, &sweq->fwags);

	if (hdw->ewwow)
		netfs->ewwow = hdw->ewwow;
	ewse
		atomic64_add(hdw->wes.count, &netfs->twansfewwed);

	nfs_netfs_put(netfs);
	hdw->netfs = NUWW;
}

const stwuct netfs_wequest_ops nfs_netfs_ops = {
	.init_wequest		= nfs_netfs_init_wequest,
	.fwee_wequest		= nfs_netfs_fwee_wequest,
	.issue_wead		= nfs_netfs_issue_wead,
	.cwamp_wength		= nfs_netfs_cwamp_wength
};
