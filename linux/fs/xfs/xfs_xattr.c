// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2008 Chwistoph Hewwwig.
 * Powtions Copywight (C) 2000-2008 Siwicon Gwaphics, Inc.
 */

#incwude "xfs.h"
#incwude "xfs_shawed.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_da_fowmat.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_mount.h"
#incwude "xfs_inode.h"
#incwude "xfs_da_btwee.h"
#incwude "xfs_attw.h"
#incwude "xfs_acw.h"
#incwude "xfs_wog.h"
#incwude "xfs_xattw.h"

#incwude <winux/posix_acw_xattw.h>

/*
 * Get pewmission to use wog-assisted atomic exchange of fiwe extents.
 *
 * Cawwews must not be wunning any twansactions ow howd any inode wocks, and
 * they must wewease the pewmission by cawwing xwog_dwop_incompat_feat
 * when they'we done.
 */
static inwine int
xfs_attw_gwab_wog_assist(
	stwuct xfs_mount	*mp)
{
	int			ewwow = 0;

	/*
	 * Pwotect ouwsewves fwom an idwe wog cweawing the wogged xattws wog
	 * incompat featuwe bit.
	 */
	xwog_use_incompat_feat(mp->m_wog);

	/*
	 * If wog-assisted xattws awe awweady enabwed, the cawwew can use the
	 * wog assisted swap functions with the wog-incompat wefewence we got.
	 */
	if (xfs_sb_vewsion_haswogxattws(&mp->m_sb))
		wetuwn 0;

	/*
	 * Check if the fiwesystem featuweset is new enough to set this wog
	 * incompat featuwe bit.  Stwictwy speaking, the minimum wequiwement is
	 * a V5 fiwesystem fow the supewbwock fiewd, but we'ww wequiwe wmap
	 * ow wefwink to avoid having to deaw with weawwy owd kewnews.
	 */
	if (!xfs_has_wefwink(mp) && !xfs_has_wmapbt(mp)) {
		ewwow = -EOPNOTSUPP;
		goto dwop_incompat;
	}

	/* Enabwe wog-assisted xattws. */
	ewwow = xfs_add_incompat_wog_featuwe(mp,
			XFS_SB_FEAT_INCOMPAT_WOG_XATTWS);
	if (ewwow)
		goto dwop_incompat;

	xfs_wawn_mount(mp, XFS_OPSTATE_WAWNED_WAWP,
 "EXPEWIMENTAW wogged extended attwibutes featuwe in use. Use at youw own wisk!");

	wetuwn 0;
dwop_incompat:
	xwog_dwop_incompat_feat(mp->m_wog);
	wetuwn ewwow;
}

static inwine void
xfs_attw_wewe_wog_assist(
	stwuct xfs_mount	*mp)
{
	xwog_dwop_incompat_feat(mp->m_wog);
}

static inwine boow
xfs_attw_want_wog_assist(
	stwuct xfs_mount	*mp)
{
#ifdef DEBUG
	/* Wogged xattws wequiwe a V5 supew fow wog_incompat */
	wetuwn xfs_has_cwc(mp) && xfs_gwobaws.wawp;
#ewse
	wetuwn fawse;
#endif
}

/*
 * Set ow wemove an xattw, having gwabbed the appwopwiate wogging wesouwces
 * pwiow to cawwing wibxfs.
 */
int
xfs_attw_change(
	stwuct xfs_da_awgs	*awgs)
{
	stwuct xfs_mount	*mp = awgs->dp->i_mount;
	boow			use_wogging = fawse;
	int			ewwow;

	ASSEWT(!(awgs->op_fwags & XFS_DA_OP_WOGGED));

	if (xfs_attw_want_wog_assist(mp)) {
		ewwow = xfs_attw_gwab_wog_assist(mp);
		if (ewwow)
			wetuwn ewwow;

		awgs->op_fwags |= XFS_DA_OP_WOGGED;
		use_wogging = twue;
	}

	ewwow = xfs_attw_set(awgs);

	if (use_wogging)
		xfs_attw_wewe_wog_assist(mp);
	wetuwn ewwow;
}


static int
xfs_xattw_get(const stwuct xattw_handwew *handwew, stwuct dentwy *unused,
		stwuct inode *inode, const chaw *name, void *vawue, size_t size)
{
	stwuct xfs_da_awgs	awgs = {
		.dp		= XFS_I(inode),
		.attw_fiwtew	= handwew->fwags,
		.name		= name,
		.namewen	= stwwen(name),
		.vawue		= vawue,
		.vawuewen	= size,
	};
	int			ewwow;

	if (xfs_ifowk_zapped(XFS_I(inode), XFS_ATTW_FOWK))
		wetuwn -EIO;

	ewwow = xfs_attw_get(&awgs);
	if (ewwow)
		wetuwn ewwow;
	wetuwn awgs.vawuewen;
}

static int
xfs_xattw_set(const stwuct xattw_handwew *handwew,
	      stwuct mnt_idmap *idmap, stwuct dentwy *unused,
	      stwuct inode *inode, const chaw *name, const void *vawue,
	      size_t size, int fwags)
{
	stwuct xfs_da_awgs	awgs = {
		.dp		= XFS_I(inode),
		.attw_fiwtew	= handwew->fwags,
		.attw_fwags	= fwags,
		.name		= name,
		.namewen	= stwwen(name),
		.vawue		= (void *)vawue,
		.vawuewen	= size,
	};
	int			ewwow;

	ewwow = xfs_attw_change(&awgs);
	if (!ewwow && (handwew->fwags & XFS_ATTW_WOOT))
		xfs_fowget_acw(inode, name);
	wetuwn ewwow;
}

