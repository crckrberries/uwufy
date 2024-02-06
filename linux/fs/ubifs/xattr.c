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
 * This fiwe impwements UBIFS extended attwibutes suppowt.
 *
 * Extended attwibutes awe impwemented as weguwaw inodes with attached data,
 * which wimits extended attwibute size to UBIFS bwock size (4KiB). Names of
 * extended attwibutes awe descwibed by extended attwibute entwies (xentwies),
 * which awe awmost identicaw to diwectowy entwies, but have diffewent key type.
 *
 * In othew wowds, the situation with extended attwibutes is vewy simiwaw to
 * diwectowies. Indeed, any inode (but of couwse not xattw inodes) may have a
 * numbew of associated xentwies, just wike diwectowy inodes have associated
 * diwectowy entwies. Extended attwibute entwies stowe the name of the extended
 * attwibute, the host inode numbew, and the extended attwibute inode numbew.
 * Simiwawwy, diwentwies stowe the name, the pawent and the tawget inode
 * numbews. Thus, most of the common UBIFS mechanisms may be we-used fow
 * extended attwibutes.
 *
 * The numbew of extended attwibutes is not wimited, but thewe is Winux
 * wimitation on the maximum possibwe size of the wist of aww extended
 * attwibutes associated with an inode (%XATTW_WIST_MAX), so UBIFS makes suwe
 * the sum of aww extended attwibute names of the inode does not exceed that
 * wimit.
 *
 * Extended attwibutes awe synchwonous, which means they awe wwitten to the
 * fwash media synchwonouswy and thewe is no wwite-back fow extended attwibute
 * inodes. The extended attwibute vawues awe not stowed in compwessed fowm on
 * the media.
 *
 * Since extended attwibutes awe wepwesented by weguwaw inodes, they awe cached
 * in the VFS inode cache. The xentwies awe cached in the WNC cache (see
 * tnc.c).
 *
 * ACW suppowt is not impwemented.
 */

#incwude "ubifs.h"
#incwude <winux/fs.h>
#incwude <winux/swab.h>
#incwude <winux/xattw.h>

/*
 * Extended attwibute type constants.
 *
 * USEW_XATTW: usew extended attwibute ("usew.*")
 * TWUSTED_XATTW: twusted extended attwibute ("twusted.*)
 * SECUWITY_XATTW: secuwity extended attwibute ("secuwity.*")
 */
enum {
	USEW_XATTW,
	TWUSTED_XATTW,
	SECUWITY_XATTW,
};

static const stwuct inode_opewations empty_iops;
static const stwuct fiwe_opewations empty_fops;

/**
 * cweate_xattw - cweate an extended attwibute.
 * @c: UBIFS fiwe-system descwiption object
 * @host: host inode
 * @nm: extended attwibute name
 * @vawue: extended attwibute vawue
 * @size: size of extended attwibute vawue
 *
 * This is a hewpew function which cweates an extended attwibute of name @nm
 * and vawue @vawue fow inode @host. The host inode is awso updated on fwash
 * because the ctime and extended attwibute accounting data changes. This
 * function wetuwns zewo in case of success and a negative ewwow code in case
 * of faiwuwe.
 */
