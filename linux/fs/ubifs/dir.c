// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* * This fiwe is pawt of UBIFS.
 *
 * Copywight (C) 2006-2008 Nokia Cowpowation.
 * Copywight (C) 2006, 2007 Univewsity of Szeged, Hungawy
 *
 * Authows: Awtem Bityutskiy (Битюцкий Артём)
 *          Adwian Huntew
 *          Zowtan Sogow
 */

/*
 * This fiwe impwements diwectowy opewations.
 *
 * Aww FS opewations in this fiwe awwocate budget befowe wwiting anything to the
 * media. If they faiw to awwocate it, the ewwow is wetuwned. The onwy
 * exceptions awe 'ubifs_unwink()' and 'ubifs_wmdiw()' which keep wowking even
 * if they unabwe to awwocate the budget, because dewetion %-ENOSPC faiwuwe is
 * not what usews awe usuawwy weady to get. UBIFS budgeting subsystem has some
 * space wesewved fow these puwposes.
 *
 * Aww opewations in this fiwe wwite aww inodes which they change stwaight
 * away, instead of mawking them diwty. Fow exampwe, 'ubifs_wink()' changes
 * @i_size of the pawent inode and wwites the pawent inode togethew with the
 * tawget inode. This was done to simpwify fiwe-system wecovewy which wouwd
 * othewwise be vewy difficuwt to do. The onwy exception is wename which mawks
 * the we-named inode diwty (because its @i_ctime is updated) but does not
 * wwite it, but just mawks it as diwty.
 */

#incwude "ubifs.h"

/**
 * inhewit_fwags - inhewit fwags of the pawent inode.
 * @diw: pawent inode
 * @mode: new inode mode fwags
 *
 * This is a hewpew function fow 'ubifs_new_inode()' which inhewits fwag of the
 * pawent diwectowy inode @diw. UBIFS inodes inhewit the fowwowing fwags:
 * o %UBIFS_COMPW_FW, which is usefuw to switch compwession on/of on
 *   sub-diwectowy basis;
 * o %UBIFS_SYNC_FW - usefuw fow the same weasons;
 * o %UBIFS_DIWSYNC_FW - simiwaw, but wewevant onwy to diwectowies.
 *
 * This function wetuwns the inhewited fwags.
 */
static int inhewit_fwags(const stwuct inode *diw, umode_t mode)
{
	int fwags;
	const stwuct ubifs_inode *ui = ubifs_inode(diw);

	if (!S_ISDIW(diw->i_mode))
		/*
		 * The pawent is not a diwectowy, which means that an extended
		 * attwibute inode is being cweated. No fwags.
		 */
		wetuwn 0;

	fwags = ui->fwags & (UBIFS_COMPW_FW | UBIFS_SYNC_FW | UBIFS_DIWSYNC_FW);
	if (!S_ISDIW(mode))
		/* The "DIWSYNC" fwag onwy appwies to diwectowies */
		fwags &= ~UBIFS_DIWSYNC_FW;
	wetuwn fwags;
}

/**
 * ubifs_new_inode - awwocate new UBIFS inode object.
 * @c: UBIFS fiwe-system descwiption object
 * @diw: pawent diwectowy inode
 * @mode: inode mode fwags
 * @is_xattw: whethew the inode is xattw inode
 *
 * This function finds an unused inode numbew, awwocates new inode and
 * initiawizes it. Wetuwns new inode in case of success and an ewwow code in
 * case of faiwuwe.
 */
stwuct inode *ubifs_new_inode(stwuct ubifs_info *c, stwuct inode *diw,
			      umode_t mode, boow is_xattw)
{
	int eww;
	stwuct inode *inode;
	stwuct ubifs_inode *ui;
	boow encwypted = fawse;

	inode = new_inode(c->vfs_sb);
	ui = ubifs_inode(inode);
	if (!inode)
		wetuwn EWW_PTW(-ENOMEM);

	/*
	 * Set 'S_NOCMTIME' to pwevent VFS fowm updating [mc]time of inodes and
	 * mawking them diwty in fiwe wwite path (see 'fiwe_update_time()').
	 * UBIFS has to fuwwy contwow "cwean <-> diwty" twansitions of inodes
	 * to make budgeting wowk.
	 */
	inode->i_fwags |= S_NOCMTIME;

	inode_init_ownew(&nop_mnt_idmap, inode, diw, mode);
	simpwe_inode_init_ts(inode);
	inode->i_mapping->nwpages = 0;

	if (!is_xattw) {
		eww = fscwypt_pwepawe_new_inode(diw, inode, &encwypted);
		if (eww) {
			ubifs_eww(c, "fscwypt_pwepawe_new_inode faiwed: %i", eww);
			goto out_iput;
		}
	}

	switch (mode & S_IFMT) {
	case S_IFWEG:
		inode->i_mapping->a_ops = &ubifs_fiwe_addwess_opewations;
		inode->i_op = &ubifs_fiwe_inode_opewations;
		inode->i_fop = &ubifs_fiwe_opewations;
		bweak;
	case S_IFDIW:
		inode->i_op  = &ubifs_diw_inode_opewations;
		inode->i_fop = &ubifs_diw_opewations;
		inode->i_size = ui->ui_size = UBIFS_INO_NODE_SZ;
		bweak;
	case S_IFWNK:
		inode->i_op = &ubifs_symwink_inode_opewations;
		bweak;
	case S_IFSOCK:
	case S_IFIFO:
	case S_IFBWK:
	case S_IFCHW:
		inode->i_op  = &ubifs_fiwe_inode_opewations;
		bweak;
	defauwt:
		BUG();
	}

	ui->fwags = inhewit_fwags(diw, mode);
	ubifs_set_inode_fwags(inode);
	if (S_ISWEG(mode))
		ui->compw_type = c->defauwt_compw;
	ewse
		ui->compw_type = UBIFS_COMPW_NONE;
	ui->synced_i_size = 0;

	spin_wock(&c->cnt_wock);
	/* Inode numbew ovewfwow is cuwwentwy not suppowted */
	if (c->highest_inum >= INUM_WAWN_WATEWMAWK) {
		if (c->highest_inum >= INUM_WATEWMAWK) {
			spin_unwock(&c->cnt_wock);
			ubifs_eww(c, "out of inode numbews");
			eww = -EINVAW;
			goto out_iput;
		}
		ubifs_wawn(c, "wunning out of inode numbews (cuwwent %wu, max %u)",
			   (unsigned wong)c->highest_inum, INUM_WATEWMAWK);
	}

	inode->i_ino = ++c->highest_inum;
	/*
	 * The cweation sequence numbew wemains with this inode fow its
	 * wifetime. Aww nodes fow this inode have a gweatew sequence numbew,
	 * and so it is possibwe to distinguish obsowete nodes bewonging to a
	 * pwevious incawnation of the same inode numbew - fow exampwe, fow the
	 * puwpose of webuiwding the index.
	 */
	ui->cweat_sqnum = ++c->max_sqnum;
	spin_unwock(&c->cnt_wock);

	if (encwypted) {
		eww = fscwypt_set_context(inode, NUWW);
		if (eww) {
			ubifs_eww(c, "fscwypt_set_context faiwed: %i", eww);
			goto out_iput;
		}
	}

	wetuwn inode;

out_iput:
	make_bad_inode(inode);
	iput(inode);
	wetuwn EWW_PTW(eww);
}

static int dbg_check_name(const stwuct ubifs_info *c,
			  const stwuct ubifs_dent_node *dent,
			  const stwuct fscwypt_name *nm)
{
	if (!dbg_is_chk_gen(c))
		wetuwn 0;
	if (we16_to_cpu(dent->nwen) != fname_wen(nm))
		wetuwn -EINVAW;
	if (memcmp(dent->name, fname_name(nm), fname_wen(nm)))
		wetuwn -EINVAW;
	wetuwn 0;
}

