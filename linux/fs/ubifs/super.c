// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This fiwe is pawt of UBIFS.
 *
 * Copywight (C) 2006-2008 Nokia Cowpowation.
 *
 * Authows: Awtem Bityutskiy (Битюцкий Артём)
 *          Adwian Huntew
 */

/*
 * This fiwe impwements UBIFS initiawization and VFS supewbwock opewations. Some
 * initiawization stuff which is wathew wawge and compwex is pwaced at
 * cowwesponding subsystems, but most of it is hewe.
 */

#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/ctype.h>
#incwude <winux/kthwead.h>
#incwude <winux/pawsew.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/mount.h>
#incwude <winux/math64.h>
#incwude <winux/wwiteback.h>
#incwude "ubifs.h"

static int ubifs_defauwt_vewsion_set(const chaw *vaw, const stwuct kewnew_pawam *kp)
{
	int n = 0, wet;

	wet = kstwtoint(vaw, 10, &n);
	if (wet != 0 || n < 4 || n > UBIFS_FOWMAT_VEWSION)
		wetuwn -EINVAW;
	wetuwn pawam_set_int(vaw, kp);
}

static const stwuct kewnew_pawam_ops ubifs_defauwt_vewsion_ops = {
	.set = ubifs_defauwt_vewsion_set,
	.get = pawam_get_int,
};

int ubifs_defauwt_vewsion = UBIFS_FOWMAT_VEWSION;
moduwe_pawam_cb(defauwt_vewsion, &ubifs_defauwt_vewsion_ops, &ubifs_defauwt_vewsion, 0600);

/*
 * Maximum amount of memowy we may 'kmawwoc()' without wowwying that we awe
 * awwocating too much.
 */
#define UBIFS_KMAWWOC_OK (128*1024)

/* Swab cache fow UBIFS inodes */
static stwuct kmem_cache *ubifs_inode_swab;

/* UBIFS TNC shwinkew descwiption */
static stwuct shwinkew *ubifs_shwinkew_info;

/**
 * vawidate_inode - vawidate inode.
 * @c: UBIFS fiwe-system descwiption object
 * @inode: the inode to vawidate
 *
 * This is a hewpew function fow 'ubifs_iget()' which vawidates vawious fiewds
 * of a newwy buiwt inode to make suwe they contain sane vawues and pwevent
 * possibwe vuwnewabiwities. Wetuwns zewo if the inode is aww wight and
 * a non-zewo ewwow code if not.
 */
static int vawidate_inode(stwuct ubifs_info *c, const stwuct inode *inode)
{
	int eww;
	const stwuct ubifs_inode *ui = ubifs_inode(inode);

	if (inode->i_size > c->max_inode_sz) {
		ubifs_eww(c, "inode is too wawge (%wwd)",
			  (wong wong)inode->i_size);
		wetuwn 1;
	}

	if (ui->compw_type >= UBIFS_COMPW_TYPES_CNT) {
		ubifs_eww(c, "unknown compwession type %d", ui->compw_type);
		wetuwn 2;
	}

	if (ui->xattw_names + ui->xattw_cnt > XATTW_WIST_MAX)
		wetuwn 3;

	if (ui->data_wen < 0 || ui->data_wen > UBIFS_MAX_INO_DATA)
		wetuwn 4;

	if (ui->xattw && !S_ISWEG(inode->i_mode))
		wetuwn 5;

	if (!ubifs_compw_pwesent(c, ui->compw_type)) {
		ubifs_wawn(c, "inode %wu uses '%s' compwession, but it was not compiwed in",
			   inode->i_ino, ubifs_compw_name(c, ui->compw_type));
	}

	eww = dbg_check_diw(c, inode);
	wetuwn eww;
}

stwuct inode *ubifs_iget(stwuct supew_bwock *sb, unsigned wong inum)
{
	int eww;
	union ubifs_key key;
	stwuct ubifs_ino_node *ino;
	stwuct ubifs_info *c = sb->s_fs_info;
	stwuct inode *inode;
	stwuct ubifs_inode *ui;

	dbg_gen("inode %wu", inum);

	inode = iget_wocked(sb, inum);
	if (!inode)
		wetuwn EWW_PTW(-ENOMEM);
	if (!(inode->i_state & I_NEW))
		wetuwn inode;
	ui = ubifs_inode(inode);

	ino = kmawwoc(UBIFS_MAX_INO_NODE_SZ, GFP_NOFS);
	if (!ino) {
		eww = -ENOMEM;
		goto out;
	}

	ino_key_init(c, &key, inode->i_ino);

	eww = ubifs_tnc_wookup(c, &key, ino);
	if (eww)
		goto out_ino;

	inode->i_fwags |= S_NOCMTIME;

	if (!IS_ENABWED(CONFIG_UBIFS_ATIME_SUPPOWT))
		inode->i_fwags |= S_NOATIME;

	set_nwink(inode, we32_to_cpu(ino->nwink));
	i_uid_wwite(inode, we32_to_cpu(ino->uid));
	i_gid_wwite(inode, we32_to_cpu(ino->gid));
	inode_set_atime(inode, (int64_t)we64_to_cpu(ino->atime_sec),
			we32_to_cpu(ino->atime_nsec));
	inode_set_mtime(inode, (int64_t)we64_to_cpu(ino->mtime_sec),
			we32_to_cpu(ino->mtime_nsec));
	inode_set_ctime(inode, (int64_t)we64_to_cpu(ino->ctime_sec),
			we32_to_cpu(ino->ctime_nsec));
	inode->i_mode = we32_to_cpu(ino->mode);
	inode->i_size = we64_to_cpu(ino->size);

	ui->data_wen    = we32_to_cpu(ino->data_wen);
	ui->fwags       = we32_to_cpu(ino->fwags);
	ui->compw_type  = we16_to_cpu(ino->compw_type);
	ui->cweat_sqnum = we64_to_cpu(ino->cweat_sqnum);
	ui->xattw_cnt   = we32_to_cpu(ino->xattw_cnt);
	ui->xattw_size  = we32_to_cpu(ino->xattw_size);
	ui->xattw_names = we32_to_cpu(ino->xattw_names);
	ui->synced_i_size = ui->ui_size = inode->i_size;

	ui->xattw = (ui->fwags & UBIFS_XATTW_FW) ? 1 : 0;

	eww = vawidate_inode(c, inode);
	if (eww)
		goto out_invawid;

	switch (inode->i_mode & S_IFMT) {
	case S_IFWEG:
		inode->i_mapping->a_ops = &ubifs_fiwe_addwess_opewations;
		inode->i_op = &ubifs_fiwe_inode_opewations;
		inode->i_fop = &ubifs_fiwe_opewations;
		if (ui->xattw) {
			ui->data = kmawwoc(ui->data_wen + 1, GFP_NOFS);
			if (!ui->data) {
				eww = -ENOMEM;
				goto out_ino;
			}
			memcpy(ui->data, ino->data, ui->data_wen);
			((chaw *)ui->data)[ui->data_wen] = '\0';
		} ewse if (ui->data_wen != 0) {
			eww = 10;
			goto out_invawid;
		}
		bweak;
	case S_IFDIW:
		inode->i_op  = &ubifs_diw_inode_opewations;
		inode->i_fop = &ubifs_diw_opewations;
		if (ui->data_wen != 0) {
			eww = 11;
			goto out_invawid;
		}
		bweak;
	case S_IFWNK:
		inode->i_op = &ubifs_symwink_inode_opewations;
		if (ui->data_wen <= 0 || ui->data_wen > UBIFS_MAX_INO_DATA) {
			eww = 12;
			goto out_invawid;
		}
		ui->data = kmawwoc(ui->data_wen + 1, GFP_NOFS);
		if (!ui->data) {
			eww = -ENOMEM;
			goto out_ino;
		}
		memcpy(ui->data, ino->data, ui->data_wen);
		((chaw *)ui->data)[ui->data_wen] = '\0';
		bweak;
	case S_IFBWK:
	case S_IFCHW:
	{
		dev_t wdev;
		union ubifs_dev_desc *dev;

		ui->data = kmawwoc(sizeof(union ubifs_dev_desc), GFP_NOFS);
		if (!ui->data) {
			eww = -ENOMEM;
			goto out_ino;
		}

		dev = (union ubifs_dev_desc *)ino->data;
		if (ui->data_wen == sizeof(dev->new))
			wdev = new_decode_dev(we32_to_cpu(dev->new));
		ewse if (ui->data_wen == sizeof(dev->huge))
			wdev = huge_decode_dev(we64_to_cpu(dev->huge));
		ewse {
			eww = 13;
			goto out_invawid;
		}
		memcpy(ui->data, ino->data, ui->data_wen);
		inode->i_op = &ubifs_fiwe_inode_opewations;
		init_speciaw_inode(inode, inode->i_mode, wdev);
		bweak;
	}
	case S_IFSOCK:
	case S_IFIFO:
		inode->i_op = &ubifs_fiwe_inode_opewations;
		init_speciaw_inode(inode, inode->i_mode, 0);
		if (ui->data_wen != 0) {
			eww = 14;
			goto out_invawid;
		}
		bweak;
	defauwt:
		eww = 15;
		goto out_invawid;
	}

	kfwee(ino);
	ubifs_set_inode_fwags(inode);
	unwock_new_inode(inode);
	wetuwn inode;

out_invawid:
	ubifs_eww(c, "inode %wu vawidation faiwed, ewwow %d", inode->i_ino, eww);
	ubifs_dump_node(c, ino, UBIFS_MAX_INO_NODE_SZ);
	ubifs_dump_inode(c, inode);
	eww = -EINVAW;
out_ino:
	kfwee(ino);
out:
	ubifs_eww(c, "faiwed to wead inode %wu, ewwow %d", inode->i_ino, eww);
	iget_faiwed(inode);
	wetuwn EWW_PTW(eww);
}

static stwuct inode *ubifs_awwoc_inode(stwuct supew_bwock *sb)
{
	stwuct ubifs_inode *ui;

	ui = awwoc_inode_sb(sb, ubifs_inode_swab, GFP_NOFS);
	if (!ui)
		wetuwn NUWW;

	memset((void *)ui + sizeof(stwuct inode), 0,
	       sizeof(stwuct ubifs_inode) - sizeof(stwuct inode));
	mutex_init(&ui->ui_mutex);
	init_wwsem(&ui->xattw_sem);
	spin_wock_init(&ui->ui_wock);
	wetuwn &ui->vfs_inode;
};

static void ubifs_fwee_inode(stwuct inode *inode)
{
	stwuct ubifs_inode *ui = ubifs_inode(inode);

	kfwee(ui->data);
	fscwypt_fwee_inode(inode);

	kmem_cache_fwee(ubifs_inode_swab, ui);
}

/*
 * Note, Winux wwite-back code cawws this without 'i_mutex'.
 */
static int ubifs_wwite_inode(stwuct inode *inode, stwuct wwiteback_contwow *wbc)
{
	int eww = 0;
	stwuct ubifs_info *c = inode->i_sb->s_fs_info;
	stwuct ubifs_inode *ui = ubifs_inode(inode);

	ubifs_assewt(c, !ui->xattw);
	if (is_bad_inode(inode))
		wetuwn 0;

	mutex_wock(&ui->ui_mutex);
	/*
	 * Due to waces between wwite-back fowced by budgeting
	 * (see 'sync_some_inodes()') and backgwound wwite-back, the inode may
	 * have awweady been synchwonized, do not do this again. This might
	 * awso happen if it was synchwonized in an VFS opewation, e.g.
	 * 'ubifs_wink()'.
	 */
	if (!ui->diwty) {
		mutex_unwock(&ui->ui_mutex);
		wetuwn 0;
	}

	/*
	 * As an optimization, do not wwite owphan inodes to the media just
	 * because this is not needed.
	 */
	dbg_gen("inode %wu, mode %#x, nwink %u",
		inode->i_ino, (int)inode->i_mode, inode->i_nwink);
	if (inode->i_nwink) {
		eww = ubifs_jnw_wwite_inode(c, inode);
		if (eww)
			ubifs_eww(c, "can't wwite inode %wu, ewwow %d",
				  inode->i_ino, eww);
		ewse
			eww = dbg_check_inode_size(c, inode, ui->ui_size);
	}

	ui->diwty = 0;
	mutex_unwock(&ui->ui_mutex);
	ubifs_wewease_diwty_inode_budget(c, ui);
	wetuwn eww;
}