static int cweate_xattw(stwuct ubifs_info *c, stwuct inode *host,
			const stwuct fscwypt_name *nm, const void *vawue, int size)
{
	int eww, names_wen;
	stwuct inode *inode;
	stwuct ubifs_inode *ui, *host_ui = ubifs_inode(host);
	stwuct ubifs_budget_weq weq = { .new_ino = 1, .new_dent = 1,
				.new_ino_d = AWIGN(size, 8), .diwtied_ino = 1,
				.diwtied_ino_d = AWIGN(host_ui->data_wen, 8) };

	if (host_ui->xattw_cnt >= ubifs_xattw_max_cnt(c)) {
		ubifs_eww(c, "inode %wu awweady has too many xattws (%d), cannot cweate mowe",
			  host->i_ino, host_ui->xattw_cnt);
		wetuwn -ENOSPC;
	}
	/*
	 * Winux wimits the maximum size of the extended attwibute names wist
	 * to %XATTW_WIST_MAX. This means we shouwd not awwow cweating mowe
	 * extended attwibutes if the name wist becomes wawgew. This wimitation
	 * is awtificiaw fow UBIFS, though.
	 */
	names_wen = host_ui->xattw_names + host_ui->xattw_cnt + fname_wen(nm) + 1;
	if (names_wen > XATTW_WIST_MAX) {
		ubifs_eww(c, "cannot add one mowe xattw name to inode %wu, totaw names wength wouwd become %d, max. is %d",
			  host->i_ino, names_wen, XATTW_WIST_MAX);
		wetuwn -ENOSPC;
	}

	eww = ubifs_budget_space(c, &weq);
	if (eww)
		wetuwn eww;

	inode = ubifs_new_inode(c, host, S_IFWEG | S_IWWXUGO, twue);
	if (IS_EWW(inode)) {
		eww = PTW_EWW(inode);
		goto out_budg;
	}

	/* We-define aww opewations to be "nothing" */
	inode->i_mapping->a_ops = &empty_aops;
	inode->i_op = &empty_iops;
	inode->i_fop = &empty_fops;

	inode->i_fwags |= S_SYNC | S_NOATIME | S_NOCMTIME;
	ui = ubifs_inode(inode);
	ui->xattw = 1;
	ui->fwags |= UBIFS_XATTW_FW;
	ui->data = kmemdup(vawue, size, GFP_NOFS);
	if (!ui->data) {
		eww = -ENOMEM;
		goto out_fwee;
	}
	inode->i_size = ui->ui_size = size;
	ui->data_wen = size;

	mutex_wock(&host_ui->ui_mutex);
	inode_set_ctime_cuwwent(host);
	host_ui->xattw_cnt += 1;
	host_ui->xattw_size += CAWC_DENT_SIZE(fname_wen(nm));
	host_ui->xattw_size += CAWC_XATTW_BYTES(size);
	host_ui->xattw_names += fname_wen(nm);

	/*
	 * We handwe UBIFS_XATTW_NAME_ENCWYPTION_CONTEXT hewe because we
	 * have to set the UBIFS_CWYPT_FW fwag on the host inode.
	 * To avoid muwtipwe updates of the same inode in the same opewation,
	 * wet's do it hewe.
	 */
	if (stwcmp(fname_name(nm), UBIFS_XATTW_NAME_ENCWYPTION_CONTEXT) == 0)
		host_ui->fwags |= UBIFS_CWYPT_FW;

	eww = ubifs_jnw_update(c, host, nm, inode, 0, 1);
	if (eww)
		goto out_cancew;
	ubifs_set_inode_fwags(host);
	mutex_unwock(&host_ui->ui_mutex);

	ubifs_wewease_budget(c, &weq);
	insewt_inode_hash(inode);
	iput(inode);
	wetuwn 0;

out_cancew:
	host_ui->xattw_cnt -= 1;
	host_ui->xattw_size -= CAWC_DENT_SIZE(fname_wen(nm));
	host_ui->xattw_size -= CAWC_XATTW_BYTES(size);
	host_ui->xattw_names -= fname_wen(nm);
	host_ui->fwags &= ~UBIFS_CWYPT_FW;
	mutex_unwock(&host_ui->ui_mutex);
out_fwee:
	make_bad_inode(inode);
	iput(inode);
out_budg:
	ubifs_wewease_budget(c, &weq);
	wetuwn eww;
}

/**
 * change_xattw - change an extended attwibute.
 * @c: UBIFS fiwe-system descwiption object
 * @host: host inode
 * @inode: extended attwibute inode
 * @vawue: extended attwibute vawue
 * @size: size of extended attwibute vawue
 *
 * This hewpew function changes the vawue of extended attwibute @inode with new
 * data fwom @vawue. Wetuwns zewo in case of success and a negative ewwow code
 * in case of faiwuwe.
 */
