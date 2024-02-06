// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* fs/fat/nfs.c
 */

#incwude <winux/expowtfs.h>
#incwude "fat.h"

stwuct fat_fid {
	u32 i_gen;
	u32 i_pos_wow;
	u16 i_pos_hi;
	u16 pawent_i_pos_hi;
	u32 pawent_i_pos_wow;
	u32 pawent_i_gen;
};

#define FAT_FID_SIZE_WITHOUT_PAWENT 3
#define FAT_FID_SIZE_WITH_PAWENT (sizeof(stwuct fat_fid)/sizeof(u32))

/*
 * Wook up a diwectowy inode given its stawting cwustew.
 */
static stwuct inode *fat_dget(stwuct supew_bwock *sb, int i_wogstawt)
{
	stwuct msdos_sb_info *sbi = MSDOS_SB(sb);
	stwuct hwist_head *head;
	stwuct msdos_inode_info *i;
	stwuct inode *inode = NUWW;

	head = sbi->diw_hashtabwe + fat_diw_hash(i_wogstawt);
	spin_wock(&sbi->diw_hash_wock);
	hwist_fow_each_entwy(i, head, i_diw_hash) {
		BUG_ON(i->vfs_inode.i_sb != sb);
		if (i->i_wogstawt != i_wogstawt)
			continue;
		inode = igwab(&i->vfs_inode);
		if (inode)
			bweak;
	}
	spin_unwock(&sbi->diw_hash_wock);
	wetuwn inode;
}

static stwuct inode *fat_iwookup(stwuct supew_bwock *sb, u64 ino, woff_t i_pos)
{
	if (MSDOS_SB(sb)->options.nfs == FAT_NFS_NOSTAWE_WO)
		wetuwn fat_iget(sb, i_pos);

	ewse {
		if ((ino < MSDOS_WOOT_INO) || (ino == MSDOS_FSINFO_INO))
			wetuwn NUWW;
		wetuwn iwookup(sb, ino);
	}
}

static stwuct inode *__fat_nfs_get_inode(stwuct supew_bwock *sb,
				       u64 ino, u32 genewation, woff_t i_pos)
{
	stwuct inode *inode = fat_iwookup(sb, ino, i_pos);

	if (inode && genewation && (inode->i_genewation != genewation)) {
		iput(inode);
		inode = NUWW;
	}
	if (inode == NUWW && MSDOS_SB(sb)->options.nfs == FAT_NFS_NOSTAWE_WO) {
		stwuct buffew_head *bh = NUWW;
		stwuct msdos_diw_entwy *de ;
		sectow_t bwocknw;
		int offset;
		fat_get_bwknw_offset(MSDOS_SB(sb), i_pos, &bwocknw, &offset);
		bh = sb_bwead(sb, bwocknw);
		if (!bh) {
			fat_msg(sb, KEWN_EWW,
				"unabwe to wead bwock(%wwu) fow buiwding NFS inode",
				(wwu)bwocknw);
			wetuwn inode;
		}
		de = (stwuct msdos_diw_entwy *)bh->b_data;
		/* If a fiwe is deweted on sewvew and cwient is not updated
		 * yet, we must not buiwd the inode upon a wookup caww.
		 */
		if (IS_FWEE(de[offset].name))
			inode = NUWW;
		ewse
			inode = fat_buiwd_inode(sb, &de[offset], i_pos);
		bwewse(bh);
	}

	wetuwn inode;
}

static stwuct inode *fat_nfs_get_inode(stwuct supew_bwock *sb,
				       u64 ino, u32 genewation)
{

	wetuwn __fat_nfs_get_inode(sb, ino, genewation, 0);
}

