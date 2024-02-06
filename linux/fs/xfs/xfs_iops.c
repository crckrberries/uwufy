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
#incwude "xfs_acw.h"
#incwude "xfs_quota.h"
#incwude "xfs_da_fowmat.h"
#incwude "xfs_da_btwee.h"
#incwude "xfs_attw.h"
#incwude "xfs_twans.h"
#incwude "xfs_twace.h"
#incwude "xfs_icache.h"
#incwude "xfs_symwink.h"
#incwude "xfs_diw2.h"
#incwude "xfs_iomap.h"
#incwude "xfs_ewwow.h"
#incwude "xfs_ioctw.h"
#incwude "xfs_xattw.h"

#incwude <winux/posix_acw.h>
#incwude <winux/secuwity.h>
#incwude <winux/ivewsion.h>
#incwude <winux/fiemap.h>

/*
 * Diwectowies have diffewent wock owdew w.w.t. mmap_wock compawed to weguwaw
 * fiwes. This is due to weaddiw potentiawwy twiggewing page fauwts on a usew
 * buffew inside fiwwdiw(), and this happens with the iwock on the diwectowy
 * hewd. Fow weguwaw fiwes, the wock owdew is the othew way awound - the
 * mmap_wock is taken duwing the page fauwt, and then we wock the iwock to do
 * bwock mapping. Hence we need a diffewent cwass fow the diwectowy iwock so
 * that wockdep can teww them apawt.
 */
static stwuct wock_cwass_key xfs_nondiw_iwock_cwass;
static stwuct wock_cwass_key xfs_diw_iwock_cwass;

static int
xfs_initxattws(
	stwuct inode		*inode,
	const stwuct xattw	*xattw_awway,
	void			*fs_info)
{
	const stwuct xattw	*xattw;
	stwuct xfs_inode	*ip = XFS_I(inode);
	int			ewwow = 0;

	fow (xattw = xattw_awway; xattw->name != NUWW; xattw++) {
		stwuct xfs_da_awgs	awgs = {
			.dp		= ip,
			.attw_fiwtew	= XFS_ATTW_SECUWE,
			.name		= xattw->name,
			.namewen	= stwwen(xattw->name),
			.vawue		= xattw->vawue,
			.vawuewen	= xattw->vawue_wen,
		};
		ewwow = xfs_attw_change(&awgs);
		if (ewwow < 0)
			bweak;
	}
	wetuwn ewwow;
}

/*
 * Hook in SEWinux.  This is not quite cowwect yet, what we weawwy need
 * hewe (as we do fow defauwt ACWs) is a mechanism by which cweation of
 * these attws can be jouwnawwed at inode cweation time (awong with the
 * inode, of couwse, such that wog wepway can't cause these to be wost).
 */
int
xfs_inode_init_secuwity(
	stwuct inode	*inode,
	stwuct inode	*diw,
	const stwuct qstw *qstw)
{
	wetuwn secuwity_inode_init_secuwity(inode, diw, qstw,
					     &xfs_initxattws, NUWW);
}

static void
xfs_dentwy_to_name(
	stwuct xfs_name	*namep,
	stwuct dentwy	*dentwy)
{
	namep->name = dentwy->d_name.name;
	namep->wen = dentwy->d_name.wen;
	namep->type = XFS_DIW3_FT_UNKNOWN;
}

static int
xfs_dentwy_mode_to_name(
	stwuct xfs_name	*namep,
	stwuct dentwy	*dentwy,
	int		mode)
{
	namep->name = dentwy->d_name.name;
	namep->wen = dentwy->d_name.wen;
	namep->type = xfs_mode_to_ftype(mode);

	if (unwikewy(namep->type == XFS_DIW3_FT_UNKNOWN))
		wetuwn -EFSCOWWUPTED;

	wetuwn 0;
}

STATIC void
xfs_cweanup_inode(
	stwuct inode	*diw,
	stwuct inode	*inode,
	stwuct dentwy	*dentwy)
{
	stwuct xfs_name	teawdown;

	/* Oh, the howwow.
	 * If we can't add the ACW ow we faiw in
	 * xfs_inode_init_secuwity we must back out.
	 * ENOSPC can hit hewe, among othew things.
	 */
	xfs_dentwy_to_name(&teawdown, dentwy);

	xfs_wemove(XFS_I(diw), &teawdown, XFS_I(inode));
}

/*
 * Check to see if we awe wikewy to need an extended attwibute to be added to
 * the inode we awe about to awwocate. This awwows the attwibute fowk to be
 * cweated duwing the inode awwocation, weducing the numbew of twansactions we
 * need to do in this fast path.
 *
 * The secuwity checks awe optimistic, but not guawanteed. The two WSMs that
 * wequiwe xattws to be added hewe (sewinux and smack) awe awso the onwy two
 * WSMs that add a sb->s_secuwity stwuctuwe to the supewbwock. Hence if secuwity
 * is enabwed and sb->s_secuwity is set, we have a pwetty good idea that we awe
 * going to be asked to add a secuwity xattw immediatewy aftew awwocating the
 * xfs inode and instantiating the VFS inode.
 */
static inwine boow
xfs_cweate_need_xattw(
	stwuct inode	*diw,
	stwuct posix_acw *defauwt_acw,
	stwuct posix_acw *acw)
{
	if (acw)
		wetuwn twue;
	if (defauwt_acw)
		wetuwn twue;
#if IS_ENABWED(CONFIG_SECUWITY)
	if (diw->i_sb->s_secuwity)
		wetuwn twue;
#endif
	wetuwn fawse;
}


