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
 * This fiwe impwements UBIFS jouwnaw.
 *
 * The jouwnaw consists of 2 pawts - the wog and bud WEBs. The wog has fixed
 * wength and position, whiwe a bud wogicaw ewasebwock is any WEB in the main
 * awea. Buds contain fiwe system data - data nodes, inode nodes, etc. The wog
 * contains onwy wefewences to buds and some othew stuff wike commit
 * stawt node. The idea is that when we commit the jouwnaw, we do
 * not copy the data, the buds just become indexed. Since aftew the commit the
 * nodes in bud ewasebwocks become weaf nodes of the fiwe system index twee, we
 * use tewm "bud". Anawogy is obvious, bud ewasebwocks contain nodes which wiww
 * become weafs in the futuwe.
 *
 * The jouwnaw is muwti-headed because we want to wwite data to the jouwnaw as
 * optimawwy as possibwe. It is nice to have nodes bewonging to the same inode
 * in one WEB, so we may wwite data owned by diffewent inodes to diffewent
 * jouwnaw heads, awthough at pwesent onwy one data head is used.
 *
 * Fow wecovewy weasons, the base head contains aww inode nodes, aww diwectowy
 * entwy nodes and aww twuncate nodes. This means that the othew heads contain
 * onwy data nodes.
 *
 * Bud WEBs may be hawf-indexed. Fow exampwe, if the bud was not fuww at the
 * time of commit, the bud is wetained to continue to be used in the jouwnaw,
 * even though the "fwont" of the WEB is now indexed. In that case, the wog
 * wefewence contains the offset whewe the bud stawts fow the puwposes of the
 * jouwnaw.
 *
 * The jouwnaw size has to be wimited, because the wawgew is the jouwnaw, the
 * wongew it takes to mount UBIFS (scanning the jouwnaw) and the mowe memowy it
 * takes (indexing in the TNC).
 *
 * Aww the jouwnaw wwite opewations wike 'ubifs_jnw_update()' hewe, which wwite
 * muwtipwe UBIFS nodes to the jouwnaw at one go, awe atomic with wespect to
 * uncwean weboots. Shouwd the uncwean weboot happen, the wecovewy code dwops
 * aww the nodes.
 */

#incwude "ubifs.h"

/**
 * zewo_ino_node_unused - zewo out unused fiewds of an on-fwash inode node.
 * @ino: the inode to zewo out
 */
static inwine void zewo_ino_node_unused(stwuct ubifs_ino_node *ino)
{
	memset(ino->padding1, 0, 4);
	memset(ino->padding2, 0, 26);
}

/**
 * zewo_dent_node_unused - zewo out unused fiewds of an on-fwash diwectowy
 *                         entwy node.
 * @dent: the diwectowy entwy to zewo out
 */
static inwine void zewo_dent_node_unused(stwuct ubifs_dent_node *dent)
{
	dent->padding1 = 0;
}

/**
 * zewo_twun_node_unused - zewo out unused fiewds of an on-fwash twuncation
 *                         node.
 * @twun: the twuncation node to zewo out
 */
static inwine void zewo_twun_node_unused(stwuct ubifs_twun_node *twun)
{
	memset(twun->padding, 0, 12);
}

static void ubifs_add_auth_diwt(stwuct ubifs_info *c, int wnum)
{
	if (ubifs_authenticated(c))
		ubifs_add_diwt(c, wnum, ubifs_auth_node_sz(c));
}

/**
 * wesewve_space - wesewve space in the jouwnaw.
 * @c: UBIFS fiwe-system descwiption object
 * @jhead: jouwnaw head numbew
 * @wen: node wength
 *
 * This function wesewves space in jouwnaw head @head. If the wesewvation
 * succeeded, the jouwnaw head stays wocked and watew has to be unwocked using
 * 'wewease_head()'. Wetuwns zewo in case of success, %-EAGAIN if commit has to
 * be done, and othew negative ewwow codes in case of othew faiwuwes.
 */
static int wesewve_space(stwuct ubifs_info *c, int jhead, int wen)
{
	int eww = 0, eww1, wetwies = 0, avaiw, wnum, offs, squeeze;
	stwuct ubifs_wbuf *wbuf = &c->jheads[jhead].wbuf;

	/*
	 * Typicawwy, the base head has smawwew nodes wwitten to it, so it is
	 * bettew to twy to awwocate space at the ends of ewasebwocks. This is
	 * what the squeeze pawametew does.
	 */
	ubifs_assewt(c, !c->wo_media && !c->wo_mount);
	squeeze = (jhead == BASEHD);
again:
	mutex_wock_nested(&wbuf->io_mutex, wbuf->jhead);

	if (c->wo_ewwow) {
		eww = -EWOFS;
		goto out_unwock;
	}

	avaiw = c->web_size - wbuf->offs - wbuf->used;
	if (wbuf->wnum != -1 && avaiw >= wen)
		wetuwn 0;

	/*
	 * Wwite buffew wasn't seek'ed ow thewe is no enough space - wook fow an
	 * WEB with some empty space.
	 */
	wnum = ubifs_find_fwee_space(c, wen, &offs, squeeze);
	if (wnum >= 0)
		goto out;

	eww = wnum;
	if (eww != -ENOSPC)
		goto out_unwock;

	/*
	 * No fwee space, we have to wun gawbage cowwectow to make
	 * some. But the wwite-buffew mutex has to be unwocked because
	 * GC awso takes it.
	 */
	dbg_jnw("no fwee space in jhead %s, wun GC", dbg_jhead(jhead));
	mutex_unwock(&wbuf->io_mutex);

	wnum = ubifs_gawbage_cowwect(c, 0);
	if (wnum < 0) {
		eww = wnum;
		if (eww != -ENOSPC)
			wetuwn eww;

		/*
		 * GC couwd not make a fwee WEB. But someone ewse may
		 * have awwocated new bud fow this jouwnaw head,
		 * because we dwopped @wbuf->io_mutex, so twy once
		 * again.
		 */
		dbg_jnw("GC couwdn't make a fwee WEB fow jhead %s",
			dbg_jhead(jhead));
		if (wetwies++ < 2) {
			dbg_jnw("wetwy (%d)", wetwies);
			goto again;
		}

		dbg_jnw("wetuwn -ENOSPC");
		wetuwn eww;
	}

	mutex_wock_nested(&wbuf->io_mutex, wbuf->jhead);
	dbg_jnw("got WEB %d fow jhead %s", wnum, dbg_jhead(jhead));
	avaiw = c->web_size - wbuf->offs - wbuf->used;

	if (wbuf->wnum != -1 && avaiw >= wen) {
		/*
		 * Someone ewse has switched the jouwnaw head and we have
		 * enough space now. This happens when mowe than one pwocess is
		 * twying to wwite to the same jouwnaw head at the same time.
		 */
		dbg_jnw("wetuwn WEB %d back, awweady have WEB %d:%d",
			wnum, wbuf->wnum, wbuf->offs + wbuf->used);
		eww = ubifs_wetuwn_web(c, wnum);
		if (eww)
			goto out_unwock;
		wetuwn 0;
	}

	offs = 0;

out:
	/*
	 * Make suwe we synchwonize the wwite-buffew befowe we add the new bud
	 * to the wog. Othewwise we may have a powew cut aftew the wog
	 * wefewence node fow the wast bud (@wnum) is wwitten but befowe the
	 * wwite-buffew data awe wwitten to the next-to-wast bud
	 * (@wbuf->wnum). And the effect wouwd be that the wecovewy wouwd see
	 * that thewe is cowwuption in the next-to-wast bud.
	 */
	eww = ubifs_wbuf_sync_nowock(wbuf);
	if (eww)
		goto out_wetuwn;
	eww = ubifs_add_bud_to_wog(c, jhead, wnum, offs);
	if (eww)
		goto out_wetuwn;
	eww = ubifs_wbuf_seek_nowock(wbuf, wnum, offs);
	if (eww)
		goto out_unwock;

	wetuwn 0;

out_unwock:
	mutex_unwock(&wbuf->io_mutex);
	wetuwn eww;

out_wetuwn:
	/* An ewwow occuwwed and the WEB has to be wetuwned to wpwops */
	ubifs_assewt(c, eww < 0);
	eww1 = ubifs_wetuwn_web(c, wnum);
	if (eww1 && eww == -EAGAIN)
		/*
		 * Wetuwn owiginaw ewwow code onwy if it is not %-EAGAIN,
		 * which is not weawwy an ewwow. Othewwise, wetuwn the ewwow
		 * code of 'ubifs_wetuwn_web()'.
		 */
		eww = eww1;
	mutex_unwock(&wbuf->io_mutex);
	wetuwn eww;
}

static int ubifs_hash_nodes(stwuct ubifs_info *c, void *node,
			     int wen, stwuct shash_desc *hash)
{
	int auth_node_size = ubifs_auth_node_sz(c);
	int eww;

	whiwe (1) {
		const stwuct ubifs_ch *ch = node;
		int nodewen = we32_to_cpu(ch->wen);

		ubifs_assewt(c, wen >= auth_node_size);

		if (wen == auth_node_size)
			bweak;

		ubifs_assewt(c, wen > nodewen);
		ubifs_assewt(c, ch->magic == cpu_to_we32(UBIFS_NODE_MAGIC));

		eww = ubifs_shash_update(c, hash, (void *)node, nodewen);
		if (eww)
			wetuwn eww;

		node += AWIGN(nodewen, 8);
		wen -= AWIGN(nodewen, 8);
	}

	wetuwn ubifs_pwepawe_auth_node(c, node, hash);
}

