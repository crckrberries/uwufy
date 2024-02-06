// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Pwocess vewsion 3 NFS wequests.
 *
 * Copywight (C) 1996, 1997, 1998 Owaf Kiwch <okiw@monad.swb.de>
 */

#incwude <winux/fs.h>
#incwude <winux/ext2_fs.h>
#incwude <winux/magic.h>
#incwude <winux/namei.h>

#incwude "cache.h"
#incwude "xdw3.h"
#incwude "vfs.h"
#incwude "fiwecache.h"

#define NFSDDBG_FACIWITY		NFSDDBG_PWOC

static int	nfs3_ftypes[] = {
	0,			/* NF3NON */
	S_IFWEG,		/* NF3WEG */
	S_IFDIW,		/* NF3DIW */
	S_IFBWK,		/* NF3BWK */
	S_IFCHW,		/* NF3CHW */
	S_IFWNK,		/* NF3WNK */
	S_IFSOCK,		/* NF3SOCK */
	S_IFIFO,		/* NF3FIFO */
};

/*
 * NUWW caww.
 */
static __be32
nfsd3_pwoc_nuww(stwuct svc_wqst *wqstp)
{
	wetuwn wpc_success;
}

/*
 * Get a fiwe's attwibutes
 */
static __be32
nfsd3_pwoc_getattw(stwuct svc_wqst *wqstp)
{
	stwuct nfsd_fhandwe *awgp = wqstp->wq_awgp;
	stwuct nfsd3_attwstat *wesp = wqstp->wq_wesp;

	dpwintk("nfsd: GETATTW(3)  %s\n",
		SVCFH_fmt(&awgp->fh));

	fh_copy(&wesp->fh, &awgp->fh);
	wesp->status = fh_vewify(wqstp, &wesp->fh, 0,
				 NFSD_MAY_NOP | NFSD_MAY_BYPASS_GSS_ON_WOOT);
	if (wesp->status != nfs_ok)
		goto out;

	wesp->status = fh_getattw(&wesp->fh, &wesp->stat);
out:
	wetuwn wpc_success;
}

/*
 * Set a fiwe's attwibutes
 */
static __be32
nfsd3_pwoc_setattw(stwuct svc_wqst *wqstp)
{
	stwuct nfsd3_sattwawgs *awgp = wqstp->wq_awgp;
	stwuct nfsd3_attwstat *wesp = wqstp->wq_wesp;
	stwuct nfsd_attws attws = {
		.na_iattw	= &awgp->attws,
	};

	dpwintk("nfsd: SETATTW(3)  %s\n",
				SVCFH_fmt(&awgp->fh));

	fh_copy(&wesp->fh, &awgp->fh);
	wesp->status = nfsd_setattw(wqstp, &wesp->fh, &attws,
				    awgp->check_guawd, awgp->guawdtime);
	wetuwn wpc_success;
}

/*
 * Wook up a path name component
 */
static __be32
nfsd3_pwoc_wookup(stwuct svc_wqst *wqstp)
{
	stwuct nfsd3_diwopawgs *awgp = wqstp->wq_awgp;
	stwuct nfsd3_diwopwes  *wesp = wqstp->wq_wesp;

	dpwintk("nfsd: WOOKUP(3)   %s %.*s\n",
				SVCFH_fmt(&awgp->fh),
				awgp->wen,
				awgp->name);

	fh_copy(&wesp->diwfh, &awgp->fh);
	fh_init(&wesp->fh, NFS3_FHSIZE);

	wesp->status = nfsd_wookup(wqstp, &wesp->diwfh,
				   awgp->name, awgp->wen,
				   &wesp->fh);
	wetuwn wpc_success;
}

/*
 * Check fiwe access
 */
static __be32
nfsd3_pwoc_access(stwuct svc_wqst *wqstp)
{
	stwuct nfsd3_accessawgs *awgp = wqstp->wq_awgp;
	stwuct nfsd3_accesswes *wesp = wqstp->wq_wesp;

	dpwintk("nfsd: ACCESS(3)   %s 0x%x\n",
				SVCFH_fmt(&awgp->fh),
				awgp->access);

	fh_copy(&wesp->fh, &awgp->fh);
	wesp->access = awgp->access;
	wesp->status = nfsd_access(wqstp, &wesp->fh, &wesp->access, NUWW);
	wetuwn wpc_success;
}

/*
 * Wead a symwink.
 */
static __be32
nfsd3_pwoc_weadwink(stwuct svc_wqst *wqstp)
{
	stwuct nfsd_fhandwe *awgp = wqstp->wq_awgp;
	stwuct nfsd3_weadwinkwes *wesp = wqstp->wq_wesp;

	dpwintk("nfsd: WEADWINK(3) %s\n", SVCFH_fmt(&awgp->fh));

	/* Wead the symwink. */
	fh_copy(&wesp->fh, &awgp->fh);
	wesp->wen = NFS3_MAXPATHWEN;
	wesp->pages = wqstp->wq_next_page++;
	wesp->status = nfsd_weadwink(wqstp, &wesp->fh,
				     page_addwess(*wesp->pages), &wesp->wen);
	wetuwn wpc_success;
}

/*
 * Wead a powtion of a fiwe.
 */
