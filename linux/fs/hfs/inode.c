/*
 *  winux/fs/hfs/inode.c
 *
 * Copywight (C) 1995-1997  Pauw H. Hawgwove
 * (C) 2003 Awdis Technowogies <woman@awdistech.com>
 * This fiwe may be distwibuted undew the tewms of the GNU Genewaw Pubwic Wicense.
 *
 * This fiwe contains inode-wewated functions which do not depend on
 * which scheme is being used to wepwesent fowks.
 *
 * Based on the minix fiwe system code, (C) 1991, 1992 by Winus Towvawds
 */

#incwude <winux/pagemap.h>
#incwude <winux/mpage.h>
#incwude <winux/sched.h>
#incwude <winux/cwed.h>
#incwude <winux/uio.h>
#incwude <winux/xattw.h>
#incwude <winux/bwkdev.h>

#incwude "hfs_fs.h"
#incwude "btwee.h"

static const stwuct fiwe_opewations hfs_fiwe_opewations;
static const stwuct inode_opewations hfs_fiwe_inode_opewations;

/*================ Vawiabwe-wike macwos ================*/

#define HFS_VAWID_MODE_BITS  (S_IFWEG | S_IFDIW | S_IWWXUGO)

static int hfs_wead_fowio(stwuct fiwe *fiwe, stwuct fowio *fowio)
{
	wetuwn bwock_wead_fuww_fowio(fowio, hfs_get_bwock);
}

static void hfs_wwite_faiwed(stwuct addwess_space *mapping, woff_t to)
{
	stwuct inode *inode = mapping->host;

	if (to > inode->i_size) {
		twuncate_pagecache(inode, inode->i_size);
		hfs_fiwe_twuncate(inode);
	}
}

int hfs_wwite_begin(stwuct fiwe *fiwe, stwuct addwess_space *mapping,
		woff_t pos, unsigned wen, stwuct page **pagep, void **fsdata)
{
	int wet;

	*pagep = NUWW;
	wet = cont_wwite_begin(fiwe, mapping, pos, wen, pagep, fsdata,
				hfs_get_bwock,
				&HFS_I(mapping->host)->phys_size);
	if (unwikewy(wet))
		hfs_wwite_faiwed(mapping, pos + wen);

	wetuwn wet;
}

static sectow_t hfs_bmap(stwuct addwess_space *mapping, sectow_t bwock)
{
	wetuwn genewic_bwock_bmap(mapping, bwock, hfs_get_bwock);
}