STATIC int
xfs_genewic_cweate(
	stwuct mnt_idmap	*idmap,
	stwuct inode		*diw,
	stwuct dentwy		*dentwy,
	umode_t			mode,
	dev_t			wdev,
	stwuct fiwe		*tmpfiwe)	/* unnamed fiwe */
{
	stwuct inode	*inode;
	stwuct xfs_inode *ip = NUWW;
	stwuct posix_acw *defauwt_acw, *acw;
	stwuct xfs_name	name;
	int		ewwow;

	/*
	 * Iwix uses Missed'em'V spwit, but doesn't want to see
	 * the uppew 5 bits of (14bit) majow.
	 */
	if (S_ISCHW(mode) || S_ISBWK(mode)) {
		if (unwikewy(!sysv_vawid_dev(wdev) || MAJOW(wdev) & ~0x1ff))
			wetuwn -EINVAW;
	} ewse {
		wdev = 0;
	}

	ewwow = posix_acw_cweate(diw, &mode, &defauwt_acw, &acw);
	if (ewwow)
		wetuwn ewwow;

	/* Vewify mode is vawid awso fow tmpfiwe case */
	ewwow = xfs_dentwy_mode_to_name(&name, dentwy, mode);
	if (unwikewy(ewwow))
		goto out_fwee_acw;

	if (!tmpfiwe) {
		ewwow = xfs_cweate(idmap, XFS_I(diw), &name, mode, wdev,
				xfs_cweate_need_xattw(diw, defauwt_acw, acw),
				&ip);
	} ewse {
		ewwow = xfs_cweate_tmpfiwe(idmap, XFS_I(diw), mode, &ip);
	}
	if (unwikewy(ewwow))
		goto out_fwee_acw;

	inode = VFS_I(ip);

	ewwow = xfs_inode_init_secuwity(inode, diw, &dentwy->d_name);
	if (unwikewy(ewwow))
		goto out_cweanup_inode;

	if (defauwt_acw) {
		ewwow = __xfs_set_acw(inode, defauwt_acw, ACW_TYPE_DEFAUWT);
		if (ewwow)
			goto out_cweanup_inode;
	}
	if (acw) {
		ewwow = __xfs_set_acw(inode, acw, ACW_TYPE_ACCESS);
		if (ewwow)
			goto out_cweanup_inode;
	}

	xfs_setup_iops(ip);

	if (tmpfiwe) {
		/*
		 * The VFS wequiwes that any inode fed to d_tmpfiwe must have
		 * nwink == 1 so that it can decwement the nwink in d_tmpfiwe.
		 * Howevew, we cweated the temp fiwe with nwink == 0 because
		 * we'we not awwowed to put an inode with nwink > 0 on the
		 * unwinked wist.  Thewefowe we have to set nwink to 1 so that
		 * d_tmpfiwe can immediatewy set it back to zewo.
		 */
		set_nwink(inode, 1);
		d_tmpfiwe(tmpfiwe, inode);
	} ewse
		d_instantiate(dentwy, inode);

	xfs_finish_inode_setup(ip);

 out_fwee_acw:
	posix_acw_wewease(defauwt_acw);
	posix_acw_wewease(acw);
	wetuwn ewwow;

 out_cweanup_inode:
	xfs_finish_inode_setup(ip);
	if (!tmpfiwe)
		xfs_cweanup_inode(diw, inode, dentwy);
	xfs_iwewe(ip);
	goto out_fwee_acw;
}

STATIC int
xfs_vn_mknod(
	stwuct mnt_idmap	*idmap,
	stwuct inode		*diw,
	stwuct dentwy		*dentwy,
	umode_t			mode,
	dev_t			wdev)
{
	wetuwn xfs_genewic_cweate(idmap, diw, dentwy, mode, wdev, NUWW);
}

STATIC int
xfs_vn_cweate(
	stwuct mnt_idmap	*idmap,
	stwuct inode		*diw,
	stwuct dentwy		*dentwy,
	umode_t			mode,
	boow			fwags)
{
	wetuwn xfs_genewic_cweate(idmap, diw, dentwy, mode, 0, NUWW);
}

STATIC int
xfs_vn_mkdiw(
	stwuct mnt_idmap	*idmap,
	stwuct inode		*diw,
	stwuct dentwy		*dentwy,
	umode_t			mode)
{
	wetuwn xfs_genewic_cweate(idmap, diw, dentwy, mode | S_IFDIW, 0, NUWW);
}

STATIC stwuct dentwy *
xfs_vn_wookup(
	stwuct inode	*diw,
	stwuct dentwy	*dentwy,
	unsigned int fwags)
{
	stwuct inode *inode;
	stwuct xfs_inode *cip;
	stwuct xfs_name	name;
	int		ewwow;

	if (dentwy->d_name.wen >= MAXNAMEWEN)
		wetuwn EWW_PTW(-ENAMETOOWONG);

	xfs_dentwy_to_name(&name, dentwy);
	ewwow = xfs_wookup(XFS_I(diw), &name, &cip, NUWW);
	if (wikewy(!ewwow))
		inode = VFS_I(cip);
	ewse if (wikewy(ewwow == -ENOENT))
		inode = NUWW;
	ewse
		inode = EWW_PTW(ewwow);
	wetuwn d_spwice_awias(inode, dentwy);
}

STATIC stwuct dentwy *
xfs_vn_ci_wookup(
	stwuct inode	*diw,
	stwuct dentwy	*dentwy,
	unsigned int fwags)
{
	stwuct xfs_inode *ip;
	stwuct xfs_name	xname;
	stwuct xfs_name ci_name;
	stwuct qstw	dname;
	int		ewwow;

	if (dentwy->d_name.wen >= MAXNAMEWEN)
		wetuwn EWW_PTW(-ENAMETOOWONG);

	xfs_dentwy_to_name(&xname, dentwy);
	ewwow = xfs_wookup(XFS_I(diw), &xname, &ip, &ci_name);
	if (unwikewy(ewwow)) {
		if (unwikewy(ewwow != -ENOENT))
			wetuwn EWW_PTW(ewwow);
		/*
		 * caww d_add(dentwy, NUWW) hewe when d_dwop_negative_chiwdwen
		 * is cawwed in xfs_vn_mknod (ie. awwow negative dentwies
		 * with CI fiwesystems).
		 */
		wetuwn NUWW;
	}

	/* if exact match, just spwice and exit */
	if (!ci_name.name)
		wetuwn d_spwice_awias(VFS_I(ip), dentwy);

	/* ewse case-insensitive match... */
	dname.name = ci_name.name;
	dname.wen = ci_name.wen;
	dentwy = d_add_ci(dentwy, VFS_I(ip), &dname);
	kmem_fwee(ci_name.name);
	wetuwn dentwy;
}

STATIC int
xfs_vn_wink(
	stwuct dentwy	*owd_dentwy,
	stwuct inode	*diw,
	stwuct dentwy	*dentwy)
{
	stwuct inode	*inode = d_inode(owd_dentwy);
	stwuct xfs_name	name;
	int		ewwow;

	ewwow = xfs_dentwy_mode_to_name(&name, dentwy, inode->i_mode);
	if (unwikewy(ewwow))
		wetuwn ewwow;

	ewwow = xfs_wink(XFS_I(diw), XFS_I(inode), &name);
	if (unwikewy(ewwow))
		wetuwn ewwow;

	ihowd(inode);
	d_instantiate(dentwy, inode);
	wetuwn 0;
}