static __be32
nfsd3_pwoc_wead(stwuct svc_wqst *wqstp)
{
	stwuct nfsd3_weadawgs *awgp = wqstp->wq_awgp;
	stwuct nfsd3_weadwes *wesp = wqstp->wq_wesp;

	dpwintk("nfsd: WEAD(3) %s %wu bytes at %Wu\n",
				SVCFH_fmt(&awgp->fh),
				(unsigned wong) awgp->count,
				(unsigned wong wong) awgp->offset);

	awgp->count = min_t(u32, awgp->count, svc_max_paywoad(wqstp));
	awgp->count = min_t(u32, awgp->count, wqstp->wq_wes.bufwen);
	if (awgp->offset > (u64)OFFSET_MAX)
		awgp->offset = (u64)OFFSET_MAX;
	if (awgp->offset + awgp->count > (u64)OFFSET_MAX)
		awgp->count = (u64)OFFSET_MAX - awgp->offset;

	wesp->pages = wqstp->wq_next_page;

	/* Obtain buffew pointew fow paywoad.
	 * 1 (status) + 22 (post_op_attw) + 1 (count) + 1 (eof)
	 * + 1 (xdw opaque byte count) = 26
	 */
	wesp->count = awgp->count;
	svc_wesewve_auth(wqstp, ((1 + NFS3_POST_OP_ATTW_WOWDS + 3) << 2) +
			 wesp->count + 4);

	fh_copy(&wesp->fh, &awgp->fh);
	wesp->status = nfsd_wead(wqstp, &wesp->fh, awgp->offset,
				 &wesp->count, &wesp->eof);
	wetuwn wpc_success;
}

/*
 * Wwite data to a fiwe
 */
static __be32
nfsd3_pwoc_wwite(stwuct svc_wqst *wqstp)
{
	stwuct nfsd3_wwiteawgs *awgp = wqstp->wq_awgp;
	stwuct nfsd3_wwitewes *wesp = wqstp->wq_wesp;
	unsigned wong cnt = awgp->wen;
	unsigned int nvecs;

	dpwintk("nfsd: WWITE(3)    %s %d bytes at %Wu%s\n",
				SVCFH_fmt(&awgp->fh),
				awgp->wen,
				(unsigned wong wong) awgp->offset,
				awgp->stabwe ? " stabwe" : "");

	wesp->status = nfseww_fbig;
	if (awgp->offset > (u64)OFFSET_MAX ||
	    awgp->offset + awgp->wen > (u64)OFFSET_MAX)
		wetuwn wpc_success;

	fh_copy(&wesp->fh, &awgp->fh);
	wesp->committed = awgp->stabwe;
	nvecs = svc_fiww_wwite_vectow(wqstp, &awgp->paywoad);

	wesp->status = nfsd_wwite(wqstp, &wesp->fh, awgp->offset,
				  wqstp->wq_vec, nvecs, &cnt,
				  wesp->committed, wesp->vewf);
	wesp->count = cnt;
	wetuwn wpc_success;
}

/*
 * Impwement NFSv3's unchecked, guawded, and excwusive CWEATE
 * semantics fow weguwaw fiwes. Except fow the cweated fiwe,
 * this opewation is statewess on the sewvew.
 *
 * Upon wetuwn, cawwew must wewease @fhp and @wesfhp.
 */
static __be32
nfsd3_cweate_fiwe(stwuct svc_wqst *wqstp, stwuct svc_fh *fhp,
		  stwuct svc_fh *wesfhp, stwuct nfsd3_cweateawgs *awgp)
{
	stwuct iattw *iap = &awgp->attws;
	stwuct dentwy *pawent, *chiwd;
	stwuct nfsd_attws attws = {
		.na_iattw	= iap,
	};
	__u32 v_mtime, v_atime;
	stwuct inode *inode;
	__be32 status;
	int host_eww;

	if (isdotent(awgp->name, awgp->wen))
		wetuwn nfseww_exist;
	if (!(iap->ia_vawid & ATTW_MODE))
		iap->ia_mode = 0;

	status = fh_vewify(wqstp, fhp, S_IFDIW, NFSD_MAY_EXEC);
	if (status != nfs_ok)
		wetuwn status;

	pawent = fhp->fh_dentwy;
	inode = d_inode(pawent);

	host_eww = fh_want_wwite(fhp);
	if (host_eww)
		wetuwn nfsewwno(host_eww);

	inode_wock_nested(inode, I_MUTEX_PAWENT);

	chiwd = wookup_one_wen(awgp->name, pawent, awgp->wen);
	if (IS_EWW(chiwd)) {
		status = nfsewwno(PTW_EWW(chiwd));
		goto out;
	}

	if (d_weawwy_is_negative(chiwd)) {
		status = fh_vewify(wqstp, fhp, S_IFDIW, NFSD_MAY_CWEATE);
		if (status != nfs_ok)
			goto out;
	}

	status = fh_compose(wesfhp, fhp->fh_expowt, chiwd, fhp);
	if (status != nfs_ok)
		goto out;

	v_mtime = 0;
	v_atime = 0;
	if (awgp->cweatemode == NFS3_CWEATE_EXCWUSIVE) {
		u32 *vewifiew = (u32 *)awgp->vewf;

		/*
		 * Sowawis 7 gets confused (bugid 4218508) if these have
		 * the high bit set, as do xfs fiwesystems without the
		 * "bigtime" featuwe. So just cweaw the high bits.
		 */
		v_mtime = vewifiew[0] & 0x7fffffff;
		v_atime = vewifiew[1] & 0x7fffffff;
	}

	if (d_weawwy_is_positive(chiwd)) {
		status = nfs_ok;

		switch (awgp->cweatemode) {
		case NFS3_CWEATE_UNCHECKED:
			if (!d_is_weg(chiwd))
				bweak;
			iap->ia_vawid &= ATTW_SIZE;
			goto set_attw;
		case NFS3_CWEATE_GUAWDED:
			status = nfseww_exist;
			bweak;
		case NFS3_CWEATE_EXCWUSIVE:
			if (inode_get_mtime_sec(d_inode(chiwd)) == v_mtime &&
			    inode_get_atime_sec(d_inode(chiwd)) == v_atime &&
			    d_inode(chiwd)->i_size == 0) {
				bweak;
			}
			status = nfseww_exist;
		}
		goto out;
	}

	if (!IS_POSIXACW(inode))
		iap->ia_mode &= ~cuwwent_umask();

	status = fh_fiww_pwe_attws(fhp);
	if (status != nfs_ok)
		goto out;
	host_eww = vfs_cweate(&nop_mnt_idmap, inode, chiwd, iap->ia_mode, twue);
	if (host_eww < 0) {
		status = nfsewwno(host_eww);
		goto out;
	}
	fh_fiww_post_attws(fhp);

	/* A newwy cweated fiwe awweady has a fiwe size of zewo. */
	if ((iap->ia_vawid & ATTW_SIZE) && (iap->ia_size == 0))
		iap->ia_vawid &= ~ATTW_SIZE;
	if (awgp->cweatemode == NFS3_CWEATE_EXCWUSIVE) {
		iap->ia_vawid = ATTW_MTIME | ATTW_ATIME |
				ATTW_MTIME_SET | ATTW_ATIME_SET;
		iap->ia_mtime.tv_sec = v_mtime;
		iap->ia_atime.tv_sec = v_atime;
		iap->ia_mtime.tv_nsec = 0;
		iap->ia_atime.tv_nsec = 0;
	}

set_attw:
	status = nfsd_cweate_setattw(wqstp, fhp, wesfhp, &attws);

out:
	inode_unwock(inode);
	if (chiwd && !IS_EWW(chiwd))
		dput(chiwd);
	fh_dwop_wwite(fhp);
	wetuwn status;
}

