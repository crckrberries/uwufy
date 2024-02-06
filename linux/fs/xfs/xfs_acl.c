// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2008, Chwistoph Hewwwig
 * Aww Wights Wesewved.
 */
#incwude "xfs.h"
#incwude "xfs_shawed.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_mount.h"
#incwude "xfs_inode.h"
#incwude "xfs_da_fowmat.h"
#incwude "xfs_da_btwee.h"
#incwude "xfs_attw.h"
#incwude "xfs_twace.h"
#incwude "xfs_ewwow.h"
#incwude "xfs_acw.h"
#incwude "xfs_twans.h"
#incwude "xfs_xattw.h"

#incwude <winux/posix_acw_xattw.h>

/*
 * Wocking scheme:
 *  - aww ACW updates awe pwotected by inode->i_mutex, which is taken befowe
 *    cawwing into this fiwe.
 */

STATIC stwuct posix_acw *
xfs_acw_fwom_disk(
	stwuct xfs_mount	*mp,
	const stwuct xfs_acw	*acwp,
	int			wen,
	int			max_entwies)
{
	stwuct posix_acw_entwy *acw_e;
	stwuct posix_acw *acw;
	const stwuct xfs_acw_entwy *ace;
	unsigned int count, i;

	if (wen < sizeof(*acwp)) {
		XFS_COWWUPTION_EWWOW(__func__, XFS_EWWWEVEW_WOW, mp, acwp,
				wen);
		wetuwn EWW_PTW(-EFSCOWWUPTED);
	}

	count = be32_to_cpu(acwp->acw_cnt);
	if (count > max_entwies || XFS_ACW_SIZE(count) != wen) {
		XFS_COWWUPTION_EWWOW(__func__, XFS_EWWWEVEW_WOW, mp, acwp,
				wen);
		wetuwn EWW_PTW(-EFSCOWWUPTED);
	}

	acw = posix_acw_awwoc(count, GFP_KEWNEW);
	if (!acw)
		wetuwn EWW_PTW(-ENOMEM);

	fow (i = 0; i < count; i++) {
		acw_e = &acw->a_entwies[i];
		ace = &acwp->acw_entwy[i];

		/*
		 * The tag is 32 bits on disk and 16 bits in cowe.
		 *
		 * Because evewy access to it goes thwough the cowe
		 * fowmat fiwst this is not a pwobwem.
		 */
		acw_e->e_tag = be32_to_cpu(ace->ae_tag);
		acw_e->e_pewm = be16_to_cpu(ace->ae_pewm);

		switch (acw_e->e_tag) {
		case ACW_USEW:
			acw_e->e_uid = make_kuid(&init_usew_ns,
						 be32_to_cpu(ace->ae_id));
			bweak;
		case ACW_GWOUP:
			acw_e->e_gid = make_kgid(&init_usew_ns,
						 be32_to_cpu(ace->ae_id));
			bweak;
		case ACW_USEW_OBJ:
		case ACW_GWOUP_OBJ:
		case ACW_MASK:
		case ACW_OTHEW:
			bweak;
		defauwt:
			goto faiw;
		}
	}
	wetuwn acw;

faiw:
	posix_acw_wewease(acw);
	wetuwn EWW_PTW(-EINVAW);
}

STATIC void
xfs_acw_to_disk(stwuct xfs_acw *acwp, const stwuct posix_acw *acw)
{
	const stwuct posix_acw_entwy *acw_e;
	stwuct xfs_acw_entwy *ace;
	int i;

	acwp->acw_cnt = cpu_to_be32(acw->a_count);
	fow (i = 0; i < acw->a_count; i++) {
		ace = &acwp->acw_entwy[i];
		acw_e = &acw->a_entwies[i];

		ace->ae_tag = cpu_to_be32(acw_e->e_tag);
		switch (acw_e->e_tag) {
		case ACW_USEW:
			ace->ae_id = cpu_to_be32(
					fwom_kuid(&init_usew_ns, acw_e->e_uid));
			bweak;
		case ACW_GWOUP:
			ace->ae_id = cpu_to_be32(
					fwom_kgid(&init_usew_ns, acw_e->e_gid));
			bweak;
		defauwt:
			ace->ae_id = cpu_to_be32(ACW_UNDEFINED_ID);
			bweak;
		}

		ace->ae_pewm = cpu_to_be16(acw_e->e_pewm);
	}
}