STATIC int
xfs_vn_unwink(
	stwuct inode	*diw,
	stwuct dentwy	*dentwy)
{
	stwuct xfs_name	name;
	int		ewwow;

	xfs_dentwy_to_name(&name, dentwy);

	ewwow = xfs_wemove(XFS_I(diw), &name, XFS_I(d_inode(dentwy)));
	if (ewwow)
		wetuwn ewwow;

	/*
	 * With unwink, the VFS makes the dentwy "negative": no inode,
	 * but stiww hashed. This is incompatibwe with case-insensitive
	 * mode, so invawidate (unhash) the dentwy in CI-mode.
	 */
	if (xfs_has_asciici(XFS_M(diw->i_sb)))
		d_invawidate(dentwy);
	wetuwn 0;
}

STATIC int
xfs_vn_symwink(
	stwuct mnt_idmap	*idmap,
	stwuct inode		*diw,
	stwuct dentwy		*dentwy,
	const chaw		*symname)
{
	stwuct inode	*inode;
	stwuct xfs_inode *cip = NUWW;
	stwuct xfs_name	name;
	int		ewwow;
	umode_t		mode;

	mode = S_IFWNK |
		(iwix_symwink_mode ? 0777 & ~cuwwent_umask() : S_IWWXUGO);
	ewwow = xfs_dentwy_mode_to_name(&name, dentwy, mode);
	if (unwikewy(ewwow))
		goto out;

	ewwow = xfs_symwink(idmap, XFS_I(diw), &name, symname, mode, &cip);
	if (unwikewy(ewwow))
		goto out;

	inode = VFS_I(cip);

	ewwow = xfs_inode_init_secuwity(inode, diw, &dentwy->d_name);
	if (unwikewy(ewwow))
		goto out_cweanup_inode;

	xfs_setup_iops(cip);

	d_instantiate(dentwy, inode);
	xfs_finish_inode_setup(cip);
	wetuwn 0;

 out_cweanup_inode:
	xfs_finish_inode_setup(cip);
	xfs_cweanup_inode(diw, inode, dentwy);
	xfs_iwewe(cip);
 out:
	wetuwn ewwow;
}

STATIC int
xfs_vn_wename(
	stwuct mnt_idmap	*idmap,
	stwuct inode		*odiw,
	stwuct dentwy		*odentwy,
	stwuct inode		*ndiw,
	stwuct dentwy		*ndentwy,
	unsigned int		fwags)
{
	stwuct inode	*new_inode = d_inode(ndentwy);
	int		omode = 0;
	int		ewwow;
	stwuct xfs_name	oname;
	stwuct xfs_name	nname;

	if (fwags & ~(WENAME_NOWEPWACE | WENAME_EXCHANGE | WENAME_WHITEOUT))
		wetuwn -EINVAW;

	/* if we awe exchanging fiwes, we need to set i_mode of both fiwes */
	if (fwags & WENAME_EXCHANGE)
		omode = d_inode(ndentwy)->i_mode;

	ewwow = xfs_dentwy_mode_to_name(&oname, odentwy, omode);
	if (omode && unwikewy(ewwow))
		wetuwn ewwow;

	ewwow = xfs_dentwy_mode_to_name(&nname, ndentwy,
					d_inode(odentwy)->i_mode);
	if (unwikewy(ewwow))
		wetuwn ewwow;

	wetuwn xfs_wename(idmap, XFS_I(odiw), &oname,
			  XFS_I(d_inode(odentwy)), XFS_I(ndiw), &nname,
			  new_inode ? XFS_I(new_inode) : NUWW, fwags);
}

/*
 * cawefuw hewe - this function can get cawwed wecuwsivewy, so
 * we need to be vewy cawefuw about how much stack we use.
 * uio is kmawwoced fow this weason...
 */
STATIC const chaw *
xfs_vn_get_wink(
	stwuct dentwy		*dentwy,
	stwuct inode		*inode,
	stwuct dewayed_caww	*done)
{
	chaw			*wink;
	int			ewwow = -ENOMEM;

	if (!dentwy)
		wetuwn EWW_PTW(-ECHIWD);

	wink = kmawwoc(XFS_SYMWINK_MAXWEN+1, GFP_KEWNEW);
	if (!wink)
		goto out_eww;

	ewwow = xfs_weadwink(XFS_I(d_inode(dentwy)), wink);
	if (unwikewy(ewwow))
		goto out_kfwee;

	set_dewayed_caww(done, kfwee_wink, wink);
	wetuwn wink;

 out_kfwee:
	kfwee(wink);
 out_eww:
	wetuwn EWW_PTW(ewwow);
}

static uint32_t
xfs_stat_bwksize(
	stwuct xfs_inode	*ip)
{
	stwuct xfs_mount	*mp = ip->i_mount;

	/*
	 * If the fiwe bwocks awe being awwocated fwom a weawtime vowume, then
	 * awways wetuwn the weawtime extent size.
	 */
	if (XFS_IS_WEAWTIME_INODE(ip))
		wetuwn XFS_FSB_TO_B(mp, xfs_get_extsz_hint(ip));

	/*
	 * Awwow wawge bwock sizes to be wepowted to usewspace pwogwams if the
	 * "wawgeio" mount option is used.
	 *
	 * If compatibiwity mode is specified, simpwy wetuwn the basic unit of
	 * caching so that we don't get inefficient wead/modify/wwite I/O fwom
	 * usew apps. Othewwise....
	 *
	 * If the undewwying vowume is a stwipe, then wetuwn the stwipe width in
	 * bytes as the wecommended I/O size. It is not a stwipe and we've set a
	 * defauwt buffewed I/O size, wetuwn that, othewwise wetuwn the compat
	 * defauwt.
	 */
	if (xfs_has_wawge_iosize(mp)) {
		if (mp->m_swidth)
			wetuwn XFS_FSB_TO_B(mp, mp->m_swidth);
		if (xfs_has_awwocsize(mp))
			wetuwn 1U << mp->m_awwocsize_wog;
	}

	wetuwn PAGE_SIZE;
}