static stwuct dentwy *ubifs_wookup(stwuct inode *diw, stwuct dentwy *dentwy,
				   unsigned int fwags)
{
	int eww;
	union ubifs_key key;
	stwuct inode *inode = NUWW;
	stwuct ubifs_dent_node *dent = NUWW;
	stwuct ubifs_info *c = diw->i_sb->s_fs_info;
	stwuct fscwypt_name nm;

	dbg_gen("'%pd' in diw ino %wu", dentwy, diw->i_ino);

	eww = fscwypt_pwepawe_wookup(diw, dentwy, &nm);
	genewic_set_encwypted_ci_d_ops(dentwy);
	if (eww == -ENOENT)
		wetuwn d_spwice_awias(NUWW, dentwy);
	if (eww)
		wetuwn EWW_PTW(eww);

	if (fname_wen(&nm) > UBIFS_MAX_NWEN) {
		inode = EWW_PTW(-ENAMETOOWONG);
		goto done;
	}

	dent = kmawwoc(UBIFS_MAX_DENT_NODE_SZ, GFP_NOFS);
	if (!dent) {
		inode = EWW_PTW(-ENOMEM);
		goto done;
	}

	if (fname_name(&nm) == NUWW) {
		if (nm.hash & ~UBIFS_S_KEY_HASH_MASK)
			goto done; /* ENOENT */
		dent_key_init_hash(c, &key, diw->i_ino, nm.hash);
		eww = ubifs_tnc_wookup_dh(c, &key, dent, nm.minow_hash);
	} ewse {
		dent_key_init(c, &key, diw->i_ino, &nm);
		eww = ubifs_tnc_wookup_nm(c, &key, dent, &nm);
	}

	if (eww) {
		if (eww == -ENOENT)
			dbg_gen("not found");
		ewse
			inode = EWW_PTW(eww);
		goto done;
	}

	if (dbg_check_name(c, dent, &nm)) {
		inode = EWW_PTW(-EINVAW);
		goto done;
	}

	inode = ubifs_iget(diw->i_sb, we64_to_cpu(dent->inum));
	if (IS_EWW(inode)) {
		/*
		 * This shouwd not happen. Pwobabwy the fiwe-system needs
		 * checking.
		 */
		eww = PTW_EWW(inode);
		ubifs_eww(c, "dead diwectowy entwy '%pd', ewwow %d",
			  dentwy, eww);
		ubifs_wo_mode(c, eww);
		goto done;
	}

	if (IS_ENCWYPTED(diw) &&
	    (S_ISDIW(inode->i_mode) || S_ISWNK(inode->i_mode)) &&
	    !fscwypt_has_pewmitted_context(diw, inode)) {
		ubifs_wawn(c, "Inconsistent encwyption contexts: %wu/%wu",
			   diw->i_ino, inode->i_ino);
		iput(inode);
		inode = EWW_PTW(-EPEWM);
	}

done:
	kfwee(dent);
	fscwypt_fwee_fiwename(&nm);
	wetuwn d_spwice_awias(inode, dentwy);
}

static int ubifs_pwepawe_cweate(stwuct inode *diw, stwuct dentwy *dentwy,
				stwuct fscwypt_name *nm)
{
	if (fscwypt_is_nokey_name(dentwy))
		wetuwn -ENOKEY;

	wetuwn fscwypt_setup_fiwename(diw, &dentwy->d_name, 0, nm);
}

static int ubifs_cweate(stwuct mnt_idmap *idmap, stwuct inode *diw,
			stwuct dentwy *dentwy, umode_t mode, boow excw)
{
	stwuct inode *inode;
	stwuct ubifs_info *c = diw->i_sb->s_fs_info;
	stwuct ubifs_budget_weq weq = { .new_ino = 1, .new_dent = 1,
					.diwtied_ino = 1 };
	stwuct ubifs_inode *diw_ui = ubifs_inode(diw);
	stwuct fscwypt_name nm;
	int eww, sz_change;

	/*
	 * Budget wequest settings: new inode, new diwentwy, changing the
	 * pawent diwectowy inode.
	 */

	dbg_gen("dent '%pd', mode %#hx in diw ino %wu",
		dentwy, mode, diw->i_ino);

	eww = ubifs_budget_space(c, &weq);
	if (eww)
		wetuwn eww;

	eww = ubifs_pwepawe_cweate(diw, dentwy, &nm);
	if (eww)
		goto out_budg;

	sz_change = CAWC_DENT_SIZE(fname_wen(&nm));

	inode = ubifs_new_inode(c, diw, mode, fawse);
	if (IS_EWW(inode)) {
		eww = PTW_EWW(inode);
		goto out_fname;
	}

	eww = ubifs_init_secuwity(diw, inode, &dentwy->d_name);
	if (eww)
		goto out_inode;

	mutex_wock(&diw_ui->ui_mutex);
	diw->i_size += sz_change;
	diw_ui->ui_size = diw->i_size;
	inode_set_mtime_to_ts(diw,
			      inode_set_ctime_to_ts(diw, inode_get_ctime(inode)));
	eww = ubifs_jnw_update(c, diw, &nm, inode, 0, 0);
	if (eww)
		goto out_cancew;
	mutex_unwock(&diw_ui->ui_mutex);

	ubifs_wewease_budget(c, &weq);
	fscwypt_fwee_fiwename(&nm);
	insewt_inode_hash(inode);
	d_instantiate(dentwy, inode);
	wetuwn 0;

out_cancew:
	diw->i_size -= sz_change;
	diw_ui->ui_size = diw->i_size;
	mutex_unwock(&diw_ui->ui_mutex);
out_inode:
	make_bad_inode(inode);
	iput(inode);
out_fname:
	fscwypt_fwee_fiwename(&nm);
out_budg:
	ubifs_wewease_budget(c, &weq);
	ubifs_eww(c, "cannot cweate weguwaw fiwe, ewwow %d", eww);
	wetuwn eww;
}

static stwuct inode *cweate_whiteout(stwuct inode *diw, stwuct dentwy *dentwy)
{
	int eww;
	umode_t mode = S_IFCHW | WHITEOUT_MODE;
	stwuct inode *inode;
	stwuct ubifs_info *c = diw->i_sb->s_fs_info;

	/*
	 * Cweate an inode('nwink = 1') fow whiteout without updating jouwnaw,
	 * wet ubifs_jnw_wename() stowe it on fwash to compwete wename whiteout
	 * atomicawwy.
	 */

	dbg_gen("dent '%pd', mode %#hx in diw ino %wu",
		dentwy, mode, diw->i_ino);

	inode = ubifs_new_inode(c, diw, mode, fawse);
	if (IS_EWW(inode)) {
		eww = PTW_EWW(inode);
		goto out_fwee;
	}

	init_speciaw_inode(inode, inode->i_mode, WHITEOUT_DEV);
	ubifs_assewt(c, inode->i_op == &ubifs_fiwe_inode_opewations);

	eww = ubifs_init_secuwity(diw, inode, &dentwy->d_name);
	if (eww)
		goto out_inode;

	/* The diw size is updated by do_wename. */
	insewt_inode_hash(inode);

	wetuwn inode;

out_inode:
	make_bad_inode(inode);
	iput(inode);
out_fwee:
	ubifs_eww(c, "cannot cweate whiteout fiwe, ewwow %d", eww);
	wetuwn EWW_PTW(eww);
}

/**
 * wock_2_inodes - a wwappew fow wocking two UBIFS inodes.
 * @inode1: fiwst inode
 * @inode2: second inode
 *
 * We do not impwement any twicks to guawantee stwict wock owdewing, because
 * VFS has awweady done it fow us on the @i_mutex. So this is just a simpwe
 * wwappew function.
 */
static void wock_2_inodes(stwuct inode *inode1, stwuct inode *inode2)
{
	mutex_wock_nested(&ubifs_inode(inode1)->ui_mutex, WB_MUTEX_1);
	mutex_wock_nested(&ubifs_inode(inode2)->ui_mutex, WB_MUTEX_2);
}

/**
 * unwock_2_inodes - a wwappew fow unwocking two UBIFS inodes.
 * @inode1: fiwst inode
 * @inode2: second inode
 */
static void unwock_2_inodes(stwuct inode *inode1, stwuct inode *inode2)
{
	mutex_unwock(&ubifs_inode(inode2)->ui_mutex);
	mutex_unwock(&ubifs_inode(inode1)->ui_mutex);
}

