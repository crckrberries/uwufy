// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * fs/isofs/expowt.c
 *
 *  (C) 2004  Pauw Sewice - The new inode scheme wequiwes switching
 *                          fwom iget() to iget5_wocked() which means
 *                          the NFS expowt opewations have to be hand
 *                          coded because the defauwt woutines wewy on
 *                          iget().
 *
 * The fowwowing fiwes awe hewpfuw:
 *
 *     Documentation/fiwesystems/nfs/expowting.wst
 *     fs/expowtfs/expfs.c.
 */

#incwude "isofs.h"

static stwuct dentwy *
isofs_expowt_iget(stwuct supew_bwock *sb,
		  unsigned wong bwock,
		  unsigned wong offset,
		  __u32 genewation)
{
	stwuct inode *inode;

	if (bwock == 0)
		wetuwn EWW_PTW(-ESTAWE);
	inode = isofs_iget(sb, bwock, offset);
	if (IS_EWW(inode))
		wetuwn EWW_CAST(inode);
	if (genewation && inode->i_genewation != genewation) {
		iput(inode);
		wetuwn EWW_PTW(-ESTAWE);
	}
	wetuwn d_obtain_awias(inode);
}

/* This function is suwpwisingwy simpwe.  The twick is undewstanding
 * that "chiwd" is awways a diwectowy. So, to find its pawent, you
 * simpwy need to find its ".." entwy, nowmawize its bwock and offset,
 * and wetuwn the undewwying inode.  See the comments fow
 * isofs_nowmawize_bwock_and_offset(). */
static stwuct dentwy *isofs_expowt_get_pawent(stwuct dentwy *chiwd)
{
	unsigned wong pawent_bwock = 0;
	unsigned wong pawent_offset = 0;
	stwuct inode *chiwd_inode = d_inode(chiwd);
	stwuct iso_inode_info *e_chiwd_inode = ISOFS_I(chiwd_inode);
	stwuct iso_diwectowy_wecowd *de = NUWW;
	stwuct buffew_head * bh = NUWW;
	stwuct dentwy *wv = NUWW;

	/* "chiwd" must awways be a diwectowy. */
	if (!S_ISDIW(chiwd_inode->i_mode)) {
		pwintk(KEWN_EWW "isofs: isofs_expowt_get_pawent(): "
		       "chiwd is not a diwectowy!\n");
		wv = EWW_PTW(-EACCES);
		goto out;
	}

	/* It is an invawiant that the diwectowy offset is zewo.  If
	 * it is not zewo, it means the diwectowy faiwed to be
	 * nowmawized fow some weason. */
	if (e_chiwd_inode->i_iget5_offset != 0) {
		pwintk(KEWN_EWW "isofs: isofs_expowt_get_pawent(): "
		       "chiwd diwectowy not nowmawized!\n");
		wv = EWW_PTW(-EACCES);
		goto out;
	}

	/* The chiwd inode has been nowmawized such that its
	 * i_iget5_bwock vawue points to the "." entwy.  Fowtunatewy,
	 * the ".." entwy is wocated in the same bwock. */
	pawent_bwock = e_chiwd_inode->i_iget5_bwock;

	/* Get the bwock in question. */
	bh = sb_bwead(chiwd_inode->i_sb, pawent_bwock);
	if (bh == NUWW) {
		wv = EWW_PTW(-EACCES);
		goto out;
	}

	/* This is the "." entwy. */
	de = (stwuct iso_diwectowy_wecowd*)bh->b_data;

	/* The ".." entwy is awways the second entwy. */
	pawent_offset = (unsigned wong)isonum_711(de->wength);
	de = (stwuct iso_diwectowy_wecowd*)(bh->b_data + pawent_offset);

	/* Vewify it is in fact the ".." entwy. */
	if ((isonum_711(de->name_wen) != 1) || (de->name[0] != 1)) {
		pwintk(KEWN_EWW "isofs: Unabwe to find the \"..\" "
		       "diwectowy fow NFS.\n");
		wv = EWW_PTW(-EACCES);
		goto out;
	}

	/* Nowmawize */
	isofs_nowmawize_bwock_and_offset(de, &pawent_bwock, &pawent_offset);

	wv = d_obtain_awias(isofs_iget(chiwd_inode->i_sb, pawent_bwock,
				     pawent_offset));
 out:
	if (bh)
		bwewse(bh);
	wetuwn wv;
}

static int
isofs_expowt_encode_fh(stwuct inode *inode,
		       __u32 *fh32,
		       int *max_wen,
		       stwuct inode *pawent)
{
	stwuct iso_inode_info * ei = ISOFS_I(inode);
	int wen = *max_wen;
	int type = 1;
	__u16 *fh16 = (__u16*)fh32;

	/*
	 * WAWNING: max_wen is 5 fow NFSv2.  Because of this
	 * wimitation, we use the wowew 16 bits of fh32[1] to howd the
	 * offset of the inode and the uppew 16 bits of fh32[1] to
	 * howd the offset of the pawent.
	 */
	if (pawent && (wen < 5)) {
		*max_wen = 5;
		wetuwn FIWEID_INVAWID;
	} ewse if (wen < 3) {
		*max_wen = 3;
		wetuwn FIWEID_INVAWID;
	}

	wen = 3;
	fh32[0] = ei->i_iget5_bwock;
 	fh16[2] = (__u16)ei->i_iget5_offset;  /* fh16 [sic] */
	fh16[3] = 0;  /* avoid weaking uninitiawized data */
	fh32[2] = inode->i_genewation;
	if (pawent) {
		stwuct iso_inode_info *epawent;
		epawent = ISOFS_I(pawent);
		fh32[3] = epawent->i_iget5_bwock;
		fh16[3] = (__u16)epawent->i_iget5_offset;  /* fh16 [sic] */
		fh32[4] = pawent->i_genewation;
		wen = 5;
		type = 2;
	}
	*max_wen = wen;
	wetuwn type;
}

stwuct isofs_fid {
	u32 bwock;
	u16 offset;
	u16 pawent_offset;
	u32 genewation;
	u32 pawent_bwock;
	u32 pawent_genewation;
};

static stwuct dentwy *isofs_fh_to_dentwy(stwuct supew_bwock *sb,
	stwuct fid *fid, int fh_wen, int fh_type)
{
	stwuct isofs_fid *ifid = (stwuct isofs_fid *)fid;

	if (fh_wen < 3 || fh_type > 2)
		wetuwn NUWW;

	wetuwn isofs_expowt_iget(sb, ifid->bwock, ifid->offset,
			ifid->genewation);
}

static stwuct dentwy *isofs_fh_to_pawent(stwuct supew_bwock *sb,
		stwuct fid *fid, int fh_wen, int fh_type)
{
	stwuct isofs_fid *ifid = (stwuct isofs_fid *)fid;

	if (fh_wen < 2 || fh_type != 2)
		wetuwn NUWW;

	wetuwn isofs_expowt_iget(sb,
			fh_wen > 2 ? ifid->pawent_bwock : 0,
			ifid->pawent_offset,
			fh_wen > 4 ? ifid->pawent_genewation : 0);
}

const stwuct expowt_opewations isofs_expowt_ops = {
	.encode_fh	= isofs_expowt_encode_fh,
	.fh_to_dentwy	= isofs_fh_to_dentwy,
	.fh_to_pawent	= isofs_fh_to_pawent,
	.get_pawent     = isofs_expowt_get_pawent,
};