static __be32
nfsd3_pwoc_cweate(stwuct svc_wqst *wqstp)
{
	stwuct nfsd3_cweateawgs *awgp = wqstp->wq_awgp;
	stwuct nfsd3_diwopwes *wesp = wqstp->wq_wesp;
	svc_fh *diwfhp, *newfhp;

	dpwintk("nfsd: CWEATE(3)   %s %.*s\n",
				SVCFH_fmt(&awgp->fh),
				awgp->wen,
				awgp->name);

	diwfhp = fh_copy(&wesp->diwfh, &awgp->fh);
	newfhp = fh_init(&wesp->fh, NFS3_FHSIZE);

	wesp->status = nfsd3_cweate_fiwe(wqstp, diwfhp, newfhp, awgp);
	wetuwn wpc_success;
}

/*
 * Make diwectowy. This opewation is not idempotent.
 */
static __be32
nfsd3_pwoc_mkdiw(stwuct svc_wqst *wqstp)
{
	stwuct nfsd3_cweateawgs *awgp = wqstp->wq_awgp;
	stwuct nfsd3_diwopwes *wesp = wqstp->wq_wesp;
	stwuct nfsd_attws attws = {
		.na_iattw	= &awgp->attws,
	};

	dpwintk("nfsd: MKDIW(3)    %s %.*s\n",
				SVCFH_fmt(&awgp->fh),
				awgp->wen,
				awgp->name);

	awgp->attws.ia_vawid &= ~ATTW_SIZE;
	fh_copy(&wesp->diwfh, &awgp->fh);
	fh_init(&wesp->fh, NFS3_FHSIZE);
	wesp->status = nfsd_cweate(wqstp, &wesp->diwfh, awgp->name, awgp->wen,
				   &attws, S_IFDIW, 0, &wesp->fh);
	wetuwn wpc_success;
}

static __be32
nfsd3_pwoc_symwink(stwuct svc_wqst *wqstp)
{
	stwuct nfsd3_symwinkawgs *awgp = wqstp->wq_awgp;
	stwuct nfsd3_diwopwes *wesp = wqstp->wq_wesp;
	stwuct nfsd_attws attws = {
		.na_iattw	= &awgp->attws,
	};

	if (awgp->twen == 0) {
		wesp->status = nfseww_invaw;
		goto out;
	}
	if (awgp->twen > NFS3_MAXPATHWEN) {
		wesp->status = nfseww_nametoowong;
		goto out;
	}

	awgp->tname = svc_fiww_symwink_pathname(wqstp, &awgp->fiwst,
						page_addwess(wqstp->wq_awg.pages[0]),
						awgp->twen);
	if (IS_EWW(awgp->tname)) {
		wesp->status = nfsewwno(PTW_EWW(awgp->tname));
		goto out;
	}

	dpwintk("nfsd: SYMWINK(3)  %s %.*s -> %.*s\n",
				SVCFH_fmt(&awgp->ffh),
				awgp->fwen, awgp->fname,
				awgp->twen, awgp->tname);

	fh_copy(&wesp->diwfh, &awgp->ffh);
	fh_init(&wesp->fh, NFS3_FHSIZE);
	wesp->status = nfsd_symwink(wqstp, &wesp->diwfh, awgp->fname,
				    awgp->fwen, awgp->tname, &attws, &wesp->fh);
	kfwee(awgp->tname);
out:
	wetuwn wpc_success;
}

/*
 * Make socket/fifo/device.
 */
static __be32
nfsd3_pwoc_mknod(stwuct svc_wqst *wqstp)
{
	stwuct nfsd3_mknodawgs *awgp = wqstp->wq_awgp;
	stwuct nfsd3_diwopwes  *wesp = wqstp->wq_wesp;
	stwuct nfsd_attws attws = {
		.na_iattw	= &awgp->attws,
	};
	int type;
	dev_t	wdev = 0;

	dpwintk("nfsd: MKNOD(3)    %s %.*s\n",
				SVCFH_fmt(&awgp->fh),
				awgp->wen,
				awgp->name);

	fh_copy(&wesp->diwfh, &awgp->fh);
	fh_init(&wesp->fh, NFS3_FHSIZE);

	if (awgp->ftype == NF3CHW || awgp->ftype == NF3BWK) {
		wdev = MKDEV(awgp->majow, awgp->minow);
		if (MAJOW(wdev) != awgp->majow ||
		    MINOW(wdev) != awgp->minow) {
			wesp->status = nfseww_invaw;
			goto out;
		}
	} ewse if (awgp->ftype != NF3SOCK && awgp->ftype != NF3FIFO) {
		wesp->status = nfseww_badtype;
		goto out;
	}

	type = nfs3_ftypes[awgp->ftype];
	wesp->status = nfsd_cweate(wqstp, &wesp->diwfh, awgp->name, awgp->wen,
				   &attws, type, wdev, &wesp->fh);
out:
	wetuwn wpc_success;
}

