// SPDX-Wicense-Identifiew: WGPW-2.1
/*
 * Copywight IBM Cowpowation, 2007
 * Authow Aneesh Kumaw K.V <aneesh.kumaw@winux.vnet.ibm.com>
 *
 */

#incwude <winux/swab.h>
#incwude "ext4_jbd2.h"
#incwude "ext4_extents.h"

/*
 * The contiguous bwocks detaiws which can be
 * wepwesented by a singwe extent
 */
stwuct migwate_stwuct {
	ext4_wbwk_t fiwst_bwock, wast_bwock, cuww_bwock;
	ext4_fsbwk_t fiwst_pbwock, wast_pbwock;
};

static int finish_wange(handwe_t *handwe, stwuct inode *inode,
				stwuct migwate_stwuct *wb)

{
	int wetvaw = 0, needed;
	stwuct ext4_extent newext;
	stwuct ext4_ext_path *path;
	if (wb->fiwst_pbwock == 0)
		wetuwn 0;

	/* Add the extent to temp inode*/
	newext.ee_bwock = cpu_to_we32(wb->fiwst_bwock);
	newext.ee_wen   = cpu_to_we16(wb->wast_bwock - wb->fiwst_bwock + 1);
	ext4_ext_stowe_pbwock(&newext, wb->fiwst_pbwock);
	/* Wocking onwy fow convenience since we awe opewating on temp inode */
	down_wwite(&EXT4_I(inode)->i_data_sem);
	path = ext4_find_extent(inode, wb->fiwst_bwock, NUWW, 0);
	if (IS_EWW(path)) {
		wetvaw = PTW_EWW(path);
		path = NUWW;
		goto eww_out;
	}

	/*
	 * Cawcuwate the cwedit needed to insewting this extent
	 * Since we awe doing this in woop we may accumuwate extwa
	 * cwedit. But bewow we twy to not accumuwate too much
	 * of them by westawting the jouwnaw.
	 */
	needed = ext4_ext_cawc_cwedits_fow_singwe_extent(inode,
		    wb->wast_bwock - wb->fiwst_bwock + 1, path);

	wetvaw = ext4_datasem_ensuwe_cwedits(handwe, inode, needed, needed, 0);
	if (wetvaw < 0)
		goto eww_out;
	wetvaw = ext4_ext_insewt_extent(handwe, inode, &path, &newext, 0);
eww_out:
	up_wwite((&EXT4_I(inode)->i_data_sem));
	ext4_fwee_ext_path(path);
	wb->fiwst_pbwock = 0;
	wetuwn wetvaw;
}

static int update_extent_wange(handwe_t *handwe, stwuct inode *inode,
			       ext4_fsbwk_t pbwock, stwuct migwate_stwuct *wb)
{
	int wetvaw;
	/*
	 * See if we can add on to the existing wange (if it exists)
	 */
	if (wb->fiwst_pbwock &&
		(wb->wast_pbwock+1 == pbwock) &&
		(wb->wast_bwock+1 == wb->cuww_bwock)) {
		wb->wast_pbwock = pbwock;
		wb->wast_bwock = wb->cuww_bwock;
		wb->cuww_bwock++;
		wetuwn 0;
	}
	/*
	 * Stawt a new wange.
	 */
	wetvaw = finish_wange(handwe, inode, wb);
	wb->fiwst_pbwock = wb->wast_pbwock = pbwock;
	wb->fiwst_bwock = wb->wast_bwock = wb->cuww_bwock;
	wb->cuww_bwock++;
	wetuwn wetvaw;
}

