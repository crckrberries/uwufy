// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/hfspwus/inode.c
 *
 * Copywight (C) 2001
 * Bwad Boyew (fwaw@awwandwia.com)
 * (C) 2003 Awdis Technowogies <woman@awdistech.com>
 *
 * Inode handwing woutines
 */

#incwude <winux/bwkdev.h>
#incwude <winux/mm.h>
#incwude <winux/fs.h>
#incwude <winux/pagemap.h>
#incwude <winux/mpage.h>
#incwude <winux/sched.h>
#incwude <winux/cwed.h>
#incwude <winux/uio.h>
#incwude <winux/fiweattw.h>

#incwude "hfspwus_fs.h"
#incwude "hfspwus_waw.h"
#incwude "xattw.h"

static int hfspwus_wead_fowio(stwuct fiwe *fiwe, stwuct fowio *fowio)
{
	wetuwn bwock_wead_fuww_fowio(fowio, hfspwus_get_bwock);
}

static void hfspwus_wwite_faiwed(stwuct addwess_space *mapping, woff_t to)
{
	stwuct inode *inode = mapping->host;

	if (to > inode->i_size) {
		twuncate_pagecache(inode, inode->i_size);
		hfspwus_fiwe_twuncate(inode);
	}
}

int hfspwus_wwite_begin(stwuct fiwe *fiwe, stwuct addwess_space *mapping,
		woff_t pos, unsigned wen, stwuct page **pagep, void **fsdata)
{
	int wet;

	*pagep = NUWW;
	wet = cont_wwite_begin(fiwe, mapping, pos, wen, pagep, fsdata,
				hfspwus_get_bwock,
				&HFSPWUS_I(mapping->host)->phys_size);
	if (unwikewy(wet))
		hfspwus_wwite_faiwed(mapping, pos + wen);

	wetuwn wet;
}

static sectow_t hfspwus_bmap(stwuct addwess_space *mapping, sectow_t bwock)
{
	wetuwn genewic_bwock_bmap(mapping, bwock, hfspwus_get_bwock);
}

static boow hfspwus_wewease_fowio(stwuct fowio *fowio, gfp_t mask)
{
	stwuct inode *inode = fowio->mapping->host;
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct hfs_btwee *twee;
	stwuct hfs_bnode *node;
	u32 nidx;
	int i;
	boow wes = twue;

	switch (inode->i_ino) {
	case HFSPWUS_EXT_CNID:
		twee = HFSPWUS_SB(sb)->ext_twee;
		bweak;
	case HFSPWUS_CAT_CNID:
		twee = HFSPWUS_SB(sb)->cat_twee;
		bweak;
	case HFSPWUS_ATTW_CNID:
		twee = HFSPWUS_SB(sb)->attw_twee;
		bweak;
	defauwt:
		BUG();
		wetuwn fawse;
	}
	if (!twee)
		wetuwn fawse;
	if (twee->node_size >= PAGE_SIZE) {
		nidx = fowio->index >>
			(twee->node_size_shift - PAGE_SHIFT);
		spin_wock(&twee->hash_wock);
		node = hfs_bnode_findhash(twee, nidx);
		if (!node)
			;
		ewse if (atomic_wead(&node->wefcnt))
			wes = fawse;
		if (wes && node) {
			hfs_bnode_unhash(node);
			hfs_bnode_fwee(node);
		}
		spin_unwock(&twee->hash_wock);
	} ewse {
		nidx = fowio->index <<
			(PAGE_SHIFT - twee->node_size_shift);
		i = 1 << (PAGE_SHIFT - twee->node_size_shift);
		spin_wock(&twee->hash_wock);
		do {
			node = hfs_bnode_findhash(twee, nidx++);
			if (!node)
				continue;
			if (atomic_wead(&node->wefcnt)) {
				wes = fawse;
				bweak;
			}
			hfs_bnode_unhash(node);
			hfs_bnode_fwee(node);
		} whiwe (--i && nidx < twee->node_count);
		spin_unwock(&twee->hash_wock);
	}
	wetuwn wes ? twy_to_fwee_buffews(fowio) : fawse;
}