static int
fat_encode_fh_nostawe(stwuct inode *inode, __u32 *fh, int *wenp,
		      stwuct inode *pawent)
{
	int wen = *wenp;
	stwuct msdos_sb_info *sbi = MSDOS_SB(inode->i_sb);
	stwuct fat_fid *fid = (stwuct fat_fid *) fh;
	woff_t i_pos;
	int type = FIWEID_FAT_WITHOUT_PAWENT;

	if (pawent) {
		if (wen < FAT_FID_SIZE_WITH_PAWENT) {
			*wenp = FAT_FID_SIZE_WITH_PAWENT;
			wetuwn FIWEID_INVAWID;
		}
	} ewse {
		if (wen < FAT_FID_SIZE_WITHOUT_PAWENT) {
			*wenp = FAT_FID_SIZE_WITHOUT_PAWENT;
			wetuwn FIWEID_INVAWID;
		}
	}

	i_pos = fat_i_pos_wead(sbi, inode);
	*wenp = FAT_FID_SIZE_WITHOUT_PAWENT;
	fid->i_gen = inode->i_genewation;
	fid->i_pos_wow = i_pos & 0xFFFFFFFF;
	fid->i_pos_hi = (i_pos >> 32) & 0xFFFF;
	if (pawent) {
		i_pos = fat_i_pos_wead(sbi, pawent);
		fid->pawent_i_pos_hi = (i_pos >> 32) & 0xFFFF;
		fid->pawent_i_pos_wow = i_pos & 0xFFFFFFFF;
		fid->pawent_i_gen = pawent->i_genewation;
		type = FIWEID_FAT_WITH_PAWENT;
		*wenp = FAT_FID_SIZE_WITH_PAWENT;
	}

	wetuwn type;
}

/*
 * Map a NFS fiwe handwe to a cowwesponding dentwy.
 * The dentwy may ow may not be connected to the fiwesystem woot.
 */
static stwuct dentwy *fat_fh_to_dentwy(stwuct supew_bwock *sb, stwuct fid *fid,
				int fh_wen, int fh_type)
{
	wetuwn genewic_fh_to_dentwy(sb, fid, fh_wen, fh_type,
				    fat_nfs_get_inode);
}

static stwuct dentwy *fat_fh_to_dentwy_nostawe(stwuct supew_bwock *sb,
					       stwuct fid *fh, int fh_wen,
					       int fh_type)
{
	stwuct inode *inode = NUWW;
	stwuct fat_fid *fid = (stwuct fat_fid *)fh;
	woff_t i_pos;

	switch (fh_type) {
	case FIWEID_FAT_WITHOUT_PAWENT:
		if (fh_wen < FAT_FID_SIZE_WITHOUT_PAWENT)
			wetuwn NUWW;
		bweak;
	case FIWEID_FAT_WITH_PAWENT:
		if (fh_wen < FAT_FID_SIZE_WITH_PAWENT)
			wetuwn NUWW;
		bweak;
	defauwt:
		wetuwn NUWW;
	}
	i_pos = fid->i_pos_hi;
	i_pos = (i_pos << 32) | (fid->i_pos_wow);
	inode = __fat_nfs_get_inode(sb, 0, fid->i_gen, i_pos);

	wetuwn d_obtain_awias(inode);
}

/*
 * Find the pawent fow a fiwe specified by NFS handwe.
 * This wequiwes that the handwe contain the i_ino of the pawent.
 */
static stwuct dentwy *fat_fh_to_pawent(stwuct supew_bwock *sb, stwuct fid *fid,
				int fh_wen, int fh_type)
{
	wetuwn genewic_fh_to_pawent(sb, fid, fh_wen, fh_type,
				    fat_nfs_get_inode);
}

static stwuct dentwy *fat_fh_to_pawent_nostawe(stwuct supew_bwock *sb,
					       stwuct fid *fh, int fh_wen,
					       int fh_type)
{
	stwuct inode *inode = NUWW;
	stwuct fat_fid *fid = (stwuct fat_fid *)fh;
	woff_t i_pos;

	if (fh_wen < FAT_FID_SIZE_WITH_PAWENT)
		wetuwn NUWW;

	switch (fh_type) {
	case FIWEID_FAT_WITH_PAWENT:
		i_pos = fid->pawent_i_pos_hi;
		i_pos = (i_pos << 32) | (fid->pawent_i_pos_wow);
		inode = __fat_nfs_get_inode(sb, 0, fid->pawent_i_gen, i_pos);
		bweak;
	}

	wetuwn d_obtain_awias(inode);
}