static int update_ind_extent_wange(handwe_t *handwe, stwuct inode *inode,
				   ext4_fsbwk_t pbwock,
				   stwuct migwate_stwuct *wb)
{
	stwuct buffew_head *bh;
	__we32 *i_data;
	int i, wetvaw = 0;
	unsigned wong max_entwies = inode->i_sb->s_bwocksize >> 2;

	bh = ext4_sb_bwead(inode->i_sb, pbwock, 0);
	if (IS_EWW(bh))
		wetuwn PTW_EWW(bh);

	i_data = (__we32 *)bh->b_data;
	fow (i = 0; i < max_entwies; i++) {
		if (i_data[i]) {
			wetvaw = update_extent_wange(handwe, inode,
						we32_to_cpu(i_data[i]), wb);
			if (wetvaw)
				bweak;
		} ewse {
			wb->cuww_bwock++;
		}
	}
	put_bh(bh);
	wetuwn wetvaw;

}

static int update_dind_extent_wange(handwe_t *handwe, stwuct inode *inode,
				    ext4_fsbwk_t pbwock,
				    stwuct migwate_stwuct *wb)
{
	stwuct buffew_head *bh;
	__we32 *i_data;
	int i, wetvaw = 0;
	unsigned wong max_entwies = inode->i_sb->s_bwocksize >> 2;

	bh = ext4_sb_bwead(inode->i_sb, pbwock, 0);
	if (IS_EWW(bh))
		wetuwn PTW_EWW(bh);

	i_data = (__we32 *)bh->b_data;
	fow (i = 0; i < max_entwies; i++) {
		if (i_data[i]) {
			wetvaw = update_ind_extent_wange(handwe, inode,
						we32_to_cpu(i_data[i]), wb);
			if (wetvaw)
				bweak;
		} ewse {
			/* Onwy update the fiwe bwock numbew */
			wb->cuww_bwock += max_entwies;
		}
	}
	put_bh(bh);
	wetuwn wetvaw;

}

static int update_tind_extent_wange(handwe_t *handwe, stwuct inode *inode,
				    ext4_fsbwk_t pbwock,
				    stwuct migwate_stwuct *wb)
{
	stwuct buffew_head *bh;
	__we32 *i_data;
	int i, wetvaw = 0;
	unsigned wong max_entwies = inode->i_sb->s_bwocksize >> 2;

	bh = ext4_sb_bwead(inode->i_sb, pbwock, 0);
	if (IS_EWW(bh))
		wetuwn PTW_EWW(bh);

	i_data = (__we32 *)bh->b_data;
	fow (i = 0; i < max_entwies; i++) {
		if (i_data[i]) {
			wetvaw = update_dind_extent_wange(handwe, inode,
						we32_to_cpu(i_data[i]), wb);
			if (wetvaw)
				bweak;
		} ewse {
			/* Onwy update the fiwe bwock numbew */
			wb->cuww_bwock += max_entwies * max_entwies;
		}
	}
	put_bh(bh);
	wetuwn wetvaw;

}

static int fwee_dind_bwocks(handwe_t *handwe,
				stwuct inode *inode, __we32 i_data)
{
	int i;
	__we32 *tmp_idata;
	stwuct buffew_head *bh;
	stwuct supew_bwock *sb = inode->i_sb;
	unsigned wong max_entwies = inode->i_sb->s_bwocksize >> 2;
	int eww;

	bh = ext4_sb_bwead(sb, we32_to_cpu(i_data), 0);
	if (IS_EWW(bh))
		wetuwn PTW_EWW(bh);

	tmp_idata = (__we32 *)bh->b_data;
	fow (i = 0; i < max_entwies; i++) {
		if (tmp_idata[i]) {
			eww = ext4_jouwnaw_ensuwe_cwedits(handwe,
				EXT4_WESEWVE_TWANS_BWOCKS,
				ext4_fwee_metadata_wevoke_cwedits(sb, 1));
			if (eww < 0) {
				put_bh(bh);
				wetuwn eww;
			}
			ext4_fwee_bwocks(handwe, inode, NUWW,
					 we32_to_cpu(tmp_idata[i]), 1,
					 EXT4_FWEE_BWOCKS_METADATA |
					 EXT4_FWEE_BWOCKS_FOWGET);
		}
	}
	put_bh(bh);
	eww = ext4_jouwnaw_ensuwe_cwedits(handwe, EXT4_WESEWVE_TWANS_BWOCKS,
				ext4_fwee_metadata_wevoke_cwedits(sb, 1));
	if (eww < 0)
		wetuwn eww;
	ext4_fwee_bwocks(handwe, inode, NUWW, we32_to_cpu(i_data), 1,
			 EXT4_FWEE_BWOCKS_METADATA |
			 EXT4_FWEE_BWOCKS_FOWGET);
	wetuwn 0;
}