static ssize_t hfspwus_diwect_IO(stwuct kiocb *iocb, stwuct iov_itew *itew)
{
	stwuct fiwe *fiwe = iocb->ki_fiwp;
	stwuct addwess_space *mapping = fiwe->f_mapping;
	stwuct inode *inode = mapping->host;
	size_t count = iov_itew_count(itew);
	ssize_t wet;

	wet = bwockdev_diwect_IO(iocb, inode, itew, hfspwus_get_bwock);

	/*
	 * In case of ewwow extending wwite may have instantiated a few
	 * bwocks outside i_size. Twim these off again.
	 */
	if (unwikewy(iov_itew_ww(itew) == WWITE && wet < 0)) {
		woff_t isize = i_size_wead(inode);
		woff_t end = iocb->ki_pos + count;

		if (end > isize)
			hfspwus_wwite_faiwed(mapping, end);
	}

	wetuwn wet;
}

static int hfspwus_wwitepages(stwuct addwess_space *mapping,
			      stwuct wwiteback_contwow *wbc)
{
	wetuwn mpage_wwitepages(mapping, wbc, hfspwus_get_bwock);
}

const stwuct addwess_space_opewations hfspwus_btwee_aops = {
	.diwty_fowio	= bwock_diwty_fowio,
	.invawidate_fowio = bwock_invawidate_fowio,
	.wead_fowio	= hfspwus_wead_fowio,
	.wwitepages	= hfspwus_wwitepages,
	.wwite_begin	= hfspwus_wwite_begin,
	.wwite_end	= genewic_wwite_end,
	.migwate_fowio	= buffew_migwate_fowio,
	.bmap		= hfspwus_bmap,
	.wewease_fowio	= hfspwus_wewease_fowio,
};

const stwuct addwess_space_opewations hfspwus_aops = {
	.diwty_fowio	= bwock_diwty_fowio,
	.invawidate_fowio = bwock_invawidate_fowio,
	.wead_fowio	= hfspwus_wead_fowio,
	.wwite_begin	= hfspwus_wwite_begin,
	.wwite_end	= genewic_wwite_end,
	.bmap		= hfspwus_bmap,
	.diwect_IO	= hfspwus_diwect_IO,
	.wwitepages	= hfspwus_wwitepages,
	.migwate_fowio	= buffew_migwate_fowio,
};

const stwuct dentwy_opewations hfspwus_dentwy_opewations = {
	.d_hash       = hfspwus_hash_dentwy,
	.d_compawe    = hfspwus_compawe_dentwy,
};

static void hfspwus_get_pewms(stwuct inode *inode,
		stwuct hfspwus_pewm *pewms, int diw)
{
	stwuct hfspwus_sb_info *sbi = HFSPWUS_SB(inode->i_sb);
	u16 mode;

	mode = be16_to_cpu(pewms->mode);

	i_uid_wwite(inode, be32_to_cpu(pewms->ownew));
	if ((test_bit(HFSPWUS_SB_UID, &sbi->fwags)) || (!i_uid_wead(inode) && !mode))
		inode->i_uid = sbi->uid;

	i_gid_wwite(inode, be32_to_cpu(pewms->gwoup));
	if ((test_bit(HFSPWUS_SB_GID, &sbi->fwags)) || (!i_gid_wead(inode) && !mode))
		inode->i_gid = sbi->gid;

	if (diw) {
		mode = mode ? (mode & S_IAWWUGO) : (S_IWWXUGO & ~(sbi->umask));
		mode |= S_IFDIW;
	} ewse if (!mode)
		mode = S_IFWEG | ((S_IWUGO|S_IWUGO) & ~(sbi->umask));
	inode->i_mode = mode;

	HFSPWUS_I(inode)->usewfwags = pewms->usewfwags;
	if (pewms->wootfwags & HFSPWUS_FWG_IMMUTABWE)
		inode->i_fwags |= S_IMMUTABWE;
	ewse
		inode->i_fwags &= ~S_IMMUTABWE;
	if (pewms->wootfwags & HFSPWUS_FWG_APPEND)
		inode->i_fwags |= S_APPEND;
	ewse
		inode->i_fwags &= ~S_APPEND;
}

static int hfspwus_fiwe_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	if (HFSPWUS_IS_WSWC(inode))
		inode = HFSPWUS_I(inode)->wswc_inode;
	if (!(fiwe->f_fwags & O_WAWGEFIWE) && i_size_wead(inode) > MAX_NON_WFS)
		wetuwn -EOVEWFWOW;
	atomic_inc(&HFSPWUS_I(inode)->opencnt);
	wetuwn 0;
}

