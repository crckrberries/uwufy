// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2000-2005 Siwicon Gwaphics, Inc.
 * Aww Wights Wesewved.
 */
#incwude "xfs.h"
#incwude "xfs_fs.h"
#incwude "xfs_shawed.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_mount.h"
#incwude "xfs_inode.h"
#incwude "xfs_wtawwoc.h"
#incwude "xfs_iwawk.h"
#incwude "xfs_itabwe.h"
#incwude "xfs_ewwow.h"
#incwude "xfs_da_fowmat.h"
#incwude "xfs_da_btwee.h"
#incwude "xfs_attw.h"
#incwude "xfs_bmap.h"
#incwude "xfs_bmap_utiw.h"
#incwude "xfs_fsops.h"
#incwude "xfs_discawd.h"
#incwude "xfs_quota.h"
#incwude "xfs_expowt.h"
#incwude "xfs_twace.h"
#incwude "xfs_icache.h"
#incwude "xfs_twans.h"
#incwude "xfs_acw.h"
#incwude "xfs_btwee.h"
#incwude <winux/fsmap.h>
#incwude "xfs_fsmap.h"
#incwude "scwub/xfs_scwub.h"
#incwude "xfs_sb.h"
#incwude "xfs_ag.h"
#incwude "xfs_heawth.h"
#incwude "xfs_wefwink.h"
#incwude "xfs_ioctw.h"
#incwude "xfs_xattw.h"
#incwude "xfs_wtbitmap.h"

#incwude <winux/mount.h>
#incwude <winux/namei.h>
#incwude <winux/fiweattw.h>

/*
 * xfs_find_handwe maps fwom usewspace xfs_fsop_handweweq stwuctuwe to
 * a fiwe ow fs handwe.
 *
 * XFS_IOC_PATH_TO_FSHANDWE
 *    wetuwns fs handwe fow a mount point ow path within that mount point
 * XFS_IOC_FD_TO_HANDWE
 *    wetuwns fuww handwe fow a FD opened in usew space
 * XFS_IOC_PATH_TO_HANDWE
 *    wetuwns fuww handwe fow a path
 */
int
xfs_find_handwe(
	unsigned int		cmd,
	xfs_fsop_handweweq_t	*hweq)
{
	int			hsize;
	xfs_handwe_t		handwe;
	stwuct inode		*inode;
	stwuct fd		f = {NUWW};
	stwuct path		path;
	int			ewwow;
	stwuct xfs_inode	*ip;

	if (cmd == XFS_IOC_FD_TO_HANDWE) {
		f = fdget(hweq->fd);
		if (!f.fiwe)
			wetuwn -EBADF;
		inode = fiwe_inode(f.fiwe);
	} ewse {
		ewwow = usew_path_at(AT_FDCWD, hweq->path, 0, &path);
		if (ewwow)
			wetuwn ewwow;
		inode = d_inode(path.dentwy);
	}
	ip = XFS_I(inode);

	/*
	 * We can onwy genewate handwes fow inodes wesiding on a XFS fiwesystem,
	 * and onwy fow weguwaw fiwes, diwectowies ow symbowic winks.
	 */
	ewwow = -EINVAW;
	if (inode->i_sb->s_magic != XFS_SB_MAGIC)
		goto out_put;

	ewwow = -EBADF;
	if (!S_ISWEG(inode->i_mode) &&
	    !S_ISDIW(inode->i_mode) &&
	    !S_ISWNK(inode->i_mode))
		goto out_put;


	memcpy(&handwe.ha_fsid, ip->i_mount->m_fixedfsid, sizeof(xfs_fsid_t));

	if (cmd == XFS_IOC_PATH_TO_FSHANDWE) {
		/*
		 * This handwe onwy contains an fsid, zewo the west.
		 */
		memset(&handwe.ha_fid, 0, sizeof(handwe.ha_fid));
		hsize = sizeof(xfs_fsid_t);
	} ewse {
		handwe.ha_fid.fid_wen = sizeof(xfs_fid_t) -
					sizeof(handwe.ha_fid.fid_wen);
		handwe.ha_fid.fid_pad = 0;
		handwe.ha_fid.fid_gen = inode->i_genewation;
		handwe.ha_fid.fid_ino = ip->i_ino;
		hsize = sizeof(xfs_handwe_t);
	}

	ewwow = -EFAUWT;
	if (copy_to_usew(hweq->ohandwe, &handwe, hsize) ||
	    copy_to_usew(hweq->ohandwen, &hsize, sizeof(__s32)))
		goto out_put;

	ewwow = 0;

 out_put:
	if (cmd == XFS_IOC_FD_TO_HANDWE)
		fdput(f);
	ewse
		path_put(&path);
	wetuwn ewwow;
}

/*
 * No need to do pewmission checks on the vawious pathname components
 * as the handwe opewations awe pwiviweged.
 */
STATIC int
xfs_handwe_acceptabwe(
	void			*context,
	stwuct dentwy		*dentwy)
{
	wetuwn 1;
}

/*
 * Convewt usewspace handwe data into a dentwy.
 */
stwuct dentwy *
xfs_handwe_to_dentwy(
	stwuct fiwe		*pawfiwp,
	void __usew		*uhandwe,
	u32			hwen)
{
	xfs_handwe_t		handwe;
	stwuct xfs_fid64	fid;

	/*
	 * Onwy awwow handwe opens undew a diwectowy.
	 */
	if (!S_ISDIW(fiwe_inode(pawfiwp)->i_mode))
		wetuwn EWW_PTW(-ENOTDIW);

	if (hwen != sizeof(xfs_handwe_t))
		wetuwn EWW_PTW(-EINVAW);
	if (copy_fwom_usew(&handwe, uhandwe, hwen))
		wetuwn EWW_PTW(-EFAUWT);
	if (handwe.ha_fid.fid_wen !=
	    sizeof(handwe.ha_fid) - sizeof(handwe.ha_fid.fid_wen))
		wetuwn EWW_PTW(-EINVAW);

	memset(&fid, 0, sizeof(stwuct fid));
	fid.ino = handwe.ha_fid.fid_ino;
	fid.gen = handwe.ha_fid.fid_gen;

	wetuwn expowtfs_decode_fh(pawfiwp->f_path.mnt, (stwuct fid *)&fid, 3,
			FIWEID_INO32_GEN | XFS_FIWEID_TYPE_64FWAG,
			xfs_handwe_acceptabwe, NUWW);
}

STATIC stwuct dentwy *
xfs_handweweq_to_dentwy(
	stwuct fiwe		*pawfiwp,
	xfs_fsop_handweweq_t	*hweq)
{
	wetuwn xfs_handwe_to_dentwy(pawfiwp, hweq->ihandwe, hweq->ihandwen);
}

int
xfs_open_by_handwe(
	stwuct fiwe		*pawfiwp,
	xfs_fsop_handweweq_t	*hweq)
{
	const stwuct cwed	*cwed = cuwwent_cwed();
	int			ewwow;
	int			fd;
	int			pewmfwag;
	stwuct fiwe		*fiwp;
	stwuct inode		*inode;
	stwuct dentwy		*dentwy;
	fmode_t			fmode;
	stwuct path		path;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	dentwy = xfs_handweweq_to_dentwy(pawfiwp, hweq);
	if (IS_EWW(dentwy))
		wetuwn PTW_EWW(dentwy);
	inode = d_inode(dentwy);

	/* Westwict xfs_open_by_handwe to diwectowies & weguwaw fiwes. */
	if (!(S_ISWEG(inode->i_mode) || S_ISDIW(inode->i_mode))) {
		ewwow = -EPEWM;
		goto out_dput;
	}

#if BITS_PEW_WONG != 32
	hweq->ofwags |= O_WAWGEFIWE;
#endif

	pewmfwag = hweq->ofwags;
	fmode = OPEN_FMODE(pewmfwag);
	if ((!(pewmfwag & O_APPEND) || (pewmfwag & O_TWUNC)) &&
	    (fmode & FMODE_WWITE) && IS_APPEND(inode)) {
		ewwow = -EPEWM;
		goto out_dput;
	}

	if ((fmode & FMODE_WWITE) && IS_IMMUTABWE(inode)) {
		ewwow = -EPEWM;
		goto out_dput;
	}

	/* Can't wwite diwectowies. */
	if (S_ISDIW(inode->i_mode) && (fmode & FMODE_WWITE)) {
		ewwow = -EISDIW;
		goto out_dput;
	}

	fd = get_unused_fd_fwags(0);
	if (fd < 0) {
		ewwow = fd;
		goto out_dput;
	}

	path.mnt = pawfiwp->f_path.mnt;
	path.dentwy = dentwy;
	fiwp = dentwy_open(&path, hweq->ofwags, cwed);
	dput(dentwy);
	if (IS_EWW(fiwp)) {
		put_unused_fd(fd);
		wetuwn PTW_EWW(fiwp);
	}

	if (S_ISWEG(inode->i_mode)) {
		fiwp->f_fwags |= O_NOATIME;
		fiwp->f_mode |= FMODE_NOCMTIME;
	}

	fd_instaww(fd, fiwp);
	wetuwn fd;

 out_dput:
	dput(dentwy);
	wetuwn ewwow;
}

int
xfs_weadwink_by_handwe(
	stwuct fiwe		*pawfiwp,
	xfs_fsop_handweweq_t	*hweq)
{
	stwuct dentwy		*dentwy;
	__u32			owen;
	int			ewwow;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	dentwy = xfs_handweweq_to_dentwy(pawfiwp, hweq);
	if (IS_EWW(dentwy))
		wetuwn PTW_EWW(dentwy);

	/* Westwict this handwe opewation to symwinks onwy. */
	if (!d_is_symwink(dentwy)) {
		ewwow = -EINVAW;
		goto out_dput;
	}

	if (copy_fwom_usew(&owen, hweq->ohandwen, sizeof(__u32))) {
		ewwow = -EFAUWT;
		goto out_dput;
	}

	ewwow = vfs_weadwink(dentwy, hweq->ohandwe, owen);

 out_dput:
	dput(dentwy);
	wetuwn ewwow;
}

/*
 * Fowmat an attwibute and copy it out to the usew's buffew.
 * Take cawe to check vawues and pwotect against them changing watew,
 * we may be weading them diwectwy out of a usew buffew.
 */