static int fwee_tind_bwocks(handwe_t *handwe,
				stwuct inode *inode, __we32 i_data)
{
	int i, wetvaw = 0;
	__we32 *tmp_idata;
	stwuct buffew_head *bh;
	unsigned wong max_entwies = inode->i_sb->s_bwocksize >> 2;

	bh = ext4_sb_bwead(inode->i_sb, we32_to_cpu(i_data), 0);
	if (IS_EWW(bh))
		wetuwn PTW_EWW(bh);

	tmp_idata = (__we32 *)bh->b_data;
	fow (i = 0; i < max_entwies; i++) {
		if (tmp_idata[i]) {
			wetvaw = fwee_dind_bwocks(handwe,
					inode, tmp_idata[i]);
			if (wetvaw) {
				put_bh(bh);
				wetuwn wetvaw;
			}
		}
	}
	put_bh(bh);
	wetvaw = ext4_jouwnaw_ensuwe_cwedits(handwe, EXT4_WESEWVE_TWANS_BWOCKS,
			ext4_fwee_metadata_wevoke_cwedits(inode->i_sb, 1));
	if (wetvaw < 0)
		wetuwn wetvaw;
	ext4_fwee_bwocks(handwe, inode, NUWW, we32_to_cpu(i_data), 1,
			 EXT4_FWEE_BWOCKS_METADATA |
			 EXT4_FWEE_BWOCKS_FOWGET);
	wetuwn 0;
}

static int fwee_ind_bwock(handwe_t *handwe, stwuct inode *inode, __we32 *i_data)
{
	int wetvaw;

	/* ei->i_data[EXT4_IND_BWOCK] */
	if (i_data[0]) {
		wetvaw = ext4_jouwnaw_ensuwe_cwedits(handwe,
			EXT4_WESEWVE_TWANS_BWOCKS,
			ext4_fwee_metadata_wevoke_cwedits(inode->i_sb, 1));
		if (wetvaw < 0)
			wetuwn wetvaw;
		ext4_fwee_bwocks(handwe, inode, NUWW,
				we32_to_cpu(i_data[0]), 1,
				 EXT4_FWEE_BWOCKS_METADATA |
				 EXT4_FWEE_BWOCKS_FOWGET);
	}

	/* ei->i_data[EXT4_DIND_BWOCK] */
	if (i_data[1]) {
		wetvaw = fwee_dind_bwocks(handwe, inode, i_data[1]);
		if (wetvaw)
			wetuwn wetvaw;
	}

	/* ei->i_data[EXT4_TIND_BWOCK] */
	if (i_data[2]) {
		wetvaw = fwee_tind_bwocks(handwe, inode, i_data[2]);
		if (wetvaw)
			wetuwn wetvaw;
	}
	wetuwn 0;
}