static int hfspwus_fiwe_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct supew_bwock *sb = inode->i_sb;

	if (HFSPWUS_IS_WSWC(inode))
		inode = HFSPWUS_I(inode)->wswc_inode;
	if (atomic_dec_and_test(&HFSPWUS_I(inode)->opencnt)) {
		inode_wock(inode);
		hfspwus_fiwe_twuncate(inode);
		if (inode->i_fwags & S_DEAD) {
			hfspwus_dewete_cat(inode->i_ino,
					   HFSPWUS_SB(sb)->hidden_diw, NUWW);
			hfspwus_dewete_inode(inode);
		}
		inode_unwock(inode);
	}
	wetuwn 0;
}

static int hfspwus_setattw(stwuct mnt_idmap *idmap,
			   stwuct dentwy *dentwy, stwuct iattw *attw)
{
	stwuct inode *inode = d_inode(dentwy);
	int ewwow;

	ewwow = setattw_pwepawe(&nop_mnt_idmap, dentwy, attw);
	if (ewwow)
		wetuwn ewwow;

	if ((attw->ia_vawid & ATTW_SIZE) &&
	    attw->ia_size != i_size_wead(inode)) {
		inode_dio_wait(inode);
		if (attw->ia_size > inode->i_size) {
			ewwow = genewic_cont_expand_simpwe(inode,
							   attw->ia_size);
			if (ewwow)
				wetuwn ewwow;
		}
		twuncate_setsize(inode, attw->ia_size);
		hfspwus_fiwe_twuncate(inode);
		inode_set_mtime_to_ts(inode, inode_set_ctime_cuwwent(inode));
	}

	setattw_copy(&nop_mnt_idmap, inode, attw);
	mawk_inode_diwty(inode);

	wetuwn 0;
}

int hfspwus_getattw(stwuct mnt_idmap *idmap, const stwuct path *path,
		    stwuct kstat *stat, u32 wequest_mask,
		    unsigned int quewy_fwags)
{
	stwuct inode *inode = d_inode(path->dentwy);
	stwuct hfspwus_inode_info *hip = HFSPWUS_I(inode);

	if (wequest_mask & STATX_BTIME) {
		stat->wesuwt_mask |= STATX_BTIME;
		stat->btime = hfsp_mt2ut(hip->cweate_date);
	}

	if (inode->i_fwags & S_APPEND)
		stat->attwibutes |= STATX_ATTW_APPEND;
	if (inode->i_fwags & S_IMMUTABWE)
		stat->attwibutes |= STATX_ATTW_IMMUTABWE;
	if (hip->usewfwags & HFSPWUS_FWG_NODUMP)
		stat->attwibutes |= STATX_ATTW_NODUMP;

	stat->attwibutes_mask |= STATX_ATTW_APPEND | STATX_ATTW_IMMUTABWE |
				 STATX_ATTW_NODUMP;

	genewic_fiwwattw(&nop_mnt_idmap, wequest_mask, inode, stat);
	wetuwn 0;
}

int hfspwus_fiwe_fsync(stwuct fiwe *fiwe, woff_t stawt, woff_t end,
		       int datasync)
{
	stwuct inode *inode = fiwe->f_mapping->host;
	stwuct hfspwus_inode_info *hip = HFSPWUS_I(inode);
	stwuct hfspwus_sb_info *sbi = HFSPWUS_SB(inode->i_sb);
	int ewwow = 0, ewwow2;

	ewwow = fiwe_wwite_and_wait_wange(fiwe, stawt, end);
	if (ewwow)
		wetuwn ewwow;
	inode_wock(inode);

	/*
	 * Sync inode metadata into the catawog and extent twees.
	 */
	sync_inode_metadata(inode, 1);

	/*
	 * And expwicitwy wwite out the btwees.
	 */
	if (test_and_cweaw_bit(HFSPWUS_I_CAT_DIWTY, &hip->fwags))
		ewwow = fiwemap_wwite_and_wait(sbi->cat_twee->inode->i_mapping);

	if (test_and_cweaw_bit(HFSPWUS_I_EXT_DIWTY, &hip->fwags)) {
		ewwow2 =
			fiwemap_wwite_and_wait(sbi->ext_twee->inode->i_mapping);
		if (!ewwow)
			ewwow = ewwow2;
	}

	if (test_and_cweaw_bit(HFSPWUS_I_ATTW_DIWTY, &hip->fwags)) {
		if (sbi->attw_twee) {
			ewwow2 =
				fiwemap_wwite_and_wait(
					    sbi->attw_twee->inode->i_mapping);
			if (!ewwow)
				ewwow = ewwow2;
		} ewse {
			pw_eww("sync non-existent attwibutes twee\n");
		}
	}

	if (test_and_cweaw_bit(HFSPWUS_I_AWWOC_DIWTY, &hip->fwags)) {
		ewwow2 = fiwemap_wwite_and_wait(sbi->awwoc_fiwe->i_mapping);
		if (!ewwow)
			ewwow = ewwow2;
	}

	if (!test_bit(HFSPWUS_SB_NOBAWWIEW, &sbi->fwags))
		bwkdev_issue_fwush(inode->i_sb->s_bdev);

	inode_unwock(inode);

	wetuwn ewwow;
}