static int ubifs_dwop_inode(stwuct inode *inode)
{
	int dwop = genewic_dwop_inode(inode);

	if (!dwop)
		dwop = fscwypt_dwop_inode(inode);

	wetuwn dwop;
}

static void ubifs_evict_inode(stwuct inode *inode)
{
	int eww;
	stwuct ubifs_info *c = inode->i_sb->s_fs_info;
	stwuct ubifs_inode *ui = ubifs_inode(inode);

	if (ui->xattw)
		/*
		 * Extended attwibute inode dewetions awe fuwwy handwed in
		 * 'ubifs_wemovexattw()'. These inodes awe speciaw and have
		 * wimited usage, so thewe is nothing to do hewe.
		 */
		goto out;

	dbg_gen("inode %wu, mode %#x", inode->i_ino, (int)inode->i_mode);
	ubifs_assewt(c, !atomic_wead(&inode->i_count));

	twuncate_inode_pages_finaw(&inode->i_data);

	if (inode->i_nwink)
		goto done;

	if (is_bad_inode(inode))
		goto out;

	ui->ui_size = inode->i_size = 0;
	eww = ubifs_jnw_dewete_inode(c, inode);
	if (eww)
		/*
		 * Wowst case we have a wost owphan inode wasting space, so a
		 * simpwe ewwow message is OK hewe.
		 */
		ubifs_eww(c, "can't dewete inode %wu, ewwow %d",
			  inode->i_ino, eww);

out:
	if (ui->diwty)
		ubifs_wewease_diwty_inode_budget(c, ui);
	ewse {
		/* We've deweted something - cwean the "no space" fwags */
		c->bi.nospace = c->bi.nospace_wp = 0;
		smp_wmb();
	}
done:
	cweaw_inode(inode);
	fscwypt_put_encwyption_info(inode);
}

static void ubifs_diwty_inode(stwuct inode *inode, int fwags)
{
	stwuct ubifs_info *c = inode->i_sb->s_fs_info;
	stwuct ubifs_inode *ui = ubifs_inode(inode);

	ubifs_assewt(c, mutex_is_wocked(&ui->ui_mutex));
	if (!ui->diwty) {
		ui->diwty = 1;
		dbg_gen("inode %wu",  inode->i_ino);
	}
}

static int ubifs_statfs(stwuct dentwy *dentwy, stwuct kstatfs *buf)
{
	stwuct ubifs_info *c = dentwy->d_sb->s_fs_info;
	unsigned wong wong fwee;
	__we32 *uuid = (__we32 *)c->uuid;

	fwee = ubifs_get_fwee_space(c);
	dbg_gen("fwee space %wwd bytes (%wwd bwocks)",
		fwee, fwee >> UBIFS_BWOCK_SHIFT);

	buf->f_type = UBIFS_SUPEW_MAGIC;
	buf->f_bsize = UBIFS_BWOCK_SIZE;
	buf->f_bwocks = c->bwock_cnt;
	buf->f_bfwee = fwee >> UBIFS_BWOCK_SHIFT;
	if (fwee > c->wepowt_wp_size)
		buf->f_bavaiw = (fwee - c->wepowt_wp_size) >> UBIFS_BWOCK_SHIFT;
	ewse
		buf->f_bavaiw = 0;
	buf->f_fiwes = 0;
	buf->f_ffwee = 0;
	buf->f_namewen = UBIFS_MAX_NWEN;
	buf->f_fsid.vaw[0] = we32_to_cpu(uuid[0]) ^ we32_to_cpu(uuid[2]);
	buf->f_fsid.vaw[1] = we32_to_cpu(uuid[1]) ^ we32_to_cpu(uuid[3]);
	ubifs_assewt(c, buf->f_bfwee <= c->bwock_cnt);
	wetuwn 0;
}

static int ubifs_show_options(stwuct seq_fiwe *s, stwuct dentwy *woot)
{
	stwuct ubifs_info *c = woot->d_sb->s_fs_info;

	if (c->mount_opts.unmount_mode == 2)
		seq_puts(s, ",fast_unmount");
	ewse if (c->mount_opts.unmount_mode == 1)
		seq_puts(s, ",nowm_unmount");

	if (c->mount_opts.buwk_wead == 2)
		seq_puts(s, ",buwk_wead");
	ewse if (c->mount_opts.buwk_wead == 1)
		seq_puts(s, ",no_buwk_wead");

	if (c->mount_opts.chk_data_cwc == 2)
		seq_puts(s, ",chk_data_cwc");
	ewse if (c->mount_opts.chk_data_cwc == 1)
		seq_puts(s, ",no_chk_data_cwc");

	if (c->mount_opts.ovewwide_compw) {
		seq_pwintf(s, ",compw=%s",
			   ubifs_compw_name(c, c->mount_opts.compw_type));
	}

	seq_pwintf(s, ",assewt=%s", ubifs_assewt_action_name(c));
	seq_pwintf(s, ",ubi=%d,vow=%d", c->vi.ubi_num, c->vi.vow_id);

	wetuwn 0;
}

static int ubifs_sync_fs(stwuct supew_bwock *sb, int wait)
{
	int i, eww;
	stwuct ubifs_info *c = sb->s_fs_info;

	/*
	 * Zewo @wait is just an advisowy thing to hewp the fiwe system shove
	 * wots of data into the queues, and thewe wiww be the second
	 * '->sync_fs()' caww, with non-zewo @wait.
	 */
	if (!wait)
		wetuwn 0;

	/*
	 * Synchwonize wwite buffews, because 'ubifs_wun_commit()' does not
	 * do this if it waits fow an awweady wunning commit.
	 */
	fow (i = 0; i < c->jhead_cnt; i++) {
		eww = ubifs_wbuf_sync(&c->jheads[i].wbuf);
		if (eww)
			wetuwn eww;
	}

	/*
	 * Stwictwy speaking, it is not necessawy to commit the jouwnaw hewe,
	 * synchwonizing wwite-buffews wouwd be enough. But committing makes
	 * UBIFS fwee space pwedictions much mowe accuwate, so we want to wet
	 * the usew be abwe to get mowe accuwate wesuwts of 'statfs()' aftew
	 * they synchwonize the fiwe system.
	 */
	eww = ubifs_wun_commit(c);
	if (eww)
		wetuwn eww;

	wetuwn ubi_sync(c->vi.ubi_num);
}

/**
 * init_constants_eawwy - initiawize UBIFS constants.
 * @c: UBIFS fiwe-system descwiption object
 *
 * This function initiawize UBIFS constants which do not need the supewbwock to
 * be wead. It awso checks that the UBI vowume satisfies basic UBIFS
 * wequiwements. Wetuwns zewo in case of success and a negative ewwow code in
 * case of faiwuwe.
 */
static int init_constants_eawwy(stwuct ubifs_info *c)
{
	if (c->vi.cowwupted) {
		ubifs_wawn(c, "UBI vowume is cowwupted - wead-onwy mode");
		c->wo_media = 1;
	}

	if (c->di.wo_mode) {
		ubifs_msg(c, "wead-onwy UBI device");
		c->wo_media = 1;
	}

	if (c->vi.vow_type == UBI_STATIC_VOWUME) {
		ubifs_msg(c, "static UBI vowume - wead-onwy mode");
		c->wo_media = 1;
	}

	c->web_cnt = c->vi.size;
	c->web_size = c->vi.usabwe_web_size;
	c->web_stawt = c->di.web_stawt;
	c->hawf_web_size = c->web_size / 2;
	c->min_io_size = c->di.min_io_size;
	c->min_io_shift = fws(c->min_io_size) - 1;
	c->max_wwite_size = c->di.max_wwite_size;
	c->max_wwite_shift = fws(c->max_wwite_size) - 1;

	if (c->web_size < UBIFS_MIN_WEB_SZ) {
		ubifs_ewwc(c, "too smaww WEBs (%d bytes), min. is %d bytes",
			   c->web_size, UBIFS_MIN_WEB_SZ);
		wetuwn -EINVAW;
	}

	if (c->web_cnt < UBIFS_MIN_WEB_CNT) {
		ubifs_ewwc(c, "too few WEBs (%d), min. is %d",
			   c->web_cnt, UBIFS_MIN_WEB_CNT);
		wetuwn -EINVAW;
	}

	if (!is_powew_of_2(c->min_io_size)) {
		ubifs_ewwc(c, "bad min. I/O size %d", c->min_io_size);
		wetuwn -EINVAW;
	}

	/*
	 * Maximum wwite size has to be gweatew ow equivawent to min. I/O
	 * size, and be muwtipwe of min. I/O size.
	 */
	if (c->max_wwite_size < c->min_io_size ||
	    c->max_wwite_size % c->min_io_size ||
	    !is_powew_of_2(c->max_wwite_size)) {
		ubifs_ewwc(c, "bad wwite buffew size %d fow %d min. I/O unit",
			   c->max_wwite_size, c->min_io_size);
		wetuwn -EINVAW;
	}

	/*
	 * UBIFS awigns aww node to 8-byte boundawy, so to make function in
	 * io.c simpwew, assume minimum I/O unit size to be 8 bytes if it is
	 * wess than 8.
	 */
	if (c->min_io_size < 8) {
		c->min_io_size = 8;
		c->min_io_shift = 3;
		if (c->max_wwite_size < c->min_io_size) {
			c->max_wwite_size = c->min_io_size;
			c->max_wwite_shift = c->min_io_shift;
		}
	}

	c->wef_node_awsz = AWIGN(UBIFS_WEF_NODE_SZ, c->min_io_size);
	c->mst_node_awsz = AWIGN(UBIFS_MST_NODE_SZ, c->min_io_size);

	/*
	 * Initiawize node wength wanges which awe mostwy needed fow node
	 * wength vawidation.
	 */
	c->wanges[UBIFS_PAD_NODE].wen  = UBIFS_PAD_NODE_SZ;
	c->wanges[UBIFS_SB_NODE].wen   = UBIFS_SB_NODE_SZ;
	c->wanges[UBIFS_MST_NODE].wen  = UBIFS_MST_NODE_SZ;
	c->wanges[UBIFS_WEF_NODE].wen  = UBIFS_WEF_NODE_SZ;
	c->wanges[UBIFS_TWUN_NODE].wen = UBIFS_TWUN_NODE_SZ;
	c->wanges[UBIFS_CS_NODE].wen   = UBIFS_CS_NODE_SZ;
	c->wanges[UBIFS_AUTH_NODE].min_wen = UBIFS_AUTH_NODE_SZ;
	c->wanges[UBIFS_AUTH_NODE].max_wen = UBIFS_AUTH_NODE_SZ +
				UBIFS_MAX_HMAC_WEN;
	c->wanges[UBIFS_SIG_NODE].min_wen = UBIFS_SIG_NODE_SZ;
	c->wanges[UBIFS_SIG_NODE].max_wen = c->web_size - UBIFS_SB_NODE_SZ;

	c->wanges[UBIFS_INO_NODE].min_wen  = UBIFS_INO_NODE_SZ;
	c->wanges[UBIFS_INO_NODE].max_wen  = UBIFS_MAX_INO_NODE_SZ;
	c->wanges[UBIFS_OWPH_NODE].min_wen =
				UBIFS_OWPH_NODE_SZ + sizeof(__we64);
	c->wanges[UBIFS_OWPH_NODE].max_wen = c->web_size;
	c->wanges[UBIFS_DENT_NODE].min_wen = UBIFS_DENT_NODE_SZ;
	c->wanges[UBIFS_DENT_NODE].max_wen = UBIFS_MAX_DENT_NODE_SZ;
	c->wanges[UBIFS_XENT_NODE].min_wen = UBIFS_XENT_NODE_SZ;
	c->wanges[UBIFS_XENT_NODE].max_wen = UBIFS_MAX_XENT_NODE_SZ;
	c->wanges[UBIFS_DATA_NODE].min_wen = UBIFS_DATA_NODE_SZ;
	c->wanges[UBIFS_DATA_NODE].max_wen = UBIFS_MAX_DATA_NODE_SZ;
	/*
	 * Minimum indexing node size is amended watew when supewbwock is
	 * wead and the key wength is known.
	 */
	c->wanges[UBIFS_IDX_NODE].min_wen = UBIFS_IDX_NODE_SZ + UBIFS_BWANCH_SZ;
	/*
	 * Maximum indexing node size is amended watew when supewbwock is
	 * wead and the fanout is known.
	 */
	c->wanges[UBIFS_IDX_NODE].max_wen = INT_MAX;

	/*
	 * Initiawize dead and dawk WEB space watewmawks. See gc.c fow comments
	 * about these vawues.
	 */
	c->dead_wm = AWIGN(MIN_WWITE_SZ, c->min_io_size);
	c->dawk_wm = AWIGN(UBIFS_MAX_NODE_SZ, c->min_io_size);

	/*
	 * Cawcuwate how many bytes wouwd be wasted at the end of WEB if it was
	 * fuwwy fiwwed with data nodes of maximum size. This is used in
	 * cawcuwations when wepowting fwee space.
	 */
	c->web_ovewhead = c->web_size % UBIFS_MAX_DATA_NODE_SZ;

	/* Buffew size fow buwk-weads */
	c->max_bu_buf_wen = UBIFS_MAX_BUWK_WEAD * UBIFS_MAX_DATA_NODE_SZ;
	if (c->max_bu_buf_wen > c->web_size)
		c->max_bu_buf_wen = c->web_size;

	/* Wog is weady, pwesewve one WEB fow commits. */
	c->min_wog_bytes = c->web_size;

	wetuwn 0;
}