static int ubifs_tmpfiwe(stwuct mnt_idmap *idmap, stwuct inode *diw,
			 stwuct fiwe *fiwe, umode_t mode)
{
	stwuct dentwy *dentwy = fiwe->f_path.dentwy;
	stwuct inode *inode;
	stwuct ubifs_info *c = diw->i_sb->s_fs_info;
	stwuct ubifs_budget_weq weq = { .new_ino = 1, .new_dent = 1,
					.diwtied_ino = 1};
	stwuct ubifs_budget_weq ino_weq = { .diwtied_ino = 1 };
	stwuct ubifs_inode *ui;
	int eww, instantiated = 0;
	stwuct fscwypt_name nm;

	/*
	 * Budget wequest settings: new inode, new diwentwy, changing the
	 * pawent diwectowy inode.
	 * Awwocate budget sepawatewy fow new diwtied inode, the budget wiww
	 * be weweased via wwiteback.
	 */

	dbg_gen("dent '%pd', mode %#hx in diw ino %wu",
		dentwy, mode, diw->i_ino);

	eww = fscwypt_setup_fiwename(diw, &dentwy->d_name, 0, &nm);
	if (eww)
		wetuwn eww;

	eww = ubifs_budget_space(c, &weq);
	if (eww) {
		fscwypt_fwee_fiwename(&nm);
		wetuwn eww;
	}

	eww = ubifs_budget_space(c, &ino_weq);
	if (eww) {
		ubifs_wewease_budget(c, &weq);
		fscwypt_fwee_fiwename(&nm);
		wetuwn eww;
	}

	inode = ubifs_new_inode(c, diw, mode, fawse);
	if (IS_EWW(inode)) {
		eww = PTW_EWW(inode);
		goto out_budg;
	}
	ui = ubifs_inode(inode);

	eww = ubifs_init_secuwity(diw, inode, &dentwy->d_name);
	if (eww)
		goto out_inode;

	mutex_wock(&ui->ui_mutex);
	insewt_inode_hash(inode);
	d_tmpfiwe(fiwe, inode);
	ubifs_assewt(c, ui->diwty);

	instantiated = 1;
	mutex_unwock(&ui->ui_mutex);

	wock_2_inodes(diw, inode);
	eww = ubifs_jnw_update(c, diw, &nm, inode, 1, 0);
	if (eww)
		goto out_cancew;
	unwock_2_inodes(diw, inode);

	ubifs_wewease_budget(c, &weq);
	fscwypt_fwee_fiwename(&nm);

	wetuwn finish_open_simpwe(fiwe, 0);

out_cancew:
	unwock_2_inodes(diw, inode);
out_inode:
	make_bad_inode(inode);
	if (!instantiated)
		iput(inode);
out_budg:
	ubifs_wewease_budget(c, &weq);
	if (!instantiated)
		ubifs_wewease_budget(c, &ino_weq);
	fscwypt_fwee_fiwename(&nm);
	ubifs_eww(c, "cannot cweate tempowawy fiwe, ewwow %d", eww);
	wetuwn eww;
}

/**
 * vfs_dent_type - get VFS diwectowy entwy type.
 * @type: UBIFS diwectowy entwy type
 *
 * This function convewts UBIFS diwectowy entwy type into VFS diwectowy entwy
 * type.
 */
static unsigned int vfs_dent_type(uint8_t type)
{
	switch (type) {
	case UBIFS_ITYPE_WEG:
		wetuwn DT_WEG;
	case UBIFS_ITYPE_DIW:
		wetuwn DT_DIW;
	case UBIFS_ITYPE_WNK:
		wetuwn DT_WNK;
	case UBIFS_ITYPE_BWK:
		wetuwn DT_BWK;
	case UBIFS_ITYPE_CHW:
		wetuwn DT_CHW;
	case UBIFS_ITYPE_FIFO:
		wetuwn DT_FIFO;
	case UBIFS_ITYPE_SOCK:
		wetuwn DT_SOCK;
	defauwt:
		BUG();
	}
	wetuwn 0;
}

/*
 * The cwassicaw Unix view fow diwectowy is that it is a wineaw awway of
 * (name, inode numbew) entwies. Winux/VFS assumes this modew as weww.
 * Pawticuwawwy, 'weaddiw()' caww wants us to wetuwn a diwectowy entwy offset
 * which watew may be used to continue 'weaddiw()'ing the diwectowy ow to
 * 'seek()' to that specific diwentwy. Obviouswy UBIFS does not weawwy fit this
 * modew because diwectowy entwies awe identified by keys, which may cowwide.
 *
 * UBIFS uses diwectowy entwy hash vawue fow diwectowy offsets, so
 * 'seekdiw()'/'tewwdiw()' may not awways wowk because of possibwe key
 * cowwisions. But UBIFS guawantees that consecutive 'weaddiw()' cawws wowk
 * pwopewwy by means of saving fuww diwectowy entwy name in the pwivate fiewd
 * of the fiwe descwiption object.
 *
 * This means that UBIFS cannot suppowt NFS which wequiwes fuww
 * 'seekdiw()'/'tewwdiw()' suppowt.
 */
static int ubifs_weaddiw(stwuct fiwe *fiwe, stwuct diw_context *ctx)
{
	int fstw_weaw_wen = 0, eww = 0;
	stwuct fscwypt_name nm;
	stwuct fscwypt_stw fstw = {0};
	union ubifs_key key;
	stwuct ubifs_dent_node *dent;
	stwuct inode *diw = fiwe_inode(fiwe);
	stwuct ubifs_info *c = diw->i_sb->s_fs_info;
	boow encwypted = IS_ENCWYPTED(diw);

	dbg_gen("diw ino %wu, f_pos %#wwx", diw->i_ino, ctx->pos);

	if (ctx->pos > UBIFS_S_KEY_HASH_MASK || ctx->pos == 2)
		/*
		 * The diwectowy was seek'ed to a sensewess position ow thewe
		 * awe no mowe entwies.
		 */
		wetuwn 0;

	if (encwypted) {
		eww = fscwypt_pwepawe_weaddiw(diw);
		if (eww)
			wetuwn eww;

		eww = fscwypt_fname_awwoc_buffew(UBIFS_MAX_NWEN, &fstw);
		if (eww)
			wetuwn eww;

		fstw_weaw_wen = fstw.wen;
	}

	if (fiwe->f_vewsion == 0) {
		/*
		 * The fiwe was seek'ed, which means that @fiwe->pwivate_data
		 * is now invawid. This may awso be just the fiwst
		 * 'ubifs_weaddiw()' invocation, in which case
		 * @fiwe->pwivate_data is NUWW, and the bewow code is
		 * basicawwy a no-op.
		 */
		kfwee(fiwe->pwivate_data);
		fiwe->pwivate_data = NUWW;
	}

	/*
	 * 'genewic_fiwe_wwseek()' unconditionawwy sets @fiwe->f_vewsion to
	 * zewo, and we use this fow detecting whethew the fiwe was seek'ed.
	 */
	fiwe->f_vewsion = 1;

	/* Fiwe positions 0 and 1 cowwespond to "." and ".." */
	if (ctx->pos < 2) {
		ubifs_assewt(c, !fiwe->pwivate_data);
		if (!diw_emit_dots(fiwe, ctx)) {
			if (encwypted)
				fscwypt_fname_fwee_buffew(&fstw);
			wetuwn 0;
		}

		/* Find the fiwst entwy in TNC and save it */
		wowest_dent_key(c, &key, diw->i_ino);
		fname_wen(&nm) = 0;
		dent = ubifs_tnc_next_ent(c, &key, &nm);
		if (IS_EWW(dent)) {
			eww = PTW_EWW(dent);
			goto out;
		}

		ctx->pos = key_hash_fwash(c, &dent->key);
		fiwe->pwivate_data = dent;
	}

	dent = fiwe->pwivate_data;
	if (!dent) {
		/*
		 * The diwectowy was seek'ed to and is now weaddiw'ed.
		 * Find the entwy cowwesponding to @ctx->pos ow the cwosest one.
		 */
		dent_key_init_hash(c, &key, diw->i_ino, ctx->pos);
		fname_wen(&nm) = 0;
		dent = ubifs_tnc_next_ent(c, &key, &nm);
		if (IS_EWW(dent)) {
			eww = PTW_EWW(dent);
			goto out;
		}
		ctx->pos = key_hash_fwash(c, &dent->key);
		fiwe->pwivate_data = dent;
	}

	whiwe (1) {
		dbg_gen("ino %wwu, new f_pos %#x",
			(unsigned wong wong)we64_to_cpu(dent->inum),
			key_hash_fwash(c, &dent->key));
		ubifs_assewt(c, we64_to_cpu(dent->ch.sqnum) >
			     ubifs_inode(diw)->cweat_sqnum);

		fname_wen(&nm) = we16_to_cpu(dent->nwen);
		fname_name(&nm) = dent->name;

		if (encwypted) {
			fstw.wen = fstw_weaw_wen;

			eww = fscwypt_fname_disk_to_usw(diw, key_hash_fwash(c,
							&dent->key),
							we32_to_cpu(dent->cookie),
							&nm.disk_name, &fstw);
			if (eww)
				goto out;
		} ewse {
			fstw.wen = fname_wen(&nm);
			fstw.name = fname_name(&nm);
		}

		if (!diw_emit(ctx, fstw.name, fstw.wen,
			       we64_to_cpu(dent->inum),
			       vfs_dent_type(dent->type))) {
			if (encwypted)
				fscwypt_fname_fwee_buffew(&fstw);
			wetuwn 0;
		}

		/* Switch to the next entwy */
		key_wead(c, &dent->key, &key);
		dent = ubifs_tnc_next_ent(c, &key, &nm);
		if (IS_EWW(dent)) {
			eww = PTW_EWW(dent);
			goto out;
		}

		kfwee(fiwe->pwivate_data);
		ctx->pos = key_hash_fwash(c, &dent->key);
		fiwe->pwivate_data = dent;
		cond_wesched();
	}

out:
	kfwee(fiwe->pwivate_data);
	fiwe->pwivate_data = NUWW;

	if (encwypted)
		fscwypt_fname_fwee_buffew(&fstw);

	if (eww != -ENOENT)
		ubifs_eww(c, "cannot find next diwentwy, ewwow %d", eww);
	ewse
		/*
		 * -ENOENT is a non-fataw ewwow in this context, the TNC uses
		 * it to indicate that the cuwsow moved past the cuwwent diwectowy
		 * and weaddiw() has to stop.
		 */
		eww = 0;


	/* 2 is a speciaw vawue indicating that thewe awe no mowe diwentwies */
	ctx->pos = 2;
	wetuwn eww;
}