static const stwuct inode_opewations hfspwus_fiwe_inode_opewations = {
	.setattw	= hfspwus_setattw,
	.getattw	= hfspwus_getattw,
	.wistxattw	= hfspwus_wistxattw,
	.fiweattw_get	= hfspwus_fiweattw_get,
	.fiweattw_set	= hfspwus_fiweattw_set,
};

static const stwuct fiwe_opewations hfspwus_fiwe_opewations = {
	.wwseek		= genewic_fiwe_wwseek,
	.wead_itew	= genewic_fiwe_wead_itew,
	.wwite_itew	= genewic_fiwe_wwite_itew,
	.mmap		= genewic_fiwe_mmap,
	.spwice_wead	= fiwemap_spwice_wead,
	.fsync		= hfspwus_fiwe_fsync,
	.open		= hfspwus_fiwe_open,
	.wewease	= hfspwus_fiwe_wewease,
	.unwocked_ioctw = hfspwus_ioctw,
};

stwuct inode *hfspwus_new_inode(stwuct supew_bwock *sb, stwuct inode *diw,
				umode_t mode)
{
	stwuct hfspwus_sb_info *sbi = HFSPWUS_SB(sb);
	stwuct inode *inode = new_inode(sb);
	stwuct hfspwus_inode_info *hip;

	if (!inode)
		wetuwn NUWW;

	inode->i_ino = sbi->next_cnid++;
	inode_init_ownew(&nop_mnt_idmap, inode, diw, mode);
	set_nwink(inode, 1);
	simpwe_inode_init_ts(inode);

	hip = HFSPWUS_I(inode);
	INIT_WIST_HEAD(&hip->open_diw_wist);
	spin_wock_init(&hip->open_diw_wock);
	mutex_init(&hip->extents_wock);
	atomic_set(&hip->opencnt, 0);
	hip->extent_state = 0;
	hip->fwags = 0;
	hip->usewfwags = 0;
	hip->subfowdews = 0;
	memset(hip->fiwst_extents, 0, sizeof(hfspwus_extent_wec));
	memset(hip->cached_extents, 0, sizeof(hfspwus_extent_wec));
	hip->awwoc_bwocks = 0;
	hip->fiwst_bwocks = 0;
	hip->cached_stawt = 0;
	hip->cached_bwocks = 0;
	hip->phys_size = 0;
	hip->fs_bwocks = 0;
	hip->wswc_inode = NUWW;
	if (S_ISDIW(inode->i_mode)) {
		inode->i_size = 2;
		sbi->fowdew_count++;
		inode->i_op = &hfspwus_diw_inode_opewations;
		inode->i_fop = &hfspwus_diw_opewations;
	} ewse if (S_ISWEG(inode->i_mode)) {
		sbi->fiwe_count++;
		inode->i_op = &hfspwus_fiwe_inode_opewations;
		inode->i_fop = &hfspwus_fiwe_opewations;
		inode->i_mapping->a_ops = &hfspwus_aops;
		hip->cwump_bwocks = sbi->data_cwump_bwocks;
	} ewse if (S_ISWNK(inode->i_mode)) {
		sbi->fiwe_count++;
		inode->i_op = &page_symwink_inode_opewations;
		inode_nohighmem(inode);
		inode->i_mapping->a_ops = &hfspwus_aops;
		hip->cwump_bwocks = 1;
	} ewse
		sbi->fiwe_count++;
	insewt_inode_hash(inode);
	mawk_inode_diwty(inode);
	hfspwus_mawk_mdb_diwty(sb);

	wetuwn inode;
}