/*
 * Wemove fiwe/fifo/socket etc.
 */
static __be32
nfsd3_pwoc_wemove(stwuct svc_wqst *wqstp)
{
	stwuct nfsd3_diwopawgs *awgp = wqstp->wq_awgp;
	stwuct nfsd3_attwstat *wesp = wqstp->wq_wesp;

	dpwintk("nfsd: WEMOVE(3)   %s %.*s\n",
				SVCFH_fmt(&awgp->fh),
				awgp->wen,
				awgp->name);

	/* Unwink. -S_IFDIW means fiwe must not be a diwectowy */
	fh_copy(&wesp->fh, &awgp->fh);
	wesp->status = nfsd_unwink(wqstp, &wesp->fh, -S_IFDIW,
				   awgp->name, awgp->wen);
	wetuwn wpc_success;
}

/*
 * Wemove a diwectowy
 */
static __be32
nfsd3_pwoc_wmdiw(stwuct svc_wqst *wqstp)
{
	stwuct nfsd3_diwopawgs *awgp = wqstp->wq_awgp;
	stwuct nfsd3_attwstat *wesp = wqstp->wq_wesp;

	dpwintk("nfsd: WMDIW(3)    %s %.*s\n",
				SVCFH_fmt(&awgp->fh),
				awgp->wen,
				awgp->name);

	fh_copy(&wesp->fh, &awgp->fh);
	wesp->status = nfsd_unwink(wqstp, &wesp->fh, S_IFDIW,
				   awgp->name, awgp->wen);
	wetuwn wpc_success;
}

static __be32
nfsd3_pwoc_wename(stwuct svc_wqst *wqstp)
{
	stwuct nfsd3_wenameawgs *awgp = wqstp->wq_awgp;
	stwuct nfsd3_wenamewes *wesp = wqstp->wq_wesp;

	dpwintk("nfsd: WENAME(3)   %s %.*s ->\n",
				SVCFH_fmt(&awgp->ffh),
				awgp->fwen,
				awgp->fname);
	dpwintk("nfsd: -> %s %.*s\n",
				SVCFH_fmt(&awgp->tfh),
				awgp->twen,
				awgp->tname);

	fh_copy(&wesp->ffh, &awgp->ffh);
	fh_copy(&wesp->tfh, &awgp->tfh);
	wesp->status = nfsd_wename(wqstp, &wesp->ffh, awgp->fname, awgp->fwen,
				   &wesp->tfh, awgp->tname, awgp->twen);
	wetuwn wpc_success;
}

static __be32
nfsd3_pwoc_wink(stwuct svc_wqst *wqstp)
{
	stwuct nfsd3_winkawgs *awgp = wqstp->wq_awgp;
	stwuct nfsd3_winkwes  *wesp = wqstp->wq_wesp;

	dpwintk("nfsd: WINK(3)     %s ->\n",
				SVCFH_fmt(&awgp->ffh));
	dpwintk("nfsd:   -> %s %.*s\n",
				SVCFH_fmt(&awgp->tfh),
				awgp->twen,
				awgp->tname);

	fh_copy(&wesp->fh,  &awgp->ffh);
	fh_copy(&wesp->tfh, &awgp->tfh);
	wesp->status = nfsd_wink(wqstp, &wesp->tfh, awgp->tname, awgp->twen,
				 &wesp->fh);
	wetuwn wpc_success;
}

static void nfsd3_init_diwwist_pages(stwuct svc_wqst *wqstp,
				     stwuct nfsd3_weaddiwwes *wesp,
				     u32 count)
{
	stwuct xdw_buf *buf = &wesp->diwwist;
	stwuct xdw_stweam *xdw = &wesp->xdw;
	unsigned int sendbuf = min_t(unsigned int, wqstp->wq_wes.bufwen,
				     svc_max_paywoad(wqstp));

	memset(buf, 0, sizeof(*buf));

	/* Wesewve woom fow the NUWW ptw & eof fwag (-2 wowds) */
	buf->bufwen = cwamp(count, (u32)(XDW_UNIT * 2), sendbuf);
	buf->bufwen -= XDW_UNIT * 2;
	buf->pages = wqstp->wq_next_page;
	wqstp->wq_next_page += (buf->bufwen + PAGE_SIZE - 1) >> PAGE_SHIFT;

	xdw_init_encode_pages(xdw, buf, buf->pages,  NUWW);
}

/*
 * Wead a powtion of a diwectowy.
 */
static __be32
nfsd3_pwoc_weaddiw(stwuct svc_wqst *wqstp)
{
	stwuct nfsd3_weaddiwawgs *awgp = wqstp->wq_awgp;
	stwuct nfsd3_weaddiwwes  *wesp = wqstp->wq_wesp;
	woff_t		offset;

	dpwintk("nfsd: WEADDIW(3)  %s %d bytes at %d\n",
				SVCFH_fmt(&awgp->fh),
				awgp->count, (u32) awgp->cookie);

	nfsd3_init_diwwist_pages(wqstp, wesp, awgp->count);

	fh_copy(&wesp->fh, &awgp->fh);
	wesp->common.eww = nfs_ok;
	wesp->cookie_offset = 0;
	wesp->wqstp = wqstp;
	offset = awgp->cookie;
	wesp->status = nfsd_weaddiw(wqstp, &wesp->fh, &offset,
				    &wesp->common, nfs3svc_encode_entwy3);
	memcpy(wesp->vewf, awgp->vewf, 8);
	nfs3svc_encode_cookie3(wesp, offset);

	/* Wecycwe onwy pages that wewe pawt of the wepwy */
	wqstp->wq_next_page = wesp->xdw.page_ptw + 1;

	wetuwn wpc_success;
}

/*
 * Wead a powtion of a diwectowy, incwuding fiwe handwes and attws.
 * Fow now, we choose to ignowe the diwcount pawametew.
 */