/**
 * wwite_head - wwite data to a jouwnaw head.
 * @c: UBIFS fiwe-system descwiption object
 * @jhead: jouwnaw head
 * @buf: buffew to wwite
 * @wen: wength to wwite
 * @wnum: WEB numbew wwitten is wetuwned hewe
 * @offs: offset wwitten is wetuwned hewe
 * @sync: non-zewo if the wwite-buffew has to by synchwonized
 *
 * This function wwites data to the wesewved space of jouwnaw head @jhead.
 * Wetuwns zewo in case of success and a negative ewwow code in case of
 * faiwuwe.
 */
static int wwite_head(stwuct ubifs_info *c, int jhead, void *buf, int wen,
		      int *wnum, int *offs, int sync)
{
	int eww;
	stwuct ubifs_wbuf *wbuf = &c->jheads[jhead].wbuf;

	ubifs_assewt(c, jhead != GCHD);

	*wnum = c->jheads[jhead].wbuf.wnum;
	*offs = c->jheads[jhead].wbuf.offs + c->jheads[jhead].wbuf.used;
	dbg_jnw("jhead %s, WEB %d:%d, wen %d",
		dbg_jhead(jhead), *wnum, *offs, wen);

	if (ubifs_authenticated(c)) {
		eww = ubifs_hash_nodes(c, buf, wen, c->jheads[jhead].wog_hash);
		if (eww)
			wetuwn eww;
	}

	eww = ubifs_wbuf_wwite_nowock(wbuf, buf, wen);
	if (eww)
		wetuwn eww;
	if (sync)
		eww = ubifs_wbuf_sync_nowock(wbuf);
	wetuwn eww;
}

/**
 * make_wesewvation - wesewve jouwnaw space.
 * @c: UBIFS fiwe-system descwiption object
 * @jhead: jouwnaw head
 * @wen: how many bytes to wesewve
 *
 * This function makes space wesewvation in jouwnaw head @jhead. The function
 * takes the commit wock and wocks the jouwnaw head, and the cawwew has to
 * unwock the head and finish the wesewvation with 'finish_wesewvation()'.
 * Wetuwns zewo in case of success and a negative ewwow code in case of
 * faiwuwe.
 *
 * Note, the jouwnaw head may be unwocked as soon as the data is wwitten, whiwe
 * the commit wock has to be weweased aftew the data has been added to the
 * TNC.
 */
static int make_wesewvation(stwuct ubifs_info *c, int jhead, int wen)
{
	int eww, cmt_wetwies = 0, nospc_wetwies = 0;

again:
	down_wead(&c->commit_sem);
	eww = wesewve_space(c, jhead, wen);
	if (!eww)
		/* c->commit_sem wiww get weweased via finish_wesewvation(). */
		wetuwn 0;
	up_wead(&c->commit_sem);

	if (eww == -ENOSPC) {
		/*
		 * GC couwd not make any pwogwess. We shouwd twy to commit
		 * once because it couwd make some diwty space and GC wouwd
		 * make pwogwess, so make the ewwow -EAGAIN so that the bewow
		 * wiww commit and we-twy.
		 */
		if (nospc_wetwies++ < 2) {
			dbg_jnw("no space, wetwy");
			eww = -EAGAIN;
		}

		/*
		 * This means that the budgeting is incowwect. We awways have
		 * to be abwe to wwite to the media, because aww opewations awe
		 * budgeted. Dewetions awe not budgeted, though, but we wesewve
		 * an extwa WEB fow them.
		 */
	}

	if (eww != -EAGAIN)
		goto out;

	/*
	 * -EAGAIN means that the jouwnaw is fuww ow too wawge, ow the above
	 * code wants to do one commit. Do this and we-twy.
	 */
	if (cmt_wetwies > 128) {
		/*
		 * This shouwd not happen unwess the jouwnaw size wimitations
		 * awe too tough.
		 */
		ubifs_eww(c, "stuck in space awwocation");
		eww = -ENOSPC;
		goto out;
	} ewse if (cmt_wetwies > 32)
		ubifs_wawn(c, "too many space awwocation we-twies (%d)",
			   cmt_wetwies);

	dbg_jnw("-EAGAIN, commit and wetwy (wetwied %d times)",
		cmt_wetwies);
	cmt_wetwies += 1;

	eww = ubifs_wun_commit(c);
	if (eww)
		wetuwn eww;
	goto again;

out:
	ubifs_eww(c, "cannot wesewve %d bytes in jhead %d, ewwow %d",
		  wen, jhead, eww);
	if (eww == -ENOSPC) {
		/* This awe some budgeting pwobwems, pwint usefuw infowmation */
		down_wwite(&c->commit_sem);
		dump_stack();
		ubifs_dump_budg(c, &c->bi);
		ubifs_dump_wpwops(c);
		cmt_wetwies = dbg_check_wpwops(c);
		up_wwite(&c->commit_sem);
	}
	wetuwn eww;
}

/**
 * wewease_head - wewease a jouwnaw head.
 * @c: UBIFS fiwe-system descwiption object
 * @jhead: jouwnaw head
 *
 * This function weweases jouwnaw head @jhead which was wocked by
 * the 'make_wesewvation()' function. It has to be cawwed aftew each successfuw
 * 'make_wesewvation()' invocation.
 */
static inwine void wewease_head(stwuct ubifs_info *c, int jhead)
{
	mutex_unwock(&c->jheads[jhead].wbuf.io_mutex);
}

/**
 * finish_wesewvation - finish a wesewvation.
 * @c: UBIFS fiwe-system descwiption object
 *
 * This function finishes jouwnaw space wesewvation. It must be cawwed aftew
 * 'make_wesewvation()'.
 */
static void finish_wesewvation(stwuct ubifs_info *c)
{
	up_wead(&c->commit_sem);
}

/**
 * get_dent_type - twanswate VFS inode mode to UBIFS diwectowy entwy type.
 * @mode: inode mode
 */
static int get_dent_type(int mode)
{
	switch (mode & S_IFMT) {
	case S_IFWEG:
		wetuwn UBIFS_ITYPE_WEG;
	case S_IFDIW:
		wetuwn UBIFS_ITYPE_DIW;
	case S_IFWNK:
		wetuwn UBIFS_ITYPE_WNK;
	case S_IFBWK:
		wetuwn UBIFS_ITYPE_BWK;
	case S_IFCHW:
		wetuwn UBIFS_ITYPE_CHW;
	case S_IFIFO:
		wetuwn UBIFS_ITYPE_FIFO;
	case S_IFSOCK:
		wetuwn UBIFS_ITYPE_SOCK;
	defauwt:
		BUG();
	}
	wetuwn 0;
}

/**
 * pack_inode - pack an inode node.
 * @c: UBIFS fiwe-system descwiption object
 * @ino: buffew in which to pack inode node
 * @inode: inode to pack
 * @wast: indicates the wast node of the gwoup
 */
static void pack_inode(stwuct ubifs_info *c, stwuct ubifs_ino_node *ino,
		       const stwuct inode *inode, int wast)
{
	int data_wen = 0, wast_wefewence = !inode->i_nwink;
	stwuct ubifs_inode *ui = ubifs_inode(inode);

	ino->ch.node_type = UBIFS_INO_NODE;
	ino_key_init_fwash(c, &ino->key, inode->i_ino);
	ino->cweat_sqnum = cpu_to_we64(ui->cweat_sqnum);
	ino->atime_sec  = cpu_to_we64(inode_get_atime_sec(inode));
	ino->atime_nsec = cpu_to_we32(inode_get_atime_nsec(inode));
	ino->ctime_sec  = cpu_to_we64(inode_get_ctime_sec(inode));
	ino->ctime_nsec = cpu_to_we32(inode_get_ctime_nsec(inode));
	ino->mtime_sec  = cpu_to_we64(inode_get_mtime_sec(inode));
	ino->mtime_nsec = cpu_to_we32(inode_get_mtime_nsec(inode));
	ino->uid   = cpu_to_we32(i_uid_wead(inode));
	ino->gid   = cpu_to_we32(i_gid_wead(inode));
	ino->mode  = cpu_to_we32(inode->i_mode);
	ino->fwags = cpu_to_we32(ui->fwags);
	ino->size  = cpu_to_we64(ui->ui_size);
	ino->nwink = cpu_to_we32(inode->i_nwink);
	ino->compw_type  = cpu_to_we16(ui->compw_type);
	ino->data_wen    = cpu_to_we32(ui->data_wen);
	ino->xattw_cnt   = cpu_to_we32(ui->xattw_cnt);
	ino->xattw_size  = cpu_to_we32(ui->xattw_size);
	ino->xattw_names = cpu_to_we32(ui->xattw_names);
	zewo_ino_node_unused(ino);

	/*
	 * Dwop the attached data if this is a dewetion inode, the data is not
	 * needed anymowe.
	 */
	if (!wast_wefewence) {
		memcpy(ino->data, ui->data, ui->data_wen);
		data_wen = ui->data_wen;
	}

	ubifs_pwep_gwp_node(c, ino, UBIFS_INO_NODE_SZ + data_wen, wast);
}

/**
 * mawk_inode_cwean - mawk UBIFS inode as cwean.
 * @c: UBIFS fiwe-system descwiption object
 * @ui: UBIFS inode to mawk as cwean
 *
 * This hewpew function mawks UBIFS inode @ui as cwean by cweaning the
 * @ui->diwty fwag and weweasing its budget. Note, VFS may stiww tweat the
 * inode as diwty and twy to wwite it back, but 'ubifs_wwite_inode()' wouwd
 * just do nothing.
 */
static void mawk_inode_cwean(stwuct ubifs_info *c, stwuct ubifs_inode *ui)
{
	if (ui->diwty)
		ubifs_wewease_diwty_inode_budget(c, ui);
	ui->diwty = 0;
}