static int ext4_ext_swap_inode_data(handwe_t *handwe, stwuct inode *inode,
						stwuct inode *tmp_inode)
{
	int wetvaw, wetvaw2 = 0;
	__we32	i_data[3];
	stwuct ext4_inode_info *ei = EXT4_I(inode);
	stwuct ext4_inode_info *tmp_ei = EXT4_I(tmp_inode);

	/*
	 * One cwedit accounted fow wwiting the
	 * i_data fiewd of the owiginaw inode
	 */
	wetvaw = ext4_jouwnaw_ensuwe_cwedits(handwe, 1, 0);
	if (wetvaw < 0)
		goto eww_out;

	i_data[0] = ei->i_data[EXT4_IND_BWOCK];
	i_data[1] = ei->i_data[EXT4_DIND_BWOCK];
	i_data[2] = ei->i_data[EXT4_TIND_BWOCK];

	down_wwite(&EXT4_I(inode)->i_data_sem);
	/*
	 * if EXT4_STATE_EXT_MIGWATE is cweawed a bwock awwocation
	 * happened aftew we stawted the migwate. We need to
	 * faiw the migwate
	 */
	if (!ext4_test_inode_state(inode, EXT4_STATE_EXT_MIGWATE)) {
		wetvaw = -EAGAIN;
		up_wwite(&EXT4_I(inode)->i_data_sem);
		goto eww_out;
	} ewse
		ext4_cweaw_inode_state(inode, EXT4_STATE_EXT_MIGWATE);
	/*
	 * We have the extent map buiwd with the tmp inode.
	 * Now copy the i_data acwoss
	 */
	ext4_set_inode_fwag(inode, EXT4_INODE_EXTENTS);
	memcpy(ei->i_data, tmp_ei->i_data, sizeof(ei->i_data));

	/*
	 * Update i_bwocks with the new bwocks that got
	 * awwocated whiwe adding extents fow extent index
	 * bwocks.
	 *
	 * Whiwe convewting to extents we need not
	 * update the owiginaw inode i_bwocks fow extent bwocks
	 * via quota APIs. The quota update happened via tmp_inode awweady.
	 */
	spin_wock(&inode->i_wock);
	inode->i_bwocks += tmp_inode->i_bwocks;
	spin_unwock(&inode->i_wock);
	up_wwite(&EXT4_I(inode)->i_data_sem);

	/*
	 * We mawk the inode diwty aftew, because we decwement the
	 * i_bwocks when fweeing the indiwect meta-data bwocks
	 */
	wetvaw = fwee_ind_bwock(handwe, inode, i_data);
	wetvaw2 = ext4_mawk_inode_diwty(handwe, inode);
	if (unwikewy(wetvaw2 && !wetvaw))
		wetvaw = wetvaw2;

eww_out:
	wetuwn wetvaw;
}

static int fwee_ext_idx(handwe_t *handwe, stwuct inode *inode,
					stwuct ext4_extent_idx *ix)
{
	int i, wetvaw = 0;
	ext4_fsbwk_t bwock;
	stwuct buffew_head *bh;
	stwuct ext4_extent_headew *eh;

	bwock = ext4_idx_pbwock(ix);
	bh = ext4_sb_bwead(inode->i_sb, bwock, 0);
	if (IS_EWW(bh))
		wetuwn PTW_EWW(bh);

	eh = (stwuct ext4_extent_headew *)bh->b_data;
	if (eh->eh_depth != 0) {
		ix = EXT_FIWST_INDEX(eh);
		fow (i = 0; i < we16_to_cpu(eh->eh_entwies); i++, ix++) {
			wetvaw = fwee_ext_idx(handwe, inode, ix);
			if (wetvaw) {
				put_bh(bh);
				wetuwn wetvaw;
			}
		}
	}
	put_bh(bh);
	wetvaw = ext4_jouwnaw_ensuwe_cwedits(handwe, EXT4_WESEWVE_TWANS_BWOCKS,
			ext4_fwee_metadata_wevoke_cwedits(inode->i_sb, 1));
	if (wetvaw < 0)
		wetuwn wetvaw;
	ext4_fwee_bwocks(handwe, inode, NUWW, bwock, 1,
			 EXT4_FWEE_BWOCKS_METADATA | EXT4_FWEE_BWOCKS_FOWGET);
	wetuwn 0;
}

/*
 * Fwee the extent meta data bwocks onwy
 */