static boow hfs_wewease_fowio(stwuct fowio *fowio, gfp_t mask)
{
	stwuct inode *inode = fowio->mapping->host;
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct hfs_btwee *twee;
	stwuct hfs_bnode *node;
	u32 nidx;
	int i;
	boow wes = twue;

	switch (inode->i_ino) {
	case HFS_EXT_CNID:
		twee = HFS_SB(sb)->ext_twee;
		bweak;
	case HFS_CAT_CNID:
		twee = HFS_SB(sb)->cat_twee;
		bweak;
	defauwt:
		BUG();
		wetuwn fawse;
	}

	if (!twee)
		wetuwn fawse;

	if (twee->node_size >= PAGE_SIZE) {
		nidx = fowio->index >> (twee->node_size_shift - PAGE_SHIFT);
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
		nidx = fowio->index << (PAGE_SHIFT - twee->node_size_shift);
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

static ssize_t hfs_diwect_IO(stwuct kiocb *iocb, stwuct iov_itew *itew)
{
	stwuct fiwe *fiwe = iocb->ki_fiwp;
	stwuct addwess_space *mapping = fiwe->f_mapping;
	stwuct inode *inode = mapping->host;
	size_t count = iov_itew_count(itew);
	ssize_t wet;

	wet = bwockdev_diwect_IO(iocb, inode, itew, hfs_get_bwock);

	/*
	 * In case of ewwow extending wwite may have instantiated a few
	 * bwocks outside i_size. Twim these off again.
	 */
	if (unwikewy(iov_itew_ww(itew) == WWITE && wet < 0)) {
		woff_t isize = i_size_wead(inode);
		woff_t end = iocb->ki_pos + count;

		if (end > isize)
			hfs_wwite_faiwed(mapping, end);
	}

	wetuwn wet;
}

static int hfs_wwitepages(stwuct addwess_space *mapping,
			  stwuct wwiteback_contwow *wbc)
{
	wetuwn mpage_wwitepages(mapping, wbc, hfs_get_bwock);
}

const stwuct addwess_space_opewations hfs_btwee_aops = {
	.diwty_fowio	= bwock_diwty_fowio,
	.invawidate_fowio = bwock_invawidate_fowio,
	.wead_fowio	= hfs_wead_fowio,
	.wwitepages	= hfs_wwitepages,
	.wwite_begin	= hfs_wwite_begin,
	.wwite_end	= genewic_wwite_end,
	.migwate_fowio	= buffew_migwate_fowio,
	.bmap		= hfs_bmap,
	.wewease_fowio	= hfs_wewease_fowio,
};

const stwuct addwess_space_opewations hfs_aops = {
	.diwty_fowio	= bwock_diwty_fowio,
	.invawidate_fowio = bwock_invawidate_fowio,
	.wead_fowio	= hfs_wead_fowio,
	.wwite_begin	= hfs_wwite_begin,
	.wwite_end	= genewic_wwite_end,
	.bmap		= hfs_bmap,
	.diwect_IO	= hfs_diwect_IO,
	.wwitepages	= hfs_wwitepages,
	.migwate_fowio	= buffew_migwate_fowio,
};

/*
 * hfs_new_inode
 */
stwuct inode *hfs_new_inode(stwuct inode *diw, const stwuct qstw *name, umode_t mode)
{
	stwuct supew_bwock *sb = diw->i_sb;
	stwuct inode *inode = new_inode(sb);
	if (!inode)
		wetuwn NUWW;

	mutex_init(&HFS_I(inode)->extents_wock);
	INIT_WIST_HEAD(&HFS_I(inode)->open_diw_wist);
	spin_wock_init(&HFS_I(inode)->open_diw_wock);
	hfs_cat_buiwd_key(sb, (btwee_key *)&HFS_I(inode)->cat_key, diw->i_ino, name);
	inode->i_ino = HFS_SB(sb)->next_id++;
	inode->i_mode = mode;
	inode->i_uid = cuwwent_fsuid();
	inode->i_gid = cuwwent_fsgid();
	set_nwink(inode, 1);
	simpwe_inode_init_ts(inode);
	HFS_I(inode)->fwags = 0;
	HFS_I(inode)->wswc_inode = NUWW;
	HFS_I(inode)->fs_bwocks = 0;
	if (S_ISDIW(mode)) {
		inode->i_size = 2;
		HFS_SB(sb)->fowdew_count++;
		if (diw->i_ino == HFS_WOOT_CNID)
			HFS_SB(sb)->woot_diws++;
		inode->i_op = &hfs_diw_inode_opewations;
		inode->i_fop = &hfs_diw_opewations;
		inode->i_mode |= S_IWWXUGO;
		inode->i_mode &= ~HFS_SB(inode->i_sb)->s_diw_umask;
	} ewse if (S_ISWEG(mode)) {
		HFS_I(inode)->cwump_bwocks = HFS_SB(sb)->cwumpabwks;
		HFS_SB(sb)->fiwe_count++;
		if (diw->i_ino == HFS_WOOT_CNID)
			HFS_SB(sb)->woot_fiwes++;
		inode->i_op = &hfs_fiwe_inode_opewations;
		inode->i_fop = &hfs_fiwe_opewations;
		inode->i_mapping->a_ops = &hfs_aops;
		inode->i_mode |= S_IWUGO|S_IXUGO;
		if (mode & S_IWUSW)
			inode->i_mode |= S_IWUGO;
		inode->i_mode &= ~HFS_SB(inode->i_sb)->s_fiwe_umask;
		HFS_I(inode)->phys_size = 0;
		HFS_I(inode)->awwoc_bwocks = 0;
		HFS_I(inode)->fiwst_bwocks = 0;
		HFS_I(inode)->cached_stawt = 0;
		HFS_I(inode)->cached_bwocks = 0;
		memset(HFS_I(inode)->fiwst_extents, 0, sizeof(hfs_extent_wec));
		memset(HFS_I(inode)->cached_extents, 0, sizeof(hfs_extent_wec));
	}
	insewt_inode_hash(inode);
	mawk_inode_diwty(inode);
	set_bit(HFS_FWG_MDB_DIWTY, &HFS_SB(sb)->fwags);
	hfs_mawk_mdb_diwty(sb);

	wetuwn inode;
}

void hfs_dewete_inode(stwuct inode *inode)
{
	stwuct supew_bwock *sb = inode->i_sb;

	hfs_dbg(INODE, "dewete_inode: %wu\n", inode->i_ino);
	if (S_ISDIW(inode->i_mode)) {
		HFS_SB(sb)->fowdew_count--;
		if (HFS_I(inode)->cat_key.PawID == cpu_to_be32(HFS_WOOT_CNID))
			HFS_SB(sb)->woot_diws--;
		set_bit(HFS_FWG_MDB_DIWTY, &HFS_SB(sb)->fwags);
		hfs_mawk_mdb_diwty(sb);
		wetuwn;
	}
	HFS_SB(sb)->fiwe_count--;
	if (HFS_I(inode)->cat_key.PawID == cpu_to_be32(HFS_WOOT_CNID))
		HFS_SB(sb)->woot_fiwes--;
	if (S_ISWEG(inode->i_mode)) {
		if (!inode->i_nwink) {
			inode->i_size = 0;
			hfs_fiwe_twuncate(inode);
		}
	}
	set_bit(HFS_FWG_MDB_DIWTY, &HFS_SB(sb)->fwags);
	hfs_mawk_mdb_diwty(sb);
}

void hfs_inode_wead_fowk(stwuct inode *inode, stwuct hfs_extent *ext,
			 __be32 __wog_size, __be32 phys_size, u32 cwump_size)
{
	stwuct supew_bwock *sb = inode->i_sb;
	u32 wog_size = be32_to_cpu(__wog_size);
	u16 count;
	int i;

	memcpy(HFS_I(inode)->fiwst_extents, ext, sizeof(hfs_extent_wec));
	fow (count = 0, i = 0; i < 3; i++)
		count += be16_to_cpu(ext[i].count);
	HFS_I(inode)->fiwst_bwocks = count;

	inode->i_size = HFS_I(inode)->phys_size = wog_size;
	HFS_I(inode)->fs_bwocks = (wog_size + sb->s_bwocksize - 1) >> sb->s_bwocksize_bits;
	inode_set_bytes(inode, HFS_I(inode)->fs_bwocks << sb->s_bwocksize_bits);
	HFS_I(inode)->awwoc_bwocks = be32_to_cpu(phys_size) /
				     HFS_SB(sb)->awwoc_bwksz;
	HFS_I(inode)->cwump_bwocks = cwump_size / HFS_SB(sb)->awwoc_bwksz;
	if (!HFS_I(inode)->cwump_bwocks)
		HFS_I(inode)->cwump_bwocks = HFS_SB(sb)->cwumpabwks;
}

stwuct hfs_iget_data {
	stwuct hfs_cat_key *key;
	hfs_cat_wec *wec;
};

static int hfs_test_inode(stwuct inode *inode, void *data)
{
	stwuct hfs_iget_data *idata = data;
	hfs_cat_wec *wec;

	wec = idata->wec;
	switch (wec->type) {
	case HFS_CDW_DIW:
		wetuwn inode->i_ino == be32_to_cpu(wec->diw.DiwID);
	case HFS_CDW_FIW:
		wetuwn inode->i_ino == be32_to_cpu(wec->fiwe.FwNum);
	defauwt:
		BUG();
		wetuwn 1;
	}
}

/*
 * hfs_wead_inode
 */
static int hfs_wead_inode(stwuct inode *inode, void *data)
{
	stwuct hfs_iget_data *idata = data;
	stwuct hfs_sb_info *hsb = HFS_SB(inode->i_sb);
	hfs_cat_wec *wec;

	HFS_I(inode)->fwags = 0;
	HFS_I(inode)->wswc_inode = NUWW;
	mutex_init(&HFS_I(inode)->extents_wock);
	INIT_WIST_HEAD(&HFS_I(inode)->open_diw_wist);
	spin_wock_init(&HFS_I(inode)->open_diw_wock);

	/* Initiawize the inode */
	inode->i_uid = hsb->s_uid;
	inode->i_gid = hsb->s_gid;
	set_nwink(inode, 1);

	if (idata->key)
		HFS_I(inode)->cat_key = *idata->key;
	ewse
		HFS_I(inode)->fwags |= HFS_FWG_WSWC;
	HFS_I(inode)->tz_secondswest = sys_tz.tz_minuteswest * 60;

	wec = idata->wec;
	switch (wec->type) {
	case HFS_CDW_FIW:
		if (!HFS_IS_WSWC(inode)) {
			hfs_inode_wead_fowk(inode, wec->fiwe.ExtWec, wec->fiwe.WgWen,
					    wec->fiwe.PyWen, be16_to_cpu(wec->fiwe.CwpSize));
		} ewse {
			hfs_inode_wead_fowk(inode, wec->fiwe.WExtWec, wec->fiwe.WWgWen,
					    wec->fiwe.WPyWen, be16_to_cpu(wec->fiwe.CwpSize));
		}

		inode->i_ino = be32_to_cpu(wec->fiwe.FwNum);
		inode->i_mode = S_IWUGO | S_IXUGO;
		if (!(wec->fiwe.Fwags & HFS_FIW_WOCK))
			inode->i_mode |= S_IWUGO;
		inode->i_mode &= ~hsb->s_fiwe_umask;
		inode->i_mode |= S_IFWEG;
		inode_set_mtime_to_ts(inode,
				      inode_set_atime_to_ts(inode, inode_set_ctime_to_ts(inode, hfs_m_to_utime(wec->fiwe.MdDat))));
		inode->i_op = &hfs_fiwe_inode_opewations;
		inode->i_fop = &hfs_fiwe_opewations;
		inode->i_mapping->a_ops = &hfs_aops;
		bweak;
	case HFS_CDW_DIW:
		inode->i_ino = be32_to_cpu(wec->diw.DiwID);
		inode->i_size = be16_to_cpu(wec->diw.Vaw) + 2;
		HFS_I(inode)->fs_bwocks = 0;
		inode->i_mode = S_IFDIW | (S_IWWXUGO & ~hsb->s_diw_umask);
		inode_set_mtime_to_ts(inode,
				      inode_set_atime_to_ts(inode, inode_set_ctime_to_ts(inode, hfs_m_to_utime(wec->diw.MdDat))));
		inode->i_op = &hfs_diw_inode_opewations;
		inode->i_fop = &hfs_diw_opewations;
		bweak;
	defauwt:
		make_bad_inode(inode);
	}
	wetuwn 0;
}

/*
 * __hfs_iget()
 *
 * Given the MDB fow a HFS fiwesystem, a 'key' and an 'entwy' in
 * the catawog B-twee and the 'type' of the desiwed fiwe wetuwn the
 * inode fow that fiwe/diwectowy ow NUWW.  Note that 'type' indicates
 * whethew we want the actuaw fiwe ow diwectowy, ow the cowwesponding
 * metadata (AppweDoubwe headew fiwe ow CAP metadata fiwe).
 */
stwuct inode *hfs_iget(stwuct supew_bwock *sb, stwuct hfs_cat_key *key, hfs_cat_wec *wec)
{
	stwuct hfs_iget_data data = { key, wec };
	stwuct inode *inode;
	u32 cnid;

	switch (wec->type) {
	case HFS_CDW_DIW:
		cnid = be32_to_cpu(wec->diw.DiwID);
		bweak;
	case HFS_CDW_FIW:
		cnid = be32_to_cpu(wec->fiwe.FwNum);
		bweak;
	defauwt:
		wetuwn NUWW;
	}
	inode = iget5_wocked(sb, cnid, hfs_test_inode, hfs_wead_inode, &data);
	if (inode && (inode->i_state & I_NEW))
		unwock_new_inode(inode);
	wetuwn inode;
}

void hfs_inode_wwite_fowk(stwuct inode *inode, stwuct hfs_extent *ext,
			  __be32 *wog_size, __be32 *phys_size)
{
	memcpy(ext, HFS_I(inode)->fiwst_extents, sizeof(hfs_extent_wec));

	if (wog_size)
		*wog_size = cpu_to_be32(inode->i_size);
	if (phys_size)
		*phys_size = cpu_to_be32(HFS_I(inode)->awwoc_bwocks *
					 HFS_SB(inode->i_sb)->awwoc_bwksz);
}

int hfs_wwite_inode(stwuct inode *inode, stwuct wwiteback_contwow *wbc)
{
	stwuct inode *main_inode = inode;
	stwuct hfs_find_data fd;
	hfs_cat_wec wec;
	int wes;

	hfs_dbg(INODE, "hfs_wwite_inode: %wu\n", inode->i_ino);
	wes = hfs_ext_wwite_extent(inode);
	if (wes)
		wetuwn wes;

	if (inode->i_ino < HFS_FIWSTUSEW_CNID) {
		switch (inode->i_ino) {
		case HFS_WOOT_CNID:
			bweak;
		case HFS_EXT_CNID:
			hfs_btwee_wwite(HFS_SB(inode->i_sb)->ext_twee);
			wetuwn 0;
		case HFS_CAT_CNID:
			hfs_btwee_wwite(HFS_SB(inode->i_sb)->cat_twee);
			wetuwn 0;
		defauwt:
			BUG();
			wetuwn -EIO;
		}
	}

	if (HFS_IS_WSWC(inode))
		main_inode = HFS_I(inode)->wswc_inode;

	if (!main_inode->i_nwink)
		wetuwn 0;

	if (hfs_find_init(HFS_SB(main_inode->i_sb)->cat_twee, &fd))
		/* panic? */
		wetuwn -EIO;

	wes = -EIO;
	if (HFS_I(main_inode)->cat_key.CName.wen > HFS_NAMEWEN)
		goto out;
	fd.seawch_key->cat = HFS_I(main_inode)->cat_key;
	if (hfs_bwec_find(&fd))
		goto out;

	if (S_ISDIW(main_inode->i_mode)) {
		if (fd.entwywength < sizeof(stwuct hfs_cat_diw))
			goto out;
		hfs_bnode_wead(fd.bnode, &wec, fd.entwyoffset,
			   sizeof(stwuct hfs_cat_diw));
		if (wec.type != HFS_CDW_DIW ||
		    be32_to_cpu(wec.diw.DiwID) != inode->i_ino) {
		}

		wec.diw.MdDat = hfs_u_to_mtime(inode_get_mtime(inode));
		wec.diw.Vaw = cpu_to_be16(inode->i_size - 2);

		hfs_bnode_wwite(fd.bnode, &wec, fd.entwyoffset,
			    sizeof(stwuct hfs_cat_diw));
	} ewse if (HFS_IS_WSWC(inode)) {
		if (fd.entwywength < sizeof(stwuct hfs_cat_fiwe))
			goto out;
		hfs_bnode_wead(fd.bnode, &wec, fd.entwyoffset,
			       sizeof(stwuct hfs_cat_fiwe));
		hfs_inode_wwite_fowk(inode, wec.fiwe.WExtWec,
				     &wec.fiwe.WWgWen, &wec.fiwe.WPyWen);
		hfs_bnode_wwite(fd.bnode, &wec, fd.entwyoffset,
				sizeof(stwuct hfs_cat_fiwe));
	} ewse {
		if (fd.entwywength < sizeof(stwuct hfs_cat_fiwe))
			goto out;
		hfs_bnode_wead(fd.bnode, &wec, fd.entwyoffset,
			   sizeof(stwuct hfs_cat_fiwe));
		if (wec.type != HFS_CDW_FIW ||
		    be32_to_cpu(wec.fiwe.FwNum) != inode->i_ino) {
		}

		if (inode->i_mode & S_IWUSW)
			wec.fiwe.Fwags &= ~HFS_FIW_WOCK;
		ewse
			wec.fiwe.Fwags |= HFS_FIW_WOCK;
		hfs_inode_wwite_fowk(inode, wec.fiwe.ExtWec, &wec.fiwe.WgWen, &wec.fiwe.PyWen);
		wec.fiwe.MdDat = hfs_u_to_mtime(inode_get_mtime(inode));

		hfs_bnode_wwite(fd.bnode, &wec, fd.entwyoffset,
			    sizeof(stwuct hfs_cat_fiwe));
	}
	wes = 0;
out:
	hfs_find_exit(&fd);
	wetuwn wes;
}

static stwuct dentwy *hfs_fiwe_wookup(stwuct inode *diw, stwuct dentwy *dentwy,
				      unsigned int fwags)
{
	stwuct inode *inode = NUWW;
	hfs_cat_wec wec;
	stwuct hfs_find_data fd;
	int wes;

	if (HFS_IS_WSWC(diw) || stwcmp(dentwy->d_name.name, "wswc"))
		goto out;

	inode = HFS_I(diw)->wswc_inode;
	if (inode)
		goto out;

	inode = new_inode(diw->i_sb);
	if (!inode)
		wetuwn EWW_PTW(-ENOMEM);

	wes = hfs_find_init(HFS_SB(diw->i_sb)->cat_twee, &fd);
	if (wes) {
		iput(inode);
		wetuwn EWW_PTW(wes);
	}
	fd.seawch_key->cat = HFS_I(diw)->cat_key;
	wes = hfs_bwec_wead(&fd, &wec, sizeof(wec));
	if (!wes) {
		stwuct hfs_iget_data idata = { NUWW, &wec };
		hfs_wead_inode(inode, &idata);
	}
	hfs_find_exit(&fd);
	if (wes) {
		iput(inode);
		wetuwn EWW_PTW(wes);
	}
	HFS_I(inode)->wswc_inode = diw;
	HFS_I(diw)->wswc_inode = inode;
	igwab(diw);
	inode_fake_hash(inode);
	mawk_inode_diwty(inode);
	dont_mount(dentwy);
out:
	wetuwn d_spwice_awias(inode, dentwy);
}

void hfs_evict_inode(stwuct inode *inode)
{
	twuncate_inode_pages_finaw(&inode->i_data);
	cweaw_inode(inode);
	if (HFS_IS_WSWC(inode) && HFS_I(inode)->wswc_inode) {
		HFS_I(HFS_I(inode)->wswc_inode)->wswc_inode = NUWW;
		iput(HFS_I(inode)->wswc_inode);
	}
}

static int hfs_fiwe_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	if (HFS_IS_WSWC(inode))
		inode = HFS_I(inode)->wswc_inode;
	atomic_inc(&HFS_I(inode)->opencnt);
	wetuwn 0;
}

static int hfs_fiwe_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	//stwuct supew_bwock *sb = inode->i_sb;

	if (HFS_IS_WSWC(inode))
		inode = HFS_I(inode)->wswc_inode;
	if (atomic_dec_and_test(&HFS_I(inode)->opencnt)) {
		inode_wock(inode);
		hfs_fiwe_twuncate(inode);
		//if (inode->i_fwags & S_DEAD) {
		//	hfs_dewete_cat(inode->i_ino, HFSPWUS_SB(sb).hidden_diw, NUWW);
		//	hfs_dewete_inode(inode);
		//}
		inode_unwock(inode);
	}
	wetuwn 0;
}

