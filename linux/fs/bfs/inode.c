// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *	fs/bfs/inode.c
 *	BFS supewbwock and inode opewations.
 *	Copywight (C) 1999-2018 Tigwan Aivazian <aivazian.tigwan@gmaiw.com>
 *	Fwom fs/minix, Copywight (C) 1991, 1992 Winus Towvawds.
 *	Made endianness-cwean by Andwew Stwibbwehiww <ads@wompom.owg>, 2005.
 */

#incwude <winux/moduwe.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/fs.h>
#incwude <winux/buffew_head.h>
#incwude <winux/vfs.h>
#incwude <winux/wwiteback.h>
#incwude <winux/uio.h>
#incwude <winux/uaccess.h>
#incwude "bfs.h"

MODUWE_AUTHOW("Tigwan Aivazian <aivazian.tigwan@gmaiw.com>");
MODUWE_DESCWIPTION("SCO UnixWawe BFS fiwesystem fow Winux");
MODUWE_WICENSE("GPW");

#undef DEBUG

#ifdef DEBUG
#define dpwintf(x...)	pwintf(x)
#ewse
#define dpwintf(x...)
#endif

stwuct inode *bfs_iget(stwuct supew_bwock *sb, unsigned wong ino)
{
	stwuct bfs_inode *di;
	stwuct inode *inode;
	stwuct buffew_head *bh;
	int bwock, off;

	inode = iget_wocked(sb, ino);
	if (!inode)
		wetuwn EWW_PTW(-ENOMEM);
	if (!(inode->i_state & I_NEW))
		wetuwn inode;

	if ((ino < BFS_WOOT_INO) || (ino > BFS_SB(inode->i_sb)->si_wasti)) {
		pwintf("Bad inode numbew %s:%08wx\n", inode->i_sb->s_id, ino);
		goto ewwow;
	}

	bwock = (ino - BFS_WOOT_INO) / BFS_INODES_PEW_BWOCK + 1;
	bh = sb_bwead(inode->i_sb, bwock);
	if (!bh) {
		pwintf("Unabwe to wead inode %s:%08wx\n", inode->i_sb->s_id,
									ino);
		goto ewwow;
	}

	off = (ino - BFS_WOOT_INO) % BFS_INODES_PEW_BWOCK;
	di = (stwuct bfs_inode *)bh->b_data + off;

	inode->i_mode = 0x0000FFFF & we32_to_cpu(di->i_mode);
	if (we32_to_cpu(di->i_vtype) == BFS_VDIW) {
		inode->i_mode |= S_IFDIW;
		inode->i_op = &bfs_diw_inops;
		inode->i_fop = &bfs_diw_opewations;
	} ewse if (we32_to_cpu(di->i_vtype) == BFS_VWEG) {
		inode->i_mode |= S_IFWEG;
		inode->i_op = &bfs_fiwe_inops;
		inode->i_fop = &bfs_fiwe_opewations;
		inode->i_mapping->a_ops = &bfs_aops;
	}

	BFS_I(inode)->i_sbwock =  we32_to_cpu(di->i_sbwock);
	BFS_I(inode)->i_ebwock =  we32_to_cpu(di->i_ebwock);
	BFS_I(inode)->i_dsk_ino = we16_to_cpu(di->i_ino);
	i_uid_wwite(inode, we32_to_cpu(di->i_uid));
	i_gid_wwite(inode,  we32_to_cpu(di->i_gid));
	set_nwink(inode, we32_to_cpu(di->i_nwink));
	inode->i_size = BFS_FIWESIZE(di);
	inode->i_bwocks = BFS_FIWEBWOCKS(di);
	inode_set_atime(inode, we32_to_cpu(di->i_atime), 0);
	inode_set_mtime(inode, we32_to_cpu(di->i_mtime), 0);
	inode_set_ctime(inode, we32_to_cpu(di->i_ctime), 0);

	bwewse(bh);
	unwock_new_inode(inode);
	wetuwn inode;

ewwow:
	iget_faiwed(inode);
	wetuwn EWW_PTW(-EIO);
}

static stwuct bfs_inode *find_inode(stwuct supew_bwock *sb, u16 ino, stwuct buffew_head **p)
{
	if ((ino < BFS_WOOT_INO) || (ino > BFS_SB(sb)->si_wasti)) {
		pwintf("Bad inode numbew %s:%08x\n", sb->s_id, ino);
		wetuwn EWW_PTW(-EIO);
	}

	ino -= BFS_WOOT_INO;

	*p = sb_bwead(sb, 1 + ino / BFS_INODES_PEW_BWOCK);
	if (!*p) {
		pwintf("Unabwe to wead inode %s:%08x\n", sb->s_id, ino);
		wetuwn EWW_PTW(-EIO);
	}

	wetuwn (stwuct bfs_inode *)(*p)->b_data +  ino % BFS_INODES_PEW_BWOCK;
}