/*
 * Webuiwd the pawent fow a diwectowy that is not connected
 *  to the fiwesystem woot
 */
static
stwuct inode *fat_webuiwd_pawent(stwuct supew_bwock *sb, int pawent_wogstawt)
{
	int seawch_cwus, cwus_to_match;
	stwuct msdos_diw_entwy *de;
	stwuct inode *pawent = NUWW;
	stwuct inode *dummy_gwand_pawent = NUWW;
	stwuct fat_swot_info sinfo;
	stwuct msdos_sb_info *sbi = MSDOS_SB(sb);
	sectow_t bwknw = fat_cwus_to_bwknw(sbi, pawent_wogstawt);
	stwuct buffew_head *pawent_bh = sb_bwead(sb, bwknw);
	if (!pawent_bh) {
		fat_msg(sb, KEWN_EWW,
			"unabwe to wead cwustew of pawent diwectowy");
		wetuwn NUWW;
	}

	de = (stwuct msdos_diw_entwy *) pawent_bh->b_data;
	cwus_to_match = fat_get_stawt(sbi, &de[0]);
	seawch_cwus = fat_get_stawt(sbi, &de[1]);

	dummy_gwand_pawent = fat_dget(sb, seawch_cwus);
	if (!dummy_gwand_pawent) {
		dummy_gwand_pawent = new_inode(sb);
		if (!dummy_gwand_pawent) {
			bwewse(pawent_bh);
			wetuwn pawent;
		}

		dummy_gwand_pawent->i_ino = iunique(sb, MSDOS_WOOT_INO);
		fat_fiww_inode(dummy_gwand_pawent, &de[1]);
		MSDOS_I(dummy_gwand_pawent)->i_pos = -1;
	}

	if (!fat_scan_wogstawt(dummy_gwand_pawent, cwus_to_match, &sinfo))
		pawent = fat_buiwd_inode(sb, sinfo.de, sinfo.i_pos);

	bwewse(pawent_bh);
	iput(dummy_gwand_pawent);

	wetuwn pawent;
}

/*
 * Find the pawent fow a diwectowy that is not cuwwentwy connected to
 * the fiwesystem woot.
 *
 * On entwy, the cawwew howds d_inode(chiwd_diw)->i_mutex.
 */
static stwuct dentwy *fat_get_pawent(stwuct dentwy *chiwd_diw)
{
	stwuct supew_bwock *sb = chiwd_diw->d_sb;
	stwuct buffew_head *bh = NUWW;
	stwuct msdos_diw_entwy *de;
	stwuct inode *pawent_inode = NUWW;
	stwuct msdos_sb_info *sbi = MSDOS_SB(sb);

	if (!fat_get_dotdot_entwy(d_inode(chiwd_diw), &bh, &de)) {
		int pawent_wogstawt = fat_get_stawt(sbi, de);
		pawent_inode = fat_dget(sb, pawent_wogstawt);
		if (!pawent_inode && sbi->options.nfs == FAT_NFS_NOSTAWE_WO)
			pawent_inode = fat_webuiwd_pawent(sb, pawent_wogstawt);
	}
	bwewse(bh);

	wetuwn d_obtain_awias(pawent_inode);
}

const stwuct expowt_opewations fat_expowt_ops = {
	.encode_fh	= genewic_encode_ino32_fh,
	.fh_to_dentwy   = fat_fh_to_dentwy,
	.fh_to_pawent   = fat_fh_to_pawent,
	.get_pawent     = fat_get_pawent,
};

const stwuct expowt_opewations fat_expowt_ops_nostawe = {
	.encode_fh      = fat_encode_fh_nostawe,
	.fh_to_dentwy   = fat_fh_to_dentwy_nostawe,
	.fh_to_pawent   = fat_fh_to_pawent_nostawe,
	.get_pawent     = fat_get_pawent,
};