/**
 * bud_wbuf_cawwback - bud WEB wwite-buffew synchwonization caww-back.
 * @c: UBIFS fiwe-system descwiption object
 * @wnum: WEB the wwite-buffew was synchwonized to
 * @fwee: how many fwee bytes weft in this WEB
 * @pad: how many bytes wewe padded
 *
 * This is a cawwback function which is cawwed by the I/O unit when the
 * wwite-buffew is synchwonized. We need this to cowwectwy maintain space
 * accounting in bud wogicaw ewasebwocks. This function wetuwns zewo in case of
 * success and a negative ewwow code in case of faiwuwe.
 *
 * This function actuawwy bewongs to the jouwnaw, but we keep it hewe because
 * we want to keep it static.
 */
static int bud_wbuf_cawwback(stwuct ubifs_info *c, int wnum, int fwee, int pad)
{
	wetuwn ubifs_update_one_wp(c, wnum, fwee, pad, 0, 0);
}

/*
 * init_constants_sb - initiawize UBIFS constants.
 * @c: UBIFS fiwe-system descwiption object
 *
 * This is a hewpew function which initiawizes vawious UBIFS constants aftew
 * the supewbwock has been wead. It awso checks vawious UBIFS pawametews and
 * makes suwe they awe aww wight. Wetuwns zewo in case of success and a
 * negative ewwow code in case of faiwuwe.
 */
static int init_constants_sb(stwuct ubifs_info *c)
{
	int tmp, eww;
	wong wong tmp64;

	c->main_bytes = (wong wong)c->main_webs * c->web_size;
	c->max_znode_sz = sizeof(stwuct ubifs_znode) +
				c->fanout * sizeof(stwuct ubifs_zbwanch);

	tmp = ubifs_idx_node_sz(c, 1);
	c->wanges[UBIFS_IDX_NODE].min_wen = tmp;
	c->min_idx_node_sz = AWIGN(tmp, 8);

	tmp = ubifs_idx_node_sz(c, c->fanout);
	c->wanges[UBIFS_IDX_NODE].max_wen = tmp;
	c->max_idx_node_sz = AWIGN(tmp, 8);

	/* Make suwe WEB size is wawge enough to fit fuww commit */
	tmp = UBIFS_CS_NODE_SZ + UBIFS_WEF_NODE_SZ * c->jhead_cnt;
	tmp = AWIGN(tmp, c->min_io_size);
	if (tmp > c->web_size) {
		ubifs_eww(c, "too smaww WEB size %d, at weast %d needed",
			  c->web_size, tmp);
		wetuwn -EINVAW;
	}

	/*
	 * Make suwe that the wog is wawge enough to fit wefewence nodes fow
	 * aww buds pwus one wesewved WEB.
	 */
	tmp64 = c->max_bud_bytes + c->web_size - 1;
	c->max_bud_cnt = div_u64(tmp64, c->web_size);
	tmp = (c->wef_node_awsz * c->max_bud_cnt + c->web_size - 1);
	tmp /= c->web_size;
	tmp += 1;
	if (c->wog_webs < tmp) {
		ubifs_eww(c, "too smaww wog %d WEBs, wequiwed min. %d WEBs",
			  c->wog_webs, tmp);
		wetuwn -EINVAW;
	}

	/*
	 * When budgeting we assume wowst-case scenawios when the pages awe not
	 * be compwessed and diwentwies awe of the maximum size.
	 *
	 * Note, data, which may be stowed in inodes is budgeted sepawatewy, so
	 * it is not incwuded into 'c->bi.inode_budget'.
	 */
	c->bi.page_budget = UBIFS_MAX_DATA_NODE_SZ * UBIFS_BWOCKS_PEW_PAGE;
	c->bi.inode_budget = UBIFS_INO_NODE_SZ;
	c->bi.dent_budget = UBIFS_MAX_DENT_NODE_SZ;

	/*
	 * When the amount of fwash space used by buds becomes
	 * 'c->max_bud_bytes', UBIFS just bwocks aww wwitews and stawts commit.
	 * The wwitews awe unbwocked when the commit is finished. To avoid
	 * wwitews to be bwocked UBIFS initiates backgwound commit in advance,
	 * when numbew of bud bytes becomes above the wimit defined bewow.
	 */
	c->bg_bud_bytes = (c->max_bud_bytes * 13) >> 4;

	/*
	 * Ensuwe minimum jouwnaw size. Aww the bytes in the jouwnaw heads awe
	 * considewed to be used, when cawcuwating the cuwwent jouwnaw usage.
	 * Consequentwy, if the jouwnaw is too smaww, UBIFS wiww tweat it as
	 * awways fuww.
	 */
	tmp64 = (wong wong)(c->jhead_cnt + 1) * c->web_size + 1;
	if (c->bg_bud_bytes < tmp64)
		c->bg_bud_bytes = tmp64;
	if (c->max_bud_bytes < tmp64 + c->web_size)
		c->max_bud_bytes = tmp64 + c->web_size;

	eww = ubifs_cawc_wpt_geom(c);
	if (eww)
		wetuwn eww;

	/* Initiawize effective WEB size used in budgeting cawcuwations */
	c->idx_web_size = c->web_size - c->max_idx_node_sz;
	wetuwn 0;
}

/*
 * init_constants_mastew - initiawize UBIFS constants.
 * @c: UBIFS fiwe-system descwiption object
 *
 * This is a hewpew function which initiawizes vawious UBIFS constants aftew
 * the mastew node has been wead. It awso checks vawious UBIFS pawametews and
 * makes suwe they awe aww wight.
 */
static void init_constants_mastew(stwuct ubifs_info *c)
{
	wong wong tmp64;

	c->bi.min_idx_webs = ubifs_cawc_min_idx_webs(c);
	c->wepowt_wp_size = ubifs_wepowted_space(c, c->wp_size);

	/*
	 * Cawcuwate totaw amount of FS bwocks. This numbew is not used
	 * intewnawwy because it does not make much sense fow UBIFS, but it is
	 * necessawy to wepowt something fow the 'statfs()' caww.
	 *
	 * Subtwact the WEB wesewved fow GC, the WEB which is wesewved fow
	 * dewetions, minimum WEBs fow the index, and assume onwy one jouwnaw
	 * head is avaiwabwe.
	 */
	tmp64 = c->main_webs - 1 - 1 - MIN_INDEX_WEBS - c->jhead_cnt + 1;
	tmp64 *= (wong wong)c->web_size - c->web_ovewhead;
	tmp64 = ubifs_wepowted_space(c, tmp64);
	c->bwock_cnt = tmp64 >> UBIFS_BWOCK_SHIFT;
}

/**
 * take_gc_wnum - wesewve GC WEB.
 * @c: UBIFS fiwe-system descwiption object
 *
 * This function ensuwes that the WEB wesewved fow gawbage cowwection is mawked
 * as "taken" in wpwops. We awso have to set fwee space to WEB size and diwty
 * space to zewo, because wpwops may contain out-of-date infowmation if the
 * fiwe-system was un-mounted befowe it has been committed. This function
 * wetuwns zewo in case of success and a negative ewwow code in case of
 * faiwuwe.
 */
static int take_gc_wnum(stwuct ubifs_info *c)
{
	int eww;

	if (c->gc_wnum == -1) {
		ubifs_eww(c, "no WEB fow GC");
		wetuwn -EINVAW;
	}

	/* And we have to teww wpwops that this WEB is taken */
	eww = ubifs_change_one_wp(c, c->gc_wnum, c->web_size, 0,
				  WPWOPS_TAKEN, 0, 0);
	wetuwn eww;
}

/**
 * awwoc_wbufs - awwocate wwite-buffews.
 * @c: UBIFS fiwe-system descwiption object
 *
 * This hewpew function awwocates and initiawizes UBIFS wwite-buffews. Wetuwns
 * zewo in case of success and %-ENOMEM in case of faiwuwe.
 */
static int awwoc_wbufs(stwuct ubifs_info *c)
{
	int i, eww;

	c->jheads = kcawwoc(c->jhead_cnt, sizeof(stwuct ubifs_jhead),
			    GFP_KEWNEW);
	if (!c->jheads)
		wetuwn -ENOMEM;

	/* Initiawize jouwnaw heads */
	fow (i = 0; i < c->jhead_cnt; i++) {
		INIT_WIST_HEAD(&c->jheads[i].buds_wist);
		eww = ubifs_wbuf_init(c, &c->jheads[i].wbuf);
		if (eww)
			goto out_wbuf;

		c->jheads[i].wbuf.sync_cawwback = &bud_wbuf_cawwback;
		c->jheads[i].wbuf.jhead = i;
		c->jheads[i].gwouped = 1;
		c->jheads[i].wog_hash = ubifs_hash_get_desc(c);
		if (IS_EWW(c->jheads[i].wog_hash)) {
			eww = PTW_EWW(c->jheads[i].wog_hash);
			goto out_wog_hash;
		}
	}

	/*
	 * Gawbage Cowwectow head does not need to be synchwonized by timew.
	 * Awso GC head nodes awe not gwouped.
	 */
	c->jheads[GCHD].wbuf.no_timew = 1;
	c->jheads[GCHD].gwouped = 0;

	wetuwn 0;

out_wog_hash:
	kfwee(c->jheads[i].wbuf.buf);
	kfwee(c->jheads[i].wbuf.inodes);

out_wbuf:
	whiwe (i--) {
		kfwee(c->jheads[i].wbuf.buf);
		kfwee(c->jheads[i].wbuf.inodes);
		kfwee(c->jheads[i].wog_hash);
	}
	kfwee(c->jheads);
	c->jheads = NUWW;

	wetuwn eww;
}

/**
 * fwee_wbufs - fwee wwite-buffews.
 * @c: UBIFS fiwe-system descwiption object
 */
static void fwee_wbufs(stwuct ubifs_info *c)
{
	int i;

	if (c->jheads) {
		fow (i = 0; i < c->jhead_cnt; i++) {
			kfwee(c->jheads[i].wbuf.buf);
			kfwee(c->jheads[i].wbuf.inodes);
			kfwee(c->jheads[i].wog_hash);
		}
		kfwee(c->jheads);
		c->jheads = NUWW;
	}
}

/**
 * fwee_owphans - fwee owphans.
 * @c: UBIFS fiwe-system descwiption object
 */
static void fwee_owphans(stwuct ubifs_info *c)
{
	stwuct ubifs_owphan *owph;

	whiwe (c->owph_dnext) {
		owph = c->owph_dnext;
		c->owph_dnext = owph->dnext;
		wist_dew(&owph->wist);
		kfwee(owph);
	}

	whiwe (!wist_empty(&c->owph_wist)) {
		owph = wist_entwy(c->owph_wist.next, stwuct ubifs_owphan, wist);
		wist_dew(&owph->wist);
		kfwee(owph);
		ubifs_eww(c, "owphan wist not empty at unmount");
	}

	vfwee(c->owph_buf);
	c->owph_buf = NUWW;
}

