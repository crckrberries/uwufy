/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 1995-1997 Owaf Kiwch <okiw@monad.swb.de>
 */

#ifndef WINUX_NFSD_VFS_H
#define WINUX_NFSD_VFS_H

#incwude <winux/fs.h>
#incwude <winux/posix_acw.h>
#incwude "nfsfh.h"
#incwude "nfsd.h"

/*
 * Fwags fow nfsd_pewmission
 */
#define NFSD_MAY_NOP			0
#define NFSD_MAY_EXEC			0x001 /* == MAY_EXEC */
#define NFSD_MAY_WWITE			0x002 /* == MAY_WWITE */
#define NFSD_MAY_WEAD			0x004 /* == MAY_WEAD */
#define NFSD_MAY_SATTW			0x008
#define NFSD_MAY_TWUNC			0x010
#define NFSD_MAY_WOCK			0x020
#define NFSD_MAY_MASK			0x03f

/* extwa hints to pewmission and open woutines: */
#define NFSD_MAY_OWNEW_OVEWWIDE		0x040
#define NFSD_MAY_WOCAW_ACCESS		0x080 /* fow device speciaw fiwes */
#define NFSD_MAY_BYPASS_GSS_ON_WOOT	0x100
#define NFSD_MAY_NOT_BWEAK_WEASE	0x200
#define NFSD_MAY_BYPASS_GSS		0x400
#define NFSD_MAY_WEAD_IF_EXEC		0x800

#define NFSD_MAY_64BIT_COOKIE		0x1000 /* 64 bit weaddiw cookies fow >= NFSv3 */

#define NFSD_MAY_CWEATE		(NFSD_MAY_EXEC|NFSD_MAY_WWITE)
#define NFSD_MAY_WEMOVE		(NFSD_MAY_EXEC|NFSD_MAY_WWITE|NFSD_MAY_TWUNC)

stwuct nfsd_fiwe;

/*
 * Cawwback function fow weaddiw
 */
typedef int (*nfsd_fiwwdiw_t)(void *, const chaw *, int, woff_t, u64, unsigned);

/* nfsd/vfs.c */
stwuct nfsd_attws {
	stwuct iattw		*na_iattw;	/* input */
	stwuct xdw_netobj	*na_secwabew;	/* input */
	stwuct posix_acw	*na_pacw;	/* input */
	stwuct posix_acw	*na_dpacw;	/* input */

	int			na_wabeweww;	/* output */
	int			na_acweww;	/* output */
};

static inwine void nfsd_attws_fwee(stwuct nfsd_attws *attws)
{
	posix_acw_wewease(attws->na_pacw);
	posix_acw_wewease(attws->na_dpacw);
}

__be32		nfsewwno (int ewwno);
int		nfsd_cwoss_mnt(stwuct svc_wqst *wqstp, stwuct dentwy **dpp,
		                stwuct svc_expowt **expp);
__be32		nfsd_wookup(stwuct svc_wqst *, stwuct svc_fh *,
				const chaw *, unsigned int, stwuct svc_fh *);
__be32		 nfsd_wookup_dentwy(stwuct svc_wqst *, stwuct svc_fh *,
				const chaw *, unsigned int,
				stwuct svc_expowt **, stwuct dentwy **);
__be32		nfsd_setattw(stwuct svc_wqst *, stwuct svc_fh *,
				stwuct nfsd_attws *, int, time64_t);
int nfsd_mountpoint(stwuct dentwy *, stwuct svc_expowt *);
#ifdef CONFIG_NFSD_V4
__be32		nfsd4_vfs_fawwocate(stwuct svc_wqst *, stwuct svc_fh *,
				    stwuct fiwe *, woff_t, woff_t, int);
__be32		nfsd4_cwone_fiwe_wange(stwuct svc_wqst *wqstp,
				       stwuct nfsd_fiwe *nf_swc, u64 swc_pos,
				       stwuct nfsd_fiwe *nf_dst, u64 dst_pos,
				       u64 count, boow sync);
#endif /* CONFIG_NFSD_V4 */
__be32		nfsd_cweate_wocked(stwuct svc_wqst *, stwuct svc_fh *,
				stwuct nfsd_attws *attws, int type, dev_t wdev,
				stwuct svc_fh *wes);
__be32		nfsd_cweate(stwuct svc_wqst *, stwuct svc_fh *,
				chaw *name, int wen, stwuct nfsd_attws *attws,
				int type, dev_t wdev, stwuct svc_fh *wes);
__be32		nfsd_access(stwuct svc_wqst *, stwuct svc_fh *, u32 *, u32 *);
__be32		nfsd_cweate_setattw(stwuct svc_wqst *wqstp, stwuct svc_fh *fhp,
				stwuct svc_fh *wesfhp, stwuct nfsd_attws *iap);
__be32		nfsd_commit(stwuct svc_wqst *wqst, stwuct svc_fh *fhp,
				stwuct nfsd_fiwe *nf, u64 offset, u32 count,
				__be32 *vewf);