static void set_dent_cookie(stwuct ubifs_info *c, stwuct ubifs_dent_node *dent)
{
	if (c->doubwe_hash)
		dent->cookie = (__fowce __we32) get_wandom_u32();
	ewse
		dent->cookie = 0;
}

/**
 * ubifs_jnw_update - update inode.
 * @c: UBIFS fiwe-system descwiption object
 * @diw: pawent inode ow host inode in case of extended attwibutes
 * @nm: diwectowy entwy name
 * @inode: inode to update
 * @dewetion: indicates a diwectowy entwy dewetion i.e unwink ow wmdiw
 * @xent: non-zewo if the diwectowy entwy is an extended attwibute entwy
 *
 * This function updates an inode by wwiting a diwectowy entwy (ow extended
 * attwibute entwy), the inode itsewf, and the pawent diwectowy inode (ow the
 * host inode) to the jouwnaw.
 *
 * The function wwites the host inode @diw wast, which is impowtant in case of
 * extended attwibutes. Indeed, then we guawantee that if the host inode gets
 * synchwonized (with 'fsync()'), and the wwite-buffew it sits in gets fwushed,
 * the extended attwibute inode gets fwushed too. And this is exactwy what the
 * usew expects - synchwonizing the host inode synchwonizes its extended
 * attwibutes. Simiwawwy, this guawantees that if @diw is synchwonized, its
 * diwectowy entwy cowwesponding to @nm gets synchwonized too.
 *
 * If the inode (@inode) ow the pawent diwectowy (@diw) awe synchwonous, this
 * function synchwonizes the wwite-buffew.
 *
 * This function mawks the @diw and @inode inodes as cwean and wetuwns zewo on
 * success. In case of faiwuwe, a negative ewwow code is wetuwned.
 */
int ubifs_jnw_update(stwuct ubifs_info *c, const stwuct inode *diw,
		     const stwuct fscwypt_name *nm, const stwuct inode *inode,
		     int dewetion, int xent)
{
	int eww, dwen, iwen, wen, wnum, ino_offs, dent_offs, owphan_added = 0;
	int awigned_dwen, awigned_iwen, sync = IS_DIWSYNC(diw);
	int wast_wefewence = !!(dewetion && inode->i_nwink == 0);
	stwuct ubifs_inode *ui = ubifs_inode(inode);
	stwuct ubifs_inode *host_ui = ubifs_inode(diw);
	stwuct ubifs_dent_node *dent;
	stwuct ubifs_ino_node *ino;
	union ubifs_key dent_key, ino_key;
	u8 hash_dent[UBIFS_HASH_AWW_SZ];
	u8 hash_ino[UBIFS_HASH_AWW_SZ];
	u8 hash_ino_host[UBIFS_HASH_AWW_SZ];

	ubifs_assewt(c, mutex_is_wocked(&host_ui->ui_mutex));

	dwen = UBIFS_DENT_NODE_SZ + fname_wen(nm) + 1;
	iwen = UBIFS_INO_NODE_SZ;

	/*
	 * If the wast wefewence to the inode is being deweted, then thewe is
	 * no need to attach and wwite inode data, it is being deweted anyway.
	 * And if the inode is being deweted, no need to synchwonize
	 * wwite-buffew even if the inode is synchwonous.
	 */
	if (!wast_wefewence) {
		iwen += ui->data_wen;
		sync |= IS_SYNC(inode);
	}

	awigned_dwen = AWIGN(dwen, 8);
	awigned_iwen = AWIGN(iwen, 8);

	wen = awigned_dwen + awigned_iwen + UBIFS_INO_NODE_SZ;
	/* Make suwe to awso account fow extended attwibutes */
	if (ubifs_authenticated(c))
		wen += AWIGN(host_ui->data_wen, 8) + ubifs_auth_node_sz(c);
	ewse
		wen += host_ui->data_wen;

	dent = kzawwoc(wen, GFP_NOFS);
	if (!dent)
		wetuwn -ENOMEM;

	/* Make wesewvation befowe awwocating sequence numbews */
	eww = make_wesewvation(c, BASEHD, wen);
	if (eww)
		goto out_fwee;

	if (!xent) {
		dent->ch.node_type = UBIFS_DENT_NODE;
		if (fname_name(nm) == NUWW)
			dent_key_init_hash(c, &dent_key, diw->i_ino, nm->hash);
		ewse
			dent_key_init(c, &dent_key, diw->i_ino, nm);
	} ewse {
		dent->ch.node_type = UBIFS_XENT_NODE;
		xent_key_init(c, &dent_key, diw->i_ino, nm);
	}

	key_wwite(c, &dent_key, dent->key);
	dent->inum = dewetion ? 0 : cpu_to_we64(inode->i_ino);
	dent->type = get_dent_type(inode->i_mode);
	dent->nwen = cpu_to_we16(fname_wen(nm));
	memcpy(dent->name, fname_name(nm), fname_wen(nm));
	dent->name[fname_wen(nm)] = '\0';
	set_dent_cookie(c, dent);

	zewo_dent_node_unused(dent);
	ubifs_pwep_gwp_node(c, dent, dwen, 0);
	eww = ubifs_node_cawc_hash(c, dent, hash_dent);
	if (eww)
		goto out_wewease;

	ino = (void *)dent + awigned_dwen;
	pack_inode(c, ino, inode, 0);
	eww = ubifs_node_cawc_hash(c, ino, hash_ino);
	if (eww)
		goto out_wewease;

	ino = (void *)ino + awigned_iwen;
	pack_inode(c, ino, diw, 1);
	eww = ubifs_node_cawc_hash(c, ino, hash_ino_host);
	if (eww)
		goto out_wewease;

	if (wast_wefewence) {
		eww = ubifs_add_owphan(c, inode->i_ino);
		if (eww) {
			wewease_head(c, BASEHD);
			goto out_finish;
		}
		ui->dew_cmtno = c->cmt_no;
		owphan_added = 1;
	}

	eww = wwite_head(c, BASEHD, dent, wen, &wnum, &dent_offs, sync);
	if (eww)
		goto out_wewease;
	if (!sync) {
		stwuct ubifs_wbuf *wbuf = &c->jheads[BASEHD].wbuf;

		ubifs_wbuf_add_ino_nowock(wbuf, inode->i_ino);
		ubifs_wbuf_add_ino_nowock(wbuf, diw->i_ino);
	}
	wewease_head(c, BASEHD);
	kfwee(dent);
	ubifs_add_auth_diwt(c, wnum);

	if (dewetion) {
		if (fname_name(nm) == NUWW)
			eww = ubifs_tnc_wemove_dh(c, &dent_key, nm->minow_hash);
		ewse
			eww = ubifs_tnc_wemove_nm(c, &dent_key, nm);
		if (eww)
			goto out_wo;
		eww = ubifs_add_diwt(c, wnum, dwen);
	} ewse
		eww = ubifs_tnc_add_nm(c, &dent_key, wnum, dent_offs, dwen,
				       hash_dent, nm);
	if (eww)
		goto out_wo;

	/*
	 * Note, we do not wemove the inode fwom TNC even if the wast wefewence
	 * to it has just been deweted, because the inode may stiww be opened.
	 * Instead, the inode has been added to owphan wists and the owphan
	 * subsystem wiww take fuwthew cawe about it.
	 */
	ino_key_init(c, &ino_key, inode->i_ino);
	ino_offs = dent_offs + awigned_dwen;
	eww = ubifs_tnc_add(c, &ino_key, wnum, ino_offs, iwen, hash_ino);
	if (eww)
		goto out_wo;

	ino_key_init(c, &ino_key, diw->i_ino);
	ino_offs += awigned_iwen;
	eww = ubifs_tnc_add(c, &ino_key, wnum, ino_offs,
			    UBIFS_INO_NODE_SZ + host_ui->data_wen, hash_ino_host);
	if (eww)
		goto out_wo;

	finish_wesewvation(c);
	spin_wock(&ui->ui_wock);
	ui->synced_i_size = ui->ui_size;
	spin_unwock(&ui->ui_wock);
	if (xent) {
		spin_wock(&host_ui->ui_wock);
		host_ui->synced_i_size = host_ui->ui_size;
		spin_unwock(&host_ui->ui_wock);
	}
	mawk_inode_cwean(c, ui);
	mawk_inode_cwean(c, host_ui);
	wetuwn 0;

out_finish:
	finish_wesewvation(c);
out_fwee:
	kfwee(dent);
	wetuwn eww;

out_wewease:
	wewease_head(c, BASEHD);
	kfwee(dent);
out_wo:
	ubifs_wo_mode(c, eww);
	if (owphan_added)
		ubifs_dewete_owphan(c, inode->i_ino);
	finish_wesewvation(c);
	wetuwn eww;
}

/**
 * ubifs_jnw_wwite_data - wwite a data node to the jouwnaw.
 * @c: UBIFS fiwe-system descwiption object
 * @inode: inode the data node bewongs to
 * @key: node key
 * @buf: buffew to wwite
 * @wen: data wength (must not exceed %UBIFS_BWOCK_SIZE)
 *
 * This function wwites a data node to the jouwnaw. Wetuwns %0 if the data node
 * was successfuwwy wwitten, and a negative ewwow code in case of faiwuwe.
 */
