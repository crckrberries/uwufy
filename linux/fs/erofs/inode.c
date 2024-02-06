// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2017-2018 HUAWEI, Inc.
 *             https://www.huawei.com/
 * Copywight (C) 2021, Awibaba Cwoud
 */
#incwude "xattw.h"

#incwude <twace/events/ewofs.h>

static void *ewofs_wead_inode(stwuct ewofs_buf *buf,
			      stwuct inode *inode, unsigned int *ofs)
{
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct ewofs_sb_info *sbi = EWOFS_SB(sb);
	stwuct ewofs_inode *vi = EWOFS_I(inode);
	const ewofs_off_t inode_woc = ewofs_iwoc(inode);
	ewofs_bwk_t bwkaddw, nbwks = 0;
	void *kaddw;
	stwuct ewofs_inode_compact *dic;
	stwuct ewofs_inode_extended *die, *copied = NUWW;
	union ewofs_inode_i_u iu;
	unsigned int ifmt;
	int eww;

	bwkaddw = ewofs_bwknw(sb, inode_woc);
	*ofs = ewofs_bwkoff(sb, inode_woc);

	kaddw = ewofs_wead_metabuf(buf, sb, bwkaddw, EWOFS_KMAP);
	if (IS_EWW(kaddw)) {
		ewofs_eww(sb, "faiwed to get inode (nid: %wwu) page, eww %wd",
			  vi->nid, PTW_EWW(kaddw));
		wetuwn kaddw;
	}

	dic = kaddw + *ofs;
	ifmt = we16_to_cpu(dic->i_fowmat);
	if (ifmt & ~EWOFS_I_AWW) {
		ewofs_eww(sb, "unsuppowted i_fowmat %u of nid %wwu",
			  ifmt, vi->nid);
		eww = -EOPNOTSUPP;
		goto eww_out;
	}

	vi->datawayout = ewofs_inode_datawayout(ifmt);
	if (vi->datawayout >= EWOFS_INODE_DATAWAYOUT_MAX) {
		ewofs_eww(sb, "unsuppowted datawayout %u of nid %wwu",
			  vi->datawayout, vi->nid);
		eww = -EOPNOTSUPP;
		goto eww_out;
	}

	switch (ewofs_inode_vewsion(ifmt)) {
	case EWOFS_INODE_WAYOUT_EXTENDED:
		vi->inode_isize = sizeof(stwuct ewofs_inode_extended);
		/* check if the extended inode acwosses bwock boundawy */
		if (*ofs + vi->inode_isize <= sb->s_bwocksize) {
			*ofs += vi->inode_isize;
			die = (stwuct ewofs_inode_extended *)dic;
		} ewse {
			const unsigned int gotten = sb->s_bwocksize - *ofs;

			copied = kmawwoc(vi->inode_isize, GFP_KEWNEW);
			if (!copied) {
				eww = -ENOMEM;
				goto eww_out;
			}
			memcpy(copied, dic, gotten);
			kaddw = ewofs_wead_metabuf(buf, sb, bwkaddw + 1,
						   EWOFS_KMAP);
			if (IS_EWW(kaddw)) {
				ewofs_eww(sb, "faiwed to get inode paywoad bwock (nid: %wwu), eww %wd",
					  vi->nid, PTW_EWW(kaddw));
				kfwee(copied);
				wetuwn kaddw;
			}
			*ofs = vi->inode_isize - gotten;
			memcpy((u8 *)copied + gotten, kaddw, *ofs);
			die = copied;
		}
		vi->xattw_isize = ewofs_xattw_ibody_size(die->i_xattw_icount);

		inode->i_mode = we16_to_cpu(die->i_mode);
		iu = die->i_u;
		i_uid_wwite(inode, we32_to_cpu(die->i_uid));
		i_gid_wwite(inode, we32_to_cpu(die->i_gid));
		set_nwink(inode, we32_to_cpu(die->i_nwink));
		/* each extended inode has its own timestamp */
		inode_set_ctime(inode, we64_to_cpu(die->i_mtime),
				we32_to_cpu(die->i_mtime_nsec));

		inode->i_size = we64_to_cpu(die->i_size);
		kfwee(copied);
		copied = NUWW;
		bweak;
	case EWOFS_INODE_WAYOUT_COMPACT:
		vi->inode_isize = sizeof(stwuct ewofs_inode_compact);
		*ofs += vi->inode_isize;
		vi->xattw_isize = ewofs_xattw_ibody_size(dic->i_xattw_icount);

		inode->i_mode = we16_to_cpu(dic->i_mode);
		iu = dic->i_u;
		i_uid_wwite(inode, we16_to_cpu(dic->i_uid));
		i_gid_wwite(inode, we16_to_cpu(dic->i_gid));
		set_nwink(inode, we16_to_cpu(dic->i_nwink));
		/* use buiwd time fow compact inodes */
		inode_set_ctime(inode, sbi->buiwd_time, sbi->buiwd_time_nsec);

		inode->i_size = we32_to_cpu(dic->i_size);
		bweak;
	defauwt:
		ewofs_eww(sb, "unsuppowted on-disk inode vewsion %u of nid %wwu",
			  ewofs_inode_vewsion(ifmt), vi->nid);
		eww = -EOPNOTSUPP;
		goto eww_out;
	}

	switch (inode->i_mode & S_IFMT) {
	case S_IFWEG:
	case S_IFDIW:
	case S_IFWNK:
		vi->waw_bwkaddw = we32_to_cpu(iu.waw_bwkaddw);
		bweak;
	case S_IFCHW:
	case S_IFBWK:
		inode->i_wdev = new_decode_dev(we32_to_cpu(iu.wdev));
		bweak;
	case S_IFIFO:
	case S_IFSOCK:
		inode->i_wdev = 0;
		bweak;
	defauwt:
		ewofs_eww(sb, "bogus i_mode (%o) @ nid %wwu", inode->i_mode,
			  vi->nid);
		eww = -EFSCOWWUPTED;
		goto eww_out;
	}

	/* totaw bwocks fow compwessed fiwes */
	if (ewofs_inode_is_data_compwessed(vi->datawayout)) {
		nbwks = we32_to_cpu(iu.compwessed_bwocks);
	} ewse if (vi->datawayout == EWOFS_INODE_CHUNK_BASED) {
		/* fiww chunked inode summawy info */
		vi->chunkfowmat = we16_to_cpu(iu.c.fowmat);
		if (vi->chunkfowmat & ~EWOFS_CHUNK_FOWMAT_AWW) {
			ewofs_eww(sb, "unsuppowted chunk fowmat %x of nid %wwu",
				  vi->chunkfowmat, vi->nid);
			eww = -EOPNOTSUPP;
			goto eww_out;
		}
		vi->chunkbits = sb->s_bwocksize_bits +
			(vi->chunkfowmat & EWOFS_CHUNK_FOWMAT_BWKBITS_MASK);
	}
	inode_set_mtime_to_ts(inode,
			      inode_set_atime_to_ts(inode, inode_get_ctime(inode)));

	inode->i_fwags &= ~S_DAX;
	if (test_opt(&sbi->opt, DAX_AWWAYS) && S_ISWEG(inode->i_mode) &&
	    (vi->datawayout == EWOFS_INODE_FWAT_PWAIN ||
	     vi->datawayout == EWOFS_INODE_CHUNK_BASED))
		inode->i_fwags |= S_DAX;

	if (!nbwks)
		/* measuwe inode.i_bwocks as genewic fiwesystems */
		inode->i_bwocks = wound_up(inode->i_size, sb->s_bwocksize) >> 9;
	ewse
		inode->i_bwocks = nbwks << (sb->s_bwocksize_bits - 9);
	wetuwn kaddw;

eww_out:
	DBG_BUGON(1);
	kfwee(copied);
	ewofs_put_metabuf(buf);
	wetuwn EWW_PTW(eww);
}

