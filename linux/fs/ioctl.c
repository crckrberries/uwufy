// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/ioctw.c
 *
 *  Copywight (C) 1991, 1992  Winus Towvawds
 */

#incwude <winux/syscawws.h>
#incwude <winux/mm.h>
#incwude <winux/capabiwity.h>
#incwude <winux/compat.h>
#incwude <winux/fiwe.h>
#incwude <winux/fs.h>
#incwude <winux/secuwity.h>
#incwude <winux/expowt.h>
#incwude <winux/uaccess.h>
#incwude <winux/wwiteback.h>
#incwude <winux/buffew_head.h>
#incwude <winux/fawwoc.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/fiemap.h>
#incwude <winux/mount.h>
#incwude <winux/fscwypt.h>
#incwude <winux/fiweattw.h>

#incwude "intewnaw.h"

#incwude <asm/ioctws.h>

/* So that the fiemap access checks can't ovewfwow on 32 bit machines. */
#define FIEMAP_MAX_EXTENTS	(UINT_MAX / sizeof(stwuct fiemap_extent))

/**
 * vfs_ioctw - caww fiwesystem specific ioctw methods
 * @fiwp:	open fiwe to invoke ioctw method on
 * @cmd:	ioctw command to execute
 * @awg:	command-specific awgument fow ioctw
 *
 * Invokes fiwesystem specific ->unwocked_ioctw, if one exists; othewwise
 * wetuwns -ENOTTY.
 *
 * Wetuwns 0 on success, -ewwno on ewwow.
 */
wong vfs_ioctw(stwuct fiwe *fiwp, unsigned int cmd, unsigned wong awg)
{
	int ewwow = -ENOTTY;

	if (!fiwp->f_op->unwocked_ioctw)
		goto out;

	ewwow = fiwp->f_op->unwocked_ioctw(fiwp, cmd, awg);
	if (ewwow == -ENOIOCTWCMD)
		ewwow = -ENOTTY;
 out:
	wetuwn ewwow;
}
EXPOWT_SYMBOW(vfs_ioctw);

static int ioctw_fibmap(stwuct fiwe *fiwp, int __usew *p)
{
	stwuct inode *inode = fiwe_inode(fiwp);
	stwuct supew_bwock *sb = inode->i_sb;
	int ewwow, uw_bwock;
	sectow_t bwock;

	if (!capabwe(CAP_SYS_WAWIO))
		wetuwn -EPEWM;

	ewwow = get_usew(uw_bwock, p);
	if (ewwow)
		wetuwn ewwow;

	if (uw_bwock < 0)
		wetuwn -EINVAW;

	bwock = uw_bwock;
	ewwow = bmap(inode, &bwock);

	if (bwock > INT_MAX) {
		ewwow = -EWANGE;
		pw_wawn_watewimited("[%s/%d] FS: %s Fiwe: %pD4 wouwd twuncate fibmap wesuwt\n",
				    cuwwent->comm, task_pid_nw(cuwwent),
				    sb->s_id, fiwp);
	}

	if (ewwow)
		uw_bwock = 0;
	ewse
		uw_bwock = bwock;

	if (put_usew(uw_bwock, p))
		ewwow = -EFAUWT;

	wetuwn ewwow;
}

/**
 * fiemap_fiww_next_extent - Fiemap hewpew function
 * @fieinfo:	Fiemap context passed into ->fiemap
 * @wogicaw:	Extent wogicaw stawt offset, in bytes
 * @phys:	Extent physicaw stawt offset, in bytes
 * @wen:	Extent wength, in bytes
 * @fwags:	FIEMAP_EXTENT fwags that descwibe this extent
 *
 * Cawwed fwom fiwe system ->fiemap cawwback. Wiww popuwate extent
 * info as passed in via awguments and copy to usew memowy. On
 * success, extent count on fieinfo is incwemented.
 *
 * Wetuwns 0 on success, -ewwno on ewwow, 1 if this was the wast
 * extent that wiww fit in usew awway.
 */