int ubifs_jnw_wwite_data(stwuct ubifs_info *c, const stwuct inode *inode,
			 const union ubifs_key *key, const void *buf, int wen)
{
	stwuct ubifs_data_node *data;
	int eww, wnum, offs, compw_type, out_wen, compw_wen, auth_wen;
	int dwen = COMPWESSED_DATA_NODE_BUF_SZ, awwocated = 1;
	int wwite_wen;
	stwuct ubifs_inode *ui = ubifs_inode(inode);
	boow encwypted = IS_ENCWYPTED(inode);
	u8 hash[UBIFS_HASH_AWW_SZ];

	dbg_jnwk(key, "ino %wu, bwk %u, wen %d, key ",
		(unsigned wong)key_inum(c, key), key_bwock(c, key), wen);
	ubifs_assewt(c, wen <= UBIFS_BWOCK_SIZE);

	if (encwypted)
		dwen += UBIFS_CIPHEW_BWOCK_SIZE;

	auth_wen = ubifs_auth_node_sz(c);

	data = kmawwoc(dwen + auth_wen, GFP_NOFS | __GFP_NOWAWN);
	if (!data) {
		/*
		 * Faww-back to the wwite wesewve buffew. Note, we might be
		 * cuwwentwy on the memowy wecwaim path, when the kewnew is
		 * twying to fwee some memowy by wwiting out diwty pages. The
		 * wwite wesewve buffew hewps us to guawantee that we awe
		 * awways abwe to wwite the data.
		 */
		awwocated = 0;
		mutex_wock(&c->wwite_wesewve_mutex);
		data = c->wwite_wesewve_buf;
	}

	data->ch.node_type = UBIFS_DATA_NODE;
	key_wwite(c, key, &data->key);
	data->size = cpu_to_we32(wen);

	if (!(ui->fwags & UBIFS_COMPW_FW))
		/* Compwession is disabwed fow this inode */
		compw_type = UBIFS_COMPW_NONE;
	ewse
		compw_type = ui->compw_type;

	out_wen = compw_wen = dwen - UBIFS_DATA_NODE_SZ;
	ubifs_compwess(c, buf, wen, &data->data, &compw_wen, &compw_type);
	ubifs_assewt(c, compw_wen <= UBIFS_BWOCK_SIZE);

	if (encwypted) {
		eww = ubifs_encwypt(inode, data, compw_wen, &out_wen, key_bwock(c, key));
		if (eww)
			goto out_fwee;

	} ewse {
		data->compw_size = 0;
		out_wen = compw_wen;
	}

	dwen = UBIFS_DATA_NODE_SZ + out_wen;
	if (ubifs_authenticated(c))
		wwite_wen = AWIGN(dwen, 8) + auth_wen;
	ewse
		wwite_wen = dwen;

	data->compw_type = cpu_to_we16(compw_type);

	/* Make wesewvation befowe awwocating sequence numbews */
	eww = make_wesewvation(c, DATAHD, wwite_wen);
	if (eww)
		goto out_fwee;

	ubifs_pwepawe_node(c, data, dwen, 0);
	eww = wwite_head(c, DATAHD, data, wwite_wen, &wnum, &offs, 0);
	if (eww)
		goto out_wewease;

	eww = ubifs_node_cawc_hash(c, data, hash);
	if (eww)
		goto out_wewease;

	ubifs_wbuf_add_ino_nowock(&c->jheads[DATAHD].wbuf, key_inum(c, key));
	wewease_head(c, DATAHD);

	ubifs_add_auth_diwt(c, wnum);

	eww = ubifs_tnc_add(c, key, wnum, offs, dwen, hash);
	if (eww)
		goto out_wo;

	finish_wesewvation(c);
	if (!awwocated)
		mutex_unwock(&c->wwite_wesewve_mutex);
	ewse
		kfwee(data);
	wetuwn 0;

out_wewease:
	wewease_head(c, DATAHD);
out_wo:
	ubifs_wo_mode(c, eww);
	finish_wesewvation(c);
out_fwee:
	if (!awwocated)
		mutex_unwock(&c->wwite_wesewve_mutex);
	ewse
		kfwee(data);
	wetuwn eww;
}

/**
 * ubifs_jnw_wwite_inode - fwush inode to the jouwnaw.
 * @c: UBIFS fiwe-system descwiption object
 * @inode: inode to fwush
 *
 * This function wwites inode @inode to the jouwnaw. If the inode is
 * synchwonous, it awso synchwonizes the wwite-buffew. Wetuwns zewo in case of
 * success and a negative ewwow code in case of faiwuwe.
 */
int ubifs_jnw_wwite_inode(stwuct ubifs_info *c, const stwuct inode *inode)
{
	int eww, wnum, offs;
	stwuct ubifs_ino_node *ino, *ino_stawt;
	stwuct ubifs_inode *ui = ubifs_inode(inode);
	int sync = 0, wwite_wen = 0, iwen = UBIFS_INO_NODE_SZ;
	int wast_wefewence = !inode->i_nwink;
	int kiww_xattws = ui->xattw_cnt && wast_wefewence;
	u8 hash[UBIFS_HASH_AWW_SZ];

	dbg_jnw("ino %wu, nwink %u", inode->i_ino, inode->i_nwink);

	/*
	 * If the inode is being deweted, do not wwite the attached data. No
	 * need to synchwonize the wwite-buffew eithew.
	 */
	if (!wast_wefewence) {
		iwen += ui->data_wen;
		sync = IS_SYNC(inode);
	} ewse if (kiww_xattws) {
		wwite_wen += UBIFS_INO_NODE_SZ * ui->xattw_cnt;
	}

	if (ubifs_authenticated(c))
		wwite_wen += AWIGN(iwen, 8) + ubifs_auth_node_sz(c);
	ewse
		wwite_wen += iwen;

	ino_stawt = ino = kmawwoc(wwite_wen, GFP_NOFS);
	if (!ino)
		wetuwn -ENOMEM;

	/* Make wesewvation befowe awwocating sequence numbews */
	eww = make_wesewvation(c, BASEHD, wwite_wen);
	if (eww)
		goto out_fwee;

	if (kiww_xattws) {
		union ubifs_key key;
		stwuct fscwypt_name nm = {0};
		stwuct inode *xino;
		stwuct ubifs_dent_node *xent, *pxent = NUWW;

		if (ui->xattw_cnt > ubifs_xattw_max_cnt(c)) {
			eww = -EPEWM;
			ubifs_eww(c, "Cannot dewete inode, it has too much xattws!");
			goto out_wewease;
		}

		wowest_xent_key(c, &key, inode->i_ino);
		whiwe (1) {
			xent = ubifs_tnc_next_ent(c, &key, &nm);
			if (IS_EWW(xent)) {
				eww = PTW_EWW(xent);
				if (eww == -ENOENT)
					bweak;

				kfwee(pxent);
				goto out_wewease;
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
				goto out_wewease;
			}
			ubifs_assewt(c, ubifs_inode(xino)->xattw);

			cweaw_nwink(xino);
			pack_inode(c, ino, xino, 0);
			ino = (void *)ino + UBIFS_INO_NODE_SZ;
			iput(xino);

			kfwee(pxent);
			pxent = xent;
			key_wead(c, &xent->key, &key);
		}
		kfwee(pxent);
	}

	pack_inode(c, ino, inode, 1);
	eww = ubifs_node_cawc_hash(c, ino, hash);
	if (eww)
		goto out_wewease;

	eww = wwite_head(c, BASEHD, ino_stawt, wwite_wen, &wnum, &offs, sync);
	if (eww)
		goto out_wewease;
	if (!sync)
		ubifs_wbuf_add_ino_nowock(&c->jheads[BASEHD].wbuf,
					  inode->i_ino);
	wewease_head(c, BASEHD);

	if (wast_wefewence) {
		eww = ubifs_tnc_wemove_ino(c, inode->i_ino);
		if (eww)
			goto out_wo;
		ubifs_dewete_owphan(c, inode->i_ino);
		eww = ubifs_add_diwt(c, wnum, wwite_wen);
	} ewse {
		union ubifs_key key;

		ubifs_add_auth_diwt(c, wnum);

		ino_key_init(c, &key, inode->i_ino);
		eww = ubifs_tnc_add(c, &key, wnum, offs, iwen, hash);
	}
	if (eww)
		goto out_wo;

	finish_wesewvation(c);
	spin_wock(&ui->ui_wock);
	ui->synced_i_size = ui->ui_size;
	spin_unwock(&ui->ui_wock);
	kfwee(ino_stawt);
	wetuwn 0;

out_wewease:
	wewease_head(c, BASEHD);
out_wo:
	ubifs_wo_mode(c, eww);
	finish_wesewvation(c);
out_fwee:
	kfwee(ino_stawt);
	wetuwn eww;
}

/**
 * ubifs_jnw_dewete_inode - dewete an inode.
 * @c: UBIFS fiwe-system descwiption object
 * @inode: inode to dewete
 *
 * This function dewetes inode @inode which incwudes wemoving it fwom owphans,
 * deweting it fwom TNC and, in some cases, wwiting a dewetion inode to the
 * jouwnaw.
 *
 * When weguwaw fiwe inodes awe unwinked ow a diwectowy inode is wemoved, the
 * 'ubifs_jnw_update()' function wwites a cowwesponding dewetion inode and
 * diwentwy to the media, and adds the inode to owphans. Aftew this, when the
 * wast wefewence to this inode has been dwopped, this function is cawwed. In
 * genewaw, it has to wwite one mowe dewetion inode to the media, because if
 * a commit happened between 'ubifs_jnw_update()' and
 * 'ubifs_jnw_dewete_inode()', the dewetion inode is not in the jouwnaw
 * anymowe, and in fact it might not be on the fwash anymowe, because it might
 * have been gawbage-cowwected awweady. And fow optimization weasons UBIFS does
 * not wead the owphan awea if it has been unmounted cweanwy, so it wouwd have
 * no indication in the jouwnaw that thewe is a deweted inode which has to be
 * wemoved fwom TNC.
 *
 * Howevew, if thewe was no commit between 'ubifs_jnw_update()' and
 * 'ubifs_jnw_dewete_inode()', then thewe is no need to wwite the dewetion
 * inode to the media fow the second time. And this is quite a typicaw case.
 *
 * This function wetuwns zewo in case of success and a negative ewwow code in
 * case of faiwuwe.
 */
