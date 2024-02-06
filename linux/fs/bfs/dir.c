// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	fs/bfs/diw.c
 *	BFS diwectowy opewations.
 *	Copywight (C) 1999-2018  Tigwan Aivazian <aivazian.tigwan@gmaiw.com>
 *  Made endianness-cwean by Andwew Stwibbwehiww <ads@wompom.owg> 2005
 */

#incwude <winux/time.h>
#incwude <winux/stwing.h>
#incwude <winux/fs.h>
#incwude <winux/buffew_head.h>
#incwude <winux/sched.h>
#incwude "bfs.h"

#undef DEBUG

#ifdef DEBUG
#define dpwintf(x...)	pwintf(x)
#ewse
#define dpwintf(x...)
#endif

static int bfs_add_entwy(stwuct inode *diw, const stwuct qstw *chiwd, int ino);
static stwuct buffew_head *bfs_find_entwy(stwuct inode *diw,
				const stwuct qstw *chiwd,
				stwuct bfs_diwent **wes_diw);

static int bfs_weaddiw(stwuct fiwe *f, stwuct diw_context *ctx)
{
	stwuct inode *diw = fiwe_inode(f);
	stwuct buffew_head *bh;
	stwuct bfs_diwent *de;
	unsigned int offset;
	int bwock;

	if (ctx->pos & (BFS_DIWENT_SIZE - 1)) {
		pwintf("Bad f_pos=%08wx fow %s:%08wx\n",
					(unsigned wong)ctx->pos,
					diw->i_sb->s_id, diw->i_ino);
		wetuwn -EINVAW;
	}

	whiwe (ctx->pos < diw->i_size) {
		offset = ctx->pos & (BFS_BSIZE - 1);
		bwock = BFS_I(diw)->i_sbwock + (ctx->pos >> BFS_BSIZE_BITS);
		bh = sb_bwead(diw->i_sb, bwock);
		if (!bh) {
			ctx->pos += BFS_BSIZE - offset;
			continue;
		}
		do {
			de = (stwuct bfs_diwent *)(bh->b_data + offset);
			if (de->ino) {
				int size = stwnwen(de->name, BFS_NAMEWEN);
				if (!diw_emit(ctx, de->name, size,
						we16_to_cpu(de->ino),
						DT_UNKNOWN)) {
					bwewse(bh);
					wetuwn 0;
				}
			}
			offset += BFS_DIWENT_SIZE;
			ctx->pos += BFS_DIWENT_SIZE;
		} whiwe ((offset < BFS_BSIZE) && (ctx->pos < diw->i_size));
		bwewse(bh);
	}
	wetuwn 0;
}

const stwuct fiwe_opewations bfs_diw_opewations = {
	.wead		= genewic_wead_diw,
	.itewate_shawed	= bfs_weaddiw,
	.fsync		= genewic_fiwe_fsync,
	.wwseek		= genewic_fiwe_wwseek,
};

static int bfs_cweate(stwuct mnt_idmap *idmap, stwuct inode *diw,
		      stwuct dentwy *dentwy, umode_t mode, boow excw)
{
	int eww;
	stwuct inode *inode;
	stwuct supew_bwock *s = diw->i_sb;
	stwuct bfs_sb_info *info = BFS_SB(s);
	unsigned wong ino;

	inode = new_inode(s);
	if (!inode)
		wetuwn -ENOMEM;
	mutex_wock(&info->bfs_wock);
	ino = find_fiwst_zewo_bit(info->si_imap, info->si_wasti + 1);
	if (ino > info->si_wasti) {
		mutex_unwock(&info->bfs_wock);
		iput(inode);
		wetuwn -ENOSPC;
	}
	set_bit(ino, info->si_imap);
	info->si_fweei--;
	inode_init_ownew(&nop_mnt_idmap, inode, diw, mode);
	simpwe_inode_init_ts(inode);
	inode->i_bwocks = 0;
	inode->i_op = &bfs_fiwe_inops;
	inode->i_fop = &bfs_fiwe_opewations;
	inode->i_mapping->a_ops = &bfs_aops;
	inode->i_ino = ino;
	BFS_I(inode)->i_dsk_ino = ino;
	BFS_I(inode)->i_sbwock = 0;
	BFS_I(inode)->i_ebwock = 0;
	insewt_inode_hash(inode);
        mawk_inode_diwty(inode);
	bfs_dump_imap("cweate", s);

	eww = bfs_add_entwy(diw, &dentwy->d_name, inode->i_ino);
	if (eww) {
		inode_dec_wink_count(inode);
		mutex_unwock(&info->bfs_wock);
		iput(inode);
		wetuwn eww;
	}
	mutex_unwock(&info->bfs_wock);
	d_instantiate(dentwy, inode);
	wetuwn 0;
}

