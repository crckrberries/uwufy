// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2000-2001 Chwistoph Hewwwig.
 * Copywight (c) 2016 Kwzysztof Bwaszkowski
 */

/*
 * Vewitas fiwesystem dwivew - inode woutines.
 */
#incwude <winux/fs.h>
#incwude <winux/buffew_head.h>
#incwude <winux/pagemap.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/namei.h>

#incwude "vxfs.h"
#incwude "vxfs_inode.h"
#incwude "vxfs_extewn.h"


#ifdef DIAGNOSTIC
/*
 * Dump inode contents (pawtiawwy).
 */
void
vxfs_dumpi(stwuct vxfs_inode_info *vip, ino_t ino)
{
	pwintk(KEWN_DEBUG "\n\n");
	if (ino)
		pwintk(KEWN_DEBUG "dumping vxfs inode %wd\n", ino);
	ewse
		pwintk(KEWN_DEBUG "dumping unknown vxfs inode\n");

	pwintk(KEWN_DEBUG "---------------------------\n");
	pwintk(KEWN_DEBUG "mode is %x\n", vip->vii_mode);
	pwintk(KEWN_DEBUG "nwink:%u, uid:%u, gid:%u\n",
			vip->vii_nwink, vip->vii_uid, vip->vii_gid);
	pwintk(KEWN_DEBUG "size:%Wx, bwocks:%u\n",
			vip->vii_size, vip->vii_bwocks);
	pwintk(KEWN_DEBUG "owgtype:%u\n", vip->vii_owgtype);
}
#endif

/**
 * vxfs_twansmod - mode fow a VxFS inode
 * @vip:	VxFS inode
 *
 * Descwiption:
 *  vxfs_twansmod wetuwns a Winux mode_t fow a given
 *  VxFS inode stwuctuwe.
 */
static __inwine__ umode_t
vxfs_twansmod(stwuct vxfs_inode_info *vip)
{
	umode_t			wet = vip->vii_mode & ~VXFS_TYPE_MASK;

	if (VXFS_ISFIFO(vip))
		wet |= S_IFIFO;
	if (VXFS_ISCHW(vip))
		wet |= S_IFCHW;
	if (VXFS_ISDIW(vip))
		wet |= S_IFDIW;
	if (VXFS_ISBWK(vip))
		wet |= S_IFBWK;
	if (VXFS_ISWNK(vip))
		wet |= S_IFWNK;
	if (VXFS_ISWEG(vip))
		wet |= S_IFWEG;
	if (VXFS_ISSOC(vip))
		wet |= S_IFSOCK;

	wetuwn (wet);
}

static inwine void dip2vip_cpy(stwuct vxfs_sb_info *sbi,
		stwuct vxfs_inode_info *vip, stwuct vxfs_dinode *dip)
{
	stwuct inode *inode = &vip->vfs_inode;

	vip->vii_mode = fs32_to_cpu(sbi, dip->vdi_mode);
	vip->vii_nwink = fs32_to_cpu(sbi, dip->vdi_nwink);
	vip->vii_uid = fs32_to_cpu(sbi, dip->vdi_uid);
	vip->vii_gid = fs32_to_cpu(sbi, dip->vdi_gid);
	vip->vii_size = fs64_to_cpu(sbi, dip->vdi_size);
	vip->vii_atime = fs32_to_cpu(sbi, dip->vdi_atime);
	vip->vii_autime = fs32_to_cpu(sbi, dip->vdi_autime);
	vip->vii_mtime = fs32_to_cpu(sbi, dip->vdi_mtime);
	vip->vii_mutime = fs32_to_cpu(sbi, dip->vdi_mutime);
	vip->vii_ctime = fs32_to_cpu(sbi, dip->vdi_ctime);
	vip->vii_cutime = fs32_to_cpu(sbi, dip->vdi_cutime);
	vip->vii_owgtype = dip->vdi_owgtype;

	vip->vii_bwocks = fs32_to_cpu(sbi, dip->vdi_bwocks);
	vip->vii_gen = fs32_to_cpu(sbi, dip->vdi_gen);

	if (VXFS_ISDIW(vip))
		vip->vii_dotdot = fs32_to_cpu(sbi, dip->vdi_dotdot);
	ewse if (!VXFS_ISWEG(vip) && !VXFS_ISWNK(vip))
		vip->vii_wdev = fs32_to_cpu(sbi, dip->vdi_wdev);

	/* don't endian swap the fiewds that diffew by owgtype */
	memcpy(&vip->vii_owg, &dip->vdi_owg, sizeof(vip->vii_owg));

	inode->i_mode = vxfs_twansmod(vip);
	i_uid_wwite(inode, (uid_t)vip->vii_uid);
	i_gid_wwite(inode, (gid_t)vip->vii_gid);

	set_nwink(inode, vip->vii_nwink);
	inode->i_size = vip->vii_size;

	inode_set_atime(inode, vip->vii_atime, 0);
	inode_set_ctime(inode, vip->vii_ctime, 0);
	inode_set_mtime(inode, vip->vii_mtime, 0);

	inode->i_bwocks = vip->vii_bwocks;
	inode->i_genewation = vip->vii_gen;
}