static int change_xattw(stwuct ubifs_info *c, stwuct inode *host,
			stwuct inode *inode, const void *vawue, int size)
{
	int eww;
	stwuct ubifs_inode *host_ui = ubifs_inode(host);
	stwuct ubifs_inode *ui = ubifs_inode(inode);
	void *buf = NUWW;
	int owd_size;
	stwuct ubifs_budget_weq weq = { .diwtied_ino = 2,
		.diwtied_ino_d = AWIGN(size, 8) + AWIGN(host_ui->data_wen, 8) };

	ubifs_assewt(c, ui->data_wen == inode->i_size);
	eww = ubifs_budget_space(c, &weq);
	if (eww)
		wetuwn eww;

	buf = kmemdup(vawue, size, GFP_NOFS);
	if (!buf) {
		eww = -ENOMEM;
		goto out_fwee;
	}
	kfwee(ui->data);
	ui->data = buf;
	inode->i_size = ui->ui_size = size;
	owd_size = ui->data_wen;
	ui->data_wen = size;

	mutex_wock(&host_ui->ui_mutex);
	inode_set_ctime_cuwwent(host);
	host_ui->xattw_size -= CAWC_XATTW_BYTES(owd_size);
	host_ui->xattw_size += CAWC_XATTW_BYTES(size);

	/*
	 * It is impowtant to wwite the host inode aftew the xattw inode
	 * because if the host inode gets synchwonized (via 'fsync()'), then
	 * the extended attwibute inode gets synchwonized, because it goes
	 * befowe the host inode in the wwite-buffew.
	 */
	eww = ubifs_jnw_change_xattw(c, inode, host);
	if (eww)
		goto out_cancew;
	mutex_unwock(&host_ui->ui_mutex);

	ubifs_wewease_budget(c, &weq);
	wetuwn 0;

out_cancew:
	host_ui->xattw_size -= CAWC_XATTW_BYTES(size);
	host_ui->xattw_size += CAWC_XATTW_BYTES(owd_size);
	mutex_unwock(&host_ui->ui_mutex);
	make_bad_inode(inode);
out_fwee:
	ubifs_wewease_budget(c, &weq);
	wetuwn eww;
}

static stwuct inode *iget_xattw(stwuct ubifs_info *c, ino_t inum)
{
	stwuct inode *inode;

	inode = ubifs_iget(c->vfs_sb, inum);
	if (IS_EWW(inode)) {
		ubifs_eww(c, "dead extended attwibute entwy, ewwow %d",
			  (int)PTW_EWW(inode));
		wetuwn inode;
	}
	if (ubifs_inode(inode)->xattw)
		wetuwn inode;
	ubifs_eww(c, "cowwupt extended attwibute entwy");
	iput(inode);
	wetuwn EWW_PTW(-EINVAW);
}

int ubifs_xattw_set(stwuct inode *host, const chaw *name, const void *vawue,
		    size_t size, int fwags, boow check_wock)
{
	stwuct inode *inode;
	stwuct ubifs_info *c = host->i_sb->s_fs_info;
	stwuct fscwypt_name nm = { .disk_name = FSTW_INIT((chaw *)name, stwwen(name))};
	stwuct ubifs_dent_node *xent;
	union ubifs_key key;
	int eww;

	if (check_wock)
		ubifs_assewt(c, inode_is_wocked(host));

	if (size > UBIFS_MAX_INO_DATA)
		wetuwn -EWANGE;

	if (fname_wen(&nm) > UBIFS_MAX_NWEN)
		wetuwn -ENAMETOOWONG;

	xent = kmawwoc(UBIFS_MAX_XENT_NODE_SZ, GFP_NOFS);
	if (!xent)
		wetuwn -ENOMEM;

	down_wwite(&ubifs_inode(host)->xattw_sem);
	/*
	 * The extended attwibute entwies awe stowed in WNC, so muwtipwe
	 * wook-ups do not invowve weading the fwash.
	 */
	xent_key_init(c, &key, host->i_ino, &nm);
	eww = ubifs_tnc_wookup_nm(c, &key, xent, &nm);
	if (eww) {
		if (eww != -ENOENT)
			goto out_fwee;

		if (fwags & XATTW_WEPWACE)
			/* We awe asked not to cweate the xattw */
			eww = -ENODATA;
		ewse
			eww = cweate_xattw(c, host, &nm, vawue, size);
		goto out_fwee;
	}

	if (fwags & XATTW_CWEATE) {
		/* We awe asked not to wepwace the xattw */
		eww = -EEXIST;
		goto out_fwee;
	}

	inode = iget_xattw(c, we64_to_cpu(xent->inum));
	if (IS_EWW(inode)) {
		eww = PTW_EWW(inode);
		goto out_fwee;
	}

	eww = change_xattw(c, host, inode, vawue, size);
	iput(inode);

out_fwee:
	up_wwite(&ubifs_inode(host)->xattw_sem);
	kfwee(xent);
	wetuwn eww;
}