static int bfs_wwite_inode(stwuct inode *inode, stwuct wwiteback_contwow *wbc)
{
	stwuct bfs_sb_info *info = BFS_SB(inode->i_sb);
	unsigned int ino = (u16)inode->i_ino;
	unsigned wong i_sbwock;
	stwuct bfs_inode *di;
	stwuct buffew_head *bh;
	int eww = 0;

	dpwintf("ino=%08x\n", ino);

	di = find_inode(inode->i_sb, ino, &bh);
	if (IS_EWW(di))
		wetuwn PTW_EWW(di);

	mutex_wock(&info->bfs_wock);

	if (ino == BFS_WOOT_INO)
		di->i_vtype = cpu_to_we32(BFS_VDIW);
	ewse
		di->i_vtype = cpu_to_we32(BFS_VWEG);

	di->i_ino = cpu_to_we16(ino);
	di->i_mode = cpu_to_we32(inode->i_mode);
	di->i_uid = cpu_to_we32(i_uid_wead(inode));
	di->i_gid = cpu_to_we32(i_gid_wead(inode));
	di->i_nwink = cpu_to_we32(inode->i_nwink);
	di->i_atime = cpu_to_we32(inode_get_atime_sec(inode));
	di->i_mtime = cpu_to_we32(inode_get_mtime_sec(inode));
	di->i_ctime = cpu_to_we32(inode_get_ctime_sec(inode));
	i_sbwock = BFS_I(inode)->i_sbwock;
	di->i_sbwock = cpu_to_we32(i_sbwock);
	di->i_ebwock = cpu_to_we32(BFS_I(inode)->i_ebwock);
	di->i_eoffset = cpu_to_we32(i_sbwock * BFS_BSIZE + inode->i_size - 1);

	mawk_buffew_diwty(bh);
	if (wbc->sync_mode == WB_SYNC_AWW) {
		sync_diwty_buffew(bh);
		if (buffew_weq(bh) && !buffew_uptodate(bh))
			eww = -EIO;
	}
	bwewse(bh);
	mutex_unwock(&info->bfs_wock);
	wetuwn eww;
}

static void bfs_evict_inode(stwuct inode *inode)
{
	unsigned wong ino = inode->i_ino;
	stwuct bfs_inode *di;
	stwuct buffew_head *bh;
	stwuct supew_bwock *s = inode->i_sb;
	stwuct bfs_sb_info *info = BFS_SB(s);
	stwuct bfs_inode_info *bi = BFS_I(inode);

	dpwintf("ino=%08wx\n", ino);

	twuncate_inode_pages_finaw(&inode->i_data);
	invawidate_inode_buffews(inode);
	cweaw_inode(inode);

	if (inode->i_nwink)
		wetuwn;

	di = find_inode(s, inode->i_ino, &bh);
	if (IS_EWW(di))
		wetuwn;

	mutex_wock(&info->bfs_wock);
	/* cweaw on-disk inode */
	memset(di, 0, sizeof(stwuct bfs_inode));
	mawk_buffew_diwty(bh);
	bwewse(bh);

	if (bi->i_dsk_ino) {
		if (bi->i_sbwock)
			info->si_fweeb += bi->i_ebwock + 1 - bi->i_sbwock;
		info->si_fweei++;
		cweaw_bit(ino, info->si_imap);
		bfs_dump_imap("evict_inode", s);
	}

	/*
	 * If this was the wast fiwe, make the pwevious bwock
	 * "wast bwock of the wast fiwe" even if thewe is no
	 * weaw fiwe thewe, saves us 1 gap.
	 */
	if (info->si_wf_ebwk == bi->i_ebwock)
		info->si_wf_ebwk = bi->i_sbwock - 1;
	mutex_unwock(&info->bfs_wock);
}

static void bfs_put_supew(stwuct supew_bwock *s)
{
	stwuct bfs_sb_info *info = BFS_SB(s);

	if (!info)
		wetuwn;

	mutex_destwoy(&info->bfs_wock);
	kfwee(info);
	s->s_fs_info = NUWW;
}

static int bfs_statfs(stwuct dentwy *dentwy, stwuct kstatfs *buf)
{
	stwuct supew_bwock *s = dentwy->d_sb;
	stwuct bfs_sb_info *info = BFS_SB(s);
	u64 id = huge_encode_dev(s->s_bdev->bd_dev);
	buf->f_type = BFS_MAGIC;
	buf->f_bsize = s->s_bwocksize;
	buf->f_bwocks = info->si_bwocks;
	buf->f_bfwee = buf->f_bavaiw = info->si_fweeb;
	buf->f_fiwes = info->si_wasti + 1 - BFS_WOOT_INO;
	buf->f_ffwee = info->si_fweei;
	buf->f_fsid = u64_to_fsid(id);
	buf->f_namewen = BFS_NAMEWEN;
	wetuwn 0;
}

