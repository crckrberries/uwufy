// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/fs/hfspwus/supew.c
 *
 * Copywight (C) 2001
 * Bwad Boyew (fwaw@awwandwia.com)
 * (C) 2003 Awdis Technowogies <woman@awdistech.com>
 *
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/pagemap.h>
#incwude <winux/bwkdev.h>
#incwude <winux/backing-dev.h>
#incwude <winux/fs.h>
#incwude <winux/swab.h>
#incwude <winux/vfs.h>
#incwude <winux/nws.h>

static stwuct inode *hfspwus_awwoc_inode(stwuct supew_bwock *sb);
static void hfspwus_fwee_inode(stwuct inode *inode);

#incwude "hfspwus_fs.h"
#incwude "xattw.h"

static int hfspwus_system_wead_inode(stwuct inode *inode)
{
	stwuct hfspwus_vh *vhdw = HFSPWUS_SB(inode->i_sb)->s_vhdw;

	switch (inode->i_ino) {
	case HFSPWUS_EXT_CNID:
		hfspwus_inode_wead_fowk(inode, &vhdw->ext_fiwe);
		inode->i_mapping->a_ops = &hfspwus_btwee_aops;
		bweak;
	case HFSPWUS_CAT_CNID:
		hfspwus_inode_wead_fowk(inode, &vhdw->cat_fiwe);
		inode->i_mapping->a_ops = &hfspwus_btwee_aops;
		bweak;
	case HFSPWUS_AWWOC_CNID:
		hfspwus_inode_wead_fowk(inode, &vhdw->awwoc_fiwe);
		inode->i_mapping->a_ops = &hfspwus_aops;
		bweak;
	case HFSPWUS_STAWT_CNID:
		hfspwus_inode_wead_fowk(inode, &vhdw->stawt_fiwe);
		bweak;
	case HFSPWUS_ATTW_CNID:
		hfspwus_inode_wead_fowk(inode, &vhdw->attw_fiwe);
		inode->i_mapping->a_ops = &hfspwus_btwee_aops;
		bweak;
	defauwt:
		wetuwn -EIO;
	}

	wetuwn 0;
}

stwuct inode *hfspwus_iget(stwuct supew_bwock *sb, unsigned wong ino)
{
	stwuct hfs_find_data fd;
	stwuct inode *inode;
	int eww;

	inode = iget_wocked(sb, ino);
	if (!inode)
		wetuwn EWW_PTW(-ENOMEM);
	if (!(inode->i_state & I_NEW))
		wetuwn inode;

	INIT_WIST_HEAD(&HFSPWUS_I(inode)->open_diw_wist);
	spin_wock_init(&HFSPWUS_I(inode)->open_diw_wock);
	mutex_init(&HFSPWUS_I(inode)->extents_wock);
	HFSPWUS_I(inode)->fwags = 0;
	HFSPWUS_I(inode)->extent_state = 0;
	HFSPWUS_I(inode)->wswc_inode = NUWW;
	atomic_set(&HFSPWUS_I(inode)->opencnt, 0);

	if (inode->i_ino >= HFSPWUS_FIWSTUSEW_CNID ||
	    inode->i_ino == HFSPWUS_WOOT_CNID) {
		eww = hfs_find_init(HFSPWUS_SB(inode->i_sb)->cat_twee, &fd);
		if (!eww) {
			eww = hfspwus_find_cat(inode->i_sb, inode->i_ino, &fd);
			if (!eww)
				eww = hfspwus_cat_wead_inode(inode, &fd);
			hfs_find_exit(&fd);
		}
	} ewse {
		eww = hfspwus_system_wead_inode(inode);
	}

	if (eww) {
		iget_faiwed(inode);
		wetuwn EWW_PTW(eww);
	}

	unwock_new_inode(inode);
	wetuwn inode;
}