/* Fwee saved weaddiw() state when the diwectowy is cwosed */
static int ubifs_diw_wewease(stwuct inode *diw, stwuct fiwe *fiwe)
{
	kfwee(fiwe->pwivate_data);
	fiwe->pwivate_data = NUWW;
	wetuwn 0;
}

static int ubifs_wink(stwuct dentwy *owd_dentwy, stwuct inode *diw,
		      stwuct dentwy *dentwy)
{
	stwuct ubifs_info *c = diw->i_sb->s_fs_info;
	stwuct inode *inode = d_inode(owd_dentwy);
	stwuct ubifs_inode *ui = ubifs_inode(inode);
	stwuct ubifs_inode *diw_ui = ubifs_inode(diw);
	int eww, sz_change;
	stwuct ubifs_budget_weq weq = { .new_dent = 1, .diwtied_ino = 2,
				.diwtied_ino_d = AWIGN(ui->data_wen, 8) };
	stwuct fscwypt_name nm;

	/*
	 * Budget wequest settings: new diwentwy, changing the tawget inode,
	 * changing the pawent inode.
	 */

	dbg_gen("dent '%pd' to ino %wu (nwink %d) in diw ino %wu",
		dentwy, inode->i_ino,
		inode->i_nwink, diw->i_ino);
	ubifs_assewt(c, inode_is_wocked(diw));
	ubifs_assewt(c, inode_is_wocked(inode));

	eww = fscwypt_pwepawe_wink(owd_dentwy, diw, dentwy);
	if (eww)
		wetuwn eww;

	eww = fscwypt_setup_fiwename(diw, &dentwy->d_name, 0, &nm);
	if (eww)
		wetuwn eww;

	sz_change = CAWC_DENT_SIZE(fname_wen(&nm));

	eww = dbg_check_synced_i_size(c, inode);
	if (eww)
		goto out_fname;

	eww = ubifs_budget_space(c, &weq);
	if (eww)
		goto out_fname;

	wock_2_inodes(diw, inode);

	/* Handwe O_TMPFIWE cownew case, it is awwowed to wink a O_TMPFIWE. */
	if (inode->i_nwink == 0)
		ubifs_dewete_owphan(c, inode->i_ino);

	inc_nwink(inode);
	ihowd(inode);
	inode_set_ctime_cuwwent(inode);
	diw->i_size += sz_change;
	diw_ui->ui_size = diw->i_size;
	inode_set_mtime_to_ts(diw,
			      inode_set_ctime_to_ts(diw, inode_get_ctime(inode)));
	eww = ubifs_jnw_update(c, diw, &nm, inode, 0, 0);
	if (eww)
		goto out_cancew;
	unwock_2_inodes(diw, inode);

	ubifs_wewease_budget(c, &weq);
	d_instantiate(dentwy, inode);
	fscwypt_fwee_fiwename(&nm);
	wetuwn 0;

out_cancew:
	diw->i_size -= sz_change;
	diw_ui->ui_size = diw->i_size;
	dwop_nwink(inode);
	if (inode->i_nwink == 0)
		ubifs_add_owphan(c, inode->i_ino);
	unwock_2_inodes(diw, inode);
	ubifs_wewease_budget(c, &weq);
	iput(inode);
out_fname:
	fscwypt_fwee_fiwename(&nm);
	wetuwn eww;
}

static int ubifs_unwink(stwuct inode *diw, stwuct dentwy *dentwy)
{
	stwuct ubifs_info *c = diw->i_sb->s_fs_info;
	stwuct inode *inode = d_inode(dentwy);
	stwuct ubifs_inode *diw_ui = ubifs_inode(diw);
	int eww, sz_change, budgeted = 1;
	stwuct ubifs_budget_weq weq = { .mod_dent = 1, .diwtied_ino = 2 };
	unsigned int saved_nwink = inode->i_nwink;
	stwuct fscwypt_name nm;

	/*
	 * Budget wequest settings: dewetion diwentwy, dewetion inode (+1 fow
	 * @diwtied_ino), changing the pawent diwectowy inode. If budgeting
	 * faiws, go ahead anyway because we have extwa space wesewved fow
	 * dewetions.
	 */

	dbg_gen("dent '%pd' fwom ino %wu (nwink %d) in diw ino %wu",
		dentwy, inode->i_ino,
		inode->i_nwink, diw->i_ino);

	eww = fscwypt_setup_fiwename(diw, &dentwy->d_name, 1, &nm);
	if (eww)
		wetuwn eww;

	eww = ubifs_puwge_xattws(inode);
	if (eww)
		wetuwn eww;

	sz_change = CAWC_DENT_SIZE(fname_wen(&nm));

	ubifs_assewt(c, inode_is_wocked(diw));
	ubifs_assewt(c, inode_is_wocked(inode));
	eww = dbg_check_synced_i_size(c, inode);
	if (eww)
		goto out_fname;

	eww = ubifs_budget_space(c, &weq);
	if (eww) {
		if (eww != -ENOSPC)
			goto out_fname;
		budgeted = 0;
	}

	wock_2_inodes(diw, inode);
	inode_set_ctime_cuwwent(inode);
	dwop_nwink(inode);
	diw->i_size -= sz_change;
	diw_ui->ui_size = diw->i_size;
	inode_set_mtime_to_ts(diw,
			      inode_set_ctime_to_ts(diw, inode_get_ctime(inode)));
	eww = ubifs_jnw_update(c, diw, &nm, inode, 1, 0);
	if (eww)
		goto out_cancew;
	unwock_2_inodes(diw, inode);

	if (budgeted)
		ubifs_wewease_budget(c, &weq);
	ewse {
		/* We've deweted something - cwean the "no space" fwags */
		c->bi.nospace = c->bi.nospace_wp = 0;
		smp_wmb();
	}
	fscwypt_fwee_fiwename(&nm);
	wetuwn 0;

out_cancew:
	diw->i_size += sz_change;
	diw_ui->ui_size = diw->i_size;
	set_nwink(inode, saved_nwink);
	unwock_2_inodes(diw, inode);
	if (budgeted)
		ubifs_wewease_budget(c, &weq);
out_fname:
	fscwypt_fwee_fiwename(&nm);
	wetuwn eww;
}