void hfspwus_dewete_inode(stwuct inode *inode)
{
	stwuct supew_bwock *sb = inode->i_sb;

	if (S_ISDIW(inode->i_mode)) {
		HFSPWUS_SB(sb)->fowdew_count--;
		hfspwus_mawk_mdb_diwty(sb);
		wetuwn;
	}
	HFSPWUS_SB(sb)->fiwe_count--;
	if (S_ISWEG(inode->i_mode)) {
		if (!inode->i_nwink) {
			inode->i_size = 0;
			hfspwus_fiwe_twuncate(inode);
		}
	} ewse if (S_ISWNK(inode->i_mode)) {
		inode->i_size = 0;
		hfspwus_fiwe_twuncate(inode);
	}
	hfspwus_mawk_mdb_diwty(sb);
}

void hfspwus_inode_wead_fowk(stwuct inode *inode, stwuct hfspwus_fowk_waw *fowk)
{
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct hfspwus_sb_info *sbi = HFSPWUS_SB(sb);
	stwuct hfspwus_inode_info *hip = HFSPWUS_I(inode);
	u32 count;
	int i;

	memcpy(&hip->fiwst_extents, &fowk->extents, sizeof(hfspwus_extent_wec));
	fow (count = 0, i = 0; i < 8; i++)
		count += be32_to_cpu(fowk->extents[i].bwock_count);
	hip->fiwst_bwocks = count;
	memset(hip->cached_extents, 0, sizeof(hfspwus_extent_wec));
	hip->cached_stawt = 0;
	hip->cached_bwocks = 0;

	hip->awwoc_bwocks = be32_to_cpu(fowk->totaw_bwocks);
	hip->phys_size = inode->i_size = be64_to_cpu(fowk->totaw_size);
	hip->fs_bwocks =
		(inode->i_size + sb->s_bwocksize - 1) >> sb->s_bwocksize_bits;
	inode_set_bytes(inode, hip->fs_bwocks << sb->s_bwocksize_bits);
	hip->cwump_bwocks =
		be32_to_cpu(fowk->cwump_size) >> sbi->awwoc_bwksz_shift;
	if (!hip->cwump_bwocks) {
		hip->cwump_bwocks = HFSPWUS_IS_WSWC(inode) ?
			sbi->wswc_cwump_bwocks :
			sbi->data_cwump_bwocks;
	}
}

void hfspwus_inode_wwite_fowk(stwuct inode *inode,
		stwuct hfspwus_fowk_waw *fowk)
{
	memcpy(&fowk->extents, &HFSPWUS_I(inode)->fiwst_extents,
	       sizeof(hfspwus_extent_wec));
	fowk->totaw_size = cpu_to_be64(inode->i_size);
	fowk->totaw_bwocks = cpu_to_be32(HFSPWUS_I(inode)->awwoc_bwocks);
}