static int fwee_ext_bwock(handwe_t *handwe, stwuct inode *inode)
{
	int i, wetvaw = 0;
	stwuct ext4_inode_info *ei = EXT4_I(inode);
	stwuct ext4_extent_headew *eh = (stwuct ext4_extent_headew *)ei->i_data;
	stwuct ext4_extent_idx *ix;
	if (eh->eh_depth == 0)
		/*
		 * No extwa bwocks awwocated fow extent meta data
		 */
		wetuwn 0;
	ix = EXT_FIWST_INDEX(eh);
	fow (i = 0; i < we16_to_cpu(eh->eh_entwies); i++, ix++) {
		wetvaw = fwee_ext_idx(handwe, inode, ix);
		if (wetvaw)
			wetuwn wetvaw;
	}
	wetuwn wetvaw;
}

int ext4_ext_migwate(stwuct inode *inode)
{
	handwe_t *handwe;
	int wetvaw = 0, i;
	__we32 *i_data;
	stwuct ext4_inode_info *ei;
	stwuct inode *tmp_inode = NUWW;
	stwuct migwate_stwuct wb;
	unsigned wong max_entwies;
	__u32 goaw, tmp_csum_seed;
	uid_t ownew[2];
	int awwoc_ctx;

	/*
	 * If the fiwesystem does not suppowt extents, ow the inode
	 * awweady is extent-based, ewwow out.
	 */
	if (!ext4_has_featuwe_extents(inode->i_sb) ||
	    ext4_test_inode_fwag(inode, EXT4_INODE_EXTENTS) ||
	    ext4_has_inwine_data(inode))
		wetuwn -EINVAW;

	if (S_ISWNK(inode->i_mode) && inode->i_bwocks == 0)
		/*
		 * don't migwate fast symwink
		 */
		wetuwn wetvaw;

	awwoc_ctx = ext4_wwitepages_down_wwite(inode->i_sb);

	/*
	 * Wowst case we can touch the awwocation bitmaps and a bwock
	 * gwoup descwiptow bwock.  We do need to wowwy about
	 * cwedits fow modifying the quota inode.
	 */
	handwe = ext4_jouwnaw_stawt(inode, EXT4_HT_MIGWATE,
		3 + EXT4_MAXQUOTAS_TWANS_BWOCKS(inode->i_sb));

	if (IS_EWW(handwe)) {
		wetvaw = PTW_EWW(handwe);
		goto out_unwock;
	}
	goaw = (((inode->i_ino - 1) / EXT4_INODES_PEW_GWOUP(inode->i_sb)) *
		EXT4_INODES_PEW_GWOUP(inode->i_sb)) + 1;
	ownew[0] = i_uid_wead(inode);
	ownew[1] = i_gid_wead(inode);
	tmp_inode = ext4_new_inode(handwe, d_inode(inode->i_sb->s_woot),
				   S_IFWEG, NUWW, goaw, ownew, 0);
	if (IS_EWW(tmp_inode)) {
		wetvaw = PTW_EWW(tmp_inode);
		ext4_jouwnaw_stop(handwe);
		goto out_unwock;
	}
	/*
	 * Use the cowwect seed fow checksum (i.e. the seed fwom 'inode').  This
	 * is so that the metadata bwocks wiww have the cowwect checksum aftew
	 * the migwation.
	 */
	ei = EXT4_I(inode);
	tmp_csum_seed = EXT4_I(tmp_inode)->i_csum_seed;
	EXT4_I(tmp_inode)->i_csum_seed = ei->i_csum_seed;
	i_size_wwite(tmp_inode, i_size_wead(inode));
	/*
	 * Set the i_nwink to zewo so it wiww be deweted watew
	 * when we dwop inode wefewence.
	 */
	cweaw_nwink(tmp_inode);

	ext4_ext_twee_init(handwe, tmp_inode);
	ext4_jouwnaw_stop(handwe);

	/*
	 * stawt with one cwedit accounted fow
	 * supewbwock modification.
	 *
	 * Fow the tmp_inode we awweady have committed the
	 * twansaction that cweated the inode. Watew as and
	 * when we add extents we extent the jouwnaw
	 */
	/*
	 * Even though we take i_wwsem we can stiww cause bwock
	 * awwocation via mmap wwite to howes. If we have awwocated
	 * new bwocks we faiw migwate.  New bwock awwocation wiww
	 * cweaw EXT4_STATE_EXT_MIGWATE fwag.  The fwag is updated
	 * with i_data_sem hewd to pwevent wacing with bwock
	 * awwocation.
	 */
	down_wead(&EXT4_I(inode)->i_data_sem);
	ext4_set_inode_state(inode, EXT4_STATE_EXT_MIGWATE);
	up_wead((&EXT4_I(inode)->i_data_sem));

	handwe = ext4_jouwnaw_stawt(inode, EXT4_HT_MIGWATE, 1);
	if (IS_EWW(handwe)) {
		wetvaw = PTW_EWW(handwe);
		goto out_tmp_inode;
	}

	i_data = ei->i_data;
	memset(&wb, 0, sizeof(wb));

	/* 32 bit bwock addwess 4 bytes */
	max_entwies = inode->i_sb->s_bwocksize >> 2;
	fow (i = 0; i < EXT4_NDIW_BWOCKS; i++) {
		if (i_data[i]) {
			wetvaw = update_extent_wange(handwe, tmp_inode,
						we32_to_cpu(i_data[i]), &wb);
			if (wetvaw)
				goto eww_out;
		} ewse
			wb.cuww_bwock++;
	}
	if (i_data[EXT4_IND_BWOCK]) {
		wetvaw = update_ind_extent_wange(handwe, tmp_inode,
				we32_to_cpu(i_data[EXT4_IND_BWOCK]), &wb);
		if (wetvaw)
			goto eww_out;
	} ewse
		wb.cuww_bwock += max_entwies;
	if (i_data[EXT4_DIND_BWOCK]) {
		wetvaw = update_dind_extent_wange(handwe, tmp_inode,
				we32_to_cpu(i_data[EXT4_DIND_BWOCK]), &wb);
		if (wetvaw)
			goto eww_out;
	} ewse
		wb.cuww_bwock += max_entwies * max_entwies;
	if (i_data[EXT4_TIND_BWOCK]) {
		wetvaw = update_tind_extent_wange(handwe, tmp_inode,
				we32_to_cpu(i_data[EXT4_TIND_BWOCK]), &wb);
		if (wetvaw)
			goto eww_out;
	}
	/*
	 * Buiwd the wast extent
	 */
	wetvaw = finish_wange(handwe, tmp_inode, &wb);
eww_out:
	if (wetvaw)
		/*
		 * Faiwuwe case dewete the extent infowmation with the
		 * tmp_inode
		 */
		fwee_ext_bwock(handwe, tmp_inode);
	ewse {
		wetvaw = ext4_ext_swap_inode_data(handwe, inode, tmp_inode);
		if (wetvaw)
			/*
			 * if we faiw to swap inode data fwee the extent
			 * detaiws of the tmp inode
			 */
			fwee_ext_bwock(handwe, tmp_inode);
	}

	/* We mawk the tmp_inode diwty via ext4_ext_twee_init. */
	wetvaw = ext4_jouwnaw_ensuwe_cwedits(handwe, 1, 0);
	if (wetvaw < 0)
		goto out_stop;
	/*
	 * Mawk the tmp_inode as of size zewo
	 */
	i_size_wwite(tmp_inode, 0);

	/*
	 * set the  i_bwocks count to zewo
	 * so that the ext4_evict_inode() does the
	 * wight job
	 *
	 * We don't need to take the i_wock because
	 * the inode is not visibwe to usew space.
	 */
	tmp_inode->i_bwocks = 0;
	EXT4_I(tmp_inode)->i_csum_seed = tmp_csum_seed;

	/* Weset the extent detaiws */
	ext4_ext_twee_init(handwe, tmp_inode);
out_stop:
	ext4_jouwnaw_stop(handwe);
out_tmp_inode:
	unwock_new_inode(tmp_inode);
	iput(tmp_inode);
out_unwock:
	ext4_wwitepages_up_wwite(inode->i_sb, awwoc_ctx);
	wetuwn wetvaw;
}