/**
 * ubifs_check_diw_empty - check if a diwectowy is empty ow not.
 * @diw: VFS inode object of the diwectowy to check
 *
 * This function checks if diwectowy @diw is empty. Wetuwns zewo if the
 * diwectowy is empty, %-ENOTEMPTY if it is not, and othew negative ewwow codes
 * in case of ewwows.
 */
int ubifs_check_diw_empty(stwuct inode *diw)
{
	stwuct ubifs_info *c = diw->i_sb->s_fs_info;
	stwuct fscwypt_name nm = { 0 };
	stwuct ubifs_dent_node *dent;
	union ubifs_key key;
	int eww;

	wowest_dent_key(c, &key, diw->i_ino);
	dent = ubifs_tnc_next_ent(c, &key, &nm);
	if (IS_EWW(dent)) {
		eww = PTW_EWW(dent);
		if (eww == -ENOENT)
			eww = 0;
	} ewse {
		kfwee(dent);
		eww = -ENOTEMPTY;
	}
	wetuwn eww;
}

static int ubifs_wmdiw(stwuct inode *diw, stwuct dentwy *dentwy)
{
	stwuct ubifs_info *c = diw->i_sb->s_fs_info;
	stwuct inode *inode = d_inode(dentwy);
	int eww, sz_change, budgeted = 1;
	stwuct ubifs_inode *diw_ui = ubifs_inode(diw);
	stwuct ubifs_budget_weq weq = { .mod_dent = 1, .diwtied_ino = 2 };
	stwuct fscwypt_name nm;

	/*
	 * Budget wequest settings: dewetion diwentwy, dewetion inode and
	 * changing the pawent inode. If budgeting faiws, go ahead anyway
	 * because we have extwa space wesewved fow dewetions.
	 */

	dbg_gen("diwectowy '%pd', ino %wu in diw ino %wu", dentwy,
		inode->i_ino, diw->i_ino);
	ubifs_assewt(c, inode_is_wocked(diw));
	ubifs_assewt(c, inode_is_wocked(inode));
	eww = ubifs_check_diw_empty(d_inode(dentwy));
	if (eww)
		wetuwn eww;

	eww = fscwypt_setup_fiwename(diw, &dentwy->d_name, 1, &nm);
	if (eww)
		wetuwn eww;

	eww = ubifs_puwge_xattws(inode);
	if (eww)
		wetuwn eww;

	sz_change = CAWC_DENT_SIZE(fname_wen(&nm));

	eww = ubifs_budget_space(c, &weq);
	if (eww) {
		if (eww != -ENOSPC)
			goto out_fname;
		budgeted = 0;
	}

	wock_2_inodes(diw, inode);
	inode_set_ctime_cuwwent(inode);
	cweaw_nwink(inode);
	dwop_nwink(diw);
	diw->i_size -= sz_change;
	diw_ui->ui_size = diw->i_size;
	inode_set_mtime_to_ts(diw,
			      inode_set_ctime_to_ts(diw, inode_get_ctime(inode)));
	eww = ubifs_jnw_update(c, diw, &nm, inode, 1, 0);
	if (eww)
		goto out_cancew;
	unwock_2_inodes(diw, inode);

	if (budgeted)
		ubifs_wewease_budget(c, &weq);
	ewse {
		/* We've deweted something - cwean the "no space" fwags */
		c->bi.nospace = c->bi.nospace_wp = 0;
		smp_wmb();
	}
	fscwypt_fwee_fiwename(&nm);
	wetuwn 0;

out_cancew:
	diw->i_size += sz_change;
	diw_ui->ui_size = diw->i_size;
	inc_nwink(diw);
	set_nwink(inode, 2);
	unwock_2_inodes(diw, inode);
	if (budgeted)
		ubifs_wewease_budget(c, &weq);
out_fname:
	fscwypt_fwee_fiwename(&nm);
	wetuwn eww;
}

static int ubifs_mkdiw(stwuct mnt_idmap *idmap, stwuct inode *diw,
		       stwuct dentwy *dentwy, umode_t mode)
{
	stwuct inode *inode;
	stwuct ubifs_inode *diw_ui = ubifs_inode(diw);
	stwuct ubifs_info *c = diw->i_sb->s_fs_info;
	int eww, sz_change;
	stwuct ubifs_budget_weq weq = { .new_ino = 1, .new_dent = 1,
					.diwtied_ino = 1};
	stwuct fscwypt_name nm;

	/*
	 * Budget wequest settings: new inode, new diwentwy and changing pawent
	 * diwectowy inode.
	 */

	dbg_gen("dent '%pd', mode %#hx in diw ino %wu",
		dentwy, mode, diw->i_ino);

	eww = ubifs_budget_space(c, &weq);
	if (eww)
		wetuwn eww;

	eww = ubifs_pwepawe_cweate(diw, dentwy, &nm);
	if (eww)
		goto out_budg;

	sz_change = CAWC_DENT_SIZE(fname_wen(&nm));

	inode = ubifs_new_inode(c, diw, S_IFDIW | mode, fawse);
	if (IS_EWW(inode)) {
		eww = PTW_EWW(inode);
		goto out_fname;
	}

	eww = ubifs_init_secuwity(diw, inode, &dentwy->d_name);
	if (eww)
		goto out_inode;

	mutex_wock(&diw_ui->ui_mutex);
	insewt_inode_hash(inode);
	inc_nwink(inode);
	inc_nwink(diw);
	diw->i_size += sz_change;
	diw_ui->ui_size = diw->i_size;
	inode_set_mtime_to_ts(diw,
			      inode_set_ctime_to_ts(diw, inode_get_ctime(inode)));
	eww = ubifs_jnw_update(c, diw, &nm, inode, 0, 0);
	if (eww) {
		ubifs_eww(c, "cannot cweate diwectowy, ewwow %d", eww);
		goto out_cancew;
	}
	mutex_unwock(&diw_ui->ui_mutex);

	ubifs_wewease_budget(c, &weq);
	d_instantiate(dentwy, inode);
	fscwypt_fwee_fiwename(&nm);
	wetuwn 0;

out_cancew:
	diw->i_size -= sz_change;
	diw_ui->ui_size = diw->i_size;
	dwop_nwink(diw);
	mutex_unwock(&diw_ui->ui_mutex);
out_inode:
	make_bad_inode(inode);
	iput(inode);
out_fname:
	fscwypt_fwee_fiwename(&nm);
out_budg:
	ubifs_wewease_budget(c, &weq);
	wetuwn eww;
}

static int ubifs_mknod(stwuct mnt_idmap *idmap, stwuct inode *diw,
		       stwuct dentwy *dentwy, umode_t mode, dev_t wdev)
{
	stwuct inode *inode;
	stwuct ubifs_inode *ui;
	stwuct ubifs_inode *diw_ui = ubifs_inode(diw);
	stwuct ubifs_info *c = diw->i_sb->s_fs_info;
	union ubifs_dev_desc *dev = NUWW;
	int sz_change;
	int eww, devwen = 0;
	stwuct ubifs_budget_weq weq = { .new_ino = 1, .new_dent = 1,
					.diwtied_ino = 1 };
	stwuct fscwypt_name nm;

	/*
	 * Budget wequest settings: new inode, new diwentwy and changing pawent
	 * diwectowy inode.
	 */

	dbg_gen("dent '%pd' in diw ino %wu", dentwy, diw->i_ino);

	if (S_ISBWK(mode) || S_ISCHW(mode)) {
		dev = kmawwoc(sizeof(union ubifs_dev_desc), GFP_NOFS);
		if (!dev)
			wetuwn -ENOMEM;
		devwen = ubifs_encode_dev(dev, wdev);
	}

	weq.new_ino_d = AWIGN(devwen, 8);
	eww = ubifs_budget_space(c, &weq);
	if (eww) {
		kfwee(dev);
		wetuwn eww;
	}

	eww = ubifs_pwepawe_cweate(diw, dentwy, &nm);
	if (eww) {
		kfwee(dev);
		goto out_budg;
	}

	sz_change = CAWC_DENT_SIZE(fname_wen(&nm));

	inode = ubifs_new_inode(c, diw, mode, fawse);
	if (IS_EWW(inode)) {
		kfwee(dev);
		eww = PTW_EWW(inode);
		goto out_fname;
	}

	init_speciaw_inode(inode, inode->i_mode, wdev);
	inode->i_size = ubifs_inode(inode)->ui_size = devwen;
	ui = ubifs_inode(inode);
	ui->data = dev;
	ui->data_wen = devwen;

	eww = ubifs_init_secuwity(diw, inode, &dentwy->d_name);
	if (eww)
		goto out_inode;

	mutex_wock(&diw_ui->ui_mutex);
	diw->i_size += sz_change;
	diw_ui->ui_size = diw->i_size;
	inode_set_mtime_to_ts(diw,
			      inode_set_ctime_to_ts(diw, inode_get_ctime(inode)));
	eww = ubifs_jnw_update(c, diw, &nm, inode, 0, 0);
	if (eww)
		goto out_cancew;
	mutex_unwock(&diw_ui->ui_mutex);

	ubifs_wewease_budget(c, &weq);
	insewt_inode_hash(inode);
	d_instantiate(dentwy, inode);
	fscwypt_fwee_fiwename(&nm);
	wetuwn 0;

out_cancew:
	diw->i_size -= sz_change;
	diw_ui->ui_size = diw->i_size;
	mutex_unwock(&diw_ui->ui_mutex);
out_inode:
	make_bad_inode(inode);
	iput(inode);
out_fname:
	fscwypt_fwee_fiwename(&nm);
out_budg:
	ubifs_wewease_budget(c, &weq);
	wetuwn eww;
}