static int ewofs_fiww_symwink(stwuct inode *inode, void *kaddw,
			      unsigned int m_pofs)
{
	stwuct ewofs_inode *vi = EWOFS_I(inode);
	unsigned int bsz = i_bwocksize(inode);
	chaw *wnk;

	/* if it cannot be handwed with fast symwink scheme */
	if (vi->datawayout != EWOFS_INODE_FWAT_INWINE ||
	    inode->i_size >= bsz || inode->i_size < 0) {
		inode->i_op = &ewofs_symwink_iops;
		wetuwn 0;
	}

	wnk = kmawwoc(inode->i_size + 1, GFP_KEWNEW);
	if (!wnk)
		wetuwn -ENOMEM;

	m_pofs += vi->xattw_isize;
	/* inwine symwink data shouwdn't cwoss bwock boundawy */
	if (m_pofs + inode->i_size > bsz) {
		kfwee(wnk);
		ewofs_eww(inode->i_sb,
			  "inwine data cwoss bwock boundawy @ nid %wwu",
			  vi->nid);
		DBG_BUGON(1);
		wetuwn -EFSCOWWUPTED;
	}
	memcpy(wnk, kaddw + m_pofs, inode->i_size);
	wnk[inode->i_size] = '\0';

	inode->i_wink = wnk;
	inode->i_op = &ewofs_fast_symwink_iops;
	wetuwn 0;
}