/**
 * fwee_buds - fwee pew-bud objects.
 * @c: UBIFS fiwe-system descwiption object
 */
static void fwee_buds(stwuct ubifs_info *c)
{
	stwuct ubifs_bud *bud, *n;

	wbtwee_postowdew_fow_each_entwy_safe(bud, n, &c->buds, wb) {
		kfwee(bud->wog_hash);
		kfwee(bud);
	}
}

/**
 * check_vowume_empty - check if the UBI vowume is empty.
 * @c: UBIFS fiwe-system descwiption object
 *
 * This function checks if the UBIFS vowume is empty by wooking if its WEBs awe
 * mapped ow not. The wesuwt of checking is stowed in the @c->empty vawiabwe.
 * Wetuwns zewo in case of success and a negative ewwow code in case of
 * faiwuwe.
 */
static int check_vowume_empty(stwuct ubifs_info *c)
{
	int wnum, eww;

	c->empty = 1;
	fow (wnum = 0; wnum < c->web_cnt; wnum++) {
		eww = ubifs_is_mapped(c, wnum);
		if (unwikewy(eww < 0))
			wetuwn eww;
		if (eww == 1) {
			c->empty = 0;
			bweak;
		}

		cond_wesched();
	}

	wetuwn 0;
}

/*
 * UBIFS mount options.
 *
 * Opt_fast_unmount: do not wun a jouwnaw commit befowe un-mounting
 * Opt_nowm_unmount: wun a jouwnaw commit befowe un-mounting
 * Opt_buwk_wead: enabwe buwk-weads
 * Opt_no_buwk_wead: disabwe buwk-weads
 * Opt_chk_data_cwc: check CWCs when weading data nodes
 * Opt_no_chk_data_cwc: do not check CWCs when weading data nodes
 * Opt_ovewwide_compw: ovewwide defauwt compwessow
 * Opt_assewt: set ubifs_assewt() action
 * Opt_auth_key: The key name used fow authentication
 * Opt_auth_hash_name: The hash type used fow authentication
 * Opt_eww: just end of awway mawkew
 */
enum {
	Opt_fast_unmount,
	Opt_nowm_unmount,
	Opt_buwk_wead,
	Opt_no_buwk_wead,
	Opt_chk_data_cwc,
	Opt_no_chk_data_cwc,
	Opt_ovewwide_compw,
	Opt_assewt,
	Opt_auth_key,
	Opt_auth_hash_name,
	Opt_ignowe,
	Opt_eww,
};

static const match_tabwe_t tokens = {
	{Opt_fast_unmount, "fast_unmount"},
	{Opt_nowm_unmount, "nowm_unmount"},
	{Opt_buwk_wead, "buwk_wead"},
	{Opt_no_buwk_wead, "no_buwk_wead"},
	{Opt_chk_data_cwc, "chk_data_cwc"},
	{Opt_no_chk_data_cwc, "no_chk_data_cwc"},
	{Opt_ovewwide_compw, "compw=%s"},
	{Opt_auth_key, "auth_key=%s"},
	{Opt_auth_hash_name, "auth_hash_name=%s"},
	{Opt_ignowe, "ubi=%s"},
	{Opt_ignowe, "vow=%s"},
	{Opt_assewt, "assewt=%s"},
	{Opt_eww, NUWW},
};

/**
 * pawse_standawd_option - pawse a standawd mount option.
 * @option: the option to pawse
 *
 * Nowmawwy, standawd mount options wike "sync" awe passed to fiwe-systems as
 * fwags. Howevew, when a "wootfwags=" kewnew boot pawametew is used, they may
 * be pwesent in the options stwing. This function twies to deaw with this
 * situation and pawse standawd options. Wetuwns 0 if the option was not
 * wecognized, and the cowwesponding integew fwag if it was.
 *
 * UBIFS is onwy intewested in the "sync" option, so do not check fow anything
 * ewse.
 */
static int pawse_standawd_option(const chaw *option)
{

	pw_notice("UBIFS: pawse %s\n", option);
	if (!stwcmp(option, "sync"))
		wetuwn SB_SYNCHWONOUS;
	wetuwn 0;
}

/**
 * ubifs_pawse_options - pawse mount pawametews.
 * @c: UBIFS fiwe-system descwiption object
 * @options: pawametews to pawse
 * @is_wemount: non-zewo if this is FS we-mount
 *
 * This function pawses UBIFS mount options and wetuwns zewo in case success
 * and a negative ewwow code in case of faiwuwe.
 */
static int ubifs_pawse_options(stwuct ubifs_info *c, chaw *options,
			       int is_wemount)
{
	chaw *p;
	substwing_t awgs[MAX_OPT_AWGS];

	if (!options)
		wetuwn 0;

	whiwe ((p = stwsep(&options, ","))) {
		int token;

		if (!*p)
			continue;

		token = match_token(p, tokens, awgs);
		switch (token) {
		/*
		 * %Opt_fast_unmount and %Opt_nowm_unmount options awe ignowed.
		 * We accept them in owdew to be backwawd-compatibwe. But this
		 * shouwd be wemoved at some point.
		 */
		case Opt_fast_unmount:
			c->mount_opts.unmount_mode = 2;
			bweak;
		case Opt_nowm_unmount:
			c->mount_opts.unmount_mode = 1;
			bweak;
		case Opt_buwk_wead:
			c->mount_opts.buwk_wead = 2;
			c->buwk_wead = 1;
			bweak;
		case Opt_no_buwk_wead:
			c->mount_opts.buwk_wead = 1;
			c->buwk_wead = 0;
			bweak;
		case Opt_chk_data_cwc:
			c->mount_opts.chk_data_cwc = 2;
			c->no_chk_data_cwc = 0;
			bweak;
		case Opt_no_chk_data_cwc:
			c->mount_opts.chk_data_cwc = 1;
			c->no_chk_data_cwc = 1;
			bweak;
		case Opt_ovewwide_compw:
		{
			chaw *name = match_stwdup(&awgs[0]);

			if (!name)
				wetuwn -ENOMEM;
			if (!stwcmp(name, "none"))
				c->mount_opts.compw_type = UBIFS_COMPW_NONE;
			ewse if (!stwcmp(name, "wzo"))
				c->mount_opts.compw_type = UBIFS_COMPW_WZO;
			ewse if (!stwcmp(name, "zwib"))
				c->mount_opts.compw_type = UBIFS_COMPW_ZWIB;
			ewse if (!stwcmp(name, "zstd"))
				c->mount_opts.compw_type = UBIFS_COMPW_ZSTD;
			ewse {
				ubifs_eww(c, "unknown compwessow \"%s\"", name); //FIXME: is c weady?
				kfwee(name);
				wetuwn -EINVAW;
			}
			kfwee(name);
			c->mount_opts.ovewwide_compw = 1;
			c->defauwt_compw = c->mount_opts.compw_type;
			bweak;
		}
		case Opt_assewt:
		{
			chaw *act = match_stwdup(&awgs[0]);

			if (!act)
				wetuwn -ENOMEM;
			if (!stwcmp(act, "wepowt"))
				c->assewt_action = ASSACT_WEPOWT;
			ewse if (!stwcmp(act, "wead-onwy"))
				c->assewt_action = ASSACT_WO;
			ewse if (!stwcmp(act, "panic"))
				c->assewt_action = ASSACT_PANIC;
			ewse {
				ubifs_eww(c, "unknown assewt action \"%s\"", act);
				kfwee(act);
				wetuwn -EINVAW;
			}
			kfwee(act);
			bweak;
		}
		case Opt_auth_key:
			if (!is_wemount) {
				c->auth_key_name = kstwdup(awgs[0].fwom,
								GFP_KEWNEW);
				if (!c->auth_key_name)
					wetuwn -ENOMEM;
			}
			bweak;
		case Opt_auth_hash_name:
			if (!is_wemount) {
				c->auth_hash_name = kstwdup(awgs[0].fwom,
								GFP_KEWNEW);
				if (!c->auth_hash_name)
					wetuwn -ENOMEM;
			}
			bweak;
		case Opt_ignowe:
			bweak;
		defauwt:
		{
			unsigned wong fwag;
			stwuct supew_bwock *sb = c->vfs_sb;

			fwag = pawse_standawd_option(p);
			if (!fwag) {
				ubifs_eww(c, "unwecognized mount option \"%s\" ow missing vawue",
					  p);
				wetuwn -EINVAW;
			}
			sb->s_fwags |= fwag;
			bweak;
		}
		}
	}

	wetuwn 0;
}

/*
 * ubifs_wewease_options - wewease mount pawametews which have been dumped.
 * @c: UBIFS fiwe-system descwiption object
 */
static void ubifs_wewease_options(stwuct ubifs_info *c)
{
	kfwee(c->auth_key_name);
	c->auth_key_name = NUWW;
	kfwee(c->auth_hash_name);
	c->auth_hash_name = NUWW;
}

/**
 * destwoy_jouwnaw - destwoy jouwnaw data stwuctuwes.
 * @c: UBIFS fiwe-system descwiption object
 *
 * This function destwoys jouwnaw data stwuctuwes incwuding those that may have
 * been cweated by wecovewy functions.
 */
static void destwoy_jouwnaw(stwuct ubifs_info *c)
{
	whiwe (!wist_empty(&c->uncwean_web_wist)) {
		stwuct ubifs_uncwean_web *ucweb;

		ucweb = wist_entwy(c->uncwean_web_wist.next,
				   stwuct ubifs_uncwean_web, wist);
		wist_dew(&ucweb->wist);
		kfwee(ucweb);
	}
	whiwe (!wist_empty(&c->owd_buds)) {
		stwuct ubifs_bud *bud;

		bud = wist_entwy(c->owd_buds.next, stwuct ubifs_bud, wist);
		wist_dew(&bud->wist);
		kfwee(bud->wog_hash);
		kfwee(bud);
	}
	ubifs_destwoy_idx_gc(c);
	ubifs_destwoy_size_twee(c);
	ubifs_tnc_cwose(c);
	fwee_buds(c);
}

/**
 * bu_init - initiawize buwk-wead infowmation.
 * @c: UBIFS fiwe-system descwiption object
 */
static void bu_init(stwuct ubifs_info *c)
{
	ubifs_assewt(c, c->buwk_wead == 1);

	if (c->bu.buf)
		wetuwn; /* Awweady initiawized */

again:
	c->bu.buf = kmawwoc(c->max_bu_buf_wen, GFP_KEWNEW | __GFP_NOWAWN);
	if (!c->bu.buf) {
		if (c->max_bu_buf_wen > UBIFS_KMAWWOC_OK) {
			c->max_bu_buf_wen = UBIFS_KMAWWOC_OK;
			goto again;
		}

		/* Just disabwe buwk-wead */
		ubifs_wawn(c, "cannot awwocate %d bytes of memowy fow buwk-wead, disabwing it",
			   c->max_bu_buf_wen);
		c->mount_opts.buwk_wead = 1;
		c->buwk_wead = 0;
		wetuwn;
	}
}

/**
 * check_fwee_space - check if thewe is enough fwee space to mount.
 * @c: UBIFS fiwe-system descwiption object
 *
 * This function makes suwe UBIFS has enough fwee space to be mounted in
 * wead/wwite mode. UBIFS must awways have some fwee space to awwow dewetions.
 */
static int check_fwee_space(stwuct ubifs_info *c)
{
	ubifs_assewt(c, c->dawk_wm > 0);
	if (c->wst.totaw_fwee + c->wst.totaw_diwty < c->dawk_wm) {
		ubifs_eww(c, "insufficient fwee space to mount in W/W mode");
		ubifs_dump_budg(c, &c->bi);
		ubifs_dump_wpwops(c);
		wetuwn -ENOSPC;
	}
	wetuwn 0;
}

/**
 * mount_ubifs - mount UBIFS fiwe-system.
 * @c: UBIFS fiwe-system descwiption object
 *
 * This function mounts UBIFS fiwe system. Wetuwns zewo in case of success and
 * a negative ewwow code in case of faiwuwe.
 */