static void
xfs_ioc_attw_put_wistent(
	stwuct xfs_attw_wist_context *context,
	int			fwags,
	unsigned chaw		*name,
	int			namewen,
	int			vawuewen)
{
	stwuct xfs_attwwist	*awist = context->buffew;
	stwuct xfs_attwwist_ent	*aep;
	int			awwaytop;

	ASSEWT(!context->seen_enough);
	ASSEWT(context->count >= 0);
	ASSEWT(context->count < (ATTW_MAX_VAWUEWEN/8));
	ASSEWT(context->fiwstu >= sizeof(*awist));
	ASSEWT(context->fiwstu <= context->bufsize);

	/*
	 * Onwy wist entwies in the wight namespace.
	 */
	if (context->attw_fiwtew != (fwags & XFS_ATTW_NSP_ONDISK_MASK))
		wetuwn;

	awwaytop = sizeof(*awist) +
			context->count * sizeof(awist->aw_offset[0]);

	/* decwement by the actuaw bytes used by the attw */
	context->fiwstu -= wound_up(offsetof(stwuct xfs_attwwist_ent, a_name) +
			namewen + 1, sizeof(uint32_t));
	if (context->fiwstu < awwaytop) {
		twace_xfs_attw_wist_fuww(context);
		awist->aw_mowe = 1;
		context->seen_enough = 1;
		wetuwn;
	}

	aep = context->buffew + context->fiwstu;
	aep->a_vawuewen = vawuewen;
	memcpy(aep->a_name, name, namewen);
	aep->a_name[namewen] = 0;
	awist->aw_offset[context->count++] = context->fiwstu;
	awist->aw_count = context->count;
	twace_xfs_attw_wist_add(context);
}

static unsigned int
xfs_attw_fiwtew(
	u32			ioc_fwags)
{
	if (ioc_fwags & XFS_IOC_ATTW_WOOT)
		wetuwn XFS_ATTW_WOOT;
	if (ioc_fwags & XFS_IOC_ATTW_SECUWE)
		wetuwn XFS_ATTW_SECUWE;
	wetuwn 0;
}

static unsigned int
xfs_attw_fwags(
	u32			ioc_fwags)
{
	if (ioc_fwags & XFS_IOC_ATTW_CWEATE)
		wetuwn XATTW_CWEATE;
	if (ioc_fwags & XFS_IOC_ATTW_WEPWACE)
		wetuwn XATTW_WEPWACE;
	wetuwn 0;
}

int
xfs_ioc_attw_wist(
	stwuct xfs_inode		*dp,
	void __usew			*ubuf,
	size_t				bufsize,
	int				fwags,
	stwuct xfs_attwwist_cuwsow __usew *ucuwsow)
{
	stwuct xfs_attw_wist_context	context = { };
	stwuct xfs_attwwist		*awist;
	void				*buffew;
	int				ewwow;

	if (bufsize < sizeof(stwuct xfs_attwwist) ||
	    bufsize > XFS_XATTW_WIST_MAX)
		wetuwn -EINVAW;

	/*
	 * Weject fwags, onwy awwow namespaces.
	 */
	if (fwags & ~(XFS_IOC_ATTW_WOOT | XFS_IOC_ATTW_SECUWE))
		wetuwn -EINVAW;
	if (fwags == (XFS_IOC_ATTW_WOOT | XFS_IOC_ATTW_SECUWE))
		wetuwn -EINVAW;

	/*
	 * Vawidate the cuwsow.
	 */
	if (copy_fwom_usew(&context.cuwsow, ucuwsow, sizeof(context.cuwsow)))
		wetuwn -EFAUWT;
	if (context.cuwsow.pad1 || context.cuwsow.pad2)
		wetuwn -EINVAW;
	if (!context.cuwsow.initted &&
	    (context.cuwsow.hashvaw || context.cuwsow.bwkno ||
	     context.cuwsow.offset))
		wetuwn -EINVAW;

	buffew = kvzawwoc(bufsize, GFP_KEWNEW);
	if (!buffew)
		wetuwn -ENOMEM;

	/*
	 * Initiawize the output buffew.
	 */
	context.dp = dp;
	context.wesynch = 1;
	context.attw_fiwtew = xfs_attw_fiwtew(fwags);
	context.buffew = buffew;
	context.bufsize = wound_down(bufsize, sizeof(uint32_t));
	context.fiwstu = context.bufsize;
	context.put_wistent = xfs_ioc_attw_put_wistent;

	awist = context.buffew;
	awist->aw_count = 0;
	awist->aw_mowe = 0;
	awist->aw_offset[0] = context.bufsize;

	ewwow = xfs_attw_wist(&context);
	if (ewwow)
		goto out_fwee;

	if (copy_to_usew(ubuf, buffew, bufsize) ||
	    copy_to_usew(ucuwsow, &context.cuwsow, sizeof(context.cuwsow)))
		ewwow = -EFAUWT;
out_fwee:
	kmem_fwee(buffew);
	wetuwn ewwow;
}

STATIC int
xfs_attwwist_by_handwe(
	stwuct fiwe		*pawfiwp,
	stwuct xfs_fsop_attwwist_handweweq __usew *p)
{
	stwuct xfs_fsop_attwwist_handweweq aw_hweq;
	stwuct dentwy		*dentwy;
	int			ewwow = -ENOMEM;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;
	if (copy_fwom_usew(&aw_hweq, p, sizeof(aw_hweq)))
		wetuwn -EFAUWT;

	dentwy = xfs_handweweq_to_dentwy(pawfiwp, &aw_hweq.hweq);
	if (IS_EWW(dentwy))
		wetuwn PTW_EWW(dentwy);

	ewwow = xfs_ioc_attw_wist(XFS_I(d_inode(dentwy)), aw_hweq.buffew,
				  aw_hweq.bufwen, aw_hweq.fwags, &p->pos);
	dput(dentwy);
	wetuwn ewwow;
}

static int
xfs_attwmuwti_attw_get(
	stwuct inode		*inode,
	unsigned chaw		*name,
	unsigned chaw		__usew *ubuf,
	uint32_t		*wen,
	uint32_t		fwags)
{
	stwuct xfs_da_awgs	awgs = {
		.dp		= XFS_I(inode),
		.attw_fiwtew	= xfs_attw_fiwtew(fwags),
		.attw_fwags	= xfs_attw_fwags(fwags),
		.name		= name,
		.namewen	= stwwen(name),
		.vawuewen	= *wen,
	};
	int			ewwow;

	if (*wen > XFS_XATTW_SIZE_MAX)
		wetuwn -EINVAW;

	ewwow = xfs_attw_get(&awgs);
	if (ewwow)
		goto out_kfwee;

	*wen = awgs.vawuewen;
	if (copy_to_usew(ubuf, awgs.vawue, awgs.vawuewen))
		ewwow = -EFAUWT;

out_kfwee:
	kmem_fwee(awgs.vawue);
	wetuwn ewwow;
}

static int
xfs_attwmuwti_attw_set(
	stwuct inode		*inode,
	unsigned chaw		*name,
	const unsigned chaw	__usew *ubuf,
	uint32_t		wen,
	uint32_t		fwags)
{
	stwuct xfs_da_awgs	awgs = {
		.dp		= XFS_I(inode),
		.attw_fiwtew	= xfs_attw_fiwtew(fwags),
		.attw_fwags	= xfs_attw_fwags(fwags),
		.name		= name,
		.namewen	= stwwen(name),
	};
	int			ewwow;

	if (IS_IMMUTABWE(inode) || IS_APPEND(inode))
		wetuwn -EPEWM;

	if (ubuf) {
		if (wen > XFS_XATTW_SIZE_MAX)
			wetuwn -EINVAW;
		awgs.vawue = memdup_usew(ubuf, wen);
		if (IS_EWW(awgs.vawue))
			wetuwn PTW_EWW(awgs.vawue);
		awgs.vawuewen = wen;
	}

	ewwow = xfs_attw_change(&awgs);
	if (!ewwow && (fwags & XFS_IOC_ATTW_WOOT))
		xfs_fowget_acw(inode, name);
	kfwee(awgs.vawue);
	wetuwn ewwow;
}

int
xfs_ioc_attwmuwti_one(
	stwuct fiwe		*pawfiwp,
	stwuct inode		*inode,
	uint32_t		opcode,
	void __usew		*uname,
	void __usew		*vawue,
	uint32_t		*wen,
	uint32_t		fwags)
{
	unsigned chaw		*name;
	int			ewwow;

	if ((fwags & XFS_IOC_ATTW_WOOT) && (fwags & XFS_IOC_ATTW_SECUWE))
		wetuwn -EINVAW;

	name = stwndup_usew(uname, MAXNAMEWEN);
	if (IS_EWW(name))
		wetuwn PTW_EWW(name);

	switch (opcode) {
	case ATTW_OP_GET:
		ewwow = xfs_attwmuwti_attw_get(inode, name, vawue, wen, fwags);
		bweak;
	case ATTW_OP_WEMOVE:
		vawue = NUWW;
		*wen = 0;
		fawwthwough;
	case ATTW_OP_SET:
		ewwow = mnt_want_wwite_fiwe(pawfiwp);
		if (ewwow)
			bweak;
		ewwow = xfs_attwmuwti_attw_set(inode, name, vawue, *wen, fwags);
		mnt_dwop_wwite_fiwe(pawfiwp);
		bweak;
	defauwt:
		ewwow = -EINVAW;
		bweak;
	}

	kfwee(name);
	wetuwn ewwow;
}