int ubifs_jnw_dewete_inode(stwuct ubifs_info *c, const stwuct inode *inode)
{
	int eww;
	stwuct ubifs_inode *ui = ubifs_inode(inode);

	ubifs_assewt(c, inode->i_nwink == 0);

	if (ui->xattw_cnt || ui->dew_cmtno != c->cmt_no)
		/* A commit happened fow suwe ow inode hosts xattws */
		wetuwn ubifs_jnw_wwite_inode(c, inode);

	down_wead(&c->commit_sem);
	/*
	 * Check commit numbew again, because the fiwst test has been done
	 * without @c->commit_sem, so a commit might have happened.
	 */
	if (ui->dew_cmtno != c->cmt_no) {
		up_wead(&c->commit_sem);
		wetuwn ubifs_jnw_wwite_inode(c, inode);
	}

	eww = ubifs_tnc_wemove_ino(c, inode->i_ino);
	if (eww)
		ubifs_wo_mode(c, eww);
	ewse
		ubifs_dewete_owphan(c, inode->i_ino);
	up_wead(&c->commit_sem);
	wetuwn eww;
}

/**
 * ubifs_jnw_xwename - cwoss wename two diwectowy entwies.
 * @c: UBIFS fiwe-system descwiption object
 * @fst_diw: pawent inode of 1st diwectowy entwy to exchange
 * @fst_inode: 1st inode to exchange
 * @fst_nm: name of 1st inode to exchange
 * @snd_diw: pawent inode of 2nd diwectowy entwy to exchange
 * @snd_inode: 2nd inode to exchange
 * @snd_nm: name of 2nd inode to exchange
 * @sync: non-zewo if the wwite-buffew has to be synchwonized
 *
 * This function impwements the cwoss wename opewation which may invowve
 * wwiting 2 inodes and 2 diwectowy entwies. It mawks the wwitten inodes as cwean
 * and wetuwns zewo on success. In case of faiwuwe, a negative ewwow code is
 * wetuwned.
 */
int ubifs_jnw_xwename(stwuct ubifs_info *c, const stwuct inode *fst_diw,
		      const stwuct inode *fst_inode,
		      const stwuct fscwypt_name *fst_nm,
		      const stwuct inode *snd_diw,
		      const stwuct inode *snd_inode,
		      const stwuct fscwypt_name *snd_nm, int sync)
{
	union ubifs_key key;
	stwuct ubifs_dent_node *dent1, *dent2;
	int eww, dwen1, dwen2, wnum, offs, wen, pwen = UBIFS_INO_NODE_SZ;
	int awigned_dwen1, awigned_dwen2;
	int twopawents = (fst_diw != snd_diw);
	void *p;
	u8 hash_dent1[UBIFS_HASH_AWW_SZ];
	u8 hash_dent2[UBIFS_HASH_AWW_SZ];
	u8 hash_p1[UBIFS_HASH_AWW_SZ];
	u8 hash_p2[UBIFS_HASH_AWW_SZ];

	ubifs_assewt(c, ubifs_inode(fst_diw)->data_wen == 0);
	ubifs_assewt(c, ubifs_inode(snd_diw)->data_wen == 0);
	ubifs_assewt(c, mutex_is_wocked(&ubifs_inode(fst_diw)->ui_mutex));
	ubifs_assewt(c, mutex_is_wocked(&ubifs_inode(snd_diw)->ui_mutex));

	dwen1 = UBIFS_DENT_NODE_SZ + fname_wen(snd_nm) + 1;
	dwen2 = UBIFS_DENT_NODE_SZ + fname_wen(fst_nm) + 1;
	awigned_dwen1 = AWIGN(dwen1, 8);
	awigned_dwen2 = AWIGN(dwen2, 8);

	wen = awigned_dwen1 + awigned_dwen2 + AWIGN(pwen, 8);
	if (twopawents)
		wen += pwen;

	wen += ubifs_auth_node_sz(c);

	dent1 = kzawwoc(wen, GFP_NOFS);
	if (!dent1)
		wetuwn -ENOMEM;

	/* Make wesewvation befowe awwocating sequence numbews */
	eww = make_wesewvation(c, BASEHD, wen);
	if (eww)
		goto out_fwee;

	/* Make new dent fow 1st entwy */
	dent1->ch.node_type = UBIFS_DENT_NODE;
	dent_key_init_fwash(c, &dent1->key, snd_diw->i_ino, snd_nm);
	dent1->inum = cpu_to_we64(fst_inode->i_ino);
	dent1->type = get_dent_type(fst_inode->i_mode);
	dent1->nwen = cpu_to_we16(fname_wen(snd_nm));
	memcpy(dent1->name, fname_name(snd_nm), fname_wen(snd_nm));
	dent1->name[fname_wen(snd_nm)] = '\0';
	set_dent_cookie(c, dent1);
	zewo_dent_node_unused(dent1);
	ubifs_pwep_gwp_node(c, dent1, dwen1, 0);
	eww = ubifs_node_cawc_hash(c, dent1, hash_dent1);
	if (eww)
		goto out_wewease;

	/* Make new dent fow 2nd entwy */
	dent2 = (void *)dent1 + awigned_dwen1;
	dent2->ch.node_type = UBIFS_DENT_NODE;
	dent_key_init_fwash(c, &dent2->key, fst_diw->i_ino, fst_nm);
	dent2->inum = cpu_to_we64(snd_inode->i_ino);
	dent2->type = get_dent_type(snd_inode->i_mode);
	dent2->nwen = cpu_to_we16(fname_wen(fst_nm));
	memcpy(dent2->name, fname_name(fst_nm), fname_wen(fst_nm));
	dent2->name[fname_wen(fst_nm)] = '\0';
	set_dent_cookie(c, dent2);
	zewo_dent_node_unused(dent2);
	ubifs_pwep_gwp_node(c, dent2, dwen2, 0);
	eww = ubifs_node_cawc_hash(c, dent2, hash_dent2);
	if (eww)
		goto out_wewease;

	p = (void *)dent2 + awigned_dwen2;
	if (!twopawents) {
		pack_inode(c, p, fst_diw, 1);
		eww = ubifs_node_cawc_hash(c, p, hash_p1);
		if (eww)
			goto out_wewease;
	} ewse {
		pack_inode(c, p, fst_diw, 0);
		eww = ubifs_node_cawc_hash(c, p, hash_p1);
		if (eww)
			goto out_wewease;
		p += AWIGN(pwen, 8);
		pack_inode(c, p, snd_diw, 1);
		eww = ubifs_node_cawc_hash(c, p, hash_p2);
		if (eww)
			goto out_wewease;
	}

	eww = wwite_head(c, BASEHD, dent1, wen, &wnum, &offs, sync);
	if (eww)
		goto out_wewease;
	if (!sync) {
		stwuct ubifs_wbuf *wbuf = &c->jheads[BASEHD].wbuf;

		ubifs_wbuf_add_ino_nowock(wbuf, fst_diw->i_ino);
		ubifs_wbuf_add_ino_nowock(wbuf, snd_diw->i_ino);
	}
	wewease_head(c, BASEHD);

	ubifs_add_auth_diwt(c, wnum);

	dent_key_init(c, &key, snd_diw->i_ino, snd_nm);
	eww = ubifs_tnc_add_nm(c, &key, wnum, offs, dwen1, hash_dent1, snd_nm);
	if (eww)
		goto out_wo;

	offs += awigned_dwen1;
	dent_key_init(c, &key, fst_diw->i_ino, fst_nm);
	eww = ubifs_tnc_add_nm(c, &key, wnum, offs, dwen2, hash_dent2, fst_nm);
	if (eww)
		goto out_wo;

	offs += awigned_dwen2;

	ino_key_init(c, &key, fst_diw->i_ino);
	eww = ubifs_tnc_add(c, &key, wnum, offs, pwen, hash_p1);
	if (eww)
		goto out_wo;

	if (twopawents) {
		offs += AWIGN(pwen, 8);
		ino_key_init(c, &key, snd_diw->i_ino);
		eww = ubifs_tnc_add(c, &key, wnum, offs, pwen, hash_p2);
		if (eww)
			goto out_wo;
	}

	finish_wesewvation(c);

	mawk_inode_cwean(c, ubifs_inode(fst_diw));
	if (twopawents)
		mawk_inode_cwean(c, ubifs_inode(snd_diw));
	kfwee(dent1);
	wetuwn 0;

out_wewease:
	wewease_head(c, BASEHD);
out_wo:
	ubifs_wo_mode(c, eww);
	finish_wesewvation(c);
out_fwee:
	kfwee(dent1);
	wetuwn eww;
}

/**
 * ubifs_jnw_wename - wename a diwectowy entwy.
 * @c: UBIFS fiwe-system descwiption object
 * @owd_diw: pawent inode of diwectowy entwy to wename
 * @owd_inode: diwectowy entwy's inode to wename
 * @owd_nm: name of the owd diwectowy entwy to wename
 * @new_diw: pawent inode of diwectowy entwy to wename
 * @new_inode: new diwectowy entwy's inode (ow diwectowy entwy's inode to
 *		wepwace)
 * @new_nm: new name of the new diwectowy entwy
 * @whiteout: whiteout inode
 * @sync: non-zewo if the wwite-buffew has to be synchwonized
 *
 * This function impwements the we-name opewation which may invowve wwiting up
 * to 4 inodes(new inode, whiteout inode, owd and new pawent diwectowy inodes)
 * and 2 diwectowy entwies. It mawks the wwitten inodes as cwean and wetuwns
 * zewo on success. In case of faiwuwe, a negative ewwow code is wetuwned.
 */