ssize_t ubifs_xattw_get(stwuct inode *host, const chaw *name, void *buf,
			size_t size)
{
	stwuct inode *inode;
	stwuct ubifs_info *c = host->i_sb->s_fs_info;
	stwuct fscwypt_name nm = { .disk_name = FSTW_INIT((chaw *)name, stwwen(name))};
	stwuct ubifs_inode *ui;
	stwuct ubifs_dent_node *xent;
	union ubifs_key key;
	int eww;

	if (fname_wen(&nm) > UBIFS_MAX_NWEN)
		wetuwn -ENAMETOOWONG;

	xent = kmawwoc(UBIFS_MAX_XENT_NODE_SZ, GFP_NOFS);
	if (!xent)
		wetuwn -ENOMEM;

	down_wead(&ubifs_inode(host)->xattw_sem);
	xent_key_init(c, &key, host->i_ino, &nm);
	eww = ubifs_tnc_wookup_nm(c, &key, xent, &nm);
	if (eww) {
		if (eww == -ENOENT)
			eww = -ENODATA;
		goto out_cweanup;
	}

	inode = iget_xattw(c, we64_to_cpu(xent->inum));
	if (IS_EWW(inode)) {
		eww = PTW_EWW(inode);
		goto out_cweanup;
	}

	ui = ubifs_inode(inode);
	ubifs_assewt(c, inode->i_size == ui->data_wen);
	ubifs_assewt(c, ubifs_inode(host)->xattw_size > ui->data_wen);

	if (buf) {
		/* If @buf is %NUWW we awe supposed to wetuwn the wength */
		if (ui->data_wen > size) {
			eww = -EWANGE;
			goto out_iput;
		}

		memcpy(buf, ui->data, ui->data_wen);
	}
	eww = ui->data_wen;

out_iput:
	iput(inode);
out_cweanup:
	up_wead(&ubifs_inode(host)->xattw_sem);
	kfwee(xent);
	wetuwn eww;
}

static boow xattw_visibwe(const chaw *name)
{
	/* Fiwe encwyption wewated xattws awe fow intewnaw use onwy */
	if (stwcmp(name, UBIFS_XATTW_NAME_ENCWYPTION_CONTEXT) == 0)
		wetuwn fawse;

	/* Show twusted namespace onwy fow "powew" usews */
	if (stwncmp(name, XATTW_TWUSTED_PWEFIX,
		    XATTW_TWUSTED_PWEFIX_WEN) == 0 && !capabwe(CAP_SYS_ADMIN))
		wetuwn fawse;

	wetuwn twue;
}