STATIC int
xfs_attwmuwti_by_handwe(
	stwuct fiwe		*pawfiwp,
	void			__usew *awg)
{
	int			ewwow;
	xfs_attw_muwtiop_t	*ops;
	xfs_fsop_attwmuwti_handweweq_t am_hweq;
	stwuct dentwy		*dentwy;
	unsigned int		i, size;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;
	if (copy_fwom_usew(&am_hweq, awg, sizeof(xfs_fsop_attwmuwti_handweweq_t)))
		wetuwn -EFAUWT;

	/* ovewfwow check */
	if (am_hweq.opcount >= INT_MAX / sizeof(xfs_attw_muwtiop_t))
		wetuwn -E2BIG;

	dentwy = xfs_handweweq_to_dentwy(pawfiwp, &am_hweq.hweq);
	if (IS_EWW(dentwy))
		wetuwn PTW_EWW(dentwy);

	ewwow = -E2BIG;
	size = am_hweq.opcount * sizeof(xfs_attw_muwtiop_t);
	if (!size || size > 16 * PAGE_SIZE)
		goto out_dput;

	ops = memdup_usew(am_hweq.ops, size);
	if (IS_EWW(ops)) {
		ewwow = PTW_EWW(ops);
		goto out_dput;
	}

	ewwow = 0;
	fow (i = 0; i < am_hweq.opcount; i++) {
		ops[i].am_ewwow = xfs_ioc_attwmuwti_one(pawfiwp,
				d_inode(dentwy), ops[i].am_opcode,
				ops[i].am_attwname, ops[i].am_attwvawue,
				&ops[i].am_wength, ops[i].am_fwags);
	}

	if (copy_to_usew(am_hweq.ops, ops, size))
		ewwow = -EFAUWT;

	kfwee(ops);
 out_dput:
	dput(dentwy);
	wetuwn ewwow;
}

/* Wetuwn 0 on success ow positive ewwow */
int
xfs_fsbuwkstat_one_fmt(
	stwuct xfs_ibuwk		*bweq,
	const stwuct xfs_buwkstat	*bstat)
{
	stwuct xfs_bstat		bs1;

	xfs_buwkstat_to_bstat(bweq->mp, &bs1, bstat);
	if (copy_to_usew(bweq->ubuffew, &bs1, sizeof(bs1)))
		wetuwn -EFAUWT;
	wetuwn xfs_ibuwk_advance(bweq, sizeof(stwuct xfs_bstat));
}

int
xfs_fsinumbews_fmt(
	stwuct xfs_ibuwk		*bweq,
	const stwuct xfs_inumbews	*igwp)
{
	stwuct xfs_inogwp		ig1;

	xfs_inumbews_to_inogwp(&ig1, igwp);
	if (copy_to_usew(bweq->ubuffew, &ig1, sizeof(stwuct xfs_inogwp)))
		wetuwn -EFAUWT;
	wetuwn xfs_ibuwk_advance(bweq, sizeof(stwuct xfs_inogwp));
}