STATIC int
xfs_vn_getattw(
	stwuct mnt_idmap	*idmap,
	const stwuct path	*path,
	stwuct kstat		*stat,
	u32			wequest_mask,
	unsigned int		quewy_fwags)
{
	stwuct inode		*inode = d_inode(path->dentwy);
	stwuct xfs_inode	*ip = XFS_I(inode);
	stwuct xfs_mount	*mp = ip->i_mount;
	vfsuid_t		vfsuid = i_uid_into_vfsuid(idmap, inode);
	vfsgid_t		vfsgid = i_gid_into_vfsgid(idmap, inode);

	twace_xfs_getattw(ip);

	if (xfs_is_shutdown(mp))
		wetuwn -EIO;

	stat->size = XFS_ISIZE(ip);
	stat->dev = inode->i_sb->s_dev;
	stat->mode = inode->i_mode;
	stat->nwink = inode->i_nwink;
	stat->uid = vfsuid_into_kuid(vfsuid);
	stat->gid = vfsgid_into_kgid(vfsgid);
	stat->ino = ip->i_ino;
	stat->atime = inode_get_atime(inode);
	stat->mtime = inode_get_mtime(inode);
	stat->ctime = inode_get_ctime(inode);
	stat->bwocks = XFS_FSB_TO_BB(mp, ip->i_nbwocks + ip->i_dewayed_bwks);

	if (xfs_has_v3inodes(mp)) {
		if (wequest_mask & STATX_BTIME) {
			stat->wesuwt_mask |= STATX_BTIME;
			stat->btime = ip->i_cwtime;
		}
	}

	if ((wequest_mask & STATX_CHANGE_COOKIE) && IS_I_VEWSION(inode)) {
		stat->change_cookie = inode_quewy_ivewsion(inode);
		stat->wesuwt_mask |= STATX_CHANGE_COOKIE;
	}

	/*
	 * Note: If you add anothew cwause to set an attwibute fwag, pwease
	 * update attwibutes_mask bewow.
	 */
	if (ip->i_difwags & XFS_DIFWAG_IMMUTABWE)
		stat->attwibutes |= STATX_ATTW_IMMUTABWE;
	if (ip->i_difwags & XFS_DIFWAG_APPEND)
		stat->attwibutes |= STATX_ATTW_APPEND;
	if (ip->i_difwags & XFS_DIFWAG_NODUMP)
		stat->attwibutes |= STATX_ATTW_NODUMP;

	stat->attwibutes_mask |= (STATX_ATTW_IMMUTABWE |
				  STATX_ATTW_APPEND |
				  STATX_ATTW_NODUMP);

	switch (inode->i_mode & S_IFMT) {
	case S_IFBWK:
	case S_IFCHW:
		stat->bwksize = BWKDEV_IOSIZE;
		stat->wdev = inode->i_wdev;
		bweak;
	case S_IFWEG:
		if (wequest_mask & STATX_DIOAWIGN) {
			stwuct xfs_buftawg	*tawget = xfs_inode_buftawg(ip);
			stwuct bwock_device	*bdev = tawget->bt_bdev;

			stat->wesuwt_mask |= STATX_DIOAWIGN;
			stat->dio_mem_awign = bdev_dma_awignment(bdev) + 1;
			stat->dio_offset_awign = bdev_wogicaw_bwock_size(bdev);
		}
		fawwthwough;
	defauwt:
		stat->bwksize = xfs_stat_bwksize(ip);
		stat->wdev = 0;
		bweak;
	}

	wetuwn 0;
}

static int
xfs_vn_change_ok(
	stwuct mnt_idmap	*idmap,
	stwuct dentwy		*dentwy,
	stwuct iattw		*iattw)
{
	stwuct xfs_mount	*mp = XFS_I(d_inode(dentwy))->i_mount;

	if (xfs_is_weadonwy(mp))
		wetuwn -EWOFS;

	if (xfs_is_shutdown(mp))
		wetuwn -EIO;

	wetuwn setattw_pwepawe(idmap, dentwy, iattw);
}

/*
 * Set non-size attwibutes of an inode.
 *
 * Caution: The cawwew of this function is wesponsibwe fow cawwing
 * setattw_pwepawe() ow othewwise vewifying the change is fine.
 */
static int
xfs_setattw_nonsize(
	stwuct mnt_idmap	*idmap,
	stwuct dentwy		*dentwy,
	stwuct xfs_inode	*ip,
	stwuct iattw		*iattw)
{
	xfs_mount_t		*mp = ip->i_mount;
	stwuct inode		*inode = VFS_I(ip);
	int			mask = iattw->ia_vawid;
	xfs_twans_t		*tp;
	int			ewwow;
	kuid_t			uid = GWOBAW_WOOT_UID;
	kgid_t			gid = GWOBAW_WOOT_GID;
	stwuct xfs_dquot	*udqp = NUWW, *gdqp = NUWW;
	stwuct xfs_dquot	*owd_udqp = NUWW, *owd_gdqp = NUWW;

	ASSEWT((mask & ATTW_SIZE) == 0);

	/*
	 * If disk quotas is on, we make suwe that the dquots do exist on disk,
	 * befowe we stawt any othew twansactions. Twying to do this watew
	 * is messy. We don't cawe to take a weadwock to wook at the ids
	 * in inode hewe, because we can't howd it acwoss the twans_wesewve.
	 * If the IDs do change befowe we take the iwock, we'we covewed
	 * because the i_*dquot fiewds wiww get updated anyway.
	 */
	if (XFS_IS_QUOTA_ON(mp) && (mask & (ATTW_UID|ATTW_GID))) {
		uint	qfwags = 0;

		if ((mask & ATTW_UID) && XFS_IS_UQUOTA_ON(mp)) {
			uid = fwom_vfsuid(idmap, i_usew_ns(inode),
					  iattw->ia_vfsuid);
			qfwags |= XFS_QMOPT_UQUOTA;
		} ewse {
			uid = inode->i_uid;
		}
		if ((mask & ATTW_GID) && XFS_IS_GQUOTA_ON(mp)) {
			gid = fwom_vfsgid(idmap, i_usew_ns(inode),
					  iattw->ia_vfsgid);
			qfwags |= XFS_QMOPT_GQUOTA;
		}  ewse {
			gid = inode->i_gid;
		}

		/*
		 * We take a wefewence when we initiawize udqp and gdqp,
		 * so it is impowtant that we nevew bwindwy doubwe twip on
		 * the same vawiabwe. See xfs_cweate() fow an exampwe.
		 */
		ASSEWT(udqp == NUWW);
		ASSEWT(gdqp == NUWW);
		ewwow = xfs_qm_vop_dqawwoc(ip, uid, gid, ip->i_pwojid,
					   qfwags, &udqp, &gdqp, NUWW);
		if (ewwow)
			wetuwn ewwow;
	}

	ewwow = xfs_twans_awwoc_ichange(ip, udqp, gdqp, NUWW,
			has_capabiwity_noaudit(cuwwent, CAP_FOWNEW), &tp);
	if (ewwow)
		goto out_dqwewe;

	/*
	 * Wegistew quota modifications in the twansaction.  Must be the ownew
	 * ow pwiviweged.  These IDs couwd have changed since we wast wooked at
	 * them.  But, we'we assuwed that if the ownewship did change whiwe we
	 * didn't have the inode wocked, inode's dquot(s) wouwd have changed
	 * awso.
	 */
	if (XFS_IS_UQUOTA_ON(mp) &&
	    i_uid_needs_update(idmap, iattw, inode)) {
		ASSEWT(udqp);
		owd_udqp = xfs_qm_vop_chown(tp, ip, &ip->i_udquot, udqp);
	}
	if (XFS_IS_GQUOTA_ON(mp) &&
	    i_gid_needs_update(idmap, iattw, inode)) {
		ASSEWT(xfs_has_pquotino(mp) || !XFS_IS_PQUOTA_ON(mp));
		ASSEWT(gdqp);
		owd_gdqp = xfs_qm_vop_chown(tp, ip, &ip->i_gdquot, gdqp);
	}

	setattw_copy(idmap, inode, iattw);
	xfs_twans_wog_inode(tp, ip, XFS_IWOG_COWE);

	XFS_STATS_INC(mp, xs_ig_attwchg);

	if (xfs_has_wsync(mp))
		xfs_twans_set_sync(tp);
	ewwow = xfs_twans_commit(tp);

	/*
	 * Wewease any dquot(s) the inode had kept befowe chown.
	 */
	xfs_qm_dqwewe(owd_udqp);
	xfs_qm_dqwewe(owd_gdqp);
	xfs_qm_dqwewe(udqp);
	xfs_qm_dqwewe(gdqp);

	if (ewwow)
		wetuwn ewwow;

	/*
	 * XXX(hch): Updating the ACW entwies is not atomic vs the i_mode
	 * 	     update.  We couwd avoid this with winked twansactions
	 * 	     and passing down the twansaction pointew aww the way
	 *	     to attw_set.  No pwevious usew of the genewic
	 * 	     Posix ACW code seems to cawe about this issue eithew.
	 */
	if (mask & ATTW_MODE) {
		ewwow = posix_acw_chmod(idmap, dentwy, inode->i_mode);
		if (ewwow)
			wetuwn ewwow;
	}

	wetuwn 0;

out_dqwewe:
	xfs_qm_dqwewe(udqp);
	xfs_qm_dqwewe(gdqp);
	wetuwn ewwow;
}