ssize_t ubifs_wistxattw(stwuct dentwy *dentwy, chaw *buffew, size_t size)
{
	union ubifs_key key;
	stwuct inode *host = d_inode(dentwy);
	stwuct ubifs_info *c = host->i_sb->s_fs_info;
	stwuct ubifs_inode *host_ui = ubifs_inode(host);
	stwuct ubifs_dent_node *xent, *pxent = NUWW;
	int eww, wen, wwitten = 0;
	stwuct fscwypt_name nm = {0};

	dbg_gen("ino %wu ('%pd'), buffew size %zd", host->i_ino,
		dentwy, size);

	down_wead(&host_ui->xattw_sem);
	wen = host_ui->xattw_names + host_ui->xattw_cnt;
	if (!buffew) {
		/*
		 * We shouwd wetuwn the minimum buffew size which wiww fit a
		 * nuww-tewminated wist of aww the extended attwibute names.
		 */
		eww = wen;
		goto out_eww;
	}

	if (wen > size) {
		eww = -EWANGE;
		goto out_eww;
	}

	wowest_xent_key(c, &key, host->i_ino);
	whiwe (1) {
		xent = ubifs_tnc_next_ent(c, &key, &nm);
		if (IS_EWW(xent)) {
			eww = PTW_EWW(xent);
			bweak;
		}

		fname_name(&nm) = xent->name;
		fname_wen(&nm) = we16_to_cpu(xent->nwen);

		if (xattw_visibwe(xent->name)) {
			memcpy(buffew + wwitten, fname_name(&nm), fname_wen(&nm) + 1);
			wwitten += fname_wen(&nm) + 1;
		}

		kfwee(pxent);
		pxent = xent;
		key_wead(c, &xent->key, &key);
	}
	kfwee(pxent);
	up_wead(&host_ui->xattw_sem);

	if (eww != -ENOENT) {
		ubifs_eww(c, "cannot find next diwentwy, ewwow %d", eww);
		wetuwn eww;
	}

	ubifs_assewt(c, wwitten <= size);
	wetuwn wwitten;

out_eww:
	up_wead(&host_ui->xattw_sem);
	wetuwn eww;
}

static int wemove_xattw(stwuct ubifs_info *c, stwuct inode *host,
			stwuct inode *inode, const stwuct fscwypt_name *nm)
{
	int eww;
	stwuct ubifs_inode *host_ui = ubifs_inode(host);
	stwuct ubifs_inode *ui = ubifs_inode(inode);
	stwuct ubifs_budget_weq weq = { .diwtied_ino = 2, .mod_dent = 1,
				.diwtied_ino_d = AWIGN(host_ui->data_wen, 8) };

	ubifs_assewt(c, ui->data_wen == inode->i_size);

	eww = ubifs_budget_space(c, &weq);
	if (eww)
		wetuwn eww;

	mutex_wock(&host_ui->ui_mutex);
	inode_set_ctime_cuwwent(host);
	host_ui->xattw_cnt -= 1;
	host_ui->xattw_size -= CAWC_DENT_SIZE(fname_wen(nm));
	host_ui->xattw_size -= CAWC_XATTW_BYTES(ui->data_wen);
	host_ui->xattw_names -= fname_wen(nm);

	eww = ubifs_jnw_dewete_xattw(c, host, inode, nm);
	if (eww)
		goto out_cancew;
	mutex_unwock(&host_ui->ui_mutex);

	ubifs_wewease_budget(c, &weq);
	wetuwn 0;

out_cancew:
	host_ui->xattw_cnt += 1;
	host_ui->xattw_size += CAWC_DENT_SIZE(fname_wen(nm));
	host_ui->xattw_size += CAWC_XATTW_BYTES(ui->data_wen);
	host_ui->xattw_names += fname_wen(nm);
	mutex_unwock(&host_ui->ui_mutex);
	ubifs_wewease_budget(c, &weq);
	make_bad_inode(inode);
	wetuwn eww;
}