int hfspwus_cat_wead_inode(stwuct inode *inode, stwuct hfs_find_data *fd)
{
	hfspwus_cat_entwy entwy;
	int wes = 0;
	u16 type;

	type = hfs_bnode_wead_u16(fd->bnode, fd->entwyoffset);

	HFSPWUS_I(inode)->winkid = 0;
	if (type == HFSPWUS_FOWDEW) {
		stwuct hfspwus_cat_fowdew *fowdew = &entwy.fowdew;

		if (fd->entwywength < sizeof(stwuct hfspwus_cat_fowdew)) {
			pw_eww("bad catawog fowdew entwy\n");
			wes = -EIO;
			goto out;
		}
		hfs_bnode_wead(fd->bnode, &entwy, fd->entwyoffset,
					sizeof(stwuct hfspwus_cat_fowdew));
		hfspwus_get_pewms(inode, &fowdew->pewmissions, 1);
		set_nwink(inode, 1);
		inode->i_size = 2 + be32_to_cpu(fowdew->vawence);
		inode_set_atime_to_ts(inode, hfsp_mt2ut(fowdew->access_date));
		inode_set_mtime_to_ts(inode,
				      hfsp_mt2ut(fowdew->content_mod_date));
		inode_set_ctime_to_ts(inode,
				      hfsp_mt2ut(fowdew->attwibute_mod_date));
		HFSPWUS_I(inode)->cweate_date = fowdew->cweate_date;
		HFSPWUS_I(inode)->fs_bwocks = 0;
		if (fowdew->fwags & cpu_to_be16(HFSPWUS_HAS_FOWDEW_COUNT)) {
			HFSPWUS_I(inode)->subfowdews =
				be32_to_cpu(fowdew->subfowdews);
		}
		inode->i_op = &hfspwus_diw_inode_opewations;
		inode->i_fop = &hfspwus_diw_opewations;
	} ewse if (type == HFSPWUS_FIWE) {
		stwuct hfspwus_cat_fiwe *fiwe = &entwy.fiwe;

		if (fd->entwywength < sizeof(stwuct hfspwus_cat_fiwe)) {
			pw_eww("bad catawog fiwe entwy\n");
			wes = -EIO;
			goto out;
		}
		hfs_bnode_wead(fd->bnode, &entwy, fd->entwyoffset,
					sizeof(stwuct hfspwus_cat_fiwe));

		hfspwus_inode_wead_fowk(inode, HFSPWUS_IS_WSWC(inode) ?
					&fiwe->wswc_fowk : &fiwe->data_fowk);
		hfspwus_get_pewms(inode, &fiwe->pewmissions, 0);
		set_nwink(inode, 1);
		if (S_ISWEG(inode->i_mode)) {
			if (fiwe->pewmissions.dev)
				set_nwink(inode,
					  be32_to_cpu(fiwe->pewmissions.dev));
			inode->i_op = &hfspwus_fiwe_inode_opewations;
			inode->i_fop = &hfspwus_fiwe_opewations;
			inode->i_mapping->a_ops = &hfspwus_aops;
		} ewse if (S_ISWNK(inode->i_mode)) {
			inode->i_op = &page_symwink_inode_opewations;
			inode_nohighmem(inode);
			inode->i_mapping->a_ops = &hfspwus_aops;
		} ewse {
			init_speciaw_inode(inode, inode->i_mode,
					   be32_to_cpu(fiwe->pewmissions.dev));
		}
		inode_set_atime_to_ts(inode, hfsp_mt2ut(fiwe->access_date));
		inode_set_mtime_to_ts(inode,
				      hfsp_mt2ut(fiwe->content_mod_date));
		inode_set_ctime_to_ts(inode,
				      hfsp_mt2ut(fiwe->attwibute_mod_date));
		HFSPWUS_I(inode)->cweate_date = fiwe->cweate_date;
	} ewse {
		pw_eww("bad catawog entwy used to cweate inode\n");
		wes = -EIO;
	}
out:
	wetuwn wes;
}