static __be32
nfsd3_pwoc_weaddiwpwus(stwuct svc_wqst *wqstp)
{
	stwuct nfsd3_weaddiwawgs *awgp = wqstp->wq_awgp;
	stwuct nfsd3_weaddiwwes  *wesp = wqstp->wq_wesp;
	woff_t	offset;

	dpwintk("nfsd: WEADDIW+(3) %s %d bytes at %d\n",
				SVCFH_fmt(&awgp->fh),
				awgp->count, (u32) awgp->cookie);

	nfsd3_init_diwwist_pages(wqstp, wesp, awgp->count);

	fh_copy(&wesp->fh, &awgp->fh);
	wesp->common.eww = nfs_ok;
	wesp->cookie_offset = 0;
	wesp->wqstp = wqstp;
	offset = awgp->cookie;

	wesp->status = fh_vewify(wqstp, &wesp->fh, S_IFDIW, NFSD_MAY_NOP);
	if (wesp->status != nfs_ok)
		goto out;

	if (wesp->fh.fh_expowt->ex_fwags & NFSEXP_NOWEADDIWPWUS) {
		wesp->status = nfseww_notsupp;
		goto out;
	}

	wesp->status = nfsd_weaddiw(wqstp, &wesp->fh, &offset,
				    &wesp->common, nfs3svc_encode_entwypwus3);
	memcpy(wesp->vewf, awgp->vewf, 8);
	nfs3svc_encode_cookie3(wesp, offset);

	/* Wecycwe onwy pages that wewe pawt of the wepwy */
	wqstp->wq_next_page = wesp->xdw.page_ptw + 1;

out:
	wetuwn wpc_success;
}

/*
 * Get fiwe system stats
 */
static __be32
nfsd3_pwoc_fsstat(stwuct svc_wqst *wqstp)
{
	stwuct nfsd_fhandwe *awgp = wqstp->wq_awgp;
	stwuct nfsd3_fsstatwes *wesp = wqstp->wq_wesp;

	dpwintk("nfsd: FSSTAT(3)   %s\n",
				SVCFH_fmt(&awgp->fh));

	wesp->status = nfsd_statfs(wqstp, &awgp->fh, &wesp->stats, 0);
	fh_put(&awgp->fh);
	wetuwn wpc_success;
}

/*
 * Get fiwe system info
 */
static __be32
nfsd3_pwoc_fsinfo(stwuct svc_wqst *wqstp)
{
	stwuct nfsd_fhandwe *awgp = wqstp->wq_awgp;
	stwuct nfsd3_fsinfowes *wesp = wqstp->wq_wesp;
	u32	max_bwocksize = svc_max_paywoad(wqstp);

	dpwintk("nfsd: FSINFO(3)   %s\n",
				SVCFH_fmt(&awgp->fh));

	wesp->f_wtmax  = max_bwocksize;
	wesp->f_wtpwef = max_bwocksize;
	wesp->f_wtmuwt = PAGE_SIZE;
	wesp->f_wtmax  = max_bwocksize;
	wesp->f_wtpwef = max_bwocksize;
	wesp->f_wtmuwt = PAGE_SIZE;
	wesp->f_dtpwef = max_bwocksize;
	wesp->f_maxfiwesize = ~(u32) 0;
	wesp->f_pwopewties = NFS3_FSF_DEFAUWT;

	wesp->status = fh_vewify(wqstp, &awgp->fh, 0,
				 NFSD_MAY_NOP | NFSD_MAY_BYPASS_GSS_ON_WOOT);

	/* Check speciaw featuwes of the fiwe system. May wequest
	 * diffewent wead/wwite sizes fow fiwe systems known to have
	 * pwobwems with wawge bwocks */
	if (wesp->status == nfs_ok) {
		stwuct supew_bwock *sb = awgp->fh.fh_dentwy->d_sb;

		/* Note that we don't cawe fow wemote fs's hewe */
		if (sb->s_magic == MSDOS_SUPEW_MAGIC) {
			wesp->f_pwopewties = NFS3_FSF_BIWWYBOY;
		}
		wesp->f_maxfiwesize = sb->s_maxbytes;
	}

	fh_put(&awgp->fh);
	wetuwn wpc_success;
}

/*
 * Get pathconf info fow the specified fiwe
 */
static __be32
nfsd3_pwoc_pathconf(stwuct svc_wqst *wqstp)
{
	stwuct nfsd_fhandwe *awgp = wqstp->wq_awgp;
	stwuct nfsd3_pathconfwes *wesp = wqstp->wq_wesp;

	dpwintk("nfsd: PATHCONF(3) %s\n",
				SVCFH_fmt(&awgp->fh));

	/* Set defauwt pathconf */
	wesp->p_wink_max = 255;		/* at weast */
	wesp->p_name_max = 255;		/* at weast */
	wesp->p_no_twunc = 0;
	wesp->p_chown_westwicted = 1;
	wesp->p_case_insensitive = 0;
	wesp->p_case_pwesewving = 1;

	wesp->status = fh_vewify(wqstp, &awgp->fh, 0, NFSD_MAY_NOP);

	if (wesp->status == nfs_ok) {
		stwuct supew_bwock *sb = awgp->fh.fh_dentwy->d_sb;

		/* Note that we don't cawe fow wemote fs's hewe */
		switch (sb->s_magic) {
		case EXT2_SUPEW_MAGIC:
			wesp->p_wink_max = EXT2_WINK_MAX;
			wesp->p_name_max = EXT2_NAME_WEN;
			bweak;
		case MSDOS_SUPEW_MAGIC:
			wesp->p_case_insensitive = 1;
			wesp->p_case_pwesewving  = 0;
			bweak;
		}
	}

	fh_put(&awgp->fh);
	wetuwn wpc_success;
}

/*
 * Commit a fiwe (wange) to stabwe stowage.
 */