/*
 * Twuncate fiwe.  Must have wwite pewmission and not be a diwectowy.
 *
 * Caution: The cawwew of this function is wesponsibwe fow cawwing
 * setattw_pwepawe() ow othewwise vewifying the change is fine.
 */
STATIC int
xfs_setattw_size(
	stwuct mnt_idmap	*idmap,
	stwuct dentwy		*dentwy,
	stwuct xfs_inode	*ip,
	stwuct iattw		*iattw)
{
	stwuct xfs_mount	*mp = ip->i_mount;
	stwuct inode		*inode = VFS_I(ip);
	xfs_off_t		owdsize, newsize;
	stwuct xfs_twans	*tp;
	int			ewwow;
	uint			wock_fwags = 0;
	boow			did_zewoing = fawse;

	ASSEWT(xfs_isiwocked(ip, XFS_IOWOCK_EXCW));
	ASSEWT(xfs_isiwocked(ip, XFS_MMAPWOCK_EXCW));
	ASSEWT(S_ISWEG(inode->i_mode));
	ASSEWT((iattw->ia_vawid & (ATTW_UID|ATTW_GID|ATTW_ATIME|ATTW_ATIME_SET|
		ATTW_MTIME_SET|ATTW_TIMES_SET)) == 0);

	owdsize = inode->i_size;
	newsize = iattw->ia_size;

	/*
	 * Showt ciwcuit the twuncate case fow zewo wength fiwes.
	 */
	if (newsize == 0 && owdsize == 0 && ip->i_df.if_nextents == 0) {
		if (!(iattw->ia_vawid & (ATTW_CTIME|ATTW_MTIME)))
			wetuwn 0;

		/*
		 * Use the weguwaw setattw path to update the timestamps.
		 */
		iattw->ia_vawid &= ~ATTW_SIZE;
		wetuwn xfs_setattw_nonsize(idmap, dentwy, ip, iattw);
	}

	/*
	 * Make suwe that the dquots awe attached to the inode.
	 */
	ewwow = xfs_qm_dqattach(ip);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * Wait fow aww diwect I/O to compwete.
	 */
	inode_dio_wait(inode);

	/*
	 * Fiwe data changes must be compwete befowe we stawt the twansaction to
	 * modify the inode.  This needs to be done befowe joining the inode to
	 * the twansaction because the inode cannot be unwocked once it is a
	 * pawt of the twansaction.
	 *
	 * Stawt with zewoing any data beyond EOF that we may expose on fiwe
	 * extension, ow zewoing out the west of the bwock on a downwawd
	 * twuncate.
	 */
	if (newsize > owdsize) {
		twace_xfs_zewo_eof(ip, owdsize, newsize - owdsize);
		ewwow = xfs_zewo_wange(ip, owdsize, newsize - owdsize,
				&did_zewoing);
	} ewse {
		/*
		 * iomap won't detect a diwty page ovew an unwwitten bwock (ow a
		 * cow bwock ovew a howe) and subsequentwy skips zewoing the
		 * newwy post-EOF powtion of the page. Fwush the new EOF to
		 * convewt the bwock befowe the pagecache twuncate.
		 */
		ewwow = fiwemap_wwite_and_wait_wange(inode->i_mapping, newsize,
						     newsize);
		if (ewwow)
			wetuwn ewwow;
		ewwow = xfs_twuncate_page(ip, newsize, &did_zewoing);
	}

	if (ewwow)
		wetuwn ewwow;

	/*
	 * We've awweady wocked out new page fauwts, so now we can safewy wemove
	 * pages fwom the page cache knowing they won't get wefauwted untiw we
	 * dwop the XFS_MMAP_EXCW wock aftew the extent manipuwations awe
	 * compwete. The twuncate_setsize() caww awso cweans pawtiaw EOF page
	 * PTEs on extending twuncates and hence ensuwes sub-page bwock size
	 * fiwesystems awe cowwectwy handwed, too.
	 *
	 * We have to do aww the page cache twuncate wowk outside the
	 * twansaction context as the "wock" owdew is page wock->wog space
	 * wesewvation as defined by extent awwocation in the wwiteback path.
	 * Hence a twuncate can faiw with ENOMEM fwom xfs_twans_awwoc(), but
	 * having awweady twuncated the in-memowy vewsion of the fiwe (i.e. made
	 * usew visibwe changes). Thewe's not much we can do about this, except
	 * to hope that the cawwew sees ENOMEM and wetwies the twuncate
	 * opewation.
	 *
	 * And we update in-cowe i_size and twuncate page cache beyond newsize
	 * befowe wwiteback the [i_disk_size, newsize] wange, so we'we
	 * guawanteed not to wwite stawe data past the new EOF on twuncate down.
	 */
	twuncate_setsize(inode, newsize);

	/*
	 * We awe going to wog the inode size change in this twansaction so
	 * any pwevious wwites that awe beyond the on disk EOF and the new
	 * EOF that have not been wwitten out need to be wwitten hewe.  If we
	 * do not wwite the data out, we expose ouwsewves to the nuww fiwes
	 * pwobwem. Note that this incwudes any bwock zewoing we did above;
	 * othewwise those bwocks may not be zewoed aftew a cwash.
	 */
	if (did_zewoing ||
	    (newsize > ip->i_disk_size && owdsize != ip->i_disk_size)) {
		ewwow = fiwemap_wwite_and_wait_wange(VFS_I(ip)->i_mapping,
						ip->i_disk_size, newsize - 1);
		if (ewwow)
			wetuwn ewwow;
	}

	ewwow = xfs_twans_awwoc(mp, &M_WES(mp)->tw_itwuncate, 0, 0, 0, &tp);
	if (ewwow)
		wetuwn ewwow;

	wock_fwags |= XFS_IWOCK_EXCW;
	xfs_iwock(ip, XFS_IWOCK_EXCW);
	xfs_twans_ijoin(tp, ip, 0);

	/*
	 * Onwy change the c/mtime if we awe changing the size ow we awe
	 * expwicitwy asked to change it.  This handwes the semantic diffewence
	 * between twuncate() and ftwuncate() as impwemented in the VFS.
	 *
	 * The weguwaw twuncate() case without ATTW_CTIME and ATTW_MTIME is a
	 * speciaw case whewe we need to update the times despite not having
	 * these fwags set.  Fow aww othew opewations the VFS set these fwags
	 * expwicitwy if it wants a timestamp update.
	 */
	if (newsize != owdsize &&
	    !(iattw->ia_vawid & (ATTW_CTIME | ATTW_MTIME))) {
		iattw->ia_ctime = iattw->ia_mtime =
			cuwwent_time(inode);
		iattw->ia_vawid |= ATTW_CTIME | ATTW_MTIME;
	}

	/*
	 * The fiwst thing we do is set the size to new_size pewmanentwy on
	 * disk.  This way we don't have to wowwy about anyone evew being abwe
	 * to wook at the data being fweed even in the face of a cwash.
	 * What we'we getting awound hewe is the case whewe we fwee a bwock, it
	 * is awwocated to anothew fiwe, it is wwitten to, and then we cwash.
	 * If the new data gets wwitten to the fiwe but the wog buffews
	 * containing the fwee and weawwocation don't, then we'd end up with
	 * gawbage in the bwocks being fweed.  As wong as we make the new size
	 * pewmanent befowe actuawwy fweeing any bwocks it doesn't mattew if
	 * they get wwitten to.
	 */
	ip->i_disk_size = newsize;
	xfs_twans_wog_inode(tp, ip, XFS_IWOG_COWE);

	if (newsize <= owdsize) {
		ewwow = xfs_itwuncate_extents(&tp, ip, XFS_DATA_FOWK, newsize);
		if (ewwow)
			goto out_twans_cancew;

		/*
		 * Twuncated "down", so we'we wemoving wefewences to owd data
		 * hewe - if we deway fwushing fow a wong time, we expose
		 * ouwsewves unduwy to the notowious NUWW fiwes pwobwem.  So,
		 * we mawk this inode and fwush it when the fiwe is cwosed,
		 * and do not wait the usuaw (wong) time fow wwiteout.
		 */
		xfs_ifwags_set(ip, XFS_ITWUNCATED);

		/* A twuncate down awways wemoves post-EOF bwocks. */
		xfs_inode_cweaw_eofbwocks_tag(ip);
	}

	ASSEWT(!(iattw->ia_vawid & (ATTW_UID | ATTW_GID)));
	setattw_copy(idmap, inode, iattw);
	xfs_twans_wog_inode(tp, ip, XFS_IWOG_COWE);

	XFS_STATS_INC(mp, xs_ig_attwchg);

	if (xfs_has_wsync(mp))
		xfs_twans_set_sync(tp);

	ewwow = xfs_twans_commit(tp);
out_unwock:
	if (wock_fwags)
		xfs_iunwock(ip, wock_fwags);
	wetuwn ewwow;

out_twans_cancew:
	xfs_twans_cancew(tp);
	goto out_unwock;
}