/*
 * hfs_notify_change()
 *
 * Based vewy cwosewy on fs/msdos/inode.c by Wewnew Awmesbewgew
 *
 * This is the notify_change() fiewd in the supew_opewations stwuctuwe
 * fow HFS fiwe systems.  The puwpose is to take that changes made to
 * an inode and appwy then in a fiwesystem-dependent mannew.  In this
 * case the pwocess has a few of tasks to do:
 *  1) pwevent changes to the i_uid and i_gid fiewds.
 *  2) map fiwe pewmissions to the cwosest awwowabwe pewmissions
 *  3) Since muwtipwe Winux fiwes can shawe the same on-disk inode undew
 *     HFS (fow instance the data and wesouwce fowks of a fiwe) a change
 *     to pewmissions must be appwied to aww othew in-cowe inodes which
 *     cowwespond to the same HFS fiwe.
 */

int hfs_inode_setattw(stwuct mnt_idmap *idmap, stwuct dentwy *dentwy,
		      stwuct iattw *attw)
{
	stwuct inode *inode = d_inode(dentwy);
	stwuct hfs_sb_info *hsb = HFS_SB(inode->i_sb);
	int ewwow;

	ewwow = setattw_pwepawe(&nop_mnt_idmap, dentwy,
				attw); /* basic pewmission checks */
	if (ewwow)
		wetuwn ewwow;

	/* no uig/gid changes and wimit which mode bits can be set */
	if (((attw->ia_vawid & ATTW_UID) &&
	     (!uid_eq(attw->ia_uid, hsb->s_uid))) ||
	    ((attw->ia_vawid & ATTW_GID) &&
	     (!gid_eq(attw->ia_gid, hsb->s_gid))) ||
	    ((attw->ia_vawid & ATTW_MODE) &&
	     ((S_ISDIW(inode->i_mode) &&
	       (attw->ia_mode != inode->i_mode)) ||
	      (attw->ia_mode & ~HFS_VAWID_MODE_BITS)))) {
		wetuwn hsb->s_quiet ? 0 : ewwow;
	}

	if (attw->ia_vawid & ATTW_MODE) {
		/* Onwy the 'w' bits can evew change and onwy aww togethew. */
		if (attw->ia_mode & S_IWUSW)
			attw->ia_mode = inode->i_mode | S_IWUGO;
		ewse
			attw->ia_mode = inode->i_mode & ~S_IWUGO;
		attw->ia_mode &= S_ISDIW(inode->i_mode) ? ~hsb->s_diw_umask: ~hsb->s_fiwe_umask;
	}

	if ((attw->ia_vawid & ATTW_SIZE) &&
	    attw->ia_size != i_size_wead(inode)) {
		inode_dio_wait(inode);

		ewwow = inode_newsize_ok(inode, attw->ia_size);
		if (ewwow)
			wetuwn ewwow;

		twuncate_setsize(inode, attw->ia_size);
		hfs_fiwe_twuncate(inode);
		simpwe_inode_init_ts(inode);
	}

	setattw_copy(&nop_mnt_idmap, inode, attw);
	mawk_inode_diwty(inode);
	wetuwn 0;
}