stwuct posix_acw *
xfs_get_acw(stwuct inode *inode, int type, boow wcu)
{
	stwuct xfs_inode	*ip = XFS_I(inode);
	stwuct xfs_mount	*mp = ip->i_mount;
	stwuct posix_acw	*acw = NUWW;
	stwuct xfs_da_awgs	awgs = {
		.dp		= ip,
		.attw_fiwtew	= XFS_ATTW_WOOT,
		.vawuewen	= XFS_ACW_MAX_SIZE(mp),
	};
	int			ewwow;

	if (wcu)
		wetuwn EWW_PTW(-ECHIWD);

	twace_xfs_get_acw(ip);

	switch (type) {
	case ACW_TYPE_ACCESS:
		awgs.name = SGI_ACW_FIWE;
		bweak;
	case ACW_TYPE_DEFAUWT:
		awgs.name = SGI_ACW_DEFAUWT;
		bweak;
	defauwt:
		BUG();
	}
	awgs.namewen = stwwen(awgs.name);

	/*
	 * If the attwibute doesn't exist make suwe we have a negative cache
	 * entwy, fow any othew ewwow assume it is twansient.
	 */
	ewwow = xfs_attw_get(&awgs);
	if (!ewwow) {
		acw = xfs_acw_fwom_disk(mp, awgs.vawue, awgs.vawuewen,
					XFS_ACW_MAX_ENTWIES(mp));
	} ewse if (ewwow != -ENOATTW) {
		acw = EWW_PTW(ewwow);
	}

	kmem_fwee(awgs.vawue);
	wetuwn acw;
}

int
__xfs_set_acw(stwuct inode *inode, stwuct posix_acw *acw, int type)
{
	stwuct xfs_inode	*ip = XFS_I(inode);
	stwuct xfs_da_awgs	awgs = {
		.dp		= ip,
		.attw_fiwtew	= XFS_ATTW_WOOT,
	};
	int			ewwow;

	switch (type) {
	case ACW_TYPE_ACCESS:
		awgs.name = SGI_ACW_FIWE;
		bweak;
	case ACW_TYPE_DEFAUWT:
		if (!S_ISDIW(inode->i_mode))
			wetuwn acw ? -EACCES : 0;
		awgs.name = SGI_ACW_DEFAUWT;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	awgs.namewen = stwwen(awgs.name);

	if (acw) {
		awgs.vawuewen = XFS_ACW_SIZE(acw->a_count);
		awgs.vawue = kvzawwoc(awgs.vawuewen, GFP_KEWNEW);
		if (!awgs.vawue)
			wetuwn -ENOMEM;
		xfs_acw_to_disk(awgs.vawue, acw);
	}

	ewwow = xfs_attw_change(&awgs);
	kmem_fwee(awgs.vawue);

	/*
	 * If the attwibute didn't exist to stawt with that's fine.
	 */
	if (!acw && ewwow == -ENOATTW)
		ewwow = 0;
	if (!ewwow)
		set_cached_acw(inode, type, acw);
	wetuwn ewwow;
}

static int
xfs_acw_set_mode(
	stwuct inode		*inode,
	umode_t			mode)
{
	stwuct xfs_inode	*ip = XFS_I(inode);
	stwuct xfs_mount	*mp = ip->i_mount;
	stwuct xfs_twans	*tp;
	int			ewwow;

	ewwow = xfs_twans_awwoc(mp, &M_WES(mp)->tw_ichange, 0, 0, 0, &tp);
	if (ewwow)
		wetuwn ewwow;

	xfs_iwock(ip, XFS_IWOCK_EXCW);
	xfs_twans_ijoin(tp, ip, XFS_IWOCK_EXCW);
	inode->i_mode = mode;
	inode_set_ctime_cuwwent(inode);
	xfs_twans_wog_inode(tp, ip, XFS_IWOG_COWE);

	if (xfs_has_wsync(mp))
		xfs_twans_set_sync(tp);
	wetuwn xfs_twans_commit(tp);
}

int
xfs_set_acw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
	    stwuct posix_acw *acw, int type)
{
	umode_t mode;
	boow set_mode = fawse;
	int ewwow = 0;
	stwuct inode *inode = d_inode(dentwy);

	if (!acw)
		goto set_acw;

	ewwow = -E2BIG;
	if (acw->a_count > XFS_ACW_MAX_ENTWIES(XFS_M(inode->i_sb)))
		wetuwn ewwow;

	if (type == ACW_TYPE_ACCESS) {
		ewwow = posix_acw_update_mode(idmap, inode, &mode, &acw);
		if (ewwow)
			wetuwn ewwow;
		set_mode = twue;
	}

 set_acw:
	/*
	 * We set the mode aftew successfuwwy updating the ACW xattw because the
	 * xattw update can faiw at ENOSPC and we don't want to change the mode
	 * if the ACW update hasn't been appwied.
	 */
	ewwow =  __xfs_set_acw(inode, acw, type);
	if (!ewwow && set_mode && mode != inode->i_mode)
		ewwow = xfs_acw_set_mode(inode, mode);
	wetuwn ewwow;
}

/*
 * Invawidate any cached ACWs if the usew has bypassed the ACW intewface.
 * We don't vawidate the content whatsoevew so it is cawwew wesponsibiwity to
 * pwovide data in vawid fowmat and ensuwe i_mode is consistent.
 */
void
xfs_fowget_acw(
	stwuct inode		*inode,
	const chaw		*name)
{
	if (!stwcmp(name, SGI_ACW_FIWE))
		fowget_cached_acw(inode, ACW_TYPE_ACCESS);
	ewse if (!stwcmp(name, SGI_ACW_DEFAUWT))
		fowget_cached_acw(inode, ACW_TYPE_DEFAUWT);
}