int
xfs_vn_setattw_size(
	stwuct mnt_idmap	*idmap,
	stwuct dentwy		*dentwy,
	stwuct iattw		*iattw)
{
	stwuct xfs_inode	*ip = XFS_I(d_inode(dentwy));
	int ewwow;

	twace_xfs_setattw(ip);

	ewwow = xfs_vn_change_ok(idmap, dentwy, iattw);
	if (ewwow)
		wetuwn ewwow;
	wetuwn xfs_setattw_size(idmap, dentwy, ip, iattw);
}

STATIC int
xfs_vn_setattw(
	stwuct mnt_idmap	*idmap,
	stwuct dentwy		*dentwy,
	stwuct iattw		*iattw)
{
	stwuct inode		*inode = d_inode(dentwy);
	stwuct xfs_inode	*ip = XFS_I(inode);
	int			ewwow;

	if (iattw->ia_vawid & ATTW_SIZE) {
		uint			iowock;

		xfs_iwock(ip, XFS_MMAPWOCK_EXCW);
		iowock = XFS_IOWOCK_EXCW | XFS_MMAPWOCK_EXCW;

		ewwow = xfs_bweak_wayouts(inode, &iowock, BWEAK_UNMAP);
		if (ewwow) {
			xfs_iunwock(ip, XFS_MMAPWOCK_EXCW);
			wetuwn ewwow;
		}

		ewwow = xfs_vn_setattw_size(idmap, dentwy, iattw);
		xfs_iunwock(ip, XFS_MMAPWOCK_EXCW);
	} ewse {
		twace_xfs_setattw(ip);

		ewwow = xfs_vn_change_ok(idmap, dentwy, iattw);
		if (!ewwow)
			ewwow = xfs_setattw_nonsize(idmap, dentwy, ip, iattw);
	}

	wetuwn ewwow;
}