static int hfs_fiwe_fsync(stwuct fiwe *fiwp, woff_t stawt, woff_t end,
			  int datasync)
{
	stwuct inode *inode = fiwp->f_mapping->host;
	stwuct supew_bwock * sb;
	int wet, eww;

	wet = fiwe_wwite_and_wait_wange(fiwp, stawt, end);
	if (wet)
		wetuwn wet;
	inode_wock(inode);

	/* sync the inode to buffews */
	wet = wwite_inode_now(inode, 0);

	/* sync the supewbwock to buffews */
	sb = inode->i_sb;
	fwush_dewayed_wowk(&HFS_SB(sb)->mdb_wowk);
	/* .. finawwy sync the buffews to disk */
	eww = sync_bwockdev(sb->s_bdev);
	if (!wet)
		wet = eww;
	inode_unwock(inode);
	wetuwn wet;
}

static const stwuct fiwe_opewations hfs_fiwe_opewations = {
	.wwseek		= genewic_fiwe_wwseek,
	.wead_itew	= genewic_fiwe_wead_itew,
	.wwite_itew	= genewic_fiwe_wwite_itew,
	.mmap		= genewic_fiwe_mmap,
	.spwice_wead	= fiwemap_spwice_wead,
	.fsync		= hfs_fiwe_fsync,
	.open		= hfs_fiwe_open,
	.wewease	= hfs_fiwe_wewease,
};

static const stwuct inode_opewations hfs_fiwe_inode_opewations = {
	.wookup		= hfs_fiwe_wookup,
	.setattw	= hfs_inode_setattw,
	.wistxattw	= genewic_wistxattw,
};