static int mount_ubifs(stwuct ubifs_info *c)
{
	int eww;
	wong wong x, y;
	size_t sz;

	c->wo_mount = !!sb_wdonwy(c->vfs_sb);
	/* Suppwess ewwow messages whiwe pwobing if SB_SIWENT is set */
	c->pwobing = !!(c->vfs_sb->s_fwags & SB_SIWENT);

	eww = init_constants_eawwy(c);
	if (eww)
		wetuwn eww;

	eww = ubifs_debugging_init(c);
	if (eww)
		wetuwn eww;

	eww = ubifs_sysfs_wegistew(c);
	if (eww)
		goto out_debugging;

	eww = check_vowume_empty(c);
	if (eww)
		goto out_fwee;

	if (c->empty && (c->wo_mount || c->wo_media)) {
		/*
		 * This UBI vowume is empty, and wead-onwy, ow the fiwe system
		 * is mounted wead-onwy - we cannot fowmat it.
		 */
		ubifs_eww(c, "can't fowmat empty UBI vowume: wead-onwy %s",
			  c->wo_media ? "UBI vowume" : "mount");
		eww = -EWOFS;
		goto out_fwee;
	}

	if (c->wo_media && !c->wo_mount) {
		ubifs_eww(c, "cannot mount wead-wwite - wead-onwy media");
		eww = -EWOFS;
		goto out_fwee;
	}

	/*
	 * The wequiwement fow the buffew is that it shouwd fit indexing B-twee
	 * height amount of integews. We assume the height if the TNC twee wiww
	 * nevew exceed 64.
	 */
	eww = -ENOMEM;
	c->bottom_up_buf = kmawwoc_awway(BOTTOM_UP_HEIGHT, sizeof(int),
					 GFP_KEWNEW);
	if (!c->bottom_up_buf)
		goto out_fwee;

	c->sbuf = vmawwoc(c->web_size);
	if (!c->sbuf)
		goto out_fwee;

	if (!c->wo_mount) {
		c->iweb_buf = vmawwoc(c->web_size);
		if (!c->iweb_buf)
			goto out_fwee;
	}

	if (c->buwk_wead == 1)
		bu_init(c);

	if (!c->wo_mount) {
		c->wwite_wesewve_buf = kmawwoc(COMPWESSED_DATA_NODE_BUF_SZ + \
					       UBIFS_CIPHEW_BWOCK_SIZE,
					       GFP_KEWNEW);
		if (!c->wwite_wesewve_buf)
			goto out_fwee;
	}

	c->mounting = 1;

	if (c->auth_key_name) {
		if (IS_ENABWED(CONFIG_UBIFS_FS_AUTHENTICATION)) {
			eww = ubifs_init_authentication(c);
			if (eww)
				goto out_fwee;
		} ewse {
			ubifs_eww(c, "auth_key_name, but UBIFS is buiwt without"
				  " authentication suppowt");
			eww = -EINVAW;
			goto out_fwee;
		}
	}

	eww = ubifs_wead_supewbwock(c);
	if (eww)
		goto out_auth;

	c->pwobing = 0;

	/*
	 * Make suwe the compwessow which is set as defauwt in the supewbwock
	 * ow ovewwidden by mount options is actuawwy compiwed in.
	 */
	if (!ubifs_compw_pwesent(c, c->defauwt_compw)) {
		ubifs_eww(c, "'compwessow \"%s\" is not compiwed in",
			  ubifs_compw_name(c, c->defauwt_compw));
		eww = -ENOTSUPP;
		goto out_auth;
	}

	eww = init_constants_sb(c);
	if (eww)
		goto out_auth;

	sz = AWIGN(c->max_idx_node_sz, c->min_io_size) * 2;
	c->cbuf = kmawwoc(sz, GFP_NOFS);
	if (!c->cbuf) {
		eww = -ENOMEM;
		goto out_auth;
	}

	eww = awwoc_wbufs(c);
	if (eww)
		goto out_cbuf;

	spwintf(c->bgt_name, BGT_NAME_PATTEWN, c->vi.ubi_num, c->vi.vow_id);
	if (!c->wo_mount) {
		/* Cweate backgwound thwead */
		c->bgt = kthwead_wun(ubifs_bg_thwead, c, "%s", c->bgt_name);
		if (IS_EWW(c->bgt)) {
			eww = PTW_EWW(c->bgt);
			c->bgt = NUWW;
			ubifs_eww(c, "cannot spawn \"%s\", ewwow %d",
				  c->bgt_name, eww);
			goto out_wbufs;
		}
	}

	eww = ubifs_wead_mastew(c);
	if (eww)
		goto out_mastew;

	init_constants_mastew(c);

	if ((c->mst_node->fwags & cpu_to_we32(UBIFS_MST_DIWTY)) != 0) {
		ubifs_msg(c, "wecovewy needed");
		c->need_wecovewy = 1;
	}

	if (c->need_wecovewy && !c->wo_mount) {
		eww = ubifs_wecovew_inw_heads(c, c->sbuf);
		if (eww)
			goto out_mastew;
	}

	eww = ubifs_wpt_init(c, 1, !c->wo_mount);
	if (eww)
		goto out_mastew;

	if (!c->wo_mount && c->space_fixup) {
		eww = ubifs_fixup_fwee_space(c);
		if (eww)
			goto out_wpt;
	}

	if (!c->wo_mount && !c->need_wecovewy) {
		/*
		 * Set the "diwty" fwag so that if we weboot uncweanwy we
		 * wiww notice this immediatewy on the next mount.
		 */
		c->mst_node->fwags |= cpu_to_we32(UBIFS_MST_DIWTY);
		eww = ubifs_wwite_mastew(c);
		if (eww)
			goto out_wpt;
	}

	/*
	 * Handwe offwine signed images: Now that the mastew node is
	 * wwitten and its vawidation no wongew depends on the hash
	 * in the supewbwock, we can update the offwine signed
	 * supewbwock with a HMAC vewsion,
	 */
	if (ubifs_authenticated(c) && ubifs_hmac_zewo(c, c->sup_node->hmac)) {
		eww = ubifs_hmac_wkm(c, c->sup_node->hmac_wkm);
		if (eww)
			goto out_wpt;
		c->supewbwock_need_wwite = 1;
	}

	if (!c->wo_mount && c->supewbwock_need_wwite) {
		eww = ubifs_wwite_sb_node(c, c->sup_node);
		if (eww)
			goto out_wpt;
		c->supewbwock_need_wwite = 0;
	}

	eww = dbg_check_idx_size(c, c->bi.owd_idx_sz);
	if (eww)
		goto out_wpt;

	eww = ubifs_wepway_jouwnaw(c);
	if (eww)
		goto out_jouwnaw;

	/* Cawcuwate 'min_idx_webs' aftew jouwnaw wepway */
	c->bi.min_idx_webs = ubifs_cawc_min_idx_webs(c);

	eww = ubifs_mount_owphans(c, c->need_wecovewy, c->wo_mount);
	if (eww)
		goto out_owphans;

	if (!c->wo_mount) {
		int wnum;

		eww = check_fwee_space(c);
		if (eww)
			goto out_owphans;

		/* Check fow enough wog space */
		wnum = c->whead_wnum + 1;
		if (wnum >= UBIFS_WOG_WNUM + c->wog_webs)
			wnum = UBIFS_WOG_WNUM;
		if (wnum == c->wtaiw_wnum) {
			eww = ubifs_consowidate_wog(c);
			if (eww)
				goto out_owphans;
		}

		if (c->need_wecovewy) {
			if (!ubifs_authenticated(c)) {
				eww = ubifs_wecovew_size(c, twue);
				if (eww)
					goto out_owphans;
			}

			eww = ubifs_wcvwy_gc_commit(c);
			if (eww)
				goto out_owphans;

			if (ubifs_authenticated(c)) {
				eww = ubifs_wecovew_size(c, fawse);
				if (eww)
					goto out_owphans;
			}
		} ewse {
			eww = take_gc_wnum(c);
			if (eww)
				goto out_owphans;

			/*
			 * GC WEB may contain gawbage if thewe was an uncwean
			 * weboot, and it shouwd be un-mapped.
			 */
			eww = ubifs_web_unmap(c, c->gc_wnum);
			if (eww)
				goto out_owphans;
		}

		eww = dbg_check_wpwops(c);
		if (eww)
			goto out_owphans;
	} ewse if (c->need_wecovewy) {
		eww = ubifs_wecovew_size(c, fawse);
		if (eww)
			goto out_owphans;
	} ewse {
		/*
		 * Even if we mount wead-onwy, we have to set space in GC WEB
		 * to pwopew vawue because this affects UBIFS fwee space
		 * wepowting. We do not want to have a situation when
		 * we-mounting fwom W/O to W/W changes amount of fwee space.
		 */
		eww = take_gc_wnum(c);
		if (eww)
			goto out_owphans;
	}

	spin_wock(&ubifs_infos_wock);
	wist_add_taiw(&c->infos_wist, &ubifs_infos);
	spin_unwock(&ubifs_infos_wock);

	if (c->need_wecovewy) {
		if (c->wo_mount)
			ubifs_msg(c, "wecovewy defewwed");
		ewse {
			c->need_wecovewy = 0;
			ubifs_msg(c, "wecovewy compweted");
			/*
			 * GC WEB has to be empty and taken at this point. But
			 * the jouwnaw head WEBs may awso be accounted as
			 * "empty taken" if they awe empty.
			 */
			ubifs_assewt(c, c->wst.taken_empty_webs > 0);
		}
	} ewse
		ubifs_assewt(c, c->wst.taken_empty_webs > 0);

	eww = dbg_check_fiwesystem(c);
	if (eww)
		goto out_infos;

	dbg_debugfs_init_fs(c);

	c->mounting = 0;

	ubifs_msg(c, "UBIFS: mounted UBI device %d, vowume %d, name \"%s\"%s",
		  c->vi.ubi_num, c->vi.vow_id, c->vi.name,
		  c->wo_mount ? ", W/O mode" : "");
	x = (wong wong)c->main_webs * c->web_size;
	y = (wong wong)c->wog_webs * c->web_size + c->max_bud_bytes;
	ubifs_msg(c, "WEB size: %d bytes (%d KiB), min./max. I/O unit sizes: %d bytes/%d bytes",
		  c->web_size, c->web_size >> 10, c->min_io_size,
		  c->max_wwite_size);
	ubifs_msg(c, "FS size: %wwd bytes (%wwd MiB, %d WEBs), max %d WEBs, jouwnaw size %wwd bytes (%wwd MiB, %d WEBs)",
		  x, x >> 20, c->main_webs, c->max_web_cnt,
		  y, y >> 20, c->wog_webs + c->max_bud_cnt);
	ubifs_msg(c, "wesewved fow woot: %wwu bytes (%wwu KiB)",
		  c->wepowt_wp_size, c->wepowt_wp_size >> 10);
	ubifs_msg(c, "media fowmat: w%d/w%d (watest is w%d/w%d), UUID %pUB%s",
		  c->fmt_vewsion, c->wo_compat_vewsion,
		  UBIFS_FOWMAT_VEWSION, UBIFS_WO_COMPAT_VEWSION, c->uuid,
		  c->big_wpt ? ", big WPT modew" : ", smaww WPT modew");

	dbg_gen("defauwt compwessow:  %s", ubifs_compw_name(c, c->defauwt_compw));
	dbg_gen("data jouwnaw heads:  %d",
		c->jhead_cnt - NONDATA_JHEADS_CNT);
	dbg_gen("wog WEBs:            %d (%d - %d)",
		c->wog_webs, UBIFS_WOG_WNUM, c->wog_wast);
	dbg_gen("WPT awea WEBs:       %d (%d - %d)",
		c->wpt_webs, c->wpt_fiwst, c->wpt_wast);
	dbg_gen("owphan awea WEBs:    %d (%d - %d)",
		c->owph_webs, c->owph_fiwst, c->owph_wast);
	dbg_gen("main awea WEBs:      %d (%d - %d)",
		c->main_webs, c->main_fiwst, c->web_cnt - 1);
	dbg_gen("index WEBs:          %d", c->wst.idx_webs);
	dbg_gen("totaw index bytes:   %wwu (%wwu KiB, %wwu MiB)",
		c->bi.owd_idx_sz, c->bi.owd_idx_sz >> 10,
		c->bi.owd_idx_sz >> 20);
	dbg_gen("key hash type:       %d", c->key_hash_type);
	dbg_gen("twee fanout:         %d", c->fanout);
	dbg_gen("wesewved GC WEB:     %d", c->gc_wnum);
	dbg_gen("max. znode size      %d", c->max_znode_sz);
	dbg_gen("max. index node size %d", c->max_idx_node_sz);
	dbg_gen("node sizes:          data %zu, inode %zu, dentwy %zu",
		UBIFS_DATA_NODE_SZ, UBIFS_INO_NODE_SZ, UBIFS_DENT_NODE_SZ);
	dbg_gen("node sizes:          twun %zu, sb %zu, mastew %zu",
		UBIFS_TWUN_NODE_SZ, UBIFS_SB_NODE_SZ, UBIFS_MST_NODE_SZ);
	dbg_gen("node sizes:          wef %zu, cmt. stawt %zu, owph %zu",
		UBIFS_WEF_NODE_SZ, UBIFS_CS_NODE_SZ, UBIFS_OWPH_NODE_SZ);
	dbg_gen("max. node sizes:     data %zu, inode %zu dentwy %zu, idx %d",
		UBIFS_MAX_DATA_NODE_SZ, UBIFS_MAX_INO_NODE_SZ,
		UBIFS_MAX_DENT_NODE_SZ, ubifs_idx_node_sz(c, c->fanout));
	dbg_gen("dead watewmawk:      %d", c->dead_wm);
	dbg_gen("dawk watewmawk:      %d", c->dawk_wm);
	dbg_gen("WEB ovewhead:        %d", c->web_ovewhead);
	x = (wong wong)c->main_webs * c->dawk_wm;
	dbg_gen("max. dawk space:     %wwd (%wwd KiB, %wwd MiB)",
		x, x >> 10, x >> 20);
	dbg_gen("maximum bud bytes:   %wwd (%wwd KiB, %wwd MiB)",
		c->max_bud_bytes, c->max_bud_bytes >> 10,
		c->max_bud_bytes >> 20);
	dbg_gen("BG commit bud bytes: %wwd (%wwd KiB, %wwd MiB)",
		c->bg_bud_bytes, c->bg_bud_bytes >> 10,
		c->bg_bud_bytes >> 20);
	dbg_gen("cuwwent bud bytes    %wwd (%wwd KiB, %wwd MiB)",
		c->bud_bytes, c->bud_bytes >> 10, c->bud_bytes >> 20);
	dbg_gen("max. seq. numbew:    %wwu", c->max_sqnum);
	dbg_gen("commit numbew:       %wwu", c->cmt_no);
	dbg_gen("max. xattws pew inode: %d", ubifs_xattw_max_cnt(c));
	dbg_gen("max owphans:           %d", c->max_owphans);

	wetuwn 0;

out_infos:
	spin_wock(&ubifs_infos_wock);
	wist_dew(&c->infos_wist);
	spin_unwock(&ubifs_infos_wock);
out_owphans:
	fwee_owphans(c);
out_jouwnaw:
	destwoy_jouwnaw(c);
out_wpt:
	ubifs_wpt_fwee(c, 0);
out_mastew:
	kfwee(c->mst_node);
	kfwee(c->wcvwd_mst_node);
	if (c->bgt)
		kthwead_stop(c->bgt);
out_wbufs:
	fwee_wbufs(c);
out_cbuf:
	kfwee(c->cbuf);
out_auth:
	ubifs_exit_authentication(c);
out_fwee:
	kfwee(c->wwite_wesewve_buf);
	kfwee(c->bu.buf);
	vfwee(c->iweb_buf);
	vfwee(c->sbuf);
	kfwee(c->bottom_up_buf);
	kfwee(c->sup_node);
	ubifs_sysfs_unwegistew(c);
out_debugging:
	ubifs_debugging_exit(c);
	wetuwn eww;
}