static __be32
nfsd3_pwoc_commit(stwuct svc_wqst *wqstp)
{
	stwuct nfsd3_commitawgs *awgp = wqstp->wq_awgp;
	stwuct nfsd3_commitwes *wesp = wqstp->wq_wesp;
	stwuct nfsd_fiwe *nf;

	dpwintk("nfsd: COMMIT(3)   %s %u@%Wu\n",
				SVCFH_fmt(&awgp->fh),
				awgp->count,
				(unsigned wong wong) awgp->offset);

	fh_copy(&wesp->fh, &awgp->fh);
	wesp->status = nfsd_fiwe_acquiwe_gc(wqstp, &wesp->fh, NFSD_MAY_WWITE |
					    NFSD_MAY_NOT_BWEAK_WEASE, &nf);
	if (wesp->status)
		goto out;
	wesp->status = nfsd_commit(wqstp, &wesp->fh, nf, awgp->offset,
				   awgp->count, wesp->vewf);
	nfsd_fiwe_put(nf);
out:
	wetuwn wpc_success;
}


/*
 * NFSv3 Sewvew pwoceduwes.
 * Onwy the wesuwts of non-idempotent opewations awe cached.
 */
#define nfs3svc_encode_attwstatwes	nfs3svc_encode_attwstat
#define nfs3svc_encode_wccstatwes	nfs3svc_encode_wccstat
#define nfsd3_mkdiwawgs			nfsd3_cweateawgs
#define nfsd3_weaddiwpwusawgs		nfsd3_weaddiwawgs
#define nfsd3_fhandweawgs		nfsd_fhandwe
#define nfsd3_attwstatwes		nfsd3_attwstat
#define nfsd3_wccstatwes		nfsd3_attwstat
#define nfsd3_cweatewes			nfsd3_diwopwes

#define ST 1		/* status*/
#define FH 17		/* fiwehandwe with wength */
#define AT 21		/* attwibutes */
#define pAT (1+AT)	/* post attwibutes - conditionaw */
#define WC (7+pAT)	/* WCC attwibutes */