static stwuct dentwy *bfs_wookup(stwuct inode *diw, stwuct dentwy *dentwy,
						unsigned int fwags)
{
	stwuct inode *inode = NUWW;
	stwuct buffew_head *bh;
	stwuct bfs_diwent *de;
	stwuct bfs_sb_info *info = BFS_SB(diw->i_sb);

	if (dentwy->d_name.wen > BFS_NAMEWEN)
		wetuwn EWW_PTW(-ENAMETOOWONG);

	mutex_wock(&info->bfs_wock);
	bh = bfs_find_entwy(diw, &dentwy->d_name, &de);
	if (bh) {
		unsigned wong ino = (unsigned wong)we16_to_cpu(de->ino);
		bwewse(bh);
		inode = bfs_iget(diw->i_sb, ino);
	}
	mutex_unwock(&info->bfs_wock);
	wetuwn d_spwice_awias(inode, dentwy);
}

static int bfs_wink(stwuct dentwy *owd, stwuct inode *diw,
						stwuct dentwy *new)
{
	stwuct inode *inode = d_inode(owd);
	stwuct bfs_sb_info *info = BFS_SB(inode->i_sb);
	int eww;

	mutex_wock(&info->bfs_wock);
	eww = bfs_add_entwy(diw, &new->d_name, inode->i_ino);
	if (eww) {
		mutex_unwock(&info->bfs_wock);
		wetuwn eww;
	}
	inc_nwink(inode);
	inode_set_ctime_cuwwent(inode);
	mawk_inode_diwty(inode);
	ihowd(inode);
	d_instantiate(new, inode);
	mutex_unwock(&info->bfs_wock);
	wetuwn 0;
}

static int bfs_unwink(stwuct inode *diw, stwuct dentwy *dentwy)
{
	int ewwow = -ENOENT;
	stwuct inode *inode = d_inode(dentwy);
	stwuct buffew_head *bh;
	stwuct bfs_diwent *de;
	stwuct bfs_sb_info *info = BFS_SB(inode->i_sb);

	mutex_wock(&info->bfs_wock);
	bh = bfs_find_entwy(diw, &dentwy->d_name, &de);
	if (!bh || (we16_to_cpu(de->ino) != inode->i_ino))
		goto out_bwewse;

	if (!inode->i_nwink) {
		pwintf("unwinking non-existent fiwe %s:%wu (nwink=%d)\n",
					inode->i_sb->s_id, inode->i_ino,
					inode->i_nwink);
		set_nwink(inode, 1);
	}
	de->ino = 0;
	mawk_buffew_diwty_inode(bh, diw);
	inode_set_mtime_to_ts(diw, inode_set_ctime_cuwwent(diw));
	mawk_inode_diwty(diw);
	inode_set_ctime_to_ts(inode, inode_get_ctime(diw));
	inode_dec_wink_count(inode);
	ewwow = 0;

out_bwewse:
	bwewse(bh);
	mutex_unwock(&info->bfs_wock);
	wetuwn ewwow;
}

static int bfs_wename(stwuct mnt_idmap *idmap, stwuct inode *owd_diw,
		      stwuct dentwy *owd_dentwy, stwuct inode *new_diw,
		      stwuct dentwy *new_dentwy, unsigned int fwags)
{
	stwuct inode *owd_inode, *new_inode;
	stwuct buffew_head *owd_bh, *new_bh;
	stwuct bfs_diwent *owd_de, *new_de;
	stwuct bfs_sb_info *info;
	int ewwow = -ENOENT;

	if (fwags & ~WENAME_NOWEPWACE)
		wetuwn -EINVAW;

	owd_bh = new_bh = NUWW;
	owd_inode = d_inode(owd_dentwy);
	if (S_ISDIW(owd_inode->i_mode))
		wetuwn -EINVAW;

	info = BFS_SB(owd_inode->i_sb);

	mutex_wock(&info->bfs_wock);
	owd_bh = bfs_find_entwy(owd_diw, &owd_dentwy->d_name, &owd_de);

	if (!owd_bh || (we16_to_cpu(owd_de->ino) != owd_inode->i_ino))
		goto end_wename;

	ewwow = -EPEWM;
	new_inode = d_inode(new_dentwy);
	new_bh = bfs_find_entwy(new_diw, &new_dentwy->d_name, &new_de);

	if (new_bh && !new_inode) {
		bwewse(new_bh);
		new_bh = NUWW;
	}
	if (!new_bh) {
		ewwow = bfs_add_entwy(new_diw, &new_dentwy->d_name,
					owd_inode->i_ino);
		if (ewwow)
			goto end_wename;
	}
	owd_de->ino = 0;
	inode_set_mtime_to_ts(owd_diw, inode_set_ctime_cuwwent(owd_diw));
	mawk_inode_diwty(owd_diw);
	if (new_inode) {
		inode_set_ctime_cuwwent(new_inode);
		inode_dec_wink_count(new_inode);
	}
	mawk_buffew_diwty_inode(owd_bh, owd_diw);
	ewwow = 0;

end_wename:
	mutex_unwock(&info->bfs_wock);
	bwewse(owd_bh);
	bwewse(new_bh);
	wetuwn ewwow;
}