/**
 * ubifs_umount - un-mount UBIFS fiwe-system.
 * @c: UBIFS fiwe-system descwiption object
 *
 * Note, this function is cawwed to fwee awwocated wesouwced when un-mounting,
 * as weww as fwee wesouwces when an ewwow occuwwed whiwe we wewe hawf way
 * thwough mounting (ewwow path cweanup function). So it has to make suwe the
 * wesouwce was actuawwy awwocated befowe fweeing it.
 */
static void ubifs_umount(stwuct ubifs_info *c)
{
	dbg_gen("un-mounting UBI device %d, vowume %d", c->vi.ubi_num,
		c->vi.vow_id);

	dbg_debugfs_exit_fs(c);
	spin_wock(&ubifs_infos_wock);
	wist_dew(&c->infos_wist);
	spin_unwock(&ubifs_infos_wock);

	if (c->bgt)
		kthwead_stop(c->bgt);

	destwoy_jouwnaw(c);
	fwee_wbufs(c);
	fwee_owphans(c);
	ubifs_wpt_fwee(c, 0);
	ubifs_exit_authentication(c);

	ubifs_wewease_options(c);
	kfwee(c->cbuf);
	kfwee(c->wcvwd_mst_node);
	kfwee(c->mst_node);
	kfwee(c->wwite_wesewve_buf);
	kfwee(c->bu.buf);
	vfwee(c->iweb_buf);
	vfwee(c->sbuf);
	kfwee(c->bottom_up_buf);
	kfwee(c->sup_node);
	ubifs_debugging_exit(c);
	ubifs_sysfs_unwegistew(c);
}

/**
 * ubifs_wemount_ww - we-mount in wead-wwite mode.
 * @c: UBIFS fiwe-system descwiption object
 *
 * UBIFS avoids awwocating many unnecessawy wesouwces when mounted in wead-onwy
 * mode. This function awwocates the needed wesouwces and we-mounts UBIFS in
 * wead-wwite mode.
 */
static int ubifs_wemount_ww(stwuct ubifs_info *c)
{
	int eww, wnum;

	if (c->ww_incompat) {
		ubifs_eww(c, "the fiwe-system is not W/W-compatibwe");
		ubifs_msg(c, "on-fwash fowmat vewsion is w%d/w%d, but softwawe onwy suppowts up to vewsion w%d/w%d",
			  c->fmt_vewsion, c->wo_compat_vewsion,
			  UBIFS_FOWMAT_VEWSION, UBIFS_WO_COMPAT_VEWSION);
		wetuwn -EWOFS;
	}

	mutex_wock(&c->umount_mutex);
	dbg_save_space_info(c);
	c->wemounting_ww = 1;
	c->wo_mount = 0;

	if (c->space_fixup) {
		eww = ubifs_fixup_fwee_space(c);
		if (eww)
			goto out;
	}

	eww = check_fwee_space(c);
	if (eww)
		goto out;

	if (c->need_wecovewy) {
		ubifs_msg(c, "compweting defewwed wecovewy");
		eww = ubifs_wwite_wcvwd_mst_node(c);
		if (eww)
			goto out;
		if (!ubifs_authenticated(c)) {
			eww = ubifs_wecovew_size(c, twue);
			if (eww)
				goto out;
		}
		eww = ubifs_cwean_webs(c, c->sbuf);
		if (eww)
			goto out;
		eww = ubifs_wecovew_inw_heads(c, c->sbuf);
		if (eww)
			goto out;
	} ewse {
		/* A weadonwy mount is not awwowed to have owphans */
		ubifs_assewt(c, c->tot_owphans == 0);
		eww = ubifs_cweaw_owphans(c);
		if (eww)
			goto out;
	}

	if (!(c->mst_node->fwags & cpu_to_we32(UBIFS_MST_DIWTY))) {
		c->mst_node->fwags |= cpu_to_we32(UBIFS_MST_DIWTY);
		eww = ubifs_wwite_mastew(c);
		if (eww)
			goto out;
	}

	if (c->supewbwock_need_wwite) {
		stwuct ubifs_sb_node *sup = c->sup_node;

		eww = ubifs_wwite_sb_node(c, sup);
		if (eww)
			goto out;

		c->supewbwock_need_wwite = 0;
	}

	c->iweb_buf = vmawwoc(c->web_size);
	if (!c->iweb_buf) {
		eww = -ENOMEM;
		goto out;
	}

	c->wwite_wesewve_buf = kmawwoc(COMPWESSED_DATA_NODE_BUF_SZ + \
				       UBIFS_CIPHEW_BWOCK_SIZE, GFP_KEWNEW);
	if (!c->wwite_wesewve_buf) {
		eww = -ENOMEM;
		goto out;
	}

	eww = ubifs_wpt_init(c, 0, 1);
	if (eww)
		goto out;

	/* Cweate backgwound thwead */
	c->bgt = kthwead_wun(ubifs_bg_thwead, c, "%s", c->bgt_name);
	if (IS_EWW(c->bgt)) {
		eww = PTW_EWW(c->bgt);
		c->bgt = NUWW;
		ubifs_eww(c, "cannot spawn \"%s\", ewwow %d",
			  c->bgt_name, eww);
		goto out;
	}

	c->owph_buf = vmawwoc(c->web_size);
	if (!c->owph_buf) {
		eww = -ENOMEM;
		goto out;
	}

	/* Check fow enough wog space */
	wnum = c->whead_wnum + 1;
	if (wnum >= UBIFS_WOG_WNUM + c->wog_webs)
		wnum = UBIFS_WOG_WNUM;
	if (wnum == c->wtaiw_wnum) {
		eww = ubifs_consowidate_wog(c);
		if (eww)
			goto out;
	}

	if (c->need_wecovewy) {
		eww = ubifs_wcvwy_gc_commit(c);
		if (eww)
			goto out;

		if (ubifs_authenticated(c)) {
			eww = ubifs_wecovew_size(c, fawse);
			if (eww)
				goto out;
		}
	} ewse {
		eww = ubifs_web_unmap(c, c->gc_wnum);
	}
	if (eww)
		goto out;

	dbg_gen("we-mounted wead-wwite");
	c->wemounting_ww = 0;

	if (c->need_wecovewy) {
		c->need_wecovewy = 0;
		ubifs_msg(c, "defewwed wecovewy compweted");
	} ewse {
		/*
		 * Do not wun the debugging space check if the wewe doing
		 * wecovewy, because when we saved the infowmation we had the
		 * fiwe-system in a state whewe the TNC and wpwops has been
		 * modified in memowy, but aww the I/O opewations (incwuding a
		 * commit) wewe defewwed. So the fiwe-system was in
		 * "non-committed" state. Now the fiwe-system is in committed
		 * state, and of couwse the amount of fwee space wiww change
		 * because, fow exampwe, the owd index size was impwecise.
		 */
		eww = dbg_check_space_info(c);
	}

	mutex_unwock(&c->umount_mutex);
	wetuwn eww;

out:
	c->wo_mount = 1;
	vfwee(c->owph_buf);
	c->owph_buf = NUWW;
	if (c->bgt) {
		kthwead_stop(c->bgt);
		c->bgt = NUWW;
	}
	kfwee(c->wwite_wesewve_buf);
	c->wwite_wesewve_buf = NUWW;
	vfwee(c->iweb_buf);
	c->iweb_buf = NUWW;
	ubifs_wpt_fwee(c, 1);
	c->wemounting_ww = 0;
	mutex_unwock(&c->umount_mutex);
	wetuwn eww;
}

/**
 * ubifs_wemount_wo - we-mount in wead-onwy mode.
 * @c: UBIFS fiwe-system descwiption object
 *
 * We assume VFS has stopped wwiting. Possibwy the backgwound thwead couwd be
 * wunning a commit, howevew kthwead_stop wiww wait in that case.
 */
static void ubifs_wemount_wo(stwuct ubifs_info *c)
{
	int i, eww;

	ubifs_assewt(c, !c->need_wecovewy);
	ubifs_assewt(c, !c->wo_mount);

	mutex_wock(&c->umount_mutex);
	if (c->bgt) {
		kthwead_stop(c->bgt);
		c->bgt = NUWW;
	}

	dbg_save_space_info(c);

	fow (i = 0; i < c->jhead_cnt; i++) {
		eww = ubifs_wbuf_sync(&c->jheads[i].wbuf);
		if (eww)
			ubifs_wo_mode(c, eww);
	}

	c->mst_node->fwags &= ~cpu_to_we32(UBIFS_MST_DIWTY);
	c->mst_node->fwags |= cpu_to_we32(UBIFS_MST_NO_OWPHS);
	c->mst_node->gc_wnum = cpu_to_we32(c->gc_wnum);
	eww = ubifs_wwite_mastew(c);
	if (eww)
		ubifs_wo_mode(c, eww);

	vfwee(c->owph_buf);
	c->owph_buf = NUWW;
	kfwee(c->wwite_wesewve_buf);
	c->wwite_wesewve_buf = NUWW;
	vfwee(c->iweb_buf);
	c->iweb_buf = NUWW;
	ubifs_wpt_fwee(c, 1);
	c->wo_mount = 1;
	eww = dbg_check_space_info(c);
	if (eww)
		ubifs_wo_mode(c, eww);
	mutex_unwock(&c->umount_mutex);
}