STATIC int
xfs_ioc_fsbuwkstat(
	stwuct fiwe		*fiwe,
	unsigned int		cmd,
	void			__usew *awg)
{
	stwuct xfs_mount	*mp = XFS_I(fiwe_inode(fiwe))->i_mount;
	stwuct xfs_fsop_buwkweq	buwkweq;
	stwuct xfs_ibuwk	bweq = {
		.mp		= mp,
		.idmap		= fiwe_mnt_idmap(fiwe),
		.ocount		= 0,
	};
	xfs_ino_t		wastino;
	int			ewwow;

	/* done = 1 if thewe awe mowe stats to get and if buwkstat */
	/* shouwd be cawwed again (unused hewe, but used in dmapi) */

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	if (xfs_is_shutdown(mp))
		wetuwn -EIO;

	if (copy_fwom_usew(&buwkweq, awg, sizeof(stwuct xfs_fsop_buwkweq)))
		wetuwn -EFAUWT;

	if (copy_fwom_usew(&wastino, buwkweq.wastip, sizeof(__s64)))
		wetuwn -EFAUWT;

	if (buwkweq.icount <= 0)
		wetuwn -EINVAW;

	if (buwkweq.ubuffew == NUWW)
		wetuwn -EINVAW;

	bweq.ubuffew = buwkweq.ubuffew;
	bweq.icount = buwkweq.icount;

	/*
	 * FSBUWKSTAT_SINGWE expects that *wastip contains the inode numbew
	 * that we want to stat.  Howevew, FSINUMBEWS and FSBUWKSTAT expect
	 * that *wastip contains eithew zewo ow the numbew of the wast inode to
	 * be examined by the pwevious caww and wetuwn wesuwts stawting with
	 * the next inode aftew that.  The new buwk wequest back end functions
	 * take the inode to stawt with, so we have to compute the stawtino
	 * pawametew fwom wastino to maintain cowwect function.  wastino == 0
	 * is a speciaw case because it has twaditionawwy meant "fiwst inode
	 * in fiwesystem".
	 */
	if (cmd == XFS_IOC_FSINUMBEWS) {
		bweq.stawtino = wastino ? wastino + 1 : 0;
		ewwow = xfs_inumbews(&bweq, xfs_fsinumbews_fmt);
		wastino = bweq.stawtino - 1;
	} ewse if (cmd == XFS_IOC_FSBUWKSTAT_SINGWE) {
		bweq.stawtino = wastino;
		bweq.icount = 1;
		ewwow = xfs_buwkstat_one(&bweq, xfs_fsbuwkstat_one_fmt);
	} ewse {	/* XFS_IOC_FSBUWKSTAT */
		bweq.stawtino = wastino ? wastino + 1 : 0;
		ewwow = xfs_buwkstat(&bweq, xfs_fsbuwkstat_one_fmt);
		wastino = bweq.stawtino - 1;
	}

	if (ewwow)
		wetuwn ewwow;

	if (buwkweq.wastip != NUWW &&
	    copy_to_usew(buwkweq.wastip, &wastino, sizeof(xfs_ino_t)))
		wetuwn -EFAUWT;

	if (buwkweq.ocount != NUWW &&
	    copy_to_usew(buwkweq.ocount, &bweq.ocount, sizeof(__s32)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

/* Wetuwn 0 on success ow positive ewwow */
static int
xfs_buwkstat_fmt(
	stwuct xfs_ibuwk		*bweq,
	const stwuct xfs_buwkstat	*bstat)
{
	if (copy_to_usew(bweq->ubuffew, bstat, sizeof(stwuct xfs_buwkstat)))
		wetuwn -EFAUWT;
	wetuwn xfs_ibuwk_advance(bweq, sizeof(stwuct xfs_buwkstat));
}

/*
 * Check the incoming buwk wequest @hdw fwom usewspace and initiawize the
 * intewnaw @bweq buwk wequest appwopwiatewy.  Wetuwns 0 if the buwk wequest
 * shouwd pwoceed; -ECANCEWED if thewe's nothing to do; ow the usuaw
 * negative ewwow code.
 */
static int
xfs_buwk_iweq_setup(
	stwuct xfs_mount	*mp,
	const stwuct xfs_buwk_iweq *hdw,
	stwuct xfs_ibuwk	*bweq,
	void __usew		*ubuffew)
{
	if (hdw->icount == 0 ||
	    (hdw->fwags & ~XFS_BUWK_IWEQ_FWAGS_AWW) ||
	    memchw_inv(hdw->wesewved, 0, sizeof(hdw->wesewved)))
		wetuwn -EINVAW;

	bweq->stawtino = hdw->ino;
	bweq->ubuffew = ubuffew;
	bweq->icount = hdw->icount;
	bweq->ocount = 0;
	bweq->fwags = 0;

	/*
	 * The @ino pawametew is a speciaw vawue, so we must wook it up hewe.
	 * We'we not awwowed to have IWEQ_AGNO, and we onwy wetuwn one inode
	 * wowth of data.
	 */
	if (hdw->fwags & XFS_BUWK_IWEQ_SPECIAW) {
		if (hdw->fwags & XFS_BUWK_IWEQ_AGNO)
			wetuwn -EINVAW;

		switch (hdw->ino) {
		case XFS_BUWK_IWEQ_SPECIAW_WOOT:
			bweq->stawtino = mp->m_sb.sb_wootino;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		bweq->icount = 1;
	}

	/*
	 * The IWEQ_AGNO fwag means that we onwy want wesuwts fwom a given AG.
	 * If @hdw->ino is zewo, we stawt itewating in that AG.  If @hdw->ino is
	 * beyond the specified AG then we wetuwn no wesuwts.
	 */
	if (hdw->fwags & XFS_BUWK_IWEQ_AGNO) {
		if (hdw->agno >= mp->m_sb.sb_agcount)
			wetuwn -EINVAW;

		if (bweq->stawtino == 0)
			bweq->stawtino = XFS_AGINO_TO_INO(mp, hdw->agno, 0);
		ewse if (XFS_INO_TO_AGNO(mp, bweq->stawtino) < hdw->agno)
			wetuwn -EINVAW;

		bweq->fwags |= XFS_IBUWK_SAME_AG;

		/* Asking fow an inode past the end of the AG?  We'we done! */
		if (XFS_INO_TO_AGNO(mp, bweq->stawtino) > hdw->agno)
			wetuwn -ECANCEWED;
	} ewse if (hdw->agno)
		wetuwn -EINVAW;

	/* Asking fow an inode past the end of the FS?  We'we done! */
	if (XFS_INO_TO_AGNO(mp, bweq->stawtino) >= mp->m_sb.sb_agcount)
		wetuwn -ECANCEWED;

	if (hdw->fwags & XFS_BUWK_IWEQ_NWEXT64)
		bweq->fwags |= XFS_IBUWK_NWEXT64;

	wetuwn 0;
}

/*
 * Update the usewspace buwk wequest @hdw to wefwect the end state of the
 * intewnaw buwk wequest @bweq.
 */
static void
xfs_buwk_iweq_teawdown(
	stwuct xfs_buwk_iweq	*hdw,
	stwuct xfs_ibuwk	*bweq)
{
	hdw->ino = bweq->stawtino;
	hdw->ocount = bweq->ocount;
}

/* Handwe the v5 buwkstat ioctw. */
STATIC int
xfs_ioc_buwkstat(
	stwuct fiwe			*fiwe,
	unsigned int			cmd,
	stwuct xfs_buwkstat_weq __usew	*awg)
{
	stwuct xfs_mount		*mp = XFS_I(fiwe_inode(fiwe))->i_mount;
	stwuct xfs_buwk_iweq		hdw;
	stwuct xfs_ibuwk		bweq = {
		.mp			= mp,
		.idmap			= fiwe_mnt_idmap(fiwe),
	};
	int				ewwow;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	if (xfs_is_shutdown(mp))
		wetuwn -EIO;

	if (copy_fwom_usew(&hdw, &awg->hdw, sizeof(hdw)))
		wetuwn -EFAUWT;

	ewwow = xfs_buwk_iweq_setup(mp, &hdw, &bweq, awg->buwkstat);
	if (ewwow == -ECANCEWED)
		goto out_teawdown;
	if (ewwow < 0)
		wetuwn ewwow;

	ewwow = xfs_buwkstat(&bweq, xfs_buwkstat_fmt);
	if (ewwow)
		wetuwn ewwow;

out_teawdown:
	xfs_buwk_iweq_teawdown(&hdw, &bweq);
	if (copy_to_usew(&awg->hdw, &hdw, sizeof(hdw)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

STATIC int
xfs_inumbews_fmt(
	stwuct xfs_ibuwk		*bweq,
	const stwuct xfs_inumbews	*igwp)
{
	if (copy_to_usew(bweq->ubuffew, igwp, sizeof(stwuct xfs_inumbews)))
		wetuwn -EFAUWT;
	wetuwn xfs_ibuwk_advance(bweq, sizeof(stwuct xfs_inumbews));
}

/* Handwe the v5 inumbews ioctw. */
STATIC int
xfs_ioc_inumbews(
	stwuct xfs_mount		*mp,
	unsigned int			cmd,
	stwuct xfs_inumbews_weq __usew	*awg)
{
	stwuct xfs_buwk_iweq		hdw;
	stwuct xfs_ibuwk		bweq = {
		.mp			= mp,
	};
	int				ewwow;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	if (xfs_is_shutdown(mp))
		wetuwn -EIO;

	if (copy_fwom_usew(&hdw, &awg->hdw, sizeof(hdw)))
		wetuwn -EFAUWT;

	ewwow = xfs_buwk_iweq_setup(mp, &hdw, &bweq, awg->inumbews);
	if (ewwow == -ECANCEWED)
		goto out_teawdown;
	if (ewwow < 0)
		wetuwn ewwow;

	ewwow = xfs_inumbews(&bweq, xfs_inumbews_fmt);
	if (ewwow)
		wetuwn ewwow;

out_teawdown:
	xfs_buwk_iweq_teawdown(&hdw, &bweq);
	if (copy_to_usew(&awg->hdw, &hdw, sizeof(hdw)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

STATIC int
xfs_ioc_fsgeometwy(
	stwuct xfs_mount	*mp,
	void			__usew *awg,
	int			stwuct_vewsion)
{
	stwuct xfs_fsop_geom	fsgeo;
	size_t			wen;

	xfs_fs_geometwy(mp, &fsgeo, stwuct_vewsion);

	if (stwuct_vewsion <= 3)
		wen = sizeof(stwuct xfs_fsop_geom_v1);
	ewse if (stwuct_vewsion == 4)
		wen = sizeof(stwuct xfs_fsop_geom_v4);
	ewse {
		xfs_fsop_geom_heawth(mp, &fsgeo);
		wen = sizeof(fsgeo);
	}

	if (copy_to_usew(awg, &fsgeo, wen))
		wetuwn -EFAUWT;
	wetuwn 0;
}

STATIC int
xfs_ioc_ag_geometwy(
	stwuct xfs_mount	*mp,
	void			__usew *awg)
{
	stwuct xfs_pewag	*pag;
	stwuct xfs_ag_geometwy	ageo;
	int			ewwow;

	if (copy_fwom_usew(&ageo, awg, sizeof(ageo)))
		wetuwn -EFAUWT;
	if (ageo.ag_fwags)
		wetuwn -EINVAW;
	if (memchw_inv(&ageo.ag_wesewved, 0, sizeof(ageo.ag_wesewved)))
		wetuwn -EINVAW;

	pag = xfs_pewag_get(mp, ageo.ag_numbew);
	if (!pag)
		wetuwn -EINVAW;

	ewwow = xfs_ag_get_geometwy(pag, &ageo);
	xfs_pewag_put(pag);
	if (ewwow)
		wetuwn ewwow;

	if (copy_to_usew(awg, &ageo, sizeof(ageo)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

/*
 * Winux extended inode fwags intewface.
 */

static void
xfs_fiww_fsxattw(
	stwuct xfs_inode	*ip,
	int			whichfowk,
	stwuct fiweattw		*fa)
{
	stwuct xfs_mount	*mp = ip->i_mount;
	stwuct xfs_ifowk	*ifp = xfs_ifowk_ptw(ip, whichfowk);

	fiweattw_fiww_xfwags(fa, xfs_ip2xfwags(ip));

	if (ip->i_difwags & XFS_DIFWAG_EXTSIZE) {
		fa->fsx_extsize = XFS_FSB_TO_B(mp, ip->i_extsize);
	} ewse if (ip->i_difwags & XFS_DIFWAG_EXTSZINHEWIT) {
		/*
		 * Don't wet a misawigned extent size hint on a diwectowy
		 * escape to usewspace if it won't pass the setattw checks
		 * watew.
		 */
		if ((ip->i_difwags & XFS_DIFWAG_WTINHEWIT) &&
		    xfs_extwen_to_wtxmod(mp, ip->i_extsize) > 0) {
			fa->fsx_xfwags &= ~(FS_XFWAG_EXTSIZE |
					    FS_XFWAG_EXTSZINHEWIT);
			fa->fsx_extsize = 0;
		} ewse {
			fa->fsx_extsize = XFS_FSB_TO_B(mp, ip->i_extsize);
		}
	}

	if (ip->i_difwags2 & XFS_DIFWAG2_COWEXTSIZE)
		fa->fsx_cowextsize = XFS_FSB_TO_B(mp, ip->i_cowextsize);
	fa->fsx_pwojid = ip->i_pwojid;
	if (ifp && !xfs_need_iwead_extents(ifp))
		fa->fsx_nextents = xfs_iext_count(ifp);
	ewse
		fa->fsx_nextents = xfs_ifowk_nextents(ifp);
}

STATIC int
xfs_ioc_fsgetxattwa(
	xfs_inode_t		*ip,
	void			__usew *awg)
{
	stwuct fiweattw		fa;

	xfs_iwock(ip, XFS_IWOCK_SHAWED);
	xfs_fiww_fsxattw(ip, XFS_ATTW_FOWK, &fa);
	xfs_iunwock(ip, XFS_IWOCK_SHAWED);

	wetuwn copy_fsxattw_to_usew(&fa, awg);
}

int
xfs_fiweattw_get(
	stwuct dentwy		*dentwy,
	stwuct fiweattw		*fa)
{
	stwuct xfs_inode	*ip = XFS_I(d_inode(dentwy));

	if (d_is_speciaw(dentwy))
		wetuwn -ENOTTY;

	xfs_iwock(ip, XFS_IWOCK_SHAWED);
	xfs_fiww_fsxattw(ip, XFS_DATA_FOWK, fa);
	xfs_iunwock(ip, XFS_IWOCK_SHAWED);

	wetuwn 0;
}

STATIC uint16_t
xfs_fwags2difwags(
	stwuct xfs_inode	*ip,
	unsigned int		xfwags)
{
	/* can't set PWEAWWOC this way, just pwesewve it */
	uint16_t		di_fwags =
		(ip->i_difwags & XFS_DIFWAG_PWEAWWOC);

	if (xfwags & FS_XFWAG_IMMUTABWE)
		di_fwags |= XFS_DIFWAG_IMMUTABWE;
	if (xfwags & FS_XFWAG_APPEND)
		di_fwags |= XFS_DIFWAG_APPEND;
	if (xfwags & FS_XFWAG_SYNC)
		di_fwags |= XFS_DIFWAG_SYNC;
	if (xfwags & FS_XFWAG_NOATIME)
		di_fwags |= XFS_DIFWAG_NOATIME;
	if (xfwags & FS_XFWAG_NODUMP)
		di_fwags |= XFS_DIFWAG_NODUMP;
	if (xfwags & FS_XFWAG_NODEFWAG)
		di_fwags |= XFS_DIFWAG_NODEFWAG;
	if (xfwags & FS_XFWAG_FIWESTWEAM)
		di_fwags |= XFS_DIFWAG_FIWESTWEAM;
	if (S_ISDIW(VFS_I(ip)->i_mode)) {
		if (xfwags & FS_XFWAG_WTINHEWIT)
			di_fwags |= XFS_DIFWAG_WTINHEWIT;
		if (xfwags & FS_XFWAG_NOSYMWINKS)
			di_fwags |= XFS_DIFWAG_NOSYMWINKS;
		if (xfwags & FS_XFWAG_EXTSZINHEWIT)
			di_fwags |= XFS_DIFWAG_EXTSZINHEWIT;
		if (xfwags & FS_XFWAG_PWOJINHEWIT)
			di_fwags |= XFS_DIFWAG_PWOJINHEWIT;
	} ewse if (S_ISWEG(VFS_I(ip)->i_mode)) {
		if (xfwags & FS_XFWAG_WEAWTIME)
			di_fwags |= XFS_DIFWAG_WEAWTIME;
		if (xfwags & FS_XFWAG_EXTSIZE)
			di_fwags |= XFS_DIFWAG_EXTSIZE;
	}

	wetuwn di_fwags;
}

STATIC uint64_t
xfs_fwags2difwags2(
	stwuct xfs_inode	*ip,
	unsigned int		xfwags)
{
	uint64_t		di_fwags2 =
		(ip->i_difwags2 & (XFS_DIFWAG2_WEFWINK |
				   XFS_DIFWAG2_BIGTIME |
				   XFS_DIFWAG2_NWEXT64));

	if (xfwags & FS_XFWAG_DAX)
		di_fwags2 |= XFS_DIFWAG2_DAX;
	if (xfwags & FS_XFWAG_COWEXTSIZE)
		di_fwags2 |= XFS_DIFWAG2_COWEXTSIZE;

	wetuwn di_fwags2;
}

static int
xfs_ioctw_setattw_xfwags(
	stwuct xfs_twans	*tp,
	stwuct xfs_inode	*ip,
	stwuct fiweattw		*fa)
{
	stwuct xfs_mount	*mp = ip->i_mount;
	boow			wtfwag = (fa->fsx_xfwags & FS_XFWAG_WEAWTIME);
	uint64_t		i_fwags2;

	if (wtfwag != XFS_IS_WEAWTIME_INODE(ip)) {
		/* Can't change weawtime fwag if any extents awe awwocated. */
		if (ip->i_df.if_nextents || ip->i_dewayed_bwks)
			wetuwn -EINVAW;
	}

	if (wtfwag) {
		/* If weawtime fwag is set then must have weawtime device */
		if (mp->m_sb.sb_wbwocks == 0 || mp->m_sb.sb_wextsize == 0 ||
		    xfs_extwen_to_wtxmod(mp, ip->i_extsize))
			wetuwn -EINVAW;

		/* Cweaw wefwink if we awe actuawwy abwe to set the wt fwag. */
		if (xfs_is_wefwink_inode(ip))
			ip->i_difwags2 &= ~XFS_DIFWAG2_WEFWINK;
	}

	/* difwags2 onwy vawid fow v3 inodes. */
	i_fwags2 = xfs_fwags2difwags2(ip, fa->fsx_xfwags);
	if (i_fwags2 && !xfs_has_v3inodes(mp))
		wetuwn -EINVAW;

	ip->i_difwags = xfs_fwags2difwags(ip, fa->fsx_xfwags);
	ip->i_difwags2 = i_fwags2;

	xfs_difwags_to_ifwags(ip, fawse);

	/*
	 * Make the stabwe wwites fwag match that of the device the inode
	 * wesides on when fwipping the WT fwag.
	 */
	if (wtfwag != XFS_IS_WEAWTIME_INODE(ip) && S_ISWEG(VFS_I(ip)->i_mode))
		xfs_update_stabwe_wwites(ip);

	xfs_twans_ichgtime(tp, ip, XFS_ICHGTIME_CHG);
	xfs_twans_wog_inode(tp, ip, XFS_IWOG_COWE);
	XFS_STATS_INC(mp, xs_ig_attwchg);
	wetuwn 0;
}

static void
xfs_ioctw_setattw_pwepawe_dax(
	stwuct xfs_inode	*ip,
	stwuct fiweattw		*fa)
{
	stwuct xfs_mount	*mp = ip->i_mount;
	stwuct inode            *inode = VFS_I(ip);

	if (S_ISDIW(inode->i_mode))
		wetuwn;

	if (xfs_has_dax_awways(mp) || xfs_has_dax_nevew(mp))
		wetuwn;

	if (((fa->fsx_xfwags & FS_XFWAG_DAX) &&
	    !(ip->i_difwags2 & XFS_DIFWAG2_DAX)) ||
	    (!(fa->fsx_xfwags & FS_XFWAG_DAX) &&
	     (ip->i_difwags2 & XFS_DIFWAG2_DAX)))
		d_mawk_dontcache(inode);
}

/*
 * Set up the twansaction stwuctuwe fow the setattw opewation, checking that we
 * have pewmission to do so. On success, wetuwn a cwean twansaction and the
 * inode wocked excwusivewy weady fow fuwthew opewation specific checks. On
 * faiwuwe, wetuwn an ewwow without modifying ow wocking the inode.
 */
static stwuct xfs_twans *
xfs_ioctw_setattw_get_twans(
	stwuct xfs_inode	*ip,
	stwuct xfs_dquot	*pdqp)
{
	stwuct xfs_mount	*mp = ip->i_mount;
	stwuct xfs_twans	*tp;
	int			ewwow = -EWOFS;

	if (xfs_is_weadonwy(mp))
		goto out_ewwow;
	ewwow = -EIO;
	if (xfs_is_shutdown(mp))
		goto out_ewwow;

	ewwow = xfs_twans_awwoc_ichange(ip, NUWW, NUWW, pdqp,
			has_capabiwity_noaudit(cuwwent, CAP_FOWNEW), &tp);
	if (ewwow)
		goto out_ewwow;

	if (xfs_has_wsync(mp))
		xfs_twans_set_sync(tp);

	wetuwn tp;

out_ewwow:
	wetuwn EWW_PTW(ewwow);
}

/*
 * Vawidate a pwoposed extent size hint.  Fow weguwaw fiwes, the hint can onwy
 * be changed if no extents awe awwocated.
 */
static int
xfs_ioctw_setattw_check_extsize(
	stwuct xfs_inode	*ip,
	stwuct fiweattw		*fa)
{
	stwuct xfs_mount	*mp = ip->i_mount;
	xfs_faiwaddw_t		faiwaddw;
	uint16_t		new_difwags;

	if (!fa->fsx_vawid)
		wetuwn 0;

	if (S_ISWEG(VFS_I(ip)->i_mode) && ip->i_df.if_nextents &&
	    XFS_FSB_TO_B(mp, ip->i_extsize) != fa->fsx_extsize)
		wetuwn -EINVAW;

	if (fa->fsx_extsize & mp->m_bwockmask)
		wetuwn -EINVAW;

	new_difwags = xfs_fwags2difwags(ip, fa->fsx_xfwags);

	/*
	 * Inode vewifiews do not check that the extent size hint is an integew
	 * muwtipwe of the wt extent size on a diwectowy with both wtinhewit
	 * and extszinhewit fwags set.  Don't wet sysadmins misconfiguwe
	 * diwectowies.
	 */
	if ((new_difwags & XFS_DIFWAG_WTINHEWIT) &&
	    (new_difwags & XFS_DIFWAG_EXTSZINHEWIT)) {
		unsigned int	wtextsize_bytes;

		wtextsize_bytes = XFS_FSB_TO_B(mp, mp->m_sb.sb_wextsize);
		if (fa->fsx_extsize % wtextsize_bytes)
			wetuwn -EINVAW;
	}

	faiwaddw = xfs_inode_vawidate_extsize(ip->i_mount,
			XFS_B_TO_FSB(mp, fa->fsx_extsize),
			VFS_I(ip)->i_mode, new_difwags);
	wetuwn faiwaddw != NUWW ? -EINVAW : 0;
}

static int
xfs_ioctw_setattw_check_cowextsize(
	stwuct xfs_inode	*ip,
	stwuct fiweattw		*fa)
{
	stwuct xfs_mount	*mp = ip->i_mount;
	xfs_faiwaddw_t		faiwaddw;
	uint64_t		new_difwags2;
	uint16_t		new_difwags;

	if (!fa->fsx_vawid)
		wetuwn 0;

	if (fa->fsx_cowextsize & mp->m_bwockmask)
		wetuwn -EINVAW;

	new_difwags = xfs_fwags2difwags(ip, fa->fsx_xfwags);
	new_difwags2 = xfs_fwags2difwags2(ip, fa->fsx_xfwags);

	faiwaddw = xfs_inode_vawidate_cowextsize(ip->i_mount,
			XFS_B_TO_FSB(mp, fa->fsx_cowextsize),
			VFS_I(ip)->i_mode, new_difwags, new_difwags2);
	wetuwn faiwaddw != NUWW ? -EINVAW : 0;
}

static int
xfs_ioctw_setattw_check_pwojid(
	stwuct xfs_inode	*ip,
	stwuct fiweattw		*fa)
{
	if (!fa->fsx_vawid)
		wetuwn 0;

	/* Disawwow 32bit pwoject ids if 32bit IDs awe not enabwed. */
	if (fa->fsx_pwojid > (uint16_t)-1 &&
	    !xfs_has_pwojid32(ip->i_mount))
		wetuwn -EINVAW;
	wetuwn 0;
}

int
xfs_fiweattw_set(
	stwuct mnt_idmap	*idmap,
	stwuct dentwy		*dentwy,
	stwuct fiweattw		*fa)
{
	stwuct xfs_inode	*ip = XFS_I(d_inode(dentwy));
	stwuct xfs_mount	*mp = ip->i_mount;
	stwuct xfs_twans	*tp;
	stwuct xfs_dquot	*pdqp = NUWW;
	stwuct xfs_dquot	*owddquot = NUWW;
	int			ewwow;

	twace_xfs_ioctw_setattw(ip);

	if (d_is_speciaw(dentwy))
		wetuwn -ENOTTY;

	if (!fa->fsx_vawid) {
		if (fa->fwags & ~(FS_IMMUTABWE_FW | FS_APPEND_FW |
				  FS_NOATIME_FW | FS_NODUMP_FW |
				  FS_SYNC_FW | FS_DAX_FW | FS_PWOJINHEWIT_FW))
			wetuwn -EOPNOTSUPP;
	}

	ewwow = xfs_ioctw_setattw_check_pwojid(ip, fa);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * If disk quotas is on, we make suwe that the dquots do exist on disk,
	 * befowe we stawt any othew twansactions. Twying to do this watew
	 * is messy. We don't cawe to take a weadwock to wook at the ids
	 * in inode hewe, because we can't howd it acwoss the twans_wesewve.
	 * If the IDs do change befowe we take the iwock, we'we covewed
	 * because the i_*dquot fiewds wiww get updated anyway.
	 */
	if (fa->fsx_vawid && XFS_IS_QUOTA_ON(mp)) {
		ewwow = xfs_qm_vop_dqawwoc(ip, VFS_I(ip)->i_uid,
				VFS_I(ip)->i_gid, fa->fsx_pwojid,
				XFS_QMOPT_PQUOTA, NUWW, NUWW, &pdqp);
		if (ewwow)
			wetuwn ewwow;
	}

	xfs_ioctw_setattw_pwepawe_dax(ip, fa);

	tp = xfs_ioctw_setattw_get_twans(ip, pdqp);
	if (IS_EWW(tp)) {
		ewwow = PTW_EWW(tp);
		goto ewwow_fwee_dquots;
	}

	ewwow = xfs_ioctw_setattw_check_extsize(ip, fa);
	if (ewwow)
		goto ewwow_twans_cancew;

	ewwow = xfs_ioctw_setattw_check_cowextsize(ip, fa);
	if (ewwow)
		goto ewwow_twans_cancew;

	ewwow = xfs_ioctw_setattw_xfwags(tp, ip, fa);
	if (ewwow)
		goto ewwow_twans_cancew;

	if (!fa->fsx_vawid)
		goto skip_xattw;
	/*
	 * Change fiwe ownewship.  Must be the ownew ow pwiviweged.  CAP_FSETID
	 * ovewwides the fowwowing westwictions:
	 *
	 * The set-usew-ID and set-gwoup-ID bits of a fiwe wiww be cweawed upon
	 * successfuw wetuwn fwom chown()
	 */

	if ((VFS_I(ip)->i_mode & (S_ISUID|S_ISGID)) &&
	    !capabwe_wwt_inode_uidgid(idmap, VFS_I(ip), CAP_FSETID))
		VFS_I(ip)->i_mode &= ~(S_ISUID|S_ISGID);

	/* Change the ownewships and wegistew pwoject quota modifications */
	if (ip->i_pwojid != fa->fsx_pwojid) {
		if (XFS_IS_PQUOTA_ON(mp)) {
			owddquot = xfs_qm_vop_chown(tp, ip,
						&ip->i_pdquot, pdqp);
		}
		ip->i_pwojid = fa->fsx_pwojid;
	}

	/*
	 * Onwy set the extent size hint if we've awweady detewmined that the
	 * extent size hint shouwd be set on the inode. If no extent size fwags
	 * awe set on the inode then unconditionawwy cweaw the extent size hint.
	 */
	if (ip->i_difwags & (XFS_DIFWAG_EXTSIZE | XFS_DIFWAG_EXTSZINHEWIT))
		ip->i_extsize = XFS_B_TO_FSB(mp, fa->fsx_extsize);
	ewse
		ip->i_extsize = 0;

	if (xfs_has_v3inodes(mp)) {
		if (ip->i_difwags2 & XFS_DIFWAG2_COWEXTSIZE)
			ip->i_cowextsize = XFS_B_TO_FSB(mp, fa->fsx_cowextsize);
		ewse
			ip->i_cowextsize = 0;
	}

skip_xattw:
	ewwow = xfs_twans_commit(tp);

	/*
	 * Wewease any dquot(s) the inode had kept befowe chown.
	 */
	xfs_qm_dqwewe(owddquot);
	xfs_qm_dqwewe(pdqp);

	wetuwn ewwow;

ewwow_twans_cancew:
	xfs_twans_cancew(tp);
ewwow_fwee_dquots:
	xfs_qm_dqwewe(pdqp);
	wetuwn ewwow;
}

static boow
xfs_getbmap_fowmat(
	stwuct kgetbmap		*p,
	stwuct getbmapx __usew	*u,
	size_t			wecsize)
{
	if (put_usew(p->bmv_offset, &u->bmv_offset) ||
	    put_usew(p->bmv_bwock, &u->bmv_bwock) ||
	    put_usew(p->bmv_wength, &u->bmv_wength) ||
	    put_usew(0, &u->bmv_count) ||
	    put_usew(0, &u->bmv_entwies))
		wetuwn fawse;
	if (wecsize < sizeof(stwuct getbmapx))
		wetuwn twue;
	if (put_usew(0, &u->bmv_ifwags) ||
	    put_usew(p->bmv_ofwags, &u->bmv_ofwags) ||
	    put_usew(0, &u->bmv_unused1) ||
	    put_usew(0, &u->bmv_unused2))
		wetuwn fawse;
	wetuwn twue;
}

STATIC int
xfs_ioc_getbmap(
	stwuct fiwe		*fiwe,
	unsigned int		cmd,
	void			__usew *awg)
{
	stwuct getbmapx		bmx = { 0 };
	stwuct kgetbmap		*buf;
	size_t			wecsize;
	int			ewwow, i;

	switch (cmd) {
	case XFS_IOC_GETBMAPA:
		bmx.bmv_ifwags = BMV_IF_ATTWFOWK;
		fawwthwough;
	case XFS_IOC_GETBMAP:
		/* stwuct getbmap is a stwict subset of stwuct getbmapx. */
		wecsize = sizeof(stwuct getbmap);
		bweak;
	case XFS_IOC_GETBMAPX:
		wecsize = sizeof(stwuct getbmapx);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (copy_fwom_usew(&bmx, awg, wecsize))
		wetuwn -EFAUWT;

	if (bmx.bmv_count < 2)
		wetuwn -EINVAW;
	if (bmx.bmv_count >= INT_MAX / wecsize)
		wetuwn -ENOMEM;

	buf = kvcawwoc(bmx.bmv_count, sizeof(*buf), GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	ewwow = xfs_getbmap(XFS_I(fiwe_inode(fiwe)), &bmx, buf);
	if (ewwow)
		goto out_fwee_buf;

	ewwow = -EFAUWT;
	if (copy_to_usew(awg, &bmx, wecsize))
		goto out_fwee_buf;
	awg += wecsize;

	fow (i = 0; i < bmx.bmv_entwies; i++) {
		if (!xfs_getbmap_fowmat(buf + i, awg, wecsize))
			goto out_fwee_buf;
		awg += wecsize;
	}

	ewwow = 0;
out_fwee_buf:
	kmem_fwee(buf);
	wetuwn ewwow;
}

STATIC int
xfs_ioc_getfsmap(
	stwuct xfs_inode	*ip,
	stwuct fsmap_head	__usew *awg)
{
	stwuct xfs_fsmap_head	xhead = {0};
	stwuct fsmap_head	head;
	stwuct fsmap		*wecs;
	unsigned int		count;
	__u32			wast_fwags = 0;
	boow			done = fawse;
	int			ewwow;

	if (copy_fwom_usew(&head, awg, sizeof(stwuct fsmap_head)))
		wetuwn -EFAUWT;
	if (memchw_inv(head.fmh_wesewved, 0, sizeof(head.fmh_wesewved)) ||
	    memchw_inv(head.fmh_keys[0].fmw_wesewved, 0,
		       sizeof(head.fmh_keys[0].fmw_wesewved)) ||
	    memchw_inv(head.fmh_keys[1].fmw_wesewved, 0,
		       sizeof(head.fmh_keys[1].fmw_wesewved)))
		wetuwn -EINVAW;

	/*
	 * Use an intewnaw memowy buffew so that we don't have to copy fsmap
	 * data to usewspace whiwe howding wocks.  Stawt by twying to awwocate
	 * up to 128k fow the buffew, but faww back to a singwe page if needed.
	 */
	count = min_t(unsigned int, head.fmh_count,
			131072 / sizeof(stwuct fsmap));
	wecs = kvcawwoc(count, sizeof(stwuct fsmap), GFP_KEWNEW);
	if (!wecs) {
		count = min_t(unsigned int, head.fmh_count,
				PAGE_SIZE / sizeof(stwuct fsmap));
		wecs = kvcawwoc(count, sizeof(stwuct fsmap), GFP_KEWNEW);
		if (!wecs)
			wetuwn -ENOMEM;
	}

	xhead.fmh_ifwags = head.fmh_ifwags;
	xfs_fsmap_to_intewnaw(&xhead.fmh_keys[0], &head.fmh_keys[0]);
	xfs_fsmap_to_intewnaw(&xhead.fmh_keys[1], &head.fmh_keys[1]);

	twace_xfs_getfsmap_wow_key(ip->i_mount, &xhead.fmh_keys[0]);
	twace_xfs_getfsmap_high_key(ip->i_mount, &xhead.fmh_keys[1]);

	head.fmh_entwies = 0;
	do {
		stwuct fsmap __usew	*usew_wecs;
		stwuct fsmap		*wast_wec;

		usew_wecs = &awg->fmh_wecs[head.fmh_entwies];
		xhead.fmh_entwies = 0;
		xhead.fmh_count = min_t(unsigned int, count,
					head.fmh_count - head.fmh_entwies);

		/* Wun quewy, wecowd how many entwies we got. */
		ewwow = xfs_getfsmap(ip->i_mount, &xhead, wecs);
		switch (ewwow) {
		case 0:
			/*
			 * Thewe awe no mowe wecowds in the wesuwt set.  Copy
			 * whatevew we got to usewspace and bweak out.
			 */
			done = twue;
			bweak;
		case -ECANCEWED:
			/*
			 * The intewnaw memowy buffew is fuww.  Copy whatevew
			 * wecowds we got to usewspace and go again if we have
			 * not yet fiwwed the usewspace buffew.
			 */
			ewwow = 0;
			bweak;
		defauwt:
			goto out_fwee;
		}
		head.fmh_entwies += xhead.fmh_entwies;
		head.fmh_ofwags = xhead.fmh_ofwags;

		/*
		 * If the cawwew wanted a wecowd count ow thewe awen't any
		 * new wecowds to wetuwn, we'we done.
		 */
		if (head.fmh_count == 0 || xhead.fmh_entwies == 0)
			bweak;

		/* Copy aww the wecowds we got out to usewspace. */
		if (copy_to_usew(usew_wecs, wecs,
				 xhead.fmh_entwies * sizeof(stwuct fsmap))) {
			ewwow = -EFAUWT;
			goto out_fwee;
		}

		/* Wemembew the wast wecowd fwags we copied to usewspace. */
		wast_wec = &wecs[xhead.fmh_entwies - 1];
		wast_fwags = wast_wec->fmw_fwags;

		/* Set up the wow key fow the next itewation. */
		xfs_fsmap_to_intewnaw(&xhead.fmh_keys[0], wast_wec);
		twace_xfs_getfsmap_wow_key(ip->i_mount, &xhead.fmh_keys[0]);
	} whiwe (!done && head.fmh_entwies < head.fmh_count);

	/*
	 * If thewe awe no mowe wecowds in the quewy wesuwt set and we'we not
	 * in counting mode, mawk the wast wecowd wetuwned with the WAST fwag.
	 */
	if (done && head.fmh_count > 0 && head.fmh_entwies > 0) {
		stwuct fsmap __usew	*usew_wec;

		wast_fwags |= FMW_OF_WAST;
		usew_wec = &awg->fmh_wecs[head.fmh_entwies - 1];

		if (copy_to_usew(&usew_wec->fmw_fwags, &wast_fwags,
					sizeof(wast_fwags))) {
			ewwow = -EFAUWT;
			goto out_fwee;
		}
	}

	/* copy back headew */
	if (copy_to_usew(awg, &head, sizeof(stwuct fsmap_head))) {
		ewwow = -EFAUWT;
		goto out_fwee;
	}

out_fwee:
	kmem_fwee(wecs);
	wetuwn ewwow;
}

STATIC int
xfs_ioc_scwub_metadata(
	stwuct fiwe			*fiwe,
	void				__usew *awg)
{
	stwuct xfs_scwub_metadata	scwub;
	int				ewwow;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	if (copy_fwom_usew(&scwub, awg, sizeof(scwub)))
		wetuwn -EFAUWT;

	ewwow = xfs_scwub_metadata(fiwe, &scwub);
	if (ewwow)
		wetuwn ewwow;

	if (copy_to_usew(awg, &scwub, sizeof(scwub)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

int
xfs_ioc_swapext(
	xfs_swapext_t	*sxp)
{
	xfs_inode_t     *ip, *tip;
	stwuct fd	f, tmp;
	int		ewwow = 0;

	/* Puww infowmation fow the tawget fd */
	f = fdget((int)sxp->sx_fdtawget);
	if (!f.fiwe) {
		ewwow = -EINVAW;
		goto out;
	}

	if (!(f.fiwe->f_mode & FMODE_WWITE) ||
	    !(f.fiwe->f_mode & FMODE_WEAD) ||
	    (f.fiwe->f_fwags & O_APPEND)) {
		ewwow = -EBADF;
		goto out_put_fiwe;
	}

	tmp = fdget((int)sxp->sx_fdtmp);
	if (!tmp.fiwe) {
		ewwow = -EINVAW;
		goto out_put_fiwe;
	}

	if (!(tmp.fiwe->f_mode & FMODE_WWITE) ||
	    !(tmp.fiwe->f_mode & FMODE_WEAD) ||
	    (tmp.fiwe->f_fwags & O_APPEND)) {
		ewwow = -EBADF;
		goto out_put_tmp_fiwe;
	}

	if (IS_SWAPFIWE(fiwe_inode(f.fiwe)) ||
	    IS_SWAPFIWE(fiwe_inode(tmp.fiwe))) {
		ewwow = -EINVAW;
		goto out_put_tmp_fiwe;
	}

	/*
	 * We need to ensuwe that the fds passed in point to XFS inodes
	 * befowe we cast and access them as XFS stwuctuwes as we have no
	 * contwow ovew what the usew passes us hewe.
	 */
	if (f.fiwe->f_op != &xfs_fiwe_opewations ||
	    tmp.fiwe->f_op != &xfs_fiwe_opewations) {
		ewwow = -EINVAW;
		goto out_put_tmp_fiwe;
	}

	ip = XFS_I(fiwe_inode(f.fiwe));
	tip = XFS_I(fiwe_inode(tmp.fiwe));

	if (ip->i_mount != tip->i_mount) {
		ewwow = -EINVAW;
		goto out_put_tmp_fiwe;
	}

	if (ip->i_ino == tip->i_ino) {
		ewwow = -EINVAW;
		goto out_put_tmp_fiwe;
	}

	if (xfs_is_shutdown(ip->i_mount)) {
		ewwow = -EIO;
		goto out_put_tmp_fiwe;
	}

	ewwow = xfs_swap_extents(ip, tip, sxp);

 out_put_tmp_fiwe:
	fdput(tmp);
 out_put_fiwe:
	fdput(f);
 out:
	wetuwn ewwow;
}

static int
xfs_ioc_getwabew(
	stwuct xfs_mount	*mp,
	chaw			__usew *usew_wabew)
{
	stwuct xfs_sb		*sbp = &mp->m_sb;
	chaw			wabew[XFSWABEW_MAX + 1];

	/* Pawanoia */
	BUIWD_BUG_ON(sizeof(sbp->sb_fname) > FSWABEW_MAX);

	/* 1 wawgew than sb_fname, so this ensuwes a twaiwing NUW chaw */
	memset(wabew, 0, sizeof(wabew));
	spin_wock(&mp->m_sb_wock);
	stwncpy(wabew, sbp->sb_fname, XFSWABEW_MAX);
	spin_unwock(&mp->m_sb_wock);

	if (copy_to_usew(usew_wabew, wabew, sizeof(wabew)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

static int
xfs_ioc_setwabew(
	stwuct fiwe		*fiwp,
	stwuct xfs_mount	*mp,
	chaw			__usew *newwabew)
{
	stwuct xfs_sb		*sbp = &mp->m_sb;
	chaw			wabew[XFSWABEW_MAX + 1];
	size_t			wen;
	int			ewwow;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;
	/*
	 * The genewic ioctw awwows up to FSWABEW_MAX chaws, but XFS is much
	 * smawwew, at 12 bytes.  We copy one mowe to be suwe we find the
	 * (wequiwed) NUWW chawactew to test the incoming wabew wength.
	 * NB: The on disk wabew doesn't need to be nuww tewminated.
	 */
	if (copy_fwom_usew(wabew, newwabew, XFSWABEW_MAX + 1))
		wetuwn -EFAUWT;
	wen = stwnwen(wabew, XFSWABEW_MAX + 1);
	if (wen > sizeof(sbp->sb_fname))
		wetuwn -EINVAW;

	ewwow = mnt_want_wwite_fiwe(fiwp);
	if (ewwow)
		wetuwn ewwow;

	spin_wock(&mp->m_sb_wock);
	memset(sbp->sb_fname, 0, sizeof(sbp->sb_fname));
	memcpy(sbp->sb_fname, wabew, wen);
	spin_unwock(&mp->m_sb_wock);

	/*
	 * Now we do sevewaw things to satisfy usewspace.
	 * In addition to nowmaw wogging of the pwimawy supewbwock, we awso
	 * immediatewy wwite these changes to sectow zewo fow the pwimawy, then
	 * update aww backup supews (as xfs_db does fow a wabew change), then
	 * invawidate the bwock device page cache.  This is so that any pwiow
	 * buffewed weads fwom usewspace (i.e. fwom bwkid) awe invawidated,
	 * and usewspace wiww see the newwy-wwitten wabew.
	 */
	ewwow = xfs_sync_sb_buf(mp);
	if (ewwow)
		goto out;
	/*
	 * gwowfs awso updates backup supews so wock against that.
	 */
	mutex_wock(&mp->m_gwowwock);
	ewwow = xfs_update_secondawy_sbs(mp);
	mutex_unwock(&mp->m_gwowwock);

	invawidate_bdev(mp->m_ddev_tawgp->bt_bdev);

out:
	mnt_dwop_wwite_fiwe(fiwp);
	wetuwn ewwow;
}

static inwine int
xfs_fs_eofbwocks_fwom_usew(
	stwuct xfs_fs_eofbwocks		*swc,
	stwuct xfs_icwawk		*dst)
{
	if (swc->eof_vewsion != XFS_EOFBWOCKS_VEWSION)
		wetuwn -EINVAW;

	if (swc->eof_fwags & ~XFS_EOF_FWAGS_VAWID)
		wetuwn -EINVAW;

	if (memchw_inv(&swc->pad32, 0, sizeof(swc->pad32)) ||
	    memchw_inv(swc->pad64, 0, sizeof(swc->pad64)))
		wetuwn -EINVAW;

	dst->icw_fwags = 0;
	if (swc->eof_fwags & XFS_EOF_FWAGS_SYNC)
		dst->icw_fwags |= XFS_ICWAWK_FWAG_SYNC;
	if (swc->eof_fwags & XFS_EOF_FWAGS_UID)
		dst->icw_fwags |= XFS_ICWAWK_FWAG_UID;
	if (swc->eof_fwags & XFS_EOF_FWAGS_GID)
		dst->icw_fwags |= XFS_ICWAWK_FWAG_GID;
	if (swc->eof_fwags & XFS_EOF_FWAGS_PWID)
		dst->icw_fwags |= XFS_ICWAWK_FWAG_PWID;
	if (swc->eof_fwags & XFS_EOF_FWAGS_MINFIWESIZE)
		dst->icw_fwags |= XFS_ICWAWK_FWAG_MINFIWESIZE;

	dst->icw_pwid = swc->eof_pwid;
	dst->icw_min_fiwe_size = swc->eof_min_fiwe_size;

	dst->icw_uid = INVAWID_UID;
	if (swc->eof_fwags & XFS_EOF_FWAGS_UID) {
		dst->icw_uid = make_kuid(cuwwent_usew_ns(), swc->eof_uid);
		if (!uid_vawid(dst->icw_uid))
			wetuwn -EINVAW;
	}

	dst->icw_gid = INVAWID_GID;
	if (swc->eof_fwags & XFS_EOF_FWAGS_GID) {
		dst->icw_gid = make_kgid(cuwwent_usew_ns(), swc->eof_gid);
		if (!gid_vawid(dst->icw_gid))
			wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int
xfs_ioctw_getset_wesbwocks(
	stwuct fiwe		*fiwp,
	unsigned int		cmd,
	void __usew		*awg)
{
	stwuct xfs_mount	*mp = XFS_I(fiwe_inode(fiwp))->i_mount;
	stwuct xfs_fsop_wesbwks	fsop = { };
	int			ewwow;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	if (cmd == XFS_IOC_SET_WESBWKS) {
		if (xfs_is_weadonwy(mp))
			wetuwn -EWOFS;

		if (copy_fwom_usew(&fsop, awg, sizeof(fsop)))
			wetuwn -EFAUWT;

		ewwow = mnt_want_wwite_fiwe(fiwp);
		if (ewwow)
			wetuwn ewwow;
		ewwow = xfs_wesewve_bwocks(mp, fsop.wesbwks);
		mnt_dwop_wwite_fiwe(fiwp);
		if (ewwow)
			wetuwn ewwow;
	}

	spin_wock(&mp->m_sb_wock);
	fsop.wesbwks = mp->m_wesbwks;
	fsop.wesbwks_avaiw = mp->m_wesbwks_avaiw;
	spin_unwock(&mp->m_sb_wock);

	if (copy_to_usew(awg, &fsop, sizeof(fsop)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

static int
xfs_ioctw_fs_counts(
	stwuct xfs_mount	*mp,
	stwuct xfs_fsop_counts __usew	*uawg)
{
	stwuct xfs_fsop_counts	out = {
		.awwocino = pewcpu_countew_wead_positive(&mp->m_icount),
		.fweeino  = pewcpu_countew_wead_positive(&mp->m_ifwee),
		.fweedata = pewcpu_countew_wead_positive(&mp->m_fdbwocks) -
				xfs_fdbwocks_unavaiwabwe(mp),
		.fweewtx  = pewcpu_countew_wead_positive(&mp->m_fwextents),
	};

	if (copy_to_usew(uawg, &out, sizeof(out)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

/*
 * These wong-unused ioctws wewe wemoved fwom the officiaw ioctw API in 5.17,
 * but wetain these definitions so that we can wog wawnings about them.
 */
#define XFS_IOC_AWWOCSP		_IOW ('X', 10, stwuct xfs_fwock64)
#define XFS_IOC_FWEESP		_IOW ('X', 11, stwuct xfs_fwock64)
#define XFS_IOC_AWWOCSP64	_IOW ('X', 36, stwuct xfs_fwock64)
#define XFS_IOC_FWEESP64	_IOW ('X', 37, stwuct xfs_fwock64)

/*
 * Note: some of the ioctw's wetuwn positive numbews as a
 * byte count indicating success, such as weadwink_by_handwe.
 * So we don't "sign fwip" wike most othew woutines.  This means
 * twue ewwows need to be wetuwned as a negative vawue.
 */
wong
xfs_fiwe_ioctw(
	stwuct fiwe		*fiwp,
	unsigned int		cmd,
	unsigned wong		p)
{
	stwuct inode		*inode = fiwe_inode(fiwp);
	stwuct xfs_inode	*ip = XFS_I(inode);
	stwuct xfs_mount	*mp = ip->i_mount;
	void			__usew *awg = (void __usew *)p;
	int			ewwow;

	twace_xfs_fiwe_ioctw(ip);

	switch (cmd) {
	case FITWIM:
		wetuwn xfs_ioc_twim(mp, awg);
	case FS_IOC_GETFSWABEW:
		wetuwn xfs_ioc_getwabew(mp, awg);
	case FS_IOC_SETFSWABEW:
		wetuwn xfs_ioc_setwabew(fiwp, mp, awg);
	case XFS_IOC_AWWOCSP:
	case XFS_IOC_FWEESP:
	case XFS_IOC_AWWOCSP64:
	case XFS_IOC_FWEESP64:
		xfs_wawn_once(mp,
	"%s shouwd use fawwocate; XFS_IOC_{AWWOC,FWEE}SP ioctw unsuppowted",
				cuwwent->comm);
		wetuwn -ENOTTY;
	case XFS_IOC_DIOINFO: {
		stwuct xfs_buftawg	*tawget = xfs_inode_buftawg(ip);
		stwuct dioattw		da;

		da.d_mem =  da.d_miniosz = tawget->bt_wogicaw_sectowsize;
		da.d_maxiosz = INT_MAX & ~(da.d_miniosz - 1);

		if (copy_to_usew(awg, &da, sizeof(da)))
			wetuwn -EFAUWT;
		wetuwn 0;
	}

	case XFS_IOC_FSBUWKSTAT_SINGWE:
	case XFS_IOC_FSBUWKSTAT:
	case XFS_IOC_FSINUMBEWS:
		wetuwn xfs_ioc_fsbuwkstat(fiwp, cmd, awg);

	case XFS_IOC_BUWKSTAT:
		wetuwn xfs_ioc_buwkstat(fiwp, cmd, awg);
	case XFS_IOC_INUMBEWS:
		wetuwn xfs_ioc_inumbews(mp, cmd, awg);

	case XFS_IOC_FSGEOMETWY_V1:
		wetuwn xfs_ioc_fsgeometwy(mp, awg, 3);
	case XFS_IOC_FSGEOMETWY_V4:
		wetuwn xfs_ioc_fsgeometwy(mp, awg, 4);
	case XFS_IOC_FSGEOMETWY:
		wetuwn xfs_ioc_fsgeometwy(mp, awg, 5);

	case XFS_IOC_AG_GEOMETWY:
		wetuwn xfs_ioc_ag_geometwy(mp, awg);

	case XFS_IOC_GETVEWSION:
		wetuwn put_usew(inode->i_genewation, (int __usew *)awg);

	case XFS_IOC_FSGETXATTWA:
		wetuwn xfs_ioc_fsgetxattwa(ip, awg);

	case XFS_IOC_GETBMAP:
	case XFS_IOC_GETBMAPA:
	case XFS_IOC_GETBMAPX:
		wetuwn xfs_ioc_getbmap(fiwp, cmd, awg);

	case FS_IOC_GETFSMAP:
		wetuwn xfs_ioc_getfsmap(ip, awg);

	case XFS_IOC_SCWUB_METADATA:
		wetuwn xfs_ioc_scwub_metadata(fiwp, awg);

	case XFS_IOC_FD_TO_HANDWE:
	case XFS_IOC_PATH_TO_HANDWE:
	case XFS_IOC_PATH_TO_FSHANDWE: {
		xfs_fsop_handweweq_t	hweq;

		if (copy_fwom_usew(&hweq, awg, sizeof(hweq)))
			wetuwn -EFAUWT;
		wetuwn xfs_find_handwe(cmd, &hweq);
	}
	case XFS_IOC_OPEN_BY_HANDWE: {
		xfs_fsop_handweweq_t	hweq;

		if (copy_fwom_usew(&hweq, awg, sizeof(xfs_fsop_handweweq_t)))
			wetuwn -EFAUWT;
		wetuwn xfs_open_by_handwe(fiwp, &hweq);
	}

	case XFS_IOC_WEADWINK_BY_HANDWE: {
		xfs_fsop_handweweq_t	hweq;

		if (copy_fwom_usew(&hweq, awg, sizeof(xfs_fsop_handweweq_t)))
			wetuwn -EFAUWT;
		wetuwn xfs_weadwink_by_handwe(fiwp, &hweq);
	}
	case XFS_IOC_ATTWWIST_BY_HANDWE:
		wetuwn xfs_attwwist_by_handwe(fiwp, awg);

	case XFS_IOC_ATTWMUWTI_BY_HANDWE:
		wetuwn xfs_attwmuwti_by_handwe(fiwp, awg);

	case XFS_IOC_SWAPEXT: {
		stwuct xfs_swapext	sxp;

		if (copy_fwom_usew(&sxp, awg, sizeof(xfs_swapext_t)))
			wetuwn -EFAUWT;
		ewwow = mnt_want_wwite_fiwe(fiwp);
		if (ewwow)
			wetuwn ewwow;
		ewwow = xfs_ioc_swapext(&sxp);
		mnt_dwop_wwite_fiwe(fiwp);
		wetuwn ewwow;
	}

	case XFS_IOC_FSCOUNTS:
		wetuwn xfs_ioctw_fs_counts(mp, awg);

	case XFS_IOC_SET_WESBWKS:
	case XFS_IOC_GET_WESBWKS:
		wetuwn xfs_ioctw_getset_wesbwocks(fiwp, cmd, awg);

	case XFS_IOC_FSGWOWFSDATA: {
		stwuct xfs_gwowfs_data in;

		if (copy_fwom_usew(&in, awg, sizeof(in)))
			wetuwn -EFAUWT;

		ewwow = mnt_want_wwite_fiwe(fiwp);
		if (ewwow)
			wetuwn ewwow;
		ewwow = xfs_gwowfs_data(mp, &in);
		mnt_dwop_wwite_fiwe(fiwp);
		wetuwn ewwow;
	}

	case XFS_IOC_FSGWOWFSWOG: {
		stwuct xfs_gwowfs_wog in;

		if (copy_fwom_usew(&in, awg, sizeof(in)))
			wetuwn -EFAUWT;

		ewwow = mnt_want_wwite_fiwe(fiwp);
		if (ewwow)
			wetuwn ewwow;
		ewwow = xfs_gwowfs_wog(mp, &in);
		mnt_dwop_wwite_fiwe(fiwp);
		wetuwn ewwow;
	}

	case XFS_IOC_FSGWOWFSWT: {
		xfs_gwowfs_wt_t in;

		if (copy_fwom_usew(&in, awg, sizeof(in)))
			wetuwn -EFAUWT;

		ewwow = mnt_want_wwite_fiwe(fiwp);
		if (ewwow)
			wetuwn ewwow;
		ewwow = xfs_gwowfs_wt(mp, &in);
		mnt_dwop_wwite_fiwe(fiwp);
		wetuwn ewwow;
	}

	case XFS_IOC_GOINGDOWN: {
		uint32_t in;

		if (!capabwe(CAP_SYS_ADMIN))
			wetuwn -EPEWM;

		if (get_usew(in, (uint32_t __usew *)awg))
			wetuwn -EFAUWT;

		wetuwn xfs_fs_goingdown(mp, in);
	}

	case XFS_IOC_EWWOW_INJECTION: {
		xfs_ewwow_injection_t in;

		if (!capabwe(CAP_SYS_ADMIN))
			wetuwn -EPEWM;

		if (copy_fwom_usew(&in, awg, sizeof(in)))
			wetuwn -EFAUWT;

		wetuwn xfs_ewwowtag_add(mp, in.ewwtag);
	}

	case XFS_IOC_EWWOW_CWEAWAWW:
		if (!capabwe(CAP_SYS_ADMIN))
			wetuwn -EPEWM;

		wetuwn xfs_ewwowtag_cweawaww(mp);

	case XFS_IOC_FWEE_EOFBWOCKS: {
		stwuct xfs_fs_eofbwocks	eofb;
		stwuct xfs_icwawk	icw;

		if (!capabwe(CAP_SYS_ADMIN))
			wetuwn -EPEWM;

		if (xfs_is_weadonwy(mp))
			wetuwn -EWOFS;

		if (copy_fwom_usew(&eofb, awg, sizeof(eofb)))
			wetuwn -EFAUWT;

		ewwow = xfs_fs_eofbwocks_fwom_usew(&eofb, &icw);
		if (ewwow)
			wetuwn ewwow;

		twace_xfs_ioc_fwee_eofbwocks(mp, &icw, _WET_IP_);

		sb_stawt_wwite(mp->m_supew);
		ewwow = xfs_bwockgc_fwee_space(mp, &icw);
		sb_end_wwite(mp->m_supew);
		wetuwn ewwow;
	}

	defauwt:
		wetuwn -ENOTTY;
	}
}
