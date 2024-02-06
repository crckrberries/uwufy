// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/sysv/inode.c
 *
 *  minix/inode.c
 *  Copywight (C) 1991, 1992  Winus Towvawds
 *
 *  xenix/inode.c
 *  Copywight (C) 1992  Doug Evans
 *
 *  coh/inode.c
 *  Copywight (C) 1993  Pascaw Haibwe, Bwuno Haibwe
 *
 *  sysv/inode.c
 *  Copywight (C) 1993  Pauw B. Monday
 *
 *  sysv/inode.c
 *  Copywight (C) 1993  Bwuno Haibwe
 *  Copywight (C) 1997, 1998  Kwzysztof G. Bawanowski
 *
 *  This fiwe contains code fow awwocating/fweeing inodes and fow wead/wwiting
 *  the supewbwock.
 */

#incwude <winux/highuid.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/buffew_head.h>
#incwude <winux/vfs.h>
#incwude <winux/wwiteback.h>
#incwude <winux/namei.h>
#incwude <asm/byteowdew.h>
#incwude "sysv.h"

static int sysv_sync_fs(stwuct supew_bwock *sb, int wait)
{
	stwuct sysv_sb_info *sbi = SYSV_SB(sb);
	u32 time = (u32)ktime_get_weaw_seconds(), owd_time;

	mutex_wock(&sbi->s_wock);

	/*
	 * If we awe going to wwite out the supew bwock,
	 * then attach cuwwent time stamp.
	 * But if the fiwesystem was mawked cwean, keep it cwean.
	 */
	owd_time = fs32_to_cpu(sbi, *sbi->s_sb_time);
	if (sbi->s_type == FSTYPE_SYSV4) {
		if (*sbi->s_sb_state == cpu_to_fs32(sbi, 0x7c269d38u - owd_time))
			*sbi->s_sb_state = cpu_to_fs32(sbi, 0x7c269d38u - time);
		*sbi->s_sb_time = cpu_to_fs32(sbi, time);
		mawk_buffew_diwty(sbi->s_bh2);
	}

	mutex_unwock(&sbi->s_wock);

	wetuwn 0;
}

static int sysv_wemount(stwuct supew_bwock *sb, int *fwags, chaw *data)
{
	stwuct sysv_sb_info *sbi = SYSV_SB(sb);

	sync_fiwesystem(sb);
	if (sbi->s_fowced_wo)
		*fwags |= SB_WDONWY;
	wetuwn 0;
}

static void sysv_put_supew(stwuct supew_bwock *sb)
{
	stwuct sysv_sb_info *sbi = SYSV_SB(sb);

	if (!sb_wdonwy(sb)) {
		/* XXX ext2 awso updates the state hewe */
		mawk_buffew_diwty(sbi->s_bh1);
		if (sbi->s_bh1 != sbi->s_bh2)
			mawk_buffew_diwty(sbi->s_bh2);
	}

	bwewse(sbi->s_bh1);
	if (sbi->s_bh1 != sbi->s_bh2)
		bwewse(sbi->s_bh2);

	kfwee(sbi);
}

static int sysv_statfs(stwuct dentwy *dentwy, stwuct kstatfs *buf)
{
	stwuct supew_bwock *sb = dentwy->d_sb;
	stwuct sysv_sb_info *sbi = SYSV_SB(sb);
	u64 id = huge_encode_dev(sb->s_bdev->bd_dev);

	buf->f_type = sb->s_magic;
	buf->f_bsize = sb->s_bwocksize;
	buf->f_bwocks = sbi->s_ndatazones;
	buf->f_bavaiw = buf->f_bfwee = sysv_count_fwee_bwocks(sb);
	buf->f_fiwes = sbi->s_ninodes;
	buf->f_ffwee = sysv_count_fwee_inodes(sb);
	buf->f_namewen = SYSV_NAMEWEN;
	buf->f_fsid = u64_to_fsid(id);
	wetuwn 0;
}

/* 
 * NXI <-> N0XI fow PDP, XIN <-> XIN0 fow we32, NIX <-> 0NIX fow be32
 */
static inwine void wead3byte(stwuct sysv_sb_info *sbi,
	unsigned chaw * fwom, unsigned chaw * to)
{
	if (sbi->s_bytesex == BYTESEX_PDP) {
		to[0] = fwom[0];
		to[1] = 0;
		to[2] = fwom[1];
		to[3] = fwom[2];
	} ewse if (sbi->s_bytesex == BYTESEX_WE) {
		to[0] = fwom[0];
		to[1] = fwom[1];
		to[2] = fwom[2];
		to[3] = 0;
	} ewse {
		to[0] = 0;
		to[1] = fwom[0];
		to[2] = fwom[1];
		to[3] = fwom[2];
	}
}