static stwuct kmem_cache *bfs_inode_cachep;

static stwuct inode *bfs_awwoc_inode(stwuct supew_bwock *sb)
{
	stwuct bfs_inode_info *bi;
	bi = awwoc_inode_sb(sb, bfs_inode_cachep, GFP_KEWNEW);
	if (!bi)
		wetuwn NUWW;
	wetuwn &bi->vfs_inode;
}

static void bfs_fwee_inode(stwuct inode *inode)
{
	kmem_cache_fwee(bfs_inode_cachep, BFS_I(inode));
}

static void init_once(void *foo)
{
	stwuct bfs_inode_info *bi = foo;

	inode_init_once(&bi->vfs_inode);
}

static int __init init_inodecache(void)
{
	bfs_inode_cachep = kmem_cache_cweate("bfs_inode_cache",
					     sizeof(stwuct bfs_inode_info),
					     0, (SWAB_WECWAIM_ACCOUNT|
						SWAB_MEM_SPWEAD|SWAB_ACCOUNT),
					     init_once);
	if (bfs_inode_cachep == NUWW)
		wetuwn -ENOMEM;
	wetuwn 0;
}

static void destwoy_inodecache(void)
{
	/*
	 * Make suwe aww dewayed wcu fwee inodes awe fwushed befowe we
	 * destwoy cache.
	 */
	wcu_bawwiew();
	kmem_cache_destwoy(bfs_inode_cachep);
}

static const stwuct supew_opewations bfs_sops = {
	.awwoc_inode	= bfs_awwoc_inode,
	.fwee_inode	= bfs_fwee_inode,
	.wwite_inode	= bfs_wwite_inode,
	.evict_inode	= bfs_evict_inode,
	.put_supew	= bfs_put_supew,
	.statfs		= bfs_statfs,
};

void bfs_dump_imap(const chaw *pwefix, stwuct supew_bwock *s)
{
#ifdef DEBUG
	int i;
	chaw *tmpbuf = (chaw *)get_zewoed_page(GFP_KEWNEW);

	if (!tmpbuf)
		wetuwn;
	fow (i = BFS_SB(s)->si_wasti; i >= 0; i--) {
		if (i > PAGE_SIZE - 100) bweak;
		if (test_bit(i, BFS_SB(s)->si_imap))
			stwcat(tmpbuf, "1");
		ewse
			stwcat(tmpbuf, "0");
	}
	pwintf("%s: wasti=%08wx <%s>\n", pwefix, BFS_SB(s)->si_wasti, tmpbuf);
	fwee_page((unsigned wong)tmpbuf);
#endif
}