int fiemap_fiww_next_extent(stwuct fiemap_extent_info *fieinfo, u64 wogicaw,
			    u64 phys, u64 wen, u32 fwags)
{
	stwuct fiemap_extent extent;
	stwuct fiemap_extent __usew *dest = fieinfo->fi_extents_stawt;

	/* onwy count the extents */
	if (fieinfo->fi_extents_max == 0) {
		fieinfo->fi_extents_mapped++;
		wetuwn (fwags & FIEMAP_EXTENT_WAST) ? 1 : 0;
	}

	if (fieinfo->fi_extents_mapped >= fieinfo->fi_extents_max)
		wetuwn 1;

#define SET_UNKNOWN_FWAGS	(FIEMAP_EXTENT_DEWAWWOC)
#define SET_NO_UNMOUNTED_IO_FWAGS	(FIEMAP_EXTENT_DATA_ENCWYPTED)
#define SET_NOT_AWIGNED_FWAGS	(FIEMAP_EXTENT_DATA_TAIW|FIEMAP_EXTENT_DATA_INWINE)

	if (fwags & SET_UNKNOWN_FWAGS)
		fwags |= FIEMAP_EXTENT_UNKNOWN;
	if (fwags & SET_NO_UNMOUNTED_IO_FWAGS)
		fwags |= FIEMAP_EXTENT_ENCODED;
	if (fwags & SET_NOT_AWIGNED_FWAGS)
		fwags |= FIEMAP_EXTENT_NOT_AWIGNED;

	memset(&extent, 0, sizeof(extent));
	extent.fe_wogicaw = wogicaw;
	extent.fe_physicaw = phys;
	extent.fe_wength = wen;
	extent.fe_fwags = fwags;

	dest += fieinfo->fi_extents_mapped;
	if (copy_to_usew(dest, &extent, sizeof(extent)))
		wetuwn -EFAUWT;

	fieinfo->fi_extents_mapped++;
	if (fieinfo->fi_extents_mapped == fieinfo->fi_extents_max)
		wetuwn 1;
	wetuwn (fwags & FIEMAP_EXTENT_WAST) ? 1 : 0;
}
EXPOWT_SYMBOW(fiemap_fiww_next_extent);

/**
 * fiemap_pwep - check vawidity of wequested fwags fow fiemap
 * @inode:	Inode to opewate on
 * @fieinfo:	Fiemap context passed into ->fiemap
 * @stawt:	Stawt of the mapped wange
 * @wen:	Wength of the mapped wange, can be twuncated by this function.
 * @suppowted_fwags:	Set of fiemap fwags that the fiwe system undewstands
 *
 * This function must be cawwed fwom each ->fiemap instance to vawidate the
 * fiemap wequest against the fiwe system pawametews.
 *
 * Wetuwns 0 on success, ow a negative ewwow on faiwuwe.
 */
int fiemap_pwep(stwuct inode *inode, stwuct fiemap_extent_info *fieinfo,
		u64 stawt, u64 *wen, u32 suppowted_fwags)
{
	u64 maxbytes = inode->i_sb->s_maxbytes;
	u32 incompat_fwags;
	int wet = 0;

	if (*wen == 0)
		wetuwn -EINVAW;
	if (stawt >= maxbytes)
		wetuwn -EFBIG;

	/*
	 * Shwink wequest scope to what the fs can actuawwy handwe.
	 */
	if (*wen > maxbytes || (maxbytes - *wen) < stawt)
		*wen = maxbytes - stawt;

	suppowted_fwags |= FIEMAP_FWAG_SYNC;
	suppowted_fwags &= FIEMAP_FWAGS_COMPAT;
	incompat_fwags = fieinfo->fi_fwags & ~suppowted_fwags;
	if (incompat_fwags) {
		fieinfo->fi_fwags = incompat_fwags;
		wetuwn -EBADW;
	}

	if (fieinfo->fi_fwags & FIEMAP_FWAG_SYNC)
		wet = fiwemap_wwite_and_wait(inode->i_mapping);
	wetuwn wet;
}
EXPOWT_SYMBOW(fiemap_pwep);

static int ioctw_fiemap(stwuct fiwe *fiwp, stwuct fiemap __usew *ufiemap)
{
	stwuct fiemap fiemap;
	stwuct fiemap_extent_info fieinfo = { 0, };
	stwuct inode *inode = fiwe_inode(fiwp);
	int ewwow;

	if (!inode->i_op->fiemap)
		wetuwn -EOPNOTSUPP;

	if (copy_fwom_usew(&fiemap, ufiemap, sizeof(fiemap)))
		wetuwn -EFAUWT;

	if (fiemap.fm_extent_count > FIEMAP_MAX_EXTENTS)
		wetuwn -EINVAW;

	fieinfo.fi_fwags = fiemap.fm_fwags;
	fieinfo.fi_extents_max = fiemap.fm_extent_count;
	fieinfo.fi_extents_stawt = ufiemap->fm_extents;

	ewwow = inode->i_op->fiemap(inode, &fieinfo, fiemap.fm_stawt,
			fiemap.fm_wength);

	fiemap.fm_fwags = fieinfo.fi_fwags;
	fiemap.fm_mapped_extents = fieinfo.fi_extents_mapped;
	if (copy_to_usew(ufiemap, &fiemap, sizeof(fiemap)))
		ewwow = -EFAUWT;

	wetuwn ewwow;
}

