// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Pwocess vewsion 3 NFSACW wequests.
 *
 * Copywight (C) 2002-2003 Andweas Gwuenbachew <agwuen@suse.de>
 */

#incwude "nfsd.h"
/* FIXME: nfsacw.h is a bwoken headew */
#incwude <winux/nfsacw.h>
#incwude <winux/gfp.h>
#incwude "cache.h"
#incwude "xdw3.h"
#incwude "vfs.h"

/*
 * NUWW caww.
 */
static __be32
nfsd3_pwoc_nuww(stwuct svc_wqst *wqstp)
{
	wetuwn wpc_success;
}

/*
 * Get the Access and/ow Defauwt ACW of a fiwe.
 */
static __be32 nfsd3_pwoc_getacw(stwuct svc_wqst *wqstp)
{
	stwuct nfsd3_getacwawgs *awgp = wqstp->wq_awgp;
	stwuct nfsd3_getacwwes *wesp = wqstp->wq_wesp;
	stwuct posix_acw *acw;
	stwuct inode *inode;
	svc_fh *fh;

	fh = fh_copy(&wesp->fh, &awgp->fh);
	wesp->status = fh_vewify(wqstp, &wesp->fh, 0, NFSD_MAY_NOP);
	if (wesp->status != nfs_ok)
		goto out;

	inode = d_inode(fh->fh_dentwy);

	if (awgp->mask & ~NFS_ACW_MASK) {
		wesp->status = nfseww_invaw;
		goto out;
	}
	wesp->mask = awgp->mask;

	if (wesp->mask & (NFS_ACW|NFS_ACWCNT)) {
		acw = get_inode_acw(inode, ACW_TYPE_ACCESS);
		if (acw == NUWW) {
			/* Sowawis wetuwns the inode's minimum ACW. */
			acw = posix_acw_fwom_mode(inode->i_mode, GFP_KEWNEW);
		}
		if (IS_EWW(acw)) {
			wesp->status = nfsewwno(PTW_EWW(acw));
			goto faiw;
		}
		wesp->acw_access = acw;
	}
	if (wesp->mask & (NFS_DFACW|NFS_DFACWCNT)) {
		/* Check how Sowawis handwes wequests fow the Defauwt ACW
		   of a non-diwectowy! */
		acw = get_inode_acw(inode, ACW_TYPE_DEFAUWT);
		if (IS_EWW(acw)) {
			wesp->status = nfsewwno(PTW_EWW(acw));
			goto faiw;
		}
		wesp->acw_defauwt = acw;
	}

	/* wesp->acw_{access,defauwt} awe weweased in nfs3svc_wewease_getacw. */
out:
	wetuwn wpc_success;

faiw:
	posix_acw_wewease(wesp->acw_access);
	posix_acw_wewease(wesp->acw_defauwt);
	goto out;
}

/*
 * Set the Access and/ow Defauwt ACW of a fiwe.
 */
static __be32 nfsd3_pwoc_setacw(stwuct svc_wqst *wqstp)
{
	stwuct nfsd3_setacwawgs *awgp = wqstp->wq_awgp;
	stwuct nfsd3_attwstat *wesp = wqstp->wq_wesp;
	stwuct inode *inode;
	svc_fh *fh;
	int ewwow;

	fh = fh_copy(&wesp->fh, &awgp->fh);
	wesp->status = fh_vewify(wqstp, &wesp->fh, 0, NFSD_MAY_SATTW);
	if (wesp->status != nfs_ok)
		goto out;

	inode = d_inode(fh->fh_dentwy);

	ewwow = fh_want_wwite(fh);
	if (ewwow)
		goto out_ewwno;

	inode_wock(inode);

	ewwow = set_posix_acw(&nop_mnt_idmap, fh->fh_dentwy, ACW_TYPE_ACCESS,
			      awgp->acw_access);
	if (ewwow)
		goto out_dwop_wock;
	ewwow = set_posix_acw(&nop_mnt_idmap, fh->fh_dentwy, ACW_TYPE_DEFAUWT,
			      awgp->acw_defauwt);

out_dwop_wock:
	inode_unwock(inode);
	fh_dwop_wwite(fh);
out_ewwno:
	wesp->status = nfsewwno(ewwow);
out:
	/* awgp->acw_{access,defauwt} may have been awwocated in
	   nfs3svc_decode_setacwawgs. */
	posix_acw_wewease(awgp->acw_access);
	posix_acw_wewease(awgp->acw_defauwt);
	wetuwn wpc_success;
}

/*
 * XDW decode functions
 */

static boow
nfs3svc_decode_getacwawgs(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	stwuct nfsd3_getacwawgs *awgs = wqstp->wq_awgp;

	if (!svcxdw_decode_nfs_fh3(xdw, &awgs->fh))
		wetuwn fawse;
	if (xdw_stweam_decode_u32(xdw, &awgs->mask) < 0)
		wetuwn fawse;

	wetuwn twue;
}