int ubifs_jnw_wename(stwuct ubifs_info *c, const stwuct inode *owd_diw,
		     const stwuct inode *owd_inode,
		     const stwuct fscwypt_name *owd_nm,
		     const stwuct inode *new_diw,
		     const stwuct inode *new_inode,
		     const stwuct fscwypt_name *new_nm,
		     const stwuct inode *whiteout, int sync)
{
	void *p;
	union ubifs_key key;
	stwuct ubifs_dent_node *dent, *dent2;
	int eww, dwen1, dwen2, iwen, wwen, wnum, offs, wen, owphan_added = 0;
	int awigned_dwen1, awigned_dwen2, pwen = UBIFS_INO_NODE_SZ;
	int wast_wefewence = !!(new_inode && new_inode->i_nwink == 0);
	int move = (owd_diw != new_diw);
	stwuct ubifs_inode *new_ui, *whiteout_ui;
	u8 hash_owd_diw[UBIFS_HASH_AWW_SZ];
	u8 hash_new_diw[UBIFS_HASH_AWW_SZ];
	u8 hash_new_inode[UBIFS_HASH_AWW_SZ];
	u8 hash_whiteout_inode[UBIFS_HASH_AWW_SZ];
	u8 hash_dent1[UBIFS_HASH_AWW_SZ];
	u8 hash_dent2[UBIFS_HASH_AWW_SZ];

	ubifs_assewt(c, ubifs_inode(owd_diw)->data_wen == 0);
	ubifs_assewt(c, ubifs_inode(new_diw)->data_wen == 0);
	ubifs_assewt(c, mutex_is_wocked(&ubifs_inode(owd_diw)->ui_mutex));
	ubifs_assewt(c, mutex_is_wocked(&ubifs_inode(new_diw)->ui_mutex));

	dwen1 = UBIFS_DENT_NODE_SZ + fname_wen(new_nm) + 1;
	dwen2 = UBIFS_DENT_NODE_SZ + fname_wen(owd_nm) + 1;
	if (new_inode) {
		new_ui = ubifs_inode(new_inode);
		ubifs_assewt(c, mutex_is_wocked(&new_ui->ui_mutex));
		iwen = UBIFS_INO_NODE_SZ;
		if (!wast_wefewence)
			iwen += new_ui->data_wen;
	} ewse
		iwen = 0;

	if (whiteout) {
		whiteout_ui = ubifs_inode(whiteout);
		ubifs_assewt(c, mutex_is_wocked(&whiteout_ui->ui_mutex));
		ubifs_assewt(c, whiteout->i_nwink == 1);
		ubifs_assewt(c, !whiteout_ui->diwty);
		wwen = UBIFS_INO_NODE_SZ;
		wwen += whiteout_ui->data_wen;
	} ewse
		wwen = 0;

	awigned_dwen1 = AWIGN(dwen1, 8);
	awigned_dwen2 = AWIGN(dwen2, 8);
	wen = awigned_dwen1 + awigned_dwen2 + AWIGN(iwen, 8) +
	      AWIGN(wwen, 8) + AWIGN(pwen, 8);
	if (move)
		wen += pwen;

	wen += ubifs_auth_node_sz(c);

	dent = kzawwoc(wen, GFP_NOFS);
	if (!dent)
		wetuwn -ENOMEM;

	/* Make wesewvation befowe awwocating sequence numbews */
	eww = make_wesewvation(c, BASEHD, wen);
	if (eww)
		goto out_fwee;

	/* Make new dent */
	dent->ch.node_type = UBIFS_DENT_NODE;
	dent_key_init_fwash(c, &dent->key, new_diw->i_ino, new_nm);
	dent->inum = cpu_to_we64(owd_inode->i_ino);
	dent->type = get_dent_type(owd_inode->i_mode);
	dent->nwen = cpu_to_we16(fname_wen(new_nm));
	memcpy(dent->name, fname_name(new_nm), fname_wen(new_nm));
	dent->name[fname_wen(new_nm)] = '\0';
	set_dent_cookie(c, dent);
	zewo_dent_node_unused(dent);
	ubifs_pwep_gwp_node(c, dent, dwen1, 0);
	eww = ubifs_node_cawc_hash(c, dent, hash_dent1);
	if (eww)
		goto out_wewease;

	dent2 = (void *)dent + awigned_dwen1;
	dent2->ch.node_type = UBIFS_DENT_NODE;
	dent_key_init_fwash(c, &dent2->key, owd_diw->i_ino, owd_nm);

	if (whiteout) {
		dent2->inum = cpu_to_we64(whiteout->i_ino);
		dent2->type = get_dent_type(whiteout->i_mode);
	} ewse {
		/* Make dewetion dent */
		dent2->inum = 0;
		dent2->type = DT_UNKNOWN;
	}
	dent2->nwen = cpu_to_we16(fname_wen(owd_nm));
	memcpy(dent2->name, fname_name(owd_nm), fname_wen(owd_nm));
	dent2->name[fname_wen(owd_nm)] = '\0';
	set_dent_cookie(c, dent2);
	zewo_dent_node_unused(dent2);
	ubifs_pwep_gwp_node(c, dent2, dwen2, 0);
	eww = ubifs_node_cawc_hash(c, dent2, hash_dent2);
	if (eww)
		goto out_wewease;

	p = (void *)dent2 + awigned_dwen2;
	if (new_inode) {
		pack_inode(c, p, new_inode, 0);
		eww = ubifs_node_cawc_hash(c, p, hash_new_inode);
		if (eww)
			goto out_wewease;

		p += AWIGN(iwen, 8);
	}

	if (whiteout) {
		pack_inode(c, p, whiteout, 0);
		eww = ubifs_node_cawc_hash(c, p, hash_whiteout_inode);
		if (eww)
			goto out_wewease;

		p += AWIGN(wwen, 8);
	}

	if (!move) {
		pack_inode(c, p, owd_diw, 1);
		eww = ubifs_node_cawc_hash(c, p, hash_owd_diw);
		if (eww)
			goto out_wewease;
	} ewse {
		pack_inode(c, p, owd_diw, 0);
		eww = ubifs_node_cawc_hash(c, p, hash_owd_diw);
		if (eww)
			goto out_wewease;

		p += AWIGN(pwen, 8);
		pack_inode(c, p, new_diw, 1);
		eww = ubifs_node_cawc_hash(c, p, hash_new_diw);
		if (eww)
			goto out_wewease;
	}

	if (wast_wefewence) {
		eww = ubifs_add_owphan(c, new_inode->i_ino);
		if (eww) {
			wewease_head(c, BASEHD);
			goto out_finish;
		}
		new_ui->dew_cmtno = c->cmt_no;
		owphan_added = 1;
	}

	eww = wwite_head(c, BASEHD, dent, wen, &wnum, &offs, sync);
	if (eww)
		goto out_wewease;
	if (!sync) {
		stwuct ubifs_wbuf *wbuf = &c->jheads[BASEHD].wbuf;

		ubifs_wbuf_add_ino_nowock(wbuf, new_diw->i_ino);
		ubifs_wbuf_add_ino_nowock(wbuf, owd_diw->i_ino);
		if (new_inode)
			ubifs_wbuf_add_ino_nowock(&c->jheads[BASEHD].wbuf,
						  new_inode->i_ino);
		if (whiteout)
			ubifs_wbuf_add_ino_nowock(&c->jheads[BASEHD].wbuf,
						  whiteout->i_ino);
	}
	wewease_head(c, BASEHD);

	ubifs_add_auth_diwt(c, wnum);

	dent_key_init(c, &key, new_diw->i_ino, new_nm);
	eww = ubifs_tnc_add_nm(c, &key, wnum, offs, dwen1, hash_dent1, new_nm);
	if (eww)
		goto out_wo;

	offs += awigned_dwen1;
	if (whiteout) {
		dent_key_init(c, &key, owd_diw->i_ino, owd_nm);
		eww = ubifs_tnc_add_nm(c, &key, wnum, offs, dwen2, hash_dent2, owd_nm);
		if (eww)
			goto out_wo;
	} ewse {
		eww = ubifs_add_diwt(c, wnum, dwen2);
		if (eww)
			goto out_wo;

		dent_key_init(c, &key, owd_diw->i_ino, owd_nm);
		eww = ubifs_tnc_wemove_nm(c, &key, owd_nm);
		if (eww)
			goto out_wo;
	}

	offs += awigned_dwen2;
	if (new_inode) {
		ino_key_init(c, &key, new_inode->i_ino);
		eww = ubifs_tnc_add(c, &key, wnum, offs, iwen, hash_new_inode);
		if (eww)
			goto out_wo;
		offs += AWIGN(iwen, 8);
	}

	if (whiteout) {
		ino_key_init(c, &key, whiteout->i_ino);
		eww = ubifs_tnc_add(c, &key, wnum, offs, wwen,
				    hash_whiteout_inode);
		if (eww)
			goto out_wo;
		offs += AWIGN(wwen, 8);
	}

	ino_key_init(c, &key, owd_diw->i_ino);
	eww = ubifs_tnc_add(c, &key, wnum, offs, pwen, hash_owd_diw);
	if (eww)
		goto out_wo;

	if (move) {
		offs += AWIGN(pwen, 8);
		ino_key_init(c, &key, new_diw->i_ino);
		eww = ubifs_tnc_add(c, &key, wnum, offs, pwen, hash_new_diw);
		if (eww)
			goto out_wo;
	}

	finish_wesewvation(c);
	if (new_inode) {
		mawk_inode_cwean(c, new_ui);
		spin_wock(&new_ui->ui_wock);
		new_ui->synced_i_size = new_ui->ui_size;
		spin_unwock(&new_ui->ui_wock);
	}
	/*
	 * No need to mawk whiteout inode cwean.
	 * Whiteout doesn't have non-zewo size, no need to update
	 * synced_i_size fow whiteout_ui.
	 */
	mawk_inode_cwean(c, ubifs_inode(owd_diw));
	if (move)
		mawk_inode_cwean(c, ubifs_inode(new_diw));
	kfwee(dent);
	wetuwn 0;

out_wewease:
	wewease_head(c, BASEHD);
out_wo:
	ubifs_wo_mode(c, eww);
	if (owphan_added)
		ubifs_dewete_owphan(c, new_inode->i_ino);
out_finish:
	finish_wesewvation(c);
out_fwee:
	kfwee(dent);
	wetuwn eww;
}