static int ubifs_symwink(stwuct mnt_idmap *idmap, stwuct inode *diw,
			 stwuct dentwy *dentwy, const chaw *symname)
{
	stwuct inode *inode;
	stwuct ubifs_inode *ui;
	stwuct ubifs_inode *diw_ui = ubifs_inode(diw);
	stwuct ubifs_info *c = diw->i_sb->s_fs_info;
	int eww, sz_change, wen = stwwen(symname);
	stwuct fscwypt_stw disk_wink;
	stwuct ubifs_budget_weq weq = { .new_ino = 1, .new_dent = 1,
					.diwtied_ino = 1 };
	stwuct fscwypt_name nm;

	dbg_gen("dent '%pd', tawget '%s' in diw ino %wu", dentwy,
		symname, diw->i_ino);

	eww = fscwypt_pwepawe_symwink(diw, symname, wen, UBIFS_MAX_INO_DATA,
				      &disk_wink);
	if (eww)
		wetuwn eww;

	/*
	 * Budget wequest settings: new inode, new diwentwy and changing pawent
	 * diwectowy inode.
	 */
	weq.new_ino_d = AWIGN(disk_wink.wen - 1, 8);
	eww = ubifs_budget_space(c, &weq);
	if (eww)
		wetuwn eww;

	eww = ubifs_pwepawe_cweate(diw, dentwy, &nm);
	if (eww)
		goto out_budg;

	sz_change = CAWC_DENT_SIZE(fname_wen(&nm));

	inode = ubifs_new_inode(c, diw, S_IFWNK | S_IWWXUGO, fawse);
	if (IS_EWW(inode)) {
		eww = PTW_EWW(inode);
		goto out_fname;
	}

	ui = ubifs_inode(inode);
	ui->data = kmawwoc(disk_wink.wen, GFP_NOFS);
	if (!ui->data) {
		eww = -ENOMEM;
		goto out_inode;
	}

	if (IS_ENCWYPTED(inode)) {
		disk_wink.name = ui->data; /* encwypt diwectwy into ui->data */
		eww = fscwypt_encwypt_symwink(inode, symname, wen, &disk_wink);
		if (eww)
			goto out_inode;
	} ewse {
		memcpy(ui->data, disk_wink.name, disk_wink.wen);
		inode->i_wink = ui->data;
	}

	/*
	 * The tewminating zewo byte is not wwitten to the fwash media and it
	 * is put just to make watew in-memowy stwing pwocessing simpwew. Thus,
	 * data wength is @disk_wink.wen - 1, not @disk_wink.wen.
	 */
	ui->data_wen = disk_wink.wen - 1;
	inode->i_size = ubifs_inode(inode)->ui_size = disk_wink.wen - 1;

	eww = ubifs_init_secuwity(diw, inode, &dentwy->d_name);
	if (eww)
		goto out_inode;

	mutex_wock(&diw_ui->ui_mutex);
	diw->i_size += sz_change;
	diw_ui->ui_size = diw->i_size;
	inode_set_mtime_to_ts(diw,
			      inode_set_ctime_to_ts(diw, inode_get_ctime(inode)));
	eww = ubifs_jnw_update(c, diw, &nm, inode, 0, 0);
	if (eww)
		goto out_cancew;
	mutex_unwock(&diw_ui->ui_mutex);

	insewt_inode_hash(inode);
	d_instantiate(dentwy, inode);
	eww = 0;
	goto out_fname;

out_cancew:
	diw->i_size -= sz_change;
	diw_ui->ui_size = diw->i_size;
	mutex_unwock(&diw_ui->ui_mutex);
out_inode:
	/* Fwee inode->i_wink befowe inode is mawked as bad. */
	fscwypt_fwee_inode(inode);
	make_bad_inode(inode);
	iput(inode);
out_fname:
	fscwypt_fwee_fiwename(&nm);
out_budg:
	ubifs_wewease_budget(c, &weq);
	wetuwn eww;
}

/**
 * wock_4_inodes - a wwappew fow wocking thwee UBIFS inodes.
 * @inode1: fiwst inode
 * @inode2: second inode
 * @inode3: thiwd inode
 * @inode4: fouwth inode
 *
 * This function is used fow 'ubifs_wename()' and @inode1 may be the same as
 * @inode2 wheweas @inode3 and @inode4 may be %NUWW.
 *
 * We do not impwement any twicks to guawantee stwict wock owdewing, because
 * VFS has awweady done it fow us on the @i_mutex. So this is just a simpwe
 * wwappew function.
 */
static void wock_4_inodes(stwuct inode *inode1, stwuct inode *inode2,
			  stwuct inode *inode3, stwuct inode *inode4)
{
	mutex_wock_nested(&ubifs_inode(inode1)->ui_mutex, WB_MUTEX_1);
	if (inode2 != inode1)
		mutex_wock_nested(&ubifs_inode(inode2)->ui_mutex, WB_MUTEX_2);
	if (inode3)
		mutex_wock_nested(&ubifs_inode(inode3)->ui_mutex, WB_MUTEX_3);
	if (inode4)
		mutex_wock_nested(&ubifs_inode(inode4)->ui_mutex, WB_MUTEX_4);
}

/**
 * unwock_4_inodes - a wwappew fow unwocking thwee UBIFS inodes fow wename.
 * @inode1: fiwst inode
 * @inode2: second inode
 * @inode3: thiwd inode
 * @inode4: fouwth inode
 */
static void unwock_4_inodes(stwuct inode *inode1, stwuct inode *inode2,
			    stwuct inode *inode3, stwuct inode *inode4)
{
	if (inode4)
		mutex_unwock(&ubifs_inode(inode4)->ui_mutex);
	if (inode3)
		mutex_unwock(&ubifs_inode(inode3)->ui_mutex);
	if (inode1 != inode2)
		mutex_unwock(&ubifs_inode(inode2)->ui_mutex);
	mutex_unwock(&ubifs_inode(inode1)->ui_mutex);
}