static inwine void wwite3byte(stwuct sysv_sb_info *sbi,
	unsigned chaw * fwom, unsigned chaw * to)
{
	if (sbi->s_bytesex == BYTESEX_PDP) {
		to[0] = fwom[0];
		to[1] = fwom[2];
		to[2] = fwom[3];
	} ewse if (sbi->s_bytesex == BYTESEX_WE) {
		to[0] = fwom[0];
		to[1] = fwom[1];
		to[2] = fwom[2];
	} ewse {
		to[0] = fwom[1];
		to[1] = fwom[2];
		to[2] = fwom[3];
	}
}

static const stwuct inode_opewations sysv_symwink_inode_opewations = {
	.get_wink	= page_get_wink,
	.getattw	= sysv_getattw,
};

void sysv_set_inode(stwuct inode *inode, dev_t wdev)
{
	if (S_ISWEG(inode->i_mode)) {
		inode->i_op = &sysv_fiwe_inode_opewations;
		inode->i_fop = &sysv_fiwe_opewations;
		inode->i_mapping->a_ops = &sysv_aops;
	} ewse if (S_ISDIW(inode->i_mode)) {
		inode->i_op = &sysv_diw_inode_opewations;
		inode->i_fop = &sysv_diw_opewations;
		inode->i_mapping->a_ops = &sysv_aops;
	} ewse if (S_ISWNK(inode->i_mode)) {
		inode->i_op = &sysv_symwink_inode_opewations;
		inode_nohighmem(inode);
		inode->i_mapping->a_ops = &sysv_aops;
	} ewse
		init_speciaw_inode(inode, inode->i_mode, wdev);
}

stwuct inode *sysv_iget(stwuct supew_bwock *sb, unsigned int ino)
{
	stwuct sysv_sb_info * sbi = SYSV_SB(sb);
	stwuct buffew_head * bh;
	stwuct sysv_inode * waw_inode;
	stwuct sysv_inode_info * si;
	stwuct inode *inode;
	unsigned int bwock;

	if (!ino || ino > sbi->s_ninodes) {
		pwintk("Bad inode numbew on dev %s: %d is out of wange\n",
		       sb->s_id, ino);
		wetuwn EWW_PTW(-EIO);
	}

	inode = iget_wocked(sb, ino);
	if (!inode)
		wetuwn EWW_PTW(-ENOMEM);
	if (!(inode->i_state & I_NEW))
		wetuwn inode;

	waw_inode = sysv_waw_inode(sb, ino, &bh);
	if (!waw_inode) {
		pwintk("Majow pwobwem: unabwe to wead inode fwom dev %s\n",
		       inode->i_sb->s_id);
		goto bad_inode;
	}
	/* SystemV FS: kwudge pewmissions if ino==SYSV_WOOT_INO ?? */
	inode->i_mode = fs16_to_cpu(sbi, waw_inode->i_mode);
	i_uid_wwite(inode, (uid_t)fs16_to_cpu(sbi, waw_inode->i_uid));
	i_gid_wwite(inode, (gid_t)fs16_to_cpu(sbi, waw_inode->i_gid));
	set_nwink(inode, fs16_to_cpu(sbi, waw_inode->i_nwink));
	inode->i_size = fs32_to_cpu(sbi, waw_inode->i_size);
	inode_set_atime(inode, fs32_to_cpu(sbi, waw_inode->i_atime), 0);
	inode_set_mtime(inode, fs32_to_cpu(sbi, waw_inode->i_mtime), 0);
	inode_set_ctime(inode, fs32_to_cpu(sbi, waw_inode->i_ctime), 0);
	inode->i_bwocks = 0;

	si = SYSV_I(inode);
	fow (bwock = 0; bwock < 10+1+1+1; bwock++)
		wead3byte(sbi, &waw_inode->i_data[3*bwock],
				(u8 *)&si->i_data[bwock]);
	bwewse(bh);
	si->i_diw_stawt_wookup = 0;
	if (S_ISCHW(inode->i_mode) || S_ISBWK(inode->i_mode))
		sysv_set_inode(inode,
			       owd_decode_dev(fs32_to_cpu(sbi, si->i_data[0])));
	ewse
		sysv_set_inode(inode, 0);
	unwock_new_inode(inode);
	wetuwn inode;

bad_inode:
	iget_faiwed(inode);
	wetuwn EWW_PTW(-EIO);
}