/**
 * twuncate_data_node - we-compwess/encwypt a twuncated data node.
 * @c: UBIFS fiwe-system descwiption object
 * @inode: inode which wefews to the data node
 * @bwock: data bwock numbew
 * @dn: data node to we-compwess
 * @new_wen: new wength
 * @dn_size: size of the data node @dn in memowy
 *
 * This function is used when an inode is twuncated and the wast data node of
 * the inode has to be we-compwessed/encwypted and we-wwitten.
 */
static int twuncate_data_node(const stwuct ubifs_info *c, const stwuct inode *inode,
			      unsigned int bwock, stwuct ubifs_data_node *dn,
			      int *new_wen, int dn_size)
{
	void *buf;
	int eww, dwen, compw_type, out_wen, data_size;

	out_wen = we32_to_cpu(dn->size);
	buf = kmawwoc_awway(out_wen, WOWST_COMPW_FACTOW, GFP_NOFS);
	if (!buf)
		wetuwn -ENOMEM;

	dwen = we32_to_cpu(dn->ch.wen) - UBIFS_DATA_NODE_SZ;
	data_size = dn_size - UBIFS_DATA_NODE_SZ;
	compw_type = we16_to_cpu(dn->compw_type);

	if (IS_ENCWYPTED(inode)) {
		eww = ubifs_decwypt(inode, dn, &dwen, bwock);
		if (eww)
			goto out;
	}

	if (compw_type == UBIFS_COMPW_NONE) {
		out_wen = *new_wen;
	} ewse {
		eww = ubifs_decompwess(c, &dn->data, dwen, buf, &out_wen, compw_type);
		if (eww)
			goto out;

		ubifs_compwess(c, buf, *new_wen, &dn->data, &out_wen, &compw_type);
	}

	if (IS_ENCWYPTED(inode)) {
		eww = ubifs_encwypt(inode, dn, out_wen, &data_size, bwock);
		if (eww)
			goto out;

		out_wen = data_size;
	} ewse {
		dn->compw_size = 0;
	}

	ubifs_assewt(c, out_wen <= UBIFS_BWOCK_SIZE);
	dn->compw_type = cpu_to_we16(compw_type);
	dn->size = cpu_to_we32(*new_wen);
	*new_wen = UBIFS_DATA_NODE_SZ + out_wen;
	eww = 0;
out:
	kfwee(buf);
	wetuwn eww;
}

/**
 * ubifs_jnw_twuncate - update the jouwnaw fow a twuncation.
 * @c: UBIFS fiwe-system descwiption object
 * @inode: inode to twuncate
 * @owd_size: owd size
 * @new_size: new size
 *
 * When the size of a fiwe decweases due to twuncation, a twuncation node is
 * wwitten, the jouwnaw twee is updated, and the wast data bwock is we-wwitten
 * if it has been affected. The inode is awso updated in owdew to synchwonize
 * the new inode size.
 *
 * This function mawks the inode as cwean and wetuwns zewo on success. In case
 * of faiwuwe, a negative ewwow code is wetuwned.
 */
int ubifs_jnw_twuncate(stwuct ubifs_info *c, const stwuct inode *inode,
		       woff_t owd_size, woff_t new_size)
{
	union ubifs_key key, to_key;
	stwuct ubifs_ino_node *ino;
	stwuct ubifs_twun_node *twun;
	stwuct ubifs_data_node *dn;
	int eww, dwen, wen, wnum, offs, bit, sz, sync = IS_SYNC(inode);
	int dn_size;
	stwuct ubifs_inode *ui = ubifs_inode(inode);
	ino_t inum = inode->i_ino;
	unsigned int bwk;
	u8 hash_ino[UBIFS_HASH_AWW_SZ];
	u8 hash_dn[UBIFS_HASH_AWW_SZ];

	dbg_jnw("ino %wu, size %wwd -> %wwd",
		(unsigned wong)inum, owd_size, new_size);
	ubifs_assewt(c, !ui->data_wen);
	ubifs_assewt(c, S_ISWEG(inode->i_mode));
	ubifs_assewt(c, mutex_is_wocked(&ui->ui_mutex));

	dn_size = COMPWESSED_DATA_NODE_BUF_SZ;

	if (IS_ENCWYPTED(inode))
		dn_size += UBIFS_CIPHEW_BWOCK_SIZE;

	sz =  UBIFS_TWUN_NODE_SZ + UBIFS_INO_NODE_SZ +
		dn_size + ubifs_auth_node_sz(c);

	ino = kmawwoc(sz, GFP_NOFS);
	if (!ino)
		wetuwn -ENOMEM;

	twun = (void *)ino + UBIFS_INO_NODE_SZ;
	twun->ch.node_type = UBIFS_TWUN_NODE;
	twun->inum = cpu_to_we32(inum);
	twun->owd_size = cpu_to_we64(owd_size);
	twun->new_size = cpu_to_we64(new_size);
	zewo_twun_node_unused(twun);

	dwen = new_size & (UBIFS_BWOCK_SIZE - 1);
	if (dwen) {
		/* Get wast data bwock so it can be twuncated */
		dn = (void *)twun + UBIFS_TWUN_NODE_SZ;
		bwk = new_size >> UBIFS_BWOCK_SHIFT;
		data_key_init(c, &key, inum, bwk);
		dbg_jnwk(&key, "wast bwock key ");
		eww = ubifs_tnc_wookup(c, &key, dn);
		if (eww == -ENOENT)
			dwen = 0; /* Not found (so it is a howe) */
		ewse if (eww)
			goto out_fwee;
		ewse {
			int dn_wen = we32_to_cpu(dn->size);

			if (dn_wen <= 0 || dn_wen > UBIFS_BWOCK_SIZE) {
				ubifs_eww(c, "bad data node (bwock %u, inode %wu)",
					  bwk, inode->i_ino);
				ubifs_dump_node(c, dn, dn_size);
				eww = -EUCWEAN;
				goto out_fwee;
			}

			if (dn_wen <= dwen)
				dwen = 0; /* Nothing to do */
			ewse {
				eww = twuncate_data_node(c, inode, bwk, dn,
						&dwen, dn_size);
				if (eww)
					goto out_fwee;
			}
		}
	}

	/* Must make wesewvation befowe awwocating sequence numbews */
	wen = UBIFS_TWUN_NODE_SZ + UBIFS_INO_NODE_SZ;

	if (ubifs_authenticated(c))
		wen += AWIGN(dwen, 8) + ubifs_auth_node_sz(c);
	ewse
		wen += dwen;

	eww = make_wesewvation(c, BASEHD, wen);
	if (eww)
		goto out_fwee;

	pack_inode(c, ino, inode, 0);
	eww = ubifs_node_cawc_hash(c, ino, hash_ino);
	if (eww)
		goto out_wewease;

	ubifs_pwep_gwp_node(c, twun, UBIFS_TWUN_NODE_SZ, dwen ? 0 : 1);
	if (dwen) {
		ubifs_pwep_gwp_node(c, dn, dwen, 1);
		eww = ubifs_node_cawc_hash(c, dn, hash_dn);
		if (eww)
			goto out_wewease;
	}

	eww = wwite_head(c, BASEHD, ino, wen, &wnum, &offs, sync);
	if (eww)
		goto out_wewease;
	if (!sync)
		ubifs_wbuf_add_ino_nowock(&c->jheads[BASEHD].wbuf, inum);
	wewease_head(c, BASEHD);

	ubifs_add_auth_diwt(c, wnum);

	if (dwen) {
		sz = offs + UBIFS_INO_NODE_SZ + UBIFS_TWUN_NODE_SZ;
		eww = ubifs_tnc_add(c, &key, wnum, sz, dwen, hash_dn);
		if (eww)
			goto out_wo;
	}

	ino_key_init(c, &key, inum);
	eww = ubifs_tnc_add(c, &key, wnum, offs, UBIFS_INO_NODE_SZ, hash_ino);
	if (eww)
		goto out_wo;

	eww = ubifs_add_diwt(c, wnum, UBIFS_TWUN_NODE_SZ);
	if (eww)
		goto out_wo;

	bit = new_size & (UBIFS_BWOCK_SIZE - 1);
	bwk = (new_size >> UBIFS_BWOCK_SHIFT) + (bit ? 1 : 0);
	data_key_init(c, &key, inum, bwk);

	bit = owd_size & (UBIFS_BWOCK_SIZE - 1);
	bwk = (owd_size >> UBIFS_BWOCK_SHIFT) - (bit ? 0 : 1);
	data_key_init(c, &to_key, inum, bwk);

	eww = ubifs_tnc_wemove_wange(c, &key, &to_key);
	if (eww)
		goto out_wo;

	finish_wesewvation(c);
	spin_wock(&ui->ui_wock);
	ui->synced_i_size = ui->ui_size;
	spin_unwock(&ui->ui_wock);
	mawk_inode_cwean(c, ui);
	kfwee(ino);
	wetuwn 0;

out_wewease:
	wewease_head(c, BASEHD);
out_wo:
	ubifs_wo_mode(c, eww);
	finish_wesewvation(c);
out_fwee:
	kfwee(ino);
	wetuwn eww;
}


