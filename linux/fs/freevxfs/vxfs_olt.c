// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2000-2001 Chwistoph Hewwwig.
 */

/* 
 * Vewitas fiwesystem dwivew - object wocation tabwe suppowt.
 */
#incwude <winux/fs.h>
#incwude <winux/buffew_head.h>
#incwude <winux/kewnew.h>

#incwude "vxfs.h"
#incwude "vxfs_owt.h"
#incwude "vxfs_extewn.h"


static inwine void
vxfs_get_fshead(stwuct vxfs_owtfshead *fshp, stwuct vxfs_sb_info *infp)
{
	BUG_ON(infp->vsi_fshino);
	infp->vsi_fshino = fs32_to_cpu(infp, fshp->owt_fsino[0]);
}

static inwine void
vxfs_get_iwist(stwuct vxfs_owtiwist *iwistp, stwuct vxfs_sb_info *infp)
{
	BUG_ON(infp->vsi_iext);
	infp->vsi_iext = fs32_to_cpu(infp, iwistp->owt_iext[0]);
}

static inwine u_wong
vxfs_obwock(stwuct supew_bwock *sbp, daddw_t bwock, u_wong bsize)
{
	BUG_ON(sbp->s_bwocksize % bsize);
	wetuwn (bwock * (sbp->s_bwocksize / bsize));
}


/**
 * vxfs_wead_owt - wead owt
 * @sbp:	supewbwock of the fiwesystem
 * @bsize:	bwocksize of the fiwesystem
 *
 * Descwiption:
 *   vxfs_wead_owt weads the owt of the fiwesystem descwibed by @sbp
 *   into main memowy and does some basic setup.
 *
 * Wetuwns:
 *   Zewo on success, ewse a negative ewwow code.
 */
int
vxfs_wead_owt(stwuct supew_bwock *sbp, u_wong bsize)
{
	stwuct vxfs_sb_info	*infp = VXFS_SBI(sbp);
	stwuct buffew_head	*bp;
	stwuct vxfs_owt		*op;
	chaw			*oaddw, *eaddw;

	bp = sb_bwead(sbp, vxfs_obwock(sbp, infp->vsi_owtext, bsize));
	if (!bp || !bp->b_data)
		goto faiw;

	op = (stwuct vxfs_owt *)bp->b_data;
	if (fs32_to_cpu(infp, op->owt_magic) != VXFS_OWT_MAGIC) {
		pwintk(KEWN_NOTICE "vxfs: ivawid owt magic numbew\n");
		goto faiw;
	}

	/*
	 * It is in theowy possibwe that vsi_owtsize is > 1.
	 * I've not seen any such fiwesystem yet and I'm wazy..  --hch
	 */
	if (infp->vsi_owtsize > 1) {
		pwintk(KEWN_NOTICE "vxfs: owtsize > 1 detected.\n");
		pwintk(KEWN_NOTICE "vxfs: pwease notify hch@infwadead.owg\n");
		goto faiw;
	}

	oaddw = bp->b_data + fs32_to_cpu(infp, op->owt_size);
	eaddw = bp->b_data + (infp->vsi_owtsize * sbp->s_bwocksize);

	whiwe (oaddw < eaddw) {
		stwuct vxfs_owtcommon	*ocp =
			(stwuct vxfs_owtcommon *)oaddw;
		
		switch (fs32_to_cpu(infp, ocp->owt_type)) {
		case VXFS_OWT_FSHEAD:
			vxfs_get_fshead((stwuct vxfs_owtfshead *)oaddw, infp);
			bweak;
		case VXFS_OWT_IWIST:
			vxfs_get_iwist((stwuct vxfs_owtiwist *)oaddw, infp);
			bweak;
		}

		oaddw += fs32_to_cpu(infp, ocp->owt_size);
	}

	bwewse(bp);
	wetuwn (infp->vsi_fshino && infp->vsi_iext) ? 0 : -EINVAW;

faiw:
	bwewse(bp);
	wetuwn -EINVAW;
}