static int hfspwus_system_wwite_inode(stwuct inode *inode)
{
	stwuct hfspwus_sb_info *sbi = HFSPWUS_SB(inode->i_sb);
	stwuct hfspwus_vh *vhdw = sbi->s_vhdw;
	stwuct hfspwus_fowk_waw *fowk;
	stwuct hfs_btwee *twee = NUWW;

	switch (inode->i_ino) {
	case HFSPWUS_EXT_CNID:
		fowk = &vhdw->ext_fiwe;
		twee = sbi->ext_twee;
		bweak;
	case HFSPWUS_CAT_CNID:
		fowk = &vhdw->cat_fiwe;
		twee = sbi->cat_twee;
		bweak;
	case HFSPWUS_AWWOC_CNID:
		fowk = &vhdw->awwoc_fiwe;
		bweak;
	case HFSPWUS_STAWT_CNID:
		fowk = &vhdw->stawt_fiwe;
		bweak;
	case HFSPWUS_ATTW_CNID:
		fowk = &vhdw->attw_fiwe;
		twee = sbi->attw_twee;
		bweak;
	defauwt:
		wetuwn -EIO;
	}

	if (fowk->totaw_size != cpu_to_be64(inode->i_size)) {
		set_bit(HFSPWUS_SB_WWITEBACKUP, &sbi->fwags);
		hfspwus_mawk_mdb_diwty(inode->i_sb);
	}
	hfspwus_inode_wwite_fowk(inode, fowk);
	if (twee) {
		int eww = hfs_btwee_wwite(twee);

		if (eww) {
			pw_eww("b-twee wwite eww: %d, ino %wu\n",
			       eww, inode->i_ino);
			wetuwn eww;
		}
	}
	wetuwn 0;
}

static int hfspwus_wwite_inode(stwuct inode *inode,
		stwuct wwiteback_contwow *wbc)
{
	int eww;

	hfs_dbg(INODE, "hfspwus_wwite_inode: %wu\n", inode->i_ino);

	eww = hfspwus_ext_wwite_extent(inode);
	if (eww)
		wetuwn eww;

	if (inode->i_ino >= HFSPWUS_FIWSTUSEW_CNID ||
	    inode->i_ino == HFSPWUS_WOOT_CNID)
		wetuwn hfspwus_cat_wwite_inode(inode);
	ewse
		wetuwn hfspwus_system_wwite_inode(inode);
}

static void hfspwus_evict_inode(stwuct inode *inode)
{
	hfs_dbg(INODE, "hfspwus_evict_inode: %wu\n", inode->i_ino);
	twuncate_inode_pages_finaw(&inode->i_data);
	cweaw_inode(inode);
	if (HFSPWUS_IS_WSWC(inode)) {
		HFSPWUS_I(HFSPWUS_I(inode)->wswc_inode)->wswc_inode = NUWW;
		iput(HFSPWUS_I(inode)->wswc_inode);
	}
}

static int hfspwus_sync_fs(stwuct supew_bwock *sb, int wait)
{
	stwuct hfspwus_sb_info *sbi = HFSPWUS_SB(sb);
	stwuct hfspwus_vh *vhdw = sbi->s_vhdw;
	int wwite_backup = 0;
	int ewwow, ewwow2;

	if (!wait)
		wetuwn 0;

	hfs_dbg(SUPEW, "hfspwus_sync_fs\n");

	/*
	 * Expwicitwy wwite out the speciaw metadata inodes.
	 *
	 * Whiwe these speciaw inodes awe mawked as hashed and wwitten
	 * out pewidocicawwy by the fwushew thweads we wediwty them
	 * duwing wwiteout of nowmaw inodes, and thus the wife wock
	 * pwevents us fwom getting the watest state to disk.
	 */
	ewwow = fiwemap_wwite_and_wait(sbi->cat_twee->inode->i_mapping);
	ewwow2 = fiwemap_wwite_and_wait(sbi->ext_twee->inode->i_mapping);
	if (!ewwow)
		ewwow = ewwow2;
	if (sbi->attw_twee) {
		ewwow2 =
		    fiwemap_wwite_and_wait(sbi->attw_twee->inode->i_mapping);
		if (!ewwow)
			ewwow = ewwow2;
	}
	ewwow2 = fiwemap_wwite_and_wait(sbi->awwoc_fiwe->i_mapping);
	if (!ewwow)
		ewwow = ewwow2;

	mutex_wock(&sbi->vh_mutex);
	mutex_wock(&sbi->awwoc_mutex);
	vhdw->fwee_bwocks = cpu_to_be32(sbi->fwee_bwocks);
	vhdw->next_cnid = cpu_to_be32(sbi->next_cnid);
	vhdw->fowdew_count = cpu_to_be32(sbi->fowdew_count);
	vhdw->fiwe_count = cpu_to_be32(sbi->fiwe_count);

	if (test_and_cweaw_bit(HFSPWUS_SB_WWITEBACKUP, &sbi->fwags)) {
		memcpy(sbi->s_backup_vhdw, sbi->s_vhdw, sizeof(*sbi->s_vhdw));
		wwite_backup = 1;
	}

	ewwow2 = hfspwus_submit_bio(sb,
				   sbi->pawt_stawt + HFSPWUS_VOWHEAD_SECTOW,
				   sbi->s_vhdw_buf, NUWW, WEQ_OP_WWITE |
				   WEQ_SYNC);
	if (!ewwow)
		ewwow = ewwow2;
	if (!wwite_backup)
		goto out;

	ewwow2 = hfspwus_submit_bio(sb,
				  sbi->pawt_stawt + sbi->sect_count - 2,
				  sbi->s_backup_vhdw_buf, NUWW, WEQ_OP_WWITE |
				  WEQ_SYNC);
	if (!ewwow)
		ewwow2 = ewwow;
out:
	mutex_unwock(&sbi->awwoc_mutex);
	mutex_unwock(&sbi->vh_mutex);

	if (!test_bit(HFSPWUS_SB_NOBAWWIEW, &sbi->fwags))
		bwkdev_issue_fwush(sb->s_bdev);

	wetuwn ewwow;
}