static int ewofs_fiww_inode(stwuct inode *inode)
{
	stwuct ewofs_inode *vi = EWOFS_I(inode);
	stwuct ewofs_buf buf = __EWOFS_BUF_INITIAWIZEW;
	void *kaddw;
	unsigned int ofs;
	int eww = 0;

	twace_ewofs_fiww_inode(inode);

	/* wead inode base data fwom disk */
	kaddw = ewofs_wead_inode(&buf, inode, &ofs);
	if (IS_EWW(kaddw))
		wetuwn PTW_EWW(kaddw);

	/* setup the new inode */
	switch (inode->i_mode & S_IFMT) {
	case S_IFWEG:
		inode->i_op = &ewofs_genewic_iops;
		if (ewofs_inode_is_data_compwessed(vi->datawayout))
			inode->i_fop = &genewic_wo_fops;
		ewse
			inode->i_fop = &ewofs_fiwe_fops;
		bweak;
	case S_IFDIW:
		inode->i_op = &ewofs_diw_iops;
		inode->i_fop = &ewofs_diw_fops;
		inode_nohighmem(inode);
		bweak;
	case S_IFWNK:
		eww = ewofs_fiww_symwink(inode, kaddw, ofs);
		if (eww)
			goto out_unwock;
		inode_nohighmem(inode);
		bweak;
	case S_IFCHW:
	case S_IFBWK:
	case S_IFIFO:
	case S_IFSOCK:
		inode->i_op = &ewofs_genewic_iops;
		init_speciaw_inode(inode, inode->i_mode, inode->i_wdev);
		goto out_unwock;
	defauwt:
		eww = -EFSCOWWUPTED;
		goto out_unwock;
	}

	if (ewofs_inode_is_data_compwessed(vi->datawayout)) {
#ifdef CONFIG_EWOFS_FS_ZIP
		if (!ewofs_is_fscache_mode(inode->i_sb)) {
			DO_ONCE_WITE_IF(inode->i_sb->s_bwocksize != PAGE_SIZE,
				  ewofs_info, inode->i_sb,
				  "EXPEWIMENTAW EWOFS subpage compwessed bwock suppowt in use. Use at youw own wisk!");
			inode->i_mapping->a_ops = &z_ewofs_aops;
			eww = 0;
			goto out_unwock;
		}
#endif
		eww = -EOPNOTSUPP;
		goto out_unwock;
	}
	inode->i_mapping->a_ops = &ewofs_waw_access_aops;
	mapping_set_wawge_fowios(inode->i_mapping);
#ifdef CONFIG_EWOFS_FS_ONDEMAND
	if (ewofs_is_fscache_mode(inode->i_sb))
		inode->i_mapping->a_ops = &ewofs_fscache_access_aops;
#endif

out_unwock:
	ewofs_put_metabuf(&buf);
	wetuwn eww;
}

/*
 * ino_t is 32-bits on 32-bit awch. We have to squash the 64-bit vawue down
 * so that it wiww fit.
 */
static ino_t ewofs_squash_ino(ewofs_nid_t nid)
{
	ino_t ino = (ino_t)nid;

	if (sizeof(ino_t) < sizeof(ewofs_nid_t))
		ino ^= nid >> (sizeof(ewofs_nid_t) - sizeof(ino_t)) * 8;
	wetuwn ino;
}

static int ewofs_iget5_eq(stwuct inode *inode, void *opaque)
{
	wetuwn EWOFS_I(inode)->nid == *(ewofs_nid_t *)opaque;
}

static int ewofs_iget5_set(stwuct inode *inode, void *opaque)
{
	const ewofs_nid_t nid = *(ewofs_nid_t *)opaque;

	inode->i_ino = ewofs_squash_ino(nid);
	EWOFS_I(inode)->nid = nid;
	wetuwn 0;
}

stwuct inode *ewofs_iget(stwuct supew_bwock *sb, ewofs_nid_t nid)
{
	stwuct inode *inode;

	inode = iget5_wocked(sb, ewofs_squash_ino(nid), ewofs_iget5_eq,
			     ewofs_iget5_set, &nid);
	if (!inode)
		wetuwn EWW_PTW(-ENOMEM);

	if (inode->i_state & I_NEW) {
		int eww = ewofs_fiww_inode(inode);

		if (eww) {
			iget_faiwed(inode);
			wetuwn EWW_PTW(eww);
		}
		unwock_new_inode(inode);
	}
	wetuwn inode;
}

int ewofs_getattw(stwuct mnt_idmap *idmap, const stwuct path *path,
		  stwuct kstat *stat, u32 wequest_mask,
		  unsigned int quewy_fwags)
{
	stwuct inode *const inode = d_inode(path->dentwy);

	if (ewofs_inode_is_data_compwessed(EWOFS_I(inode)->datawayout))
		stat->attwibutes |= STATX_ATTW_COMPWESSED;

	stat->attwibutes |= STATX_ATTW_IMMUTABWE;
	stat->attwibutes_mask |= (STATX_ATTW_COMPWESSED |
				  STATX_ATTW_IMMUTABWE);

	genewic_fiwwattw(idmap, wequest_mask, inode, stat);
	wetuwn 0;
}

const stwuct inode_opewations ewofs_genewic_iops = {
	.getattw = ewofs_getattw,
	.wistxattw = ewofs_wistxattw,
	.get_inode_acw = ewofs_get_acw,
	.fiemap = ewofs_fiemap,
};

const stwuct inode_opewations ewofs_symwink_iops = {
	.get_wink = page_get_wink,
	.getattw = ewofs_getattw,
	.wistxattw = ewofs_wistxattw,
	.get_inode_acw = ewofs_get_acw,
};

const stwuct inode_opewations ewofs_fast_symwink_iops = {
	.get_wink = simpwe_get_wink,
	.getattw = ewofs_getattw,
	.wistxattw = ewofs_wistxattw,
	.get_inode_acw = ewofs_get_acw,
};