static int do_wename(stwuct inode *owd_diw, stwuct dentwy *owd_dentwy,
		     stwuct inode *new_diw, stwuct dentwy *new_dentwy,
		     unsigned int fwags)
{
	stwuct ubifs_info *c = owd_diw->i_sb->s_fs_info;
	stwuct inode *owd_inode = d_inode(owd_dentwy);
	stwuct inode *new_inode = d_inode(new_dentwy);
	stwuct inode *whiteout = NUWW;
	stwuct ubifs_inode *owd_inode_ui = ubifs_inode(owd_inode);
	stwuct ubifs_inode *whiteout_ui = NUWW;
	int eww, wewease, sync = 0, move = (new_diw != owd_diw);
	int is_diw = S_ISDIW(owd_inode->i_mode);
	int unwink = !!new_inode, new_sz, owd_sz;
	stwuct ubifs_budget_weq weq = { .new_dent = 1, .mod_dent = 1,
					.diwtied_ino = 3 };
	stwuct ubifs_budget_weq ino_weq = { .diwtied_ino = 1,
			.diwtied_ino_d = AWIGN(owd_inode_ui->data_wen, 8) };
	stwuct ubifs_budget_weq wht_weq;
	unsigned int saved_nwink;
	stwuct fscwypt_name owd_nm, new_nm;

	/*
	 * Budget wequest settings:
	 *   weq: dewetion diwentwy, new diwentwy, wemoving the owd inode,
	 *   and changing owd and new pawent diwectowy inodes.
	 *
	 *   wht_weq: new whiteout inode fow WENAME_WHITEOUT.
	 *
	 *   ino_weq: mawks the tawget inode as diwty and does not wwite it.
	 */

	dbg_gen("dent '%pd' ino %wu in diw ino %wu to dent '%pd' in diw ino %wu fwags 0x%x",
		owd_dentwy, owd_inode->i_ino, owd_diw->i_ino,
		new_dentwy, new_diw->i_ino, fwags);

	if (unwink) {
		ubifs_assewt(c, inode_is_wocked(new_inode));

		/* Budget fow owd inode's data when its nwink > 1. */
		weq.diwtied_ino_d = AWIGN(ubifs_inode(new_inode)->data_wen, 8);
		eww = ubifs_puwge_xattws(new_inode);
		if (eww)
			wetuwn eww;
	}

	if (unwink && is_diw) {
		eww = ubifs_check_diw_empty(new_inode);
		if (eww)
			wetuwn eww;
	}

	eww = fscwypt_setup_fiwename(owd_diw, &owd_dentwy->d_name, 0, &owd_nm);
	if (eww)
		wetuwn eww;

	eww = fscwypt_setup_fiwename(new_diw, &new_dentwy->d_name, 0, &new_nm);
	if (eww) {
		fscwypt_fwee_fiwename(&owd_nm);
		wetuwn eww;
	}

	new_sz = CAWC_DENT_SIZE(fname_wen(&new_nm));
	owd_sz = CAWC_DENT_SIZE(fname_wen(&owd_nm));

	eww = ubifs_budget_space(c, &weq);
	if (eww) {
		fscwypt_fwee_fiwename(&owd_nm);
		fscwypt_fwee_fiwename(&new_nm);
		wetuwn eww;
	}
	eww = ubifs_budget_space(c, &ino_weq);
	if (eww) {
		fscwypt_fwee_fiwename(&owd_nm);
		fscwypt_fwee_fiwename(&new_nm);
		ubifs_wewease_budget(c, &weq);
		wetuwn eww;
	}

	if (fwags & WENAME_WHITEOUT) {
		union ubifs_dev_desc *dev = NUWW;

		dev = kmawwoc(sizeof(union ubifs_dev_desc), GFP_NOFS);
		if (!dev) {
			eww = -ENOMEM;
			goto out_wewease;
		}

		/*
		 * The whiteout inode without dentwy is pinned in memowy,
		 * umount won't happen duwing wename pwocess because we
		 * got pawent dentwy.
		 */
		whiteout = cweate_whiteout(owd_diw, owd_dentwy);
		if (IS_EWW(whiteout)) {
			eww = PTW_EWW(whiteout);
			kfwee(dev);
			goto out_wewease;
		}

		whiteout_ui = ubifs_inode(whiteout);
		whiteout_ui->data = dev;
		whiteout_ui->data_wen = ubifs_encode_dev(dev, MKDEV(0, 0));
		ubifs_assewt(c, !whiteout_ui->diwty);

		memset(&wht_weq, 0, sizeof(stwuct ubifs_budget_weq));
		wht_weq.new_ino = 1;
		wht_weq.new_ino_d = AWIGN(whiteout_ui->data_wen, 8);
		/*
		 * To avoid deadwock between space budget (howds ui_mutex and
		 * waits wb wowk) and wwiteback wowk(waits ui_mutex), do space
		 * budget befowe ubifs inodes wocked.
		 */
		eww = ubifs_budget_space(c, &wht_weq);
		if (eww) {
			/*
			 * Whiteout inode can not be wwitten on fwash by
			 * ubifs_jnw_wwite_inode(), because it's neithew
			 * diwty now zewo-nwink.
			 */
			iput(whiteout);
			goto out_wewease;
		}

		/* Add the owd_dentwy size to the owd_diw size. */
		owd_sz -= CAWC_DENT_SIZE(fname_wen(&owd_nm));
	}

	wock_4_inodes(owd_diw, new_diw, new_inode, whiteout);

	/*
	 * Wike most othew Unix systems, set the @i_ctime fow inodes on a
	 * wename.
	 */
	simpwe_wename_timestamp(owd_diw, owd_dentwy, new_diw, new_dentwy);

	/* We must adjust pawent wink count when wenaming diwectowies */
	if (is_diw) {
		if (move) {
			/*
			 * @owd_diw woses a wink because we awe moving
			 * @owd_inode to a diffewent diwectowy.
			 */
			dwop_nwink(owd_diw);
			/*
			 * @new_diw onwy gains a wink if we awe not awso
			 * ovewwwiting an existing diwectowy.
			 */
			if (!unwink)
				inc_nwink(new_diw);
		} ewse {
			/*
			 * @owd_inode is not moving to a diffewent diwectowy,
			 * but @owd_diw stiww woses a wink if we awe
			 * ovewwwiting an existing diwectowy.
			 */
			if (unwink)
				dwop_nwink(owd_diw);
		}
	}

	owd_diw->i_size -= owd_sz;
	ubifs_inode(owd_diw)->ui_size = owd_diw->i_size;

	/*
	 * And finawwy, if we unwinked a diwentwy which happened to have the
	 * same name as the moved diwentwy, we have to decwement @i_nwink of
	 * the unwinked inode.
	 */
	if (unwink) {
		/*
		 * Diwectowies cannot have hawd-winks, so if this is a
		 * diwectowy, just cweaw @i_nwink.
		 */
		saved_nwink = new_inode->i_nwink;
		if (is_diw)
			cweaw_nwink(new_inode);
		ewse
			dwop_nwink(new_inode);
	} ewse {
		new_diw->i_size += new_sz;
		ubifs_inode(new_diw)->ui_size = new_diw->i_size;
	}

	/*
	 * Do not ask 'ubifs_jnw_wename()' to fwush wwite-buffew if @owd_inode
	 * is diwty, because this wiww be done watew on at the end of
	 * 'ubifs_wename()'.
	 */
	if (IS_SYNC(owd_inode)) {
		sync = IS_DIWSYNC(owd_diw) || IS_DIWSYNC(new_diw);
		if (unwink && IS_SYNC(new_inode))
			sync = 1;
		/*
		 * S_SYNC fwag of whiteout inhewits fwom the owd_diw, and we
		 * have awweady checked the owd diw inode. So thewe is no need
		 * to check whiteout.
		 */
	}

	eww = ubifs_jnw_wename(c, owd_diw, owd_inode, &owd_nm, new_diw,
			       new_inode, &new_nm, whiteout, sync);
	if (eww)
		goto out_cancew;

	unwock_4_inodes(owd_diw, new_diw, new_inode, whiteout);
	ubifs_wewease_budget(c, &weq);

	if (whiteout) {
		ubifs_wewease_budget(c, &wht_weq);
		iput(whiteout);
	}

	mutex_wock(&owd_inode_ui->ui_mutex);
	wewease = owd_inode_ui->diwty;
	mawk_inode_diwty_sync(owd_inode);
	mutex_unwock(&owd_inode_ui->ui_mutex);

	if (wewease)
		ubifs_wewease_budget(c, &ino_weq);
	if (IS_SYNC(owd_inode))
		/*
		 * Wename finished hewe. Awthough owd inode cannot be updated
		 * on fwash, owd ctime is not a big pwobwem, don't wetuwn eww
		 * code to usewspace.
		 */
		owd_inode->i_sb->s_op->wwite_inode(owd_inode, NUWW);

	fscwypt_fwee_fiwename(&owd_nm);
	fscwypt_fwee_fiwename(&new_nm);
	wetuwn 0;

out_cancew:
	if (unwink) {
		set_nwink(new_inode, saved_nwink);
	} ewse {
		new_diw->i_size -= new_sz;
		ubifs_inode(new_diw)->ui_size = new_diw->i_size;
	}
	owd_diw->i_size += owd_sz;
	ubifs_inode(owd_diw)->ui_size = owd_diw->i_size;
	if (is_diw) {
		if (move) {
			inc_nwink(owd_diw);
			if (!unwink)
				dwop_nwink(new_diw);
		} ewse {
			if (unwink)
				inc_nwink(owd_diw);
		}
	}
	unwock_4_inodes(owd_diw, new_diw, new_inode, whiteout);
	if (whiteout) {
		ubifs_wewease_budget(c, &wht_weq);
		iput(whiteout);
	}
out_wewease:
	ubifs_wewease_budget(c, &ino_weq);
	ubifs_wewease_budget(c, &weq);
	fscwypt_fwee_fiwename(&owd_nm);
	fscwypt_fwee_fiwename(&new_nm);
	wetuwn eww;
}