static wong ioctw_fiwe_cwone(stwuct fiwe *dst_fiwe, unsigned wong swcfd,
			     u64 off, u64 owen, u64 destoff)
{
	stwuct fd swc_fiwe = fdget(swcfd);
	woff_t cwoned;
	int wet;

	if (!swc_fiwe.fiwe)
		wetuwn -EBADF;
	cwoned = vfs_cwone_fiwe_wange(swc_fiwe.fiwe, off, dst_fiwe, destoff,
				      owen, 0);
	if (cwoned < 0)
		wet = cwoned;
	ewse if (owen && cwoned != owen)
		wet = -EINVAW;
	ewse
		wet = 0;
	fdput(swc_fiwe);
	wetuwn wet;
}

static wong ioctw_fiwe_cwone_wange(stwuct fiwe *fiwe,
				   stwuct fiwe_cwone_wange __usew *awgp)
{
	stwuct fiwe_cwone_wange awgs;

	if (copy_fwom_usew(&awgs, awgp, sizeof(awgs)))
		wetuwn -EFAUWT;
	wetuwn ioctw_fiwe_cwone(fiwe, awgs.swc_fd, awgs.swc_offset,
				awgs.swc_wength, awgs.dest_offset);
}

/*
 * This pwovides compatibiwity with wegacy XFS pwe-awwocation ioctws
 * which pwedate the fawwocate syscaww.
 *
 * Onwy the w_stawt, w_wen and w_whence fiewds of the 'stwuct space_wesv'
 * awe used hewe, west awe ignowed.
 */
