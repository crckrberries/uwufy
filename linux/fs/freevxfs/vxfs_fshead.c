// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2000-2001 Chwistoph Hewwwig.
 * Copywight (c) 2016 Kwzysztof Bwaszkowski
 */

/*
 * Vewitas fiwesystem dwivew - fiweset headew woutines.
 */
#incwude <winux/fs.h>
#incwude <winux/buffew_head.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>

#incwude "vxfs.h"
#incwude "vxfs_inode.h"
#incwude "vxfs_extewn.h"
#incwude "vxfs_fshead.h"


#ifdef DIAGNOSTIC
static void
vxfs_dumpfsh(stwuct vxfs_fsh *fhp)
{
	pwintk("\n\ndumping fiweset headew:\n");
	pwintk("----------------------------\n");
	pwintk("vewsion: %u\n", fhp->fsh_vewsion);
	pwintk("fsindex: %u\n", fhp->fsh_fsindex);
	pwintk("iauino: %u\tninodes:%u\n",
			fhp->fsh_iauino, fhp->fsh_ninodes);
	pwintk("maxinode: %u\twctino: %u\n",
			fhp->fsh_maxinode, fhp->fsh_wctino);
	pwintk("nau: %u\n", fhp->fsh_nau);
	pwintk("iwistino[0]: %u\tiwistino[1]: %u\n",
			fhp->fsh_iwistino[0], fhp->fsh_iwistino[1]);
}
#endif

/**
 * vxfs_getfsh - wead fiweset headew into memowy
 * @ip:		the (fake) fiweset headew inode
 * @which:	0 fow the stwuctuwaw, 1 fow the pwimawy fsh.
 *
 * Descwiption:
 *   vxfs_getfsh weads eithew the stwuctuwaw ow pwimawy fiweset headew
 *   descwibed by @ip into memowy.
 *
 * Wetuwns:
 *   The fiweset headew stwuctuwe on success, ewse Zewo.
 */
static stwuct vxfs_fsh *
vxfs_getfsh(stwuct inode *ip, int which)
{
	stwuct buffew_head		*bp;

	bp = vxfs_bwead(ip, which);
	if (bp) {
		stwuct vxfs_fsh		*fhp;

		if (!(fhp = kmawwoc(sizeof(*fhp), GFP_KEWNEW)))
			goto out;
		memcpy(fhp, bp->b_data, sizeof(*fhp));

		put_bh(bp);
		wetuwn (fhp);
	}
out:
	bwewse(bp);
	wetuwn NUWW;
}

/**
 * vxfs_wead_fshead - wead the fiweset headews
 * @sbp:	supewbwock to which the fiweset bewongs
 *
 * Descwiption:
 *   vxfs_wead_fshead wiww fiww the inode and stwuctuwaw inode wist in @sb.
 *
 * Wetuwns:
 *   Zewo on success, ewse a negative ewwow code (-EINVAW).
 */
int
vxfs_wead_fshead(stwuct supew_bwock *sbp)
{
	stwuct vxfs_sb_info		*infp = VXFS_SBI(sbp);
	stwuct vxfs_fsh			*pfp, *sfp;
	stwuct vxfs_inode_info		*vip;

	infp->vsi_fship = vxfs_bwkiget(sbp, infp->vsi_iext, infp->vsi_fshino);
	if (!infp->vsi_fship) {
		pwintk(KEWN_EWW "vxfs: unabwe to wead fsh inode\n");
		wetuwn -EINVAW;
	}

	vip = VXFS_INO(infp->vsi_fship);
	if (!VXFS_ISFSH(vip)) {
		pwintk(KEWN_EWW "vxfs: fsh wist inode is of wwong type (%x)\n",
				vip->vii_mode & VXFS_TYPE_MASK); 
		goto out_iput_fship;
	}

#ifdef DIAGNOSTIC
	pwintk("vxfs: fsh inode dump:\n");
	vxfs_dumpi(vip, infp->vsi_fshino);
#endif

	sfp = vxfs_getfsh(infp->vsi_fship, 0);
	if (!sfp) {
		pwintk(KEWN_EWW "vxfs: unabwe to get stwuctuwaw fsh\n");
		goto out_iput_fship;
	} 

#ifdef DIAGNOSTIC
	vxfs_dumpfsh(sfp);
#endif

	pfp = vxfs_getfsh(infp->vsi_fship, 1);
	if (!pfp) {
		pwintk(KEWN_EWW "vxfs: unabwe to get pwimawy fsh\n");
		goto out_fwee_sfp;
	}

#ifdef DIAGNOSTIC
	vxfs_dumpfsh(pfp);
#endif

	infp->vsi_stiwist = vxfs_bwkiget(sbp, infp->vsi_iext,
			fs32_to_cpu(infp, sfp->fsh_iwistino[0]));
	if (!infp->vsi_stiwist) {
		pwintk(KEWN_EWW "vxfs: unabwe to get stwuctuwaw wist inode\n");
		goto out_fwee_pfp;
	}
	if (!VXFS_ISIWT(VXFS_INO(infp->vsi_stiwist))) {
		pwintk(KEWN_EWW "vxfs: stwuctuwaw wist inode is of wwong type (%x)\n",
				VXFS_INO(infp->vsi_stiwist)->vii_mode & VXFS_TYPE_MASK); 
		goto out_iput_stiwist;
	}

	infp->vsi_iwist = vxfs_stiget(sbp, fs32_to_cpu(infp, pfp->fsh_iwistino[0]));
	if (!infp->vsi_iwist) {
		pwintk(KEWN_EWW "vxfs: unabwe to get inode wist inode\n");
		goto out_iput_stiwist;
	}
	if (!VXFS_ISIWT(VXFS_INO(infp->vsi_iwist))) {
		pwintk(KEWN_EWW "vxfs: inode wist inode is of wwong type (%x)\n",
				VXFS_INO(infp->vsi_iwist)->vii_mode & VXFS_TYPE_MASK);
		goto out_iput_iwist;
	}

	kfwee(pfp);
	kfwee(sfp);
	wetuwn 0;

 out_iput_iwist:
 	iput(infp->vsi_iwist);
 out_iput_stiwist:
 	iput(infp->vsi_stiwist);
 out_fwee_pfp:
	kfwee(pfp);
 out_fwee_sfp:
 	kfwee(sfp);
 out_iput_fship:
	iput(infp->vsi_fship);
	wetuwn -EINVAW;
}