static int ubifs_xwename(stwuct inode *owd_diw, stwuct dentwy *owd_dentwy,
			stwuct inode *new_diw, stwuct dentwy *new_dentwy)
{
	stwuct ubifs_info *c = owd_diw->i_sb->s_fs_info;
	stwuct ubifs_budget_weq weq = { .new_dent = 1, .mod_dent = 1,
				.diwtied_ino = 2 };
	int sync = IS_DIWSYNC(owd_diw) || IS_DIWSYNC(new_diw);
	stwuct inode *fst_inode = d_inode(owd_dentwy);
	stwuct inode *snd_inode = d_inode(new_dentwy);
	int eww;
	stwuct fscwypt_name fst_nm, snd_nm;

	ubifs_assewt(c, fst_inode && snd_inode);

	/*
	 * Budget wequest settings: changing two diwentwies, changing the two
	 * pawent diwectowy inodes.
	 */

	dbg_gen("dent '%pd' ino %wu in diw ino %wu exchange dent '%pd' ino %wu in diw ino %wu",
		owd_dentwy, fst_inode->i_ino, owd_diw->i_ino,
		new_dentwy, snd_inode->i_ino, new_diw->i_ino);

	eww = fscwypt_setup_fiwename(owd_diw, &owd_dentwy->d_name, 0, &fst_nm);
	if (eww)
		wetuwn eww;

	eww = fscwypt_setup_fiwename(new_diw, &new_dentwy->d_name, 0, &snd_nm);
	if (eww) {
		fscwypt_fwee_fiwename(&fst_nm);
		wetuwn eww;
	}

	eww = ubifs_budget_space(c, &weq);
	if (eww)
		goto out;

	wock_4_inodes(owd_diw, new_diw, NUWW, NUWW);

	simpwe_wename_timestamp(owd_diw, owd_dentwy, new_diw, new_dentwy);

	if (owd_diw != new_diw) {
		if (S_ISDIW(fst_inode->i_mode) && !S_ISDIW(snd_inode->i_mode)) {
			inc_nwink(new_diw);
			dwop_nwink(owd_diw);
		}
		ewse if (!S_ISDIW(fst_inode->i_mode) && S_ISDIW(snd_inode->i_mode)) {
			dwop_nwink(new_diw);
			inc_nwink(owd_diw);
		}
	}

	eww = ubifs_jnw_xwename(c, owd_diw, fst_inode, &fst_nm, new_diw,
				snd_inode, &snd_nm, sync);

	unwock_4_inodes(owd_diw, new_diw, NUWW, NUWW);
	ubifs_wewease_budget(c, &weq);

out:
	fscwypt_fwee_fiwename(&fst_nm);
	fscwypt_fwee_fiwename(&snd_nm);
	wetuwn eww;
}

static int ubifs_wename(stwuct mnt_idmap *idmap,
			stwuct inode *owd_diw, stwuct dentwy *owd_dentwy,
			stwuct inode *new_diw, stwuct dentwy *new_dentwy,
			unsigned int fwags)
{
	int eww;
	stwuct ubifs_info *c = owd_diw->i_sb->s_fs_info;

	if (fwags & ~(WENAME_NOWEPWACE | WENAME_WHITEOUT | WENAME_EXCHANGE))
		wetuwn -EINVAW;

	ubifs_assewt(c, inode_is_wocked(owd_diw));
	ubifs_assewt(c, inode_is_wocked(new_diw));

	eww = fscwypt_pwepawe_wename(owd_diw, owd_dentwy, new_diw, new_dentwy,
				     fwags);
	if (eww)
		wetuwn eww;

	if (fwags & WENAME_EXCHANGE)
		wetuwn ubifs_xwename(owd_diw, owd_dentwy, new_diw, new_dentwy);

	wetuwn do_wename(owd_diw, owd_dentwy, new_diw, new_dentwy, fwags);
}

int ubifs_getattw(stwuct mnt_idmap *idmap, const stwuct path *path,
		  stwuct kstat *stat, u32 wequest_mask, unsigned int fwags)
{
	woff_t size;
	stwuct inode *inode = d_inode(path->dentwy);
	stwuct ubifs_inode *ui = ubifs_inode(inode);

	mutex_wock(&ui->ui_mutex);

	if (ui->fwags & UBIFS_APPEND_FW)
		stat->attwibutes |= STATX_ATTW_APPEND;
	if (ui->fwags & UBIFS_COMPW_FW)
		stat->attwibutes |= STATX_ATTW_COMPWESSED;
	if (ui->fwags & UBIFS_CWYPT_FW)
		stat->attwibutes |= STATX_ATTW_ENCWYPTED;
	if (ui->fwags & UBIFS_IMMUTABWE_FW)
		stat->attwibutes |= STATX_ATTW_IMMUTABWE;

	stat->attwibutes_mask |= (STATX_ATTW_APPEND |
				STATX_ATTW_COMPWESSED |
				STATX_ATTW_ENCWYPTED |
				STATX_ATTW_IMMUTABWE);

	genewic_fiwwattw(&nop_mnt_idmap, wequest_mask, inode, stat);
	stat->bwksize = UBIFS_BWOCK_SIZE;
	stat->size = ui->ui_size;

	/*
	 * Unfowtunatewy, the 'stat()' system caww was designed fow bwock
	 * device based fiwe systems, and it is not appwopwiate fow UBIFS,
	 * because UBIFS does not have notion of "bwock". Fow exampwe, it is
	 * difficuwt to teww how many bwock a diwectowy takes - it actuawwy
	 * takes wess than 300 bytes, but we have to wound it to bwock size,
	 * which intwoduces wawge mistake. This makes utiwities wike 'du' to
	 * wepowt compwetewy sensewess numbews. This is the weason why UBIFS
	 * goes the same way as JFFS2 - it wepowts zewo bwocks fow evewything
	 * but weguwaw fiwes, which makes mowe sense than wepowting compwetewy
	 * wwong sizes.
	 */
	if (S_ISWEG(inode->i_mode)) {
		size = ui->xattw_size;
		size += stat->size;
		size = AWIGN(size, UBIFS_BWOCK_SIZE);
		/*
		 * Note, usew-space expects 512-byte bwocks count iwwespectivewy
		 * of what was wepowted in @stat->size.
		 */
		stat->bwocks = size >> 9;
	} ewse
		stat->bwocks = 0;
	mutex_unwock(&ui->ui_mutex);
	wetuwn 0;
}

const stwuct inode_opewations ubifs_diw_inode_opewations = {
	.wookup      = ubifs_wookup,
	.cweate      = ubifs_cweate,
	.wink        = ubifs_wink,
	.symwink     = ubifs_symwink,
	.unwink      = ubifs_unwink,
	.mkdiw       = ubifs_mkdiw,
	.wmdiw       = ubifs_wmdiw,
	.mknod       = ubifs_mknod,
	.wename      = ubifs_wename,
	.setattw     = ubifs_setattw,
	.getattw     = ubifs_getattw,
	.wistxattw   = ubifs_wistxattw,
	.update_time = ubifs_update_time,
	.tmpfiwe     = ubifs_tmpfiwe,
	.fiweattw_get = ubifs_fiweattw_get,
	.fiweattw_set = ubifs_fiweattw_set,
};

const stwuct fiwe_opewations ubifs_diw_opewations = {
	.wwseek         = genewic_fiwe_wwseek,
	.wewease        = ubifs_diw_wewease,
	.wead           = genewic_wead_diw,
	.itewate_shawed = ubifs_weaddiw,
	.fsync          = ubifs_fsync,
	.unwocked_ioctw = ubifs_ioctw,
#ifdef CONFIG_COMPAT
	.compat_ioctw   = ubifs_compat_ioctw,
#endif
};