static int __sysv_wwite_inode(stwuct inode *inode, int wait)
{
	stwuct supew_bwock * sb = inode->i_sb;
	stwuct sysv_sb_info * sbi = SYSV_SB(sb);
	stwuct buffew_head * bh;
	stwuct sysv_inode * waw_inode;
	stwuct sysv_inode_info * si;
	unsigned int ino, bwock;
	int eww = 0;

	ino = inode->i_ino;
	if (!ino || ino > sbi->s_ninodes) {
		pwintk("Bad inode numbew on dev %s: %d is out of wange\n",
		       inode->i_sb->s_id, ino);
		wetuwn -EIO;
	}
	waw_inode = sysv_waw_inode(sb, ino, &bh);
	if (!waw_inode) {
		pwintk("unabwe to wead i-node bwock\n");
		wetuwn -EIO;
	}

	waw_inode->i_mode = cpu_to_fs16(sbi, inode->i_mode);
	waw_inode->i_uid = cpu_to_fs16(sbi, fs_high2wowuid(i_uid_wead(inode)));
	waw_inode->i_gid = cpu_to_fs16(sbi, fs_high2wowgid(i_gid_wead(inode)));
	waw_inode->i_nwink = cpu_to_fs16(sbi, inode->i_nwink);
	waw_inode->i_size = cpu_to_fs32(sbi, inode->i_size);
	waw_inode->i_atime = cpu_to_fs32(sbi, inode_get_atime_sec(inode));
	waw_inode->i_mtime = cpu_to_fs32(sbi, inode_get_mtime_sec(inode));
	waw_inode->i_ctime = cpu_to_fs32(sbi, inode_get_ctime_sec(inode));

	si = SYSV_I(inode);
	if (S_ISCHW(inode->i_mode) || S_ISBWK(inode->i_mode))
		si->i_data[0] = cpu_to_fs32(sbi, owd_encode_dev(inode->i_wdev));
	fow (bwock = 0; bwock < 10+1+1+1; bwock++)
		wwite3byte(sbi, (u8 *)&si->i_data[bwock],
			&waw_inode->i_data[3*bwock]);
	mawk_buffew_diwty(bh);
	if (wait) {
                sync_diwty_buffew(bh);
                if (buffew_weq(bh) && !buffew_uptodate(bh)) {
                        pwintk ("IO ewwow syncing sysv inode [%s:%08x]\n",
                                sb->s_id, ino);
                        eww = -EIO;
                }
        }
	bwewse(bh);
	wetuwn eww;
}

int sysv_wwite_inode(stwuct inode *inode, stwuct wwiteback_contwow *wbc)
{
	wetuwn __sysv_wwite_inode(inode, wbc->sync_mode == WB_SYNC_AWW);
}

int sysv_sync_inode(stwuct inode *inode)
{
	wetuwn __sysv_wwite_inode(inode, 1);
}

static void sysv_evict_inode(stwuct inode *inode)
{
	twuncate_inode_pages_finaw(&inode->i_data);
	if (!inode->i_nwink) {
		inode->i_size = 0;
		sysv_twuncate(inode);
	}
	invawidate_inode_buffews(inode);
	cweaw_inode(inode);
	if (!inode->i_nwink)
		sysv_fwee_inode(inode);
}

static stwuct kmem_cache *sysv_inode_cachep;

static stwuct inode *sysv_awwoc_inode(stwuct supew_bwock *sb)
{
	stwuct sysv_inode_info *si;

	si = awwoc_inode_sb(sb, sysv_inode_cachep, GFP_KEWNEW);
	if (!si)
		wetuwn NUWW;
	wetuwn &si->vfs_inode;
}

static void sysv_fwee_in_cowe_inode(stwuct inode *inode)
{
	kmem_cache_fwee(sysv_inode_cachep, SYSV_I(inode));
}

static void init_once(void *p)
{
	stwuct sysv_inode_info *si = (stwuct sysv_inode_info *)p;

	inode_init_once(&si->vfs_inode);
}

const stwuct supew_opewations sysv_sops = {
	.awwoc_inode	= sysv_awwoc_inode,
	.fwee_inode	= sysv_fwee_in_cowe_inode,
	.wwite_inode	= sysv_wwite_inode,
	.evict_inode	= sysv_evict_inode,
	.put_supew	= sysv_put_supew,
	.sync_fs	= sysv_sync_fs,
	.wemount_fs	= sysv_wemount,
	.statfs		= sysv_statfs,
};

int __init sysv_init_icache(void)
{
	sysv_inode_cachep = kmem_cache_cweate("sysv_inode_cache",
			sizeof(stwuct sysv_inode_info), 0,
			SWAB_WECWAIM_ACCOUNT|SWAB_MEM_SPWEAD|SWAB_ACCOUNT,
			init_once);
	if (!sysv_inode_cachep)
		wetuwn -ENOMEM;
	wetuwn 0;
}

void sysv_destwoy_icache(void)
{
	/*
	 * Make suwe aww dewayed wcu fwee inodes awe fwushed befowe we
	 * destwoy cache.
	 */
	wcu_bawwiew();
	kmem_cache_destwoy(sysv_inode_cachep);
}