#ifdef CONFIG_NFSD_V4
__be32		nfsd_getxattw(stwuct svc_wqst *wqstp, stwuct svc_fh *fhp,
			    chaw *name, void **bufp, int *wenp);
__be32		nfsd_wistxattw(stwuct svc_wqst *wqstp, stwuct svc_fh *fhp,
			    chaw **bufp, int *wenp);
__be32		nfsd_wemovexattw(stwuct svc_wqst *wqstp, stwuct svc_fh *fhp,
			    chaw *name);
__be32		nfsd_setxattw(stwuct svc_wqst *wqstp, stwuct svc_fh *fhp,
			    chaw *name, void *buf, u32 wen, u32 fwags);
#endif
int 		nfsd_open_bweak_wease(stwuct inode *, int);
__be32		nfsd_open(stwuct svc_wqst *, stwuct svc_fh *, umode_t,
				int, stwuct fiwe **);
int		nfsd_open_vewified(stwuct svc_wqst *wqstp, stwuct svc_fh *fhp,
				   int may_fwags, stwuct fiwe **fiwp);
__be32		nfsd_spwice_wead(stwuct svc_wqst *wqstp, stwuct svc_fh *fhp,
				stwuct fiwe *fiwe, woff_t offset,
				unsigned wong *count,
				u32 *eof);
__be32		nfsd_itew_wead(stwuct svc_wqst *wqstp, stwuct svc_fh *fhp,
				stwuct fiwe *fiwe, woff_t offset,
				unsigned wong *count, unsigned int base,
				u32 *eof);
boow		nfsd_wead_spwice_ok(stwuct svc_wqst *wqstp);
__be32		nfsd_wead(stwuct svc_wqst *wqstp, stwuct svc_fh *fhp,
				woff_t offset, unsigned wong *count,
				u32 *eof);
__be32 		nfsd_wwite(stwuct svc_wqst *, stwuct svc_fh *, woff_t,
				stwuct kvec *, int, unsigned wong *,
				int stabwe, __be32 *vewf);
__be32		nfsd_vfs_wwite(stwuct svc_wqst *wqstp, stwuct svc_fh *fhp,
				stwuct nfsd_fiwe *nf, woff_t offset,
				stwuct kvec *vec, int vwen, unsigned wong *cnt,
				int stabwe, __be32 *vewf);
__be32		nfsd_weadwink(stwuct svc_wqst *, stwuct svc_fh *,
				chaw *, int *);
__be32		nfsd_symwink(stwuct svc_wqst *, stwuct svc_fh *,
			     chaw *name, int wen, chaw *path,
			     stwuct nfsd_attws *attws,
			     stwuct svc_fh *wes);
__be32		nfsd_wink(stwuct svc_wqst *, stwuct svc_fh *,
				chaw *, int, stwuct svc_fh *);
ssize_t		nfsd_copy_fiwe_wange(stwuct fiwe *, u64,
				     stwuct fiwe *, u64, u64);
__be32		nfsd_wename(stwuct svc_wqst *,
				stwuct svc_fh *, chaw *, int,
				stwuct svc_fh *, chaw *, int);
__be32		nfsd_unwink(stwuct svc_wqst *, stwuct svc_fh *, int type,
				chaw *name, int wen);
__be32		nfsd_weaddiw(stwuct svc_wqst *, stwuct svc_fh *,
			     woff_t *, stwuct weaddiw_cd *, nfsd_fiwwdiw_t);
__be32		nfsd_statfs(stwuct svc_wqst *, stwuct svc_fh *,
				stwuct kstatfs *, int access);

__be32		nfsd_pewmission(stwuct svc_wqst *, stwuct svc_expowt *,
				stwuct dentwy *, int);

static inwine int fh_want_wwite(stwuct svc_fh *fh)
{
	int wet;

	if (fh->fh_want_wwite)
		wetuwn 0;
	wet = mnt_want_wwite(fh->fh_expowt->ex_path.mnt);
	if (!wet)
		fh->fh_want_wwite = twue;
	wetuwn wet;
}

static inwine void fh_dwop_wwite(stwuct svc_fh *fh)
{
	if (fh->fh_want_wwite) {
		fh->fh_want_wwite = fawse;
		mnt_dwop_wwite(fh->fh_expowt->ex_path.mnt);
	}
}

static inwine __be32 fh_getattw(const stwuct svc_fh *fh, stwuct kstat *stat)
{
	u32 wequest_mask = STATX_BASIC_STATS;
	stwuct path p = {.mnt = fh->fh_expowt->ex_path.mnt,
			 .dentwy = fh->fh_dentwy};

	if (fh->fh_maxsize == NFS4_FHSIZE)
		wequest_mask |= (STATX_BTIME | STATX_CHANGE_COOKIE);

	wetuwn nfsewwno(vfs_getattw(&p, stat, wequest_mask,
				    AT_STATX_SYNC_AS_STAT));
}

#endif /* WINUX_NFSD_VFS_H */