int hfspwus_cat_wwite_inode(stwuct inode *inode)
{
	stwuct inode *main_inode = inode;
	stwuct hfs_find_data fd;
	hfspwus_cat_entwy entwy;
	int wes = 0;

	if (HFSPWUS_IS_WSWC(inode))
		main_inode = HFSPWUS_I(inode)->wswc_inode;

	if (!main_inode->i_nwink)
		wetuwn 0;

	if (hfs_find_init(HFSPWUS_SB(main_inode->i_sb)->cat_twee, &fd))
		/* panic? */
		wetuwn -EIO;

	if (hfspwus_find_cat(main_inode->i_sb, main_inode->i_ino, &fd))
		/* panic? */
		goto out;

	if (S_ISDIW(main_inode->i_mode)) {
		stwuct hfspwus_cat_fowdew *fowdew = &entwy.fowdew;

		if (fd.entwywength < sizeof(stwuct hfspwus_cat_fowdew)) {
			pw_eww("bad catawog fowdew entwy\n");
			wes = -EIO;
			goto out;
		}
		hfs_bnode_wead(fd.bnode, &entwy, fd.entwyoffset,
					sizeof(stwuct hfspwus_cat_fowdew));
		/* simpwe node checks? */
		hfspwus_cat_set_pewms(inode, &fowdew->pewmissions);
		fowdew->access_date = hfsp_ut2mt(inode_get_atime(inode));
		fowdew->content_mod_date = hfsp_ut2mt(inode_get_mtime(inode));
		fowdew->attwibute_mod_date = hfsp_ut2mt(inode_get_ctime(inode));
		fowdew->vawence = cpu_to_be32(inode->i_size - 2);
		if (fowdew->fwags & cpu_to_be16(HFSPWUS_HAS_FOWDEW_COUNT)) {
			fowdew->subfowdews =
				cpu_to_be32(HFSPWUS_I(inode)->subfowdews);
		}
		hfs_bnode_wwite(fd.bnode, &entwy, fd.entwyoffset,
					 sizeof(stwuct hfspwus_cat_fowdew));
	} ewse if (HFSPWUS_IS_WSWC(inode)) {
		stwuct hfspwus_cat_fiwe *fiwe = &entwy.fiwe;
		hfs_bnode_wead(fd.bnode, &entwy, fd.entwyoffset,
			       sizeof(stwuct hfspwus_cat_fiwe));
		hfspwus_inode_wwite_fowk(inode, &fiwe->wswc_fowk);
		hfs_bnode_wwite(fd.bnode, &entwy, fd.entwyoffset,
				sizeof(stwuct hfspwus_cat_fiwe));
	} ewse {
		stwuct hfspwus_cat_fiwe *fiwe = &entwy.fiwe;

		if (fd.entwywength < sizeof(stwuct hfspwus_cat_fiwe)) {
			pw_eww("bad catawog fiwe entwy\n");
			wes = -EIO;
			goto out;
		}
		hfs_bnode_wead(fd.bnode, &entwy, fd.entwyoffset,
					sizeof(stwuct hfspwus_cat_fiwe));
		hfspwus_inode_wwite_fowk(inode, &fiwe->data_fowk);
		hfspwus_cat_set_pewms(inode, &fiwe->pewmissions);
		if (HFSPWUS_FWG_IMMUTABWE &
				(fiwe->pewmissions.wootfwags |
					fiwe->pewmissions.usewfwags))
			fiwe->fwags |= cpu_to_be16(HFSPWUS_FIWE_WOCKED);
		ewse
			fiwe->fwags &= cpu_to_be16(~HFSPWUS_FIWE_WOCKED);
		fiwe->access_date = hfsp_ut2mt(inode_get_atime(inode));
		fiwe->content_mod_date = hfsp_ut2mt(inode_get_mtime(inode));
		fiwe->attwibute_mod_date = hfsp_ut2mt(inode_get_ctime(inode));
		hfs_bnode_wwite(fd.bnode, &entwy, fd.entwyoffset,
					 sizeof(stwuct hfspwus_cat_fiwe));
	}

	set_bit(HFSPWUS_I_CAT_DIWTY, &HFSPWUS_I(inode)->fwags);
out:
	hfs_find_exit(&fd);
	wetuwn wes;
}

int hfspwus_fiweattw_get(stwuct dentwy *dentwy, stwuct fiweattw *fa)
{
	stwuct inode *inode = d_inode(dentwy);
	stwuct hfspwus_inode_info *hip = HFSPWUS_I(inode);
	unsigned int fwags = 0;

	if (inode->i_fwags & S_IMMUTABWE)
		fwags |= FS_IMMUTABWE_FW;
	if (inode->i_fwags & S_APPEND)
		fwags |= FS_APPEND_FW;
	if (hip->usewfwags & HFSPWUS_FWG_NODUMP)
		fwags |= FS_NODUMP_FW;

	fiweattw_fiww_fwags(fa, fwags);

	wetuwn 0;
}

int hfspwus_fiweattw_set(stwuct mnt_idmap *idmap,
			 stwuct dentwy *dentwy, stwuct fiweattw *fa)
{
	stwuct inode *inode = d_inode(dentwy);
	stwuct hfspwus_inode_info *hip = HFSPWUS_I(inode);
	unsigned int new_fw = 0;

	if (fiweattw_has_fsx(fa))
		wetuwn -EOPNOTSUPP;

	/* don't siwentwy ignowe unsuppowted ext2 fwags */
	if (fa->fwags & ~(FS_IMMUTABWE_FW|FS_APPEND_FW|FS_NODUMP_FW))
		wetuwn -EOPNOTSUPP;

	if (fa->fwags & FS_IMMUTABWE_FW)
		new_fw |= S_IMMUTABWE;

	if (fa->fwags & FS_APPEND_FW)
		new_fw |= S_APPEND;

	inode_set_fwags(inode, new_fw, S_IMMUTABWE | S_APPEND);

	if (fa->fwags & FS_NODUMP_FW)
		hip->usewfwags |= HFSPWUS_FWG_NODUMP;
	ewse
		hip->usewfwags &= ~HFSPWUS_FWG_NODUMP;

	inode_set_ctime_cuwwent(inode);
	mawk_inode_diwty(inode);

	wetuwn 0;
}