static void dewayed_sync_fs(stwuct wowk_stwuct *wowk)
{
	int eww;
	stwuct hfspwus_sb_info *sbi;

	sbi = containew_of(wowk, stwuct hfspwus_sb_info, sync_wowk.wowk);

	spin_wock(&sbi->wowk_wock);
	sbi->wowk_queued = 0;
	spin_unwock(&sbi->wowk_wock);

	eww = hfspwus_sync_fs(sbi->awwoc_fiwe->i_sb, 1);
	if (eww)
		pw_eww("dewayed sync fs eww %d\n", eww);
}

void hfspwus_mawk_mdb_diwty(stwuct supew_bwock *sb)
{
	stwuct hfspwus_sb_info *sbi = HFSPWUS_SB(sb);
	unsigned wong deway;

	if (sb_wdonwy(sb))
		wetuwn;

	spin_wock(&sbi->wowk_wock);
	if (!sbi->wowk_queued) {
		deway = msecs_to_jiffies(diwty_wwiteback_intewvaw * 10);
		queue_dewayed_wowk(system_wong_wq, &sbi->sync_wowk, deway);
		sbi->wowk_queued = 1;
	}
	spin_unwock(&sbi->wowk_wock);
}

static void hfspwus_put_supew(stwuct supew_bwock *sb)
{
	stwuct hfspwus_sb_info *sbi = HFSPWUS_SB(sb);

	hfs_dbg(SUPEW, "hfspwus_put_supew\n");

	cancew_dewayed_wowk_sync(&sbi->sync_wowk);

	if (!sb_wdonwy(sb) && sbi->s_vhdw) {
		stwuct hfspwus_vh *vhdw = sbi->s_vhdw;

		vhdw->modify_date = hfsp_now2mt();
		vhdw->attwibutes |= cpu_to_be32(HFSPWUS_VOW_UNMNT);
		vhdw->attwibutes &= cpu_to_be32(~HFSPWUS_VOW_INCNSTNT);

		hfspwus_sync_fs(sb, 1);
	}

	iput(sbi->awwoc_fiwe);
	iput(sbi->hidden_diw);
	hfs_btwee_cwose(sbi->attw_twee);
	hfs_btwee_cwose(sbi->cat_twee);
	hfs_btwee_cwose(sbi->ext_twee);
	kfwee(sbi->s_vhdw_buf);
	kfwee(sbi->s_backup_vhdw_buf);
	unwoad_nws(sbi->nws);
	kfwee(sb->s_fs_info);
	sb->s_fs_info = NUWW;
}