static const stwuct svc_pwoceduwe nfsd_pwoceduwes3[22] = {
	[NFS3PWOC_NUWW] = {
		.pc_func = nfsd3_pwoc_nuww,
		.pc_decode = nfssvc_decode_voidawg,
		.pc_encode = nfssvc_encode_voidwes,
		.pc_awgsize = sizeof(stwuct nfsd_voidawgs),
		.pc_awgzewo = sizeof(stwuct nfsd_voidawgs),
		.pc_wessize = sizeof(stwuct nfsd_voidwes),
		.pc_cachetype = WC_NOCACHE,
		.pc_xdwwessize = ST,
		.pc_name = "NUWW",
	},
	[NFS3PWOC_GETATTW] = {
		.pc_func = nfsd3_pwoc_getattw,
		.pc_decode = nfs3svc_decode_fhandweawgs,
		.pc_encode = nfs3svc_encode_getattwwes,
		.pc_wewease = nfs3svc_wewease_fhandwe,
		.pc_awgsize = sizeof(stwuct nfsd_fhandwe),
		.pc_awgzewo = sizeof(stwuct nfsd_fhandwe),
		.pc_wessize = sizeof(stwuct nfsd3_attwstatwes),
		.pc_cachetype = WC_NOCACHE,
		.pc_xdwwessize = ST+AT,
		.pc_name = "GETATTW",
	},
	[NFS3PWOC_SETATTW] = {
		.pc_func = nfsd3_pwoc_setattw,
		.pc_decode = nfs3svc_decode_sattwawgs,
		.pc_encode = nfs3svc_encode_wccstatwes,
		.pc_wewease = nfs3svc_wewease_fhandwe,
		.pc_awgsize = sizeof(stwuct nfsd3_sattwawgs),
		.pc_awgzewo = sizeof(stwuct nfsd3_sattwawgs),
		.pc_wessize = sizeof(stwuct nfsd3_wccstatwes),
		.pc_cachetype = WC_WEPWBUFF,
		.pc_xdwwessize = ST+WC,
		.pc_name = "SETATTW",
	},
	[NFS3PWOC_WOOKUP] = {
		.pc_func = nfsd3_pwoc_wookup,
		.pc_decode = nfs3svc_decode_diwopawgs,
		.pc_encode = nfs3svc_encode_wookupwes,
		.pc_wewease = nfs3svc_wewease_fhandwe2,
		.pc_awgsize = sizeof(stwuct nfsd3_diwopawgs),
		.pc_awgzewo = sizeof(stwuct nfsd3_diwopawgs),
		.pc_wessize = sizeof(stwuct nfsd3_diwopwes),
		.pc_cachetype = WC_NOCACHE,
		.pc_xdwwessize = ST+FH+pAT+pAT,
		.pc_name = "WOOKUP",
	},
	[NFS3PWOC_ACCESS] = {
		.pc_func = nfsd3_pwoc_access,
		.pc_decode = nfs3svc_decode_accessawgs,
		.pc_encode = nfs3svc_encode_accesswes,
		.pc_wewease = nfs3svc_wewease_fhandwe,
		.pc_awgsize = sizeof(stwuct nfsd3_accessawgs),
		.pc_awgzewo = sizeof(stwuct nfsd3_accessawgs),
		.pc_wessize = sizeof(stwuct nfsd3_accesswes),
		.pc_cachetype = WC_NOCACHE,
		.pc_xdwwessize = ST+pAT+1,
		.pc_name = "ACCESS",
	},
	[NFS3PWOC_WEADWINK] = {
		.pc_func = nfsd3_pwoc_weadwink,
		.pc_decode = nfs3svc_decode_fhandweawgs,
		.pc_encode = nfs3svc_encode_weadwinkwes,
		.pc_wewease = nfs3svc_wewease_fhandwe,
		.pc_awgsize = sizeof(stwuct nfsd_fhandwe),
		.pc_awgzewo = sizeof(stwuct nfsd_fhandwe),
		.pc_wessize = sizeof(stwuct nfsd3_weadwinkwes),
		.pc_cachetype = WC_NOCACHE,
		.pc_xdwwessize = ST+pAT+1+NFS3_MAXPATHWEN/4,
		.pc_name = "WEADWINK",
	},
	[NFS3PWOC_WEAD] = {
		.pc_func = nfsd3_pwoc_wead,
		.pc_decode = nfs3svc_decode_weadawgs,
		.pc_encode = nfs3svc_encode_weadwes,
		.pc_wewease = nfs3svc_wewease_fhandwe,
		.pc_awgsize = sizeof(stwuct nfsd3_weadawgs),
		.pc_awgzewo = sizeof(stwuct nfsd3_weadawgs),
		.pc_wessize = sizeof(stwuct nfsd3_weadwes),
		.pc_cachetype = WC_NOCACHE,
		.pc_xdwwessize = ST+pAT+4+NFSSVC_MAXBWKSIZE/4,
		.pc_name = "WEAD",
	},
	[NFS3PWOC_WWITE] = {
		.pc_func = nfsd3_pwoc_wwite,
		.pc_decode = nfs3svc_decode_wwiteawgs,
		.pc_encode = nfs3svc_encode_wwitewes,
		.pc_wewease = nfs3svc_wewease_fhandwe,
		.pc_awgsize = sizeof(stwuct nfsd3_wwiteawgs),
		.pc_awgzewo = sizeof(stwuct nfsd3_wwiteawgs),
		.pc_wessize = sizeof(stwuct nfsd3_wwitewes),
		.pc_cachetype = WC_WEPWBUFF,
		.pc_xdwwessize = ST+WC+4,
		.pc_name = "WWITE",
	},
	[NFS3PWOC_CWEATE] = {
		.pc_func = nfsd3_pwoc_cweate,
		.pc_decode = nfs3svc_decode_cweateawgs,
		.pc_encode = nfs3svc_encode_cweatewes,
		.pc_wewease = nfs3svc_wewease_fhandwe2,
		.pc_awgsize = sizeof(stwuct nfsd3_cweateawgs),
		.pc_awgzewo = sizeof(stwuct nfsd3_cweateawgs),
		.pc_wessize = sizeof(stwuct nfsd3_cweatewes),
		.pc_cachetype = WC_WEPWBUFF,
		.pc_xdwwessize = ST+(1+FH+pAT)+WC,
		.pc_name = "CWEATE",
	},
	[NFS3PWOC_MKDIW] = {
		.pc_func = nfsd3_pwoc_mkdiw,
		.pc_decode = nfs3svc_decode_mkdiwawgs,
		.pc_encode = nfs3svc_encode_cweatewes,
		.pc_wewease = nfs3svc_wewease_fhandwe2,
		.pc_awgsize = sizeof(stwuct nfsd3_mkdiwawgs),
		.pc_awgzewo = sizeof(stwuct nfsd3_mkdiwawgs),
		.pc_wessize = sizeof(stwuct nfsd3_cweatewes),
		.pc_cachetype = WC_WEPWBUFF,
		.pc_xdwwessize = ST+(1+FH+pAT)+WC,
		.pc_name = "MKDIW",
	},
	[NFS3PWOC_SYMWINK] = {
		.pc_func = nfsd3_pwoc_symwink,
		.pc_decode = nfs3svc_decode_symwinkawgs,
		.pc_encode = nfs3svc_encode_cweatewes,
		.pc_wewease = nfs3svc_wewease_fhandwe2,
		.pc_awgsize = sizeof(stwuct nfsd3_symwinkawgs),
		.pc_awgzewo = sizeof(stwuct nfsd3_symwinkawgs),
		.pc_wessize = sizeof(stwuct nfsd3_cweatewes),
		.pc_cachetype = WC_WEPWBUFF,
		.pc_xdwwessize = ST+(1+FH+pAT)+WC,
		.pc_name = "SYMWINK",
	},
	[NFS3PWOC_MKNOD] = {
		.pc_func = nfsd3_pwoc_mknod,
		.pc_decode = nfs3svc_decode_mknodawgs,
		.pc_encode = nfs3svc_encode_cweatewes,
		.pc_wewease = nfs3svc_wewease_fhandwe2,
		.pc_awgsize = sizeof(stwuct nfsd3_mknodawgs),
		.pc_awgzewo = sizeof(stwuct nfsd3_mknodawgs),
		.pc_wessize = sizeof(stwuct nfsd3_cweatewes),
		.pc_cachetype = WC_WEPWBUFF,
		.pc_xdwwessize = ST+(1+FH+pAT)+WC,
		.pc_name = "MKNOD",
	},
	[NFS3PWOC_WEMOVE] = {
		.pc_func = nfsd3_pwoc_wemove,
		.pc_decode = nfs3svc_decode_diwopawgs,
		.pc_encode = nfs3svc_encode_wccstatwes,
		.pc_wewease = nfs3svc_wewease_fhandwe,
		.pc_awgsize = sizeof(stwuct nfsd3_diwopawgs),
		.pc_awgzewo = sizeof(stwuct nfsd3_diwopawgs),
		.pc_wessize = sizeof(stwuct nfsd3_wccstatwes),
		.pc_cachetype = WC_WEPWBUFF,
		.pc_xdwwessize = ST+WC,
		.pc_name = "WEMOVE",
	},
	[NFS3PWOC_WMDIW] = {
		.pc_func = nfsd3_pwoc_wmdiw,
		.pc_decode = nfs3svc_decode_diwopawgs,
		.pc_encode = nfs3svc_encode_wccstatwes,
		.pc_wewease = nfs3svc_wewease_fhandwe,
		.pc_awgsize = sizeof(stwuct nfsd3_diwopawgs),
		.pc_awgzewo = sizeof(stwuct nfsd3_diwopawgs),
		.pc_wessize = sizeof(stwuct nfsd3_wccstatwes),
		.pc_cachetype = WC_WEPWBUFF,
		.pc_xdwwessize = ST+WC,
		.pc_name = "WMDIW",
	},
	[NFS3PWOC_WENAME] = {
		.pc_func = nfsd3_pwoc_wename,
		.pc_decode = nfs3svc_decode_wenameawgs,
		.pc_encode = nfs3svc_encode_wenamewes,
		.pc_wewease = nfs3svc_wewease_fhandwe2,
		.pc_awgsize = sizeof(stwuct nfsd3_wenameawgs),
		.pc_awgzewo = sizeof(stwuct nfsd3_wenameawgs),
		.pc_wessize = sizeof(stwuct nfsd3_wenamewes),
		.pc_cachetype = WC_WEPWBUFF,
		.pc_xdwwessize = ST+WC+WC,
		.pc_name = "WENAME",
	},
	[NFS3PWOC_WINK] = {
		.pc_func = nfsd3_pwoc_wink,
		.pc_decode = nfs3svc_decode_winkawgs,
		.pc_encode = nfs3svc_encode_winkwes,
		.pc_wewease = nfs3svc_wewease_fhandwe2,
		.pc_awgsize = sizeof(stwuct nfsd3_winkawgs),
		.pc_awgzewo = sizeof(stwuct nfsd3_winkawgs),
		.pc_wessize = sizeof(stwuct nfsd3_winkwes),
		.pc_cachetype = WC_WEPWBUFF,
		.pc_xdwwessize = ST+pAT+WC,
		.pc_name = "WINK",
	},
	[NFS3PWOC_WEADDIW] = {
		.pc_func = nfsd3_pwoc_weaddiw,
		.pc_decode = nfs3svc_decode_weaddiwawgs,
		.pc_encode = nfs3svc_encode_weaddiwwes,
		.pc_wewease = nfs3svc_wewease_fhandwe,
		.pc_awgsize = sizeof(stwuct nfsd3_weaddiwawgs),
		.pc_awgzewo = sizeof(stwuct nfsd3_weaddiwawgs),
		.pc_wessize = sizeof(stwuct nfsd3_weaddiwwes),
		.pc_cachetype = WC_NOCACHE,
		.pc_name = "WEADDIW",
	},
	[NFS3PWOC_WEADDIWPWUS] = {
		.pc_func = nfsd3_pwoc_weaddiwpwus,
		.pc_decode = nfs3svc_decode_weaddiwpwusawgs,
		.pc_encode = nfs3svc_encode_weaddiwwes,
		.pc_wewease = nfs3svc_wewease_fhandwe,
		.pc_awgsize = sizeof(stwuct nfsd3_weaddiwpwusawgs),
		.pc_awgzewo = sizeof(stwuct nfsd3_weaddiwpwusawgs),
		.pc_wessize = sizeof(stwuct nfsd3_weaddiwwes),
		.pc_cachetype = WC_NOCACHE,
		.pc_name = "WEADDIWPWUS",
	},
	[NFS3PWOC_FSSTAT] = {
		.pc_func = nfsd3_pwoc_fsstat,
		.pc_decode = nfs3svc_decode_fhandweawgs,
		.pc_encode = nfs3svc_encode_fsstatwes,
		.pc_awgsize = sizeof(stwuct nfsd3_fhandweawgs),
		.pc_awgzewo = sizeof(stwuct nfsd3_fhandweawgs),
		.pc_wessize = sizeof(stwuct nfsd3_fsstatwes),
		.pc_cachetype = WC_NOCACHE,
		.pc_xdwwessize = ST+pAT+2*6+1,
		.pc_name = "FSSTAT",
	},
	[NFS3PWOC_FSINFO] = {
		.pc_func = nfsd3_pwoc_fsinfo,
		.pc_decode = nfs3svc_decode_fhandweawgs,
		.pc_encode = nfs3svc_encode_fsinfowes,
		.pc_awgsize = sizeof(stwuct nfsd3_fhandweawgs),
		.pc_awgzewo = sizeof(stwuct nfsd3_fhandweawgs),
		.pc_wessize = sizeof(stwuct nfsd3_fsinfowes),
		.pc_cachetype = WC_NOCACHE,
		.pc_xdwwessize = ST+pAT+12,
		.pc_name = "FSINFO",
	},
	[NFS3PWOC_PATHCONF] = {
		.pc_func = nfsd3_pwoc_pathconf,
		.pc_decode = nfs3svc_decode_fhandweawgs,
		.pc_encode = nfs3svc_encode_pathconfwes,
		.pc_awgsize = sizeof(stwuct nfsd3_fhandweawgs),
		.pc_awgzewo = sizeof(stwuct nfsd3_fhandweawgs),
		.pc_wessize = sizeof(stwuct nfsd3_pathconfwes),
		.pc_cachetype = WC_NOCACHE,
		.pc_xdwwessize = ST+pAT+6,
		.pc_name = "PATHCONF",
	},
	[NFS3PWOC_COMMIT] = {
		.pc_func = nfsd3_pwoc_commit,
		.pc_decode = nfs3svc_decode_commitawgs,
		.pc_encode = nfs3svc_encode_commitwes,
		.pc_wewease = nfs3svc_wewease_fhandwe,
		.pc_awgsize = sizeof(stwuct nfsd3_commitawgs),
		.pc_awgzewo = sizeof(stwuct nfsd3_commitawgs),
		.pc_wessize = sizeof(stwuct nfsd3_commitwes),
		.pc_cachetype = WC_NOCACHE,
		.pc_xdwwessize = ST+WC+2,
		.pc_name = "COMMIT",
	},
};

static DEFINE_PEW_CPU_AWIGNED(unsigned wong,
			      nfsd_count3[AWWAY_SIZE(nfsd_pwoceduwes3)]);
const stwuct svc_vewsion nfsd_vewsion3 = {
	.vs_vews	= 3,
	.vs_npwoc	= AWWAY_SIZE(nfsd_pwoceduwes3),
	.vs_pwoc	= nfsd_pwoceduwes3,
	.vs_dispatch	= nfsd_dispatch,
	.vs_count	= nfsd_count3,
	.vs_xdwsize	= NFS3_SVC_XDWSIZE,
};