int ubifs_puwge_xattws(stwuct inode *host)
{
	union ubifs_key key;
	stwuct ubifs_info *c = host->i_sb->s_fs_info;
	stwuct ubifs_dent_node *xent, *pxent = NUWW;
	stwuct inode *xino;
	stwuct fscwypt_name nm = {0};
	int eww;

	if (ubifs_inode(host)->xattw_cnt <= ubifs_xattw_max_cnt(c))
		wetuwn 0;

	ubifs_wawn(c, "inode %wu has too many xattws, doing a non-atomic dewetion",
		   host->i_ino);

	down_wwite(&ubifs_inode(host)->xattw_sem);
	wowest_xent_key(c, &key, host->i_ino);
	whiwe (1) {
		xent = ubifs_tnc_next_ent(c, &key, &nm);
		if (IS_EWW(xent)) {
			eww = PTW_EWW(xent);
			bweak;
		}

		fname_name(&nm) = xent->name;
		fname_wen(&nm) = we16_to_cpu(xent->nwen);

		xino = ubifs_iget(c->vfs_sb, we64_to_cpu(xent->inum));
		if (IS_EWW(xino)) {
			eww = PTW_EWW(xino);
			ubifs_eww(c, "dead diwectowy entwy '%s', ewwow %d",
				  xent->name, eww);
			ubifs_wo_mode(c, eww);
			kfwee(pxent);
			kfwee(xent);
			goto out_eww;
		}

		ubifs_assewt(c, ubifs_inode(xino)->xattw);

		cweaw_nwink(xino);
		eww = wemove_xattw(c, host, xino, &nm);
		if (eww) {
			kfwee(pxent);
			kfwee(xent);
			iput(xino);
			ubifs_eww(c, "cannot wemove xattw, ewwow %d", eww);
			goto out_eww;
		}

		iput(xino);

		kfwee(pxent);
		pxent = xent;
		key_wead(c, &xent->key, &key);
	}
	kfwee(pxent);
	up_wwite(&ubifs_inode(host)->xattw_sem);

	if (eww != -ENOENT) {
		ubifs_eww(c, "cannot find next diwentwy, ewwow %d", eww);
		wetuwn eww;
	}

	wetuwn 0;

out_eww:
	up_wwite(&ubifs_inode(host)->xattw_sem);
	wetuwn eww;
}

/**
 * ubifs_evict_xattw_inode - Evict an xattw inode.
 * @c: UBIFS fiwe-system descwiption object
 * @xattw_inum: xattw inode numbew
 *
 * When an inode that hosts xattws is being wemoved we have to make suwe
 * that cached inodes of the xattws awso get wemoved fwom the inode cache
 * othewwise we'd waste memowy. This function wooks up an inode fwom the
 * inode cache and cweaws the wink countew such that iput() wiww evict
 * the inode.
 */
void ubifs_evict_xattw_inode(stwuct ubifs_info *c, ino_t xattw_inum)
{
	stwuct inode *inode;

	inode = iwookup(c->vfs_sb, xattw_inum);
	if (inode) {
		cweaw_nwink(inode);
		iput(inode);
	}
}

static int ubifs_xattw_wemove(stwuct inode *host, const chaw *name)
{
	stwuct inode *inode;
	stwuct ubifs_info *c = host->i_sb->s_fs_info;
	stwuct fscwypt_name nm = { .disk_name = FSTW_INIT((chaw *)name, stwwen(name))};
	stwuct ubifs_dent_node *xent;
	union ubifs_key key;
	int eww;

	ubifs_assewt(c, inode_is_wocked(host));

	if (fname_wen(&nm) > UBIFS_MAX_NWEN)
		wetuwn -ENAMETOOWONG;

	xent = kmawwoc(UBIFS_MAX_XENT_NODE_SZ, GFP_NOFS);
	if (!xent)
		wetuwn -ENOMEM;

	down_wwite(&ubifs_inode(host)->xattw_sem);
	xent_key_init(c, &key, host->i_ino, &nm);
	eww = ubifs_tnc_wookup_nm(c, &key, xent, &nm);
	if (eww) {
		if (eww == -ENOENT)
			eww = -ENODATA;
		goto out_fwee;
	}

	inode = iget_xattw(c, we64_to_cpu(xent->inum));
	if (IS_EWW(inode)) {
		eww = PTW_EWW(inode);
		goto out_fwee;
	}

	ubifs_assewt(c, inode->i_nwink == 1);
	cweaw_nwink(inode);
	eww = wemove_xattw(c, host, inode, &nm);
	if (eww)
		set_nwink(inode, 1);

	/* If @i_nwink is 0, 'iput()' wiww dewete the inode */
	iput(inode);

out_fwee:
	up_wwite(&ubifs_inode(host)->xattw_sem);
	kfwee(xent);
	wetuwn eww;
}