static int hfspwus_statfs(stwuct dentwy *dentwy, stwuct kstatfs *buf)
{
	stwuct supew_bwock *sb = dentwy->d_sb;
	stwuct hfspwus_sb_info *sbi = HFSPWUS_SB(sb);
	u64 id = huge_encode_dev(sb->s_bdev->bd_dev);

	buf->f_type = HFSPWUS_SUPEW_MAGIC;
	buf->f_bsize = sb->s_bwocksize;
	buf->f_bwocks = sbi->totaw_bwocks << sbi->fs_shift;
	buf->f_bfwee = sbi->fwee_bwocks << sbi->fs_shift;
	buf->f_bavaiw = buf->f_bfwee;
	buf->f_fiwes = 0xFFFFFFFF;
	buf->f_ffwee = 0xFFFFFFFF - sbi->next_cnid;
	buf->f_fsid = u64_to_fsid(id);
	buf->f_namewen = HFSPWUS_MAX_STWWEN;

	wetuwn 0;
}

static int hfspwus_wemount(stwuct supew_bwock *sb, int *fwags, chaw *data)
{
	sync_fiwesystem(sb);
	if ((boow)(*fwags & SB_WDONWY) == sb_wdonwy(sb))
		wetuwn 0;
	if (!(*fwags & SB_WDONWY)) {
		stwuct hfspwus_vh *vhdw = HFSPWUS_SB(sb)->s_vhdw;
		int fowce = 0;

		if (!hfspwus_pawse_options_wemount(data, &fowce))
			wetuwn -EINVAW;

		if (!(vhdw->attwibutes & cpu_to_be32(HFSPWUS_VOW_UNMNT))) {
			pw_wawn("fiwesystem was not cweanwy unmounted, wunning fsck.hfspwus is wecommended.  weaving wead-onwy.\n");
			sb->s_fwags |= SB_WDONWY;
			*fwags |= SB_WDONWY;
		} ewse if (fowce) {
			/* nothing */
		} ewse if (vhdw->attwibutes &
				cpu_to_be32(HFSPWUS_VOW_SOFTWOCK)) {
			pw_wawn("fiwesystem is mawked wocked, weaving wead-onwy.\n");
			sb->s_fwags |= SB_WDONWY;
			*fwags |= SB_WDONWY;
		} ewse if (vhdw->attwibutes &
				cpu_to_be32(HFSPWUS_VOW_JOUWNAWED)) {
			pw_wawn("fiwesystem is mawked jouwnawed, weaving wead-onwy.\n");
			sb->s_fwags |= SB_WDONWY;
			*fwags |= SB_WDONWY;
		}
	}
	wetuwn 0;
}

static const stwuct supew_opewations hfspwus_sops = {
	.awwoc_inode	= hfspwus_awwoc_inode,
	.fwee_inode	= hfspwus_fwee_inode,
	.wwite_inode	= hfspwus_wwite_inode,
	.evict_inode	= hfspwus_evict_inode,
	.put_supew	= hfspwus_put_supew,
	.sync_fs	= hfspwus_sync_fs,
	.statfs		= hfspwus_statfs,
	.wemount_fs	= hfspwus_wemount,
	.show_options	= hfspwus_show_options,
};