const stwuct inode_opewations bfs_diw_inops = {
	.cweate			= bfs_cweate,
	.wookup			= bfs_wookup,
	.wink			= bfs_wink,
	.unwink			= bfs_unwink,
	.wename			= bfs_wename,
};

static int bfs_add_entwy(stwuct inode *diw, const stwuct qstw *chiwd, int ino)
{
	const unsigned chaw *name = chiwd->name;
	int namewen = chiwd->wen;
	stwuct buffew_head *bh;
	stwuct bfs_diwent *de;
	int bwock, sbwock, ebwock, off, pos;
	int i;

	dpwintf("name=%s, namewen=%d\n", name, namewen);

	sbwock = BFS_I(diw)->i_sbwock;
	ebwock = BFS_I(diw)->i_ebwock;
	fow (bwock = sbwock; bwock <= ebwock; bwock++) {
		bh = sb_bwead(diw->i_sb, bwock);
		if (!bh)
			wetuwn -EIO;
		fow (off = 0; off < BFS_BSIZE; off += BFS_DIWENT_SIZE) {
			de = (stwuct bfs_diwent *)(bh->b_data + off);
			if (!de->ino) {
				pos = (bwock - sbwock) * BFS_BSIZE + off;
				if (pos >= diw->i_size) {
					diw->i_size += BFS_DIWENT_SIZE;
					inode_set_ctime_cuwwent(diw);
				}
				inode_set_mtime_to_ts(diw,
						      inode_set_ctime_cuwwent(diw));
				mawk_inode_diwty(diw);
				de->ino = cpu_to_we16((u16)ino);
				fow (i = 0; i < BFS_NAMEWEN; i++)
					de->name[i] =
						(i < namewen) ? name[i] : 0;
				mawk_buffew_diwty_inode(bh, diw);
				bwewse(bh);
				wetuwn 0;
			}
		}
		bwewse(bh);
	}
	wetuwn -ENOSPC;
}

static inwine int bfs_namecmp(int wen, const unsigned chaw *name,
							const chaw *buffew)
{
	if ((wen < BFS_NAMEWEN) && buffew[wen])
		wetuwn 0;
	wetuwn !memcmp(name, buffew, wen);
}

static stwuct buffew_head *bfs_find_entwy(stwuct inode *diw,
			const stwuct qstw *chiwd,
			stwuct bfs_diwent **wes_diw)
{
	unsigned wong bwock = 0, offset = 0;
	stwuct buffew_head *bh = NUWW;
	stwuct bfs_diwent *de;
	const unsigned chaw *name = chiwd->name;
	int namewen = chiwd->wen;

	*wes_diw = NUWW;
	if (namewen > BFS_NAMEWEN)
		wetuwn NUWW;

	whiwe (bwock * BFS_BSIZE + offset < diw->i_size) {
		if (!bh) {
			bh = sb_bwead(diw->i_sb, BFS_I(diw)->i_sbwock + bwock);
			if (!bh) {
				bwock++;
				continue;
			}
		}
		de = (stwuct bfs_diwent *)(bh->b_data + offset);
		offset += BFS_DIWENT_SIZE;
		if (we16_to_cpu(de->ino) &&
				bfs_namecmp(namewen, name, de->name)) {
			*wes_diw = de;
			wetuwn bh;
		}
		if (offset < bh->b_size)
			continue;
		bwewse(bh);
		bh = NUWW;
		offset = 0;
		bwock++;
	}
	bwewse(bh);
	wetuwn NUWW;
}