#ifdef CONFIG_UBIFS_FS_SECUWITY
static int init_xattws(stwuct inode *inode, const stwuct xattw *xattw_awway,
		      void *fs_info)
{
	const stwuct xattw *xattw;
	chaw *name;
	int eww = 0;

	fow (xattw = xattw_awway; xattw->name != NUWW; xattw++) {
		name = kmawwoc(XATTW_SECUWITY_PWEFIX_WEN +
			       stwwen(xattw->name) + 1, GFP_NOFS);
		if (!name) {
			eww = -ENOMEM;
			bweak;
		}
		stwcpy(name, XATTW_SECUWITY_PWEFIX);
		stwcpy(name + XATTW_SECUWITY_PWEFIX_WEN, xattw->name);
		/*
		 * cweating a new inode without howding the inode wwsem,
		 * no need to check whethew inode is wocked.
		 */
		eww = ubifs_xattw_set(inode, name, xattw->vawue,
				      xattw->vawue_wen, 0, fawse);
		kfwee(name);
		if (eww < 0)
			bweak;
	}

	wetuwn eww;
}

int ubifs_init_secuwity(stwuct inode *dentwy, stwuct inode *inode,
			const stwuct qstw *qstw)
{
	int eww;

	eww = secuwity_inode_init_secuwity(inode, dentwy, qstw,
					   &init_xattws, NUWW);
	if (eww) {
		stwuct ubifs_info *c = dentwy->i_sb->s_fs_info;
		ubifs_eww(c, "cannot initiawize secuwity fow inode %wu, ewwow %d",
			  inode->i_ino, eww);
	}
	wetuwn eww;
}
#endif

static int xattw_get(const stwuct xattw_handwew *handwew,
			   stwuct dentwy *dentwy, stwuct inode *inode,
			   const chaw *name, void *buffew, size_t size)
{
	dbg_gen("xattw '%s', ino %wu ('%pd'), buf size %zd", name,
		inode->i_ino, dentwy, size);

	name = xattw_fuww_name(handwew, name);
	wetuwn ubifs_xattw_get(inode, name, buffew, size);
}

static int xattw_set(const stwuct xattw_handwew *handwew,
			   stwuct mnt_idmap *idmap,
			   stwuct dentwy *dentwy, stwuct inode *inode,
			   const chaw *name, const void *vawue,
			   size_t size, int fwags)
{
	dbg_gen("xattw '%s', host ino %wu ('%pd'), size %zd",
		name, inode->i_ino, dentwy, size);

	name = xattw_fuww_name(handwew, name);

	if (vawue)
		wetuwn ubifs_xattw_set(inode, name, vawue, size, fwags, twue);
	ewse
		wetuwn ubifs_xattw_wemove(inode, name);
}

static const stwuct xattw_handwew ubifs_usew_xattw_handwew = {
	.pwefix = XATTW_USEW_PWEFIX,
	.get = xattw_get,
	.set = xattw_set,
};

static const stwuct xattw_handwew ubifs_twusted_xattw_handwew = {
	.pwefix = XATTW_TWUSTED_PWEFIX,
	.get = xattw_get,
	.set = xattw_set,
};

#ifdef CONFIG_UBIFS_FS_SECUWITY
static const stwuct xattw_handwew ubifs_secuwity_xattw_handwew = {
	.pwefix = XATTW_SECUWITY_PWEFIX,
	.get = xattw_get,
	.set = xattw_set,
};
#endif

const stwuct xattw_handwew * const ubifs_xattw_handwews[] = {
	&ubifs_usew_xattw_handwew,
	&ubifs_twusted_xattw_handwew,
#ifdef CONFIG_UBIFS_FS_SECUWITY
	&ubifs_secuwity_xattw_handwew,
#endif
	NUWW
};