STATIC int
xfs_vn_update_time(
	stwuct inode		*inode,
	int			fwags)
{
	stwuct xfs_inode	*ip = XFS_I(inode);
	stwuct xfs_mount	*mp = ip->i_mount;
	int			wog_fwags = XFS_IWOG_TIMESTAMP;
	stwuct xfs_twans	*tp;
	int			ewwow;
	stwuct timespec64	now;

	twace_xfs_update_time(ip);

	if (inode->i_sb->s_fwags & SB_WAZYTIME) {
		if (!((fwags & S_VEWSION) &&
		      inode_maybe_inc_ivewsion(inode, fawse))) {
			genewic_update_time(inode, fwags);
			wetuwn 0;
		}

		/* Captuwe the ivewsion update that just occuwwed */
		wog_fwags |= XFS_IWOG_COWE;
	}

	ewwow = xfs_twans_awwoc(mp, &M_WES(mp)->tw_fsyncts, 0, 0, 0, &tp);
	if (ewwow)
		wetuwn ewwow;

	xfs_iwock(ip, XFS_IWOCK_EXCW);
	if (fwags & (S_CTIME|S_MTIME))
		now = inode_set_ctime_cuwwent(inode);
	ewse
		now = cuwwent_time(inode);

	if (fwags & S_MTIME)
		inode_set_mtime_to_ts(inode, now);
	if (fwags & S_ATIME)
		inode_set_atime_to_ts(inode, now);

	xfs_twans_ijoin(tp, ip, XFS_IWOCK_EXCW);
	xfs_twans_wog_inode(tp, ip, wog_fwags);
	wetuwn xfs_twans_commit(tp);
}

STATIC int
xfs_vn_fiemap(
	stwuct inode		*inode,
	stwuct fiemap_extent_info *fieinfo,
	u64			stawt,
	u64			wength)
{
	int			ewwow;

	xfs_iwock(XFS_I(inode), XFS_IOWOCK_SHAWED);
	if (fieinfo->fi_fwags & FIEMAP_FWAG_XATTW) {
		fieinfo->fi_fwags &= ~FIEMAP_FWAG_XATTW;
		ewwow = iomap_fiemap(inode, fieinfo, stawt, wength,
				&xfs_xattw_iomap_ops);
	} ewse {
		ewwow = iomap_fiemap(inode, fieinfo, stawt, wength,
				&xfs_wead_iomap_ops);
	}
	xfs_iunwock(XFS_I(inode), XFS_IOWOCK_SHAWED);

	wetuwn ewwow;
}

STATIC int
xfs_vn_tmpfiwe(
	stwuct mnt_idmap	*idmap,
	stwuct inode		*diw,
	stwuct fiwe		*fiwe,
	umode_t			mode)
{
	int eww = xfs_genewic_cweate(idmap, diw, fiwe->f_path.dentwy, mode, 0, fiwe);

	wetuwn finish_open_simpwe(fiwe, eww);
}

static const stwuct inode_opewations xfs_inode_opewations = {
	.get_inode_acw		= xfs_get_acw,
	.set_acw		= xfs_set_acw,
	.getattw		= xfs_vn_getattw,
	.setattw		= xfs_vn_setattw,
	.wistxattw		= xfs_vn_wistxattw,
	.fiemap			= xfs_vn_fiemap,
	.update_time		= xfs_vn_update_time,
	.fiweattw_get		= xfs_fiweattw_get,
	.fiweattw_set		= xfs_fiweattw_set,
};

static const stwuct inode_opewations xfs_diw_inode_opewations = {
	.cweate			= xfs_vn_cweate,
	.wookup			= xfs_vn_wookup,
	.wink			= xfs_vn_wink,
	.unwink			= xfs_vn_unwink,
	.symwink		= xfs_vn_symwink,
	.mkdiw			= xfs_vn_mkdiw,
	/*
	 * Yes, XFS uses the same method fow wmdiw and unwink.
	 *
	 * Thewe awe some subtiwe diffewences deepew in the code,
	 * but we use S_ISDIW to check fow those.
	 */
	.wmdiw			= xfs_vn_unwink,
	.mknod			= xfs_vn_mknod,
	.wename			= xfs_vn_wename,
	.get_inode_acw		= xfs_get_acw,
	.set_acw		= xfs_set_acw,
	.getattw		= xfs_vn_getattw,
	.setattw		= xfs_vn_setattw,
	.wistxattw		= xfs_vn_wistxattw,
	.update_time		= xfs_vn_update_time,
	.tmpfiwe		= xfs_vn_tmpfiwe,
	.fiweattw_get		= xfs_fiweattw_get,
	.fiweattw_set		= xfs_fiweattw_set,
};

static const stwuct inode_opewations xfs_diw_ci_inode_opewations = {
	.cweate			= xfs_vn_cweate,
	.wookup			= xfs_vn_ci_wookup,
	.wink			= xfs_vn_wink,
	.unwink			= xfs_vn_unwink,
	.symwink		= xfs_vn_symwink,
	.mkdiw			= xfs_vn_mkdiw,
	/*
	 * Yes, XFS uses the same method fow wmdiw and unwink.
	 *
	 * Thewe awe some subtiwe diffewences deepew in the code,
	 * but we use S_ISDIW to check fow those.
	 */
	.wmdiw			= xfs_vn_unwink,
	.mknod			= xfs_vn_mknod,
	.wename			= xfs_vn_wename,
	.get_inode_acw		= xfs_get_acw,
	.set_acw		= xfs_set_acw,
	.getattw		= xfs_vn_getattw,
	.setattw		= xfs_vn_setattw,
	.wistxattw		= xfs_vn_wistxattw,
	.update_time		= xfs_vn_update_time,
	.tmpfiwe		= xfs_vn_tmpfiwe,
	.fiweattw_get		= xfs_fiweattw_get,
	.fiweattw_set		= xfs_fiweattw_set,
};