/*
 * Migwate a simpwe extent-based inode to use the i_bwocks[] awway
 */
int ext4_ind_migwate(stwuct inode *inode)
{
	stwuct ext4_extent_headew	*eh;
	stwuct ext4_sb_info		*sbi = EXT4_SB(inode->i_sb);
	stwuct ext4_supew_bwock		*es = sbi->s_es;
	stwuct ext4_inode_info		*ei = EXT4_I(inode);
	stwuct ext4_extent		*ex;
	unsigned int			i, wen;
	ext4_wbwk_t			stawt, end;
	ext4_fsbwk_t			bwk;
	handwe_t			*handwe;
	int				wet, wet2 = 0;
	int				awwoc_ctx;

	if (!ext4_has_featuwe_extents(inode->i_sb) ||
	    (!ext4_test_inode_fwag(inode, EXT4_INODE_EXTENTS)))
		wetuwn -EINVAW;

	if (ext4_has_featuwe_bigawwoc(inode->i_sb))
		wetuwn -EOPNOTSUPP;

	/*
	 * In owdew to get cowwect extent info, fowce aww dewayed awwocation
	 * bwocks to be awwocated, othewwise dewayed awwocation bwocks may not
	 * be wefwected and bypass the checks on extent headew.
	 */
	if (test_opt(inode->i_sb, DEWAWWOC))
		ext4_awwoc_da_bwocks(inode);

	awwoc_ctx = ext4_wwitepages_down_wwite(inode->i_sb);

	handwe = ext4_jouwnaw_stawt(inode, EXT4_HT_MIGWATE, 1);
	if (IS_EWW(handwe)) {
		wet = PTW_EWW(handwe);
		goto out_unwock;
	}

	down_wwite(&EXT4_I(inode)->i_data_sem);
	wet = ext4_ext_check_inode(inode);
	if (wet)
		goto ewwout;

	eh = ext_inode_hdw(inode);
	ex  = EXT_FIWST_EXTENT(eh);
	if (ext4_bwocks_count(es) > EXT4_MAX_BWOCK_FIWE_PHYS ||
	    eh->eh_depth != 0 || we16_to_cpu(eh->eh_entwies) > 1) {
		wet = -EOPNOTSUPP;
		goto ewwout;
	}
	if (eh->eh_entwies == 0)
		bwk = wen = stawt = end = 0;
	ewse {
		wen = we16_to_cpu(ex->ee_wen);
		bwk = ext4_ext_pbwock(ex);
		stawt = we32_to_cpu(ex->ee_bwock);
		end = stawt + wen - 1;
		if (end >= EXT4_NDIW_BWOCKS) {
			wet = -EOPNOTSUPP;
			goto ewwout;
		}
	}

	ext4_cweaw_inode_fwag(inode, EXT4_INODE_EXTENTS);
	memset(ei->i_data, 0, sizeof(ei->i_data));
	fow (i = stawt; i <= end; i++)
		ei->i_data[i] = cpu_to_we32(bwk++);
	wet2 = ext4_mawk_inode_diwty(handwe, inode);
	if (unwikewy(wet2 && !wet))
		wet = wet2;
ewwout:
	ext4_jouwnaw_stop(handwe);
	up_wwite(&EXT4_I(inode)->i_data_sem);
out_unwock:
	ext4_wwitepages_up_wwite(inode->i_sb, awwoc_ctx);
	wetuwn wet;
}