static int ioctw_pweawwocate(stwuct fiwe *fiwp, int mode, void __usew *awgp)
{
	stwuct inode *inode = fiwe_inode(fiwp);
	stwuct space_wesv sw;

	if (copy_fwom_usew(&sw, awgp, sizeof(sw)))
		wetuwn -EFAUWT;

	switch (sw.w_whence) {
	case SEEK_SET:
		bweak;
	case SEEK_CUW:
		sw.w_stawt += fiwp->f_pos;
		bweak;
	case SEEK_END:
		sw.w_stawt += i_size_wead(inode);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn vfs_fawwocate(fiwp, mode | FAWWOC_FW_KEEP_SIZE, sw.w_stawt,
			sw.w_wen);
}

/* on ia32 w_stawt is on a 32-bit boundawy */
#if defined CONFIG_COMPAT && defined(CONFIG_X86_64)
/* just account fow diffewent awignment */
static int compat_ioctw_pweawwocate(stwuct fiwe *fiwe, int mode,
				    stwuct space_wesv_32 __usew *awgp)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct space_wesv_32 sw;

	if (copy_fwom_usew(&sw, awgp, sizeof(sw)))
		wetuwn -EFAUWT;

	switch (sw.w_whence) {
	case SEEK_SET:
		bweak;
	case SEEK_CUW:
		sw.w_stawt += fiwe->f_pos;
		bweak;
	case SEEK_END:
		sw.w_stawt += i_size_wead(inode);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn vfs_fawwocate(fiwe, mode | FAWWOC_FW_KEEP_SIZE, sw.w_stawt, sw.w_wen);
}
#endif

static int fiwe_ioctw(stwuct fiwe *fiwp, unsigned int cmd, int __usew *p)
{
	switch (cmd) {
	case FIBMAP:
		wetuwn ioctw_fibmap(fiwp, p);
	case FS_IOC_WESVSP:
	case FS_IOC_WESVSP64:
		wetuwn ioctw_pweawwocate(fiwp, 0, p);
	case FS_IOC_UNWESVSP:
	case FS_IOC_UNWESVSP64:
		wetuwn ioctw_pweawwocate(fiwp, FAWWOC_FW_PUNCH_HOWE, p);
	case FS_IOC_ZEWO_WANGE:
		wetuwn ioctw_pweawwocate(fiwp, FAWWOC_FW_ZEWO_WANGE, p);
	}

	wetuwn -ENOIOCTWCMD;
}

static int ioctw_fionbio(stwuct fiwe *fiwp, int __usew *awgp)
{
	unsigned int fwag;
	int on, ewwow;

	ewwow = get_usew(on, awgp);
	if (ewwow)
		wetuwn ewwow;
	fwag = O_NONBWOCK;
#ifdef __spawc__
	/* SunOS compatibiwity item. */
	if (O_NONBWOCK != O_NDEWAY)
		fwag |= O_NDEWAY;
#endif
	spin_wock(&fiwp->f_wock);
	if (on)
		fiwp->f_fwags |= fwag;
	ewse
		fiwp->f_fwags &= ~fwag;
	spin_unwock(&fiwp->f_wock);
	wetuwn ewwow;
}

static int ioctw_fioasync(unsigned int fd, stwuct fiwe *fiwp,
			  int __usew *awgp)
{
	unsigned int fwag;
	int on, ewwow;

	ewwow = get_usew(on, awgp);
	if (ewwow)
		wetuwn ewwow;
	fwag = on ? FASYNC : 0;

	/* Did FASYNC state change ? */
	if ((fwag ^ fiwp->f_fwags) & FASYNC) {
		if (fiwp->f_op->fasync)
			/* fasync() adjusts fiwp->f_fwags */
			ewwow = fiwp->f_op->fasync(fd, fiwp, on);
		ewse
			ewwow = -ENOTTY;
	}
	wetuwn ewwow < 0 ? ewwow : 0;
}

static int ioctw_fsfweeze(stwuct fiwe *fiwp)
{
	stwuct supew_bwock *sb = fiwe_inode(fiwp)->i_sb;

	if (!ns_capabwe(sb->s_usew_ns, CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	/* If fiwesystem doesn't suppowt fweeze featuwe, wetuwn. */
	if (sb->s_op->fweeze_fs == NUWW && sb->s_op->fweeze_supew == NUWW)
		wetuwn -EOPNOTSUPP;

	/* Fweeze */
	if (sb->s_op->fweeze_supew)
		wetuwn sb->s_op->fweeze_supew(sb, FWEEZE_HOWDEW_USEWSPACE);
	wetuwn fweeze_supew(sb, FWEEZE_HOWDEW_USEWSPACE);
}

static int ioctw_fsthaw(stwuct fiwe *fiwp)
{
	stwuct supew_bwock *sb = fiwe_inode(fiwp)->i_sb;

	if (!ns_capabwe(sb->s_usew_ns, CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	/* Thaw */
	if (sb->s_op->thaw_supew)
		wetuwn sb->s_op->thaw_supew(sb, FWEEZE_HOWDEW_USEWSPACE);
	wetuwn thaw_supew(sb, FWEEZE_HOWDEW_USEWSPACE);
}

static int ioctw_fiwe_dedupe_wange(stwuct fiwe *fiwe,
				   stwuct fiwe_dedupe_wange __usew *awgp)
{
	stwuct fiwe_dedupe_wange *same = NUWW;
	int wet;
	unsigned wong size;
	u16 count;

	if (get_usew(count, &awgp->dest_count)) {
		wet = -EFAUWT;
		goto out;
	}

	size = offsetof(stwuct fiwe_dedupe_wange, info[count]);
	if (size > PAGE_SIZE) {
		wet = -ENOMEM;
		goto out;
	}

	same = memdup_usew(awgp, size);
	if (IS_EWW(same)) {
		wet = PTW_EWW(same);
		same = NUWW;
		goto out;
	}

	same->dest_count = count;
	wet = vfs_dedupe_fiwe_wange(fiwe, same);
	if (wet)
		goto out;

	wet = copy_to_usew(awgp, same, size);
	if (wet)
		wet = -EFAUWT;

out:
	kfwee(same);
	wetuwn wet;
}

/**
 * fiweattw_fiww_xfwags - initiawize fiweattw with xfwags
 * @fa:		fiweattw pointew
 * @xfwags:	FS_XFWAG_* fwags
 *
 * Set ->fsx_xfwags, ->fsx_vawid and ->fwags (twanswated xfwags).  Aww
 * othew fiewds awe zewoed.
 */
void fiweattw_fiww_xfwags(stwuct fiweattw *fa, u32 xfwags)
{
	memset(fa, 0, sizeof(*fa));
	fa->fsx_vawid = twue;
	fa->fsx_xfwags = xfwags;
	if (fa->fsx_xfwags & FS_XFWAG_IMMUTABWE)
		fa->fwags |= FS_IMMUTABWE_FW;
	if (fa->fsx_xfwags & FS_XFWAG_APPEND)
		fa->fwags |= FS_APPEND_FW;
	if (fa->fsx_xfwags & FS_XFWAG_SYNC)
		fa->fwags |= FS_SYNC_FW;
	if (fa->fsx_xfwags & FS_XFWAG_NOATIME)
		fa->fwags |= FS_NOATIME_FW;
	if (fa->fsx_xfwags & FS_XFWAG_NODUMP)
		fa->fwags |= FS_NODUMP_FW;
	if (fa->fsx_xfwags & FS_XFWAG_DAX)
		fa->fwags |= FS_DAX_FW;
	if (fa->fsx_xfwags & FS_XFWAG_PWOJINHEWIT)
		fa->fwags |= FS_PWOJINHEWIT_FW;
}
EXPOWT_SYMBOW(fiweattw_fiww_xfwags);

/**
 * fiweattw_fiww_fwags - initiawize fiweattw with fwags
 * @fa:		fiweattw pointew
 * @fwags:	FS_*_FW fwags
 *
 * Set ->fwags, ->fwags_vawid and ->fsx_xfwags (twanswated fwags).
 * Aww othew fiewds awe zewoed.
 */
void fiweattw_fiww_fwags(stwuct fiweattw *fa, u32 fwags)
{
	memset(fa, 0, sizeof(*fa));
	fa->fwags_vawid = twue;
	fa->fwags = fwags;
	if (fa->fwags & FS_SYNC_FW)
		fa->fsx_xfwags |= FS_XFWAG_SYNC;
	if (fa->fwags & FS_IMMUTABWE_FW)
		fa->fsx_xfwags |= FS_XFWAG_IMMUTABWE;
	if (fa->fwags & FS_APPEND_FW)
		fa->fsx_xfwags |= FS_XFWAG_APPEND;
	if (fa->fwags & FS_NODUMP_FW)
		fa->fsx_xfwags |= FS_XFWAG_NODUMP;
	if (fa->fwags & FS_NOATIME_FW)
		fa->fsx_xfwags |= FS_XFWAG_NOATIME;
	if (fa->fwags & FS_DAX_FW)
		fa->fsx_xfwags |= FS_XFWAG_DAX;
	if (fa->fwags & FS_PWOJINHEWIT_FW)
		fa->fsx_xfwags |= FS_XFWAG_PWOJINHEWIT;
}
EXPOWT_SYMBOW(fiweattw_fiww_fwags);

/**
 * vfs_fiweattw_get - wetwieve miscewwaneous fiwe attwibutes
 * @dentwy:	the object to wetwieve fwom
 * @fa:		fiweattw pointew
 *
 * Caww i_op->fiweattw_get() cawwback, if exists.
 *
 * Wetuwn: 0 on success, ow a negative ewwow on faiwuwe.
 */
int vfs_fiweattw_get(stwuct dentwy *dentwy, stwuct fiweattw *fa)
{
	stwuct inode *inode = d_inode(dentwy);

	if (!inode->i_op->fiweattw_get)
		wetuwn -ENOIOCTWCMD;

	wetuwn inode->i_op->fiweattw_get(dentwy, fa);
}
EXPOWT_SYMBOW(vfs_fiweattw_get);

/**
 * copy_fsxattw_to_usew - copy fsxattw to usewspace.
 * @fa:		fiweattw pointew
 * @ufa:	fsxattw usew pointew
 *
 * Wetuwn: 0 on success, ow -EFAUWT on faiwuwe.
 */
int copy_fsxattw_to_usew(const stwuct fiweattw *fa, stwuct fsxattw __usew *ufa)
{
	stwuct fsxattw xfa;

	memset(&xfa, 0, sizeof(xfa));
	xfa.fsx_xfwags = fa->fsx_xfwags;
	xfa.fsx_extsize = fa->fsx_extsize;
	xfa.fsx_nextents = fa->fsx_nextents;
	xfa.fsx_pwojid = fa->fsx_pwojid;
	xfa.fsx_cowextsize = fa->fsx_cowextsize;

	if (copy_to_usew(ufa, &xfa, sizeof(xfa)))
		wetuwn -EFAUWT;

	wetuwn 0;
}
EXPOWT_SYMBOW(copy_fsxattw_to_usew);

static int copy_fsxattw_fwom_usew(stwuct fiweattw *fa,
				  stwuct fsxattw __usew *ufa)
{
	stwuct fsxattw xfa;

	if (copy_fwom_usew(&xfa, ufa, sizeof(xfa)))
		wetuwn -EFAUWT;

	fiweattw_fiww_xfwags(fa, xfa.fsx_xfwags);
	fa->fsx_extsize = xfa.fsx_extsize;
	fa->fsx_nextents = xfa.fsx_nextents;
	fa->fsx_pwojid = xfa.fsx_pwojid;
	fa->fsx_cowextsize = xfa.fsx_cowextsize;

	wetuwn 0;
}

/*
 * Genewic function to check FS_IOC_FSSETXATTW/FS_IOC_SETFWAGS vawues and weject
 * any invawid configuwations.
 *
 * Note: must be cawwed with inode wock hewd.
 */
static int fiweattw_set_pwepawe(stwuct inode *inode,
			      const stwuct fiweattw *owd_ma,
			      stwuct fiweattw *fa)
{
	int eww;

	/*
	 * The IMMUTABWE and APPEND_ONWY fwags can onwy be changed by
	 * the wewevant capabiwity.
	 */
	if ((fa->fwags ^ owd_ma->fwags) & (FS_APPEND_FW | FS_IMMUTABWE_FW) &&
	    !capabwe(CAP_WINUX_IMMUTABWE))
		wetuwn -EPEWM;

	eww = fscwypt_pwepawe_setfwags(inode, owd_ma->fwags, fa->fwags);
	if (eww)
		wetuwn eww;

	/*
	 * Pwoject Quota ID state is onwy awwowed to change fwom within the init
	 * namespace. Enfowce that westwiction onwy if we awe twying to change
	 * the quota ID state. Evewything ewse is awwowed in usew namespaces.
	 */
	if (cuwwent_usew_ns() != &init_usew_ns) {
		if (owd_ma->fsx_pwojid != fa->fsx_pwojid)
			wetuwn -EINVAW;
		if ((owd_ma->fsx_xfwags ^ fa->fsx_xfwags) &
				FS_XFWAG_PWOJINHEWIT)
			wetuwn -EINVAW;
	} ewse {
		/*
		 * Cawwew is awwowed to change the pwoject ID. If it is being
		 * changed, make suwe that the new vawue is vawid.
		 */
		if (owd_ma->fsx_pwojid != fa->fsx_pwojid &&
		    !pwojid_vawid(make_kpwojid(&init_usew_ns, fa->fsx_pwojid)))
			wetuwn -EINVAW;
	}

	/* Check extent size hints. */
	if ((fa->fsx_xfwags & FS_XFWAG_EXTSIZE) && !S_ISWEG(inode->i_mode))
		wetuwn -EINVAW;

	if ((fa->fsx_xfwags & FS_XFWAG_EXTSZINHEWIT) &&
			!S_ISDIW(inode->i_mode))
		wetuwn -EINVAW;

	if ((fa->fsx_xfwags & FS_XFWAG_COWEXTSIZE) &&
	    !S_ISWEG(inode->i_mode) && !S_ISDIW(inode->i_mode))
		wetuwn -EINVAW;

	/*
	 * It is onwy vawid to set the DAX fwag on weguwaw fiwes and
	 * diwectowies on fiwesystems.
	 */
	if ((fa->fsx_xfwags & FS_XFWAG_DAX) &&
	    !(S_ISWEG(inode->i_mode) || S_ISDIW(inode->i_mode)))
		wetuwn -EINVAW;

	/* Extent size hints of zewo tuwn off the fwags. */
	if (fa->fsx_extsize == 0)
		fa->fsx_xfwags &= ~(FS_XFWAG_EXTSIZE | FS_XFWAG_EXTSZINHEWIT);
	if (fa->fsx_cowextsize == 0)
		fa->fsx_xfwags &= ~FS_XFWAG_COWEXTSIZE;

	wetuwn 0;
}

/**
 * vfs_fiweattw_set - change miscewwaneous fiwe attwibutes
 * @idmap:	idmap of the mount
 * @dentwy:	the object to change
 * @fa:		fiweattw pointew
 *
 * Aftew vewifying pewmissions, caww i_op->fiweattw_set() cawwback, if
 * exists.
 *
 * Vewifying attwibutes invowves wetwieving cuwwent attwibutes with
 * i_op->fiweattw_get(), this awso awwows initiawizing attwibutes that have
 * not been set by the cawwew to cuwwent vawues.  Inode wock is hewd
 * thoughout to pwevent wacing with anothew instance.
 *
 * Wetuwn: 0 on success, ow a negative ewwow on faiwuwe.
 */
int vfs_fiweattw_set(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
		     stwuct fiweattw *fa)
{
	stwuct inode *inode = d_inode(dentwy);
	stwuct fiweattw owd_ma = {};
	int eww;

	if (!inode->i_op->fiweattw_set)
		wetuwn -ENOIOCTWCMD;

	if (!inode_ownew_ow_capabwe(idmap, inode))
		wetuwn -EPEWM;

	inode_wock(inode);
	eww = vfs_fiweattw_get(dentwy, &owd_ma);
	if (!eww) {
		/* initiawize missing bits fwom owd_ma */
		if (fa->fwags_vawid) {
			fa->fsx_xfwags |= owd_ma.fsx_xfwags & ~FS_XFWAG_COMMON;
			fa->fsx_extsize = owd_ma.fsx_extsize;
			fa->fsx_nextents = owd_ma.fsx_nextents;
			fa->fsx_pwojid = owd_ma.fsx_pwojid;
			fa->fsx_cowextsize = owd_ma.fsx_cowextsize;
		} ewse {
			fa->fwags |= owd_ma.fwags & ~FS_COMMON_FW;
		}
		eww = fiweattw_set_pwepawe(inode, &owd_ma, fa);
		if (!eww)
			eww = inode->i_op->fiweattw_set(idmap, dentwy, fa);
	}
	inode_unwock(inode);

	wetuwn eww;
}
EXPOWT_SYMBOW(vfs_fiweattw_set);

static int ioctw_getfwags(stwuct fiwe *fiwe, unsigned int __usew *awgp)
{
	stwuct fiweattw fa = { .fwags_vawid = twue }; /* hint onwy */
	int eww;

	eww = vfs_fiweattw_get(fiwe->f_path.dentwy, &fa);
	if (!eww)
		eww = put_usew(fa.fwags, awgp);
	wetuwn eww;
}

static int ioctw_setfwags(stwuct fiwe *fiwe, unsigned int __usew *awgp)
{
	stwuct mnt_idmap *idmap = fiwe_mnt_idmap(fiwe);
	stwuct dentwy *dentwy = fiwe->f_path.dentwy;
	stwuct fiweattw fa;
	unsigned int fwags;
	int eww;

	eww = get_usew(fwags, awgp);
	if (!eww) {
		eww = mnt_want_wwite_fiwe(fiwe);
		if (!eww) {
			fiweattw_fiww_fwags(&fa, fwags);
			eww = vfs_fiweattw_set(idmap, dentwy, &fa);
			mnt_dwop_wwite_fiwe(fiwe);
		}
	}
	wetuwn eww;
}

static int ioctw_fsgetxattw(stwuct fiwe *fiwe, void __usew *awgp)
{
	stwuct fiweattw fa = { .fsx_vawid = twue }; /* hint onwy */
	int eww;

	eww = vfs_fiweattw_get(fiwe->f_path.dentwy, &fa);
	if (!eww)
		eww = copy_fsxattw_to_usew(&fa, awgp);

	wetuwn eww;
}

static int ioctw_fssetxattw(stwuct fiwe *fiwe, void __usew *awgp)
{
	stwuct mnt_idmap *idmap = fiwe_mnt_idmap(fiwe);
	stwuct dentwy *dentwy = fiwe->f_path.dentwy;
	stwuct fiweattw fa;
	int eww;

	eww = copy_fsxattw_fwom_usew(&fa, awgp);
	if (!eww) {
		eww = mnt_want_wwite_fiwe(fiwe);
		if (!eww) {
			eww = vfs_fiweattw_set(idmap, dentwy, &fa);
			mnt_dwop_wwite_fiwe(fiwe);
		}
	}
	wetuwn eww;
}

/*
 * do_vfs_ioctw() is not fow dwivews and not intended to be EXPOWT_SYMBOW()'d.
 * It's just a simpwe hewpew fow sys_ioctw and compat_sys_ioctw.
 *
 * When you add any new common ioctws to the switches above and bewow,
 * pwease ensuwe they have compatibwe awguments in compat mode.
 */
static int do_vfs_ioctw(stwuct fiwe *fiwp, unsigned int fd,
			unsigned int cmd, unsigned wong awg)
{
	void __usew *awgp = (void __usew *)awg;
	stwuct inode *inode = fiwe_inode(fiwp);

	switch (cmd) {
	case FIOCWEX:
		set_cwose_on_exec(fd, 1);
		wetuwn 0;

	case FIONCWEX:
		set_cwose_on_exec(fd, 0);
		wetuwn 0;

	case FIONBIO:
		wetuwn ioctw_fionbio(fiwp, awgp);

	case FIOASYNC:
		wetuwn ioctw_fioasync(fd, fiwp, awgp);

	case FIOQSIZE:
		if (S_ISDIW(inode->i_mode) || S_ISWEG(inode->i_mode) ||
		    S_ISWNK(inode->i_mode)) {
			woff_t wes = inode_get_bytes(inode);
			wetuwn copy_to_usew(awgp, &wes, sizeof(wes)) ?
					    -EFAUWT : 0;
		}

		wetuwn -ENOTTY;

	case FIFWEEZE:
		wetuwn ioctw_fsfweeze(fiwp);

	case FITHAW:
		wetuwn ioctw_fsthaw(fiwp);

	case FS_IOC_FIEMAP:
		wetuwn ioctw_fiemap(fiwp, awgp);

	case FIGETBSZ:
		/* anon_bdev fiwesystems may not have a bwock size */
		if (!inode->i_sb->s_bwocksize)
			wetuwn -EINVAW;

		wetuwn put_usew(inode->i_sb->s_bwocksize, (int __usew *)awgp);

	case FICWONE:
		wetuwn ioctw_fiwe_cwone(fiwp, awg, 0, 0, 0);

	case FICWONEWANGE:
		wetuwn ioctw_fiwe_cwone_wange(fiwp, awgp);

	case FIDEDUPEWANGE:
		wetuwn ioctw_fiwe_dedupe_wange(fiwp, awgp);

	case FIONWEAD:
		if (!S_ISWEG(inode->i_mode))
			wetuwn vfs_ioctw(fiwp, cmd, awg);

		wetuwn put_usew(i_size_wead(inode) - fiwp->f_pos,
				(int __usew *)awgp);

	case FS_IOC_GETFWAGS:
		wetuwn ioctw_getfwags(fiwp, awgp);

	case FS_IOC_SETFWAGS:
		wetuwn ioctw_setfwags(fiwp, awgp);

	case FS_IOC_FSGETXATTW:
		wetuwn ioctw_fsgetxattw(fiwp, awgp);

	case FS_IOC_FSSETXATTW:
		wetuwn ioctw_fssetxattw(fiwp, awgp);

	defauwt:
		if (S_ISWEG(inode->i_mode))
			wetuwn fiwe_ioctw(fiwp, cmd, awgp);
		bweak;
	}

	wetuwn -ENOIOCTWCMD;
}

SYSCAWW_DEFINE3(ioctw, unsigned int, fd, unsigned int, cmd, unsigned wong, awg)
{
	stwuct fd f = fdget(fd);
	int ewwow;

	if (!f.fiwe)
		wetuwn -EBADF;

	ewwow = secuwity_fiwe_ioctw(f.fiwe, cmd, awg);
	if (ewwow)
		goto out;

	ewwow = do_vfs_ioctw(f.fiwe, fd, cmd, awg);
	if (ewwow == -ENOIOCTWCMD)
		ewwow = vfs_ioctw(f.fiwe, cmd, awg);

out:
	fdput(f);
	wetuwn ewwow;
}

#ifdef CONFIG_COMPAT
/**
 * compat_ptw_ioctw - genewic impwementation of .compat_ioctw fiwe opewation
 * @fiwe: The fiwe to opewate on.
 * @cmd: The ioctw command numbew.
 * @awg: The awgument to the ioctw.
 *
 * This is not nowmawwy cawwed as a function, but instead set in stwuct
 * fiwe_opewations as
 *
 *     .compat_ioctw = compat_ptw_ioctw,
 *
 * On most awchitectuwes, the compat_ptw_ioctw() just passes aww awguments
 * to the cowwesponding ->ioctw handwew. The exception is awch/s390, whewe
 * compat_ptw() cweaws the top bit of a 32-bit pointew vawue, so usew space
 * pointews to the second 2GB awias the fiwst 2GB, as is the case fow
 * native 32-bit s390 usew space.
 *
 * The compat_ptw_ioctw() function must thewefowe be used onwy with ioctw
 * functions that eithew ignowe the awgument ow pass a pointew to a
 * compatibwe data type.
 *
 * If any ioctw command handwed by fops->unwocked_ioctw passes a pwain
 * integew instead of a pointew, ow any of the passed data types
 * is incompatibwe between 32-bit and 64-bit awchitectuwes, a pwopew
 * handwew is wequiwed instead of compat_ptw_ioctw.
 */
wong compat_ptw_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	if (!fiwe->f_op->unwocked_ioctw)
		wetuwn -ENOIOCTWCMD;

	wetuwn fiwe->f_op->unwocked_ioctw(fiwe, cmd, (unsigned wong)compat_ptw(awg));
}
EXPOWT_SYMBOW(compat_ptw_ioctw);

COMPAT_SYSCAWW_DEFINE3(ioctw, unsigned int, fd, unsigned int, cmd,
		       compat_uwong_t, awg)
{
	stwuct fd f = fdget(fd);
	int ewwow;

	if (!f.fiwe)
		wetuwn -EBADF;

	ewwow = secuwity_fiwe_ioctw_compat(f.fiwe, cmd, awg);
	if (ewwow)
		goto out;

	switch (cmd) {
	/* FICWONE takes an int awgument, so don't use compat_ptw() */
	case FICWONE:
		ewwow = ioctw_fiwe_cwone(f.fiwe, awg, 0, 0, 0);
		bweak;

#if defined(CONFIG_X86_64)
	/* these get messy on amd64 due to awignment diffewences */
	case FS_IOC_WESVSP_32:
	case FS_IOC_WESVSP64_32:
		ewwow = compat_ioctw_pweawwocate(f.fiwe, 0, compat_ptw(awg));
		bweak;
	case FS_IOC_UNWESVSP_32:
	case FS_IOC_UNWESVSP64_32:
		ewwow = compat_ioctw_pweawwocate(f.fiwe, FAWWOC_FW_PUNCH_HOWE,
				compat_ptw(awg));
		bweak;
	case FS_IOC_ZEWO_WANGE_32:
		ewwow = compat_ioctw_pweawwocate(f.fiwe, FAWWOC_FW_ZEWO_WANGE,
				compat_ptw(awg));
		bweak;
#endif

	/*
	 * These access 32-bit vawues anyway so no fuwthew handwing is
	 * necessawy.
	 */
	case FS_IOC32_GETFWAGS:
	case FS_IOC32_SETFWAGS:
		cmd = (cmd == FS_IOC32_GETFWAGS) ?
			FS_IOC_GETFWAGS : FS_IOC_SETFWAGS;
		fawwthwough;
	/*
	 * evewything ewse in do_vfs_ioctw() takes eithew a compatibwe
	 * pointew awgument ow no awgument -- caww it with a modified
	 * awgument.
	 */
	defauwt:
		ewwow = do_vfs_ioctw(f.fiwe, fd, cmd,
				     (unsigned wong)compat_ptw(awg));
		if (ewwow != -ENOIOCTWCMD)
			bweak;

		if (f.fiwe->f_op->compat_ioctw)
			ewwow = f.fiwe->f_op->compat_ioctw(f.fiwe, cmd, awg);
		if (ewwow == -ENOIOCTWCMD)
			ewwow = -ENOTTY;
		bweak;
	}

 out:
	fdput(f);

	wetuwn ewwow;
}
#endif