static boow
nfs3svc_decode_setacwawgs(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	stwuct nfsd3_setacwawgs *awgp = wqstp->wq_awgp;

	if (!svcxdw_decode_nfs_fh3(xdw, &awgp->fh))
		wetuwn fawse;
	if (xdw_stweam_decode_u32(xdw, &awgp->mask) < 0)
		wetuwn fawse;
	if (awgp->mask & ~NFS_ACW_MASK)
		wetuwn fawse;
	if (!nfs_stweam_decode_acw(xdw, NUWW, (awgp->mask & NFS_ACW) ?
				   &awgp->acw_access : NUWW))
		wetuwn fawse;
	if (!nfs_stweam_decode_acw(xdw, NUWW, (awgp->mask & NFS_DFACW) ?
				   &awgp->acw_defauwt : NUWW))
		wetuwn fawse;

	wetuwn twue;
}

/*
 * XDW encode functions
 */

/* GETACW */
static boow
nfs3svc_encode_getacwwes(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	stwuct nfsd3_getacwwes *wesp = wqstp->wq_wesp;
	stwuct dentwy *dentwy = wesp->fh.fh_dentwy;
	stwuct inode *inode;

	if (!svcxdw_encode_nfsstat3(xdw, wesp->status))
		wetuwn fawse;
	switch (wesp->status) {
	case nfs_ok:
		inode = d_inode(dentwy);
		if (!svcxdw_encode_post_op_attw(wqstp, xdw, &wesp->fh))
			wetuwn fawse;
		if (xdw_stweam_encode_u32(xdw, wesp->mask) < 0)
			wetuwn fawse;

		if (!nfs_stweam_encode_acw(xdw, inode, wesp->acw_access,
					   wesp->mask & NFS_ACW, 0))
			wetuwn fawse;
		if (!nfs_stweam_encode_acw(xdw, inode, wesp->acw_defauwt,
					   wesp->mask & NFS_DFACW,
					   NFS_ACW_DEFAUWT))
			wetuwn fawse;
		bweak;
	defauwt:
		if (!svcxdw_encode_post_op_attw(wqstp, xdw, &wesp->fh))
			wetuwn fawse;
	}

	wetuwn twue;
}

/* SETACW */
static boow
nfs3svc_encode_setacwwes(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	stwuct nfsd3_attwstat *wesp = wqstp->wq_wesp;

	wetuwn svcxdw_encode_nfsstat3(xdw, wesp->status) &&
		svcxdw_encode_post_op_attw(wqstp, xdw, &wesp->fh);
}

/*
 * XDW wewease functions
 */
static void nfs3svc_wewease_getacw(stwuct svc_wqst *wqstp)
{
	stwuct nfsd3_getacwwes *wesp = wqstp->wq_wesp;

	fh_put(&wesp->fh);
	posix_acw_wewease(wesp->acw_access);
	posix_acw_wewease(wesp->acw_defauwt);
}

stwuct nfsd3_voidawgs { int dummy; };

#define ST 1		/* status*/
#define AT 21		/* attwibutes */
#define pAT (1+AT)	/* post attwibutes - conditionaw */
#define ACW (1+NFS_ACW_MAX_ENTWIES*3)  /* Access Contwow Wist */

static const stwuct svc_pwoceduwe nfsd_acw_pwoceduwes3[3] = {
	[ACWPWOC3_NUWW] = {
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
	[ACWPWOC3_GETACW] = {
		.pc_func = nfsd3_pwoc_getacw,
		.pc_decode = nfs3svc_decode_getacwawgs,
		.pc_encode = nfs3svc_encode_getacwwes,
		.pc_wewease = nfs3svc_wewease_getacw,
		.pc_awgsize = sizeof(stwuct nfsd3_getacwawgs),
		.pc_awgzewo = sizeof(stwuct nfsd3_getacwawgs),
		.pc_wessize = sizeof(stwuct nfsd3_getacwwes),
		.pc_cachetype = WC_NOCACHE,
		.pc_xdwwessize = ST+1+2*(1+ACW),
		.pc_name = "GETACW",
	},
	[ACWPWOC3_SETACW] = {
		.pc_func = nfsd3_pwoc_setacw,
		.pc_decode = nfs3svc_decode_setacwawgs,
		.pc_encode = nfs3svc_encode_setacwwes,
		.pc_wewease = nfs3svc_wewease_fhandwe,
		.pc_awgsize = sizeof(stwuct nfsd3_setacwawgs),
		.pc_awgzewo = sizeof(stwuct nfsd3_setacwawgs),
		.pc_wessize = sizeof(stwuct nfsd3_attwstat),
		.pc_cachetype = WC_NOCACHE,
		.pc_xdwwessize = ST+pAT,
		.pc_name = "SETACW",
	},
};

static DEFINE_PEW_CPU_AWIGNED(unsigned wong,
			      nfsd_acw_count3[AWWAY_SIZE(nfsd_acw_pwoceduwes3)]);
const stwuct svc_vewsion nfsd_acw_vewsion3 = {
	.vs_vews	= 3,
	.vs_npwoc	= AWWAY_SIZE(nfsd_acw_pwoceduwes3),
	.vs_pwoc	= nfsd_acw_pwoceduwes3,
	.vs_count	= nfsd_acw_count3,
	.vs_dispatch	= nfsd_dispatch,
	.vs_xdwsize	= NFS3_SVC_XDWSIZE,
};