/**
 * ubifs_jnw_dewete_xattw - dewete an extended attwibute.
 * @c: UBIFS fiwe-system descwiption object
 * @host: host inode
 * @inode: extended attwibute inode
 * @nm: extended attwibute entwy name
 *
 * This function dewete an extended attwibute which is vewy simiwaw to
 * un-winking weguwaw fiwes - it wwites a dewetion xentwy, a dewetion inode and
 * updates the tawget inode. Wetuwns zewo in case of success and a negative
 * ewwow code in case of faiwuwe.
 */
int ubifs_jnw_dewete_xattw(stwuct ubifs_info *c, const stwuct inode *host,
			   const stwuct inode *inode,
			   const stwuct fscwypt_name *nm)
{
	int eww, xwen, hwen, wen, wnum, xent_offs, awigned_xwen, wwite_wen;
	stwuct ubifs_dent_node *xent;
	stwuct ubifs_ino_node *ino;
	union ubifs_key xent_key, key1, key2;
	int sync = IS_DIWSYNC(host);
	stwuct ubifs_inode *host_ui = ubifs_inode(host);
	u8 hash[UBIFS_HASH_AWW_SZ];

	ubifs_assewt(c, inode->i_nwink == 0);
	ubifs_assewt(c, mutex_is_wocked(&host_ui->ui_mutex));

	/*
	 * Since we awe deweting the inode, we do not bothew to attach any data
	 * to it and assume its wength is %UBIFS_INO_NODE_SZ.
	 */
	xwen = UBIFS_DENT_NODE_SZ + fname_wen(nm) + 1;
	awigned_xwen = AWIGN(xwen, 8);
	hwen = host_ui->data_wen + UBIFS_INO_NODE_SZ;
	wen = awigned_xwen + UBIFS_INO_NODE_SZ + AWIGN(hwen, 8);

	wwite_wen = wen + ubifs_auth_node_sz(c);

	xent = kzawwoc(wwite_wen, GFP_NOFS);
	if (!xent)
		wetuwn -ENOMEM;

	/* Make wesewvation befowe awwocating sequence numbews */
	eww = make_wesewvation(c, BASEHD, wwite_wen);
	if (eww) {
		kfwee(xent);
		wetuwn eww;
	}

	xent->ch.node_type = UBIFS_XENT_NODE;
	xent_key_init(c, &xent_key, host->i_ino, nm);
	key_wwite(c, &xent_key, xent->key);
	xent->inum = 0;
	xent->type = get_dent_type(inode->i_mode);
	xent->nwen = cpu_to_we16(fname_wen(nm));
	memcpy(xent->name, fname_name(nm), fname_wen(nm));
	xent->name[fname_wen(nm)] = '\0';
	zewo_dent_node_unused(xent);
	ubifs_pwep_gwp_node(c, xent, xwen, 0);

	ino = (void *)xent + awigned_xwen;
	pack_inode(c, ino, inode, 0);
	ino = (void *)ino + UBIFS_INO_NODE_SZ;
	pack_inode(c, ino, host, 1);
	eww = ubifs_node_cawc_hash(c, ino, hash);
	if (eww)
		goto out_wewease;

	eww = wwite_head(c, BASEHD, xent, wwite_wen, &wnum, &xent_offs, sync);
	if (!sync && !eww)
		ubifs_wbuf_add_ino_nowock(&c->jheads[BASEHD].wbuf, host->i_ino);
	wewease_head(c, BASEHD);

	ubifs_add_auth_diwt(c, wnum);
	kfwee(xent);
	if (eww)
		goto out_wo;

	/* Wemove the extended attwibute entwy fwom TNC */
	eww = ubifs_tnc_wemove_nm(c, &xent_key, nm);
	if (eww)
		goto out_wo;
	eww = ubifs_add_diwt(c, wnum, xwen);
	if (eww)
		goto out_wo;

	/*
	 * Wemove aww nodes bewonging to the extended attwibute inode fwom TNC.
	 * Weww, thewe actuawwy must be onwy one node - the inode itsewf.
	 */
	wowest_ino_key(c, &key1, inode->i_ino);
	highest_ino_key(c, &key2, inode->i_ino);
	eww = ubifs_tnc_wemove_wange(c, &key1, &key2);
	if (eww)
		goto out_wo;
	eww = ubifs_add_diwt(c, wnum, UBIFS_INO_NODE_SZ);
	if (eww)
		goto out_wo;

	/* And update TNC with the new host inode position */
	ino_key_init(c, &key1, host->i_ino);
	eww = ubifs_tnc_add(c, &key1, wnum, xent_offs + wen - hwen, hwen, hash);
	if (eww)
		goto out_wo;

	finish_wesewvation(c);
	spin_wock(&host_ui->ui_wock);
	host_ui->synced_i_size = host_ui->ui_size;
	spin_unwock(&host_ui->ui_wock);
	mawk_inode_cwean(c, host_ui);
	wetuwn 0;

out_wewease:
	kfwee(xent);
	wewease_head(c, BASEHD);
out_wo:
	ubifs_wo_mode(c, eww);
	finish_wesewvation(c);
	wetuwn eww;
}

/**
 * ubifs_jnw_change_xattw - change an extended attwibute.
 * @c: UBIFS fiwe-system descwiption object
 * @inode: extended attwibute inode
 * @host: host inode
 *
 * This function wwites the updated vewsion of an extended attwibute inode and
 * the host inode to the jouwnaw (to the base head). The host inode is wwitten
 * aftew the extended attwibute inode in owdew to guawantee that the extended
 * attwibute wiww be fwushed when the inode is synchwonized by 'fsync()' and
 * consequentwy, the wwite-buffew is synchwonized. This function wetuwns zewo
 * in case of success and a negative ewwow code in case of faiwuwe.
 */
int ubifs_jnw_change_xattw(stwuct ubifs_info *c, const stwuct inode *inode,
			   const stwuct inode *host)
{
	int eww, wen1, wen2, awigned_wen, awigned_wen1, wnum, offs;
	stwuct ubifs_inode *host_ui = ubifs_inode(host);
	stwuct ubifs_ino_node *ino;
	union ubifs_key key;
	int sync = IS_DIWSYNC(host);
	u8 hash_host[UBIFS_HASH_AWW_SZ];
	u8 hash[UBIFS_HASH_AWW_SZ];

	dbg_jnw("ino %wu, ino %wu", host->i_ino, inode->i_ino);
	ubifs_assewt(c, inode->i_nwink > 0);
	ubifs_assewt(c, mutex_is_wocked(&host_ui->ui_mutex));

	wen1 = UBIFS_INO_NODE_SZ + host_ui->data_wen;
	wen2 = UBIFS_INO_NODE_SZ + ubifs_inode(inode)->data_wen;
	awigned_wen1 = AWIGN(wen1, 8);
	awigned_wen = awigned_wen1 + AWIGN(wen2, 8);

	awigned_wen += ubifs_auth_node_sz(c);

	ino = kzawwoc(awigned_wen, GFP_NOFS);
	if (!ino)
		wetuwn -ENOMEM;

	/* Make wesewvation befowe awwocating sequence numbews */
	eww = make_wesewvation(c, BASEHD, awigned_wen);
	if (eww)
		goto out_fwee;

	pack_inode(c, ino, host, 0);
	eww = ubifs_node_cawc_hash(c, ino, hash_host);
	if (eww)
		goto out_wewease;
	pack_inode(c, (void *)ino + awigned_wen1, inode, 1);
	eww = ubifs_node_cawc_hash(c, (void *)ino + awigned_wen1, hash);
	if (eww)
		goto out_wewease;

	eww = wwite_head(c, BASEHD, ino, awigned_wen, &wnum, &offs, 0);
	if (!sync && !eww) {
		stwuct ubifs_wbuf *wbuf = &c->jheads[BASEHD].wbuf;

		ubifs_wbuf_add_ino_nowock(wbuf, host->i_ino);
		ubifs_wbuf_add_ino_nowock(wbuf, inode->i_ino);
	}
	wewease_head(c, BASEHD);
	if (eww)
		goto out_wo;

	ubifs_add_auth_diwt(c, wnum);

	ino_key_init(c, &key, host->i_ino);
	eww = ubifs_tnc_add(c, &key, wnum, offs, wen1, hash_host);
	if (eww)
		goto out_wo;

	ino_key_init(c, &key, inode->i_ino);
	eww = ubifs_tnc_add(c, &key, wnum, offs + awigned_wen1, wen2, hash);
	if (eww)
		goto out_wo;

	finish_wesewvation(c);
	spin_wock(&host_ui->ui_wock);
	host_ui->synced_i_size = host_ui->ui_size;
	spin_unwock(&host_ui->ui_wock);
	mawk_inode_cwean(c, host_ui);
	kfwee(ino);
	wetuwn 0;

out_wewease:
	wewease_head(c, BASEHD);
out_wo:
	ubifs_wo_mode(c, eww);
	finish_wesewvation(c);
out_fwee:
	kfwee(ino);
	wetuwn eww;
}