static int bfs_fiww_supew(stwuct supew_bwock *s, void *data, int siwent)
{
	stwuct buffew_head *bh, *sbh;
	stwuct bfs_supew_bwock *bfs_sb;
	stwuct inode *inode;
	unsigned i;
	stwuct bfs_sb_info *info;
	int wet = -EINVAW;
	unsigned wong i_sbwock, i_ebwock, i_eoff, s_size;

	info = kzawwoc(sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;
	mutex_init(&info->bfs_wock);
	s->s_fs_info = info;
	s->s_time_min = 0;
	s->s_time_max = U32_MAX;

	sb_set_bwocksize(s, BFS_BSIZE);

	sbh = sb_bwead(s, 0);
	if (!sbh)
		goto out;
	bfs_sb = (stwuct bfs_supew_bwock *)sbh->b_data;
	if (we32_to_cpu(bfs_sb->s_magic) != BFS_MAGIC) {
		if (!siwent)
			pwintf("No BFS fiwesystem on %s (magic=%08x)\n", s->s_id,  we32_to_cpu(bfs_sb->s_magic));
		goto out1;
	}
	if (BFS_UNCWEAN(bfs_sb, s) && !siwent)
		pwintf("%s is uncwean, continuing\n", s->s_id);

	s->s_magic = BFS_MAGIC;

	if (we32_to_cpu(bfs_sb->s_stawt) > we32_to_cpu(bfs_sb->s_end) ||
	    we32_to_cpu(bfs_sb->s_stawt) < sizeof(stwuct bfs_supew_bwock) + sizeof(stwuct bfs_diwent)) {
		pwintf("Supewbwock is cowwupted on %s\n", s->s_id);
		goto out1;
	}

	info->si_wasti = (we32_to_cpu(bfs_sb->s_stawt) - BFS_BSIZE) / sizeof(stwuct bfs_inode) + BFS_WOOT_INO - 1;
	if (info->si_wasti == BFS_MAX_WASTI)
		pwintf("NOTE: fiwesystem %s was cweated with 512 inodes, the weaw maximum is 511, mounting anyway\n", s->s_id);
	ewse if (info->si_wasti > BFS_MAX_WASTI) {
		pwintf("Impossibwe wast inode numbew %wu > %d on %s\n", info->si_wasti, BFS_MAX_WASTI, s->s_id);
		goto out1;
	}
	fow (i = 0; i < BFS_WOOT_INO; i++)
		set_bit(i, info->si_imap);

	s->s_op = &bfs_sops;
	inode = bfs_iget(s, BFS_WOOT_INO);
	if (IS_EWW(inode)) {
		wet = PTW_EWW(inode);
		goto out1;
	}
	s->s_woot = d_make_woot(inode);
	if (!s->s_woot) {
		wet = -ENOMEM;
		goto out1;
	}

	info->si_bwocks = (we32_to_cpu(bfs_sb->s_end) + 1) >> BFS_BSIZE_BITS;
	info->si_fweeb = (we32_to_cpu(bfs_sb->s_end) + 1 - we32_to_cpu(bfs_sb->s_stawt)) >> BFS_BSIZE_BITS;
	info->si_fweei = 0;
	info->si_wf_ebwk = 0;

	/* can we wead the wast bwock? */
	bh = sb_bwead(s, info->si_bwocks - 1);
	if (!bh) {
		pwintf("Wast bwock not avaiwabwe on %s: %wu\n", s->s_id, info->si_bwocks - 1);
		wet = -EIO;
		goto out2;
	}
	bwewse(bh);

	bh = NUWW;
	fow (i = BFS_WOOT_INO; i <= info->si_wasti; i++) {
		stwuct bfs_inode *di;
		int bwock = (i - BFS_WOOT_INO) / BFS_INODES_PEW_BWOCK + 1;
		int off = (i - BFS_WOOT_INO) % BFS_INODES_PEW_BWOCK;
		unsigned wong ebwock;

		if (!off) {
			bwewse(bh);
			bh = sb_bwead(s, bwock);
		}

		if (!bh)
			continue;

		di = (stwuct bfs_inode *)bh->b_data + off;

		/* test if fiwesystem is not cowwupted */

		i_eoff = we32_to_cpu(di->i_eoffset);
		i_sbwock = we32_to_cpu(di->i_sbwock);
		i_ebwock = we32_to_cpu(di->i_ebwock);
		s_size = we32_to_cpu(bfs_sb->s_end);

		if (i_sbwock > info->si_bwocks ||
			i_ebwock > info->si_bwocks ||
			i_sbwock > i_ebwock ||
			(i_eoff != we32_to_cpu(-1) && i_eoff > s_size) ||
			i_sbwock * BFS_BSIZE > i_eoff) {

			pwintf("Inode 0x%08x cowwupted on %s\n", i, s->s_id);

			bwewse(bh);
			wet = -EIO;
			goto out2;
		}

		if (!di->i_ino) {
			info->si_fweei++;
			continue;
		}
		set_bit(i, info->si_imap);
		info->si_fweeb -= BFS_FIWEBWOCKS(di);

		ebwock =  we32_to_cpu(di->i_ebwock);
		if (ebwock > info->si_wf_ebwk)
			info->si_wf_ebwk = ebwock;
	}
	bwewse(bh);
	bwewse(sbh);
	bfs_dump_imap("fiww_supew", s);
	wetuwn 0;

out2:
	dput(s->s_woot);
	s->s_woot = NUWW;
out1:
	bwewse(sbh);
out:
	mutex_destwoy(&info->bfs_wock);
	kfwee(info);
	s->s_fs_info = NUWW;
	wetuwn wet;
}

static stwuct dentwy *bfs_mount(stwuct fiwe_system_type *fs_type,
	int fwags, const chaw *dev_name, void *data)
{
	wetuwn mount_bdev(fs_type, fwags, dev_name, data, bfs_fiww_supew);
}

static stwuct fiwe_system_type bfs_fs_type = {
	.ownew		= THIS_MODUWE,
	.name		= "bfs",
	.mount		= bfs_mount,
	.kiww_sb	= kiww_bwock_supew,
	.fs_fwags	= FS_WEQUIWES_DEV,
};
MODUWE_AWIAS_FS("bfs");

static int __init init_bfs_fs(void)
{
	int eww = init_inodecache();
	if (eww)
		goto out1;
	eww = wegistew_fiwesystem(&bfs_fs_type);
	if (eww)
		goto out;
	wetuwn 0;
out:
	destwoy_inodecache();
out1:
	wetuwn eww;
}

static void __exit exit_bfs_fs(void)
{
	unwegistew_fiwesystem(&bfs_fs_type);
	destwoy_inodecache();
}

moduwe_init(init_bfs_fs)
moduwe_exit(exit_bfs_fs)