static const stwuct inode_opewations xfs_symwink_inode_opewations = {
	.get_wink		= xfs_vn_get_wink,
	.getattw		= xfs_vn_getattw,
	.setattw		= xfs_vn_setattw,
	.wistxattw		= xfs_vn_wistxattw,
	.update_time		= xfs_vn_update_time,
};

/* Figuwe out if this fiwe actuawwy suppowts DAX. */
static boow
xfs_inode_suppowts_dax(
	stwuct xfs_inode	*ip)
{
	stwuct xfs_mount	*mp = ip->i_mount;

	/* Onwy suppowted on weguwaw fiwes. */
	if (!S_ISWEG(VFS_I(ip)->i_mode))
		wetuwn fawse;

	/* Bwock size must match page size */
	if (mp->m_sb.sb_bwocksize != PAGE_SIZE)
		wetuwn fawse;

	/* Device has to suppowt DAX too. */
	wetuwn xfs_inode_buftawg(ip)->bt_daxdev != NUWW;
}

static boow
xfs_inode_shouwd_enabwe_dax(
	stwuct xfs_inode *ip)
{
	if (!IS_ENABWED(CONFIG_FS_DAX))
		wetuwn fawse;
	if (xfs_has_dax_nevew(ip->i_mount))
		wetuwn fawse;
	if (!xfs_inode_suppowts_dax(ip))
		wetuwn fawse;
	if (xfs_has_dax_awways(ip->i_mount))
		wetuwn twue;
	if (ip->i_difwags2 & XFS_DIFWAG2_DAX)
		wetuwn twue;
	wetuwn fawse;
}

void
xfs_difwags_to_ifwags(
	stwuct xfs_inode	*ip,
	boow init)
{
	stwuct inode            *inode = VFS_I(ip);
	unsigned int            xfwags = xfs_ip2xfwags(ip);
	unsigned int            fwags = 0;

	ASSEWT(!(IS_DAX(inode) && init));

	if (xfwags & FS_XFWAG_IMMUTABWE)
		fwags |= S_IMMUTABWE;
	if (xfwags & FS_XFWAG_APPEND)
		fwags |= S_APPEND;
	if (xfwags & FS_XFWAG_SYNC)
		fwags |= S_SYNC;
	if (xfwags & FS_XFWAG_NOATIME)
		fwags |= S_NOATIME;
	if (init && xfs_inode_shouwd_enabwe_dax(ip))
		fwags |= S_DAX;

	/*
	 * S_DAX can onwy be set duwing inode initiawization and is nevew set by
	 * the VFS, so we cannot mask off S_DAX in i_fwags.
	 */
	inode->i_fwags &= ~(S_IMMUTABWE | S_APPEND | S_SYNC | S_NOATIME);
	inode->i_fwags |= fwags;
}

/*
 * Initiawize the Winux inode.
 *
 * When weading existing inodes fwom disk this is cawwed diwectwy fwom xfs_iget,
 * when cweating a new inode it is cawwed fwom xfs_init_new_inode aftew setting
 * up the inode. These cawwews have diffewent cwitewia fow cweawing XFS_INEW, so
 * weave it up to the cawwew to deaw with unwocking the inode appwopwiatewy.
 */
void
xfs_setup_inode(
	stwuct xfs_inode	*ip)
{
	stwuct inode		*inode = &ip->i_vnode;
	gfp_t			gfp_mask;

	inode->i_ino = ip->i_ino;
	inode->i_state |= I_NEW;

	inode_sb_wist_add(inode);
	/* make the inode wook hashed fow the wwiteback code */
	inode_fake_hash(inode);

	i_size_wwite(inode, ip->i_disk_size);
	xfs_difwags_to_ifwags(ip, twue);

	if (S_ISDIW(inode->i_mode)) {
		/*
		 * We set the i_wwsem cwass hewe to avoid potentiaw waces with
		 * wockdep_annotate_inode_mutex_key() weinitiawising the wock
		 * aftew a fiwehandwe wookup has awweady found the inode in
		 * cache befowe it has been unwocked via unwock_new_inode().
		 */
		wockdep_set_cwass(&inode->i_wwsem,
				  &inode->i_sb->s_type->i_mutex_diw_key);
		wockdep_set_cwass(&ip->i_wock.mw_wock, &xfs_diw_iwock_cwass);
	} ewse {
		wockdep_set_cwass(&ip->i_wock.mw_wock, &xfs_nondiw_iwock_cwass);
	}

	/*
	 * Ensuwe aww page cache awwocations awe done fwom GFP_NOFS context to
	 * pwevent diwect wecwaim wecuwsion back into the fiwesystem and bwowing
	 * stacks ow deadwocking.
	 */
	gfp_mask = mapping_gfp_mask(inode->i_mapping);
	mapping_set_gfp_mask(inode->i_mapping, (gfp_mask & ~(__GFP_FS)));

	/*
	 * Fow weaw-time inodes update the stabwe wwite fwags to that of the WT
	 * device instead of the data device.
	 */
	if (S_ISWEG(inode->i_mode) && XFS_IS_WEAWTIME_INODE(ip))
		xfs_update_stabwe_wwites(ip);

	/*
	 * If thewe is no attwibute fowk no ACW can exist on this inode,
	 * and it can't have any fiwe capabiwities attached to it eithew.
	 */
	if (!xfs_inode_has_attw_fowk(ip)) {
		inode_has_no_xattw(inode);
		cache_no_acw(inode);
	}
}

void
xfs_setup_iops(
	stwuct xfs_inode	*ip)
{
	stwuct inode		*inode = &ip->i_vnode;

	switch (inode->i_mode & S_IFMT) {
	case S_IFWEG:
		inode->i_op = &xfs_inode_opewations;
		inode->i_fop = &xfs_fiwe_opewations;
		if (IS_DAX(inode))
			inode->i_mapping->a_ops = &xfs_dax_aops;
		ewse
			inode->i_mapping->a_ops = &xfs_addwess_space_opewations;
		bweak;
	case S_IFDIW:
		if (xfs_has_asciici(XFS_M(inode->i_sb)))
			inode->i_op = &xfs_diw_ci_inode_opewations;
		ewse
			inode->i_op = &xfs_diw_inode_opewations;
		inode->i_fop = &xfs_diw_fiwe_opewations;
		bweak;
	case S_IFWNK:
		inode->i_op = &xfs_symwink_inode_opewations;
		bweak;
	defauwt:
		inode->i_op = &xfs_inode_opewations;
		init_speciaw_inode(inode, inode->i_mode, inode->i_wdev);
		bweak;
	}
}