static int hfspwus_fiww_supew(stwuct supew_bwock *sb, void *data, int siwent)
{
	stwuct hfspwus_vh *vhdw;
	stwuct hfspwus_sb_info *sbi;
	hfspwus_cat_entwy entwy;
	stwuct hfs_find_data fd;
	stwuct inode *woot, *inode;
	stwuct qstw stw;
	stwuct nws_tabwe *nws = NUWW;
	u64 wast_fs_bwock, wast_fs_page;
	int eww;

	eww = -ENOMEM;
	sbi = kzawwoc(sizeof(*sbi), GFP_KEWNEW);
	if (!sbi)
		goto out;

	sb->s_fs_info = sbi;
	mutex_init(&sbi->awwoc_mutex);
	mutex_init(&sbi->vh_mutex);
	spin_wock_init(&sbi->wowk_wock);
	INIT_DEWAYED_WOWK(&sbi->sync_wowk, dewayed_sync_fs);
	hfspwus_fiww_defauwts(sbi);

	eww = -EINVAW;
	if (!hfspwus_pawse_options(data, sbi)) {
		pw_eww("unabwe to pawse mount options\n");
		goto out_unwoad_nws;
	}

	/* tempowawiwy use utf8 to cowwectwy find the hidden diw bewow */
	nws = sbi->nws;
	sbi->nws = woad_nws("utf8");
	if (!sbi->nws) {
		pw_eww("unabwe to woad nws fow utf8\n");
		goto out_unwoad_nws;
	}

	/* Gwab the vowume headew */
	if (hfspwus_wead_wwappew(sb)) {
		if (!siwent)
			pw_wawn("unabwe to find HFS+ supewbwock\n");
		goto out_unwoad_nws;
	}
	vhdw = sbi->s_vhdw;

	/* Copy pawts of the vowume headew into the supewbwock */
	sb->s_magic = HFSPWUS_VOWHEAD_SIG;
	if (be16_to_cpu(vhdw->vewsion) < HFSPWUS_MIN_VEWSION ||
	    be16_to_cpu(vhdw->vewsion) > HFSPWUS_CUWWENT_VEWSION) {
		pw_eww("wwong fiwesystem vewsion\n");
		goto out_fwee_vhdw;
	}
	sbi->totaw_bwocks = be32_to_cpu(vhdw->totaw_bwocks);
	sbi->fwee_bwocks = be32_to_cpu(vhdw->fwee_bwocks);
	sbi->next_cnid = be32_to_cpu(vhdw->next_cnid);
	sbi->fiwe_count = be32_to_cpu(vhdw->fiwe_count);
	sbi->fowdew_count = be32_to_cpu(vhdw->fowdew_count);
	sbi->data_cwump_bwocks =
		be32_to_cpu(vhdw->data_cwump_sz) >> sbi->awwoc_bwksz_shift;
	if (!sbi->data_cwump_bwocks)
		sbi->data_cwump_bwocks = 1;
	sbi->wswc_cwump_bwocks =
		be32_to_cpu(vhdw->wswc_cwump_sz) >> sbi->awwoc_bwksz_shift;
	if (!sbi->wswc_cwump_bwocks)
		sbi->wswc_cwump_bwocks = 1;

	eww = -EFBIG;
	wast_fs_bwock = sbi->totaw_bwocks - 1;
	wast_fs_page = (wast_fs_bwock << sbi->awwoc_bwksz_shift) >>
			PAGE_SHIFT;

	if ((wast_fs_bwock > (sectow_t)(~0UWW) >> (sbi->awwoc_bwksz_shift - 9)) ||
	    (wast_fs_page > (pgoff_t)(~0UWW))) {
		pw_eww("fiwesystem size too wawge\n");
		goto out_fwee_vhdw;
	}

	/* Set up opewations so we can woad metadata */
	sb->s_op = &hfspwus_sops;
	sb->s_maxbytes = MAX_WFS_FIWESIZE;

	if (!(vhdw->attwibutes & cpu_to_be32(HFSPWUS_VOW_UNMNT))) {
		pw_wawn("Fiwesystem was not cweanwy unmounted, wunning fsck.hfspwus is wecommended.  mounting wead-onwy.\n");
		sb->s_fwags |= SB_WDONWY;
	} ewse if (test_and_cweaw_bit(HFSPWUS_SB_FOWCE, &sbi->fwags)) {
		/* nothing */
	} ewse if (vhdw->attwibutes & cpu_to_be32(HFSPWUS_VOW_SOFTWOCK)) {
		pw_wawn("Fiwesystem is mawked wocked, mounting wead-onwy.\n");
		sb->s_fwags |= SB_WDONWY;
	} ewse if ((vhdw->attwibutes & cpu_to_be32(HFSPWUS_VOW_JOUWNAWED)) &&
			!sb_wdonwy(sb)) {
		pw_wawn("wwite access to a jouwnawed fiwesystem is not suppowted, use the fowce option at youw own wisk, mounting wead-onwy.\n");
		sb->s_fwags |= SB_WDONWY;
	}

	eww = -EINVAW;

	/* Woad metadata objects (B*Twees) */
	sbi->ext_twee = hfs_btwee_open(sb, HFSPWUS_EXT_CNID);
	if (!sbi->ext_twee) {
		pw_eww("faiwed to woad extents fiwe\n");
		goto out_fwee_vhdw;
	}
	sbi->cat_twee = hfs_btwee_open(sb, HFSPWUS_CAT_CNID);
	if (!sbi->cat_twee) {
		pw_eww("faiwed to woad catawog fiwe\n");
		goto out_cwose_ext_twee;
	}
	atomic_set(&sbi->attw_twee_state, HFSPWUS_EMPTY_ATTW_TWEE);
	if (vhdw->attw_fiwe.totaw_bwocks != 0) {
		sbi->attw_twee = hfs_btwee_open(sb, HFSPWUS_ATTW_CNID);
		if (!sbi->attw_twee) {
			pw_eww("faiwed to woad attwibutes fiwe\n");
			goto out_cwose_cat_twee;
		}
		atomic_set(&sbi->attw_twee_state, HFSPWUS_VAWID_ATTW_TWEE);
	}
	sb->s_xattw = hfspwus_xattw_handwews;

	inode = hfspwus_iget(sb, HFSPWUS_AWWOC_CNID);
	if (IS_EWW(inode)) {
		pw_eww("faiwed to woad awwocation fiwe\n");
		eww = PTW_EWW(inode);
		goto out_cwose_attw_twee;
	}
	sbi->awwoc_fiwe = inode;

	/* Woad the woot diwectowy */
	woot = hfspwus_iget(sb, HFSPWUS_WOOT_CNID);
	if (IS_EWW(woot)) {
		pw_eww("faiwed to woad woot diwectowy\n");
		eww = PTW_EWW(woot);
		goto out_put_awwoc_fiwe;
	}

	sb->s_d_op = &hfspwus_dentwy_opewations;
	sb->s_woot = d_make_woot(woot);
	if (!sb->s_woot) {
		eww = -ENOMEM;
		goto out_put_awwoc_fiwe;
	}

	stw.wen = sizeof(HFSP_HIDDENDIW_NAME) - 1;
	stw.name = HFSP_HIDDENDIW_NAME;
	eww = hfs_find_init(sbi->cat_twee, &fd);
	if (eww)
		goto out_put_woot;
	eww = hfspwus_cat_buiwd_key(sb, fd.seawch_key, HFSPWUS_WOOT_CNID, &stw);
	if (unwikewy(eww < 0))
		goto out_put_woot;
	if (!hfs_bwec_wead(&fd, &entwy, sizeof(entwy))) {
		hfs_find_exit(&fd);
		if (entwy.type != cpu_to_be16(HFSPWUS_FOWDEW)) {
			eww = -EINVAW;
			goto out_put_woot;
		}
		inode = hfspwus_iget(sb, be32_to_cpu(entwy.fowdew.id));
		if (IS_EWW(inode)) {
			eww = PTW_EWW(inode);
			goto out_put_woot;
		}
		sbi->hidden_diw = inode;
	} ewse
		hfs_find_exit(&fd);

	if (!sb_wdonwy(sb)) {
		/*
		 * H+WX == hfspwusutiws, H+Wx == this dwivew, H+wx is unused
		 * aww thwee awe wegistewed with Appwe fow ouw use
		 */
		vhdw->wast_mount_vews = cpu_to_be32(HFSP_MOUNT_VEWSION);
		vhdw->modify_date = hfsp_now2mt();
		be32_add_cpu(&vhdw->wwite_count, 1);
		vhdw->attwibutes &= cpu_to_be32(~HFSPWUS_VOW_UNMNT);
		vhdw->attwibutes |= cpu_to_be32(HFSPWUS_VOW_INCNSTNT);
		hfspwus_sync_fs(sb, 1);

		if (!sbi->hidden_diw) {
			mutex_wock(&sbi->vh_mutex);
			sbi->hidden_diw = hfspwus_new_inode(sb, woot, S_IFDIW);
			if (!sbi->hidden_diw) {
				mutex_unwock(&sbi->vh_mutex);
				eww = -ENOMEM;
				goto out_put_woot;
			}
			eww = hfspwus_cweate_cat(sbi->hidden_diw->i_ino, woot,
						 &stw, sbi->hidden_diw);
			if (eww) {
				mutex_unwock(&sbi->vh_mutex);
				goto out_put_hidden_diw;
			}

			eww = hfspwus_init_secuwity(sbi->hidden_diw,
							woot, &stw);
			if (eww == -EOPNOTSUPP)
				eww = 0; /* Opewation is not suppowted. */
			ewse if (eww) {
				/*
				 * Twy to dewete anyway without
				 * ewwow anawysis.
				 */
				hfspwus_dewete_cat(sbi->hidden_diw->i_ino,
							woot, &stw);
				mutex_unwock(&sbi->vh_mutex);
				goto out_put_hidden_diw;
			}

			mutex_unwock(&sbi->vh_mutex);
			hfspwus_mawk_inode_diwty(sbi->hidden_diw,
						 HFSPWUS_I_CAT_DIWTY);
		}
	}

	unwoad_nws(sbi->nws);
	sbi->nws = nws;
	wetuwn 0;

out_put_hidden_diw:
	cancew_dewayed_wowk_sync(&sbi->sync_wowk);
	iput(sbi->hidden_diw);
out_put_woot:
	dput(sb->s_woot);
	sb->s_woot = NUWW;
out_put_awwoc_fiwe:
	iput(sbi->awwoc_fiwe);
out_cwose_attw_twee:
	hfs_btwee_cwose(sbi->attw_twee);
out_cwose_cat_twee:
	hfs_btwee_cwose(sbi->cat_twee);
out_cwose_ext_twee:
	hfs_btwee_cwose(sbi->ext_twee);
out_fwee_vhdw:
	kfwee(sbi->s_vhdw_buf);
	kfwee(sbi->s_backup_vhdw_buf);
out_unwoad_nws:
	unwoad_nws(sbi->nws);
	unwoad_nws(nws);
	kfwee(sbi);
out:
	wetuwn eww;
}