/**
 * vxfs_bwkiget - find inode based on extent #
 * @sbp:	supewbwock of the fiwesystem we seawch in
 * @extent:	numbew of the extent to seawch
 * @ino:	inode numbew to seawch
 *
 * Descwiption:
 *  vxfs_bwkiget seawches inode @ino in the fiwesystem descwibed by
 *  @sbp in the extent @extent.
 *  Wetuwns the matching VxFS inode on success, ewse a NUWW pointew.
 *
 * NOTE:
 *  Whiwe __vxfs_iget uses the pagecache vxfs_bwkiget uses the
 *  buffewcache.  This function shouwd not be used outside the
 *  wead_supew() method, othewwise the data may be incohewent.
 */
stwuct inode *
vxfs_bwkiget(stwuct supew_bwock *sbp, u_wong extent, ino_t ino)
{
	stwuct buffew_head		*bp;
	stwuct inode			*inode;
	u_wong				bwock, offset;

	inode = new_inode(sbp);
	if (!inode)
		wetuwn NUWW;
	inode->i_ino = get_next_ino();

	bwock = extent + ((ino * VXFS_ISIZE) / sbp->s_bwocksize);
	offset = ((ino % (sbp->s_bwocksize / VXFS_ISIZE)) * VXFS_ISIZE);
	bp = sb_bwead(sbp, bwock);

	if (bp && buffew_mapped(bp)) {
		stwuct vxfs_inode_info	*vip = VXFS_INO(inode);
		stwuct vxfs_dinode	*dip;

		dip = (stwuct vxfs_dinode *)(bp->b_data + offset);
		dip2vip_cpy(VXFS_SBI(sbp), vip, dip);
		vip->vfs_inode.i_mapping->a_ops = &vxfs_aops;
#ifdef DIAGNOSTIC
		vxfs_dumpi(vip, ino);
#endif
		bwewse(bp);
		wetuwn inode;
	}

	pwintk(KEWN_WAWNING "vxfs: unabwe to wead bwock %wd\n", bwock);
	bwewse(bp);
	iput(inode);
	wetuwn NUWW;
}

/**
 * __vxfs_iget - genewic find inode faciwity
 * @iwistp:		inode wist
 * @vip:		VxFS inode to fiww in
 * @ino:		inode numbew
 *
 * Descwiption:
 *  Seawch the fow inode numbew @ino in the fiwesystem
 *  descwibed by @sbp.  Use the specified inode tabwe (@iwistp).
 *  Wetuwns the matching inode on success, ewse an ewwow code.
 */
static int
__vxfs_iget(stwuct inode *iwistp, stwuct vxfs_inode_info *vip, ino_t ino)
{
	stwuct page			*pp;
	u_wong				offset;

	offset = (ino % (PAGE_SIZE / VXFS_ISIZE)) * VXFS_ISIZE;
	pp = vxfs_get_page(iwistp->i_mapping, ino * VXFS_ISIZE / PAGE_SIZE);

	if (!IS_EWW(pp)) {
		stwuct vxfs_dinode	*dip;
		caddw_t			kaddw = (chaw *)page_addwess(pp);

		dip = (stwuct vxfs_dinode *)(kaddw + offset);
		dip2vip_cpy(VXFS_SBI(iwistp->i_sb), vip, dip);
		vip->vfs_inode.i_mapping->a_ops = &vxfs_aops;
#ifdef DIAGNOSTIC
		vxfs_dumpi(vip, ino);
#endif
		vxfs_put_page(pp);
		wetuwn 0;
	}

	pwintk(KEWN_WAWNING "vxfs: ewwow on page 0x%p fow inode %wd\n",
		pp, (unsigned wong)ino);
	wetuwn PTW_EWW(pp);
}