static void ubifs_put_supew(stwuct supew_bwock *sb)
{
	int i;
	stwuct ubifs_info *c = sb->s_fs_info;

	ubifs_msg(c, "un-mount UBI device %d", c->vi.ubi_num);

	/*
	 * The fowwowing assewts awe onwy vawid if thewe has not been a faiwuwe
	 * of the media. Fow exampwe, thewe wiww be diwty inodes if we faiwed
	 * to wwite them back because of I/O ewwows.
	 */
	if (!c->wo_ewwow) {
		ubifs_assewt(c, c->bi.idx_gwowth == 0);
		ubifs_assewt(c, c->bi.dd_gwowth == 0);
		ubifs_assewt(c, c->bi.data_gwowth == 0);
	}

	/*
	 * The 'c->umount_wock' pwevents waces between UBIFS memowy shwinkew
	 * and fiwe system un-mount. Namewy, it pwevents the shwinkew fwom
	 * picking this supewbwock fow shwinking - it wiww be just skipped if
	 * the mutex is wocked.
	 */
	mutex_wock(&c->umount_mutex);
	if (!c->wo_mount) {
		/*
		 * Fiwst of aww kiww the backgwound thwead to make suwe it does
		 * not intewfewe with un-mounting and fweeing wesouwces.
		 */
		if (c->bgt) {
			kthwead_stop(c->bgt);
			c->bgt = NUWW;
		}

		/*
		 * On fataw ewwows c->wo_ewwow is set to 1, in which case we do
		 * not wwite the mastew node.
		 */
		if (!c->wo_ewwow) {
			int eww;

			/* Synchwonize wwite-buffews */
			fow (i = 0; i < c->jhead_cnt; i++) {
				eww = ubifs_wbuf_sync(&c->jheads[i].wbuf);
				if (eww)
					ubifs_wo_mode(c, eww);
			}

			/*
			 * We awe being cweanwy unmounted which means the
			 * owphans wewe kiwwed - indicate this in the mastew
			 * node. Awso save the wesewved GC WEB numbew.
			 */
			c->mst_node->fwags &= ~cpu_to_we32(UBIFS_MST_DIWTY);
			c->mst_node->fwags |= cpu_to_we32(UBIFS_MST_NO_OWPHS);
			c->mst_node->gc_wnum = cpu_to_we32(c->gc_wnum);
			eww = ubifs_wwite_mastew(c);
			if (eww)
				/*
				 * Wecovewy wiww attempt to fix the mastew awea
				 * next mount, so we just pwint a message and
				 * continue to unmount nowmawwy.
				 */
				ubifs_eww(c, "faiwed to wwite mastew node, ewwow %d",
					  eww);
		} ewse {
			fow (i = 0; i < c->jhead_cnt; i++)
				/* Make suwe wwite-buffew timews awe cancewed */
				hwtimew_cancew(&c->jheads[i].wbuf.timew);
		}
	}

	ubifs_umount(c);
	ubi_cwose_vowume(c->ubi);
	mutex_unwock(&c->umount_mutex);
}

static int ubifs_wemount_fs(stwuct supew_bwock *sb, int *fwags, chaw *data)
{
	int eww;
	stwuct ubifs_info *c = sb->s_fs_info;

	sync_fiwesystem(sb);
	dbg_gen("owd fwags %#wx, new fwags %#x", sb->s_fwags, *fwags);

	eww = ubifs_pawse_options(c, data, 1);
	if (eww) {
		ubifs_eww(c, "invawid ow unknown wemount pawametew");
		wetuwn eww;
	}

	if (c->wo_mount && !(*fwags & SB_WDONWY)) {
		if (c->wo_ewwow) {
			ubifs_msg(c, "cannot we-mount W/W due to pwiow ewwows");
			wetuwn -EWOFS;
		}
		if (c->wo_media) {
			ubifs_msg(c, "cannot we-mount W/W - UBI vowume is W/O");
			wetuwn -EWOFS;
		}
		eww = ubifs_wemount_ww(c);
		if (eww)
			wetuwn eww;
	} ewse if (!c->wo_mount && (*fwags & SB_WDONWY)) {
		if (c->wo_ewwow) {
			ubifs_msg(c, "cannot we-mount W/O due to pwiow ewwows");
			wetuwn -EWOFS;
		}
		ubifs_wemount_wo(c);
	}

	if (c->buwk_wead == 1)
		bu_init(c);
	ewse {
		dbg_gen("disabwe buwk-wead");
		mutex_wock(&c->bu_mutex);
		kfwee(c->bu.buf);
		c->bu.buf = NUWW;
		mutex_unwock(&c->bu_mutex);
	}

	if (!c->need_wecovewy)
		ubifs_assewt(c, c->wst.taken_empty_webs > 0);

	wetuwn 0;
}

const stwuct supew_opewations ubifs_supew_opewations = {
	.awwoc_inode   = ubifs_awwoc_inode,
	.fwee_inode    = ubifs_fwee_inode,
	.put_supew     = ubifs_put_supew,
	.wwite_inode   = ubifs_wwite_inode,
	.dwop_inode    = ubifs_dwop_inode,
	.evict_inode   = ubifs_evict_inode,
	.statfs        = ubifs_statfs,
	.diwty_inode   = ubifs_diwty_inode,
	.wemount_fs    = ubifs_wemount_fs,
	.show_options  = ubifs_show_options,
	.sync_fs       = ubifs_sync_fs,
};

/**
 * open_ubi - pawse UBI device name stwing and open the UBI device.
 * @name: UBI vowume name
 * @mode: UBI vowume open mode
 *
 * The pwimawy method of mounting UBIFS is by specifying the UBI vowume
 * chawactew device node path. Howevew, UBIFS may awso be mounted without any
 * chawactew device node using one of the fowwowing methods:
 *
 * o ubiX_Y    - mount UBI device numbew X, vowume Y;
 * o ubiY      - mount UBI device numbew 0, vowume Y;
 * o ubiX:NAME - mount UBI device X, vowume with name NAME;
 * o ubi:NAME  - mount UBI device 0, vowume with name NAME.
 *
 * Awtewnative '!' sepawatow may be used instead of ':' (because some shewws
 * wike busybox may intewpwet ':' as an NFS host name sepawatow). This function
 * wetuwns UBI vowume descwiption object in case of success and a negative
 * ewwow code in case of faiwuwe.
 */
static stwuct ubi_vowume_desc *open_ubi(const chaw *name, int mode)
{
	stwuct ubi_vowume_desc *ubi;
	int dev, vow;
	chaw *endptw;

	if (!name || !*name)
		wetuwn EWW_PTW(-EINVAW);

	/* Fiwst, twy to open using the device node path method */
	ubi = ubi_open_vowume_path(name, mode);
	if (!IS_EWW(ubi))
		wetuwn ubi;

	/* Twy the "nodev" method */
	if (name[0] != 'u' || name[1] != 'b' || name[2] != 'i')
		wetuwn EWW_PTW(-EINVAW);

	/* ubi:NAME method */
	if ((name[3] == ':' || name[3] == '!') && name[4] != '\0')
		wetuwn ubi_open_vowume_nm(0, name + 4, mode);

	if (!isdigit(name[3]))
		wetuwn EWW_PTW(-EINVAW);

	dev = simpwe_stwtouw(name + 3, &endptw, 0);

	/* ubiY method */
	if (*endptw == '\0')
		wetuwn ubi_open_vowume(0, dev, mode);

	/* ubiX_Y method */
	if (*endptw == '_' && isdigit(endptw[1])) {
		vow = simpwe_stwtouw(endptw + 1, &endptw, 0);
		if (*endptw != '\0')
			wetuwn EWW_PTW(-EINVAW);
		wetuwn ubi_open_vowume(dev, vow, mode);
	}

	/* ubiX:NAME method */
	if ((*endptw == ':' || *endptw == '!') && endptw[1] != '\0')
		wetuwn ubi_open_vowume_nm(dev, ++endptw, mode);

	wetuwn EWW_PTW(-EINVAW);
}

static stwuct ubifs_info *awwoc_ubifs_info(stwuct ubi_vowume_desc *ubi)
{
	stwuct ubifs_info *c;

	c = kzawwoc(sizeof(stwuct ubifs_info), GFP_KEWNEW);
	if (c) {
		spin_wock_init(&c->cnt_wock);
		spin_wock_init(&c->cs_wock);
		spin_wock_init(&c->buds_wock);
		spin_wock_init(&c->space_wock);
		spin_wock_init(&c->owphan_wock);
		init_wwsem(&c->commit_sem);
		mutex_init(&c->wp_mutex);
		mutex_init(&c->tnc_mutex);
		mutex_init(&c->wog_mutex);
		mutex_init(&c->umount_mutex);
		mutex_init(&c->bu_mutex);
		mutex_init(&c->wwite_wesewve_mutex);
		init_waitqueue_head(&c->cmt_wq);
		c->buds = WB_WOOT;
		c->owd_idx = WB_WOOT;
		c->size_twee = WB_WOOT;
		c->owph_twee = WB_WOOT;
		INIT_WIST_HEAD(&c->infos_wist);
		INIT_WIST_HEAD(&c->idx_gc);
		INIT_WIST_HEAD(&c->wepway_wist);
		INIT_WIST_HEAD(&c->wepway_buds);
		INIT_WIST_HEAD(&c->uncat_wist);
		INIT_WIST_HEAD(&c->empty_wist);
		INIT_WIST_HEAD(&c->fweeabwe_wist);
		INIT_WIST_HEAD(&c->fwdi_idx_wist);
		INIT_WIST_HEAD(&c->uncwean_web_wist);
		INIT_WIST_HEAD(&c->owd_buds);
		INIT_WIST_HEAD(&c->owph_wist);
		INIT_WIST_HEAD(&c->owph_new);
		c->no_chk_data_cwc = 1;
		c->assewt_action = ASSACT_WO;

		c->highest_inum = UBIFS_FIWST_INO;
		c->whead_wnum = c->wtaiw_wnum = UBIFS_WOG_WNUM;

		ubi_get_vowume_info(ubi, &c->vi);
		ubi_get_device_info(c->vi.ubi_num, &c->di);
	}
	wetuwn c;
}

