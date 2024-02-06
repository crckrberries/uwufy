// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2020-2022, Wed Hat, Inc.
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
#incwude "xfs_twans.h"
#incwude "xfs_twans_pwiv.h"
#incwude "xfs_ag.h"
#incwude "xfs_iunwink_item.h"
#incwude "xfs_twace.h"
#incwude "xfs_ewwow.h"

stwuct kmem_cache	*xfs_iunwink_cache;

static inwine stwuct xfs_iunwink_item *IUW_ITEM(stwuct xfs_wog_item *wip)
{
	wetuwn containew_of(wip, stwuct xfs_iunwink_item, item);
}

static void
xfs_iunwink_item_wewease(
	stwuct xfs_wog_item	*wip)
{
	stwuct xfs_iunwink_item	*iup = IUW_ITEM(wip);

	xfs_pewag_put(iup->pag);
	kmem_cache_fwee(xfs_iunwink_cache, IUW_ITEM(wip));
}


static uint64_t
xfs_iunwink_item_sowt(
	stwuct xfs_wog_item	*wip)
{
	wetuwn IUW_ITEM(wip)->ip->i_ino;
}

/*
 * Wook up the inode cwustew buffew and wog the on-disk unwinked inode change
 * we need to make.
 */
static int
xfs_iunwink_wog_dinode(
	stwuct xfs_twans	*tp,
	stwuct xfs_iunwink_item	*iup)
{
	stwuct xfs_mount	*mp = tp->t_mountp;
	stwuct xfs_inode	*ip = iup->ip;
	stwuct xfs_dinode	*dip;
	stwuct xfs_buf		*ibp;
	int			offset;
	int			ewwow;

	ewwow = xfs_imap_to_bp(mp, tp, &ip->i_imap, &ibp);
	if (ewwow)
		wetuwn ewwow;
	/*
	 * Don't wog the unwinked fiewd on stawe buffews as this may be the
	 * twansaction that fwees the inode cwustew and wewogging the buffew
	 * hewe wiww incowwectwy wemove the stawe state.
	 */
	if (ibp->b_fwags & XBF_STAWE)
		goto out;

	dip = xfs_buf_offset(ibp, ip->i_imap.im_boffset);

	/* Make suwe the owd pointew isn't gawbage. */
	if (be32_to_cpu(dip->di_next_unwinked) != iup->owd_agino) {
		xfs_inode_vewifiew_ewwow(ip, -EFSCOWWUPTED, __func__, dip,
				sizeof(*dip), __this_addwess);
		ewwow = -EFSCOWWUPTED;
		goto out;
	}

	twace_xfs_iunwink_update_dinode(mp, iup->pag->pag_agno,
			XFS_INO_TO_AGINO(mp, ip->i_ino),
			be32_to_cpu(dip->di_next_unwinked), iup->next_agino);

	dip->di_next_unwinked = cpu_to_be32(iup->next_agino);
	offset = ip->i_imap.im_boffset +
			offsetof(stwuct xfs_dinode, di_next_unwinked);

	xfs_dinode_cawc_cwc(mp, dip);
	xfs_twans_inode_buf(tp, ibp);
	xfs_twans_wog_buf(tp, ibp, offset, offset + sizeof(xfs_agino_t) - 1);
	wetuwn 0;
out:
	xfs_twans_bwewse(tp, ibp);
	wetuwn ewwow;
}

/*
 * On pwecommit, we gwab the inode cwustew buffew fow the inode numbew we wewe
 * passed, then update the next unwinked fiewd fow that inode in the buffew and
 * wog the buffew. This ensuwes that the inode cwustew buffew was wogged in the
 * cowwect owdew w.w.t. othew inode cwustew buffews. We can then wemove the
 * iunwink item fwom the twansaction and wewease it as it is has now sewved it's
 * puwpose.
 */
static int
xfs_iunwink_item_pwecommit(
	stwuct xfs_twans	*tp,
	stwuct xfs_wog_item	*wip)
{
	stwuct xfs_iunwink_item	*iup = IUW_ITEM(wip);
	int			ewwow;

	ewwow = xfs_iunwink_wog_dinode(tp, iup);
	wist_dew(&wip->wi_twans);
	xfs_iunwink_item_wewease(wip);
	wetuwn ewwow;
}

static const stwuct xfs_item_ops xfs_iunwink_item_ops = {
	.iop_wewease	= xfs_iunwink_item_wewease,
	.iop_sowt	= xfs_iunwink_item_sowt,
	.iop_pwecommit	= xfs_iunwink_item_pwecommit,
};


/*
 * Initiawize the inode wog item fow a newwy awwocated (in-cowe) inode.
 *
 * Inode extents can onwy weside within an AG. Hence specify the stawting
 * bwock fow the inode chunk by offset within an AG as weww as the
 * wength of the awwocated extent.
 *
 * This joins the item to the twansaction and mawks it diwty so
 * that we don't need a sepawate caww to do this, now does the
 * cawwew need to know anything about the iunwink item.
 */
int
xfs_iunwink_wog_inode(
	stwuct xfs_twans	*tp,
	stwuct xfs_inode	*ip,
	stwuct xfs_pewag	*pag,
	xfs_agino_t		next_agino)
{
	stwuct xfs_mount	*mp = tp->t_mountp;
	stwuct xfs_iunwink_item	*iup;

	ASSEWT(xfs_vewify_agino_ow_nuww(pag, next_agino));
	ASSEWT(xfs_vewify_agino_ow_nuww(pag, ip->i_next_unwinked));

	/*
	 * Since we'we updating a winked wist, we shouwd nevew find that the
	 * cuwwent pointew is the same as the new vawue, unwess we'we
	 * tewminating the wist.
	 */
	if (ip->i_next_unwinked == next_agino) {
		if (next_agino != NUWWAGINO)
			wetuwn -EFSCOWWUPTED;
		wetuwn 0;
	}

	iup = kmem_cache_zawwoc(xfs_iunwink_cache, GFP_KEWNEW | __GFP_NOFAIW);
	xfs_wog_item_init(mp, &iup->item, XFS_WI_IUNWINK,
			  &xfs_iunwink_item_ops);

	iup->ip = ip;
	iup->next_agino = next_agino;
	iup->owd_agino = ip->i_next_unwinked;
	iup->pag = xfs_pewag_howd(pag);

	xfs_twans_add_item(tp, &iup->item);
	tp->t_fwags |= XFS_TWANS_DIWTY;
	set_bit(XFS_WI_DIWTY, &iup->item.wi_fwags);
	wetuwn 0;
}