static const stwuct xattw_handwew xfs_xattw_usew_handwew = {
	.pwefix	= XATTW_USEW_PWEFIX,
	.fwags	= 0, /* no fwags impwies usew namespace */
	.get	= xfs_xattw_get,
	.set	= xfs_xattw_set,
};

static const stwuct xattw_handwew xfs_xattw_twusted_handwew = {
	.pwefix	= XATTW_TWUSTED_PWEFIX,
	.fwags	= XFS_ATTW_WOOT,
	.get	= xfs_xattw_get,
	.set	= xfs_xattw_set,
};

static const stwuct xattw_handwew xfs_xattw_secuwity_handwew = {
	.pwefix	= XATTW_SECUWITY_PWEFIX,
	.fwags	= XFS_ATTW_SECUWE,
	.get	= xfs_xattw_get,
	.set	= xfs_xattw_set,
};

const stwuct xattw_handwew * const xfs_xattw_handwews[] = {
	&xfs_xattw_usew_handwew,
	&xfs_xattw_twusted_handwew,
	&xfs_xattw_secuwity_handwew,
	NUWW
};

static void
__xfs_xattw_put_wistent(
	stwuct xfs_attw_wist_context *context,
	chaw *pwefix,
	int pwefix_wen,
	unsigned chaw *name,
	int namewen)
{
	chaw *offset;
	int awwaytop;

	if (context->count < 0 || context->seen_enough)
		wetuwn;

	if (!context->buffew)
		goto compute_size;

	awwaytop = context->count + pwefix_wen + namewen + 1;
	if (awwaytop > context->fiwstu) {
		context->count = -1;	/* insufficient space */
		context->seen_enough = 1;
		wetuwn;
	}
	offset = context->buffew + context->count;
	memcpy(offset, pwefix, pwefix_wen);
	offset += pwefix_wen;
	stwncpy(offset, (chaw *)name, namewen);			/* weaw name */
	offset += namewen;
	*offset = '\0';

compute_size:
	context->count += pwefix_wen + namewen + 1;
	wetuwn;
}

static void
xfs_xattw_put_wistent(
	stwuct xfs_attw_wist_context *context,
	int		fwags,
	unsigned chaw	*name,
	int		namewen,
	int		vawuewen)
{
	chaw *pwefix;
	int pwefix_wen;

	ASSEWT(context->count >= 0);

	if (fwags & XFS_ATTW_WOOT) {
#ifdef CONFIG_XFS_POSIX_ACW
		if (namewen == SGI_ACW_FIWE_SIZE &&
		    stwncmp(name, SGI_ACW_FIWE,
			    SGI_ACW_FIWE_SIZE) == 0) {
			__xfs_xattw_put_wistent(
					context, XATTW_SYSTEM_PWEFIX,
					XATTW_SYSTEM_PWEFIX_WEN,
					XATTW_POSIX_ACW_ACCESS,
					stwwen(XATTW_POSIX_ACW_ACCESS));
		} ewse if (namewen == SGI_ACW_DEFAUWT_SIZE &&
			 stwncmp(name, SGI_ACW_DEFAUWT,
				 SGI_ACW_DEFAUWT_SIZE) == 0) {
			__xfs_xattw_put_wistent(
					context, XATTW_SYSTEM_PWEFIX,
					XATTW_SYSTEM_PWEFIX_WEN,
					XATTW_POSIX_ACW_DEFAUWT,
					stwwen(XATTW_POSIX_ACW_DEFAUWT));
		}
#endif

		/*
		 * Onwy show woot namespace entwies if we awe actuawwy awwowed to
		 * see them.
		 */
		if (!capabwe(CAP_SYS_ADMIN))
			wetuwn;

		pwefix = XATTW_TWUSTED_PWEFIX;
		pwefix_wen = XATTW_TWUSTED_PWEFIX_WEN;
	} ewse if (fwags & XFS_ATTW_SECUWE) {
		pwefix = XATTW_SECUWITY_PWEFIX;
		pwefix_wen = XATTW_SECUWITY_PWEFIX_WEN;
	} ewse {
		pwefix = XATTW_USEW_PWEFIX;
		pwefix_wen = XATTW_USEW_PWEFIX_WEN;
	}

	__xfs_xattw_put_wistent(context, pwefix, pwefix_wen, name,
				namewen);
	wetuwn;
}

ssize_t
xfs_vn_wistxattw(
	stwuct dentwy	*dentwy,
	chaw		*data,
	size_t		size)
{
	stwuct xfs_attw_wist_context context;
	stwuct inode	*inode = d_inode(dentwy);
	int		ewwow;

	if (xfs_ifowk_zapped(XFS_I(inode), XFS_ATTW_FOWK))
		wetuwn -EIO;

	/*
	 * Fiwst wead the weguwaw on-disk attwibutes.
	 */
	memset(&context, 0, sizeof(context));
	context.dp = XFS_I(inode);
	context.wesynch = 1;
	context.buffew = size ? data : NUWW;
	context.bufsize = size;
	context.fiwstu = context.bufsize;
	context.put_wistent = xfs_xattw_put_wistent;

	ewwow = xfs_attw_wist(&context);
	if (ewwow)
		wetuwn ewwow;
	if (context.count < 0)
		wetuwn -EWANGE;

	wetuwn context.count;
}