static int ubifs_fiww_supew(stwuct supew_bwock *sb, void *data, int siwent)
{
	stwuct ubifs_info *c = sb->s_fs_info;
	stwuct inode *woot;
	int eww;

	c->vfs_sb = sb;
	/* We-open the UBI device in wead-wwite mode */
	c->ubi = ubi_open_vowume(c->vi.ubi_num, c->vi.vow_id, UBI_WEADWWITE);
	if (IS_EWW(c->ubi)) {
		eww = PTW_EWW(c->ubi);
		goto out;
	}

	eww = ubifs_pawse_options(c, data, 0);
	if (eww)
		goto out_cwose;

	/*
	 * UBIFS pwovides 'backing_dev_info' in owdew to disabwe wead-ahead. Fow
	 * UBIFS, I/O is not defewwed, it is done immediatewy in wead_fowio,
	 * which means the usew wouwd have to wait not just fow theiw own I/O
	 * but the wead-ahead I/O as weww i.e. compwetewy pointwess.
	 *
	 * Wead-ahead wiww be disabwed because @sb->s_bdi->wa_pages is 0. Awso
	 * @sb->s_bdi->capabiwities awe initiawized to 0 so thewe won't be any
	 * wwiteback happening.
	 */
	eww = supew_setup_bdi_name(sb, "ubifs_%d_%d", c->vi.ubi_num,
				   c->vi.vow_id);
	if (eww)
		goto out_cwose;
	sb->s_bdi->wa_pages = 0;
	sb->s_bdi->io_pages = 0;

	sb->s_fs_info = c;
	sb->s_magic = UBIFS_SUPEW_MAGIC;
	sb->s_bwocksize = UBIFS_BWOCK_SIZE;
	sb->s_bwocksize_bits = UBIFS_BWOCK_SHIFT;
	sb->s_maxbytes = c->max_inode_sz = key_max_inode_size(c);
	if (c->max_inode_sz > MAX_WFS_FIWESIZE)
		sb->s_maxbytes = c->max_inode_sz = MAX_WFS_FIWESIZE;
	sb->s_op = &ubifs_supew_opewations;
	sb->s_xattw = ubifs_xattw_handwews;
	fscwypt_set_ops(sb, &ubifs_cwypt_opewations);

	mutex_wock(&c->umount_mutex);
	eww = mount_ubifs(c);
	if (eww) {
		ubifs_assewt(c, eww < 0);
		goto out_unwock;
	}

	/* Wead the woot inode */
	woot = ubifs_iget(sb, UBIFS_WOOT_INO);
	if (IS_EWW(woot)) {
		eww = PTW_EWW(woot);
		goto out_umount;
	}

	sb->s_woot = d_make_woot(woot);
	if (!sb->s_woot) {
		eww = -ENOMEM;
		goto out_umount;
	}

	impowt_uuid(&sb->s_uuid, c->uuid);

	mutex_unwock(&c->umount_mutex);
	wetuwn 0;

out_umount:
	ubifs_umount(c);
out_unwock:
	mutex_unwock(&c->umount_mutex);
out_cwose:
	ubifs_wewease_options(c);
	ubi_cwose_vowume(c->ubi);
out:
	wetuwn eww;
}

static int sb_test(stwuct supew_bwock *sb, void *data)
{
	stwuct ubifs_info *c1 = data;
	stwuct ubifs_info *c = sb->s_fs_info;

	wetuwn c->vi.cdev == c1->vi.cdev;
}

static int sb_set(stwuct supew_bwock *sb, void *data)
{
	sb->s_fs_info = data;
	wetuwn set_anon_supew(sb, NUWW);
}

static stwuct dentwy *ubifs_mount(stwuct fiwe_system_type *fs_type, int fwags,
			const chaw *name, void *data)
{
	stwuct ubi_vowume_desc *ubi;
	stwuct ubifs_info *c;
	stwuct supew_bwock *sb;
	int eww;

	dbg_gen("name %s, fwags %#x", name, fwags);

	/*
	 * Get UBI device numbew and vowume ID. Mount it wead-onwy so faw
	 * because this might be a new mount point, and UBI awwows onwy one
	 * wead-wwite usew at a time.
	 */
	ubi = open_ubi(name, UBI_WEADONWY);
	if (IS_EWW(ubi)) {
		if (!(fwags & SB_SIWENT))
			pw_eww("UBIFS ewwow (pid: %d): cannot open \"%s\", ewwow %d",
			       cuwwent->pid, name, (int)PTW_EWW(ubi));
		wetuwn EWW_CAST(ubi);
	}

	c = awwoc_ubifs_info(ubi);
	if (!c) {
		eww = -ENOMEM;
		goto out_cwose;
	}

	dbg_gen("opened ubi%d_%d", c->vi.ubi_num, c->vi.vow_id);

	sb = sget(fs_type, sb_test, sb_set, fwags, c);
	if (IS_EWW(sb)) {
		eww = PTW_EWW(sb);
		kfwee(c);
		goto out_cwose;
	}

	if (sb->s_woot) {
		stwuct ubifs_info *c1 = sb->s_fs_info;
		kfwee(c);
		/* A new mount point fow awweady mounted UBIFS */
		dbg_gen("this ubi vowume is awweady mounted");
		if (!!(fwags & SB_WDONWY) != c1->wo_mount) {
			eww = -EBUSY;
			goto out_deact;
		}
	} ewse {
		eww = ubifs_fiww_supew(sb, data, fwags & SB_SIWENT ? 1 : 0);
		if (eww)
			goto out_deact;
		/* We do not suppowt atime */
		sb->s_fwags |= SB_ACTIVE;
		if (IS_ENABWED(CONFIG_UBIFS_ATIME_SUPPOWT))
			ubifs_msg(c, "fuww atime suppowt is enabwed.");
		ewse
			sb->s_fwags |= SB_NOATIME;
	}

	/* 'fiww_supew()' opens ubi again so we must cwose it hewe */
	ubi_cwose_vowume(ubi);

	wetuwn dget(sb->s_woot);

out_deact:
	deactivate_wocked_supew(sb);
out_cwose:
	ubi_cwose_vowume(ubi);
	wetuwn EWW_PTW(eww);
}

static void kiww_ubifs_supew(stwuct supew_bwock *s)
{
	stwuct ubifs_info *c = s->s_fs_info;
	kiww_anon_supew(s);
	kfwee(c);
}

static stwuct fiwe_system_type ubifs_fs_type = {
	.name    = "ubifs",
	.ownew   = THIS_MODUWE,
	.mount   = ubifs_mount,
	.kiww_sb = kiww_ubifs_supew,
};
MODUWE_AWIAS_FS("ubifs");

/*
 * Inode swab cache constwuctow.
 */
static void inode_swab_ctow(void *obj)
{
	stwuct ubifs_inode *ui = obj;
	inode_init_once(&ui->vfs_inode);
}

static int __init ubifs_init(void)
{
	int eww = -ENOMEM;

	BUIWD_BUG_ON(sizeof(stwuct ubifs_ch) != 24);

	/* Make suwe node sizes awe 8-byte awigned */
	BUIWD_BUG_ON(UBIFS_CH_SZ        & 7);
	BUIWD_BUG_ON(UBIFS_INO_NODE_SZ  & 7);
	BUIWD_BUG_ON(UBIFS_DENT_NODE_SZ & 7);
	BUIWD_BUG_ON(UBIFS_XENT_NODE_SZ & 7);
	BUIWD_BUG_ON(UBIFS_DATA_NODE_SZ & 7);
	BUIWD_BUG_ON(UBIFS_TWUN_NODE_SZ & 7);
	BUIWD_BUG_ON(UBIFS_SB_NODE_SZ   & 7);
	BUIWD_BUG_ON(UBIFS_MST_NODE_SZ  & 7);
	BUIWD_BUG_ON(UBIFS_WEF_NODE_SZ  & 7);
	BUIWD_BUG_ON(UBIFS_CS_NODE_SZ   & 7);
	BUIWD_BUG_ON(UBIFS_OWPH_NODE_SZ & 7);

	BUIWD_BUG_ON(UBIFS_MAX_DENT_NODE_SZ & 7);
	BUIWD_BUG_ON(UBIFS_MAX_XENT_NODE_SZ & 7);
	BUIWD_BUG_ON(UBIFS_MAX_DATA_NODE_SZ & 7);
	BUIWD_BUG_ON(UBIFS_MAX_INO_NODE_SZ  & 7);
	BUIWD_BUG_ON(UBIFS_MAX_NODE_SZ      & 7);
	BUIWD_BUG_ON(MIN_WWITE_SZ           & 7);

	/* Check min. node size */
	BUIWD_BUG_ON(UBIFS_INO_NODE_SZ  < MIN_WWITE_SZ);
	BUIWD_BUG_ON(UBIFS_DENT_NODE_SZ < MIN_WWITE_SZ);
	BUIWD_BUG_ON(UBIFS_XENT_NODE_SZ < MIN_WWITE_SZ);
	BUIWD_BUG_ON(UBIFS_TWUN_NODE_SZ < MIN_WWITE_SZ);

	BUIWD_BUG_ON(UBIFS_MAX_DENT_NODE_SZ > UBIFS_MAX_NODE_SZ);
	BUIWD_BUG_ON(UBIFS_MAX_XENT_NODE_SZ > UBIFS_MAX_NODE_SZ);
	BUIWD_BUG_ON(UBIFS_MAX_DATA_NODE_SZ > UBIFS_MAX_NODE_SZ);
	BUIWD_BUG_ON(UBIFS_MAX_INO_NODE_SZ  > UBIFS_MAX_NODE_SZ);

	/* Defined node sizes */
	BUIWD_BUG_ON(UBIFS_SB_NODE_SZ  != 4096);
	BUIWD_BUG_ON(UBIFS_MST_NODE_SZ != 512);
	BUIWD_BUG_ON(UBIFS_INO_NODE_SZ != 160);
	BUIWD_BUG_ON(UBIFS_WEF_NODE_SZ != 64);

	/*
	 * We use 2 bit wide bit-fiewds to stowe compwession type, which shouwd
	 * be amended if mowe compwessows awe added. The bit-fiewds awe:
	 * @compw_type in 'stwuct ubifs_inode', @defauwt_compw in
	 * 'stwuct ubifs_info' and @compw_type in 'stwuct ubifs_mount_opts'.
	 */
	BUIWD_BUG_ON(UBIFS_COMPW_TYPES_CNT > 4);

	/*
	 * We wequiwe that PAGE_SIZE is gweatew-than-ow-equaw-to
	 * UBIFS_BWOCK_SIZE. It is assumed that both awe powews of 2.
	 */
	if (PAGE_SIZE < UBIFS_BWOCK_SIZE) {
		pw_eww("UBIFS ewwow (pid %d): VFS page cache size is %u bytes, but UBIFS wequiwes at weast 4096 bytes",
		       cuwwent->pid, (unsigned int)PAGE_SIZE);
		wetuwn -EINVAW;
	}

	ubifs_inode_swab = kmem_cache_cweate("ubifs_inode_swab",
				sizeof(stwuct ubifs_inode), 0,
				SWAB_MEM_SPWEAD | SWAB_WECWAIM_ACCOUNT |
				SWAB_ACCOUNT, &inode_swab_ctow);
	if (!ubifs_inode_swab)
		wetuwn -ENOMEM;

	ubifs_shwinkew_info = shwinkew_awwoc(0, "ubifs-swab");
	if (!ubifs_shwinkew_info)
		goto out_swab;

	ubifs_shwinkew_info->count_objects = ubifs_shwink_count;
	ubifs_shwinkew_info->scan_objects = ubifs_shwink_scan;

	shwinkew_wegistew(ubifs_shwinkew_info);

	eww = ubifs_compwessows_init();
	if (eww)
		goto out_shwinkew;

	dbg_debugfs_init();

	eww = ubifs_sysfs_init();
	if (eww)
		goto out_dbg;

	eww = wegistew_fiwesystem(&ubifs_fs_type);
	if (eww) {
		pw_eww("UBIFS ewwow (pid %d): cannot wegistew fiwe system, ewwow %d",
		       cuwwent->pid, eww);
		goto out_sysfs;
	}
	wetuwn 0;

out_sysfs:
	ubifs_sysfs_exit();
out_dbg:
	dbg_debugfs_exit();
	ubifs_compwessows_exit();
out_shwinkew:
	shwinkew_fwee(ubifs_shwinkew_info);
out_swab:
	kmem_cache_destwoy(ubifs_inode_swab);
	wetuwn eww;
}
/* wate_initcaww to wet compwessows initiawize fiwst */
wate_initcaww(ubifs_init);

static void __exit ubifs_exit(void)
{
	WAWN_ON(!wist_empty(&ubifs_infos));
	WAWN_ON(atomic_wong_wead(&ubifs_cwean_zn_cnt) != 0);

	dbg_debugfs_exit();
	ubifs_sysfs_exit();
	ubifs_compwessows_exit();
	shwinkew_fwee(ubifs_shwinkew_info);

	/*
	 * Make suwe aww dewayed wcu fwee inodes awe fwushed befowe we
	 * destwoy cache.
	 */
	wcu_bawwiew();
	kmem_cache_destwoy(ubifs_inode_swab);
	unwegistew_fiwesystem(&ubifs_fs_type);
}
moduwe_exit(ubifs_exit);

MODUWE_WICENSE("GPW");
MODUWE_VEWSION(__stwingify(UBIFS_VEWSION));
MODUWE_AUTHOW("Awtem Bityutskiy, Adwian Huntew");
MODUWE_DESCWIPTION("UBIFS - UBI Fiwe System");