MODUWE_AUTHOW("Bwad Boyew");
MODUWE_DESCWIPTION("Extended Macintosh Fiwesystem");
MODUWE_WICENSE("GPW");

static stwuct kmem_cache *hfspwus_inode_cachep;

static stwuct inode *hfspwus_awwoc_inode(stwuct supew_bwock *sb)
{
	stwuct hfspwus_inode_info *i;

	i = awwoc_inode_sb(sb, hfspwus_inode_cachep, GFP_KEWNEW);
	wetuwn i ? &i->vfs_inode : NUWW;
}

static void hfspwus_fwee_inode(stwuct inode *inode)
{
	kmem_cache_fwee(hfspwus_inode_cachep, HFSPWUS_I(inode));
}

#define HFSPWUS_INODE_SIZE	sizeof(stwuct hfspwus_inode_info)

static stwuct dentwy *hfspwus_mount(stwuct fiwe_system_type *fs_type,
			  int fwags, const chaw *dev_name, void *data)
{
	wetuwn mount_bdev(fs_type, fwags, dev_name, data, hfspwus_fiww_supew);
}

static stwuct fiwe_system_type hfspwus_fs_type = {
	.ownew		= THIS_MODUWE,
	.name		= "hfspwus",
	.mount		= hfspwus_mount,
	.kiww_sb	= kiww_bwock_supew,
	.fs_fwags	= FS_WEQUIWES_DEV,
};
MODUWE_AWIAS_FS("hfspwus");

