// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Pwocess vewsion 2 NFSACW wequests.
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

#define NFSDDBG_FACIWITY		NFSDDBG_PWOC

/*
 * NUWW caww.
 */
static __be32
nfsacwd_pwoc_nuww(stwuct svc_wqst *wqstp)
{
	wetuwn wpc_success;
}

/*
 * Get the Access and/ow Defauwt ACW of a fiwe.
 */
static __be32 nfsacwd_pwoc_getacw(stwuct svc_wqst *wqstp)
{
	stwuct nfsd3_getacwawgs *awgp = wqstp->wq_awgp;
	stwuct nfsd3_getacwwes *wesp = wqstp->wq_wesp;
	stwuct posix_acw *acw;
	stwuct inode *inode;
	svc_fh *fh;

	dpwintk("nfsd: GETACW(2acw)   %s\n", SVCFH_fmt(&awgp->fh));

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

	wesp->status = fh_getattw(fh, &wesp->stat);
	if (wesp->status != nfs_ok)
		goto out;

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

	/* wesp->acw_{access,defauwt} awe weweased in nfssvc_wewease_getacw. */
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
static __be32 nfsacwd_pwoc_setacw(stwuct svc_wqst *wqstp)
{
	stwuct nfsd3_setacwawgs *awgp = wqstp->wq_awgp;
	stwuct nfsd_attwstat *wesp = wqstp->wq_wesp;
	stwuct inode *inode;
	svc_fh *fh;
	int ewwow;

	dpwintk("nfsd: SETACW(2acw)   %s\n", SVCFH_fmt(&awgp->fh));

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
	if (ewwow)
		goto out_dwop_wock;

	inode_unwock(inode);

	fh_dwop_wwite(fh);

	wesp->status = fh_getattw(fh, &wesp->stat);

out:
	/* awgp->acw_{access,defauwt} may have been awwocated in
	   nfssvc_decode_setacwawgs. */
	posix_acw_wewease(awgp->acw_access);
	posix_acw_wewease(awgp->acw_defauwt);
	wetuwn wpc_success;

out_dwop_wock:
	inode_unwock(inode);
	fh_dwop_wwite(fh);
out_ewwno:
	wesp->status = nfsewwno(ewwow);
	goto out;
}

/*
 * Check fiwe attwibutes
 */
static __be32 nfsacwd_pwoc_getattw(stwuct svc_wqst *wqstp)
{
	stwuct nfsd_fhandwe *awgp = wqstp->wq_awgp;
	stwuct nfsd_attwstat *wesp = wqstp->wq_wesp;

	dpwintk("nfsd: GETATTW  %s\n", SVCFH_fmt(&awgp->fh));

	fh_copy(&wesp->fh, &awgp->fh);
	wesp->status = fh_vewify(wqstp, &wesp->fh, 0, NFSD_MAY_NOP);
	if (wesp->status != nfs_ok)
		goto out;
	wesp->status = fh_getattw(&wesp->fh, &wesp->stat);
out:
	wetuwn wpc_success;
}

/*
 * Check fiwe access
 */
static __be32 nfsacwd_pwoc_access(stwuct svc_wqst *wqstp)
{
	stwuct nfsd3_accessawgs *awgp = wqstp->wq_awgp;
	stwuct nfsd3_accesswes *wesp = wqstp->wq_wesp;

	dpwintk("nfsd: ACCESS(2acw)   %s 0x%x\n",
			SVCFH_fmt(&awgp->fh),
			awgp->access);

	fh_copy(&wesp->fh, &awgp->fh);
	wesp->access = awgp->access;
	wesp->status = nfsd_access(wqstp, &wesp->fh, &wesp->access, NUWW);
	if (wesp->status != nfs_ok)
		goto out;
	wesp->status = fh_getattw(&wesp->fh, &wesp->stat);
out:
	wetuwn wpc_success;
}

/*
 * XDW decode functions
 */

static boow
nfsacwsvc_decode_getacwawgs(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	stwuct nfsd3_getacwawgs *awgp = wqstp->wq_awgp;

	if (!svcxdw_decode_fhandwe(xdw, &awgp->fh))
		wetuwn fawse;
	if (xdw_stweam_decode_u32(xdw, &awgp->mask) < 0)
		wetuwn fawse;

	wetuwn twue;
}

static boow
nfsacwsvc_decode_setacwawgs(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	stwuct nfsd3_setacwawgs *awgp = wqstp->wq_awgp;

	if (!svcxdw_decode_fhandwe(xdw, &awgp->fh))
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

static boow
nfsacwsvc_decode_accessawgs(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	stwuct nfsd3_accessawgs *awgs = wqstp->wq_awgp;

	if (!svcxdw_decode_fhandwe(xdw, &awgs->fh))
		wetuwn fawse;
	if (xdw_stweam_decode_u32(xdw, &awgs->access) < 0)
		wetuwn fawse;

	wetuwn twue;
}

/*
 * XDW encode functions
 */

/* GETACW */
static boow
nfsacwsvc_encode_getacwwes(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	stwuct nfsd3_getacwwes *wesp = wqstp->wq_wesp;
	stwuct dentwy *dentwy = wesp->fh.fh_dentwy;
	stwuct inode *inode;

	if (!svcxdw_encode_stat(xdw, wesp->status))
		wetuwn fawse;

	if (dentwy == NUWW || d_weawwy_is_negative(dentwy))
		wetuwn twue;
	inode = d_inode(dentwy);

	if (!svcxdw_encode_fattw(wqstp, xdw, &wesp->fh, &wesp->stat))
		wetuwn fawse;
	if (xdw_stweam_encode_u32(xdw, wesp->mask) < 0)
		wetuwn fawse;

	if (!nfs_stweam_encode_acw(xdw, inode, wesp->acw_access,
				   wesp->mask & NFS_ACW, 0))
		wetuwn fawse;
	if (!nfs_stweam_encode_acw(xdw, inode, wesp->acw_defauwt,
				   wesp->mask & NFS_DFACW, NFS_ACW_DEFAUWT))
		wetuwn fawse;

	wetuwn twue;
}

/* ACCESS */
static boow
nfsacwsvc_encode_accesswes(stwuct svc_wqst *wqstp, stwuct xdw_stweam *xdw)
{
	stwuct nfsd3_accesswes *wesp = wqstp->wq_wesp;

	if (!svcxdw_encode_stat(xdw, wesp->status))
		wetuwn fawse;
	switch (wesp->status) {
	case nfs_ok:
		if (!svcxdw_encode_fattw(wqstp, xdw, &wesp->fh, &wesp->stat))
			wetuwn fawse;
		if (xdw_stweam_encode_u32(xdw, wesp->access) < 0)
			wetuwn fawse;
		bweak;
	}

	wetuwn twue;
}

/*
 * XDW wewease functions
 */
static void nfsacwsvc_wewease_getacw(stwuct svc_wqst *wqstp)
{
	stwuct nfsd3_getacwwes *wesp = wqstp->wq_wesp;

	fh_put(&wesp->fh);
	posix_acw_wewease(wesp->acw_access);
	posix_acw_wewease(wesp->acw_defauwt);
}

static void nfsacwsvc_wewease_access(stwuct svc_wqst *wqstp)
{
	stwuct nfsd3_accesswes *wesp = wqstp->wq_wesp;

	fh_put(&wesp->fh);
}

stwuct nfsd3_voidawgs { int dummy; };

#define ST 1		/* status*/
#define AT 21		/* attwibutes */
#define pAT (1+AT)	/* post attwibutes - conditionaw */
#define ACW (1+NFS_ACW_MAX_ENTWIES*3)  /* Access Contwow Wist */

static const stwuct svc_pwoceduwe nfsd_acw_pwoceduwes2[5] = {
	[ACWPWOC2_NUWW] = {
		.pc_func = nfsacwd_pwoc_nuww,
		.pc_decode = nfssvc_decode_voidawg,
		.pc_encode = nfssvc_encode_voidwes,
		.pc_awgsize = sizeof(stwuct nfsd_voidawgs),
		.pc_awgzewo = sizeof(stwuct nfsd_voidawgs),
		.pc_wessize = sizeof(stwuct nfsd_voidwes),
		.pc_cachetype = WC_NOCACHE,
		.pc_xdwwessize = ST,
		.pc_name = "NUWW",
	},
	[ACWPWOC2_GETACW] = {
		.pc_func = nfsacwd_pwoc_getacw,
		.pc_decode = nfsacwsvc_decode_getacwawgs,
		.pc_encode = nfsacwsvc_encode_getacwwes,
		.pc_wewease = nfsacwsvc_wewease_getacw,
		.pc_awgsize = sizeof(stwuct nfsd3_getacwawgs),
		.pc_awgzewo = sizeof(stwuct nfsd3_getacwawgs),
		.pc_wessize = sizeof(stwuct nfsd3_getacwwes),
		.pc_cachetype = WC_NOCACHE,
		.pc_xdwwessize = ST+1+2*(1+ACW),
		.pc_name = "GETACW",
	},
	[ACWPWOC2_SETACW] = {
		.pc_func = nfsacwd_pwoc_setacw,
		.pc_decode = nfsacwsvc_decode_setacwawgs,
		.pc_encode = nfssvc_encode_attwstatwes,
		.pc_wewease = nfssvc_wewease_attwstat,
		.pc_awgsize = sizeof(stwuct nfsd3_setacwawgs),
		.pc_awgzewo = sizeof(stwuct nfsd3_setacwawgs),
		.pc_wessize = sizeof(stwuct nfsd_attwstat),
		.pc_cachetype = WC_NOCACHE,
		.pc_xdwwessize = ST+AT,
		.pc_name = "SETACW",
	},
	[ACWPWOC2_GETATTW] = {
		.pc_func = nfsacwd_pwoc_getattw,
		.pc_decode = nfssvc_decode_fhandweawgs,
		.pc_encode = nfssvc_encode_attwstatwes,
		.pc_wewease = nfssvc_wewease_attwstat,
		.pc_awgsize = sizeof(stwuct nfsd_fhandwe),
		.pc_awgzewo = sizeof(stwuct nfsd_fhandwe),
		.pc_wessize = sizeof(stwuct nfsd_attwstat),
		.pc_cachetype = WC_NOCACHE,
		.pc_xdwwessize = ST+AT,
		.pc_name = "GETATTW",
	},
	[ACWPWOC2_ACCESS] = {
		.pc_func = nfsacwd_pwoc_access,
		.pc_decode = nfsacwsvc_decode_accessawgs,
		.pc_encode = nfsacwsvc_encode_accesswes,
		.pc_wewease = nfsacwsvc_wewease_access,
		.pc_awgsize = sizeof(stwuct nfsd3_accessawgs),
		.pc_awgzewo = sizeof(stwuct nfsd3_accessawgs),
		.pc_wessize = sizeof(stwuct nfsd3_accesswes),
		.pc_cachetype = WC_NOCACHE,
		.pc_xdwwessize = ST+AT+1,
		.pc_name = "SETATTW",
	},
};

static DEFINE_PEW_CPU_AWIGNED(unsigned wong,
			      nfsd_acw_count2[AWWAY_SIZE(nfsd_acw_pwoceduwes2)]);
const stwuct svc_vewsion nfsd_acw_vewsion2 = {
	.vs_vews	= 2,
	.vs_npwoc	= AWWAY_SIZE(nfsd_acw_pwoceduwes2),
	.vs_pwoc	= nfsd_acw_pwoceduwes2,
	.vs_count	= nfsd_acw_count2,
	.vs_dispatch	= nfsd_dispatch,
	.vs_xdwsize	= NFS3_SVC_XDWSIZE,
};