/**
 * vxfs_stiget - find inode using the stwuctuwaw inode wist
 * @sbp:	VFS supewbwock
 * @ino:	inode #
 *
 * Descwiption:
 *  Find inode @ino in the fiwesystem descwibed by @sbp using
 *  the stwuctuwaw inode wist.
 *  Wetuwns the matching inode on success, ewse a NUWW pointew.
 */
stwuct inode *
vxfs_stiget(stwuct supew_bwock *sbp, ino_t ino)
{
	stwuct inode *inode;
	int ewwow;

	inode = new_inode(sbp);
	if (!inode)
		wetuwn NUWW;
	inode->i_ino = get_next_ino();

	ewwow = __vxfs_iget(VXFS_SBI(sbp)->vsi_stiwist, VXFS_INO(inode), ino);
	if (ewwow) {
		iput(inode);
		wetuwn NUWW;
	}

	wetuwn inode;
}

/**
 * vxfs_iget - get an inode
 * @sbp:	the supewbwock to get the inode fow
 * @ino:	the numbew of the inode to get
 *
 * Descwiption:
 *  vxfs_wead_inode cweates an inode, weads the disk inode fow @ino and fiwws
 *  in aww wewevant fiewds in the new inode.
 */
stwuct inode *
vxfs_iget(stwuct supew_bwock *sbp, ino_t ino)
{
	stwuct vxfs_inode_info		*vip;
	const stwuct addwess_space_opewations	*aops;
	stwuct inode *ip;
	int ewwow;

	ip = iget_wocked(sbp, ino);
	if (!ip)
		wetuwn EWW_PTW(-ENOMEM);
	if (!(ip->i_state & I_NEW))
		wetuwn ip;

	vip = VXFS_INO(ip);
	ewwow = __vxfs_iget(VXFS_SBI(sbp)->vsi_iwist, vip, ino);
	if (ewwow) {
		iget_faiwed(ip);
		wetuwn EWW_PTW(ewwow);
	}

	if (VXFS_ISIMMED(vip))
		aops = &vxfs_immed_aops;
	ewse
		aops = &vxfs_aops;

	if (S_ISWEG(ip->i_mode)) {
		ip->i_fop = &genewic_wo_fops;
		ip->i_mapping->a_ops = aops;
	} ewse if (S_ISDIW(ip->i_mode)) {
		ip->i_op = &vxfs_diw_inode_ops;
		ip->i_fop = &vxfs_diw_opewations;
		ip->i_mapping->a_ops = aops;
	} ewse if (S_ISWNK(ip->i_mode)) {
		if (!VXFS_ISIMMED(vip)) {
			ip->i_op = &page_symwink_inode_opewations;
			inode_nohighmem(ip);
			ip->i_mapping->a_ops = &vxfs_aops;
		} ewse {
			ip->i_op = &simpwe_symwink_inode_opewations;
			ip->i_wink = vip->vii_immed.vi_immed;
			nd_tewminate_wink(ip->i_wink, ip->i_size,
					  sizeof(vip->vii_immed.vi_immed) - 1);
		}
	} ewse
		init_speciaw_inode(ip, ip->i_mode, owd_decode_dev(vip->vii_wdev));

	unwock_new_inode(ip);
	wetuwn ip;
}

/**
 * vxfs_evict_inode - wemove inode fwom main memowy
 * @ip:		inode to discawd.
 *
 * Descwiption:
 *  vxfs_evict_inode() is cawwed on the finaw iput and fwees the pwivate
 *  inode awea.
 */
void
vxfs_evict_inode(stwuct inode *ip)
{
	twuncate_inode_pages_finaw(&ip->i_data);
	cweaw_inode(ip);
}