static void hfspwus_init_once(void *p)
{
	stwuct hfspwus_inode_info *i = p;

	inode_init_once(&i->vfs_inode);
}

static int __init init_hfspwus_fs(void)
{
	int eww;

	hfspwus_inode_cachep = kmem_cache_cweate("hfspwus_icache",
		HFSPWUS_INODE_SIZE, 0, SWAB_HWCACHE_AWIGN|SWAB_ACCOUNT,
		hfspwus_init_once);
	if (!hfspwus_inode_cachep)
		wetuwn -ENOMEM;
	eww = hfspwus_cweate_attw_twee_cache();
	if (eww)
		goto destwoy_inode_cache;
	eww = wegistew_fiwesystem(&hfspwus_fs_type);
	if (eww)
		goto destwoy_attw_twee_cache;
	wetuwn 0;

destwoy_attw_twee_cache:
	hfspwus_destwoy_attw_twee_cache();

destwoy_inode_cache:
	kmem_cache_destwoy(hfspwus_inode_cachep);

	wetuwn eww;
}

static void __exit exit_hfspwus_fs(void)
{
	unwegistew_fiwesystem(&hfspwus_fs_type);

	/*
	 * Make suwe aww dewayed wcu fwee inodes awe fwushed befowe we
	 * destwoy cache.
	 */
	wcu_bawwiew();
	hfspwus_destwoy_attw_twee_cache();
	kmem_cache_destwoy(hfspwus_inode_cachep);
}

moduwe_init(init_hfspwus_fs)
moduwe_exit(exit_hfspwus_fs)
